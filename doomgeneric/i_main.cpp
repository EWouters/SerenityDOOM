//
// Copyright(C) 1993-1996 Id Software, Inc.
// Copyright(C) 2005-2014 Simon Howard
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// DESCRIPTION:
//	Main program, simply calls D_DoomMain high level loop.
//

//#include "config.h"

#include <LibGUI/Action.h>
#include <LibGUI/Application.h>
#include <LibGUI/Menu.h>
#include <LibGUI/MenuBar.h>

#include <stdio.h>

extern "C" {
//#include "doomtype.h"
//#include "i_system.h"

#include "m_argv.h"

//
// D_DoomMain()
// Not a globally visible function, just included for source reference,
// calls all startup code, parses command line options.
//

void D_DoomMain(void);

void M_FindResponseFile(void);

void dg_Create();
void DG_SetFullscreen(bool);
}

int main(int argc, char** argv)
{
    GUI::Application app(argc, argv);

    auto menubar = make<GUI::MenuBar>();

    auto doom_menu = GUI::Menu::construct("DOOM");
    doom_menu->add_action(GUI::CommonActions::make_quit_action([](auto&) {
        exit(0);
    }));
    menubar->add_menu(move(doom_menu));

    auto view_menu = GUI::Menu::construct("View");
    auto fullscreen_action = GUI::CommonActions::make_fullscreen_action([&](auto& action) {
        action.set_checked(!action.is_checked());
        DG_SetFullscreen(action.is_checked());
    });
    fullscreen_action->set_checkable(true);
    view_menu->add_action(fullscreen_action);
    menubar->add_menu(move(view_menu));

    app.set_menubar(move(menubar));

    // save arguments

    myargc = argc;
    myargv = argv;

    M_FindResponseFile();

    // start doom
    printf("Starting D_DoomMain\r\n");

    dg_Create();

    D_DoomMain();

    return 0;
}
