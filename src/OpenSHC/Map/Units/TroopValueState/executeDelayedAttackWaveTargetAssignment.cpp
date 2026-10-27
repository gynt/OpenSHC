#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00520CD0
        void TroopValueState::executeDelayedAttackWaveTargetAssignment(int attackID)
        {
            int playerID = (char)DAT_TroopValueState::instance.attackInfo.attackWavePlayerIDArray[attackID];
            if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CUSTOM_MAP
                && DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == OpenSHC::Map::MT_SIEGE) {
                playerID = 2;
            }
            DAT_TroopValueState::instance.attackInfo.breachWarningGate++;
            if (MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::canKeepReachSignpostZone, DAT_GameState::ptr)(
                    DAT_GameSynchronyState::instance.currentPlayerSlotID, playerID, attackID)
                == FALSE) {
                DAT_TroopValueState::instance.attackInfo.attackWaveState[attackID] = 3;
                DAT_TroopValueState::instance.attackInfo.attackWaveTicker[attackID] = 0;
                return;
            }
            DAT_TroopValueState::instance.attackInfo.attackWaveTicker[attackID]++;
            if (DAT_TroopValueState::instance.attackInfo.attackWaveTicker[attackID] < 400) {
                return;
            }
            DAT_TroopValueState::instance.attackInfo.attackWaveTicker[attackID] = 0;
            DAT_TroopValueState::instance.attackInfo.someCounter1++;
            MACRO_CALL_MEMBER(TroopValueState_Func::aiRecomputeAttacks, this)(
                DAT_TroopValueState::instance.attackInfo.attackWaveRecomputeStep[attackID]++, attackID);
            MACRO_CALL_MEMBER(TroopValueState_Func::collectWaveTribesSortedByTypePriority, this)(
                attackID, 1000, 10000, STBT_0x41b);
            MACRO_CALL_MEMBER(TroopValueState_Func::applyTribeBehaviorTypes, this)(STBT_0x41b, STBT_1, 50, 50);
            MACRO_CALL_MEMBER(TroopValueState_Func::collectWaveTribesSortedByTypePriority, this)(
                attackID, 1000, 10000, STBT_0x418);
            MACRO_CALL_MEMBER(TroopValueState_Func::applyTribeBehaviorTypes, this)(STBT_0x418, STBT_1, 20, 70);
            if (DAT_TroopValueState::instance.attackInfo.peopleTargetsAvailable != 0
                && DAT_TroopValueState::instance.attackInfo.fightingTribeCount >= 10) {
                MACRO_CALL_MEMBER(TroopValueState_Func::collectWaveTribesSortedByTypePriority, this)(
                    attackID, 1, DAT_TroopValueState::instance.attackInfo.peopleTargetsAvailable, STBT_0x3fb);
                MACRO_CALL_MEMBER(TroopValueState_Func::applyTribeBehaviorTypes, this)(STBT_0x3fb, STBT_1, 5, 15);
            }
            if (DAT_TroopValueState::instance.attackInfo.lordTargetsAvailable != 0) {
                MACRO_CALL_MEMBER(TroopValueState_Func::collectWaveTribesSortedByTypePriority, this)(
                    attackID, DAT_TroopValueState::instance.attackInfo.field_0x20f3c, 1000, STBT_0x3fd);
                MACRO_CALL_MEMBER(TroopValueState_Func::assignBehaviorTypeToNearbyTribes, this)(STBT_0x3fd, 1, 0, 5);
            }
            if (DAT_TroopValueState::instance.attackInfo.high3 != 0) {
                MACRO_CALL_MEMBER(TroopValueState_Func::collectWaveTribesSortedByTypePriority, this)(
                    attackID, DAT_TroopValueState::instance.attackInfo.high3, 10000, STBT_0x3f8);
                MACRO_CALL_MEMBER(TroopValueState_Func::applyTribeBehaviorTypes, this)(STBT_0x3f8, STBT_1, 20, 10);
            }
            if (DAT_TroopValueState::instance.attackInfo.arch3 != 0) {
                MACRO_CALL_MEMBER(TroopValueState_Func::collectWaveTribesSortedByTypePriority, this)(
                    attackID, DAT_TroopValueState::instance.attackInfo.arch3, 10000, STBT_0x3f9);
                MACRO_CALL_MEMBER(TroopValueState_Func::applyTribeBehaviorTypes, this)(STBT_0x3f9, STBT_1, 20, 10);
            }
            if (DAT_TroopValueState::instance.attackInfo.peopleTargetsAvailable != 0) {
                MACRO_CALL_MEMBER(TroopValueState_Func::collectWaveTribesSortedByTypePriority, this)(
                    attackID, 2, DAT_TroopValueState::instance.attackInfo.peopleTargetsAvailable, STBT_0x3fb);
                MACRO_CALL_MEMBER(TroopValueState_Func::applyTribeBehaviorTypes, this)(STBT_0x3fb, STBT_1, 0, 10);
            }
            if (DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].town2 != 0) {
                MACRO_CALL_MEMBER(TroopValueState_Func::collectWaveTribesSortedByTypePriority, this)(
                    attackID, 1, DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].town2, STBT_0x3f5);
                MACRO_CALL_MEMBER(TroopValueState_Func::applyTribeBehaviorTypes, this)(STBT_0x3f5, STBT_1, 20, 10);
            }
            MACRO_CALL_MEMBER(TroopValueState_Func::collectWaveTribesSortedByTypePriority, this)(
                attackID, 1000, 10000, STBT_0x411);
            MACRO_CALL_MEMBER(TroopValueState_Func::assignBehaviorTypeAndLinkSupportTribe, this)(
                attackID, playerID, STBT_0x411, 0, 10);
            MACRO_CALL_MEMBER(TroopValueState_Func::collectWaveTribesSortedByTypePriority, this)(
                attackID, 1000, 10000, STBT_7);
            MACRO_CALL_MEMBER(TroopValueState_Func::applyTribeBehaviorTypes, this)(STBT_7, STBT_1, 0, 5);
            MACRO_CALL_MEMBER(TroopValueState_Func::collectWaveTribesSortedByTypePriority, this)(
                attackID, 1000, 10000, STBT_0x416);
            MACRO_CALL_MEMBER(TroopValueState_Func::applyTribeBehaviorTypes, this)(STBT_0x416, STBT_1, 0, 5);
        }

    }
}
}
