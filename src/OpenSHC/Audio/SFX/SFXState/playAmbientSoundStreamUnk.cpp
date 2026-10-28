#include "../SFXState.func.hpp"

#include "OpenSHC/Audio/mss/SoundSystem.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_SpeechDefinedData.hpp"

namespace OpenSHC {
namespace Audio {
    namespace SFX {

        // FUNCTION: STRONGHOLDCRUSADER 0x0044A0F0
        void SFXState::playNextAmbientSoundIfStreamIdle(AmbientSFXType ambientSoundIndexUnk)
        {
            if (MACRO_CALL_MEMBER(MSS::SoundSystem_Func::isSampleOrStreamPlaying, DAT_SoundSystemState::ptr)(
                    MSS::enums::SND_STR_AMBIENT_1)) {
                return;
            }
            DAT_SoundSystemState::instance.streamUnduckedFileVolume[1]
                = DAT_SpeechDefinedData::instance.ambientSfxTable[ambientSoundIndexUnk].variationVolumes
                      [DAT_SpeechDefinedData::instance.ambientSfxTable[ambientSoundIndexUnk].nextVariantIndex];
            if (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_HISTORIC_MISSION_PICTURE
                || DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_HISTORIC_MISSION_INTRO
                || DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_HISTORIC_CAMPAIGN_INTRO) {
                DAT_SoundSystemState::instance.streamUnduckedFileVolume[1] = 127;
            }
            if (ambientSoundIndexUnk == ASFXT_BATTLE_OR_INTENSE || ambientSoundIndexUnk == ASFXT_HEAVY) {
                MACRO_CALL_MEMBER(MSS::SoundSystem_Func::playSoundOnSfxSoundStream1, DAT_SoundSystemState::ptr)(
                    DAT_SpeechDefinedData::instance.ambientSfxTable[ambientSoundIndexUnk].ambientWavs_0x8
                        [DAT_SpeechDefinedData::instance.ambientSfxTable[ambientSoundIndexUnk].nextVariantIndex],
                    50);
            } else {
                MACRO_CALL_MEMBER(
                    MSS::SoundSystem_Func::playSoundOnSfxSoundStream1OnceUninterruptible, DAT_SoundSystemState::ptr)(
                    DAT_SpeechDefinedData::instance.ambientSfxTable[ambientSoundIndexUnk].ambientWavs_0x8
                        [DAT_SpeechDefinedData::instance.ambientSfxTable[ambientSoundIndexUnk].nextVariantIndex]);
            }
            DAT_SpeechDefinedData::instance.ambientSfxTable[ambientSoundIndexUnk].nextVariantIndex++;
            if (DAT_SpeechDefinedData::instance.ambientSfxTable[ambientSoundIndexUnk].nextVariantIndex
                >= DAT_SpeechDefinedData::instance.ambientSfxTable[ambientSoundIndexUnk].variantCount) {
                DAT_SpeechDefinedData::instance.ambientSfxTable[ambientSoundIndexUnk].nextVariantIndex = 0;
            }
        }

    }
}
}
