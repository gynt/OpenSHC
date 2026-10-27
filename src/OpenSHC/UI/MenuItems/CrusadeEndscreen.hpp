/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/CrusadeEndscreen.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace CrusadeEndscreen {

            /**
             * Crusade end-screen button handler: only button 10 does something; it re-invokes the Select Crusade
             * action with option 4 (Extreme trail), 3 (Warchest trail) or 1 (original trail) according to
             * DAT_GameCore.currentTrailType.
             */
            void __cdecl MenuItemActionHandler_CrusadeEndscreen_Main(int param_1, ...);

        } // namespace CrusadeEndscreen
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
