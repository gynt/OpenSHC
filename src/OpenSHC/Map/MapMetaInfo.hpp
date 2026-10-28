/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/MapMetaInfo.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {

#pragma pack(push, 1)
    // SIZE: 0x0000000C
    typedef struct MapMetaInfo {

        // [054 0x0046C280] per-entry scalar returned as the checksum of one map (filled from
        // fileHashFunctionByteByByte), not an array Unsigned Double-Word (ddw, 4-bytes)
        dword fileChecksum; // 0x00000000 length: 4
        char mapType; // 0x00000004 length: 1
        // Unsigned Byte (db)
        char mapLocked; // 0x00000005 length: 1
        // Unsigned Byte (db)
        char mapBalance; // 0x00000006 length: 1
        // Unsigned Byte (db)
        char mapEndInt2; // 0x00000007 length: 1
        // Unsigned Byte (db)
        char mapPlayerCount; // 0x00000008 length: 1
        // [054 0x0046C200] copied into DAT_MapPropertiesState.scenarionMissionType Unsigned Byte (db)
        char scenarioMissionType; // 0x00000009 length: 1
        // [054 0x0046C200] copied into DAT_MapPropertiesState.scenarioMissionSiegeOrInvasion Unsigned Byte (db)
        char scenarioMissionSiegeOrInvasion; // 0x0000000A length: 1
        undefined1 padding_0xb[1]; // 0x0000000B length: 1

    } MapMetaInfo;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(MapMetaInfo) == 12, MapMetaInfo);
} // namespace Map
} // namespace OpenSHC
