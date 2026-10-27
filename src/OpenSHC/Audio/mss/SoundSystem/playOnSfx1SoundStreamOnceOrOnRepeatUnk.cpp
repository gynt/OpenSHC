#include "../SoundSystem.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Audio/mss/SoundFlagsAndLoopCountBitwiseFlagEnum.hpp"

#include "OpenSHC/Globals/DAT_SFXState.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x0047B590
        void SoundSystem::playSoundOnSfxSoundStream1OnceUninterruptible(char* filename)
        {
            this->streamUnduckedFileVolume[1]
                = MACRO_CALL_MEMBER(SFX::SFXState_Func::getSoundVolumeForFilename, DAT_SFXState::ptr)(filename);
            MACRO_CALL_MEMBER(SoundSystem_Func::startSoundStream, this)(
                enums::SND_STR_AMBIENT_1, filename, FLAG_SOUND_UNINTERRUPTABLE | 1);
        }

    }
}
}
