// Copyright (C) 1997, 1999-2001, 2008 Nathan Lamont
// Copyright (C) 2016 The Antares Authors
//
// This file is part of Antares, a tactical space combat game.
//
// Antares is free software: you can redistribute it and/or modify it
// under the terms of the Lesser GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Antares is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with Antares.  If not, see http://www.gnu.org/licenses/

#include "game/sys.hpp"

#include "config/gamepad.hpp"
#include "config/keys.hpp"
#include "data/string-list.hpp"
#include "drawing/text.hpp"
#include "lang/defines.hpp"

namespace antares {

ANTARES_GLOBAL SystemGlobals sys;

void sys_init() {
    sys.fonts.tactical = new Font("tactical");
    sys.fonts.computer = new Font("computer");
    sys.fonts.button = new Font("button");
    sys.fonts.title = new Font("title");
    sys.fonts.small_button = new Font("button-small");

    sys.key_names = to_vector(StringList(KEY_NAMES));
    sys.key_long_names = to_vector(StringList(KEY_LONG_NAMES));
    sys.gamepad_names = to_vector(StringList(Gamepad::NAMES));
    sys.gamepad_long_names = to_vector(StringList(Gamepad::LONG_NAMES));
}

}  // namespace antares
