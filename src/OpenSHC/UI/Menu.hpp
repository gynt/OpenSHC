/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/Menu.hpp'
*/

#pragma once

#include "OpenSHC/UI/Enums/MenuItemHandleState.hpp"
#include "OpenSHC/UI/FwdMenuMenuItem.hpp"
#include "OpenSHC/UI/MenuItem.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::UI::MenuItem;
    using OpenSHC::UI::Enums::MenuItemHandleState;

#pragma pack(push, 1)

    // SIZE: 0x00000044
    class Menu {
    public:
        MenuItem* menuItemArray; // 0x00000000 length: 4
        int xPosition; // 0x00000004 length: 4
        int yPosition; // 0x00000008 length: 4
        // [211 0x004F4290] clicked flag cleared when now - clickTimestamp exceeds it
        int clickHighlightMs; // 0x0000000C length: 4
        // [211 0x004F4290] set 1 by setupMenuForRendering, cleared after the input pass in updateMenuButtons;
        // slider input skipped while set
        int isFirstFrame; // 0x00000010 length: 4
        // [UNK PASS] was currentBuildMenuButtonShiftUnk_0x14
        int currentBuildMenuButtonShift; // 0x00000014 length: 4
        // [211 0x004F64A0] 0 idle, set 1 when hover starts, 2 when tooltip shown, reset to 0 otherwise
        int tooltipState; // 0x00000018 length: 4
        int mouseXScreenSpace; // 0x0000001C length: 4
        int mouseYScreenSpace; // 0x00000020 length: 4
        // Bubble-help tooltip x (centered on mouse, clamped to screen)
        int tooltipX; // 0x00000024 length: 4
        // Bubble-help tooltip y (mouse y +0x10 or -0x44, clamped)
        int tooltipY; // 0x00000028 length: 4
        // Bubble-help text number within group (from TextMessageLookupTable)
        int tooltipTextIndexInGroup; // 0x0000002C length: 4
        // Bubble-help text group index
        int tooltipTextGroup; // 0x00000030 length: 4
        // [211 0x004F64A0] set to timeGetTime() when hover starts; tooltip shown after >200 ms
        int hoverStartTime; // 0x00000034 length: 4
        MenuItem* hoveredItem; // 0x00000038 length: 4
        // [211 0x004F64A0] item the tooltip text belongs to; tooltip drawn only while it is still hovered (also
        // used for hover-sound dedup in handleMenuElementsCallbacks) Created by retype action
        MenuItem* tooltipItem; // 0x0000003C length: 4
        // Set when a newly hovered item played its hover SFX; prevents more this update; reset in updateMenuButtons
        int hoverSoundPlayedThisFrame; // 0x00000040 length: 4

    private:
        Menu(Menu const&);
        void operator=(Menu const&);

    public:
        Menu() {};
        ~Menu() {};

        // Constructor
        /**
         * Menu constructor: stores the item array, resets position/state, then walks items up to MIT_LAST_ENTRY:
         * links each to this menu, inits its control-id/state shorts, stores tab skip counts, propagates group
         * action/render handlers to child items (flag 0x2000000), counts sub-group items (0x11000000 heads, parent
         * marked 0x20000000), and for runs of 0x4000000 items marks the item just before the run with 0x8000000.
         */
        Menu* Constructor_Menu(MenuItem* menuItemArrayAddress);

        /**
         * Walks the menu item array, honouring tab skip/stop, stop, build-menu-shift, modal and
         * (sub)group/alternative control items, and dispatches each eligible item to the per-item handler selected
         * by funcIndex (0 input, 1 reset, 2 prepare+render, 3 render of 0x800000 items). The dispatch is a jump-
         * table inside the loop (MenuItem::handleMenuElementsCallbacks / prepareAndRenderMenuItems /
         * resetMenuItemState) and the loop continues afterwards; only a nonzero result of the input callback ends
         * the walk early. The decompiler's 'call then return' is an artefact.
         */
        void handleMenuItems(MenuItemHandleState funcIndex);

        /**
         * Per-frame input pass for a menu: clears someMenuItemPtr_0x3c if nothing was hovered last frame, resets
         * hoveredItem/field16_0x40/MenuHandlerState.mouseOverMenuItem, runs
         * handleMenuItems(MIHS_HANDLE_INPUT_CALLBACKS), then clears this->one.
         */
        void updateMenuButtons();

        /**
         * Hover help for the menu's hovered item (in the building/status menu view only for barracks, mercenary,
         * tower, gatehouse, engineers/tunnelers guild and cathedral tabs). Lookup types 1-4 and 6-13 set the
         * bottom-left help text (types 6, 7, 12 always, the rest only with bubble help on); type 0 does nothing;
         * other types run a tooltip state machine (needs bubble help and no mouse button held): 0 idle -> 1 records
         * hover time and mouse pos -> after >200 ms without mouse movement 2 stores the text (Resume Game
         * substitution) and item -> draws a dimmed bordered tooltip box near the cursor, clamped to the screen,
         * while that item stays hovered. Any other case resets the state to 0. NAME? renders menu tooltips/help
         * text, not the construction menu.
         */
        void renderMenuHoverHelp();

        /**
         * For each menu item with a valid UC id, loads its screen position and deactivated flag from the UC layout
         * data for the given UC position index.
         */
        void loadMenuElements(int ucPositionIndex);
    };

    static_assert_cpp98_obj(sizeof(Menu) == 68, Menu);

#pragma pack(pop)

} // namespace UI
} // namespace OpenSHC
