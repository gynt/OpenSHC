#include "../SoundSystem.func.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x00479E60
        void SoundSystem::setStreamOrSfxVolume(int streamIndex, int volume)
        {
            if (!this->soundSystemInitialized) {
                return;
            }

            if (streamIndex == -1) {
                this->sampleVolume = volume;
                for (int i = 1; i < 32; ++i) {
                    AIL_set_sample_volume(
                        this->sample[i], (this->sampleSndStructVolumePercentage_0x3174[i] * volume) / 100);
                }
                return;
            }
            this->streamVolume[streamIndex] = volume;
            if (!this->streamOpen[streamIndex]) {
                return;
            }
            if (streamIndex == 0) {
                AIL_set_sample_volume(
                    this->musicSample, (this->streamAppliedFileVolume[0] * volume) / 100);
                return;
            }
            AIL_set_stream_volume(
                this->stream_0xc[streamIndex], (this->streamAppliedFileVolume[streamIndex] * volume) / 100);
        }

    }
}
}
