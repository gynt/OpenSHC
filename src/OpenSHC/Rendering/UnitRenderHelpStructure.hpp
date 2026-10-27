/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Rendering/UnitRenderHelpStructure.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Rendering {

#pragma pack(push, 1)
    // SIZE: 0x00000020
    typedef struct UnitRenderHelpStructure {

        int unitIDOrStatus; // 0x00000000 length: 4
        int ownerColor; // 0x00000004 length: 4
        int spriteID; // 0x00000008 length: 4
        int drawX; // 0x0000000C length: 4
        int drawY; // 0x00000010 length: 4
        // [181 0x004E7810] for unit entries (unitID > 0) passed as width to renderUnitAnimationUnk and used to
        // centre the health bar ((w-0x16)/2)
        int imageIDOrWidth; // 0x00000014 length: 4
        // [181 0x004E7810] for unit entries passed as height to renderUnitAnimationUnk; packed flags for unitID 0
        int blendOrHeight; // 0x00000018 length: 4
        // [181 0x004E7810] for unit entries passed as imageAddress (byte*) to renderUnitAnimationUnk; mask frame
        // for unitID -1
        int gmIDOrPixelPtr; // 0x0000001C length: 4

    } UnitRenderHelpStructure;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(UnitRenderHelpStructure) == 32, UnitRenderHelpStructure);
} // namespace Rendering
} // namespace OpenSHC
