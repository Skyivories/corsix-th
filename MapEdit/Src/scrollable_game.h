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

#pragma once
// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif
// ----------------------------
#include "embedded_game.h"

class ScrollableGamePanel : public wxPanel, public IEmbeddedGamePanel
{
public:
    ScrollableGamePanel(wxWindow *pParent);
    ~ScrollableGamePanel();

    void setExtraLuaInitFunction(lua_CFunction fn, void* arg);
    void setLogWindow(frmLog *pLogWindow);
    bool loadLua();

    lua_State* getLua();
    THMap* getMap();

    enum
    {
        ID_X_SCROLL = wxID_HIGHEST + 1,
        ID_Y_SCROLL
    };

protected:
    EmbeddedGamePanel* m_pGamePanel;
    wxScrollBar* m_pMapScrollX;
    wxScrollBar* m_pMapScrollY;
    lua_CFunction m_fnExtraInit;
    void* m_pExtraInitArg;
    bool m_bShouldRespondToScroll;

    void _onResize(wxSizeEvent& e);
    void _onScroll(wxScrollEvent& e);

    static int _l_extra_init(lua_State *L);
    static int _l_init_with_app(lua_State *L);
    static int _l_on_ui_scroll_map(lua_State *L);

    DECLARE_EVENT_TABLE();
};
