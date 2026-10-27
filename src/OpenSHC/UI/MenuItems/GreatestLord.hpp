/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/GreatestLord.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace GreatestLord {

            /**
             * Render callback for the Greatest Lord table column-header buttons (10, 11, 12): the header matching
             * the current sort (tableSortBy -1/1/0) is drawn as pressed with renderGM at (DAT_ButtonX, DAT_ButtonY)
             * using the button's hover picture (getPictureNumberInGm(TRUE)) plus 0xE (plus 1 for button 12); all
             * other cases use RenderButtonImageWithBlending.
             */
            void __cdecl MenuItemRenderFunction_GreatestLord_Main(int param_1, ...);

            /**
             * Action handler of the Greatest Lord screen: buttons 1/100 close the modal; header buttons 10/11/12
             * set tableSortBy to -1/1/0.
             */
            void __cdecl MenuItemActionHandler_GreatestLord_Main(int param_1, ...);

        } // namespace GreatestLord
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
