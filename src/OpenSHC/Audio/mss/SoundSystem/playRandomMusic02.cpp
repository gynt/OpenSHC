#include "../SoundSystem.func.hpp"

#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SoundEffectsHelperData1.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x0047AB10
        void SoundSystem::playRandomMusic02(int param_1)
        {
            if (DAT_SoundEffectsHelperData1::ptr->SEC_Section1079.musicMode == 5) {
                return;
            }
            DAT_SoundEffectsHelperData1::ptr->SEC_Section1079.battleMusicVariant = 2;
            DAT_SoundEffectsHelperData1::ptr->SEC_Section1079.battleSegmentCounter = 0;
            DAT_SoundEffectsHelperData1::ptr->SEC_Section1079.musicMode = 5;
            DAT_SoundEffectsHelperData1::ptr->SEC_Section1079.battleEndTransitionDone = 0;
            DAT_SoundEffectsHelperData1::ptr->SEC_Section1079.troopValueLevel = param_1;
            DAT_SoundEffectsHelperData1::ptr->DAT_SomeSoundTime2 = timeGetTime();

            if (param_1 != 2) {
                if (DAT_TroopValueState::ptr->attackInfo.attackWaveMusicPending == 0) {
                    MACRO_CALL_MEMBER(
                        Map::Units::TroopValueState_Func::recountTotalTroopValue, DAT_TroopValueState::ptr)();
                }
                int const currentPlayerTotalTroopValue
                    = DAT_TroopValueState::ptr->attackInfo
                          .playerTotalTroopValueArray[DAT_GameSynchronyState::ptr->currentPlayerSlotID];
                DAT_SoundEffectsHelperData1::ptr->musicOwnTroopValueAtBattleStart = currentPlayerTotalTroopValue;
                DAT_SoundEffectsHelperData1::ptr->musicOwnTroopValue = currentPlayerTotalTroopValue;

                DAT_SoundEffectsHelperData1::ptr->enemyTotalTroopValue = 0;
                for (int i = 1; i < 9; ++i) {
                    if (DAT_GameSynchronyState::ptr->currentPlayerSlotID == i) {
                        continue;
                    }
                    DAT_SoundEffectsHelperData1::ptr->enemyTotalTroopValue
                        += DAT_TroopValueState::ptr->attackInfo.playerTotalTroopValueArray[i];
                }

                DAT_SoundEffectsHelperData1::ptr->musicEnemyTroopValue
                    = DAT_SoundEffectsHelperData1::ptr->enemyTotalTroopValue;
                DAT_SoundEffectsHelperData1::ptr->battleMoodTrend = 0;
                if (DAT_SoundEffectsHelperData1::ptr->enemyTotalTroopValue < 100) {
                    param_1 = 0;
                    DAT_SoundEffectsHelperData1::ptr->SEC_Section1079.troopValueLevel = 0;
                    DAT_SoundEffectsHelperData1::ptr->SEC_Section1079.battleMusicVariant
                        = DAT_SoundEffectsHelperData1::ptr->SEC_Section1079.incrementorUpTo4;
                } else if (DAT_SoundEffectsHelperData1::ptr->enemyTotalTroopValue < 250) {
                    if ((DAT_SoundEffectsHelperData1::ptr->SEC_Section1079.incrementorUpTo4 == 1)
                        || (DAT_SoundEffectsHelperData1::ptr->SEC_Section1079.incrementorUpTo4 == 3)) {
                        param_1 = 0;
                        DAT_SoundEffectsHelperData1::ptr->SEC_Section1079.troopValueLevel = 0;
                        DAT_SoundEffectsHelperData1::ptr->SEC_Section1079.battleMusicVariant = 5;
                    } else {
                        param_1 = 1;
                        DAT_SoundEffectsHelperData1::ptr->SEC_Section1079.troopValueLevel = 1;
                        DAT_SoundEffectsHelperData1::ptr->SEC_Section1079.battleMusicVariant = 1;
                    }
                } else {
                    param_1 = 1;
                    DAT_SoundEffectsHelperData1::ptr->SEC_Section1079.troopValueLevel = 1;
                    DAT_SoundEffectsHelperData1::ptr->SEC_Section1079.battleMusicVariant = 2;
                }
            } else {
                int iVar1 = 3;
                if (DAT_GameSynchronyState::ptr->currentGameMode != Game::GM_SOLITARY) {
                    iVar1 = SEC_RNG::ptr->currentNumber1 % 5;
                }
                if ((iVar1 == 0) || (iVar1 == 1)) {
                    param_1 = 0;
                    DAT_SoundEffectsHelperData1::ptr->SEC_Section1079.troopValueLevel = 0;
                    DAT_SoundEffectsHelperData1::ptr->SEC_Section1079.battleMusicVariant = (iVar1 + 1);
                }
                if (iVar1 == 2) {
                    MACRO_CALL_MEMBER(SoundSystem_Func::setupVolumeAndSoundID, this)(DE::SHCDE::MUSIC_TUNE_BATTLE_L1A);
                    DAT_SoundEffectsHelperData1::ptr->SEC_Section1079.battleMusicVariant = 1;
                } else if (iVar1 >= 3) {
                    MACRO_CALL_MEMBER(
                        Map::Units::TroopValueState_Func::recountTotalTroopValue, DAT_TroopValueState::ptr)();
                    int const currentPlayerTotalTroopValue
                        = DAT_TroopValueState::ptr->attackInfo
                              .playerTotalTroopValueArray[DAT_GameSynchronyState::ptr->currentPlayerSlotID];
                    DAT_SoundEffectsHelperData1::ptr->musicOwnTroopValueAtBattleStart = currentPlayerTotalTroopValue;
                    DAT_SoundEffectsHelperData1::ptr->musicOwnTroopValue = currentPlayerTotalTroopValue;

                    DAT_SoundEffectsHelperData1::ptr->enemyTotalTroopValue = 0;
                    for (int i = 1; i < 9; ++i) {
                        if (DAT_GameSynchronyState::ptr->currentPlayerSlotID == i) {
                            continue;
                        }
                        DAT_SoundEffectsHelperData1::ptr->enemyTotalTroopValue
                            += DAT_TroopValueState::ptr->attackInfo.playerTotalTroopValueArray[i];
                    }

                    DAT_SoundEffectsHelperData1::ptr->SEC_Section1079.battleMusicVariant = 2;
                    DAT_SoundEffectsHelperData1::ptr->musicEnemyTroopValue
                        = DAT_SoundEffectsHelperData1::ptr->enemyTotalTroopValue;
                    DAT_SoundEffectsHelperData1::ptr->battleMoodTrend = 0;
                    DAT_SoundEffectsHelperData1::ptr->SEC_Section1079.battleSegmentCounter = 1;
                }
            }

            ++DAT_SoundEffectsHelperData1::ptr->SEC_Section1079.incrementorUpTo4;
            if (4 < DAT_SoundEffectsHelperData1::ptr->SEC_Section1079.incrementorUpTo4) {
                DAT_SoundEffectsHelperData1::ptr->SEC_Section1079.incrementorUpTo4 = 1;
            }
            if (this->playingMusicId != 0) {
                MACRO_CALL_MEMBER(SoundSystem_Func::setSomeSoundTime, this)();
            }

            if (param_1 == 0) {
                switch (DAT_SoundEffectsHelperData1::ptr->SEC_Section1079.battleMusicVariant) {
                case 1:
                    MACRO_CALL_MEMBER(SoundSystem_Func::setupVolumeAndSoundID, this)(DE::SHCDE::MUSIC_TUNE_BATTLE1A);
                    return;
                case 2:
                    MACRO_CALL_MEMBER(SoundSystem_Func::setupVolumeAndSoundID, this)(DE::SHCDE::MUSIC_TUNE_BATTLE2A);
                    return;
                case 3:
                case 4:
                    MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber1, SEC_RNG::ptr)();
                    switch (SEC_RNG::ptr->currentNumber1 % 3) {
                    case 0:
                        MACRO_CALL_MEMBER(SoundSystem_Func::setupVolumeAndSoundID, this)(DE::SHCDE::MUSIC_TUNE_BATTLE3);
                        return;
                    case 1:
                        MACRO_CALL_MEMBER(SoundSystem_Func::setupVolumeAndSoundID, this)(DE::SHCDE::MUSIC_TUNE_BATTLE4);
                        return;
                    default:
                        MACRO_CALL_MEMBER(SoundSystem_Func::setupVolumeAndSoundID, this)(DE::SHCDE::MUSIC_TUNE_BATTLE);
                        return;
                    }
                default:
                    MACRO_CALL_MEMBER(SoundSystem_Func::setupVolumeAndSoundID, this)(DE::SHCDE::MUSIC_TUNE_BATTLE2A);
                    return;
                }
            } else if (param_1 == 2) {
                MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber1, SEC_RNG::ptr)();
                if (DAT_GameSynchronyState::ptr->currentGameMode != Game::GM_SOLITARY) {
                    MACRO_CALL_MEMBER(SoundSystem_Func::endSoundStream, this)(enums::SND_STR_MUSIC);
                    this->musicFadeState = 0;
                    this->playingMusicId = 0;
                    if (DAT_SoundEffectsHelperData1::ptr->SEC_Section1079.battleMusicVariant != 1) {
                        DAT_SoundEffectsHelperData1::ptr->SEC_Section1079.battleSegmentCounter = 1;
                        MACRO_CALL_MEMBER(SoundSystem_Func::setupVolumeAndSoundID, this)(
                            DE::SHCDE::MUSIC_TUNE_BATTLE_L2_GLORY1);
                    }
                } else if (SEC_RNG::ptr->currentNumber1 % 3 == 0) {
                    MACRO_CALL_MEMBER(SoundSystem_Func::setupVolumeAndSoundID, this)(DE::SHCDE::MUSIC_TUNE_BATTLE_L1A);
                    DAT_SoundEffectsHelperData1::ptr->SEC_Section1079.battleMusicVariant = 1;

                } else {
                    DAT_SoundEffectsHelperData1::ptr->SEC_Section1079.battleSegmentCounter = 1;
                    MACRO_CALL_MEMBER(SoundSystem_Func::endSoundStream, this)(enums::SND_STR_MUSIC);
                    this->musicFadeState = 0;
                    this->playingMusicId = 0;
                    DAT_SoundEffectsHelperData1::ptr->SEC_Section1079.battleMusicVariant = 2;
                    MACRO_CALL_MEMBER(SoundSystem_Func::setupVolumeAndSoundID, this)(
                        DE::SHCDE::MUSIC_TUNE_BATTLE_L2_GLORY1);
                }
                MACRO_CALL_MEMBER(SoundSystem_Func::requestFadeInForNextTrack, this)();
            } else {
                switch (DAT_SoundEffectsHelperData1::ptr->SEC_Section1079.battleMusicVariant) {
                case 1:
                    MACRO_CALL_MEMBER(SoundSystem_Func::setupVolumeAndSoundID, this)(DE::SHCDE::MUSIC_TUNE_BATTLE_L1A);
                    return;
                case 2:
                    MACRO_CALL_MEMBER(SoundSystem_Func::setupVolumeAndSoundID, this)(DE::SHCDE::MUSIC_TUNE_BATTLE2B);
                    MACRO_CALL_MEMBER(SoundSystem_Func::requestFadeInForNextTrack, this)();
                    return;
                default:
                    return;
                }
            }
        }

    }
}
}
