#include "../SoundSystem.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Audio/mss/SoundFlagsAndLoopCountBitwiseFlagEnum.hpp"

#include "OpenSHC/Globals/DAT_SoundEffectsHelperData1.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x004799A0
        void SoundSystem::endSoundStream(SHC_SoundStream sndStreamIndex)
        {
            if (!this->soundSystemInitialized) {
                return;
            }

            if (sndStreamIndex == enums::SND_STR_MUSIC) {
                this->streamOpen[0] = 0;
                DAT_SoundEffectsHelperData1::ptr->musicStreamBusyMainThread = true;
                if (this->currentMusicFileHandle != -1) {
                    AIL_end_sample(this->musicSample);
                    MACRO_CALL(OS_Func::_ucrt_close)(this->currentMusicFileHandle);
                }
                if (this->queuedMusicFileHandle != -1) {
                    MACRO_CALL(OS_Func::_ucrt_close)(this->queuedMusicFileHandle);
                }
                this->queuedMusicFileHandle = -1;
                this->currentMusicFileHandle = -1;
                this->musicStreamStopped = 1;
                DAT_SoundEffectsHelperData1::ptr->musicStreamBusyMainThread = false;
                this->playingMusicId = 0;
                return;
            }

            if (!this->streamOpen[sndStreamIndex]) {
                return;
            }

            if (this->streamFlagsAndLoopCount[sndStreamIndex] & FLAG_SOUND_UNINTERRUPTABLE
                && AIL_stream_status(this->stream_0xc[sndStreamIndex]) == SMP_PLAYING) {
                return;
            }
            AIL_close_stream(this->stream_0xc[sndStreamIndex]);
            this->streamOpen[sndStreamIndex] = 0;
            this->stream_0xc[sndStreamIndex] = 0x0;
        }

    }
}
}
