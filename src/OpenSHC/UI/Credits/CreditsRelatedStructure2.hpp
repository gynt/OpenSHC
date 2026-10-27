/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/Credits/CreditsRelatedStructure2.hpp'
*/

#pragma once

#include "OpenSHC/Audio/MSS/SoundFlagsAndLoopCount.hpp"
#include "OpenSHC/Audio/MSS/enums/SHC_SoundStreamInt.hpp"

namespace OpenSHC {
namespace UI {
    namespace Credits {

        using OpenSHC::Audio::MSS::SoundFlagsAndLoopCount;
        using OpenSHC::Audio::MSS::enums::SHC_SoundStreamInt;

#pragma pack(push, 1)
        // SIZE: 0x0000005C
        typedef struct CreditsRelatedStructure2 {

            // Credits/intro script opcode (5/6/7 image, 0xc/0xd bink, 0xe-0x10 text, 0x15 fixed image, 0x1c pause,
            // 0x1f segment end, 0x20 terminator, 0x27, 0x28, 0x29/0x2a box...)
            int commandType; // 0x00000000 length: 4
            // [RUNTIME] command argument; a SHC_SoundStream only for sound commands (5..9, 90 seen otherwise)
            int arg; // 0x00000004 length: 4
            int x; // 0x00000008 length: 4
            int y; // 0x0000000C length: 4
            // Image width (from loaded gfx) or text max width
            int width; // 0x00000010 length: 4
            // Image/box height
            int height; // 0x00000014 length: 4
            // Text command font size (copied to element fontSize)
            int fontSize; // 0x00000018 length: 4
            // Placeholder +0x1C is a dword written with 0/1/2 by all credits command builders (array at 0xEB9B68,
            // stride 0x5C).
            undefined1 fadeMode[4]; // 0x0000001C length: 4
            SoundFlagsAndLoopCount flagLoopCount; // 0x00000020 length: 4
            // [176 0x004E0A50] used as sound stream index in opcode 0xd as well as bink slot in 0xc
            int slotIndex; // 0x00000024 length: 4
            // Render layer passed to the created element (7 for fixed images); for bink commands passed to the bink
            // player
            int drawLayer; // 0x00000028 length: 4
            int volume; // 0x0000002C length: 4
            // Text command: single-line centered vs word-wrapped
            int isSingleLine; // 0x00000030 length: 4
            // Text command: 1 renders text black
            int useBlackTextColor; // 0x00000034 length: 4
            // Image command: alternate gfx on mouse hover (-1 none)
            int hoverGfxIndex; // 0x00000038 length: 4
            // [RUNTIME] inline file name (code takes its address), not a pointer
            char binkFileName[32]; // 0x0000003C length: 32

        } CreditsRelatedStructure2;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(CreditsRelatedStructure2) == 92, CreditsRelatedStructure2);
    } // namespace Credits
} // namespace UI
} // namespace OpenSHC
