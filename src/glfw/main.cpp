// Copyright (C) 1997, 1999-2001, 2008 Nathan Lamont
// Copyright (C) 2015-2017 The Antares Authors
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

#include <GLFW/glfw3.h>

#include <time.h>
#include <pn/file>
#include <sfz/sfz.hpp>

#include "config/dirs.hpp"
#include "config/file-prefs-driver.hpp"
#include "config/ledger.hpp"
#include "config/preferences.hpp"
#include "data/scenario-list.hpp"
#include "game/sys.hpp"
#include "glfw/video-driver.hpp"
#include "sound/openal-driver.hpp"
#include "ui/flows/master.hpp"

using sfz::range;

namespace args = sfz::args;

namespace antares {
namespace {

void usage(pn::file_view out, pn::string_view progname, int retcode) {
    pn::format(
            out,
            "usage: {0} [OPTIONS] [scenario]\n"
            "\n"
            "  Antares: a tactical space combat game\n"
            "\n"
            "  arguments:\n"
            "    scenario            select scenario\n"
            "\n"
            "  options:\n"
            "    -h, --app-data      set path to application data\n"
            "                        (default: {0})\n"
            "    -h, --help          display this help screen\n",
            progname, default_application_path());
    exit(retcode);
}

void main(int argc, char* const* argv) {
    pn::string_view progname = sfz::path::basename(argv[0]);
    pn::string      app_data = default_application_path();

    args::callbacks callbacks;

    sfz::optional<pn::string> scenario;
    scenario.emplace(kFactoryScenarioIdentifier);
    callbacks.argument = [&scenario](pn::string_view arg) {
        if (!scenario.has_value()) {
            scenario.emplace(arg.copy());
        } else {
            return false;
        }
        return true;
    };

    callbacks.short_option = [&progname, &app_data](
                                     pn::rune opt, const args::callbacks::get_value_f& get_value) {
        switch (opt.value()) {
            case 'a': app_data = get_value().copy(); return true;
            case 'h': usage(stdout, progname, 0); return true;
            default: return false;
        }
    };

    callbacks.long_option =
            [&callbacks](pn::string_view opt, const args::callbacks::get_value_f& get_value) {
                if (opt == "app-data") {
                    return callbacks.short_option(pn::rune{'a'}, get_value);
                } else if (opt == "help") {
                    return callbacks.short_option(pn::rune{'h'}, get_value);
                } else {
                    return false;
                }
            };

    args::parse(argc - 1, argv + 1, callbacks);

    if (!sfz::path::isdir(application_path())) {
        if (app_data.empty()) {
            throw std::runtime_error(
                    "application data not installed\n"
                    "\n"
                    "Please install it, or specify a path with --app-data\n\n");
        } else {
            throw std::runtime_error(
                    pn::format("{0}: application data not found", application_path()).c_str());
        }
        exit(1);
    } else {
        set_application_path(app_data);
    }

    FilePrefsDriver prefs;

    if (scenario.has_value()) {
        sys.prefs->set_scenario_identifier(*scenario);
        bool         have_scenario = false;
        ScenarioList l;
        for (auto i : range(l.size())) {
            const auto& entry = l.at(i);
            if (entry.identifier == *scenario) {
                if (entry.installed) {
                    have_scenario = true;
                    break;
                } else {
                    throw std::runtime_error(
                            "factory scenario not installed\n"
                            "\n"
                            "Please run antares-install-data");
                }
            }
        }
        if (!have_scenario) {
            throw std::runtime_error(
                    pn::format("{1}: scenario not installed\n", progname, *scenario).c_str());
        }
    }

    DirectoryLedger   ledger;
    OpenAlSoundDriver sound;
    GLFWVideoDriver   video;
    video.loop(new Master(time(NULL)));
}

void print_nested_exception(const std::exception& e) {
    pn::format(stderr, ": {0}", e.what());
    try {
        std::rethrow_if_nested(e);
    } catch (const std::exception& e) {
        print_nested_exception(e);
    }
}

void print_exception(pn::string_view progname, const std::exception& e) {
    pn::format(stderr, "{0}: {1}", sfz::path::basename(progname), e.what());
    try {
        std::rethrow_if_nested(e);
    } catch (const std::exception& e) {
        print_nested_exception(e);
    }
    pn::format(stderr, "\n");
}

}  // namespace
}  // namespace antares

int main(int argc, char* const* argv) {
    try {
        antares::main(argc, argv);
    } catch (const std::exception& e) {
        antares::print_exception(argv[0], e);
        return 1;
    }
    return 0;
}
