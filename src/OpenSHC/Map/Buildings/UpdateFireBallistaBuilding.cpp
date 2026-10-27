#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/AI/Tribes/AITribeType.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    // attackWave > 0 is signed (jle 0x41E26F); waveTribeCountThisTick is a signed byte (jg 0x41E27F).
    // buildingProgress spawns at > 0x140 (jle 0x41E33C). currentEmployeeCount is a signed short (cmp dx at
    // 0x41E3CF/0x41E3DB, movsx at 0x41E477/0x41E5AE). The first loop re-reads DAT_CurrentBuildingID every
    // iteration (0x41E46A); the crew copy re-reads it after the loop (0x41E601), destroyBuilding uses that ID.
    // FUNCTION: STRONGHOLDCRUSADER 0x0041E240
    void Buildings::UpdateFireBallistaBuilding()
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
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = 3;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = 2;
                }
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                buildingID);
            buildingID = DAT_CurrentBuildingID::instance;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].oldVisualActiveState = 0;
        }
        int* progressPtr = &DAT_BuildingsState::instance.buildings[buildingID].buildingProgress;
        *progressPtr = *progressPtr + DAT_BuildingsState::instance.buildings[buildingID].currentEmployeeCount;
        if (DAT_BuildingsState::instance.buildings[buildingID].buildingProgress <= 0x140) {
            return;
        }
        int owner = DAT_BuildingsState::instance.buildings[buildingID].owner;
        int siegeID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(owner,
            owner, DAT_BuildingsState::instance.buildings[buildingID].x * 8,
            DAT_BuildingsState::instance.buildings[buildingID].y * 8,
            DAT_BuildingsState::instance.buildings[buildingID].terrainHeight, OpenSHC::Map::Units::UT_S_FBALLISTA);
        if (siegeID == 0) {
            progressPtr = &DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingProgress;
            *progressPtr = *progressPtr
                - DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].currentEmployeeCount;
            return;
        }
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::generateSiegeCreationInformation, DAT_AICState::ptr)(
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner,
            DAT_CurrentBuildingID::instance, siegeID);
        short employeeCount = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].currentEmployeeCount;
        if (employeeCount != 2) {
            int i = 0;
            if (employeeCount > 0) {
                do {
                    int unitID = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerID[i];
                    DAT_UnitsState::instance.units[unitID].state.generic
                        = OpenSHC::Map::Units::States::US_FADE_TRANSITION;
                    DAT_UnitsState::instance.units[unitID].fadeLevel = 0x20;
                    DAT_UnitsState::instance.units[unitID].fadeAlphaStep = 0xfe;
                    DAT_UnitsState::instance.units[unitID].stateAfterFade
                        = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                    DAT_UnitsState::instance.units[unitID].totalSizeOfPathPlan = 0;
                    DAT_UnitsState::instance.units[unitID].unknownMovementRelated_0x2d2 = 0;
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::resetUnitMovementState, DAT_UnitsState::ptr)(
                        unitID);
                    short behaviour = DAT_UnitsState::instance.units[unitID].aiUnitBehaviourType;
                    DAT_UnitsState::instance.units[unitID].targetingType_OR_performanceStep
                        = OpenSHC::Map::Units::UIT_MAN_SIEGE_EQUIPMENT;
                    DAT_UnitsState::instance.units[unitID].targetUnitId = (short)siegeID;
                    if (behaviour == 0x16) {
                        DAT_UnitsState::instance.units[siegeID].aiUnitBehaviourType = 0x15;
                    }
                    i = i + 1;
                } while (i < DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].currentEmployeeCount);
            }
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].currentEmployeeCount = 0;
        } else {
            short* workerPtr = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerID;
            if (DAT_UnitsState::instance
                    .units[DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerID[0]]
                    .aiUnitBehaviourType
                == 0x16) {
                DAT_UnitsState::instance.units[siegeID].aiUnitBehaviourType = 0x15;
            }
            int remaining = 2;
            do {
                short workerID = *workerPtr;
                workerPtr = workerPtr + 1;
                remaining = remaining - 1;
                DAT_UnitsState::instance.units[workerID].state.generic = OpenSHC::Map::Units::States::US_AIM_WEAPONUnk;
            } while (remaining != 0);
        }
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::calculatePreferredRelativeOrientation,
            DAT_DirectionAlgorithmState::ptr)(DAT_UnitsState::instance.units[siegeID].x,
            DAT_UnitsState::instance.units[siegeID].y,
            DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .campground.xEntry,
            DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .campground.yEntry);
        if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] == -1
            && DAT_GameSynchronyState::instance.currentAIArray[playerID] == 0) {
            DAT_UnitsState::instance.units[siegeID].facingDirection
                = (short)DAT_DirectionAlgorithmState::instance.orientation;
        } else {
            int keepID = DAT_GameState::instance.playerDataArray[playerID].keep.id;
            DAT_UnitsState::instance.units[siegeID].facingDirection = 0;
            if (keepID == 0) {
                int* cowCountPtr = &DAT_GameState::instance.playerDataArray[playerID].cowCount;
                *cowCountPtr = *cowCountPtr + 2;
            }
        }
        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TroopValueState_Func::addUnitToNewTribe, DAT_TroopValueState::ptr)(
            siegeID, DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].attackWave,
            OpenSHC::AI::Tribes::AITT_FIRE_BALLISTAS, playerID);
        buildingID = DAT_CurrentBuildingID::instance;
        DAT_UnitsState::instance.units[siegeID].unknownSiegeTentRelated02
            = (char)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].unknownSiegeTentRelated01 + 1;
        employeeCount = DAT_BuildingsState::instance.buildings[buildingID].currentEmployeeCount;
        int remaining = employeeCount;
        DAT_UnitsState::instance.units[siegeID].logicalState = 5;
        if (remaining > 0) {
            int* srcUID = DAT_BuildingsState::instance.buildings[buildingID].workerUID;
            int* dstUID = DAT_UnitsState::instance.units[siegeID].manningEngineerUIDRef;
            short* dstID = DAT_UnitsState::instance.units[siegeID].manningEngineerRef;
            short* srcID = DAT_BuildingsState::instance.buildings[buildingID].workerID;
            do {
                *dstID = *srcID;
                *dstUID = *srcUID;
                srcID = srcID + 1;
                dstID = dstID + 1;
                srcUID = srcUID + 1;
                dstUID = dstUID + 1;
                remaining = remaining - 1;
            } while (remaining != 0);
        }
        bool menuOpen = DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_BUILDING_AND_STATUS_MENU;
        DAT_UnitsState::instance.units[siegeID].digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
            = employeeCount;
        if (menuOpen && DAT_CurrentBuildingID::instance == DAT_BuildingsState::instance.menuSelectedBuildingID) {
            DAT_BuildingsState::instance.selectNewSiegeEngineCountdown = 2;
            DAT_BuildingsState::instance.newSiegeEngineUnitID = siegeID;
        }
        DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding = 1;
        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::destroyBuilding, DAT_BuildingsState::ptr)(
            DAT_CurrentBuildingID::instance);
    }

}
}
