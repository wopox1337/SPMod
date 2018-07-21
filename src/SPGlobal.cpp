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

#include "spmod.hpp"

std::unique_ptr<SPGlobal> gSPGlobal;

SPGlobal::SPGlobal(fs::path &&dllDir) : m_SPModDir(dllDir.parent_path().parent_path()),
                                        m_nativeManager(std::make_unique<NativeMngr>()),
                                        m_pluginManager(std::make_unique<PluginMngr>()),
                                        m_forwardManager(std::make_unique<ForwardMngr>()),
                                        m_loggingSystem(std::make_unique<Logger>()),
                                        m_cmdManager(std::make_unique<CommandMngr>()),
                                        m_timerManager(std::make_unique<TimerMngr>()),
                                        m_modName(GET_GAME_INFO(PLID, GINFO_NAME)),
                                        m_spFactory(nullptr)
{
    // Sets default dirs
    setScriptsDir("scripts");
    setLogsDir("logs");
    setDllsDir("dlls");

    // Initialize SourcePawn library
    _initSourcePawn();

    // Add definition spmod natives
    m_nativeManager->addNatives(gSPModModuleDef.get(), gCoreNatives);
    m_nativeManager->addNatives(gSPModModuleDef.get(), gCvarsNatives);
    m_nativeManager->addNatives(gSPModModuleDef.get(), gForwardsNatives);
    m_nativeManager->addNatives(gSPModModuleDef.get(), gStringNatives);
    m_nativeManager->addNatives(gSPModModuleDef.get(), gMessageNatives);
    m_nativeManager->addNatives(gSPModModuleDef.get(), gCmdsNatives);
    m_nativeManager->addNatives(gSPModModuleDef.get(), gTimerNatives);
    m_nativeManager->addNatives(gSPModModuleDef.get(), gFloatNatives);

    // Sets up listener for debbugging
    getSPEnvironment()->APIv2()->SetDebugListener(m_loggingSystem.get());
}

void SPGlobal::setScriptsDir(std::string_view folder)
{
    m_SPModScriptsDir = m_SPModDir / folder.data();
}

void SPGlobal::setLogsDir(std::string_view folder)
{
    m_SPModLogsDir = m_SPModDir / folder.data();
}

void SPGlobal::setDllsDir(std::string_view folder)
{
    m_SPModDllsDir = m_SPModDir / folder.data();
}

void SPGlobal::_initSourcePawn()
{
    fs::path SPDir(getDllsDirCore());
    SPDir /= SPGlobal::sourcepawnLibrary;

#ifdef SP_POSIX
    void *libraryHandle = dlopen(SPDir.c_str(), RTLD_NOW);
#else
    HMODULE libraryHandle = LoadLibrary(SPDir.string().c_str());
#endif

    if (!libraryHandle)
        throw std::runtime_error("Failed to open SourcePawn library");

#ifdef SP_POSIX
    auto getFactoryFunc = reinterpret_cast<SourcePawn::GetSourcePawnFactoryFn>
                                (dlsym(libraryHandle, "GetSourcePawnFactory"));
#else
    auto getFactoryFunc = reinterpret_cast<SourcePawn::GetSourcePawnFactoryFn>
                                (GetProcAddress(libraryHandle, "GetSourcePawnFactory"));
#endif

    if (!getFactoryFunc)
    {
#ifdef SP_POSIX
        dlclose(libraryHandle);
#else
        FreeLibrary(libraryHandle);
#endif
        throw std::runtime_error("Cannot find SourcePawn factory function");
    }

    SourcePawn::ISourcePawnFactory *SPFactory = getFactoryFunc(SOURCEPAWN_API_VERSION);
    if (!SPFactory)
    {
#ifdef SP_POSIX
        dlclose(libraryHandle);
#else
        FreeLibrary(libraryHandle);
#endif
        throw std::runtime_error("Wrong SourcePawn library version");
    }

    m_SPLibraryHandle = libraryHandle;
    m_spFactory = SPFactory;
    m_spFactory->NewEnvironment();
    getSPEnvironment()->APIv2()->SetJitEnabled(true);
}