#include "../SoundSystem.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Audio/MSS/SoundFlagsAndLoopCountBitwiseFlagEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_SFXDefinedData.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x0047B670
        void SoundSystem::playSpeechSfx(char* soundFileName)
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
            ++DAT_SFXDefinedData::instance.speechStreamRoundRobin;
            if (DAT_SFXDefinedData::instance.speechStreamRoundRobin > 4) {
                DAT_SFXDefinedData::instance.speechStreamRoundRobin = 3;
            }
            if (this->streamOpen[DAT_SFXDefinedData::instance.speechStreamRoundRobin]) {
                MACRO_CALL_MEMBER(SoundSystem_Func::endSoundStream, this)(
                    (SHC_SoundStream)DAT_SFXDefinedData::instance.speechStreamRoundRobin);
            }
            int const nextVolume
                = MACRO_CALL_MEMBER(SFX::SFXState_Func::getSoundVolumeForFilename, DAT_SFXState::ptr)(soundFileName);
            this->streamUnduckedFileVolume[3] = nextVolume;
            this->streamUnduckedFileVolume[4] = nextVolume;
            MACRO_CALL_MEMBER(SoundSystem_Func::startSoundStream, this)(
                (SHC_SoundStream)DAT_SFXDefinedData::instance.speechStreamRoundRobin, soundFileName, 1);
            DAT_SoundSystemState::instance.lastUsedSpeechStream = DAT_SFXDefinedData::instance.speechStreamRoundRobin;
        }
    }

}
}
