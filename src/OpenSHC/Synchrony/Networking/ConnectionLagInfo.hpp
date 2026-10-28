/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Synchrony/Networking/ConnectionLagInfo.hpp'
*/

#pragma once

#include "WinDef.h"

namespace OpenSHC {
namespace Synchrony {
    namespace Networking {

#pragma pack(push, 1)
        // SIZE: 0x00000024
        typedef struct ConnectionLagInfo {

            int mapTimeInTicks; // 0x00000000 length: 4
            int subtractedMapTicks; // 0x00000004 length: 4
            int counter; // 0x00000008 length: 4
            // [193 0x004882A0] average of subtractedMapTicks (half round-trip in map ticks)
            int avgHalfRttTicks; // 0x0000000C length: 4
            int now; // 0x00000010 length: 4
            DWORD subtractedTime; // 0x00000014 length: 4
            // [193 0x004882A0] average of subtractedTime (half round-trip in ms), computed from offset entries
            int avgHalfRttMs; // 0x00000018 length: 4
            // [193 0x004882A0] set to 1 once a matching ping reply was measured in game
            int hasLatencySample; // 0x0000001C length: 4
            // Created by retype action
            DWORD time; // 0x00000020 length: 4

        } ConnectionLagInfo;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(ConnectionLagInfo) == 36, ConnectionLagInfo);
    } // namespace Networking
} // namespace Synchrony
} // namespace OpenSHC
