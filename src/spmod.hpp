/*  SPMod - SourcePawn Scripting Engine for Half-Life
 *  Copyright (C) 2018  SPMod Development Team
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.

 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.

 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once

// STL C++
#include <memory>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <experimental/filesystem>
#include <exception>
#include <array>
#include <variant>

namespace fs = std::experimental::filesystem;

// C
#include <cstring>
#include <cstdarg>

// Sourcepawn
#include <sp_vm_api.h>

// Metamod & HLSDK
#include <extdll.h>
#include <meta_api.h>

// ReHLDS
#include <osconfig.h>
#include <rehlds_api.h>

extern IRehldsApi *gRehldsApi;
extern const RehldsFuncs_t *gRehldsFuncs;
extern IRehldsHookchains *gRehldsHookchains;
extern IRehldsServerStatic *gRehldsServerStatic;

extern bool initRehldsApi();

// SPMod interface
#include <ISPGlobal.hpp>

using namespace SPMod;

// SPMod specific
#include "PluginSystem.hpp"
#include "ForwardSystem.hpp"
#include "SPGlobal.hpp"

constexpr auto gSPModAuthor = "SPMod Development Team";
constexpr auto gSPModVersion = "0.0.1";

// Core natives (coreNatives.cpp)
extern sp_nativeinfo_t gCoreNatives[];
