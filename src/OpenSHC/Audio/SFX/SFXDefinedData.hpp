/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Audio/SFX/SFXDefinedData.hpp'
*/

#pragma once

#include "OpenSHC/Audio/SFX/MusicSfx.hpp"

#include "mmsystem.h"

namespace OpenSHC {
namespace Audio {
    namespace SFX {

        using OpenSHC::Audio::SFX::MusicSfx;

#pragma pack(push, 1)
        // SIZE: 0x000004EC
        typedef struct SFXDefinedData {

            MMRESULT SomeTimerIdentifier; // 0x00000000 length: 4
            MusicSfx Pointers[116]; // 0x00000004 length: 928
            // [from][to] nonzero if battle-music segment 'to' may follow segment 'from' (segments = music ids
            // 0x22..0x29)
            int battleMusicSegmentTransitions[8][8]; // 0x000003A4 length: 256
            // per battle-music segment (exe init 1,0,2,1,0,0,0,0): tag 1/2 compared with battleMoodTrend when
            // choosing the next segment - a segment whose tag equals the trend is excluded, one with the opposite
            // tag is added twice; 0 = neutral (segment 4 is always weighted x6)
            int battleMusicSegmentMoodTag[8]; // 0x000004A4 length: 32
            // 6 pause lengths in ms (exe init 22500,33750,45000,33750,67500,45000) between the end of one peace-
            // time track and the next (timeGetTime - lastMusicEndTime), indexed by
            // SoundEffectsHelperData1.musicSilenceIntervalIndex
            uint musicSilenceIntervalsMs[6]; // 0x000004C4 length: 24
            int lastUsedSpeechStream; // 0x000004DC length: 4
            // speech stream index alternating 3/4 (exe init 4): playSpeechSfx increments it (wrapping 5 -> 3)
            // before playing, ends that stream if busy, and stores it to lastUsedSpeechStreamUnk
            int speechStreamRoundRobin; // 0x000004E0 length: 4
            // sound stream index (exe init 4) used by playAmbientStreamWithLoop, which plays tutorial narration
            // (callers are tutorial UI)
            int tutorialSpeechStreamIndex; // 0x000004E4 length: 4
            undefined1 padding_0x4e8[4]; // 0x000004E8 length: 4

        } SFXDefinedData;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(SFXDefinedData) == 1260, SFXDefinedData);
    } // namespace SFX
} // namespace Audio
} // namespace OpenSHC
