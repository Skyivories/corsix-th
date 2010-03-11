/*
Copyright (c) 2010 Peter "Corsix" Cawley

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

#include "th_lua_internal.h"
#include "th_gfx.h"
#include "th_map.h"

static int l_anims_new(lua_State *L)
{
    THAnimationManager* pAnims = luaT_stdnew<THAnimationManager>(L, LUA_ENVIRONINDEX, true);
    return 1;
}

static int l_anims_set_spritesheet(lua_State *L)
{
    THAnimationManager* pAnims = luaT_testuserdata<THAnimationManager>(L);
    THSpriteSheet* pSheet = luaT_testuserdata<THSpriteSheet>(L, 2);
    lua_settop(L, 2);

    pAnims->setSpriteSheet(pSheet);
    luaT_setenvfield(L, 1, "sprites");
    return 1;
}

static int l_anims_load(lua_State *L)
{
    THAnimationManager* pAnims = luaT_testuserdata<THAnimationManager>(L);
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
    THAnimationManager* pAnims = luaT_testuserdata<THAnimationManager>(L);
    int iAnim = luaL_checkint(L, 2);

    lua_pushinteger(L, pAnims->getFirstFrame((unsigned int)iAnim));
    return 1;
}

static int l_anims_getnext(lua_State *L)
{
    THAnimationManager* pAnims = luaT_testuserdata<THAnimationManager>(L);
    int iFrame = luaL_checkint(L, 2);

    lua_pushinteger(L, pAnims->getNextFrame((unsigned int)iFrame));
    return 1;
}

static int l_anims_set_alt_pal(lua_State *L)
{
    THAnimationManager* pAnims = luaT_testuserdata<THAnimationManager>(L);
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

static int l_anims_set_marker(lua_State *L)
{
    THAnimationManager* pAnims = luaT_testuserdata<THAnimationManager>(L);
    lua_pushboolean(L, pAnims->setFrameMarker((unsigned int)luaL_checkinteger(L, 2),
        luaL_checkint(L, 3), luaL_checkint(L, 4)) ? 1 : 0);
    return 1;
}

static int l_anims_set_secondary_marker(lua_State *L)
{
    THAnimationManager* pAnims = luaT_testuserdata<THAnimationManager>(L);
    lua_pushboolean(L, pAnims->setFrameSecondaryMarker((unsigned int)luaL_checkinteger(L, 2),
        luaL_checkint(L, 3), luaL_checkint(L, 4)) ? 1 : 0);
    return 1;
}

static int l_anims_draw(lua_State *L)
{
    THAnimationManager* pAnims = luaT_testuserdata<THAnimationManager>(L);
    THRenderTarget* pCanvas = luaT_testuserdata<THRenderTarget>(L, 2);
    int iFrame = luaL_checkint(L, 3);
    THLayers_t* pLayers = luaT_testuserdata<THLayers_t>(L, 4, lua_upvalueindex(2));
    int iX = luaL_checkint(L, 5);
    int iY = luaL_checkint(L, 6);
    int iFlags = luaL_optint(L, 7, 0);
    
    pAnims->drawFrame(pCanvas, (unsigned int)iFrame, *pLayers, iX, iY, iFlags);

    lua_settop(L, 1);
    return 1;
}

static int l_anim_new(lua_State *L)
{
    THAnimation* pAnimation = luaT_stdnew<THAnimation>(L, LUA_ENVIRONINDEX, true);
    lua_rawgeti(L, LUA_ENVIRONINDEX, 2);
    lua_pushlightuserdata(L, pAnimation);
    lua_pushvalue(L, -3);
    lua_rawset(L, -3);
    lua_pop(L, 1);
    return 1;
}

static int l_anim_persist(lua_State *L)
{
    THAnimation* pAnimation = luaT_testuserdata<THAnimation>(L);
    lua_settop(L, 2);
    lua_insert(L, 1);
    LuaPersistWriter* pWriter = (LuaPersistWriter*)lua_touserdata(L, 1);

    pAnimation->persist(pWriter);
    lua_rawgeti(L, LUA_ENVIRONINDEX, 1);
    lua_pushlightuserdata(L, pAnimation);
    lua_gettable(L, -2);
    pWriter->writeStackObject(-1);
    lua_pop(L, 2);
    return 0;
}

static int l_anim_depersist(lua_State *L)
{
    THAnimation* pAnimation = luaT_testuserdata<THAnimation>(L);
    lua_settop(L, 2);
    lua_insert(L, 1);
    LuaPersistReader* pReader = (LuaPersistReader*)lua_touserdata(L, 1);

    new (pAnimation) THAnimation; // Call constructor

    lua_rawgeti(L, LUA_ENVIRONINDEX, 2);
    lua_pushlightuserdata(L, pAnimation);
    lua_pushvalue(L, 2);
    lua_settable(L, -3);
    lua_pop(L, 1);
    pAnimation->depersist(pReader);
    lua_rawgeti(L, LUA_ENVIRONINDEX, 1);
    lua_pushlightuserdata(L, pAnimation);
    if(!pReader->readStackObject())
        return 0;
    lua_settable(L, -3);
    lua_pop(L, 1);
    return 0;
}

static int l_anim_set_hitresult(lua_State *L)
{
    luaL_checktype(L, 1, LUA_TUSERDATA);
    lua_settop(L, 2);
    lua_rawgeti(L, LUA_ENVIRONINDEX, 1);
    lua_pushlightuserdata(L, lua_touserdata(L, 1));
    lua_pushvalue(L, 2);
    lua_settable(L, 3);
    lua_settop(L, 1);
    return 1;
}

static int l_anim_set_frame(lua_State *L)
{
    THAnimation* pAnimation = luaT_testuserdata<THAnimation>(L);
    pAnimation->setFrame(luaL_checkint(L, 2));
    lua_settop(L, 1);
    return 1;
}

static int l_anim_set_crop(lua_State *L)
{
    THAnimation* pAnimation = luaT_testuserdata<THAnimation>(L);
    pAnimation->setCropColumn(luaL_checkint(L, 2));
    lua_settop(L, 1);
    return 1;
}

static int l_anim_set_anim(lua_State *L)
{
    THAnimation* pAnimation = luaT_testuserdata<THAnimation>(L);
    THAnimationManager* pManager = luaT_testuserdata<THAnimationManager>(L, 2);
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
    lua_pushnil(L);
    luaT_setenvfield(L, 1, "morph_target");

    return 1;
}

static int l_anim_set_morph(lua_State *L)
{
    THAnimation* pAnimation = luaT_testuserdata<THAnimation>(L);
    THAnimation* pMorphTarget = luaT_testuserdata<THAnimation>(L, 2, LUA_ENVIRONINDEX);

    pAnimation->setMorphTarget(pMorphTarget);
    lua_settop(L, 2);
    luaT_setenvfield(L, 1, "morph_target");

    return 1;
}

static int l_anim_get_anim(lua_State *L)
{
    THAnimation* pAnimation = luaT_testuserdata<THAnimation>(L);
    lua_pushinteger(L, pAnimation->getAnimation());

    return 1;
}

static int l_anim_set_tile(lua_State *L)
{
    THAnimation* pAnimation = luaT_testuserdata<THAnimation>(L);
    if(lua_isnoneornil(L, 2))
    {
        pAnimation->removeFromTile();
        lua_pushnil(L);
        luaT_setenvfield(L, 1, "map");
        lua_settop(L, 1);
    }
    else
    {
        THMap* pMap = luaT_testuserdata<THMap>(L, 2);
        THMapNode* pNode = pMap->getNode(luaL_checkint(L, 3) - 1, luaL_checkint(L, 4) - 1);
        if(pNode)
            pAnimation->attachToTile(pNode);
        else
        {
            luaL_argerror(L, 3, lua_pushfstring(L, "Map index out of bounds ("
                LUA_NUMBER_FMT "," LUA_NUMBER_FMT ")", lua_tonumber(L, 3),
                lua_tonumber(L, 4)));
        }

        lua_settop(L, 2);
        luaT_setenvfield(L, 1, "map");
    }

    return 1;
}

static int l_anim_get_tile(lua_State *L)
{
    THAnimation* pAnimation = luaT_testuserdata<THAnimation>(L);
    lua_settop(L, 1);
    lua_getfenv(L, 1);
    lua_getfield(L, 2, "map");
    lua_replace(L, 2);
    if(lua_isnil(L, 2))
    {
        return 0;
    }
    THMap* pMap = (THMap*)lua_touserdata(L, 2);
    const THLinkList* pListNode = pAnimation->getPrevious();
    while(pListNode->pPrev)
    {
        pListNode = pListNode->pPrev;
    }
    // Casting pListNode to a THMapNode* is slightly dubious, but it should
    // work. If on the normal list, then pListNode will be a THMapNode*, and
    // all is fine. However, if on the early list, pListNode will be pointing
    // to a member of a THMapNode, so we're relying on pointer arithmetic
    // being a subtract and integer divide by sizeof(THMapNode) to yield the
    // correct map node.
    const THMapNode *pRootNode = pMap->getNodeUnchecked(0, 0);
    uintptr_t iDiff = reinterpret_cast<const char*>(pListNode) -
                      reinterpret_cast<const char*>(pRootNode);
    int iIndex = (int)(iDiff / sizeof(THMapNode));
    int iY = iIndex / pMap->getWidth();
    int iX = iIndex - (iY * pMap->getWidth());
    lua_pushinteger(L, iX + 1);
    lua_pushinteger(L, iY + 1);
    return 3; // map, x, y
}

static int l_anim_set_parent(lua_State *L)
{
    THAnimation* pAnimation = luaT_testuserdata<THAnimation>(L);
    THAnimation* pParent = luaT_testuserdata<THAnimation>(L, 2, LUA_ENVIRONINDEX, false);
    pAnimation->setParent(pParent);
    lua_settop(L, 1);
    return 1;
}

static int l_anim_set_flag(lua_State *L)
{
    THAnimation* pAnimation = luaT_testuserdata<THAnimation>(L);
    pAnimation->setFlags(luaL_checkint(L, 2));

    lua_settop(L, 1);
    return 1;
}

static int l_anim_set_flag_partial(lua_State *L)
{
    THAnimation* pAnimation = luaT_testuserdata<THAnimation>(L);
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
    THAnimation* pAnimation = luaT_testuserdata<THAnimation>(L);
    pAnimation->setFlags(pAnimation->getFlags() & ~(THDF_Alpha50 | THDF_Alpha75));

    lua_settop(L, 1);
    return 1;
}

static int l_anim_make_invisible(lua_State *L)
{
    THAnimation* pAnimation = luaT_testuserdata<THAnimation>(L);
    pAnimation->setFlags(pAnimation->getFlags() | THDF_Alpha50 | THDF_Alpha75);

    lua_settop(L, 1);
    return 1;
}

static int l_anim_get_flag(lua_State *L)
{
    THAnimation* pAnimation = luaT_testuserdata<THAnimation>(L);
    lua_pushinteger(L, pAnimation->getFlags());

    return 1;
}

static int l_anim_set_position(lua_State *L)
{
    THAnimation* pAnimation = luaT_testuserdata<THAnimation>(L);

    pAnimation->setPosition(luaL_checkint(L, 2), luaL_checkint(L, 3));

    lua_settop(L, 1);
    return 1;
}

static int l_anim_get_position(lua_State *L)
{
    THAnimation* pAnimation = luaT_testuserdata<THAnimation>(L);

    lua_pushinteger(L, pAnimation->getX());
    lua_pushinteger(L, pAnimation->getY());

    return 2;
}

static int l_anim_set_speed(lua_State *L)
{
    THAnimation* pAnimation = luaT_testuserdata<THAnimation>(L);

    pAnimation->setSpeed(luaL_optint(L, 2, 0), luaL_optint(L, 3, 0));

    lua_settop(L, 1);
    return 1;
}

static int l_anim_set_layer(lua_State *L)
{
    THAnimation* pAnimation = luaT_testuserdata<THAnimation>(L);

    pAnimation->setLayer(luaL_checkint(L, 2), luaL_optint(L, 3, 0));

    lua_settop(L, 1);
    return 1;
}

static int l_anim_set_tag(lua_State *L)
{
    THAnimation* pAnimation = luaT_testuserdata<THAnimation>(L);
    lua_settop(L, 2);
    luaT_setenvfield(L, 1, "tag");
    return 1;
}

static int l_anim_get_tag(lua_State *L)
{
    THAnimation* pAnimation = luaT_testuserdata<THAnimation>(L);
    lua_settop(L, 1);
    lua_getfenv(L, 1);
    lua_getfield(L, 2, "tag");
    return 1;
}

static int l_anim_get_marker(lua_State *L)
{
    THAnimation* pAnimation = luaT_testuserdata<THAnimation>(L);
    int iX = 0;
    int iY = 0;
    pAnimation->getMarker(&iX, &iY);
    lua_pushinteger(L, iX);
    lua_pushinteger(L, iY);
    return 2;
}

static int l_anim_get_secondary_marker(lua_State *L)
{
    THAnimation* pAnimation = luaT_testuserdata<THAnimation>(L);
    int iX = 0;
    int iY = 0;
    pAnimation->getSecondaryMarker(&iX, &iY);
    lua_pushinteger(L, iX);
    lua_pushinteger(L, iY);
    return 2;
}

static int l_anim_tick(lua_State *L)
{
    THAnimation* pAnimation = luaT_testuserdata<THAnimation>(L);
    pAnimation->tick();
    lua_settop(L, 1);
    return 1;
}

static int l_anim_draw(lua_State *L)
{
    THAnimation* pAnimation = luaT_testuserdata<THAnimation>(L);
    THRenderTarget* pCanvas = luaT_testuserdata<THRenderTarget>(L, 2);
    pAnimation->draw(pCanvas, luaL_checkint(L, 3), luaL_checkint(L, 4));
    lua_settop(L, 1);
    return 1;
}

void THLuaRegisterAnims(const THLuaRegisterState_t *pState)
{
    // Anims
    luaT_class(THAnimationManager, l_anims_new, "anims", MT_Anims);
    luaT_setfunction(l_anims_load, "load");
    luaT_setfunction(l_anims_set_spritesheet, "setSheet", MT_Sheet);
    luaT_setfunction(l_anims_getfirst, "getFirstFrame");
    luaT_setfunction(l_anims_getnext, "getNextFrame");
    luaT_setfunction(l_anims_set_alt_pal, "setAnimationGhostPalette");
    luaT_setfunction(l_anims_set_marker, "setFrameMarker");
    luaT_setfunction(l_anims_set_secondary_marker, "setFrameSecondaryMarker");
    luaT_setfunction(l_anims_draw, "draw", MT_Surface, MT_Layers);
    luaT_endclass();

    // Weak table at AnimMetatable[1] for light UD -> object lookup
    // For hitTest / setHitTestResult
    lua_newtable(pState->L);
    lua_createtable(pState->L, 0, 1);
    lua_pushliteral(pState->L, "v");
    lua_setfield(pState->L, -2, "__mode");
    lua_setmetatable(pState->L, -2);
    lua_rawseti(pState->L, pState->aiMetatables[MT_Anim], 1);

    // Weak table at AnimMetatable[2] for light UD -> full UD lookup
    // For persisting Map
    lua_newtable(pState->L);
    lua_createtable(pState->L, 0, 1);
    lua_pushliteral(pState->L, "v");
    lua_setfield(pState->L, -2, "__mode");
    lua_setmetatable(pState->L, -2);
    lua_rawseti(pState->L, pState->aiMetatables[MT_Anim], 2);

    // Anim
    luaT_class(THAnimation, l_anim_new, "animation", MT_Anim);
    luaT_setmetamethod(l_anim_persist, "persist");
    luaT_setmetamethod(l_anim_depersist, "depersist");
    luaT_setfunction(l_anim_set_anim, "setAnimation", MT_Anims);
    luaT_setfunction(l_anim_set_crop, "setCrop");
    luaT_setfunction(l_anim_set_morph, "setMorph");
    luaT_setfunction(l_anim_set_frame, "setFrame");
    luaT_setfunction(l_anim_get_anim, "getAnimation");
    luaT_setfunction(l_anim_set_tile, "setTile", MT_Map);
    luaT_setfunction(l_anim_get_tile, "getTile");
    luaT_setfunction(l_anim_set_parent, "setParent");
    luaT_setfunction(l_anim_set_flag, "setFlag");
    luaT_setfunction(l_anim_set_flag_partial, "setPartialFlag");
    luaT_setfunction(l_anim_get_flag, "getFlag");
    luaT_setfunction(l_anim_make_visible, "makeVisible");
    luaT_setfunction(l_anim_make_invisible, "makeInvisible");
    luaT_setfunction(l_anim_set_tag, "setTag");
    luaT_setfunction(l_anim_get_tag, "getTag");
    luaT_setfunction(l_anim_set_position, "setPosition");
    luaT_setfunction(l_anim_get_position, "getPosition");
    luaT_setfunction(l_anim_set_speed, "setSpeed");
    luaT_setfunction(l_anim_set_layer, "setLayer");
    luaT_setfunction(l_anim_set_hitresult, "setHitTestResult");
    luaT_setfunction(l_anim_get_marker, "getMarker");
    luaT_setfunction(l_anim_get_secondary_marker, "getSecondaryMarker");
    luaT_setfunction(l_anim_tick, "tick");
    luaT_setfunction(l_anim_draw, "draw", MT_Surface);
    luaT_endclass();
}
