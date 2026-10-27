#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using namespace OpenSHC::Map::Buildings;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051C570
        undefined4 TroopValueState::ifNecessaryThrowOilAutomatically(int unitID)
        {
            int const tribeID = DAT_UnitsState::instance.units[unitID].tribeID;
            int range = 4;
            if (DAT_UnitsState::instance.units[unitID].terrainOrClimbHeight > 110) {
                range = 5;
            }
            if (tribeID <= 0) {
                return 0;
            }
            if (DAT_UnitsState::instance.units[unitID].closestEnemyMicroDistance > 80) {
                return 0;
            }
            int const owner = DAT_UnitsState::instance.units[unitID].owner;
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[owner] != -1
                && DAT_TribesState::instance.tribes[tribeID].unitStance == Behavior::USE_STAND_GROUND) {
                return 0;
            }
            ++DAT_UnitsState::instance.units[unitID].updateTickTracker;
            if (DAT_UnitsState::instance.units[unitID].updateTickTracker < 8) {
                return 0;
            }
            DAT_UnitsState::instance.units[unitID].updateTickTracker = 0;
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::computeTotalUnitsWithinDistance,
                DAT_PathFindingState::ptr)(owner, 0, 0, DAT_UnitsState::instance.units[unitID].tile, range);
            if (DAT_TribesState::instance.tribes[tribeID].unitStance == Behavior::USE_AGGRESSIVE) {
                if (DAT_PathFindingState::instance.ALGO_TotalTroopCount < 1) {
                    return 0;
                }
            } else if (DAT_PathFindingState::instance.ALGO_TotalTroopCount <= 3
                && DAT_PathFindingState::instance.ALGO_TotalTroopValue < 20) {
                return 0;
            }
            int const enemyUnitID = DAT_PathFindingState::instance.firstMatchingUnitID;
            if (enemyUnitID == 0) {
                return 0;
            }
            short const buildingID
                = DAT_TileMapState::instance.BuildingLayer[DAT_UnitsState::instance.units[enemyUnitID].tile];
            if (buildingID != 0) {
                int footprintSize;
                switch (DAT_BuildingsState::instance.buildings[buildingID].buildingType) {
                case BT_CAMPGROUND:
                    footprintSize = 7;
                    break;
                case BT_PARADEGROUND:
                case BT_PARADEGROUND2:
                case BT_PARADEGROUND3:
                case BT_PARADEGROUND4:
                case BT_PARADEGROUND5:
                    footprintSize = 5;
                    break;
                case BT_OILSMELTER_PART:
                    footprintSize = 4;
                    break;
                default:
                    goto throwOil;
                }
                int const buildingX = DAT_BuildingsState::instance.buildings[buildingID].x;
                int const buildingY = DAT_BuildingsState::instance.buildings[buildingID].y;
                int i = 0;
                int friendlyValue = 0;
                int enemyValue = 0;
                do {
                    MACRO_CALL_MEMBER(TileMapState_Func::getBuildingSizeIndexMappingData, DAT_TileMapState::ptr)(
                        i, footprintSize);
                    for (int tileUnitID = (short)DAT_TileMapState::instance
                             .UnitLayer[DAT_ViewportRenderState::instance
                                            .translationMatrix[DAT_TileMapState::instance.buildingY + buildingY]
                                            .addXgetTile
                                 + DAT_TileMapState::instance.buildingX + buildingX];
                        tileUnitID != 0;
                        tileUnitID = (short)DAT_UnitsState::instance.units[tileUnitID].nextUnitOnTheSameTile) {
                        if (DAT_UnitsState::instance.units[tileUnitID].isSelectable_OR_matchTime != 0) {
                            if (DAT_GameState::instance.mapAndTime
                                    .playerTeams[DAT_UnitsState::instance.units[unitID].owner]
                                != DAT_GameState::instance.mapAndTime
                                    .playerTeams[DAT_UnitsState::instance.units[tileUnitID].owner]) {
                                enemyValue += MACRO_CALL_MEMBER(
                                    TroopValueState_Func::getValueOfTroopType, DAT_TroopValueState::ptr)(
                                    (UnitType)DAT_UnitsState::instance.units[tileUnitID].unitType);
                            } else {
                                friendlyValue += MACRO_CALL_MEMBER(
                                    TroopValueState_Func::getValueOfTroopType, DAT_TroopValueState::ptr)(
                                    (UnitType)DAT_UnitsState::instance.units[tileUnitID].unitType);
                            }
                        }
                    }
                    ++i;
                } while (i < DAT_TileMapState::instance.constructionTileCount);
                if (friendlyValue > enemyValue) {
                    return 0;
                }
            }
        throwOil:
            DAT_UnitsState::instance.units[unitID].targetingType_OR_performanceStep = UIT_THROW_OIL;
            DAT_UnitsState::instance.units[unitID].attackAtTileX = DAT_UnitsState::instance.units[enemyUnitID].x;
            DAT_UnitsState::instance.units[unitID].attackAtTileY = DAT_UnitsState::instance.units[enemyUnitID].y;
            DAT_UnitsState::instance.units[unitID].animationFrame = 4;
            return 1;
        }

    }
}
}
