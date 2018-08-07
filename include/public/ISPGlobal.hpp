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

#include <cstddef>
#include <IHelpers.hpp>

#ifdef SP_CLANG
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wnon-virtual-dtor"
    #pragma clang diagnostic ignored "-Wunused-parameter"
#elif defined SP_GCC
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wnon-virtual-dtor"
    #pragma GCC diagnostic ignored "-Wunused-parameter"
    #pragma GCC diagnostic ignored "-Wpedantic"
#elif defined SP_MSVC
    #pragma warning(push)
    // Unreferenced formal parameter
    #pragma warning(disable : 4100)
#endif
#include <sp_vm_api.h>
#ifdef SP_CLANG
    #pragma clang diagnostic pop
#elif defined SP_GCC
    #pragma GCC diagnostic pop
#elif defined SP_MSVC
    #pragma warning(pop)
#endif

#include <IForwardSystem.hpp>
#include <IPluginSystem.hpp>
#include <INativeSystem.hpp>
#include <ICvarSystem.hpp>
#include <ITimerSystem.hpp>
#include <IUtilsSystem.hpp>
#include <IPlayerSystem.hpp>

namespace SPMod
{
    using sp_api_t = unsigned long;
    constexpr sp_api_t SPMOD_API_VERSION = 0;

    class IModuleInterface;

    class ISPGlobal SPMOD_FINAL
    {
    public:

        /**
         * @brief Returns home dir of SPMod.
         *
         * @return        Home dir.
         */
        virtual const char *getHome() const = 0;

        /**
         * @brief Returns name of the mod.
         *
         * @return        Mod name.
         */
        virtual const char *getModName() const = 0;

        /**
         * @brief Returns SPMod plugin manager.
         *
         * @return        Plugin manager.
         */
        virtual IPluginMngr *getPluginManager() const = 0;

        /**
         * @brief Returns SPMod native manager.
         *
         * @return              Native manager.
         */
        virtual INativeMngr *getNativeManager() const = 0;

        /**
         * @brief Returns SPMod forward manager.
         *
         * @return        Forward manager.
         */
        virtual IForwardMngr *getForwardManager() const = 0;

        /**
        * @brief Returns SPMod cvar manager.
        *
        * @return                cvar manager.
        */
        virtual ICvarMngr *getCvarManager() const = 0;

        /**
         * @brief Return SPMod timer manager.
         *
         * @return              Timer manager.
         */
        virtual ITimerMngr *getTimerManager() const = 0;

        /**
         * @brief Return SPMod player manager.
         *
         * @return              Player manager.
         */
        virtual IPlayerMngr *getPlayerManager() const = 0;

        /**
         * @brief Return SPMod utils funcs.
         *
         * @return              Utils funcs.
         */
        virtual IUtils *getUtils() const = 0;

        /**
         * @brief Returns current SourcePawn environment.
         *
         * @return        SourcePawn environment.
         */
        virtual SourcePawn::ISourcePawnEnvironment *getSPEnvironment() const = 0;

        /**
         * @brief Formats a string according to the SPMod format rules.
         *
         * @param buffer        Destination buffer.
         * @param length        Length of buffer.
         * @param format        Formatting string.
         * @param ctx           Plugin context.
         * @param params        Params list passed by native.
         * @param param         Index of param which contains first formatting argument.
         *
         * @return              Number of characters written.
         */
        virtual unsigned int formatString(char *buffer,
                                        size_t length,
                                        const char *format,
                                        SourcePawn::IPluginContext *ctx,
                                        const cell_t *params,
                                        size_t param) const = 0;

    protected:
        virtual ~ISPGlobal() {};
    };

    using fnSPModQuery = int (*)(ISPGlobal *spmodInstance);

   /**
    * @brief Entry point for modules to obtain access to SPMod API.
    */
    SPMOD_API int SPMod_Query(ISPGlobal *spmodInstance);

   /**
    * @brief Interface for registering a module.
    */
    class IModuleInterface
    {
    public:

        /**
         * @brief Returns SPMod API version used by module.
         *
         * @return        SPMod API version.
         */
        virtual sp_api_t getInterfaceVersion() const
        {
            return SPMOD_API_VERSION;
        }

        /**
         * @brief Returns name of the module.
         *
         * @note        Must be implemented.
         *
         * @return      Module name.
         */
        virtual const char *getName() const = 0;

    protected:
        virtual ~IModuleInterface() {}
    };
}
