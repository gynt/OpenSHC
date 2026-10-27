/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuHandlerState.hpp'
*/

#pragma once

#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/UI/Menu.hpp"
#include "OpenSHC/UI/MenuIDMenuElementAddressPair.hpp"
#include "OpenSHC/UI/UC.hpp"
#include "OpenSHC/UI/UCPointerStruct.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::UI::Menu;
    using OpenSHC::UI::MenuIDMenuElementAddressPair;
    using OpenSHC::UI::UC;
    using OpenSHC::UI::UCPointerStruct;
    using OpenSHC::UI::Enums::MenuViewType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

    // SIZE: 0x00000040
    class MenuHandlerState {
    public:
        MenuIDMenuElementAddressPair* pointerToMenuIDMenuElementAddressMap; // 0x00000000 length: 4
        Menu* currentMenu; // 0x00000004 length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        UCPointerStruct ucPtrStruct; // 0x00000008 length: 4
        undefined1 padding_0xc[4]; // 0x0000000C length: 4
        int x; // 0x00000010 length: 4
        int y; // 0x00000014 length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        BOOLEnum isBuildMenuTransitioning_0x18; // 0x00000018 length: 4
        // [211 0x004F4C60] prepareAndRenderMenuItems skips buttons whose shifted x is below it Unsigned Double-Word
        // (ddw, 4-bytes)
        dword buildMenuClipLeft; // 0x0000001C length: 4
        // [211 0x004F4C60] prepareAndRenderMenuItems skips buttons whose shifted right edge exceeds it Unsigned
        // Double-Word (ddw, 4-bytes)
        dword buildMenuClipRight; // 0x00000020 length: 4
        int buildMenuBackgroundLeftShift_0x24; // 0x00000024 length: 4
        dword buildMenuItemsLeftShift_0x28; // 0x00000028 length: 4
        int buildMenuTransitionDirection_0x2c; // 0x0000002C length: 4
        int buildMenuTransitionStartTime_0x30; // 0x00000030 length: 4
        // In ms. Only the logic, visuals and menu interaction are not bound to this time.
        int buildMenuTransitionDuration_0x34; // 0x00000034 length: 4
        // Seems to be a percentage.
        int buildMenuTransitionProgress_0x38; // 0x00000038 length: 4
        // Set 1 when mouse is inside any handled menu item this frame; modal with border flag 0x800 uses it
        dword mouseOverMenuItem; // 0x0000003C length: 4

    private:
        MenuHandlerState(MenuHandlerState const&);
        void operator=(MenuHandlerState const&);

    public:
        MenuHandlerState() {};
        ~MenuHandlerState() {};

        /**
         * Resets build-menu transition state (not transitioning, background shift 0, direction -1) and stores the
         * two arguments into MenuHandlerState.buildMenuClipLeft/const516, used by prepareAndRenderMenuItems as left/right
         * clip limits (item-relative x) of build-menu buttons during the slide transition.
         */
        void setupBuildMenuState(dword clipLeft, dword clipRight);

        /**
         * Starts the build-menu slide transition: records start time and duration, sets transitioning flag,
         * progress 0, flips the direction sign (-1 <-> +1), plays a UI sound.
         */
        void startBuildMenuTransition(int transitionDuration);

        /**
         * Per frame: if progress already reached 100 just clears the transitioning flag; otherwise updates progress
         * (clamped 1..100 %) from elapsed time and computes shift = progress*376/100. Direction <= 0: background
         * shift 376-shift, items -shift before 50 % then same as background; direction > 0: background shift =
         * shift, items = shift, minus 376 from 50 % on (items jump to the other side halfway).
         */
        void computeBuildMenuTransitionShift();

        /**
         * Stores the UC layout array and menu-id/menu map, loads element positions for every menu in the map,
         * prepares the button/alpha surface and loads all modal menus' elements.
         */
        void initializeUI(
            MenuIDMenuElementAddressPair* menuIDMenuElementAddressPair, UC* ucPtr, char* ptrStrongholdUCString);

        /**
         * Looks up the menu for menuID in the menu map; if found makes it current, resets its items' state, resets
         * tooltip state (zero=0), sets one=1 (first-frame flag) and reloads its element positions.
         */
        void setupMenuForRendering(MenuViewType menuID);
    };

    static_assert_cpp98_obj(sizeof(MenuHandlerState) == 64, MenuHandlerState);

#pragma pack(pop)

} // namespace UI
} // namespace OpenSHC
