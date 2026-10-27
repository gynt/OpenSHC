// disable deprecation warnings for strcpy
#pragma warning(disable : 4996)

#include "../SoundSystem.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"

#include "OpenSHC/Globals/DAT_SFXState.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x0047B760
        void SoundSystem::playMusicFile(char* filename, SoundFlagsAndLoopCount flagsAndLoop)
        {
            if (!this->soundSystemInitialized) {
                return;
            }
            strcpy(this->currentMusicFilename, filename);
            int const _volume
                = MACRO_CALL_MEMBER(SFX::SFXState_Func::getSoundVolumeForFilename, DAT_SFXState::ptr)(filename);
            this->currentMusicFileVolume = _volume;
            this->streamUnduckedFileVolume[0] = (this->musicVolumeScalePercent * _volume) / 100;
            MACRO_CALL_MEMBER(SoundSystem_Func::startSoundStream, this)(enums::SND_STR_MUSIC, filename, flagsAndLoop);
        }
    }

}
}
