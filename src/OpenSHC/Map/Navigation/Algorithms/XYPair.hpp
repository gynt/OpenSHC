/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Navigation/Algorithms/XYPair.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Navigation {
        namespace Algorithms {

#pragma pack(push, 1)
            // SIZE: 0x00000008
            typedef struct XYPair {

                // XYPair offset 0 is always paired with .y as X (9 batches; review 379 instruction-level check at
                // 0x4DDA30); textPageStartTime was propagated from one unrelated use [249 0x004DAFB0] holds
                // timeGetTime() set in DisplayFullScreenTextPage and subtracted here
                int x; // 0x00000000 length: 4
                int y; // 0x00000004 length: 4

            } XYPair;
#pragma pack(pop)

            static_assert_cpp98_obj(sizeof(XYPair) == 8, XYPair);
        } // namespace Algorithms
    } // namespace Navigation
} // namespace Map
} // namespace OpenSHC
