#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/AI/Tribes/AITribeType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using namespace OpenSHC::AI::Tribes;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051FB90
        void TroopValueState::recountAttackTroopValue(int forceRecount)
        {
            if (forceRecount != 0) {
                DAT_TroopValueState::instance.attackInfo.counter = 16;
            }
            DAT_TroopValueState::instance.attackInfo.counter++;
            if (DAT_TroopValueState::instance.attackInfo.counter < 16) {
                return;
            }
            DAT_TroopValueState::instance.attackInfo.counter = 0;
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                sizeof(DAT_TroopValueState::instance.attackInfo.aiTribeSizesPerTribeType), 0,
                &DAT_TroopValueState::instance.attackInfo.aiTribeSizesPerTribeType);
            DAT_TroopValueState::instance.attackInfo.attackForceTooWeak = 0;
            DAT_TroopValueState::instance.attackInfo.size = 0;
            DAT_TroopValueState::instance.attackInfo.aiTroops = 0;
            DAT_TroopValueState::instance.attackInfo.fightingTribeCount = 0;
            DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen = 0;
            DAT_TroopValueState::instance.attackInfo.pikemenSwordsmenAndMore = 0;
            DAT_TroopValueState::instance.attackInfo.engineers = 0;
            DAT_TroopValueState::instance.attackInfo.laddermen = 0;
            DAT_TroopValueState::instance.attackInfo.slaveTribeCount = 0;
            DAT_TroopValueState::instance.attackInfo.catapults = 0;
            DAT_TroopValueState::instance.attackInfo.knights = 0;
            DAT_TroopValueState::instance.attackInfo.ranged = 0;
            // tribeType is read from the tribe at every comparison (a local copy moves the loop's base pointer)
            for (int tribeID = 1; tribeID < 1250; ++tribeID) {
                if (DAT_TribesState::instance.tribes[tribeID].tribeState == 0) {
                    continue;
                }
                if (MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::isPlayerSlotNotHuman,
                        DAT_GameState::ptr)(DAT_TribesState::instance.tribes[tribeID].owner)
                    == FALSE) {
                    if (DAT_TribesState::instance.tribes[tribeID].owner
                        == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                        DAT_TroopValueState::instance.attackInfo.size += DAT_TribesState::instance.tribes[tribeID].size;
                    }
                    continue;
                }
                int const tribeSize = DAT_TribesState::instance.tribes[tribeID].size;
                // aiTribeSizesPerTribeType is an int array indexed by AITribeType
                ((int*)&DAT_TroopValueState::instance.attackInfo
                        .aiTribeSizesPerTribeType)[DAT_TribesState::instance.tribes[tribeID].tribeType]
                    += tribeSize;
                if (DAT_TribesState::instance.tribes[tribeID].tribeType == AITT_ENGINEERS) {
                    DAT_TroopValueState::instance.attackInfo.engineers++;
                } else if (DAT_TribesState::instance.tribes[tribeID].tribeType == AITT_LADDERMEN) {
                    DAT_TroopValueState::instance.attackInfo.laddermen++;
                } else if (DAT_TribesState::instance.tribes[tribeID].tribeType == AITT_BATTERING_RAMS
                    || DAT_TribesState::instance.tribes[tribeID].tribeType == AITT_SIEGE_TOWERS
                    || DAT_TribesState::instance.tribes[tribeID].tribeType == AITT_PORTABLE_SHIELDS) {
                } else if (DAT_TribesState::instance.tribes[tribeID].tribeType == AITT_CATAPULTS) {
                    if (DAT_UnitsState::instance.units[DAT_TribesState::instance.tribes[tribeID].leaderUnitID]
                            .stoneAmmunition
                        > 0) {
                        DAT_TroopValueState::instance.attackInfo.catapults++;
                    }
                } else if (DAT_TribesState::instance.tribes[tribeID].tribeType == AITT_TREBUCHETS) {
                    if (DAT_UnitsState::instance.units[DAT_TribesState::instance.tribes[tribeID].leaderUnitID]
                            .stoneAmmunition
                        > 0) {
                        DAT_TroopValueState::instance.attackInfo.catapults++;
                    }
                } else if (DAT_TribesState::instance.tribes[tribeID].tribeType != AITT_TUNNELERS
                    && (DAT_TribesState::instance.tribes[tribeID].tribeType < AITT_DEER
                        || DAT_TribesState::instance.tribes[tribeID].tribeType >= AITT_ARAB_ARCHERS)) {
                    DAT_TroopValueState::instance.attackInfo.aiTroops += tribeSize;
                    DAT_TroopValueState::instance.attackInfo.fightingTribeCount++;
                    if (DAT_TribesState::instance.tribes[tribeID].tribeType == AITT_SPEARMEN) {
                        DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen++;
                    } else if (DAT_TribesState::instance.tribes[tribeID].tribeType == AITT_MACEMEN) {
                        DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen++;
                    } else if (DAT_TribesState::instance.tribes[tribeID].tribeType == AITT_SLAVES) {
                        DAT_TroopValueState::instance.attackInfo.slaveTribeCount++;
                    } else if (DAT_TribesState::instance.tribes[tribeID].tribeType == AITT_PIKEMEN) {
                        DAT_TroopValueState::instance.attackInfo.pikemenSwordsmenAndMore++;
                    } else if (DAT_TribesState::instance.tribes[tribeID].tribeType == AITT_SWORDSMEN) {
                        DAT_TroopValueState::instance.attackInfo.pikemenSwordsmenAndMore++;
                    } else if (DAT_TribesState::instance.tribes[tribeID].tribeType == AITT_ARAB_SWORDSMEN) {
                        DAT_TroopValueState::instance.attackInfo.pikemenSwordsmenAndMore++;
                    } else if (DAT_TribesState::instance.tribes[tribeID].tribeType == AITT_ASSASSINS) {
                        DAT_TroopValueState::instance.attackInfo.pikemenSwordsmenAndMore++;
                    } else if (DAT_TribesState::instance.tribes[tribeID].tribeType == AITT_KNIGHTS) {
                        DAT_TroopValueState::instance.attackInfo.knights++;
                    } else if (DAT_TribesState::instance.tribes[tribeID].tribeType == AITT_MONKS) {
                        DAT_TroopValueState::instance.attackInfo.pikemenSwordsmenAndMore++;
                    } else if (DAT_TribesState::instance.tribes[tribeID].tribeType == AITT_ARCHERS
                        || DAT_TribesState::instance.tribes[tribeID].tribeType == AITT_CROSSBOWMEN
                        || DAT_TribesState::instance.tribes[tribeID].tribeType == AITT_ARAB_ARCHERS
                        || DAT_TribesState::instance.tribes[tribeID].tribeType == AITT_HORSE_ARCHERS
                        || DAT_TribesState::instance.tribes[tribeID].tribeType == AITT_SLINGERS
                        || DAT_TribesState::instance.tribes[tribeID].tribeType == AITT_FIRE_THROWERS) {
                        DAT_TroopValueState::instance.attackInfo.ranged++;
                    }
                }
            }
            if (DAT_TroopValueState::instance.attackInfo.knights != 0) {
                if (DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen != 0) {
                    DAT_TroopValueState::instance.attackInfo.knights = 0;
                }
                if (DAT_TroopValueState::instance.attackInfo.pikemenSwordsmenAndMore != 0) {
                    DAT_TroopValueState::instance.attackInfo.knights = 0;
                }
            }
            int minTroops = 6;
            if (DAT_GameState::instance.mapAndTime.difficulty == 0) {
                minTroops = 3;
            }
            if (DAT_TroopValueState::instance.attackInfo.aiTroops <= 0
                || DAT_TroopValueState::instance.attackInfo.fightingTribeCount <= 0) {
                DAT_TroopValueState::instance.attackInfo.attackForceTooWeak = 1;
            }
            if (DAT_TroopValueState::instance.attackInfo.size > DAT_TroopValueState::instance.attackInfo.aiTroops * 3
                && DAT_TroopValueState::instance.attackInfo.aiTroops < minTroops) {
                MACRO_CALL_MEMBER(TroopValueState_Func::recountTotalTroopValue, this)();
                if (DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[2]
                        + DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[3]
                        + DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[4]
                        + DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[5]
                    < 30) {
                    DAT_TroopValueState::instance.attackInfo.attackForceTooWeak = 1;
                }
            }
        }

    }
}
}
