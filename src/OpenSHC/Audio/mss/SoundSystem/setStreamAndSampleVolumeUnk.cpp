#include "../SoundSystem.func.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // NOTE:
        // Quick test showed usage for SND_STR_MUSIC (0) and SND_STR_AMBIENT_2 (2), but this might be coincidental
        // Test showed usage mostly for fading music out, during gameplay or during menu switches

        // FUNCTION: STRONGHOLDCRUSADER 0x00479AF0
        void SoundSystem::setStreamFileVolume(SHC_SoundStream sndStreamIndex, int volumeParam)
        {
            if (!(this->soundSystemInitialized && this->streamOpen[sndStreamIndex])) {
                return;
            }

            if (sndStreamIndex == enums::SND_STR_MUSIC) {
                AIL_set_sample_volume(this->musicSample, (this->streamVolume[0] * volumeParam) / 100);
            } else {
                AIL_set_stream_volume(
                    this->stream_0xc[sndStreamIndex], (this->streamVolume[sndStreamIndex] * volumeParam) / 100);
            }
            this->streamAppliedFileVolume[sndStreamIndex] = volumeParam;
        }

    }
}
}
