/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Audio/Speech/SpeechDefinedData.hpp'
*/

#pragma once

#include "OpenSHC/Audio/SFX/AmbientSfx.hpp"
#include "OpenSHC/Audio/SFX/NameSpeechPair.hpp"
#include "OpenSHC/Audio/SFX/SpeechEffectPath.hpp"
#include "OpenSHC/Audio/SFX/UnitSpeechData.hpp"

namespace OpenSHC {
namespace Audio {
    namespace Speech {

        using OpenSHC::Audio::SFX::AmbientSfx;
        using OpenSHC::Audio::SFX::NameSpeechPair;
        using OpenSHC::Audio::SFX::SpeechEffectPath;
        using OpenSHC::Audio::SFX::UnitSpeechData;

#pragma pack(push, 1)
        // SIZE: 0x0049D4C4
        typedef struct SpeechDefinedData {

            undefined1 padding_0x0[4]; // 0x00000000 length: 4
            char WavFileGroups[2][270][8][1000]; // 0x00000004 length: 4320000
            // 10 ambient sound types (AmbientSFXType: wind, battle, heavy...), each with wav variants and volumes
            AmbientSfx ambientSfxTable[10]; // 0x0041EB04 length: 720
            // UnitSpeechData per unit speech action ID (42), with numberOfVariations
            UnitSpeechData unitSpeechTable[42]; // 0x0041EDD4 length: 6216
            SpeechEffectPath SpeechEffectPathArray[40]; // 0x0042061C length: 640
            char SpeechEffectFileArray[65][1000]; // 0x0042089C length: 65000
            NameSpeechPair LordNameToCall[223]; // 0x00430684 length: 446000
            // ambient type currently playing on SFX stream 2 (7 or 8), -1 = none (tweakVolume)
            int stream2AmbientType; // 0x0049D4B4 length: 4
            // ambient type to switch to after the SFX1 fade-out completes; -1 = none
            undefined4 pendingAmbientTypeAfterFade; // 0x0049D4B8 length: 4
            // [039 0x0044BCE0] holds ambient type 2/4/5/6 or -1, not a stream ID
            int currentAmbientType; // 0x0049D4BC length: 4
            undefined1 padding_0x49d4c0[4]; // 0x0049D4C0 length: 4

        } SpeechDefinedData;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(SpeechDefinedData) == 4838596, SpeechDefinedData);
    } // namespace Speech
} // namespace Audio
} // namespace OpenSHC
