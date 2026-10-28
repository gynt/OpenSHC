#include "../SoundSystem.func.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x00479A60
        BOOLEnum SoundSystem::isSampleOrStreamPlaying(SHC_SoundStream streamIndex)
        {
            if (!(this->soundSystemInitialized && this->streamOpen[streamIndex])) {
                return false;
            }

            if (streamIndex == enums::SND_STR_MUSIC) {
                if (AIL_sample_status(this->musicSample) == SMP_PLAYING) {
                    return true;
                }
            } else {
                HSTREAM const stream = this->stream_0xc[streamIndex];
                if (stream && AIL_stream_status(stream) == SMP_PLAYING) {
                    return true;
                }
            }
            return false;
        }

    }
}
}
