#include "OpenSHC/AI/Tribes/AITribeType.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_AttackInfoDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {

    // Same flow as UpdateSiegeTowerBuilding: spawn at progress > 0x78, UT_S_SHIELD, exactly 1 engineer starts
    // operating, tribe type AITT_PORTABLE_SHIELDS.
    // FUNCTION: STRONGHOLDCRUSADER 0x004205B0
    void Buildings::UpdateShieldBuilding()
    {
        int buildingID = DAT_CurrentBuildingID::instance;
        int playerID = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        int wave = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].attackWave;
        if (wave > 0 && DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY
            && (char)DAT_TroopValueState::instance.attackInfo.waveTribeCountThisTick[wave] <= 0) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].logicalState
                = OpenSHC::Map::Buildings::BLS_REMOVE;
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].oldVisualActiveState == -1) {
            int fullID = DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID];
            DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive = 1;
            DAT_BuildingsState::instance.buildings[buildingID].ownerColorIndex
                = DAT_BuildingsState::instance.buildings[buildingID].owner;
            DAT_BuildingsState::instance.buildings[buildingID].renderAnimation = 1;
            DAT_BuildingsState::instance.buildings[buildingID].showOverlays = 0;
            if (fullID != -1) {
                DAT_BuildingsState::instance.buildings[buildingID].animationFrame = 1;
            } else {
                int lordType = MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::getLordTypeForPlayer,
                    DAT_GameSynchronyState::ptr)(playerID);
                buildingID = DAT_CurrentBuildingID::instance;
                if (lordType == 0) {
                    DAT_BuildingsState::instance.buildings[buildingID].animationFrame = 3;
                } else {
                    DAT_BuildingsState::instance.buildings[buildingID].animationFrame = 2;
                }
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                buildingID);
            buildingID = DAT_CurrentBuildingID::instance;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].oldVisualActiveState = 0;
        }
        int* progressPtr = &DAT_BuildingsState::instance.buildings[buildingID].buildingProgress;
        *progressPtr = *progressPtr + DAT_BuildingsState::instance.buildings[buildingID].currentEmployeeCount;
        if (DAT_BuildingsState::instance.buildings[buildingID].buildingProgress <= 0x78) {
            return;
        }
        int owner = DAT_BuildingsState::instance.buildings[buildingID].owner;
        int siegeID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(owner,
            owner, DAT_BuildingsState::instance.buildings[buildingID].x * 8,
            DAT_BuildingsState::instance.buildings[buildingID].y * 8,
            DAT_BuildingsState::instance.buildings[buildingID].terrainHeight, OpenSHC::Map::Units::UT_S_SHIELD);
        if (siegeID == 0) {
            progressPtr = &DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingProgress;
            *progressPtr = *progressPtr
                - DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].currentEmployeeCount;
            return;
        }
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].currentEmployeeCount != 1) {
            int offsetIndex = SEC_RNG::instance.currentNumber2 % 16;
            MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
            int i = 0;
            buildingID = DAT_CurrentBuildingID::instance;
            if (DAT_BuildingsState::instance.buildings[buildingID].currentEmployeeCount > 0) {
                do {
                    int unitID = DAT_BuildingsState::instance.buildings[buildingID].workerID[i];
                    int x = DAT_AttackInfoDefinedData::instance.unitScatterOffsetsXY[offsetIndex][0]
                        + DAT_BuildingsState::instance.buildings[buildingID].x;
                    int y = DAT_AttackInfoDefinedData::instance.unitScatterOffsetsXY[offsetIndex][1]
                        + DAT_BuildingsState::instance.buildings[buildingID].y;
                    offsetIndex = (offsetIndex + 1) % 16;
                    DAT_UnitsState::instance.units[unitID].state.generic
                        = OpenSHC::Map::Units::States::US_FADE_TRANSITION;
                    DAT_UnitsState::instance.units[unitID].fadeLevel = 0x20;
                    DAT_UnitsState::instance.units[unitID].fadeAlphaStep = 0xfe;
                    DAT_UnitsState::instance.units[unitID].stateAfterFade
                        = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                    MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::computeNextRallyPointDestination,
                        DAT_PathFindingState::ptr)(-1, x, y);
                    int tile = DAT_PathFindingState::instance.ALG_ResultTile;
                    short height = DAT_TileMapState::instance.HeightLayer[tile];
                    int resultX = DAT_PathFindingState::instance.ALG_ResultX;
                    int resultY = DAT_PathFindingState::instance.ALG_ResultY;
                    DAT_UnitsState::instance.units[unitID].tile = tile;
                    DAT_UnitsState::instance.units[unitID].moveToTile = tile;
                    DAT_UnitsState::instance.units[unitID].x = (short)resultX;
                    DAT_UnitsState::instance.units[unitID].mimicCurrentXPosition = (short)resultX;
                    DAT_UnitsState::instance.units[unitID].terrainOrClimbHeight = height;
                    DAT_UnitsState::instance.units[unitID].y = (short)resultY;
                    DAT_UnitsState::instance.units[unitID].mimicCurrentYPosition = (short)resultY;
                    DAT_UnitsState::instance.units[unitID].microXPosition = (short)(resultX * 8 + 4);
                    DAT_UnitsState::instance.units[unitID].microYPosition = (short)(resultY * 8 + 4);
                    DAT_UnitsState::instance.units[unitID].totalSizeOfPathPlan = 0;
                    DAT_UnitsState::instance.units[unitID].unknownMovementRelated_0x2d2 = 0;
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::updateMicroPosition, DAT_UnitsState::ptr)(
                        unitID);
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::resetUnitMovementState, DAT_UnitsState::ptr)(
                        unitID);
                    buildingID = DAT_CurrentBuildingID::instance;
                    DAT_UnitsState::instance.units[unitID].targetingType_OR_performanceStep
                        = OpenSHC::Map::Units::UIT_MAN_SIEGE_EQUIPMENT;
                    DAT_UnitsState::instance.units[unitID].targetUnitId = (short)siegeID;
                    i = i + 1;
                } while (i < DAT_BuildingsState::instance.buildings[buildingID].currentEmployeeCount);
            }
            DAT_BuildingsState::instance.buildings[buildingID].currentEmployeeCount = 0;
        } else {
            short* workerPtr = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerID;
            int remaining = 1;
            do {
                DAT_UnitsState::instance.units[*workerPtr].state.generic = OpenSHC::Map::Units::States::US_AIM_WEAPONUnk;
                workerPtr = workerPtr + 1;
                remaining = remaining - 1;
            } while (remaining != 0);
        }
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::calculatePreferredRelativeOrientation,
            DAT_DirectionAlgorithmState::ptr)(DAT_UnitsState::instance.units[siegeID].x,
            DAT_UnitsState::instance.units[siegeID].y,
            DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .campground.xEntry,
            DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .campground.yEntry);
        buildingID = DAT_CurrentBuildingID::instance;
        short ownerID = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[ownerID] == -1
            && DAT_GameSynchronyState::instance.currentAIArray[ownerID] == 0) {
            DAT_UnitsState::instance.units[siegeID].facingDirection
                = (short)DAT_DirectionAlgorithmState::instance.orientation;
        } else {
            DAT_UnitsState::instance.units[siegeID].facingDirection = 0;
        }
        int attackWave = DAT_BuildingsState::instance.buildings[buildingID].attackWave;
        DAT_UnitsState::instance.units[siegeID].unknownSiegeTentRelated02
            = (char)DAT_BuildingsState::instance.buildings[buildingID].unknownSiegeTentRelated01 + 1;
        DAT_UnitsState::instance.units[siegeID].logicalState = 5;
        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TroopValueState_Func::addUnitToNewTribe, DAT_TroopValueState::ptr)(
            siegeID, attackWave, OpenSHC::AI::Tribes::AITT_PORTABLE_SHIELDS, playerID);
        buildingID = DAT_CurrentBuildingID::instance;
        short employeeCount = DAT_BuildingsState::instance.buildings[buildingID].currentEmployeeCount;
        if (employeeCount > 0) {
            int remaining = employeeCount;
            int k = 0;
            do {
                DAT_UnitsState::instance.units[siegeID].manningEngineerRef[k]
                    = DAT_BuildingsState::instance.buildings[buildingID].workerID[k];
                DAT_UnitsState::instance.units[siegeID].manningEngineerUIDRef[k]
                    = DAT_BuildingsState::instance.buildings[buildingID].workerUID[k];
                k = k + 1;
                remaining = remaining - 1;
            } while (remaining != 0);
            buildingID = DAT_CurrentBuildingID::instance;
        }
        bool menuOpen = DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_BUILDING_AND_STATUS_MENU;
        DAT_UnitsState::instance.units[siegeID].digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
            = employeeCount;
        if (menuOpen && buildingID == DAT_BuildingsState::instance.menuSelectedBuildingID) {
            DAT_BuildingsState::instance.selectNewSiegeEngineCountdown = 2;
            DAT_BuildingsState::instance.newSiegeEngineUnitID = siegeID;
        }
        DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding = 1;
        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::destroyBuilding, DAT_BuildingsState::ptr)(
            buildingID);
    }

}
}
