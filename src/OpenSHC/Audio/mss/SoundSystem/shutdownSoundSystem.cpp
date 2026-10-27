#include "../SoundSystem.func.hpp"

#include "OpenSHC/Rendering/Bink/BinkControlClass.func.hpp"

#include "OpenSHC/Globals/DAT_BinkControlState.hpp"
#include "OpenSHC/Globals/DAT_SFXDefinedData.hpp"
#include "OpenSHC/Globals/DAT_SoundEffectsHelperData1.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x0047A690
        void SoundSystem::shutdownSoundSystem()
        {
            if (!this->soundSystemInitialized) {
                return;
            }

            MACRO_CALL_MEMBER(Rendering::Bink::BinkControlClass_Func::stopAllBinkPlayback, DAT_BinkControlState::ptr)();
            if (DAT_SFXDefinedData::ptr->SomeTimerIdentifier != UINT_MAX) {
                timeKillEvent(DAT_SFXDefinedData::ptr->SomeTimerIdentifier);
                timeEndPeriod(DAT_SoundEffectsHelperData1::ptr->SND_SomeTimerResolution);
                DAT_SFXDefinedData::ptr->SomeTimerIdentifier = UINT_MAX;
            }
            for (int i = 0; i < 5; ++i) {
                this->streamFlagsAndLoopCount[i] = 0;
                MACRO_CALL_MEMBER(SoundSystem_Func::endSoundStream, this)((SHC_SoundStream)i);
            }
            for (int i = 1; i < 32; ++i) {
                AIL_end_sample(this->sample[i]);
                AIL_release_sample_handle(this->sample[i]);
            }
            for (int i = 1; i < this->loadedSoundsCountAndIndex_0x316c; ++i) {
                if (this->soundFileDataPointerArray_0x122c[i]) {
                    AIL_mem_free_lock(this->soundFileDataPointerArray_0x122c[i]);
                }
            }
            AIL_mem_free_lock(this->musicSampleBuffers[0]);
            AIL_mem_free_lock(this->musicSampleBuffers[1]);
            AIL_release_sample_handle(this->musicSample);
            AIL_close_digital_driver(this->digSndDriver_0x4);
            AIL_shutdown();
            this->soundSystemInitialized = FALSE;
        }

    }
}
}
