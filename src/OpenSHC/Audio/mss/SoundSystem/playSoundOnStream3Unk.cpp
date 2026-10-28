#include "../SoundSystem.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"

#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x0047B830
        void SoundSystem::playSoundOnSpeechStream1(char* filename, SoundFlagsAndLoopCount flagsAndLoopCount)
        {
            if (!this->soundSystemInitialized) {
                return;
            }
            int const volume
                = MACRO_CALL_MEMBER(SFX::SFXState_Func::getSoundVolumeForFilename, DAT_SFXState::ptr)(filename);
            this->streamUnduckedFileVolume[3] = volume;
            this->streamUnduckedFileVolume[4] = volume;
            MACRO_CALL_MEMBER(SoundSystem_Func::startSoundStream, this)(
                enums::SND_STR_SPEECH_1, filename, flagsAndLoopCount);
            DAT_SoundSystemState::instance.lastUsedSpeechStream = 3;
        }
    }

}
}
