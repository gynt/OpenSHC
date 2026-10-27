/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Rendering/Bink/BinkControlClass.hpp'
*/

#pragma once

#include "OpenSHC/Audio/MSS/enums/SHC_SoundStream.hpp"
#include "OpenSHC/Audio/MSS/enums/SHC_SoundStreamInt.hpp"
#include "OpenSHC/Rendering/Bink/UnsortedBinkFlagInt.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "Mss32.h"
#include "WinDef.h"
#include "binkw32.h"

namespace OpenSHC {
namespace Rendering {
    namespace Bink {

        using OpenSHC::Audio::MSS::enums::SHC_SoundStream;
        using OpenSHC::Audio::MSS::enums::SHC_SoundStreamInt;
        using OpenSHC::Rendering::Bink::UnsortedBinkFlagInt;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

        // SIZE: 0x00000060
        class BinkControlClass {
        public:
            // [177 0x00408ED0] playBINK param_4; 0 copies frames to the screenMenu surface, nonzero to the mapGame
            // surface
            dword useMapGameSurface[2]; // 0x00000000 length: 8
            int xPos[2]; // 0x00000008 length: 8
            int yPos[2]; // 0x00000010 length: 8
            BOOLEnum frameReadyToDisplay[2]; // 0x00000018 length: 8
            // [177 0x00408ED0] playBINK param_3 (credits flagLoopCount); at the last frame 0 stops/holds the video,
            // nonzero calls BinkNextFrame (wraps)
            dword loopFlag[2]; // 0x00000020 length: 8
            // [177 0x00408ED0] playBINK param_7; compared with copyBinkToVideoBuffer's argument; 2 = full-screen
            // menu video
            dword displayMode[2]; // 0x00000028 length: 8
            // [177 0x00408FC0] set to 1 when a non-looping video reaches its last frame and the slot is stopped
            dword playbackEnded[2]; // 0x00000030 length: 8
            // [177 0x00408FC0] set to 1 when a non-looping displayMode-2 video reaches its last frame and is kept
            // open
            dword lastFrameReached[2]; // 0x00000038 length: 8
            SHC_SoundStreamInt soundStreamIndex[2]; // 0x00000040 length: 8
            dword startTime[2]; // 0x00000048 length: 8
            HBINK binkObjPtrArray[2]; // 0x00000050 length: 8
            UnsortedBinkFlagInt mapGameSurfaceType; // 0x00000058 length: 4
            UnsortedBinkFlagInt screenMenuSurfaceType_0x5c; // 0x0000005C length: 4

        private:
            BinkControlClass(BinkControlClass const&);
            void operator=(BinkControlClass const&);

        public:
            BinkControlClass() {};
            ~BinkControlClass() {};

            /**
             * Clears both Bink handle slots and registers Miles (BinkOpenMiles) with the given digital driver as
             * Bink's sound system.
             */
            void zeroBinkPtrAndLoadBinkSoundSystem(HDIGDRIVER drvrPtr);

            /**
             * Closes the Bink video in the given slot if open and clears its handle; for slot 1 (in-game message
             * video) also clears GameCore.isBinkVideoPlaying and sets countdown to 1.
             */
            void stopBinkPlayback(int binkObjIndex);

            /**
             * If sound output is active, links a Bink slot to a sound stream and records the current time (used
             * later to detect the stream end / 20 s timeout).
             */
            void setBinkSndStreamAndStartTime(int binkObjIndex, SHC_SoundStream soundStreamIndexUnk);

            /**
             * Stops Bink playback in both slots (0 and 1).
             */
            void stopAllBinkPlayback();

            /**
             * Opens a Bink file (resolved via FRT_BINKS) in the given slot, closing any previous video; with sound
             * off it is muted, otherwise its volume is getSoundVolumeForFilename(binkFileName)*250. Initialises the
             * slot state. Decompiler stack is 8 bytes off after BinkOpen (stdcall _BinkOpen@8 modelled without
             * purge): the real code passes the ORIGINAL binkFileName to getSoundVolumeForFilename (shown as
             * unaff_retaddr) and stores xPos[i]=xPos, yPos[i]=yPos, unknownParam04[i]=param_4,
             * unknownParam03[i]=param_3, unknownParam07[i]=param_7.
             */
            void playBINK(
                int binkObjIndex, char* binkFileName, DWORD param_3, DWORD param_4, int xPos, int yPos, DWORD param_7);

            /**
             * Per-frame Bink update for both slots: expires a linked sound stream (ended or >20 s); for slots whose
             * displayMode equals the argument resets the end flags, waits/advances the frame
             * (BinkWait/BinkDoFrame/BinkNextFrame) and at the last frame of a non-looping video either stops it (no
             * linked stream, mode != 2), holds it on the last frame while a linked stream still plays, or (mode 2)
             * keeps it and sets unknown02_zero; then copies a ready frame into the locked screenMenu or mapGame
             * DirectDraw surface (Lock with DDLOCK_WAIT, Restore + relock on DDERR_SURFACELOST, BinkCopyToBuffer,
             * Unlock). Mode 2 also moves the current menu to the border offset and clears the screen black. The
             * SND_STR_* constants shown for the neighbouring fields are 0/1 flag values mistyped by the struct
             * walk.
             */
            void copyBinkToVideoBuffer(dword displayMode);

            /**
             * Advances both Bink slots one frame without drawing: expires linked sound streams (ended or >20 s),
             * resets the end flags, does BinkWait/DoFrame/NextFrame; at the last frame of a non-looping video it
             * stops it (no linked stream, displayMode != 2), holds it while a linked stream plays, or flags
             * unknown02_zero for displayMode 2; marks frames ready to display. The SND_STR_* constants
             * compared/stored here are 0/1/2 flag and mode values mistyped by the struct walk.
             */
            void processBinkFrames();

            void stopAllBinkPlaybackThunk();
        };

        static_assert_cpp98_obj(sizeof(BinkControlClass) == 96, BinkControlClass);

#pragma pack(pop)

    } // namespace Bink
} // namespace Rendering
} // namespace OpenSHC
