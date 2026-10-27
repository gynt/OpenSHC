#include "../SoundSystem.func.hpp"

#include "OpenSHC/Audio/MSS/SoundFlagsAndLoopCountBitwiseFlagEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_SFXDefinedData.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x0047B5F0
        void SoundSystem::playSoundOnSpeechStream(char* filename)
        {
            if (!this->soundSystemInitialized) {
                return;
            }
            if ((this->streamFlagsAndLoopCount[enums::SND_STR_SPEECH_1] & FLAG_SOUND_UNINTERRUPTABLE)
                && MACRO_CALL_MEMBER(SoundSystem_Func::isSampleOrStreamPlaying, this)(enums::SND_STR_SPEECH_1)) {
                return;
            }
            if (DAT_GameCore::instance.gameMode_2 == Game::GM_CRUSADER_TUTORIAL) {
                return;
            }
            ++DAT_SFXDefinedData::instance.lastUsedSpeechStream;
            if (DAT_SFXDefinedData::instance.lastUsedSpeechStream > 4) {
                DAT_SFXDefinedData::instance.lastUsedSpeechStream = 3;
            }
            if (this->streamOpen[DAT_SFXDefinedData::instance.lastUsedSpeechStream]) {
                MACRO_CALL_MEMBER(SoundSystem_Func::endSoundStream, this)(
                    (SHC_SoundStream)DAT_SFXDefinedData::instance.lastUsedSpeechStream);
            }
            SHC_SoundStream const speechStream = (SHC_SoundStream)DAT_SFXDefinedData::instance.lastUsedSpeechStream;
            this->streamUnduckedFileVolume[3] = 100;
            this->streamUnduckedFileVolume[4] = 100;
            MACRO_CALL_MEMBER(SoundSystem_Func::startSoundStream, this)(speechStream, filename, 1);
            DAT_SoundSystemState::instance.lastUsedSpeechStream
                = DAT_SFXDefinedData::instance.lastUsedSpeechStream;
        }

    }
}
}
