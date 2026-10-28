/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/CrusadeMissionIntro.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace CrusadeMissionIntro {

            /**
             * Render callback of the crusade mission intro: when the current trail's progress is >= its mission
             * count (50/30/20) the trail is finished, so button 10 (start) is drawn disabled
             * (DAT_ButtonDisabled=1, not hovered). Then renders the current button normally.
             */
            void __cdecl MenuItemRenderFunction_CrusadeMissionIntro_Main(int param_1, ...);

            /**
             * Crusade mission intro button handler. 10: if GameCore.briefingOpenedFromInGame==1 returns to the running game
             * (MVT_BUILD_MENU), otherwise starts SetupSkirmishMode for the current trail's mission if progress <
             * mission count (20/30/50). 11: back to the crusade map, or a yes/no confirm dialog (action 7) when
             * field22_0x64==1.
             */
            void __cdecl MenuItemActionHandler_CrusadeMissionIntro_Main(int param_1, ...);

        } // namespace CrusadeMissionIntro
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
