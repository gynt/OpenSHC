/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/IdentityOptions.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace IdentityOptions {

            /**
             * Action handler of the identity options lord picker: 0x15/0x16 choose lord type 0/1 (resetting the
             * face to 2/3 if below 0x14), 0x28/0x29 step the lord face index backward/forward cycling within
             * 2..0x15.
             */
            void __cdecl MenuItemActionHandler_IdentityOptions_LordIcons(int param_1, ...);

            /**
             * Render callback of the identity options lord picker: ids > 0x27 are the arrow buttons; 0x17 draws a
             * frame with the chosen lord face (drawBitmapFace(lordIconUnk-2)); 0x15/0x16 draw the two lord-type
             * icons with a selection highlight on the one matching selectedLordTypeUnk.
             */
            void __cdecl MenuItemRenderFunction_IdentityOptions_LordIcons(int param_1, ...);

            /**
             * Identity options confirm (button 0x11): with user text input briefly disabled resets the text handler
             * to slot 9, closes the dialog and, unless the game mode is GM_SOLITARY, queues game command 0x60
             * (presumably broadcasting the new identity).
             */
            void __cdecl MenuItemActionHandler_IdentityOptions_Confirm(int param_1, ...);

        } // namespace IdentityOptions
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
