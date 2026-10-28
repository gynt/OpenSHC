#include "../SFXState.func.hpp"

#include "OpenSHC/Audio/mss/SoundSystem.func.hpp"

#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_SpeechDefinedData.hpp"

namespace OpenSHC {
namespace Audio {
    namespace SFX {

        // FUNCTION: STRONGHOLDCRUSADER 0x0044A1B0
        void SFXState::playNextAmbientSoundIfStream2Idle(int ambientSoundIndexUnk)
        {
            if (MACRO_CALL_MEMBER(MSS::SoundSystem_Func::isSampleOrStreamPlaying, DAT_SoundSystemState::ptr)(
                    MSS::enums::SND_STR_AMBIENT_2)) {
                return;
            }
            DAT_SoundSystemState::instance.streamUnduckedFileVolume[2]
                = DAT_SpeechDefinedData::instance.ambientSfxTable[ambientSoundIndexUnk].variationVolumes
                      [DAT_SpeechDefinedData::instance.ambientSfxTable[ambientSoundIndexUnk].nextVariantIndex];
            if (ambientSoundIndexUnk == 5) {
                MACRO_CALL_MEMBER(MSS::SoundSystem_Func::playSoundOnSfxSoundStream2, DAT_SoundSystemState::ptr)(
                    DAT_SpeechDefinedData::instance.ambientSfxTable[ambientSoundIndexUnk].ambientWavs_0x8
                        [DAT_SpeechDefinedData::instance.ambientSfxTable[ambientSoundIndexUnk].nextVariantIndex],
                    50);
            } else {
                MACRO_CALL_MEMBER(MSS::SoundSystem_Func::playSoundOnSoundStream2, DAT_SoundSystemState::ptr)(
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
