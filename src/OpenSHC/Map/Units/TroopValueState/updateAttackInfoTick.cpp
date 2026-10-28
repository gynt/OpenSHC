#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Units.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/MapType2.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051FE80
        void TroopValueState::updateAttackInfoTick()
        {
            if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CUSTOM_MAP
                && DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == OpenSHC::Map::MT_SIEGE) {
                DAT_TroopValueState::instance.attackInfo.pitchRelatedPlayerID = 1;
                DAT_TroopValueState::instance.attackInfo.playerID_0x2c850 = 2;
            } else {
                DAT_TroopValueState::instance.attackInfo.pitchRelatedPlayerID
                    = MACRO_CALL(OpenSHC::Map::Units_Func::FindFirstOpponentWithKeep)();
                DAT_TroopValueState::instance.attackInfo.playerID_0x2c850 = 1;
            }
            // field_0x2c854 (undefined1[4] in the header) is an int: count of completed defence schedule cycles
            int* const scheduleCycleCount = (int*)DAT_TroopValueState::instance.attackInfo.field_0x2c854;
            if (DAT_TroopValueState::instance.attackInfo.defenseScheduleTick == 0) {
                DAT_TroopValueState::instance.attackInfo.unitsSentToKeep
                    = DAT_TroopValueState::instance.attackInfo.defenseScheduleTick;
                *scheduleCycleCount = DAT_TroopValueState::instance.attackInfo.defenseScheduleTick;
                MACRO_CALL_MEMBER(TroopValueState_Func::collectArcherUnitsByLocation, this)();
                MACRO_CALL_MEMBER(TroopValueState_Func::assignMacemenAndKnightsNotFromPlayer1ToTribes, this)();
            } else if (DAT_TroopValueState::instance.attackInfo.defenseScheduleTick == 1) {
                MACRO_CALL_MEMBER(TroopValueState_Func::updateArcherBrazierProximityFlags, this)();
            } else if (DAT_TroopValueState::instance.attackInfo.defenseScheduleTick == 50) {
            } else if (DAT_TroopValueState::instance.attackInfo.defenseScheduleTick == 100) {
            } else if (DAT_TroopValueState::instance.attackInfo.defenseScheduleTick == 70) {
                MACRO_CALL_MEMBER(TroopValueState_Func::trySendMacemenTribeToAttack, this)();
            } else if (DAT_TroopValueState::instance.attackInfo.defenseScheduleTick == 60) {
                MACRO_CALL_MEMBER(TroopValueState_Func::trySendKnightTribeToAttack, this)();
            }
            if ((DAT_TroopValueState::instance.attackInfo.defenseScheduleTick & 0xf) == 0) {
                MACRO_CALL_MEMBER(TroopValueState_Func::queueOilThrowForIdleEngineers, this)();
            }
            if ((DAT_TroopValueState::instance.attackInfo.defenseScheduleTick & 0xf) == 8) {
                MACRO_CALL_MEMBER(TroopValueState_Func::redeployArchersToDefensivePositions, this)();
            }
            DAT_TroopValueState::instance.attackInfo.defenseScheduleTick++;
            if (DAT_TroopValueState::instance.attackInfo.defenseScheduleTick > 100) {
                (*scheduleCycleCount)++;
                DAT_TroopValueState::instance.attackInfo.defenseScheduleTick = 2;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::unitsCanMoveFromKeepOfPlayerToAnotherArea,
                    DAT_GameState::ptr)(1)
                    != FALSE
                && DAT_TroopValueState::instance.attackInfo.unitsSentToKeep == 0) {
                DAT_TroopValueState::instance.attackInfo.unitsSentToKeep = 1;
                MACRO_CALL_MEMBER(TroopValueState_Func::commandUnitsToMoveToKeep, this)();
            }
            MACRO_CALL_MEMBER(TroopValueState_Func::processSpottedEnemyTiles, this)();
        }

    }
}
}
