/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/ScrollingHandler.hpp'
*/

#pragma once

#include "OpenSHC/UI/ScrollDirectionInt.hpp"
#include "OpenSHC/UI/ScrollSpeedInt.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::UI::ScrollDirectionInt;
    using OpenSHC::UI::ScrollSpeedInt;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

    // SIZE: 0x00000048
    class ScrollingHandler {
    public:
        BOOLEnum isScrolling_0x0; // 0x00000000 length: 4
        ScrollDirectionInt scrollDirection_0x4; // 0x00000004 length: 4
        BOOLEnum scrollRight; // 0x00000008 length: 4
        BOOLEnum scrollLeft; // 0x0000000C length: 4
        BOOLEnum scrollDown; // 0x00000010 length: 4
        BOOLEnum scrollUp; // 0x00000014 length: 4
        BOOLEnum rightKeyDown_0x18; // 0x00000018 length: 4
        BOOLEnum leftKeyDown_0x1c; // 0x0000001C length: 4
        BOOLEnum downKeyDown_0x20; // 0x00000020 length: 4
        BOOLEnum upKeyDown_0x24; // 0x00000024 length: 4
        undefined4 field10_0x28; // 0x00000028 length: 4
        // scrollDistanceBase value used when not scrolling (1)
        undefined4 minScrollDistance; // 0x0000002C length: 4
        // Milliseconds of continuous scrolling per +1 scroll distance (0x14/0x11 by resolution; scaled by speed
        // setting)
        undefined4 scrollAccelMsPerStep; // 0x00000030 length: 4
        // Scroll distance cap basis (cap = value*2/3, scaled by speed setting); 0x28 at 800x600, 0x34 at 1024x768
        undefined4 maxScrollDistance; // 0x00000034 length: 4
        ScrollSpeedInt scrollSpeedSetting_0x38; // 0x00000038 length: 4
        int scrollDistanceBase; // 0x0000003C length: 4
        int timeOfLastNotScroll_0x40; // 0x00000040 length: 4
        // [255 0x00468AD0] now - timeOfLastNotScroll while scrolling
        int scrollElapsedMs; // 0x00000044 length: 4

    private:
        ScrollingHandler(ScrollingHandler const&);
        void operator=(ScrollingHandler const&);

    public:
        ScrollingHandler() {};
        ~ScrollingHandler() {};

        // Constructor
        /**
         * Constructor of the global ScrollingHandler: clears all scroll/key flags, direction = SD_NONE, step
         * interval 20 ms, max scroll distance 40, min distance 1, speed setting normal.
         */
        ScrollingHandler* Constructor_ScrollingHandler();

        /**
         * Per-frame scroll update: when no modal dialog is open, held arrow keys set the scroll flags; combines
         * up/down/left/right flags into scrollDirection. When not scrolling resets distance to the minimum and
         * records the time; otherwise scrollDistanceBase = elapsed ms / step interval (interval x2/3 for fast, x1.5
         * for slow), capped at 2/3 of the max distance (x1.33 i.e. *0x85/100 for fast, /2 for slow). Clears the
         * per-frame direction flags.
         */
        void handleScrolling();

        /**
         * Getter: returns ScrollingHandler.scrollDistanceBase (current scroll step distance computed by
         * handleScrolling).
         */
        int getScrollDistanceBase();
    };

    static_assert_cpp98_obj(sizeof(ScrollingHandler) == 72, ScrollingHandler);

#pragma pack(pop)

} // namespace UI
} // namespace OpenSHC
