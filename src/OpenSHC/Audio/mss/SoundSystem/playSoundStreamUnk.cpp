#include "../SoundSystem.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Audio/mss/SoundFlagsAndLoopCountBitwiseFlagEnum.hpp"

#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x0047B060
        void SoundSystem::startSoundStream(
            SHC_SoundStream sndStreamIndex, char* filename, SoundFlagsAndLoopCount flagsAndLoopCount)
        {
            if (!this->soundSystemInitialized) {
                return;
            }

            if (flagsAndLoopCount & FLAG_SOUND_UNKNOWN_FLAG_2) {
                this->streamFlagsAndLoopCount[sndStreamIndex] = 1;
            }
            MACRO_CALL_MEMBER(SoundSystem_Func::endSoundStream, this)(sndStreamIndex);

            if (!this->sfxEnabled || DAT_WindowAndDirectDraw::ptr->isNotProcessingInputEvents
                || !DAT_WindowAndDirectDraw::ptr->gameFocused || this->streamOpen[sndStreamIndex]) {
                return;
            }

            if (sndStreamIndex == enums::SND_STR_MUSIC) {
                AIL_init_sample(this->musicSample);
                AIL_set_sample_type(this->musicSample, DIG_F_STEREO_16, 0);
                AIL_set_sample_playback_rate(this->musicSample, 22050);
                AIL_set_sample_pan(this->musicSample, 64);
                AIL_set_sample_volume(this->musicSample,
                    (this->streamVolume[sndStreamIndex] * this->streamUnduckedFileVolume[sndStreamIndex]) / 100);
                this->streamAppliedFileVolume[sndStreamIndex]
                    = this->streamUnduckedFileVolume[sndStreamIndex];
                this->currentMusicFileHandle = MACRO_CALL(OS_Func::_ucrt_open)(filename, _O_BINARY, 0);
                this->streamFlagsAndLoopCount[sndStreamIndex] = flagsAndLoopCount;
                this->musicStreamStopped = 0;
                if (this->currentMusicFileHandle == -1) {
                    return;
                }
                MACRO_CALL_MEMBER(SoundSystem_Func::refillMusicStreamBuffer, this)();
                MACRO_CALL_MEMBER(SoundSystem_Func::refillMusicStreamBuffer, this)();
                this->streamOpen[sndStreamIndex] = true;
                return;
            }

            this->stream_0xc[sndStreamIndex] = AIL_open_stream(this->digSndDriver_0x4, filename, 0);
            if (!this->stream_0xc[sndStreamIndex]) {
                return;
            }

            this->streamOpen[sndStreamIndex] = true;
            this->streamFlagsAndLoopCount[sndStreamIndex] = flagsAndLoopCount;
            // "!sndStreamIndex" was required to get the full byte match. This might indicate that instead of using "0"
            // directly to refer to the first/music stream, the just negate the given stream index, which is always 0.
            // It might be a coincidence or the current re-implementation of this method lacks some other pattern, but
            // it works for now and could be something to consider should other behaviors like this show up.
            if ((flagsAndLoopCount & FLAG_SOUND_UNKNOWN_FLAG_1) && this->streamOpen[!sndStreamIndex]) {
                AIL_set_sample_volume(this->musicSample,
                    this->streamVolume[!sndStreamIndex] * (this->streamUnduckedFileVolume[!sndStreamIndex] / 2)
                        / 100);
                this->streamAppliedFileVolume[!sndStreamIndex]
                    = this->streamUnduckedFileVolume[!sndStreamIndex] / 2;
            }
            if (flagsAndLoopCount & (FLAG_SOUND_UNKNOWN_FLAG_2 | FLAG_SOUND_UNINTERRUPTABLE)) {
                flagsAndLoopCount = 1;
            }
            AIL_set_stream_volume(this->stream_0xc[sndStreamIndex],
                (this->streamVolume[sndStreamIndex] * this->streamUnduckedFileVolume[sndStreamIndex]) / 100);
            this->streamAppliedFileVolume[sndStreamIndex] = this->streamUnduckedFileVolume[sndStreamIndex];
            AIL_set_stream_loop_count(
                this->stream_0xc[sndStreamIndex], flagsAndLoopCount & FLAG_SOUND_LOOP_COUNT_FIELD);
            AIL_start_stream(this->stream_0xc[sndStreamIndex]);
        }

    }
}
}
