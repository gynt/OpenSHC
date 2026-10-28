#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Commands::MappersEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051B310
        int TroopValueState::placeSiegeTentAtAttackAngle(int tribeID, MappersEnum commandBuildingType)
        {
            int const newSlot = MACRO_CALL_MEMBER(
                OpenSHC::Map::Navigation::PathFindingState_Func::findFreeSiegeTentPointIndex,
                DAT_PathFindingState::ptr)(200,
                DAT_UnitsState::instance.units[DAT_TribesState::instance.tribes[tribeID].leaderUnitID].x,
                DAT_UnitsState::instance.units[DAT_TribesState::instance.tribes[tribeID].leaderUnitID].y, tribeID);
            if (newSlot != 0) {
                DAT_TribesState::instance.tribes[tribeID].previousTentPointIndex
                    = DAT_TribesState::instance.tribes[tribeID].tentPointIndex;
                DAT_TroopValueState::instance.attackInfo
                    .tentPointsValues[DAT_TribesState::instance.tribes[tribeID].previousTentPointIndex]
                    .tribeID
                    = 0;
                DAT_TroopValueState::instance.attackInfo
                    .tentPointsValues[DAT_TribesState::instance.tribes[tribeID].previousTentPointIndex]
                    .tribeUID
                    = 0;
                DAT_TroopValueState::instance.attackInfo.tentPointsValues[newSlot].tribeUID
                    = DAT_TribesState::instance.tribes[tribeID].uid;
                DAT_TroopValueState::instance.attackInfo.tentPointsValues[newSlot].tribeID = tribeID;
                DAT_TroopValueState::instance.attackInfo.tentPointsValues[newSlot].reservationTimer = 3;
                DAT_TribesState::instance.tribes[tribeID].tentPointIndex = newSlot;
                MACRO_CALL_MEMBER(TileMapState_Func::placeBuilding, DAT_TileMapState::ptr)(
                    DAT_TribesState::instance.tribes[tribeID].owner,
                    DAT_TroopValueState::instance.attackInfo.tentPointsValues[newSlot].x - 1,
                    DAT_TroopValueState::instance.attackInfo.tentPointsValues[newSlot].y - 1, commandBuildingType, 3,
                    15);
                DAT_BuildingsState::instance.buildings[DAT_TileMapState::instance.placedBuildingID].attackWave
                    = DAT_TribesState::instance.tribes[tribeID].attackWave;
                MACRO_CALL_MEMBER(TribesState_Func::giveTribeAnInstruction, DAT_TribesState::ptr)(tribeID,
                    UIT_CONSTRUCT_SIEGE_EQUIPMENTOIL_DUTYENGINEERRELATED, DAT_TileMapState::instance.placedBuildingID,
                    DAT_BuildingsState::instance.buildings[DAT_TileMapState::instance.placedBuildingID].uid, 0);
                return newSlot;
            }
            return 0;
        }

    }
}
}
