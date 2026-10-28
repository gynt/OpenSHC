/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuModalComposition.hpp'
*/

#pragma once

#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuModalTypeInt.hpp"
#include "OpenSHC/UI/MenuModal.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::UI::MenuModal;
    using OpenSHC::UI::Enums::MenuModalType;
    using OpenSHC::UI::Enums::MenuModalTypeInt;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

    // SIZE: 0x0000007C
    class MenuModalComposition {
    public:
        // Unsigned Double-Word (ddw, 4-bytes)
        int slot; // 0x00000000 length: 4
        MenuModal modalMenu; // 0x00000004 length: 40
        // Unsigned Double-Word (ddw, 4-bytes)
        MenuModalTypeInt activeModalDialogID; // 0x0000002C length: 4
        // [235 0x004A9ED0] reset on activation; set by update() when the 12 px title bar is grabbed Unsigned
        // Double-Word (ddw, 4-bytes)
        dword isBeingDragged; // 0x00000030 length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        dword mouseRelativeX; // 0x00000034 length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        dword mouseRelativeY; // 0x00000038 length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        dword sliderMinimum; // 0x0000003C length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        dword sliderMaximum; // 0x00000040 length: 4
        undefined1 padding_0x44[8]; // 0x00000044 length: 8
        // Unsigned Double-Word (ddw, 4-bytes)
        int textGroup; // 0x0000004C length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        int textIndex; // 0x00000050 length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        dword sliderValue; // 0x00000054 length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        int* destination; // 0x00000058 length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        short* destination2; // 0x0000005C length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        pointer sliderCallbackFunction; // 0x00000060 length: 4
        // [234 0x004AA970] rows with index >= this are not drawn / not selectable Unsigned Double-Word (ddw,
        // 4-bytes)
        dword optionCount; // 0x00000064 length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        dword disappearAfter; // 0x00000068 length: 4
        // [235 0x004B0B30] when set, disappearAfter is decreased over time and the modal closes at <1; fade-in is
        // skipped while set Unsigned Double-Word (ddw, 4-bytes)
        dword isFadingOut; // 0x0000006C length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        dword timeItIsSet; // 0x00000070 length: 4
        // [235 0x004AA1F0] set to 1 when the mouse is over the modal, it is being dragged, or a full-screen menu is
        // open; -1 (set by item handlers during updateMenuButtons) skips one frame Unsigned Double-Word (ddw,
        // 4-bytes)
        int capturesMouse; // 0x00000074 length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        dword mbr_0x78; // 0x00000078 length: 4

    private:
        MenuModalComposition(MenuModalComposition const&);
        void operator=(MenuModalComposition const&);

    public:
        MenuModalComposition() {};
        ~MenuModalComposition() {};

        // Constructor
        /**
         * MenuModalComposition constructor: sets the slot number and no active modal dialog (slots 0/1/2 =
         * DAT_MenuModalComposition1/2/3).
         */
        MenuModalComposition* Constructor_MenuModalComposition(int slot);

        /**
         * Walks the global modal list and loads the menu elements of every modal that has an attached Menu.
         */
        void loadAllMenuElementsOfMenuModals();

        /**
         * Returns the registered MenuModal with the given id from the global modal list, or NULL.
         */
        MenuModal* findModalMenu(MenuModalType menuModalID);

        /**
         * Activates modal dialog menuModalID in this composition: if retainOther is FALSE and this is slot 0,
         * clears text-input modals; if an AI-lord message is showing, the next queued message takes precedence
         * (returns without activating if one starts); copies the MenuModal template (10 dwords) into modalMenu,
         * clears dragging, rounds tiled-border sizes (0x220) up to 24 px, converts 800x600-relative or centred (-1)
         * coordinates to the current resolution (in-game centring excludes the 128 px bottom panel), resets the
         * fade state/timer (fade-in when border 0x400) and the attached Menu's item state.
         */
        void activateModalDialog(MenuModalType menuModalID, BOOLEnum retainOther);

        /**
         * Like activateModalDialog (without retainOther) but places the modal at explicit screen coordinates
         * (dialogX, dialogY), clamped to the screen; used e.g. for the tactical power bar and drop-down option
         * lists.
         */
        void setExtraActiveModalDialog(MenuModalType menuModalID, int dialogX, int dialogY);

        /**
         * Per-frame modal update: for modals with styleFlags 2 and 4, a left click on the 12 px title bar starts
         * dragging, the modal follows the mouse while the button is held and is clamped to the screen (in-game:
         * above the 128 px panel). Syncs the attached Menu position and updates its buttons. Then sets
         * capturesMouse = 1 when hovered or dragged, in any non-ingame menu except scenario description, or for
         * slot 0 while a game-halting menu is open; a -1 left by a button handler suppresses this for one frame.
         * Style 0x800 takes capturesMouse from MenuHandlerState.mouseOverMenuItem; style 0x1000 moves it into
         * mbr_0x78 (except scenario help text) and clears it.
         */
        void update();

        /**
         * If the composition (this; all callers pass DAT_MenuModalComposition1, slot 0) has an active dialog,
         * writes its x/y (plus camera offset when in-game), width and height to the out pointers, excluding the 12
         * px title bar if present.
         */
        void fillWithMenuModalDimensions(int* xPtr, int* yPtr, int* widthPtr, int* heigthPtr);

        /**
         * Configures the overlay slider in this composition (all callers pass DAT_MenuModalComposition2) for an int
         * destination: min/max, initial position (raw value when range <= 200, otherwise non-linear: the first 1/5
         * of the range is expanded 4x), destination pointer (destination2 cleared), no text, and change callback.
         */
        void setSliderParameters(int minimum, int maximum, int value, undefined* destination, void* callbackFunction);

        /**
         * Same as setSliderParameters but the destination is a short* (destination2) instead of int*.
         */
        void setSliderParameters2(
            dword minimum, dword maximum, dword value, dword destination, undefined* callbackFunction);

        /**
         * Configures a drop-down option list in this composition (sole caller passes DAT_MenuModalComposition1):
         * text group and first text index of the options, option count (mbr_0x64), current selection, int
         * destination and callback; sets the list modal template height to 25 px per option. NAME? it sets up a
         * drop-down list, not a slider.
         */
        void setDropDownListParameters(
            int param_1, int param_2, dword param_3, dword param_4, undefined* param_5, undefined* param_6);

        /**
         * Renders the active modal: while fading out decreases disappearAfter and closes the modal at <1 (style
         * 0x400 grows it again while fading in); picks the surface (screen menu, or map surface with camera offset
         * in-game); draws title bar/background/dim/rounded borders per styleFlags bits (0x20 also sets the text
         * editor dialog rect); for tiled borders (0x20/0x200) tiles the 24 px frame graphics from
         * GID_INTERFACE_ICONS_3 with fade alpha and a blended inner box; calls the modal's render function, then
         * renders the attached Menu and its hover help.
         */
        void renderMenuModal();

        /**
         * Activates modalDialogID in DAT_MenuModalComposition1 (slot 0), renders it immediately and, if more than
         * 30 ms passed since the last time, blits its rectangle to the screen; then deactivates it again. Used for
         * synchronous progress-bar dialogs during save/load/network.
         */
        void activateModalDialog2(MenuModalType modalDialogID);
    };

    static_assert_cpp98_obj(sizeof(MenuModalComposition) == 124, MenuModalComposition);

#pragma pack(pop)

} // namespace UI
} // namespace OpenSHC
