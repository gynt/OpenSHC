#include "../SoundSystem.func.hpp"

#include "OpenSHC/Audio/mss/SoundFlagsAndLoopCountBitwiseFlagEnum.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x00479F30
        void SoundSystem::turnSoundOff()
        {
            if (!this->soundSystemInitialized) {
                return;
            }

            for (int i = 0; i < 5; ++i) {
                this->streamFlagsAndLoopCount[i] &= ~FLAG_SOUND_UNINTERRUPTABLE;
                MACRO_CALL_MEMBER(SoundSystem_Func::endSoundStream, this)((SHC_SoundStream)i);
            }

            for (int i = 1; i < 32; ++i) {
                AIL_end_sample(this->sample[i]);
                this->sampleSoundIndex_0x20c[i] = 0;
            }

            for (int i = 1; i < this->loadedSoundsCountAndIndex_0x316c; ++i) {
                this->soundFileCurrSampleNum_0x28c[i] = -1;
            }
            this->sfxEnabled = 0;
        }

    }
}
}
