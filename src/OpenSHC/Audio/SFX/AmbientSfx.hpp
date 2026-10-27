/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Audio/SFX/AmbientSfx.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Audio {
    namespace SFX {

#pragma pack(push, 1)
        // SIZE: 0x00000048
        typedef struct AmbientSfx {

            // number of wav variants for this ambient type; nextVariantIndex wraps to 0 when reaching it
            int variantCount; // 0x00000000 length: 4
            char* ambientWavs_0x8[8]; // 0x00000004 length: 32
            // [039 0x0044AE90] 8 ints filled with getSoundVolumeForFilename of the 8 filename pointers located 8
            // ints before (piVar7[-8])
            int variationVolumes[8]; // 0x00000024 length: 32
            // cyclic index into ambientWavs/volume arrays of the variant to play next
            int nextVariantIndex; // 0x00000044 length: 4

        } AmbientSfx;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(AmbientSfx) == 72, AmbientSfx);
    } // namespace SFX
} // namespace Audio
} // namespace OpenSHC
