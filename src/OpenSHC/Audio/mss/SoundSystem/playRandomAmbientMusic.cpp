#include "../SoundSystem.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXDefinedData.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_SoundEffectsHelperData1.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x0047B890
        void SoundSystem::updateMusic()
        {
            if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY
                && MACRO_CALL_MEMBER(Game::GameCore_Func::isInGameView, DAT_GameCore::ptr)()
                && DAT_GameCore::instance.currentMenuViewType != UI::Enums::MVT_MAP_EDITOR_LANDSCAPING) {
                if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .campground.id
                        <= 0
                    || DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .lordID
                        <= 0) {
                    DAT_TroopValueState::instance.attackInfo.enemyUnitsOnKeepCount = 0;
                } else {
                    if (0 < DAT_TroopValueState::instance.attackInfo.buildingDamageEventCount
                        && DAT_TroopValueState::instance.attackInfo.breachWarningGate == 1) {
                        DAT_TroopValueState::instance.attackInfo.breachWarningGate = 2;
                        /* "the enemy has breached the walls!" */
                        MACRO_CALL_MEMBER(SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                            s_General_Warning15_wav_005a6ce4);
                    }
                    if (DAT_TroopValueState::instance.attackInfo.enemyUnitsOnKeepCount != 0) {
                        DAT_TroopValueState::instance.attackInfo.enemyUnitsOnKeepCount = 0;
                        if (90000 < timeGetTime()
                                - DAT_SoundEffectsHelperData1::instance
                                    .DAT_enemyInsideCastleSoundWarningCooldownTimer) {
                            /* the enemy are inside the castle! */
                            MACRO_CALL_MEMBER(SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                                s_General_Warning4_wav_005a6ccc);
                            DAT_SoundEffectsHelperData1::instance.DAT_enemyInsideCastleSoundWarningCooldownTimer
                                = timeGetTime();
                        }
                    }
                }
            }
            if (200 < DAT_GameCore::instance.mapTimeInTicks - DAT_GameCore::instance.someSoundMatchTime_1) {
                DAT_GameCore::instance.battleLevel = DAT_GameCore::instance.battleLevelAccumulator;
                DAT_GameCore::instance.someSoundMatchTime_1 = DAT_GameCore::instance.mapTimeInTicks;
                DAT_GameCore::instance.battleLevelAccumulator = 0;
            }
            if (0 < this->playingMusicId && this->musicFadeState != 0) {
                if (this->musicFadeState == 2) {
                    unsigned int const transitionPercent = (timeGetTime() - this->musicFadeStartTime) / 10;
                    if (transitionPercent >= 100) {
                        MACRO_CALL_MEMBER(SoundSystem_Func::stopMusicPlayback, this)();
                        this->playingMusicId = 0;
                        this->musicFadeState = 0;
                    } else {
                        MACRO_CALL_MEMBER(SoundSystem_Func::setStreamFileVolume, this)(enums::SND_STR_MUSIC,
                            ((100 - transitionPercent) * this->streamUnduckedFileVolume[0]) / 100);
                        return;
                    }
                }
                if (this->musicFadeState == 1) {
                    unsigned int const transitionPercent = (timeGetTime() - this->musicFadeStartTime) / 200;
                    if (transitionPercent >= 100) {
                        MACRO_CALL_MEMBER(SoundSystem_Func::setStreamFileVolume, this)(
                            enums::SND_STR_MUSIC, (100 * this->streamUnduckedFileVolume[0]) / 100);
                        this->musicFadeState = 0;
                    } else {
                        MACRO_CALL_MEMBER(SoundSystem_Func::setStreamFileVolume, this)(
                            enums::SND_STR_MUSIC, (transitionPercent * this->streamUnduckedFileVolume[0]) / 100);
                        return;
                    }
                }
            }
            if (this->pendingMusicId != this->playingMusicId && 0 < this->pendingMusicId) {
                if (this->fadeInNextTrack == 1) {
                    this->musicFadeState = 1;
                    this->musicFadeStartTime = timeGetTime();
                    this->fadeInNextTrack = 0;
                }
                if (DAT_SFXDefinedData::instance.Pointers[this->pendingMusicId].unknownFlag_0x4) {
                    MACRO_CALL_MEMBER(SoundSystem_Func::playMusicFileByNameWithVolume, this)(
                        DAT_SFXDefinedData::instance.Pointers[this->pendingMusicId].musicFile,
                        this->pendingMusicVolume);
                    this->playingMusicId = this->pendingMusicId;
                } else {
                    MACRO_CALL_MEMBER(SoundSystem_Func::playMusicOnceWithVolume, this)(
                        DAT_SFXDefinedData::instance.Pointers[this->pendingMusicId].musicFile,
                        this->pendingMusicVolume);
                    this->playingMusicId = this->pendingMusicId;
                    this->pendingMusicId = 0;
                }
            }

            if ((MACRO_CALL_MEMBER(Game::GameCore_Func::isInGameView, DAT_GameCore::ptr)()
                    || (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_SCENARIO_DESCRIPTION
                        && DAT_GameCore::instance.briefingOpenedFromInGame != 0))
                && DAT_GameCore::instance.gameMode_2 != Game::GM_CRUSADER_TUTORIAL
                && DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY) {
                if (DAT_TroopValueState::instance.attackInfo.attackWaveMusicPending != 0
                    && 0 < DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .totalEnemyUnitsCount) {
                    if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.siegeAttackerMusicMode) {
                        MACRO_CALL_MEMBER(SoundSystem_Func::playRandomMusic02, this)(2);
                    } else {
                        MACRO_CALL_MEMBER(SoundSystem_Func::playRandomMusic02, this)(1);
                    }
                    DAT_TroopValueState::instance.attackInfo.attackWaveMusicPending = 0;
                }
                if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicMode == 5) {
                    if ((DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                .totalEnemyUnitsCount
                            == 0)
                        && (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.siegeAttackerMusicMode == 0)) {
                        MACRO_CALL_MEMBER(
                            SoundSystem_Func::handleBattleEndMusicTransition, DAT_SoundSystemState::ptr)();
                    }
                    if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.troopValueLevel != 0
                        && DAT_SoundEffectsHelperData1::instance.SEC_Section1079.battleMusicVariant == 2
                        && 30000 < timeGetTime() - DAT_SoundEffectsHelperData1::instance.DAT_SomeSoundTime2) {
                        DAT_SoundEffectsHelperData1::instance.DAT_SomeSoundTime2 = timeGetTime();
                        MACRO_CALL_MEMBER(
                            Map::Units::TroopValueState_Func::recountTotalTroopValue, DAT_TroopValueState::ptr)();

                        int const currentPlayerTotalTroopValue
                            = DAT_TroopValueState::instance.attackInfo
                                  .playerTotalTroopValueArray[DAT_GameSynchronyState::instance.currentPlayerSlotID];

                        int enemyPlayerTotalTroopValue = 0;
                        for (int i = 1; i < 9; ++i) {
                            if (DAT_GameSynchronyState::instance.currentPlayerSlotID == i) {
                                continue;
                            }
                            enemyPlayerTotalTroopValue
                                += DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[i];
                        }

                        if (DAT_SoundEffectsHelperData1::instance.musicOwnTroopValueAtBattleStart < 1) {
                            DAT_SoundEffectsHelperData1::instance.musicOwnTroopValueAtBattleStart = 1;
                        }
                        int somePercentage1
                            = (currentPlayerTotalTroopValue * 100) / DAT_SoundEffectsHelperData1::instance.musicOwnTroopValueAtBattleStart;
                        if (100 < somePercentage1) {
                            somePercentage1 = 100;
                        }
                        DAT_SoundEffectsHelperData1::instance.musicOwnTroopValue = currentPlayerTotalTroopValue;

                        if (DAT_SoundEffectsHelperData1::instance.enemyTotalTroopValue < 1) {
                            DAT_SoundEffectsHelperData1::instance.enemyTotalTroopValue = 1;
                        }
                        int somePercentage2 = (enemyPlayerTotalTroopValue * 100)
                            / DAT_SoundEffectsHelperData1::instance.enemyTotalTroopValue;
                        if (100 < somePercentage2) {
                            somePercentage2 = 100;
                        }
                        DAT_SoundEffectsHelperData1::instance.musicEnemyTroopValue = enemyPlayerTotalTroopValue;

                        int const someValue = somePercentage1 - somePercentage2;
                        if (someValue > 20) {
                            DAT_SoundEffectsHelperData1::instance.battleMoodTrend = 1;
                        } else if (someValue < -20) {
                            DAT_SoundEffectsHelperData1::instance.battleMoodTrend = 2;
                        } else {
                            DAT_SoundEffectsHelperData1::instance.battleMoodTrend = 0;
                        }
                    }
                    if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicMode == 5) {
                        return;
                    }
                }
                if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.siegeAttackerMusicMode != 0) {
                    MACRO_CALL_MEMBER(SoundSystem_Func::playRandomMusic02, this)(2);
                } else if (0
                        < DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .totalEnemyUnitsCount
                    && DAT_TroopValueState::instance.attackInfo.attackForceTooWeak == 0) {
                    MACRO_CALL_MEMBER(SoundSystem_Func::playRandomMusic02, this)(1);
                    MACRO_CALL_MEMBER(SoundSystem_Func::playBattleGloryMusicIfConditionsMet, this)();
                }

                if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicMode == 5) {
                    return;
                }

                if (this->playingMusicId != 0) {
                    if (!MACRO_CALL_MEMBER(SoundSystem_Func::isSampleOrStreamPlaying, this)(enums::SND_STR_MUSIC)) {
                        if (9 < this->playingMusicId) {
                            this->peaceMusicPauseStartTime = timeGetTime();
                        }
                        this->playingMusicId = 0;
                        this->pendingMusicId = 0;
                    }
                    if (this->playingMusicId != 0) {
                        return;
                    }
                }
                if (this->peaceMusicPauseStartTime == 0) {
                    this->peaceMusicPauseStartTime = timeGetTime();
                }
                if (this->playingMusicId != 0) {
                    return;
                }

                if (timeGetTime() - this->peaceMusicPauseStartTime
                    <= DAT_SFXDefinedData::instance.musicSilenceIntervalsMs[DAT_SoundEffectsHelperData1::instance.musicSilenceIntervalIndex]) {
                    return;
                }

                ++DAT_SoundEffectsHelperData1::instance.musicSilenceIntervalIndex;
                if (DAT_SoundEffectsHelperData1::instance.musicSilenceIntervalIndex >= 6) {
                    DAT_SoundEffectsHelperData1::instance.musicSilenceIntervalIndex = 0;
                }
                MACRO_CALL_MEMBER(SoundSystem_Func::selectAndPlayMoodBasedMusic, this)();
            } else {
                if (!MACRO_CALL_MEMBER(Game::GameCore_Func::isInGameView, DAT_GameCore::ptr)()) {
                    return;
                }
                if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY) {
                    return;
                }

                int const battleLevelTemp = DAT_GameCore::instance.battleLevel2 + 2500;
                int const iVar7 = DAT_GameCore::instance.battleLevel2;
                if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicMode != 5) {
                    if (0 < DAT_GameCore::instance.battleLevel2) {
                        --DAT_GameCore::instance.battleLevel2;
                    }
                    if (DAT_GameCore::instance.battleLevel >= battleLevelTemp) {
                        MACRO_CALL_MEMBER(SoundSystem_Func::playRandomMusic02, this)(2);
                        DAT_GameCore::instance.battleLevel2 = 0;
                    }
                } else {
                    if (DAT_GameCore::instance.battleLevel2 < 50000) {
                        DAT_GameCore::instance.battleLevel2 = DAT_GameCore::instance.battleLevel2 + 1;
                    }
                }
                if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicMode == 5) {
                    if (DAT_GameCore::instance.battleLevel < iVar7) {
                        MACRO_CALL_MEMBER(
                            SoundSystem_Func::handleBattleEndMusicTransition, DAT_SoundSystemState::ptr)();
                    }
                    if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.troopValueLevel != 0
                        && DAT_SoundEffectsHelperData1::instance.SEC_Section1079.battleMusicVariant == 2
                        && 30000 < timeGetTime() - DAT_SoundEffectsHelperData1::instance.DAT_SomeSoundTime2) {
                        MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber1, SEC_RNG::ptr)();
                        int const randomNumber = SEC_RNG::instance.currentNumber1 % 3;
                        if (randomNumber == 0)
                            DAT_SoundEffectsHelperData1::instance.battleMoodTrend = 1;
                        else if (randomNumber == 1)
                            DAT_SoundEffectsHelperData1::instance.battleMoodTrend = 2;
                        else
                            DAT_SoundEffectsHelperData1::instance.battleMoodTrend = 0;
                    }
                }

                if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicMode == 5) {
                    return;
                }

                if (this->playingMusicId != 0) {
                    if (!MACRO_CALL_MEMBER(SoundSystem_Func::isSampleOrStreamPlaying, this)(enums::SND_STR_MUSIC)) {
                        if (9 < this->playingMusicId) {
                            this->peaceMusicPauseStartTime = timeGetTime();
                        }
                        this->playingMusicId = 0;
                        this->pendingMusicId = 0;
                    }
                    if (this->playingMusicId != 0) {
                        return;
                    }
                }
                if (this->peaceMusicPauseStartTime == 0) {
                    this->peaceMusicPauseStartTime = timeGetTime();
                }
                if (this->playingMusicId != 0) {
                    return;
                }

                if (timeGetTime() - this->peaceMusicPauseStartTime
                    <= DAT_SFXDefinedData::instance.musicSilenceIntervalsMs[DAT_SoundEffectsHelperData1::instance.musicSilenceIntervalIndex]) {
                    return;
                }

                ++DAT_SoundEffectsHelperData1::instance.musicSilenceIntervalIndex;
                if (DAT_SoundEffectsHelperData1::instance.musicSilenceIntervalIndex >= 6) {
                    DAT_SoundEffectsHelperData1::instance.musicSilenceIntervalIndex = 0;
                }
                MACRO_CALL_MEMBER(SoundSystem_Func::selectAndPlayMoodBasedMusic, this)();
            }
        }

    }
}
}
