#include "../SoundSystem.func.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x0047B870
        void SoundSystem::enableSoundAndRestartMusic()
        {
            if (!this->soundSystemInitialized) {
                return;
            }
            this->sfxEnabled = true;
            MACRO_CALL_MEMBER(SoundSystem_Func::playMusicFile, this)(
                this->currentMusicFilename, this->streamFlagsAndLoopCount[0]);
        }
    }

}
}
