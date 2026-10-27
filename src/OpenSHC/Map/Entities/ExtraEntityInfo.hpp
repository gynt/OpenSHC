/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Entities/ExtraEntityInfo.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Entities {

#pragma pack(push, 1)
        // SIZE: 0x00000064
        typedef struct ExtraEntityInfo {

            short entityID; // 0x00000000 length: 2
            short randomNumber; // 0x00000002 length: 2
            int entityUID; // 0x00000004 length: 4
            // Seagull slot state: 0 = free, 2 = active
            short slotState; // 0x00000008 length: 2
            // Zeroed in createSeagull; no reader seen
            short unkResetOnCreateA; // 0x0000000A length: 2
            short x; // 0x0000000C length: 2
            short y; // 0x0000000E length: 2
            short x_2; // 0x00000010 length: 2
            short y_2; // 0x00000012 length: 2
            short angle; // 0x00000014 length: 2
            // [075 0x00406650] random 24..39, multiplied by sin/cos of the angle to get the target offset
            short circleRadius; // 0x00000016 length: 2
            // +-1 factor of the 20-degree gull circling step (2 functions agree)
            short circleDirection; // 0x00000018 length: 2
            // Lap counter cycling -20..19 (one step per full circle); while negative the circle radius
            // unknownCounter_0x16 grows by 1 per lap, while positive it shrinks (clamped 24..80)
            short circlePhase; // 0x0000001A length: 2
            short angle_2; // 0x0000001C length: 2
            // random 60..99, radius of the orbit-centre offset in processSeaGulls (2 functions agree); Center
            // spelling as in types.h
            short orbitCenterRadius; // 0x0000001E length: 2
            // +1/-1 increment applied to angle_2 each tick
            short angle2Step; // 0x00000020 length: 2
            // init 400, reset 400..799; counts down before a new sea destination is picked (2 functions agree)
            short retargetWaitCountdown; // 0x00000022 length: 2
            short x_3; // 0x00000024 length: 2
            short y_3; // 0x00000026 length: 2
            // Bresenham increment 2*minor for seagull drift line
            short lineStepIncMinor; // 0x00000028 length: 2
            // Bresenham increment 2*minor - 2*major
            short lineStepIncMajor; // 0x0000002A length: 2
            // Bresenham error accumulator
            short lineStepError; // 0x0000002C length: 2
            // 0 none, 1 vertical, 2 horizontal, 3 Y-major, 4 X-major
            short lineStepMode; // 0x0000002E length: 2
            // +1/-1 X direction of drift line
            short lineStepDirX; // 0x00000030 length: 2
            // +1/-1 Y direction of drift line
            short lineStepDirY; // 0x00000032 length: 2
            // Ticks until the next centre step (5 after creation, reset to 10)
            short lineStepDelay; // 0x00000034 length: 2
            // set to 0xA0 when diving; at 0 gull resurfaces with FX_GULL_SURFACE
            short diveCountdown; // 0x00000036 length: 2
            // Remaining drift steps (major delta)
            short lineStepsLeft; // 0x00000038 length: 2
            short field28_0x3a; // 0x0000003A length: 2
            short field29_0x3c; // 0x0000003C length: 2
            short field30_0x3e; // 0x0000003E length: 2
            short field31_0x40; // 0x00000040 length: 2
            short field32_0x42; // 0x00000042 length: 2
            short field33_0x44; // 0x00000044 length: 2
            short field34_0x46; // 0x00000046 length: 2
            short field35_0x48; // 0x00000048 length: 2
            short field36_0x4a; // 0x0000004A length: 2
            short field37_0x4c; // 0x0000004C length: 2
            short field38_0x4e; // 0x0000004E length: 2
            short field39_0x50; // 0x00000050 length: 2
            short field40_0x52; // 0x00000052 length: 2
            short field41_0x54; // 0x00000054 length: 2
            short field42_0x56; // 0x00000056 length: 2
            short field43_0x58; // 0x00000058 length: 2
            short field44_0x5a; // 0x0000005A length: 2
            short field45_0x5c; // 0x0000005C length: 2
            short field46_0x5e; // 0x0000005E length: 2
            short field47_0x60; // 0x00000060 length: 2
            short field48_0x62; // 0x00000062 length: 2

        } ExtraEntityInfo;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(ExtraEntityInfo) == 100, ExtraEntityInfo);
    } // namespace Entities
} // namespace Map
} // namespace OpenSHC
