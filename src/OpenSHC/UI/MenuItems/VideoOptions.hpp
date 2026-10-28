/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/VideoOptions.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace VideoOptions {

            /**
             * Renders the video options buttons: -10/-20 draw cursor-type icons (GM_INTERFACE_ICONS3 0xb6/0xb7, +2
             * when that cursor type is selected), -1 draws the selected resolution string, -2 shows the zoom
             * setting label (text 0xe for 0, 0xd for 1) and -3 the scroll-speed label (0x14/0x15/0x13); non-
             * negative ids are basic buttons with TEXT_GAME_OPTIONS labels.
             */
            void __cdecl MenuItemRenderFunction_VideoOptions_Main(int param_1, ...);

            /**
             * Video options action handler. 0xb cycles the selected resolution (custom order, skipping resolutions
             * not flagged supported); 0xc toggles the zoom setting; 0x10 cycles scroll speed 0..2; -20/-10 select
             * cursor type 1/2; 0x12 (OK) applies a changed resolution (re-creating DDraw/viewport, stopping Bink
             * playback, repositioning the tactical power bar for the new resolution), then zoom, cursor and scroll
             * speed, and pops the dialog; 0x11 (cancel) just pops the dialog.
             */
            void __cdecl MenuItemActionHandler_VideoOptions_Main(int param_1, ...);

        } // namespace VideoOptions
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
