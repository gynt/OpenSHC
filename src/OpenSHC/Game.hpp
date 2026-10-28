/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Game.hpp'
*/

#pragma once

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
namespace OpenSHC {
namespace Game {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /**
     * Adds a positive unit value to the global unitValueKilledByCurrentPlayer; non-positive values are ignored.
     */
    void __cdecl addUnitValueKilledByCurrentPlayer(int value);

    /**
     * Tutorial gate: always TRUE when tutorial restrictions are disabled. Action types 1/2 are allowed only at
     * specific tutorial steps with a specific parameter (0x28, 0x13, 3, 7, 1) and sub-step/counter conditions,
     * FALSE otherwise; type 3 (rations) is allowed only at step 8 and type 4 (taxes) only at step 10, and there
     * only the value 4 resp. 7 once the setting already equals it. Unknown action types are allowed.
     */
    BOOLEnum __cdecl Tutorial_IsActionAllowed(undefined4 actionType, int actionParam);

} // namespace Game
} // namespace OpenSHC
