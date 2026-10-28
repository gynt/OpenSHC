#include "../SoundSystem.func.hpp"

#include "OpenSHC/Audio/mss.func.hpp"
#include "OpenSHC/Rendering/Bink/BinkControlClass.func.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_BinkControlState.hpp"
#include "OpenSHC/Globals/DAT_SFXDefinedData.hpp"
#include "OpenSHC/Globals/DAT_SoundEffectsHelperData1.hpp"

// not using copied helper
#undef AIL_startup

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x0047C400
        void SoundSystem::initMiles()
        {
            AIL_set_redist_directory(s_miles_005a6cfc);
            MACRO_CALL(MSS_Func::RegisterMilesAILShutdown)();
            AIL_startup();
            DAT_SoundEffectsHelperData1::instance.SND_Waveformat.wFormatTag = WAVE_FORMAT_PCM;
            DAT_SoundEffectsHelperData1::instance.SND_Waveformat.nChannels = 2;
            DAT_SoundEffectsHelperData1::instance.SND_Waveformat.nSamplesPerSec = 44100;
            DAT_SoundEffectsHelperData1::instance.SND_Waveformat.nAvgBytesPerSec = 176400;
            DAT_SoundEffectsHelperData1::instance.SND_Waveformat.nBlockAlign = 4;
            DAT_SoundEffectsHelperData1::instance.SND_Waveformat.wBitsPerSample = 16;
            BOOL const _waveOpenErrorUnk = AIL_waveOutOpen(
                &this->digSndDriver_0x4, 0, -1, &DAT_SoundEffectsHelperData1::instance.SND_Waveformat);
            if (_waveOpenErrorUnk == AIL_NO_ERROR) {
                this->soundSystemInitialized = TRUE;
            } else {
                this->soundSystemInitialized = FALSE;
            }
            if (!this->soundSystemInitialized) {
                return;
            }

            MACRO_CALL_MEMBER(Rendering::Bink::BinkControlClass_Func::zeroBinkPtrAndLoadBinkSoundSystem,
                DAT_BinkControlState::ptr)(this->digSndDriver_0x4);
            this->streamOpen[0] = 0;
            this->streamOpen[1] = 0;
            this->streamOpen[2] = 0;
            this->streamOpen[3] = 0;
            this->streamOpen[4] = 0;
            for (int i = 0; i < 32; ++i) {
                this->sample[i] = AIL_allocate_sample_handle(this->digSndDriver_0x4);
                this->sampleSoundIndex_0x20c[i] = 0;
            }
            this->loadedSoundsCountAndIndex_0x316c = 1;
            for (int i = 0; i < 1000; ++i) {
                this->soundFileCurrSampleNum_0x28c[i] = -1;
            }
            this->musicVolumeScalePercent = 100;
            this->musicFadeState = 0;
            this->musicSample = AIL_allocate_sample_handle(this->digSndDriver_0x4);
            this->musicSampleBufferSize
                = AIL_minimum_sample_buffer_size(this->digSndDriver_0x4, 22050, DIG_F_STEREO_16);
            if (this->musicSampleBufferSize < 0x10000) {
                this->musicSampleBufferSize = 0x10000;
            }
            this->musicSampleBuffers[0] = AIL_mem_alloc_lock(this->musicSampleBufferSize);
            this->musicSampleBuffers[1] = AIL_mem_alloc_lock(this->musicSampleBufferSize);
            this->currentMusicFileHandle = -1;
            this->queuedMusicFileHandle = -1;
            this->pendingMusicId = -1;
            this->playingMusicId = 0;
            this->peaceMusicPauseStartTime = 0;

            timecaps_tag _timeCaps;
            MMRESULT const _err = timeGetDevCaps(&_timeCaps, sizeof(timecaps_tag));
            if (_err != MMSYSERR_NOERROR) {
                return;
            }
            unsigned int const uPeriod = min(max(_timeCaps.wPeriodMin, 10), _timeCaps.wPeriodMax);
            DAT_SoundEffectsHelperData1::instance.SND_SomeTimerResolution = uPeriod;
            timeBeginPeriod(uPeriod);
            DAT_SFXDefinedData::instance.SomeTimerIdentifier
                = timeSetEvent(50, uPeriod, MSS_Func::SndSystemTimeCallback::get(), 0, 0x1);
        }

    }
}
}
