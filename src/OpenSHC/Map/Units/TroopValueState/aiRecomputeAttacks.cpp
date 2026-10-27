#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Util/Timing/Stopwatch.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnknownStopwatch.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x005202B0
        void TroopValueState::aiRecomputeAttacks(undefined4 unusedRecomputeCount, int attackID)
        {
            int const playerID = (char)DAT_TroopValueState::instance.attackInfo.attackWavePlayerIDArray[attackID];
            MACRO_CALL_MEMBER(OpenSHC::Util::Timing::Stopwatch_Func::start, DAT_UnknownStopwatch::ptr)();
            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].currentPlayerID_OR_attackedPlayerID_OR_one
                = DAT_GameSynchronyState::instance.currentPlayerSlotID;
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                sizeof(DAT_TileMapState::instance.AIZoneLayer), 0, DAT_TileMapState::instance.AIZoneLayer);
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                sizeof(DAT_TileMapState::instance.AIInfoLayer), 0, DAT_TileMapState::instance.AIInfoLayer);
            MACRO_CALL_MEMBER(TroopValueState_Func::recountAttackTroopValue, this)(1);
            MACRO_CALL_MEMBER(TroopValueState_Func::computeAttackWaveTroopComposition, this)();
            // attackWaveSignpostIndex is an int[50] (header declares a single int followed by padding)
            int signpostTile = DAT_GameState::instance.mapAndTime
                                   .signpostEntryData[(&DAT_TroopValueState::instance.attackInfo.attackWaveSignpostIndex)[attackID]]
                                   .tile;
            if (signpostTile <= 0) {
                signpostTile = DAT_GameState::instance.mapAndTime.signpostEntryData[0].tile;
                (&DAT_TroopValueState::instance.attackInfo.attackWaveSignpostIndex)[attackID] = 0;
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::computeAIZoneLayer,
                DAT_PathFindingState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID, 1,
                (short)DAT_TileMapState::instance.PathConnectionLayer[signpostTile]);
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkLayerAndAIPathCostLayer,
                DAT_PathFindingState::ptr)(60, 0, 0, playerID);
            MACRO_CALL_MEMBER(TroopValueState_Func::initializeAttackZoneSearch, this)(attackID);
            MACRO_CALL_MEMBER(TroopValueState_Func::recomputeTargetedBuildingTilesArray, this)(
                DAT_TroopValueState::instance.attackInfo.attacker);
            MACRO_CALL_MEMBER(TroopValueState_Func::recomputeAttackInfo, this)(
                DAT_TroopValueState::instance.attackInfo.attacker,
                DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1]
                    .currentPlayerID_OR_attackedPlayerID_OR_one);
            MACRO_CALL_MEMBER(TroopValueState_Func::computeSiegeSpotScores, this)(
                DAT_GameSynchronyState::instance.currentPlayerSlotID, DAT_TroopValueState::instance.attackInfo.attacker);
            MACRO_CALL_MEMBER(TroopValueState_Func::setScale3, this)(1, playerID);
            MACRO_CALL_MEMBER(TroopValueState_Func::setTown2, this)(1, playerID);
            MACRO_CALL_MEMBER(TroopValueState_Func::countAvailablePeopleValueSlots, this)(1);
            MACRO_CALL_MEMBER(TroopValueState_Func::countAvailableLordValueSlots, this)(1);
            MACRO_CALL_MEMBER(TroopValueState_Func::setGate2, this)(1, playerID);
            MACRO_CALL_MEMBER(TroopValueState_Func::setWide3, this)(1, playerID);
            MACRO_CALL_MEMBER(TroopValueState_Func::setMoat3, this)(1, playerID);
            MACRO_CALL_MEMBER(TroopValueState_Func::countAvailableHighValueSlots, this)(1);
            MACRO_CALL_MEMBER(TroopValueState_Func::countAvailableArcherValueSlots, this)(1);
            if (DAT_TroopValueState::instance.attackInfo.attackVectorRecalcToggle <= 0) {
                MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::calculateAttackVectorsToCampFireOfPlayer,
                    DAT_GameState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID);
                DAT_TroopValueState::instance.attackInfo.attackVectorRecalcToggle = 1;
            }
            DAT_TroopValueState::instance.attackInfo.attackVectorRecalcToggle++;
            if (DAT_TroopValueState::instance.attackInfo.attackVectorRecalcToggle > 1) {
                DAT_TroopValueState::instance.attackInfo.attackVectorRecalcToggle = 0;
            }
            MACRO_CALL_MEMBER(OpenSHC::Util::Timing::Stopwatch_Func::stop, DAT_UnknownStopwatch::ptr)();
        }

    }
}
}
