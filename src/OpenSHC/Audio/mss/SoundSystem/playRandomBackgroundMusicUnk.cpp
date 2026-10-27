#include "../SoundSystem.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Audio/mss/SoundFlagsAndLoopCountBitwiseFlagEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXDefinedData.hpp"
#include "OpenSHC/Globals/DAT_SoundEffectsHelperData1.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x0047BF20
        void SoundSystem::queueNextBattleMusicSegment()
        {
            if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicMode != 5) {
                return;
            }

            // NOTE: Current state has a mismatch with the bytes of this condition: The following early return is
            //   directly placed under it. So resolve this, one can move the first early return inside this if as or,
            //   which will produce the proper code for this position, but messes with the rest of the function in such
            //   a way that is produces a lower match. Due to the amount of time already spend, the function is kept in
            //   this state and maybe one day tackled again when the last once are cleaned up.
            if (!MACRO_CALL_MEMBER(Game::GameCore_Func::isInGameView, DAT_GameCore::ptr)()
                && (DAT_GameCore::instance.currentMenuViewType != UI::Enums::MVT_SCENARIO_DESCRIPTION
                    || !DAT_GameCore::instance.briefingOpenedFromInGame)) {
                if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicMode == 5) {
                    DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicMode = 1;
                }
                return;
            }

            int bVar7 = true;
            if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.troopValueLevel == 0) {
                switch (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.battleMusicVariant) {
                case 1:
                    if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.battleSegmentCounter == 0) {
                        DAT_SoundEffectsHelperData1::instance.SEC_Section1079.battleSegmentCounter = 1;
                        MACRO_CALL_MEMBER(SoundSystem_Func::openSound, this)(
                            DAT_SFXDefinedData::instance.Pointers[23].musicFile);
                    } else {
                        MACRO_CALL_MEMBER(SoundSystem_Func::openSound, this)(
                            DAT_SFXDefinedData::instance.Pointers[23].musicFile);
                        if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY) {
                            DAT_GameCore::instance.battleLevel2 += 2000;
                        }
                    }
                    if ((this->streamFlagsAndLoopCount[0] & FLAG_SOUND_LOOP_COUNT_FIELD) == 0) {
                        ++this->streamFlagsAndLoopCount[0];
                    }
                    return;

                case 2:
                    if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.battleSegmentCounter == 0) {
                        DAT_SoundEffectsHelperData1::instance.SEC_Section1079.battleSegmentCounter = 1;
                        MACRO_CALL_MEMBER(SoundSystem_Func::openSound, this)(
                            DAT_SFXDefinedData::instance.Pointers[25].musicFile);
                    } else {
                        MACRO_CALL_MEMBER(SoundSystem_Func::openSound, this)(
                            DAT_SFXDefinedData::instance.Pointers[25].musicFile);
                        if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY) {
                            DAT_GameCore::instance.battleLevel2 += 2000;
                        }
                    }
                    if ((this->streamFlagsAndLoopCount[0] & FLAG_SOUND_LOOP_COUNT_FIELD) == 0) {
                        ++this->streamFlagsAndLoopCount[0];
                    }
                    return;

                case 5:
                    ++DAT_SoundEffectsHelperData1::instance.SEC_Section1079.battleSegmentCounter;
                    if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.battleSegmentCounter > 2) {
                        DAT_SoundEffectsHelperData1::instance.SEC_Section1079.battleSegmentCounter = 1;
                        if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY) {
                            DAT_GameCore::instance.battleLevel2 += 2000;
                        }
                    }
                    if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.battleSegmentCounter == 1) {
                        MACRO_CALL_MEMBER(SoundSystem_Func::openSound, this)(
                            DAT_SFXDefinedData::instance.Pointers[25].musicFile);
                        if ((this->streamFlagsAndLoopCount[0] & FLAG_SOUND_LOOP_COUNT_FIELD) == 0) {
                            ++this->streamFlagsAndLoopCount[0];
                        }
                    } else {
                        MACRO_CALL_MEMBER(SoundSystem_Func::openSound, this)(
                            DAT_SFXDefinedData::instance.Pointers[27].musicFile);
                        if ((this->streamFlagsAndLoopCount[0] & FLAG_SOUND_LOOP_COUNT_FIELD) == 0) {
                            ++this->streamFlagsAndLoopCount[0];
                        }
                    }
                    return;
                }
            } else if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.battleMusicVariant == 1) {
                if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.battleEndTransitionDone == 0) {
                    if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.battleSegmentCounter == 0) {
                        MACRO_CALL_MEMBER(SoundSystem_Func::openSound, this)(
                            DAT_SFXDefinedData::instance.Pointers[30].musicFile);
                    } else if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.battleSegmentCounter == 1) {
                        MACRO_CALL_MEMBER(SoundSystem_Func::openSound, this)(
                            DAT_SFXDefinedData::instance.Pointers[31].musicFile);
                    } else {
                        MACRO_CALL_MEMBER(SoundSystem_Func::openSound, this)(
                            DAT_SFXDefinedData::instance.Pointers[31].musicFile);
                        if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY) {
                            DAT_GameCore::instance.battleLevel2 += 5000;
                        }
                    }
                    ++DAT_SoundEffectsHelperData1::instance.SEC_Section1079.battleSegmentCounter;
                    if ((this->streamFlagsAndLoopCount[0] & FLAG_SOUND_LOOP_COUNT_FIELD) == 0) {
                        ++this->streamFlagsAndLoopCount[0];
                    }
                    return;
                }
                DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicMode = 1;
                bVar7 = false;
            } else {
                if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.battleEndTransitionDone == 0) {
                    if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.battleSegmentCounter == 0) {
                        if (this->playingMusicId != 25) {
                            MACRO_CALL_MEMBER(SoundSystem_Func::openSound, this)(
                                DAT_SFXDefinedData::instance.Pointers[25].musicFile);
                            if ((this->streamFlagsAndLoopCount[0] & FLAG_SOUND_LOOP_COUNT_FIELD) == 0) {
                                ++this->streamFlagsAndLoopCount[0];
                            }
                            return;
                        }
                    } else {
                        if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.battleSegmentCounter < 2) {
                            ++DAT_SoundEffectsHelperData1::instance.SEC_Section1079.battleSegmentCounter;
                            if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.battleSegmentCounter == 2) {
                                MACRO_CALL_MEMBER(SoundSystem_Func::openSound, this)(
                                    DAT_SFXDefinedData::instance.Pointers[34].musicFile);
                            }
                            DAT_SoundEffectsHelperData1::instance.currentBattleMusicId = 34;
                        } else {
                            int iVar5 = DAT_SoundEffectsHelperData1::instance.currentBattleMusicId + -34;
                            int iVar6 = 0;
                            if (iVar5 < 0 || 7 < iVar5) {
                                iVar5 = 0;
                            }

                            int aiStack_50[20];
                            for (int i = 0; i < 8; ++i) {
                                if (iVar5 == i || DAT_SFXDefinedData::instance.battleMusicSegmentTransitions[iVar5][i] == 0) {
                                    continue;
                                }
                                if (i == 4) {
                                    aiStack_50[iVar6++] = i;
                                    aiStack_50[iVar6++] = i;
                                    aiStack_50[iVar6++] = i;
                                    aiStack_50[iVar6++] = i;
                                    aiStack_50[iVar6++] = i;
                                    aiStack_50[iVar6++] = i;
                                    continue;
                                }
                                int iVar1 = DAT_SFXDefinedData::instance.battleMusicSegmentMoodTag[i];
                                int field6_0x34 = DAT_SoundEffectsHelperData1::instance.battleMoodTrend;
                                if ((iVar1 == 1 && iVar1 == field6_0x34) || (iVar1 == 2 && iVar1 == field6_0x34)) {
                                    continue;
                                }
                                aiStack_50[iVar6++] = i;
                                if (field6_0x34 == 1 && iVar1 == 2) {
                                    aiStack_50[iVar6++] = i;
                                } else if (field6_0x34 == 2 && iVar1 == 1) {
                                    aiStack_50[iVar6++] = i;
                                }
                            }

                            int sfxIndex;
                            if (iVar6 == 0) {
                                sfxIndex = iVar5 + 34;
                            } else {
                                MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber1, SEC_RNG::ptr)();
                                sfxIndex = aiStack_50[SEC_RNG::instance.currentNumber1 % iVar6] + 34;
                            }
                            MACRO_CALL_MEMBER(SoundSystem_Func::openSound, this)(
                                DAT_SFXDefinedData::instance.Pointers[sfxIndex].musicFile);
                            DAT_SoundEffectsHelperData1::instance.currentBattleMusicId = sfxIndex;
                        }
                        if ((this->streamFlagsAndLoopCount[0] & FLAG_SOUND_LOOP_COUNT_FIELD) == 0) {
                            ++this->streamFlagsAndLoopCount[0];
                        }
                        return;
                    }
                } else {
                    DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicMode = 1;
                    bVar7 = false;
                }
            }
            if (this->queuedMusicFileHandle != -1) {
                DAT_SoundEffectsHelperData1::instance.musicStreamBusyMainThread = TRUE;
                MACRO_CALL(OS_Func::_ucrt_close)(this->queuedMusicFileHandle);
                this->queuedMusicFileHandle = -1;
                DAT_SoundEffectsHelperData1::instance.musicStreamBusyMainThread = FALSE;
            }
            if (bVar7) {
                if ((this->streamFlagsAndLoopCount[0] & FLAG_SOUND_LOOP_COUNT_FIELD) == 1) {
                    this->streamFlagsAndLoopCount[0] &= ~FLAG_SOUND_LOOP_COUNT_FIELD;
                }
            } else {
                if ((this->streamFlagsAndLoopCount[0] & FLAG_SOUND_LOOP_COUNT_FIELD) == 0) {
                    ++this->streamFlagsAndLoopCount[0];
                }
            }
        }

    }
}
}
