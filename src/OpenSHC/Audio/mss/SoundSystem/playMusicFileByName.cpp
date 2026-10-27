// disable deprecation warnings for strcpy
#pragma warning(disable : 4996)

#include "../SoundSystem.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"

#include "OpenSHC/Globals/DAT_SFXState.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x0047b250
        void SoundSystem::playMusicFileByName(char* filename)
        {
            if (!this->soundSystemInitialized) {
                return;
            }
            strcpy(this->currentMusicFilename, filename);
            this->currentMusicFileVolume
                = MACRO_CALL_MEMBER(SFX::SFXState_Func::getSoundVolumeForFilename, DAT_SFXState::ptr)(filename);
            if (this->musicFadeState == 1) {
                this->streamUnduckedFileVolume[0] = 0;
            } else {
                this->streamUnduckedFileVolume[0] = (this->musicVolumeScalePercent * this->currentMusicFileVolume) / 100;
            }
            MACRO_CALL_MEMBER(SoundSystem_Func::startSoundStream, this)(enums::SND_STR_MUSIC, filename, 0);
            this->streamUnduckedFileVolume[0] = (this->musicVolumeScalePercent * this->currentMusicFileVolume) / 100;
        }

    }
}
}
