/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Units/Climbing/ClimbLogicDefinedData.hpp'
*/

#pragma once

#include "OpenSHC/Map/Navigation/Algorithms/XYPair.hpp"
#include "OpenSHC/Util/FunctionTypes/NoArgCallback.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {
        namespace Climbing {

            using OpenSHC::Map::Navigation::Algorithms::XYPair;
            using OpenSHC::Util::FunctionTypes::NoArgCallback;

#pragma pack(push, 1)
            // SIZE: 0x000002BC
            typedef struct ClimbLogicDefinedData {

                // updateClimbData calls [type*4+0xB3907C]: +0x00 is a 10-entry handler table
                // (469F10,4A4D60,469F10,4A4E40,4A4F90,4A50E0,469F10,4A5230,469F10,469F10), +0x28 is zero padding
                // before directionScanOrder. Requested by manual_changes.json.
                NoArgCallback* updateFunctions[10]; // 0x00000000 length: 40
                undefined1 padding_0x28[4]; // 0x00000028 length: 4
                // 8 direction indices in fan-out order {0,1,7,2,6,3,5,4} (bytes at 0xB390A8), iterated over
                // neighbour tiles by collectCliffEdgeTilesForClimbData and UpdateChicken. The updateClimbData
                // reference is a decompiler fold: the call reads the function table at ClimbLogicDefinedData+0
                // (0xB3907C) indexed by climbData.type
                int directionScanOrder[8]; // 0x0000002C length: 32
                int field6_0x4c[55]; // 0x0000004C length: 220
                undefined1 field7_0x128; // 0x00000128 length: 1
                undefined1 field8_0x129; // 0x00000129 length: 1
                undefined1 field9_0x12a; // 0x0000012A length: 1
                undefined1 field10_0x12b; // 0x0000012B length: 1
                byte BitFlagHelperForPathLinkage[8]; // 0x0000012C length: 8
                byte DirectionArray[8]; // 0x00000134 length: 8
                // Per direction d (8) the triple {d, d+-1, d-+1} (forward arc, bytes at 0xB391B8);
                // findBestAttackTargetTileWithHeightAndOwner uses only the first entry or all 3 depending on search
                // distance parity
                int directionArcTriples[8][3]; // 0x0000013C length: 96
                XYPair CardinalHorizontalFirstSearchOrder[4]; // 0x0000019C length: 32
                XYPair OrderedOrientationBasedCardinalDirectionList[8][4]; // 0x000001BC length: 256

            } ClimbLogicDefinedData;
#pragma pack(pop)

            static_assert_cpp98_obj(sizeof(ClimbLogicDefinedData) == 700, ClimbLogicDefinedData);
        } // namespace Climbing
    } // namespace Units
} // namespace Map
} // namespace OpenSHC
