/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Input/MouseState.hpp'
*/

#pragma once

#include "OpenSHC/Input/Mouse/ClickTypeBitMaskEnumByte.hpp"
#include "OpenSHC/Input/Mouse/MouseClickInteraction.hpp"
#include "OpenSHC/Input/Mouse/MouseXYUUStruct.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "WinDef.h"

namespace OpenSHC {
namespace Input {

    using OpenSHC::Input::Mouse::ClickTypeBitMaskEnumByte;
    using OpenSHC::Input::Mouse::MouseClickInteraction;
    using OpenSHC::Input::Mouse::MouseXYUUStruct;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

    // SIZE: 0x00000274
    class MouseState {
    public:
        dword inactiveTime; // 0x00000000 length: 4
        undefined4 time0; // 0x00000004 length: 4
        BOOLEnum anyActivity; // 0x00000008 length: 4
        undefined4 flag; // 0x0000000C length: 4
        int screenSpaceX; // 0x00000010 length: 4
        int screenSpaceY; // 0x00000014 length: 4
        int cursorPosX; // 0x00000018 length: 4
        int cursorPosY; // 0x0000001C length: 4
        int previousScreenSpaceX; // 0x00000020 length: 4
        int previousScreenSpaceY; // 0x00000024 length: 4
        // [055 0x00468100] set whenever the left button state changes to released, mirrors
        // rightClickStop/midClickStop
        BOOLEnum leftClickStop; // 0x00000028 length: 4
        undefined4 midClickStop; // 0x0000002C length: 4
        undefined4 rightClickStop; // 0x00000030 length: 4
        undefined4 leftClickStart; // 0x00000034 length: 4
        undefined4 midClickStart; // 0x00000038 length: 4
        undefined4 rightClickStart; // 0x0000003C length: 4
        BOOLEnum leftClickState; // 0x00000040 length: 4
        BOOLEnum midClickState; // 0x00000044 length: 4
        BOOLEnum rightClickState; // 0x00000048 length: 4
        BOOLEnum previousLeftClickState; // 0x0000004C length: 4
        // [055 0x00468100] compared with midClickState to detect middle-button edges, but never assigned the
        // current state (only reset to 0) - edge detection is broken
        undefined4 previousMidClickState; // 0x00000050 length: 4
        uint previousRightClickState; // 0x00000054 length: 4
        // 8 means scroll up, 7 means scroll down
        undefined4 scrollEventData; // 0x00000058 length: 4
        int lastSetCursorType; // 0x0000005C length: 4
        RECT selectionBox; // 0x00000060 length: 16
        RECT previousSelectionBox; // 0x00000070 length: 16
        undefined4 hitboxXStart; // 0x00000080 length: 4
        undefined4 hitboxYStart; // 0x00000084 length: 4
        undefined4 hitboxXEnd; // 0x00000088 length: 4
        undefined4 hitboxYEnd; // 0x0000008C length: 4
        int selectionBoxMode; // 0x00000090 length: 4
        // 1 while a drag selection box is being drawn (extendSelectionBoxToMouse), 0 on reset; drawMouseBasedBox
        // renders it when set
        undefined4 selectionBoxActive; // 0x00000094 length: 4
        // accessed by 0x4346e4, 0x434975
        undefined1 field_0x98[4]; // 0x00000098 length: 4
        // [056 0x004685C0] first gate for drawing the right-drag camera widget (together with rightClickState)
        int rightDragCameraWidgetEnabled; // 0x0000009C length: 4
        MouseXYUUStruct mouseXY[10]; // 0x000000A0 length: 160
        int mouseXY8[10]; // 0x00000140 length: 40
        int index; // 0x00000168 length: 4
        undefined4 storedScreenSpaceX; // 0x0000016C length: 4
        undefined4 storedScreenSpaceY; // 0x00000170 length: 4
        // ticks of the current right-drag gesture, reset when no gesture distance is reached
        undefined4 rightDragTickCount; // 0x00000174 length: 4
        // scroll speed from right-drag distance: 0 (<12px), len/2 (<28px), 40
        undefined4 rightDragScrollSpeed; // 0x00000178 length: 4
        // zeroed each right-drag update; no reader seen
        undefined4 rightDragField17c; // 0x0000017C length: 4
        undefined4 mouseBasedEvent; // 0x00000180 length: 4
        // zeroed in storeXYAndResetMouseState; no reader seen
        undefined4 rightDragField184; // 0x00000184 length: 4
        // 0 on first rotate gesture trigger, 8 while held (reset value 8)
        undefined4 rotateGestureRepeat; // 0x00000188 length: 4
        undefined4 mapOrientationCopy1; // 0x0000018C length: 4
        undefined4 mapOrientationCopy2; // 0x00000190 length: 4
        undefined4 mapOrientationCopy3; // 0x00000194 length: 4
        // right-drag-to-the-right (direction 2, >= 55 px) camera gesture: 0 idle, 1 fired (mouseBasedEvent 4 ->
        // resetupViewport zoom toggle), 2 consumed by the in-game / landscaping handler; cleared on gesture timeout
        undefined4 zoomGestureState; // 0x00000198 length: 4
        // right-drag-to-the-left (direction 6, >= 55 px) camera gesture: 0 idle, 1 fired (mouseBasedEvent 5 ->
        // toggleFlatView), 2 consumed by the handler; cleared on gesture timeout
        undefined4 flatViewGestureState; // 0x0000019C length: 4
        undefined4 currentTime1; // 0x000001A0 length: 4
        undefined4 currentTime2; // 0x000001A4 length: 4
        undefined4 currentTime3; // 0x000001A8 length: 4
        // ms since gesture start (currentTime3 - currentTime2)
        int gestureElapsedMs; // 0x000001AC length: 4
        // gesture timeout: 1500 ms after rotate, 2000 ms after up/down; gesture state resets when exceeded
        int gestureTimeoutMs; // 0x000001B0 length: 4
        // set 1 once the rotate gesture applied a rotation, reset on timeout
        undefined4 rotateGestureFired; // 0x000001B4 length: 4
        // winning right-drag gesture this tick: 0 none, 1 fast scroll (down drag), 2 rotate (up drag), 3 zoom
        // (right drag), 4 flat view (left drag); renderPreviewAtMouseLocation highlights the gesture icons by it
        undefined4 activeCameraGesture; // 0x000001B8 length: 4
        // nonzero blocks the rotate (up-drag) gesture; set by the scroll, zoom and flat-view gestures; reset in
        // storeXYAndResetMouseState
        undefined4 rotateGestureLocked; // 0x000001BC length: 4
        // nonzero blocks drag-scrolling (set by the rotate, zoom and flat-view gestures); reset in
        // storeXYAndResetMouseState
        undefined4 scrollGestureLocked; // 0x000001C0 length: 4
        // nonzero blocks the left-drag (direction 6) flat-view gesture; set by the other gestures
        undefined4 flatViewGestureLocked; // 0x000001C4 length: 4
        // nonzero blocks the right-drag (direction 2) zoom gesture; set by the other gestures
        undefined4 zoomGestureLocked; // 0x000001C8 length: 4
        int leftClickStartMoment; // 0x000001CC length: 4
        // [055 0x00468100] set to the mouse position at the moment the left button goes down, compared later to
        // detect dragging (same for dragReleaseY)
        undefined4 leftPressX; // 0x000001D0 length: 4
        undefined4 dragReleaseY; // 0x000001D4 length: 4
        int resetPending; // 0x000001D8 length: 4
        // Switch 1..5/1000/1001 selecting the cursor overlay sprite, reset to -1 per frame; not a placement cursor
        // id placement cursor id: -1 none, 1000 = wall placement; values < 1000 / <= 1000 change cursor and map
        // rendering
        int cursorOverlayMode; // 0x000001DC length: 4
        int waitCursorToggle; // 0x000001E0 length: 4
        // zeroed in MouseState constructor; no other use seen
        int ctorZeroed1e4; // 0x000001E4 length: 4
        undefined1 padding_0x1e8[8]; // 0x000001E8 length: 8
        undefined4 cursorType; // 0x000001F0 length: 4
        short mouseWindowX; // 0x000001F4 length: 2
        short mouseWindowY; // 0x000001F6 length: 2
        short mouseWheelDelta; // 0x000001F8 length: 2
        ClickTypeBitMaskEnumByte mouseClickTypes; // 0x000001FA length: 1
        undefined1 padding1; // 0x000001FB length: 1
        HCURSOR currentDefaultCursor; // 0x000001FC length: 4
        HCURSOR currentDeleteCursor_0x200; // 0x00000200 length: 4
        HCURSOR unknownNotAniDeleteNotCursor_0x204; // 0x00000204 length: 4
        HCURSOR currentWaitCursor_0x208; // 0x00000208 length: 4
        HCURSOR currentHandCursor_0x20c; // 0x0000020C length: 4
        HCURSOR currentDeleteNotCursor_0x210; // 0x00000210 length: 4
        HCURSOR currentDefaultArabCursor_0x214; // 0x00000214 length: 4
        HCURSOR unknownNotAniCursor_0x218; // 0x00000218 length: 4
        undefined1 padding_0x21c[8]; // 0x0000021C length: 8
        HCURSOR swordCursor_0x224; // 0x00000224 length: 4
        HCURSOR deleteCursor_0x228; // 0x00000228 length: 4
        undefined1 padding_0x22c[4]; // 0x0000022C length: 4
        HCURSOR jesterCursor_0x230; // 0x00000230 length: 4
        HCURSOR handCursor_0x234; // 0x00000234 length: 4
        HCURSOR deleteNotCursor_0x238; // 0x00000238 length: 4
        HCURSOR scimitarCursor_0x23c; // 0x0000023C length: 4
        undefined1 padding_0x240[12]; // 0x00000240 length: 12
        HCURSOR notAniDefaultCursor_0x24c; // 0x0000024C length: 4
        HCURSOR notAniDeleteCursor_0x250; // 0x00000250 length: 4
        undefined1 padding_0x254[4]; // 0x00000254 length: 4
        HCURSOR notAniWaitCursor_0x258; // 0x00000258 length: 4
        HCURSOR notAniHandCursor_0x25c; // 0x0000025C length: 4
        HCURSOR notAniDeleteNotCursor_0x260; // 0x00000260 length: 4
        HCURSOR notAniDefaultArabCursor_0x264; // 0x00000264 length: 4
        undefined1 padding_0x268[12]; // 0x00000268 length: 12

    private:
        MouseState(MouseState const&);
        void operator=(MouseState const&);

    public:
        MouseState() {};
        ~MouseState() {};

        // Constructor
        /**
         * MouseState constructor: records time0, resets gesture state via storeXYAndResetMouseState, clears
         * previewEnabled/flag/resetPending/waitCursorToggle/cursorType/field70_0x1e4, sets field68_0x1dc = -1 and
         * returns &DAT_MouseState.
         */
        MouseState* Constructor_MouseState();

        /**
         * Selects the active cursor handle set from cursorType: 1 = animated set (sword, delete, jester wait, hand,
         * scimitar, delete-not), 2 = non-animated set; other values leave the current cursors unchanged.
         */
        void makeSelectedCursorTypeCurrent();

        /**
         * Window-message handler helper: stores the mouse window position and sets/clears the left, middle or right
         * button-down bit in mouseClickTypes according to clickType.
         */
        void updateMousePositionAndClicks(short xMousePos, short yMousePos, MouseClickInteraction clickType);

        /**
         * Stores the mouse wheel delta (from WM_MOUSEWHEEL) as a short in DAT_MouseState.mouseWheelDelta.
         */
        void updateMouseWheelStatus(int delta);

        /**
         * Returns TRUE if the mouse screen position lies in the half-open rectangle [xPos, xPos+width) x [yPos,
         * yPos+heigth).
         */
        BOOLEnum isMouseInsideBox(int xPos, int yPos, int width, int heigth);

        /**
         * Per-frame mouse update: latches mouseWindowX/Y as the screen position (recording moves in a 10-entry ring
         * buffer), sets edge-scroll flags from GetCursorPos, derives right (bit 0x10), middle (0x40) and left
         * (0x01) button states from mouseClickTypes with start/stop edges, tracks the left press position/time
         * (leftClickStartMoment = press time; -1 once moved while held; every frame while released -2 if still at
         * the press position and not dragged, else -3), updates the inactivity timer and maps the wheel delta to
         * scrollEventData (7 = down, 8 = up, 9 = none). Game bug: previousMidClickState is never saved here, so
         * midClickStart fires every frame the middle button is held and midClickStop never fires.
         */
        void updateMouseStateBasedOnCursorAndTime();

        /**
         * Tail-calls SetCursor (overwriting its own argument slot) with the handle for cursorType: 0 ->
         * currentDefaultCursor (both lastSetCursorType branches load the same handle), 1 -> field +0x204, 3 ->
         * currentWaitCursor, 4 -> currentHandCursor, 5 -> currentDeleteNotCursor, 6 -> currentDefaultArabCursor,
         * anything else (incl. 2) -> currentDeleteCursor. Returns SetCursor's previous cursor handle.
         */
        HCURSOR setCursor(DWORD cursorType);

        /**
         * Starts a point/drag selection box at the mouse: sets selectionBox and previousSelectionBox to a 3x3
         * world-pixel square around (screen mouse + camera offset), doubling coordinates when zoomed out
         * (selectionBox only). Clears the 'box dragged' flag (field31_0x94) and sets selectionBoxMode = 1.
         */
        void beginPointSelectionBox();

        /**
         * Sets the mouse hit box (hitboxXStart/YStart/XEnd/YEnd) to a width x height rectangle centred on the mouse
         * in world-pixel coordinates (screen + camera offset), doubled when the viewport is zoomed out.
         */
        void setupHitBox(int width, int height);

        /**
         * NAME? Only clears the selection box state: zeroes selectionBox and previousSelectionBox, selectionBoxMode
         * and the box-dragged flag (field31_0x94); does not touch the cursor (better: resetSelectionBox). Called on
         * menu switches, map load and game end.
         */
        void resetMouseCursorState();

        /**
         * NAME? Draws the right-drag camera-control widget around the stored right-click position
         * (storedScreenSpaceX/Y) while previewEnabled, the right button is held, viewportState.field0_0x0 is set
         * and the view is MVT_BUILD_MENU or the landscaping editor: rotate icon 50px above (frame chosen by map
         * orientation), scroll icon 50px below (alternate frame when mouseBasedEvent == 1), zoom icon 80px right
         * (frame by isZoomedOutUnk) and flat-view icon 80px left (frame by flatViewToggleValue1), all from
         * GM_FLOATS and each suppressed by its own hide flag; field59_0x1b8 == 3 / 4 selects the highlighted zoom /
         * flat-view frame. Better name: renderRightDragCameraWidget.
         */
        void renderPreviewAtMouseLocation();

        /**
         * Resets the right-drag camera-gesture state: clears the 10-entry mouseXY history, stores the current mouse
         * position as the gesture anchor (storedScreenSpaceX/Y), resets gesture counters/flags and hide-icon flags,
         * copies the current mapOrientation into the three orientation copies and stamps currentTime1..3 with
         * timeGetTime().
         */
        void storeXYAndResetMouseState();

        /**
         * If resetPending was set, only clears it; otherwise clears all mouse-button state (click start/stop,
         * current and previous left/mid/right states, draggingStopped) and sets mouseClickTypes to
         * ~(LEFT_UP|LEFT_DOWN). Called around modal file dialogs and window messages. NAME? better
         * clearMouseButtonState.
         */
        void resetMouseState2();

        /**
         * Loads the game's cursors: static cursors from exe resources (default, delete, delete-not; hand and arab-
         * default reuse the default resource id; wait = system IDC_WAIT) and animated cursors from
         * sword/delete/jester/hand/delete_not/scimitar.ani. If cursorType is 0 it becomes 2 when
         * DAT_WindowAndDirectDraw.not_DDCAPS2_CANBOBHARDWARE_0xe0 is set, else 1, and is applied via
         * makeSelectedCursorTypeCurrent; finally loads the optional extra resource cursors notAniDeleteNotCursorRef
         * / notAniUnknownCursorRef when non-zero.
         */
        void loadAndSetCursor(int notAniDefaultCursorRef, int notAniDeleteCursorRef, int notAniDeleteNotCursorRef,
            int unused1, int unused2, int unused3, int unused4, int notAniUnknownCursorRef);

        /**
         * Extends the selection box's right/bottom corner to the current mouse world position (doubled when zoomed
         * out), sets selectionBoxMode = 2 and, if the box's axis distance (setAxisBasedDistanceResult ->
         * distanceHigh) exceeds 16, sets field31_0x94 to mark it as a real drag box.
         */
        void extendSelectionBoxToMouse();

        /**
         * Interprets a right-button drag from the anchor (storedScreenSpaceX/Y) as a camera gesture and reports it
         * in mouseBasedEvent: down (dir 4) 12..27 px -> rightDragScrollSpeed = len/2, event 2; >=28 px -> speed 40,
         * event 1, gesture 1 and the rotate/flat/zoom gestures locked; up (dir 0) >=22 px -> gesture 2, 1500 ms
         * timeout and, once per gesture (rotateGestureFired), target orientation = (mapOrientationCopy3 + 6) % 8,
         * event 3 when it differs from mapOrientationCopy2; right (dir 2) >=55 px -> gesture 3, 2000 ms timeout,
         * event 4 and zoomGestureState = 1 unless zoomGestureState is already 2; left (dir 6) >=55 px -> gesture 4,
         * 2000 ms timeout, event 5 and flatViewGestureState = 1 unless it is 2. Gesture states reset when elapsed >
         * gestureTimeoutMs; currentTime2 restarts on timeout or when the active gesture drops below its threshold.
         */
        void updateRightDragCameraControl();

        /**
         * Draws the drag-selection rectangle (black outer border, white 1px-inset inner border) on the RT_MAP_GAME
         * surface using previousSelectionBox, but only when the box is a real drag (field31_0x94); in that case, if
         * neither the left button is held nor draggingStopped is set, it resets the selection box instead of
         * drawing. NAME? better drawSelectionBox.
         */
        void drawMouseBasedBox();
    };

    static_assert_cpp98_obj(sizeof(MouseState) == 628, MouseState);

#pragma pack(pop)

} // namespace Input
} // namespace OpenSHC
