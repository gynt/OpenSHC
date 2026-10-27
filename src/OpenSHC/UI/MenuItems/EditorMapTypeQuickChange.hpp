/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/EditorMapTypeQuickChange.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace EditorMapTypeQuickChange {

            /**
             * Map editor settings handler: 0-2 set map lock state, 3-6 set map type (siege/invasion/economic/just
             * build) unless mapHasCertainEvent, 10/11 single/multiplayer, 0x14-0x17 resize map to 160/200/300/400
             * and rebuild height borders, pathing linkage, runs a game tick, wildlife grid, minimap and viewport.
             */
            void __cdecl MenuItemActionHandler_EditorMapSettings_Main(int param_1, ...);

            /**
             * Renders map editor settings buttons with hard-coded English labels (Editable/Playable/Mission,
             * Siege/Invasion/Economic/Just Build, Single/Multi, King of the Hill, 160x160..400x400); the button
             * matching the current lock state, map type, single/multi, KotH flag or map size is drawn pressed
             * (DAT_ButtonCurrentlyInteracting=TRUE), hover only changes the text colour. The King of the Hill
             * button (0xc) is not drawn at all for single-player maps.
             */
            void __cdecl MenuItemRenderFunction_EditorMapTypeQuickChange_Main(int param_1, ...);

        } // namespace EditorMapTypeQuickChange
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
