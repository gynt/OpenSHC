#include "../SoundSystem.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"

#include "OpenSHC/Globals/DAT_SFXState.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x0047B5C0
        void SoundSystem::playSoundOnSoundStream2(char* filename)
        {
            this->streamUnduckedFileVolume[1]
                = MACRO_CALL_MEMBER(SFX::SFXState_Func::getSoundVolumeForFilename, DAT_SFXState::ptr)(filename);
            MACRO_CALL_MEMBER(SoundSystem_Func::startSoundStream, this)(enums::SND_STR_AMBIENT_2, filename, 1);
        }

    }
}
}
