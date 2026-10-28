#include "../SoundSystem.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Audio/mss/SoundFlagsAndLoopCountBitwiseFlagEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_SFXDefinedData.hpp"
#include "OpenSHC/Globals/DAT_SoundEffectsHelperData1.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x0047A790
        void SoundSystem::refillMusicStreamBuffer()
        {
            if (!this->soundSystemInitialized) {
                return;
            }
            if (!this->digSndDriver_0x4) {
                return;
            }

            int const _buffNum = AIL_sample_buffer_ready(this->musicSample);
            if (_buffNum == -1) {
                return;
            }

            int readFileBytes = MACRO_CALL(OS_Func::_ucrt_read)(this->currentMusicFileHandle,
                this->musicSampleBuffers[_buffNum], this->musicSampleBufferSize);

            // if the buffer is not completely filled, it seems to go through potential options to fill it
            if (this->musicSampleBufferSize != readFileBytes) {
                MACRO_CALL_MEMBER(SoundSystem_Func::queueNextBattleMusicSegment, this)();

                if (DAT_GameCore::ptr->currentMenuViewType == UI::Enums::MVT_HISTORIC_MISSION_PICTURE
                    || DAT_GameCore::ptr->currentMenuViewType == UI::Enums::MVT_HISTORIC_MISSION_INTRO
                    || DAT_GameCore::ptr->currentMenuViewType == UI::Enums::MVT_SCENARIO_DESCRIPTION) {
                    if (this->playingMusicId == 50) {
                        MACRO_CALL_MEMBER(SoundSystem_Func::openSound, this)(
                            DAT_SFXDefinedData::ptr->Pointers[72].musicFile);
                    } else if (this->playingMusicId == 72) {
                        MACRO_CALL_MEMBER(SoundSystem_Func::openSound, this)(
                            DAT_SFXDefinedData::ptr->Pointers[50].musicFile);
                    }
                }

                if (DAT_GameCore::ptr->currentMenuViewType == UI::Enums::MVT_CREDITS) {
                    MACRO_CALL_MEMBER(SoundSystem_Func::playDarMehqOrGlory, this)();
                }

                if (this->playingMusicId >= 73) {
                    if (this->playingMusicId >= 97) {
                        if (0 < DAT_SoundEffectsHelperData1::ptr->fluteFollowUpTracksRemaining) {
                            int _selection;
                            for (int i = 0; i < 16; ++i) {
                                /* this call is in a different thread! */
                                MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber1, SEC_RNG::ptr)();
                                _selection = SEC_RNG::ptr->currentNumber1 % 19;
                                if (_selection
                                    != DAT_SoundEffectsHelperData1::ptr->DAT_RandomVariationCurrentPlayingMusic_02)
                                    break;
                            }
                            DAT_SoundEffectsHelperData1::ptr->DAT_RandomVariationCurrentPlayingMusic_02 = _selection;
                            MACRO_CALL_MEMBER(SoundSystem_Func::openSound, this)(
                                DAT_SFXDefinedData::ptr->Pointers[_selection + 97].musicFile);
                            --DAT_SoundEffectsHelperData1::ptr->fluteFollowUpTracksRemaining;
                            if (DAT_SoundEffectsHelperData1::ptr->fluteFollowUpTracksRemaining > 3) {
                                DAT_SoundEffectsHelperData1::ptr->fluteFollowUpTracksRemaining = 0;
                            }
                        }
                    } else {
                        if (0 < DAT_SoundEffectsHelperData1::ptr->oudFollowUpTracksLeft) {
                            int _selection;
                            for (int i = 0; i < 16; ++i) {
                                MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber1, SEC_RNG::ptr)();
                                _selection = SEC_RNG::ptr->currentNumber1 % 24;
                                if (_selection
                                    != DAT_SoundEffectsHelperData1::ptr->DAT_RandomVariationCurrentPlayingMusic_01)
                                    break;
                            }
                            DAT_SoundEffectsHelperData1::ptr->DAT_RandomVariationCurrentPlayingMusic_01 = _selection;
                            MACRO_CALL_MEMBER(SoundSystem_Func::openSound, this)(
                                DAT_SFXDefinedData::ptr->Pointers[_selection + 73].musicFile);
                            DAT_SoundEffectsHelperData1::ptr->oudFollowUpTracksLeft += -1;
                            if (DAT_SoundEffectsHelperData1::ptr->oudFollowUpTracksLeft > 3) {
                                DAT_SoundEffectsHelperData1::ptr->oudFollowUpTracksLeft = 0;
                            }
                        }
                    }
                }

                if (this->queuedMusicFileHandle != -1) {
                    MACRO_CALL(OS_Func::_ucrt_close)(this->currentMusicFileHandle);
                    this->currentMusicFileHandle = this->queuedMusicFileHandle;
                    this->queuedMusicFileHandle = -1;
                    readFileBytes += MACRO_CALL(OS_Func::_ucrt_read)(this->currentMusicFileHandle,
                        (void*)((int)this->musicSampleBuffers[_buffNum] + readFileBytes),
                        this->musicSampleBufferSize - readFileBytes);
                } else if ((this->streamFlagsAndLoopCount[0] & FLAG_SOUND_LOOP_COUNT_FIELD) == 1) {
                    MACRO_CALL_MEMBER(SoundSystem_Func::stopMusicPlayback, this)();
                    return;
                } else if ((this->streamFlagsAndLoopCount[0] & FLAG_SOUND_LOOP_COUNT_FIELD) == 0) {
                    MACRO_CALL(OS_Func::_ucrt_lseek)(this->currentMusicFileHandle, 0, FILE_BEGIN);
                    readFileBytes += MACRO_CALL(OS_Func::_ucrt_read)(this->currentMusicFileHandle,
                        (void*)((int)this->musicSampleBuffers[_buffNum] + readFileBytes),
                        this->musicSampleBufferSize - readFileBytes);
                }
            }
            AIL_load_sample_buffer(
                this->musicSample, _buffNum, this->musicSampleBuffers[_buffNum], readFileBytes);
        }

    }
}
}
