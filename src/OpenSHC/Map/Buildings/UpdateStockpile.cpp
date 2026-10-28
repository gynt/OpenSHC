#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    // Every 4th tick (test byte [mapTimeInTicks], 3) moves one unit of each starting good from pendingResources
    // into this stockpile. Wood/hops/pitch/flour decrement pendingResources before incrementing the building
    // counter, stone/iron/wheat/ale after it (store order at 0x412406 / 0x4124CA).
    // FUNCTION: STRONGHOLDCRUSADER 0x00412360
    void Buildings::UpdateStockpile()
    {
        int buildingID = DAT_CurrentBuildingID::instance;
        int playerID = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        int anyDelivered = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 0;
        if ((DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY
                || playerID != DAT_GameState::instance.mapAndTime.somePlayerID)
            && (DAT_GameCore::instance.mapTimeInTicks & 3) == 0
            && DAT_GameState::instance.playerDataArray[playerID].hasInitialResourceRecievingStarted == 0
            && DAT_GameCore::instance.gameMode_2 != Game::GM_EDITOR
            && DAT_GameCore::instance.gameMode_2 != Game::GM_SIEGE_THAT
            && DAT_GameState::instance.playerDataArray[playerID].goodsDeliveryDelay == 0) {
            if (DAT_GameState::instance.playerDataArray[playerID].pendingResources[2] > 0
                && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::buildingHasSpaceForResource, DAT_BuildingsState::ptr)(
                       buildingID, OpenSHC::Game::Resources::RT_WOOD)
                    != 0) {
                int startAmount = DAT_GameState::instance.playerDataArray[playerID].pendingResources[2];
                int* counterPtr = &DAT_GameState::instance.playerDataArray[playerID].currentResources[2];
                *counterPtr = *counterPtr + 1;
                DAT_GameState::instance.playerDataArray[playerID].pendingResources[2] = startAmount - 1;
                DAT_BuildingsState::instance.buildings[buildingID].resources[2] += 1;
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::computeResourceSumForBuilding, DAT_BuildingsState::ptr)(
                    buildingID);
                DAT_GameState::instance.playerDataArray[playerID].hasInitialResourceRecievingStarted = 1;
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(buildingID);
                anyDelivered = 1;
                buildingID = DAT_CurrentBuildingID::instance;
            }
            if (DAT_GameState::instance.playerDataArray[playerID].pendingResources[3] > 0
                && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::buildingHasSpaceForResource, DAT_BuildingsState::ptr)(
                       buildingID, OpenSHC::Game::Resources::RT_HOPS)
                    != 0) {
                int startAmount = DAT_GameState::instance.playerDataArray[playerID].pendingResources[3];
                int* counterPtr = &DAT_GameState::instance.playerDataArray[playerID].currentResources[3];
                *counterPtr = *counterPtr + 1;
                DAT_GameState::instance.playerDataArray[playerID].pendingResources[3] = startAmount - 1;
                DAT_BuildingsState::instance.buildings[buildingID].resources[3] += 1;
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::computeResourceSumForBuilding, DAT_BuildingsState::ptr)(
                    buildingID);
                DAT_GameState::instance.playerDataArray[playerID].hasInitialResourceRecievingStarted = 1;
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(buildingID);
                anyDelivered = 1;
                buildingID = DAT_CurrentBuildingID::instance;
            }
            if (DAT_GameState::instance.playerDataArray[playerID].pendingResources[4] > 0
                && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::buildingHasSpaceForResource, DAT_BuildingsState::ptr)(
                       buildingID, OpenSHC::Game::Resources::RT_STONE)
                    != 0) {
                int startAmount = DAT_GameState::instance.playerDataArray[playerID].pendingResources[4];
                int* counterPtr = &DAT_GameState::instance.playerDataArray[playerID].currentResources[4];
                *counterPtr = *counterPtr + 1;
                DAT_BuildingsState::instance.buildings[buildingID].resources[4] += 1;
                DAT_GameState::instance.playerDataArray[playerID].pendingResources[4] = startAmount - 1;
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::computeResourceSumForBuilding, DAT_BuildingsState::ptr)(
                    buildingID);
                DAT_GameState::instance.playerDataArray[playerID].hasInitialResourceRecievingStarted = 1;
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(buildingID);
                anyDelivered = 1;
                buildingID = DAT_CurrentBuildingID::instance;
            }
            if (DAT_GameState::instance.playerDataArray[playerID].pendingResources[6] > 0
                && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::buildingHasSpaceForResource, DAT_BuildingsState::ptr)(
                       buildingID, OpenSHC::Game::Resources::RT_IRON)
                    != 0) {
                int startAmount = DAT_GameState::instance.playerDataArray[playerID].pendingResources[6];
                int* counterPtr = &DAT_GameState::instance.playerDataArray[playerID].currentResources[6];
                *counterPtr = *counterPtr + 1;
                DAT_BuildingsState::instance.buildings[buildingID].resources[6] += 1;
                DAT_GameState::instance.playerDataArray[playerID].pendingResources[6] = startAmount - 1;
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::computeResourceSumForBuilding, DAT_BuildingsState::ptr)(
                    buildingID);
                DAT_GameState::instance.playerDataArray[playerID].hasInitialResourceRecievingStarted = 1;
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(buildingID);
                anyDelivered = 1;
                buildingID = DAT_CurrentBuildingID::instance;
            }
            if (DAT_GameState::instance.playerDataArray[playerID].pendingResources[7] > 0
                && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::buildingHasSpaceForResource, DAT_BuildingsState::ptr)(
                       buildingID, OpenSHC::Game::Resources::RT_PITCH)
                    != 0) {
                int startAmount = DAT_GameState::instance.playerDataArray[playerID].pendingResources[7];
                int* counterPtr = &DAT_GameState::instance.playerDataArray[playerID].currentResources[7];
                *counterPtr = *counterPtr + 1;
                DAT_GameState::instance.playerDataArray[playerID].pendingResources[7] = startAmount - 1;
                DAT_BuildingsState::instance.buildings[buildingID].resources[7] += 1;
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::computeResourceSumForBuilding, DAT_BuildingsState::ptr)(
                    buildingID);
                DAT_GameState::instance.playerDataArray[playerID].hasInitialResourceRecievingStarted = 1;
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(buildingID);
                anyDelivered = 1;
                buildingID = DAT_CurrentBuildingID::instance;
            }
            if (DAT_GameState::instance.playerDataArray[playerID].pendingResources[9] > 0
                && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::buildingHasSpaceForResource, DAT_BuildingsState::ptr)(
                       buildingID, OpenSHC::Game::Resources::RT_WHEAT)
                    != 0) {
                int startAmount = DAT_GameState::instance.playerDataArray[playerID].pendingResources[9];
                int* counterPtr = &DAT_GameState::instance.playerDataArray[playerID].currentResources[9];
                *counterPtr = *counterPtr + 1;
                DAT_BuildingsState::instance.buildings[buildingID].resources[9] += 1;
                DAT_GameState::instance.playerDataArray[playerID].pendingResources[9] = startAmount - 1;
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::computeResourceSumForBuilding, DAT_BuildingsState::ptr)(
                    buildingID);
                DAT_GameState::instance.playerDataArray[playerID].hasInitialResourceRecievingStarted = 1;
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(buildingID);
                anyDelivered = 1;
                buildingID = DAT_CurrentBuildingID::instance;
            }
            if (DAT_GameState::instance.playerDataArray[playerID].pendingResources[0xe] > 0
                && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::buildingHasSpaceForResource, DAT_BuildingsState::ptr)(
                       buildingID, OpenSHC::Game::Resources::RT_ALE)
                    != 0) {
                int startAmount = DAT_GameState::instance.playerDataArray[playerID].pendingResources[0xe];
                int* counterPtr = &DAT_GameState::instance.playerDataArray[playerID].currentResources[0xe];
                *counterPtr = *counterPtr + 1;
                DAT_BuildingsState::instance.buildings[buildingID].resources[0xe] += 1;
                DAT_GameState::instance.playerDataArray[playerID].pendingResources[0xe] = startAmount - 1;
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::computeResourceSumForBuilding, DAT_BuildingsState::ptr)(
                    buildingID);
                DAT_GameState::instance.playerDataArray[playerID].hasInitialResourceRecievingStarted = 1;
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(buildingID);
                anyDelivered = 1;
                buildingID = DAT_CurrentBuildingID::instance;
            }
            if (DAT_GameState::instance.playerDataArray[playerID].pendingResources[0x10] > 0
                && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::buildingHasSpaceForResource,
                       DAT_BuildingsState::ptr)(buildingID, OpenSHC::Game::Resources::RT_FLOUR)
                    != 0) {
                int startAmount = DAT_GameState::instance.playerDataArray[playerID].pendingResources[0x10];
                int* counterPtr = &DAT_GameState::instance.playerDataArray[playerID].currentResources[0x10];
                *counterPtr = *counterPtr + 1;
                DAT_GameState::instance.playerDataArray[playerID].pendingResources[0x10] = startAmount - 1;
                DAT_BuildingsState::instance.buildings[buildingID].resources[0x10] += 1;
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::computeResourceSumForBuilding, DAT_BuildingsState::ptr)(
                    buildingID);
                DAT_GameState::instance.playerDataArray[playerID].hasInitialResourceRecievingStarted = 1;
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(buildingID);
            } else if (anyDelivered == 0) {
                return;
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::countPlayerResources, DAT_BuildingsState::ptr)(playerID);        }
    }

}
}