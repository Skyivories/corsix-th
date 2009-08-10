/*
Copyright (c) 2009 Peter "Corsix" Cawley

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "config.h"
#include "th_lua.h"
#include "th_map.h"
#include "th_gfx.h"
#include "th_pathfind.h"
#include <new>
#include <string.h>

//! Set a field on the environment table of an object
void luaT_setenvfield(lua_State *L, int index, const char *k)
{
    lua_getfenv(L, index);
    lua_pushstring(L, k);
    lua_pushvalue(L, -3);
    lua_settable(L, -3);
    lua_pop(L, 2);
}

//! Push a C closure as a callable table
static void luaT_pushcclosuretable(lua_State *L, lua_CFunction fn, int n)
{
    lua_pushcclosure(L, fn, n); // .. fn <top
    lua_createtable(L, 0, 1); // .. fn mt <top
    lua_pushliteral(L, "__call"); // .. fn mt __call <top
    lua_pushvalue(L, -3); // .. fn mt __call fn <top
    lua_settable(L, -3); // .. fn mt <top
    lua_newtable(L); // .. fn mt t <top
    lua_replace(L, -3); // .. t mt <top
    lua_setmetatable(L, -2); // .. t <top
}

void luaT_addcleanup(lua_State *L, void(*fnCleanup)(void))
{
    lua_checkstack(L, 2);
    lua_getfield(L, LUA_REGISTRYINDEX, "_CLEANUP");
    int idx = 1 + (int)lua_objlen(L, -1);
    lua_pushlightuserdata(L, (void*)fnCleanup);
    lua_rawseti(L, -2, idx);
    lua_pop(L, 1);
}

//! Check for a string or userdata
const unsigned char* luaT_checkfile(lua_State *L, int idx, size_t* pDataLen)
{
    const unsigned char *pData;
    size_t iLength;
    if(lua_type(L, idx) == LUA_TUSERDATA)
    {
        pData = (const unsigned char*)lua_touserdata(L, idx);
        iLength = lua_objlen(L, idx);
    }
    else
    {
        pData = (const unsigned char*)luaL_checklstring(L, idx, &iLength);
    }
    if(pDataLen != 0)
        *pDataLen = iLength;
    return pData;
}

static int l_map_new(lua_State *L)
{
    THMap* pMap = luaT_stdnew<THMap>(L, LUA_ENVIRONINDEX, true);
    return 1;
}

static int l_map_set_sheet(lua_State *L)
{
    THMap* pMap = luaT_testuserdata<THMap, false>(L, 1, LUA_ENVIRONINDEX, "Map");
    THSpriteSheet* pSheet = luaT_testuserdata<THSpriteSheet, false>(L, 2, lua_upvalueindex(1), "SpriteSheet");
    lua_settop(L, 2);

    pMap->setBlockSheet(pSheet);
    luaT_setenvfield(L, 1, "sprites");
    return 1;
}

static int l_map_load(lua_State *L)
{
    THMap* pMap = luaT_testuserdata<THMap, false>(L, 1, LUA_ENVIRONINDEX, "Map");
    size_t iDataLen;
    const unsigned char* pData = luaT_checkfile(L, 2, &iDataLen);
    if(pMap->loadFromTHFile(pData, iDataLen))
        lua_pushboolean(L, 1);
    else
        lua_pushboolean(L, 0);
    return 1;
}

THAnimation* l_map_updateblueprint_getnextanim(lua_State *L, int& iIndex)
{
    THAnimation *pAnim;
    lua_rawgeti(L, 10, iIndex);
    if(lua_type(L, -1) == LUA_TNIL)
    {
        lua_pop(L, 1);
        pAnim = luaT_new(L, THAnimation);
        lua_pushvalue(L, lua_upvalueindex(2));
        lua_setmetatable(L, -2);
        lua_createtable(L, 0, 2);
        lua_pushvalue(L, 1);
        lua_setfield(L, -2, "map");
        lua_pushvalue(L, 11);
        lua_setfield(L, -2, "animator");
        lua_setfenv(L, -2);
        lua_rawseti(L, 10, iIndex);
    }
    else
    {
        pAnim = luaT_testuserdata<THAnimation, false>(L, -1, lua_upvalueindex(2), "Animation");
        lua_pop(L, 1);
    }
    ++iIndex;
    return pAnim;
}

static int l_map_updateblueprint(lua_State *L)
{
    // NB: This function can be implemented in Lua, but is implemented in C for
    // efficiency.
    const unsigned short iFloorTileGood = 24 + (THDF_Alpha50 << 8);
    const unsigned short iFloorTileGoodCenter = 37 + (THDF_Alpha50 << 8);
    const unsigned short iFloorTileBad  = 67 + (THDF_Alpha50 << 8);
    const unsigned int iWallAnimTopCorner = 124;
    const unsigned int iWallAnim = 120;

    THMap* pMap = luaT_testuserdata<THMap, false>(L, 1, LUA_ENVIRONINDEX, "Map");
    int iOldX = luaL_checkint(L, 2) - 1;
    int iOldY = luaL_checkint(L, 3) - 1;
    int iOldW = luaL_checkint(L, 4);
    int iOldH = luaL_checkint(L, 5);
    int iNewX = luaL_checkint(L, 6) - 1;
    int iNewY = luaL_checkint(L, 7) - 1;
    int iNewW = luaL_checkint(L, 8);
    int iNewH = luaL_checkint(L, 9);
    luaL_checktype(L, 10, LUA_TTABLE); // Animation list
    THAnimationManager* pAnims = luaT_testuserdata<THAnimationManager, false>(L, 11, lua_upvalueindex(1), "Animator");
    bool entire_invalid = lua_toboolean(L, 12) != 0;
    bool valid = !entire_invalid;

    if(iOldX < 0 || iOldY < 0 || (iOldX + iOldW) > pMap->getWidth() || (iOldY + iOldH) > pMap->getHeight())
        luaL_argerror(L, 2, "Old rectangle is out of bounds");
    if(iNewX < 0 || iNewY < 0 || (iNewX + iNewW) >= pMap->getWidth() || (iNewY + iNewH) >= pMap->getHeight())
        luaL_argerror(L, 6, "New rectangle is out of bounds");

    // Clear old floor tiles
    for(int iY = iOldY; iY < iOldY + iOldH; ++iY)
    {
        for(int iX = iOldX; iX < iOldX + iOldW; ++iX)
        {
            THMapNode *pNode = pMap->getNodeUnchecked(iX, iY);
            pNode->iBlock[3] = 0;
            pNode->iFlags |= (pNode->iFlags & THMN_PassableIfNotForBlueprint) >> THMN_PassableIfNotForBlueprint_ShiftDelta;
        }
    }

#define IsValid(node) \
    (!entire_invalid && (((node)->iFlags & (THMN_Buildable | THMN_Room)) == THMN_Buildable))

    // Set new floor tiles
    for(int iY = iNewY; iY < iNewY + iNewH; ++iY)
    {
        for(int iX = iNewX; iX < iNewX + iNewW; ++iX)
        {
            THMapNode *pNode = pMap->getNodeUnchecked(iX, iY);
            if(IsValid(pNode))
                pNode->iBlock[3] = iFloorTileGood;
            else
            {
                pNode->iBlock[3] = iFloorTileBad;
                valid = false;
            }
            pNode->iFlags |= (pNode->iFlags & THMN_Passable) << THMN_PassableIfNotForBlueprint_ShiftDelta;
            pNode->iFlags &= ~THMN_Passable;
        }
    }

    // Set center floor tiles
    if(iNewW >= 2 && iNewH >= 2)
    {
        int iCenterX = iNewX + (iNewW - 2) / 2;
        int iCenterY = iNewY + (iNewH - 2) / 2;

        THMapNode *pNode = pMap->getNodeUnchecked(iCenterX, iCenterY);
        if(pNode->iBlock[3] == iFloorTileGood)
            pNode->iBlock[3] = iFloorTileGoodCenter + 2;
        pNode = pMap->getNodeUnchecked(iCenterX + 1, iCenterY);
        if(pNode->iBlock[3] == iFloorTileGood)
            pNode->iBlock[3] = iFloorTileGoodCenter + 1;
        pNode = pMap->getNodeUnchecked(iCenterX, iCenterY + 1);
        if(pNode->iBlock[3] == iFloorTileGood)
            pNode->iBlock[3] = iFloorTileGoodCenter + 0;
        pNode = pMap->getNodeUnchecked(iCenterX + 1, iCenterY + 1);
        if(pNode->iBlock[3] == iFloorTileGood)
            pNode->iBlock[3] = iFloorTileGoodCenter + 3;
    }

    // Set wall animations
    int iNextAnim = 1;
    THAnimation *pAnim = l_map_updateblueprint_getnextanim(L, iNextAnim);
    THMapNode *pNode = pMap->getNodeUnchecked(iNewX, iNewY);
    pAnim->setAnimation(pAnims, iWallAnimTopCorner);
    pAnim->setFlags(THDF_ListBottom | (IsValid(pNode) ? 0 : THDF_AltPalette));
    pAnim->attachToTile(pNode);

    for(int iX = iNewX; iX < iNewX + iNewW; ++iX)
    {
        if(iX != iNewX)
        {
            pAnim = l_map_updateblueprint_getnextanim(L, iNextAnim);
            pNode = pMap->getNodeUnchecked(iX, iNewY);
            pAnim->setAnimation(pAnims, iWallAnim);
            pAnim->setFlags(THDF_ListBottom | (IsValid(pNode) ? 0 : THDF_AltPalette));
            pAnim->attachToTile(pNode);
            pAnim->setPosition(0, 0);
        }
        pAnim = l_map_updateblueprint_getnextanim(L, iNextAnim);
        pNode = pMap->getNodeUnchecked(iX, iNewY + iNewH - 1);
        pAnim->setAnimation(pAnims, iWallAnim);
        pAnim->setFlags(THDF_ListBottom | (IsValid(pNode) ? 0 : THDF_AltPalette));
        pNode = pMap->getNodeUnchecked(iX, iNewY + iNewH);
        pAnim->attachToTile(pNode);
        pAnim->setPosition(0, -1);
    }
    for(int iY = iNewY; iY < iNewY + iNewH; ++iY)
    {
        if(iY != iNewY)
        {
            pAnim = l_map_updateblueprint_getnextanim(L, iNextAnim);
            pNode = pMap->getNodeUnchecked(iNewX, iY);
            pAnim->setAnimation(pAnims, iWallAnim);
            pAnim->setFlags(THDF_ListBottom | THDF_FlipHorizontal | (IsValid(pNode) ? 0 : THDF_AltPalette));
            pAnim->attachToTile(pNode);
            pAnim->setPosition(2, 0);
        }
        pAnim = l_map_updateblueprint_getnextanim(L, iNextAnim);
        pNode = pMap->getNodeUnchecked(iNewX + iNewW - 1, iY);
        pAnim->setAnimation(pAnims, iWallAnim);
        pAnim->setFlags(THDF_ListBottom | THDF_FlipHorizontal | (IsValid(pNode) ? 0 : THDF_AltPalette));
        pNode = pMap->getNodeUnchecked(iNewX + iNewW, iY);
        pAnim->attachToTile(pNode);
        pAnim->setPosition(2, -1);
    }

#undef IsValid

    // Clear away extra animations
    int iAnimCount = lua_objlen(L, 10);
    if(iAnimCount >= iNextAnim)
    {
        for(int i = iNextAnim; i <= iAnimCount; ++i)
        {
            pAnim = l_map_updateblueprint_getnextanim(L, iNextAnim);
            pAnim->removeFromTile();
            lua_pushnil(L);
            lua_rawseti(L, 10, i);
        }
    }

    lua_pushboolean(L, valid ? 1 : 0);
    return 1;
}

static int l_map_getsize(lua_State *L)
{
    THMap* pMap = luaT_testuserdata<THMap, false>(L, 1, LUA_ENVIRONINDEX, "Map");
    lua_pushinteger(L, pMap->getWidth());
    lua_pushinteger(L, pMap->getHeight());
    return 2;
}

static int l_map_getcell(lua_State *L)
{
    THMap* pMap = luaT_testuserdata<THMap, false>(L, 1, LUA_ENVIRONINDEX, "Map");
    int iX = luaL_checkint(L, 2) - 1; // Lua arrays start at 1 - pretend
    int iY = luaL_checkint(L, 3) - 1; // the map does too.
    THMapNode* pNode = pMap->getNode(iX, iY);
    if(pNode == NULL)
        return luaL_argerror(L, 2, "Map co-ordinates out of bounds");
    if(lua_isnoneornil(L, 4))
    {
        lua_pushinteger(L, pNode->iBlock[0]);
        lua_pushinteger(L, pNode->iBlock[1]);
        lua_pushinteger(L, pNode->iBlock[2]);
        lua_pushinteger(L, pNode->iBlock[3]);
        return 4;
    }
    else
    {
        int iLayer = luaL_checkint(L, 4) - 1;
        if(iLayer < 0 || iLayer >= 4)
            return luaL_argerror(L, 4, "Layer index is out of bounds (1-4)");
        lua_pushinteger(L, pNode->iBlock[iLayer]);
        return 1;
    }
}

static int l_map_getcellflags(lua_State *L)
{
    THMap* pMap = luaT_testuserdata<THMap, false>(L, 1, LUA_ENVIRONINDEX, "Map");
    int iX = luaL_checkint(L, 2) - 1; // Lua arrays start at 1 - pretend
    int iY = luaL_checkint(L, 3) - 1; // the map does too.
    THMapNode* pNode = pMap->getNode(iX, iY);
    if(pNode == NULL)
        return luaL_argerror(L, 2, "Map co-ordinates out of bounds");
    if(lua_type(L, 4) != LUA_TTABLE)
    {
        lua_settop(L, 3);
        lua_createtable(L, 0, 1);
    }
    else
    {
        lua_settop(L, 4);
    }

#define Flag(CName, LName) \
    { \
        lua_pushliteral(L, LName); \
        lua_pushboolean(L, (pNode->iFlags & CName) ? 1 : 0); \
        lua_settable(L, 4); \
    }

    Flag(THMN_Passable, "passable")
    Flag(THMN_Hospital, "hospital")
    Flag(THMN_Buildable, "buildable")
    Flag(THMN_Room, "room")
    Flag(THMN_DoorWest, "doorWest")
    Flag(THMN_DoorNorth, "doorNorth")
    Flag(THMN_CanTravelN, "travelNorth")
    Flag(THMN_CanTravelE, "travelEast")
    Flag(THMN_CanTravelS, "travelSouth")
    Flag(THMN_CanTravelW, "travelWest")

#undef Flag

    return 1;
}

static int l_map_setcellflags(lua_State *L)
{
    THMap* pMap = luaT_testuserdata<THMap, false>(L, 1, LUA_ENVIRONINDEX, "Map");
    int iX = luaL_checkint(L, 2) - 1; // Lua arrays start at 1 - pretend
    int iY = luaL_checkint(L, 3) - 1; // the map does too.
    THMapNode* pNode = pMap->getNode(iX, iY);
    if(pNode == NULL)
        return luaL_argerror(L, 2, "Map co-ordinates out of bounds");
    luaL_checktype(L, 4, LUA_TTABLE);
    lua_settop(L, 4);

#define Flag(CName, LName) \
    if(strcmp(field, LName) == 0) \
    { \
        if(lua_toboolean(L, 6) == 0) \
            pNode->iFlags &= ~CName; \
        else \
            pNode->iFlags |= CName; \
    } else

    lua_pushnil(L);
    while(lua_next(L, 4))
    {
        if(lua_type(L, 5) == LUA_TSTRING)
        {
            const char *field = lua_tostring(L, 5);
            Flag(THMN_Passable, "passable")
            Flag(THMN_Hospital, "hospital")
            Flag(THMN_Buildable, "buildable")
            Flag(THMN_Room, "room")
            Flag(THMN_DoorWest, "doorWest")
            Flag(THMN_DoorNorth, "doorNorth")
            /* else */ {
                luaL_error(L, "Invalid flag \'%s\'", field);
            }
        }
        lua_settop(L, 5);
    }

#undef Flag

    return 0;
}

static int l_map_setwallflags(lua_State *L)
{
    THMap* pMap = luaT_testuserdata<THMap, false>(L, 1, LUA_ENVIRONINDEX, "Map");
    pMap->setAllWallDrawFlags((unsigned char)luaL_checkint(L, 2));
    lua_settop(L, 1);
    return 1;
}

static int l_map_setcell(lua_State *L)
{
    THMap* pMap = luaT_testuserdata<THMap, false>(L, 1, LUA_ENVIRONINDEX, "Map");
    int iX = luaL_checkint(L, 2) - 1; // Lua arrays start at 1 - pretend
    int iY = luaL_checkint(L, 3) - 1; // the map does too.
    THMapNode* pNode = pMap->getNode(iX, iY);
    if(pNode == NULL)
        return luaL_argerror(L, 2, "Map co-ordinates out of bounds");
    int iLayer = luaL_checkint(L, 4) - 1;
    if(iLayer < 0 || iLayer >= 4)
        return luaL_argerror(L, 4, "Layer index is out of bounds (1-4)");
    int iBlock = luaL_checkint(L, 5);

    pNode->iBlock[iLayer] = (uint16_t)iBlock;

    lua_settop(L, 1);
    return 1;
}

static int l_map_mark_room(lua_State *L)
{
    THMap* pMap = luaT_testuserdata<THMap, false>(L, 1, LUA_ENVIRONINDEX, "Map");
    int iX_ = luaL_checkint(L, 2) - 1;
    int iY_ = luaL_checkint(L, 3) - 1;
    int iW = luaL_checkint(L, 4);
    int iH = luaL_checkint(L, 5);
    int iTile = luaL_checkint(L, 6);

    if(iX_ < 0 || iY_ < 0 || (iX_ + iW) > pMap->getWidth() || (iY_ + iH) > pMap->getHeight())
        luaL_argerror(L, 2, "Rectangle is out of bounds");

    for(int iY = iY_; iY < iY_ + iH; ++iY)
    {
        for(int iX = iX_; iX < iX_ + iW; ++iX)
        {
            THMapNode *pNode = pMap->getNodeUnchecked(iX, iY);
            pNode->iBlock[0] = iTile;
            pNode->iBlock[3] = 0;
            unsigned long iFlags = pNode->iFlags;
            iFlags |= THMN_Room;
            iFlags |= (iFlags & THMN_PassableIfNotForBlueprint) >> THMN_PassableIfNotForBlueprint_ShiftDelta;
            iFlags &= ~THMN_PassableIfNotForBlueprint;
            pNode->iFlags = iFlags;
        }
    }

    pMap->updatePathfinding();
    pMap->updateShadows();

    lua_settop(L, 1);
    return 1;
}

static int l_map_draw(lua_State *L)
{
    THMap* pMap = luaT_testuserdata<THMap, false>(L, 1, LUA_ENVIRONINDEX, "Map");
    THRenderTarget* pCanvas = luaT_testuserdata<THRenderTarget, true>(L, 2, lua_upvalueindex(1), "Surface");

    pMap->draw(pCanvas, luaL_checkint(L, 3), luaL_checkint(L, 4), luaL_checkint(L, 5),
        luaL_checkint(L, 6), luaL_optint(L, 7, 0), luaL_optint(L, 8, 0));

    lua_settop(L, 1);
    return 1;
}

static int l_palette_new(lua_State *L)
{
    THPalette* pPalette = luaT_stdnew<THPalette>(L);
    return 1;
}

static int l_palette_load(lua_State *L)
{
    THPalette* pPalette = luaT_testuserdata<THPalette, false>(L, 1, LUA_ENVIRONINDEX, "Palette");
    size_t iDataLen;
    const unsigned char* pData = luaT_checkfile(L, 2, &iDataLen);
    if(pPalette->loadFromTHFile(pData, iDataLen))
        lua_pushboolean(L, 1);
    else
        lua_pushboolean(L, 0);
    return 1;
}

static int l_palette_assign(lua_State *L)
{
    THPalette* pPalette = luaT_testuserdata<THPalette, false>(L, 1, LUA_ENVIRONINDEX, "Palette");
    THRenderTarget* pSurface = luaT_testuserdata<THRenderTarget, true>(L, 2, lua_upvalueindex(1), "Surface");

    pPalette->assign(pSurface, lua_toboolean(L, 3) != 0);

    lua_settop(L, 1);
    return 1;
}

static int l_spritesheet_new(lua_State *L)
{
    THSpriteSheet* pSheet = luaT_stdnew<THSpriteSheet>(L, LUA_ENVIRONINDEX, true);
    return 1;
}

static int l_spritesheet_set_pal(lua_State *L)
{
    THSpriteSheet* pSheet = luaT_testuserdata<THSpriteSheet, false>(L, 1, LUA_ENVIRONINDEX, "SpriteSheet");
    THPalette* pPalette = luaT_testuserdata<THPalette, false>(L, 2, lua_upvalueindex(1), "Palette");
    lua_settop(L, 2);

    pSheet->setPalette(pPalette);
    luaT_setenvfield(L, 1, "palette");
    return 1;
}

static int l_spritesheet_load(lua_State *L)
{
    THSpriteSheet* pSheet = luaT_testuserdata<THSpriteSheet, false>(L, 1, LUA_ENVIRONINDEX, "SpriteSheet");
    size_t iDataLenTable, iDataLenChunk;
    const unsigned char* pDataTable = luaT_checkfile(L, 2, &iDataLenTable);
    const unsigned char* pDataChunk = luaT_checkfile(L, 3, &iDataLenChunk);
    bool bComplex = lua_toboolean(L, 4) != 0;
    THRenderTarget* pSurface = luaT_testuserdata<THRenderTarget, true>(L, 5, lua_upvalueindex(1), NULL);

    if(pSheet->loadFromTHFile(pDataTable, iDataLenTable, pDataChunk, iDataLenChunk, bComplex, pSurface))
        lua_pushboolean(L, 1);
    else
        lua_pushboolean(L, 0);

    return 1;
}

static int l_spritesheet_count(lua_State *L)
{
    THSpriteSheet* pSheet = luaT_testuserdata<THSpriteSheet, false>(L, 1, LUA_ENVIRONINDEX, "SpriteSheet");

    lua_pushinteger(L, pSheet->getSpriteCount());
    return 1;
}

static int l_spritesheet_size(lua_State *L)
{
    THSpriteSheet* pSheet = luaT_testuserdata<THSpriteSheet, false>(L, 1, LUA_ENVIRONINDEX, "SpriteSheet");
    int iSprite = luaL_checkint(L, 2); // No array adjustment
    if(iSprite < 0 || (unsigned int)iSprite >= pSheet->getSpriteCount())
        return luaL_argerror(L, 2, "Sprite index out of bounds");

    unsigned int iWidth, iHeight;
    pSheet->getSpriteSizeUnchecked((unsigned int)iSprite, &iWidth, &iHeight);

    lua_pushinteger(L, iWidth);
    lua_pushinteger(L, iHeight);
    return 2;
}

static int l_spritesheet_draw(lua_State *L)
{
    THSpriteSheet* pSheet = luaT_testuserdata<THSpriteSheet, false>(L, 1, LUA_ENVIRONINDEX, "SpriteSheet");
    THRenderTarget* pCanvas = luaT_testuserdata<THRenderTarget, true>(L, 2, lua_upvalueindex(1), "Surface");
    int iSprite = luaL_checkint(L, 3); // No array adjustment

    pSheet->drawSprite(pCanvas, iSprite, luaL_optint(L, 4, 0), luaL_optint(L, 5, 0), luaL_optint(L, 6, 0));

    lua_settop(L, 1);
    return 1;
}

static int l_font_new(lua_State *L)
{
    THFont* pFont = luaT_stdnew<THFont>(L, LUA_ENVIRONINDEX, true);
    return 1;
}

static int l_font_set_spritesheet(lua_State *L)
{
    THFont* pFont = luaT_testuserdata<THFont, false>(L, 1, LUA_ENVIRONINDEX, "Font");
    THSpriteSheet* pSheet = luaT_testuserdata<THSpriteSheet, false>(L, 2, lua_upvalueindex(1), "SpriteSheet");
    lua_settop(L, 2);

    pFont->setSpriteSheet(pSheet);
    luaT_setenvfield(L, 1, "sprites");
    return 1;
}

static int l_font_set_sep(lua_State *L)
{
    THFont* pFont = luaT_testuserdata<THFont, false>(L, 1, LUA_ENVIRONINDEX, "Font");

    pFont->setSeparation(luaL_checkint(L, 2), luaL_optint(L, 3, 0));

    lua_settop(L, 1);
    return 1;
}

static int l_font_get_size(lua_State *L)
{
    THFont* pFont = luaT_testuserdata<THFont, false>(L, 1, LUA_ENVIRONINDEX, "Font");
    size_t iMsgLen;
    const char* sMsg = luaL_checklstring(L, 2, &iMsgLen);

    int iWidth, iHeight;
    pFont->getTextSize(sMsg, iMsgLen, &iWidth, &iHeight);

    lua_pushinteger(L, iWidth);
    lua_pushinteger(L, iHeight);
    return 2;
}

static int l_font_draw(lua_State *L)
{
    THFont* pFont = luaT_testuserdata<THFont, false>(L, 1, LUA_ENVIRONINDEX, "Font");
    THRenderTarget* pCanvas = luaT_testuserdata<THRenderTarget, true>(L, 2, lua_upvalueindex(1), "Surface");
    size_t iMsgLen;
    const char* sMsg = luaL_checklstring(L, 3, &iMsgLen);
    int iX = luaL_checkint(L, 4);
    int iY = luaL_checkint(L, 5);
    if(!lua_isnoneornil(L, 7))
    {
        int iW = luaL_checkint(L, 6);
        int iH = luaL_checkint(L, 7);
        int iWidth, iHeight;
        pFont->getTextSize(sMsg, iMsgLen, &iWidth, &iHeight);
        if(iW > iWidth)
            iX += (iW - iWidth) / 2;
        if(iH > iHeight)
            iY += (iH - iHeight) / 2;
    }
    pFont->drawText(pCanvas, sMsg, iMsgLen, iX, iY);

    lua_settop(L, 1);
    return 1;
}

static int l_font_draw_wrapped(lua_State *L)
{
    THFont* pFont = luaT_testuserdata<THFont, false>(L, 1, LUA_ENVIRONINDEX, "Font");
    THRenderTarget* pCanvas = luaT_testuserdata<THRenderTarget, true>(L, 2, lua_upvalueindex(1), "Surface");
    size_t iMsgLen;
    const char* sMsg = luaL_checklstring(L, 3, &iMsgLen);
    int iX = luaL_checkint(L, 4);
    int iY = luaL_checkint(L, 5);
    int iW = luaL_checkint(L, 6);

    pFont->drawTextWrapped(pCanvas, sMsg, iMsgLen, iX, iY, iW);

    lua_settop(L, 1);
    return 1;
}

static int l_layers_new(lua_State *L)
{
    THLayers_t* pLayers = luaT_stdnew<THLayers_t>(L, LUA_ENVIRONINDEX, false);
    for(int i = 0; i < 13; ++i)
        pLayers->iLayerContents[i] = 0;
    return 1;
}

static int l_layers_get(lua_State *L)
{
    THLayers_t* pLayers = luaT_testuserdata<THLayers_t, false>(L, 1, LUA_ENVIRONINDEX, "Layers");
    int iLayer = luaL_checkint(L, 2);
    if(0 <= iLayer && iLayer < 13)
        lua_pushinteger(L, pLayers->iLayerContents[iLayer]);
    else
        lua_pushnil(L);
    return 1;
}

static int l_layers_set(lua_State *L)
{
    THLayers_t* pLayers = luaT_testuserdata<THLayers_t, false>(L, 1, LUA_ENVIRONINDEX, "Layers");
    int iLayer = luaL_checkint(L, 2);
    int iValue = luaL_checkint(L, 3);
    if(0 <= iLayer && iLayer < 13)
        pLayers->iLayerContents[iLayer] = (unsigned char)iValue;
    return 0;
}

static int l_anims_new(lua_State *L)
{
    THAnimationManager* pAnims = luaT_stdnew<THAnimationManager>(L, LUA_ENVIRONINDEX, true);
    return 1;
}

static int l_anims_set_spritesheet(lua_State *L)
{
    THAnimationManager* pAnims = luaT_testuserdata<THAnimationManager, false>(L, 1, LUA_ENVIRONINDEX, "Animator");
    THSpriteSheet* pSheet = luaT_testuserdata<THSpriteSheet, false>(L, 2, lua_upvalueindex(1), "SpriteSheet");
    lua_settop(L, 2);

    pAnims->setSpriteSheet(pSheet);
    luaT_setenvfield(L, 1, "sprites");
    return 1;
}

static int l_anims_load(lua_State *L)
{
    THAnimationManager* pAnims = luaT_testuserdata<THAnimationManager, false>(L, 1, LUA_ENVIRONINDEX, "Animator");
    size_t iStartDataLength, iFrameDataLength, iListDataLength, iElementDataLength;
    const unsigned char* pStartData = luaT_checkfile(L, 2, &iStartDataLength);
    const unsigned char* pFrameData = luaT_checkfile(L, 3, &iFrameDataLength);
    const unsigned char* pListData = luaT_checkfile(L, 4, &iListDataLength);
    const unsigned char* pElementData = luaT_checkfile(L, 5, &iElementDataLength);

    if(pAnims->loadFromTHFile(pStartData, iStartDataLength, pFrameData, iFrameDataLength,
        pListData, iListDataLength, pElementData, iElementDataLength))
    {
        lua_pushboolean(L, 1);
    }
    else
    {
        lua_pushboolean(L, 0);
    }

    return 1;
}

static int l_anims_getfirst(lua_State *L)
{
    THAnimationManager* pAnims = luaT_testuserdata<THAnimationManager, false>(L, 1, LUA_ENVIRONINDEX, "Animator");
    int iAnim = luaL_checkint(L, 2);

    lua_pushinteger(L, pAnims->getFirstFrame((unsigned int)iAnim));
    return 1;
}

static int l_anims_getnext(lua_State *L)
{
    THAnimationManager* pAnims = luaT_testuserdata<THAnimationManager, false>(L, 1, LUA_ENVIRONINDEX, "Animator");
    int iFrame = luaL_checkint(L, 2);

    lua_pushinteger(L, pAnims->getNextFrame((unsigned int)iFrame));
    return 1;
}

static int l_anims_set_alt_pal(lua_State *L)
{
    THAnimationManager* pAnims = luaT_testuserdata<THAnimationManager, false>(L, 1, LUA_ENVIRONINDEX, "Animator");
    unsigned int iAnimation = luaL_checkint(L, 2);
    size_t iPalLen;
    const unsigned char *pPal = luaT_checkfile(L, 3, &iPalLen);
    if(iPalLen != 256)
        return luaL_typerror(L, 3, "GhostPalette string");

    pAnims->setAnimationAltPaletteMap(iAnimation, pPal);

    lua_getfenv(L, 1);
    lua_insert(L, 2);
    lua_settop(L, 4);
    lua_settable(L, 2);
    lua_settop(L, 1);
    return 1;
}

static int l_anims_draw(lua_State *L)
{
    THAnimationManager* pAnims = luaT_testuserdata<THAnimationManager, false>(L, 1, LUA_ENVIRONINDEX, "Animator");
    THRenderTarget* pCanvas = luaT_testuserdata<THRenderTarget, true>(L, 2, lua_upvalueindex(1), "Surface");
    int iFrame = luaL_checkint(L, 3);
    THLayers_t* pLayers = luaT_testuserdata<THLayers_t, false>(L, 4, lua_upvalueindex(2), "Layers");
    int iX = luaL_checkint(L, 5);
    int iY = luaL_checkint(L, 6);
    int iFlags = luaL_optint(L, 7, 0);
    
    pAnims->drawFrame(pCanvas, (unsigned int)iFrame, *pLayers, iX, iY, iFlags);

    lua_settop(L, 1);
    return 1;
}

static int l_path_new(lua_State *L)
{
    THPathfinder* pPathfinder = luaT_stdnew<THPathfinder>(L, LUA_ENVIRONINDEX, true);
    return 1;
}

static int l_path_set_map(lua_State *L)
{
    THPathfinder* pPathfinder = luaT_testuserdata<THPathfinder, false>(L, 1, LUA_ENVIRONINDEX, "Pathfinder");
    THMap* pMap = luaT_testuserdata<THMap, false>(L, 2, lua_upvalueindex(1), "Map");
    lua_settop(L, 2);

    pPathfinder->setDefaultMap(pMap);
    luaT_setenvfield(L, 1, "map");
    return 1;
}

static int l_path_distance(lua_State *L)
{
    THPathfinder* pPathfinder = luaT_testuserdata<THPathfinder, false>(L, 1, LUA_ENVIRONINDEX, "Pathfinder");
    if(pPathfinder->findPath(NULL, luaL_checkint(L, 2) - 1, luaL_checkint(L, 3) - 1,
        luaL_checkint(L, 4) - 1, luaL_checkint(L, 5) - 1))
    {
        lua_pushinteger(L, pPathfinder->getPathLength());
    }
    else
    {
        lua_pushboolean(L, 0);
    }
    return 1;
}

static int l_path_path(lua_State *L)
{
    THPathfinder* pPathfinder = luaT_testuserdata<THPathfinder, false>(L, 1, LUA_ENVIRONINDEX, "Pathfinder");
    pPathfinder->findPath(NULL, luaL_checkint(L, 2) - 1, luaL_checkint(L, 3) - 1,
        luaL_checkint(L, 4) - 1, luaL_checkint(L, 5) - 1);
    pPathfinder->pushResult(L);
    return 2;
}

static int l_anim_new(lua_State *L)
{
    THAnimation* pAnimation = luaT_stdnew<THAnimation>(L, LUA_ENVIRONINDEX, true);
    return 1;
}

static int l_anim_set_anim(lua_State *L)
{
    THAnimation* pAnimation = luaT_testuserdata<THAnimation, false>(L, 1, LUA_ENVIRONINDEX, "Animation");
    THAnimationManager* pManager = luaT_testuserdata<THAnimationManager, false>(L, 2, lua_upvalueindex(1), "Animator");
    int iAnim = luaL_checkint(L, 3);
    if(iAnim < 0 || (unsigned int)iAnim >= pManager->getAnimationCount())
        luaL_argerror(L, 3, "Animation index out of bounds");

    if(lua_isnoneornil(L, 4))
        pAnimation->setFlags(0);
    else
        pAnimation->setFlags(luaL_checkint(L, 4));

    pAnimation->setAnimation(pManager, iAnim);
    lua_settop(L, 2);
    luaT_setenvfield(L, 1, "animator");

    return 1;
}

static int l_anim_get_anim(lua_State *L)
{
    THAnimation* pAnimation = luaT_testuserdata<THAnimation, false>(L, 1, LUA_ENVIRONINDEX, "Animation");
    lua_pushinteger(L, pAnimation->getAnimation());

    return 1;
}

static int l_anim_set_tile(lua_State *L)
{
    THAnimation* pAnimation = luaT_testuserdata<THAnimation, false>(L, 1, LUA_ENVIRONINDEX, "Animation");
    if(lua_isnoneornil(L, 2))
    {
        pAnimation->removeFromTile();
        lua_pushnil(L);
        luaT_setenvfield(L, 1, "map");
        lua_settop(L, 1);
    }
    else
    {
        THMap* pMap = luaT_testuserdata<THMap, false>(L, 2, lua_upvalueindex(1), "Map");
        THMapNode* pNode = pMap->getNode(luaL_checkint(L, 3) - 1, luaL_checkint(L, 4) - 1);
        if(pNode)
            pAnimation->attachToTile(pNode);
        else
            luaL_argerror(L, 2, "Map index out of bounds");

        lua_settop(L, 2);
        luaT_setenvfield(L, 1, "map");
    }

    return 1;
}

static int l_anim_get_tile(lua_State *L)
{
    THAnimation* pAnimation = luaT_testuserdata<THAnimation, false>(L, 1, LUA_ENVIRONINDEX, "Animation");
    lua_settop(L, 1);
    lua_getfenv(L, 1);
    lua_getfield(L, 2, "map");
    lua_replace(L, 2);
    if(lua_isnil(L, 2))
    {
        return 0;
    }
    THMap* pMap = (THMap*)lua_touserdata(L, 2);
    THLinkList* pListNode = pAnimation->getPrevious();
    while(pListNode->pPrev)
    {
        pListNode = pListNode->pPrev;
    }
    int iIndex = reinterpret_cast<THMapNode*>(pListNode) - pMap->getNodeUnchecked(0, 0);
    int iY = iIndex / pMap->getWidth();
    int iX = iIndex - (iY * pMap->getWidth());
    lua_pushinteger(L, iX + 1);
    lua_pushinteger(L, iY + 1);
    return 3; // map, x, y
}

static int l_anim_set_flag(lua_State *L)
{
    THAnimation* pAnimation = luaT_testuserdata<THAnimation, false>(L, 1, LUA_ENVIRONINDEX, "Animation");
    pAnimation->setFlags(luaL_checkint(L, 2));

    lua_settop(L, 1);
    return 1;
}

static int l_anim_set_flag_partial(lua_State *L)
{
    THAnimation* pAnimation = luaT_testuserdata<THAnimation, false>(L, 1, LUA_ENVIRONINDEX, "Animation");
    int iFlags = luaL_checkint(L, 2);
    if(lua_isnone(L, 3) || lua_toboolean(L, 3))
    {
        pAnimation->setFlags(pAnimation->getFlags() | iFlags);
    }
    else
    {
        pAnimation->setFlags(pAnimation->getFlags() & ~iFlags);
    }
    lua_settop(L, 1);
    return 1;
}

static int l_anim_make_visible(lua_State *L)
{
    THAnimation* pAnimation = luaT_testuserdata<THAnimation, false>(L, 1, LUA_ENVIRONINDEX, "Animation");
    pAnimation->setFlags(pAnimation->getFlags() & ~(THDF_Alpha50 | THDF_Alpha75));

    lua_settop(L, 1);
    return 1;
}

static int l_anim_make_invisible(lua_State *L)
{
    THAnimation* pAnimation = luaT_testuserdata<THAnimation, false>(L, 1, LUA_ENVIRONINDEX, "Animation");
    pAnimation->setFlags(pAnimation->getFlags() | THDF_Alpha50 | THDF_Alpha75);

    lua_settop(L, 1);
    return 1;
}

static int l_anim_get_flag(lua_State *L)
{
    THAnimation* pAnimation = luaT_testuserdata<THAnimation, false>(L, 1, LUA_ENVIRONINDEX, "Animation");
    lua_pushinteger(L, pAnimation->getFlags());

    return 1;
}

static int l_anim_set_position(lua_State *L)
{
    THAnimation* pAnimation = luaT_testuserdata<THAnimation, false>(L, 1, LUA_ENVIRONINDEX, "Animation");

    pAnimation->setPosition(luaL_checkint(L, 2), luaL_checkint(L, 3));

    lua_settop(L, 1);
    return 1;
}

static int l_anim_get_position(lua_State *L)
{
    THAnimation* pAnimation = luaT_testuserdata<THAnimation, false>(L, 1, LUA_ENVIRONINDEX, "Animation");

    lua_pushinteger(L, pAnimation->getX());
    lua_pushinteger(L, pAnimation->getY());

    return 2;
}

static int l_anim_set_speed(lua_State *L)
{
    THAnimation* pAnimation = luaT_testuserdata<THAnimation, false>(L, 1, LUA_ENVIRONINDEX, "Animation");

    pAnimation->setSpeed(luaL_optint(L, 2, 0), luaL_optint(L, 3, 0));

    lua_settop(L, 1);
    return 1;
}

static int l_anim_set_layer(lua_State *L)
{
    THAnimation* pAnimation = luaT_testuserdata<THAnimation, false>(L, 1, LUA_ENVIRONINDEX, "Animation");

    pAnimation->setLayer(luaL_checkint(L, 2), luaL_optint(L, 3, 0));

    lua_settop(L, 1);
    return 1;
}

static int l_anim_set_tag(lua_State *L)
{
    THAnimation* pAnimation = luaT_testuserdata<THAnimation, false>(L, 1, LUA_ENVIRONINDEX, "Animation");
    lua_settop(L, 2);
    luaT_setenvfield(L, 1, "tag");
    return 1;
}

static int l_anim_get_tag(lua_State *L)
{
    THAnimation* pAnimation = luaT_testuserdata<THAnimation, false>(L, 1, LUA_ENVIRONINDEX, "Animation");
    lua_settop(L, 1);
    lua_getfenv(L, 1);
    lua_getfield(L, 2, "tag");
    return 1;
}

static int l_anim_tick(lua_State *L)
{
    THAnimation* pAnimation = luaT_testuserdata<THAnimation, false>(L, 1, LUA_ENVIRONINDEX, "Animation");
    pAnimation->tick();
    lua_settop(L, 1);
    return 1;
}

static int l_anim_draw(lua_State *L)
{
    THAnimation* pAnimation = luaT_testuserdata<THAnimation, false>(L, 1, LUA_ENVIRONINDEX, "Animation");
    THRenderTarget* pCanvas = luaT_testuserdata<THRenderTarget, true>(L, 2, lua_upvalueindex(1), "Surface");
    pAnimation->draw(pCanvas, luaL_checkint(L, 3), luaL_checkint(L, 4));
    lua_settop(L, 1);
    return 1;
}

static int l_load_strings(lua_State *L)
{
    size_t iDataLength;
    const unsigned char* pData = luaT_checkfile(L, 1, &iDataLength);

    THStringList oStrings;
    if(!oStrings.loadFromTHFile(pData, iDataLength))
    {
        lua_pushboolean(L, 0);
        return 1;
    }

    lua_settop(L, 0);
    lua_createtable(L, (int)oStrings.getSectionCount(), 0);
    for(unsigned int iSec = 0; iSec < oStrings.getSectionCount(); ++iSec)
    {
        unsigned int iCount = oStrings.getSectionSize(iSec);
        lua_createtable(L, (int)iCount, 0);
        for(unsigned int iStr = 0; iStr < iCount; ++iStr)
        {
            lua_pushstring(L, oStrings.getString(iSec, iStr));
            lua_rawseti(L, 2, (int)(iStr + 1));
        }
        lua_rawseti(L, 1, (int)(iSec + 1));
    }
    return 1;
}

int luaopen_th(lua_State *L)
{
    lua_settop(L, 0);

    // Create metatables
    const int iMapMT     = 1; lua_createtable(L, 0, 0);
    const int iPaletteMT = 2; lua_createtable(L, 0, 0);
    const int iSheetMT   = 3; lua_createtable(L, 0, 0);
    const int iFontMT    = 4; lua_createtable(L, 0, 0);
    const int iLayersMT  = 5; lua_createtable(L, 0, 0);
    const int iAnimsMT   = 6; lua_createtable(L, 0, 0);
    const int iAnimMT    = 7; lua_createtable(L, 0, 0);
    const int iPathMT    = 8; lua_createtable(L, 0, 0);
    const int iSurfaceMT = 9; lua_getfield(L, LUA_REGISTRYINDEX, "Surface_meta");

    const int iTH = 10; lua_createtable(L, 0, 5);
    const int iTop = iTH;

    if(lua_isnil(L, iSurfaceMT))
    {
        lua_getglobal(L, "require");
        lua_pushliteral(L, "sdl");
        lua_call(L, 1, 0);
        lua_getfield(L, LUA_REGISTRYINDEX, "Surface_meta");
        lua_replace(L, iSurfaceMT);
    }

    // Misc
    lua_settop(L, iTop);
    lua_pushcfunction(L, l_load_strings);
    lua_setfield(L, iTH, "LoadStrings");

    // Map
    lua_settop(L, iTop);
    lua_pushvalue(L, iMapMT);
    lua_replace(L, LUA_ENVIRONINDEX);
    lua_pushcclosure(L, luaT_stdgc<THMap, false, LUA_ENVIRONINDEX>, 0);
    lua_setfield(L, iMapMT, "__gc");
    luaT_pushcclosuretable(L, l_map_new, 0);
    lua_pushvalue(L, -1);
    lua_setfield(L, iMapMT, "__index");
    lua_pushcfunction(L, l_map_load);
    lua_setfield(L, -2, "load");
    lua_pushcfunction(L, l_map_getsize);
    lua_setfield(L, -2, "size");
    lua_pushcfunction(L, l_map_getcell);
    lua_setfield(L, -2, "getCell");
    lua_pushcfunction(L, l_map_getcellflags);
    lua_setfield(L, -2, "getCellFlags");
    lua_pushcfunction(L, l_map_setcellflags);
    lua_setfield(L, -2, "setCellFlags");
    lua_pushcfunction(L, l_map_setcell);
    lua_setfield(L, -2, "setCell");
    lua_pushcfunction(L, l_map_setwallflags);
    lua_setfield(L, -2, "setWallDrawFlags");
    lua_pushvalue(L, iAnimsMT);
    lua_pushvalue(L, iAnimMT);
    lua_pushcclosure(L, l_map_updateblueprint, 2);
    lua_setfield(L, -2, "updateRoomBlueprint");
    lua_pushcfunction(L, l_map_mark_room);
    lua_setfield(L, -2, "markRoom");
    lua_pushvalue(L, iSheetMT);
    lua_pushcclosure(L, l_map_set_sheet, 1);
    lua_setfield(L, -2, "setSheet");   
    lua_pushvalue(L, iSurfaceMT);
    lua_pushcclosure(L, l_map_draw, 1);
    lua_setfield(L, -2, "draw");
    lua_setfield(L, iTH, "map");

    // Palette
    lua_settop(L, iTop);
    lua_pushvalue(L, iPaletteMT);
    lua_replace(L, LUA_ENVIRONINDEX);
    lua_pushcclosure(L, luaT_stdgc<THPalette, false, LUA_ENVIRONINDEX>, 0);
    lua_setfield(L, iPaletteMT, "__gc");
    luaT_pushcclosuretable(L, l_palette_new, 0);
    lua_pushvalue(L, -1);
    lua_setfield(L, iPaletteMT, "__index");
    lua_pushcfunction(L, l_palette_load);
    lua_setfield(L, -2, "load");
    lua_pushvalue(L, iSurfaceMT);
    lua_pushcclosure(L, l_palette_assign, 1);
    lua_setfield(L, -2, "assign");
    lua_setfield(L, iTH, "palette");

    // Sprite sheet
    lua_settop(L, iTop);
    lua_pushvalue(L, iSheetMT);
    lua_replace(L, LUA_ENVIRONINDEX);
    lua_pushcclosure(L, luaT_stdgc<THSpriteSheet, false, LUA_ENVIRONINDEX>, 0);
    lua_setfield(L, iSheetMT, "__gc");
    lua_pushcfunction(L, l_spritesheet_count);
    lua_setfield(L, iSheetMT, "__len");
    luaT_pushcclosuretable(L, l_spritesheet_new, 0);
    lua_pushvalue(L, -1);
    lua_setfield(L, iSheetMT, "__index");
    lua_pushvalue(L, iSurfaceMT);
    lua_pushcclosure(L, l_spritesheet_load, 1);
    lua_setfield(L, -2, "load");
    lua_pushvalue(L, iPaletteMT);
    lua_pushcclosure(L, l_spritesheet_set_pal, 1);
    lua_setfield(L, -2, "setPalette");
    lua_pushcfunction(L, l_spritesheet_size);
    lua_setfield(L, -2, "size");
    lua_pushvalue(L, iSurfaceMT);
    lua_pushcclosure(L, l_spritesheet_draw, 1);
    lua_setfield(L, -2, "draw");
    lua_setfield(L, iTH, "sheet");

    // Font
    lua_settop(L, iTop);
    lua_pushvalue(L, iFontMT);
    lua_replace(L, LUA_ENVIRONINDEX);
    lua_pushcclosure(L, luaT_stdgc<THFont, false, LUA_ENVIRONINDEX>, 0);
    lua_setfield(L, iFontMT, "__gc");
    luaT_pushcclosuretable(L, l_font_new, 0);
    lua_pushvalue(L, -1);
    lua_setfield(L, iFontMT, "__index");
    lua_pushcfunction(L, l_font_get_size);
    lua_setfield(L, -2, "sizeOf");
    lua_pushvalue(L, iSheetMT);
    lua_pushcclosure(L, l_font_set_spritesheet, 1);
    lua_setfield(L, -2, "setSheet");
    lua_pushcfunction(L, l_font_set_sep);
    lua_setfield(L, -2, "setSeparation");
    lua_pushvalue(L, iSurfaceMT);
    lua_pushcclosure(L, l_font_draw, 1);
    lua_setfield(L, -2, "draw");
    lua_pushvalue(L, iSurfaceMT);
    lua_pushcclosure(L, l_font_draw_wrapped, 1);
    lua_setfield(L, -2, "drawWrapped");
    lua_setfield(L, iTH, "font");

    // Layers
    lua_settop(L, iTop);
    lua_pushvalue(L, iLayersMT);
    lua_replace(L, LUA_ENVIRONINDEX);
    lua_pushcclosure(L, luaT_stdgc<THLayers_t, false, LUA_ENVIRONINDEX>, 0);
    lua_setfield(L, iLayersMT, "__gc");
    lua_pushcfunction(L, l_layers_get);
    lua_setfield(L, iLayersMT, "__index");
    lua_pushcfunction(L, l_layers_set);
    lua_setfield(L, iLayersMT, "__newindex");
    luaT_pushcclosuretable(L, l_layers_new, 0);
    lua_setfield(L, iTH, "layers");

    // Anims
    lua_settop(L, iTop);
    lua_pushvalue(L, iAnimsMT);
    lua_replace(L, LUA_ENVIRONINDEX);
    lua_pushcclosure(L, luaT_stdgc<THAnimationManager, false, LUA_ENVIRONINDEX>, 0);
    lua_setfield(L, iAnimsMT, "__gc");
    luaT_pushcclosuretable(L, l_anims_new, 0);
    lua_pushvalue(L, -1);
    lua_setfield(L, iAnimsMT, "__index");
    lua_pushcfunction(L, l_anims_load);
    lua_setfield(L, -2, "load");
    lua_pushvalue(L, iSheetMT);
    lua_pushcclosure(L, l_anims_set_spritesheet, 1);
    lua_setfield(L, -2, "setSheet");
    lua_pushcfunction(L, l_anims_getfirst);
    lua_setfield(L, -2, "getFirstFrame");
    lua_pushcfunction(L, l_anims_getnext);
    lua_setfield(L, -2, "getNextFrame");
    lua_pushcfunction(L, l_anims_set_alt_pal);
    lua_setfield(L, -2, "setAnimationGhostPalette");
    lua_pushvalue(L, iSurfaceMT);
    lua_pushvalue(L, iLayersMT);
    lua_pushcclosure(L, l_anims_draw, 2);
    lua_setfield(L, -2, "draw");
    lua_setfield(L, iTH, "anims");

    // Anim
    lua_settop(L, iTop);
    lua_pushvalue(L, iAnimMT);
    lua_replace(L, LUA_ENVIRONINDEX);
    lua_pushcclosure(L, luaT_stdgc<THAnimation, false, LUA_ENVIRONINDEX>, 0);
    lua_setfield(L, iAnimMT, "__gc");
    luaT_pushcclosuretable(L, l_anim_new, 0);
    lua_pushvalue(L, -1);
    lua_setfield(L, iAnimMT, "__index");
    lua_pushvalue(L, iAnimsMT);
    lua_pushcclosure(L, l_anim_set_anim, 1);
    lua_setfield(L, -2, "setAnimation");
    lua_pushcfunction(L, l_anim_get_anim);
    lua_setfield(L, -2, "getAnimation");
    lua_pushvalue(L, iMapMT);
    lua_pushcclosure(L, l_anim_set_tile, 1);
    lua_setfield(L, -2, "setTile");
    lua_pushcfunction(L, l_anim_get_tile);
    lua_setfield(L, -2, "getTile");
    lua_pushcfunction(L, l_anim_set_flag);
    lua_setfield(L, -2, "setFlag");
    lua_pushcfunction(L, l_anim_set_flag_partial);
    lua_setfield(L, -2, "setPartialFlag");
    lua_pushcfunction(L, l_anim_get_flag);
    lua_setfield(L, -2, "getFlag");
    lua_pushcfunction(L, l_anim_make_visible);
    lua_setfield(L, -2, "makeVisible");
    lua_pushcfunction(L, l_anim_make_invisible);
    lua_setfield(L, -2, "makeInvisible");
    lua_pushcfunction(L, l_anim_set_tag);
    lua_setfield(L, -2, "setTag");
    lua_pushcfunction(L, l_anim_get_tag);
    lua_setfield(L, -2, "getTag");
    lua_pushcfunction(L, l_anim_set_position);
    lua_setfield(L, -2, "setPosition");
    lua_pushcfunction(L, l_anim_get_position);
    lua_setfield(L, -2, "getPosition");
    lua_pushcfunction(L, l_anim_set_speed);
    lua_setfield(L, -2, "setSpeed");
    lua_pushcfunction(L, l_anim_set_layer);
    lua_setfield(L, -2, "setLayer");
    lua_pushcfunction(L, l_anim_tick);
    lua_setfield(L, -2, "tick");
    lua_pushvalue(L, iSurfaceMT);
    lua_pushcclosure(L, l_anim_draw, 1);
    lua_setfield(L, -2, "draw");
    lua_setfield(L, iTH, "animation");

    // Path
    lua_settop(L, iTop);
    lua_pushvalue(L, iPathMT);
    lua_replace(L, LUA_ENVIRONINDEX);
    lua_pushcclosure(L, luaT_stdgc<THPathfinder, false, LUA_ENVIRONINDEX>, 0);
    lua_setfield(L, iPathMT, "__gc");
    luaT_pushcclosuretable(L, l_path_new, 0);
    lua_pushvalue(L, -1);
    lua_setfield(L, iPathMT, "__index");
    lua_pushcfunction(L, l_path_distance);
    lua_setfield(L, -2, "findDistance");
    lua_pushcfunction(L, l_path_path);
    lua_setfield(L, -2, "findPath");
    lua_pushvalue(L, iMapMT);
    lua_pushcclosure(L, l_path_set_map, 1);
    lua_setfield(L, -2, "setMap");   
    lua_setfield(L, iTH, "pathfinder");

    lua_settop(L, iTH);
    return 1;
}
