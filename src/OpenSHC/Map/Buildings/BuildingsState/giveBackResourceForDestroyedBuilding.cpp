#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Game::GameMode2;
        using OpenSHC::Game::Resources::ResourceType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00421D70
        void BuildingsState::giveBackResourceForDestroyedBuilding(
            int buildingIDORIfNegResourceType, int playerID, int param_3)
        {
            // Matching note: Every branch gives back all five resources itself; the compiler merges the identical
            // pitch and gold tails. In the building branch the original keeps the address of buildingType in a
            // register and the wood share in ebx; our compiler spills the address instead.
            // param_3 is the percentage of the costs that is given back
            if (param_3 == 0) {
                return;
            }
            int percentage = param_3;
            if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                percentage = 100;
            }

            if (buildingIDORIfNegResourceType == -1) {
                // Stone of a wall
                if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                    ++DAT_GameState::instance.playerDataArray[playerID]
                          .pendingResources[OpenSHC::Game::Resources::RT_STONE];
                    return;
                }
                DAT_GameState::instance.playerDataArray[playerID].stoneGainedFraction += percentage * 2 / 100;
                int stone = DAT_GameState::instance.playerDataArray[playerID].stoneGainedFraction / 4;
                DAT_GameState::instance.playerDataArray[playerID].stoneGainedFraction -= stone * 4;
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceGain,
                        DAT_BuildingsState::ptr)(playerID, OpenSHC::Game::Resources::RT_STONE, stone)
                    == FALSE) {
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::playSFXNoSpaceInTheStockPile,
                        DAT_GameState::ptr)(playerID);
                }
                return;
            }
            if (buildingIDORIfNegResourceType == -2) {
                // Wood
                DAT_GameState::instance.playerDataArray[playerID].woodGainedFraction += percentage * 2 / 100;
                int wood = DAT_GameState::instance.playerDataArray[playerID].woodGainedFraction / 4;
                DAT_GameState::instance.playerDataArray[playerID].woodGainedFraction -= wood * 4;
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceGain,
                        DAT_BuildingsState::ptr)(playerID, OpenSHC::Game::Resources::RT_WOOD, wood)
                    == FALSE) {
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::playSFXNoSpaceInTheStockPile,
                        DAT_GameState::ptr)(playerID);
                }
                return;
            }

#define GIVE_BACK_RESOURCE(resourceType, amount)                                                                     \
    if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceGain,                         \
            DAT_BuildingsState::ptr)(playerID, resourceType, amount)                                                 \
        == FALSE) {                                                                                                  \
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::playSFXNoSpaceInTheStockPile, DAT_GameState::ptr)( \
            playerID);                                                                                               \
    }

            if (buildingIDORIfNegResourceType == -3) {
                // Mangonel on a tower
                int wood = DAT_BuildingsState::instance.buildingCosts[BT_TOWER1_RUIN_OR_MANGONEL].requiredWood * percentage / 100;
                int stone
                    = DAT_BuildingsState::instance.buildingCosts[BT_TOWER1_RUIN_OR_MANGONEL].requiredStone_0x4 * percentage / 100;
                int iron = DAT_BuildingsState::instance.buildingCosts[BT_TOWER1_RUIN_OR_MANGONEL].requiredIron_0x8 * percentage / 100;
                int pitch = DAT_BuildingsState::instance.buildingCosts[BT_TOWER1_RUIN_OR_MANGONEL].requiredPitch_0xc * percentage / 100;
                int gold = DAT_BuildingsState::instance.buildingCosts[BT_TOWER1_RUIN_OR_MANGONEL].requiredGold * percentage / 100;
                GIVE_BACK_RESOURCE(OpenSHC::Game::Resources::RT_WOOD, wood)
                GIVE_BACK_RESOURCE(OpenSHC::Game::Resources::RT_STONE, stone)
                GIVE_BACK_RESOURCE(OpenSHC::Game::Resources::RT_IRON, iron)
                GIVE_BACK_RESOURCE(OpenSHC::Game::Resources::RT_PITCH, pitch)
                GIVE_BACK_RESOURCE(OpenSHC::Game::Resources::RT_GOLD, gold)
            } else if (buildingIDORIfNegResourceType == -4) {
                // Ballista on a tower
                int wood = DAT_BuildingsState::instance.buildingCosts[BT_TOWER2_RUIN_OR_BALLISTA].requiredWood * percentage / 100;
                int stone
                    = DAT_BuildingsState::instance.buildingCosts[BT_TOWER2_RUIN_OR_BALLISTA].requiredStone_0x4 * percentage / 100;
                int iron = DAT_BuildingsState::instance.buildingCosts[BT_TOWER2_RUIN_OR_BALLISTA].requiredIron_0x8 * percentage / 100;
                int pitch = DAT_BuildingsState::instance.buildingCosts[BT_TOWER2_RUIN_OR_BALLISTA].requiredPitch_0xc * percentage / 100;
                int gold = DAT_BuildingsState::instance.buildingCosts[BT_TOWER2_RUIN_OR_BALLISTA].requiredGold * percentage / 100;
                GIVE_BACK_RESOURCE(OpenSHC::Game::Resources::RT_WOOD, wood)
                GIVE_BACK_RESOURCE(OpenSHC::Game::Resources::RT_STONE, stone)
                GIVE_BACK_RESOURCE(OpenSHC::Game::Resources::RT_IRON, iron)
                GIVE_BACK_RESOURCE(OpenSHC::Game::Resources::RT_PITCH, pitch)
                GIVE_BACK_RESOURCE(OpenSHC::Game::Resources::RT_GOLD, gold)
            } else {
                int wood
                    = DAT_BuildingsState::instance.buildingCosts[this->buildings[buildingIDORIfNegResourceType].buildingType].requiredWood
                    * percentage / 100;
                int stone
                    = DAT_BuildingsState::instance.buildingCosts[this->buildings[buildingIDORIfNegResourceType].buildingType].requiredStone_0x4
                    * percentage / 100;
                int iron
                    = DAT_BuildingsState::instance.buildingCosts[this->buildings[buildingIDORIfNegResourceType].buildingType].requiredIron_0x8
                    * percentage / 100;
                int pitch
                    = DAT_BuildingsState::instance.buildingCosts[this->buildings[buildingIDORIfNegResourceType].buildingType].requiredPitch_0xc
                    * percentage / 100;
                int gold
                    = DAT_BuildingsState::instance.buildingCosts[this->buildings[buildingIDORIfNegResourceType].buildingType].requiredGold
                    * percentage / 100;
                int siegeStone = stone;
                int siegeGold = gold;
                if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Buildings::BuildingsState_Func::resourceGainForKillingPitAndPitchDitch, this)(
                        (BuildingType)this->buildings[buildingIDORIfNegResourceType].buildingType, &siegeStone,
                        &siegeGold);
                    DAT_GameState::instance.playerDataArray[playerID].pendingResources[OpenSHC::Game::Resources::RT_STONE]
                        += siegeStone;
                    DAT_GameState::instance.playerDataArray[playerID].pendingResources[OpenSHC::Game::Resources::RT_GOLD]
                        += siegeGold;
                    return;
                }
                GIVE_BACK_RESOURCE(OpenSHC::Game::Resources::RT_WOOD, wood)
                GIVE_BACK_RESOURCE(OpenSHC::Game::Resources::RT_STONE, stone)
                GIVE_BACK_RESOURCE(OpenSHC::Game::Resources::RT_IRON, iron)
                GIVE_BACK_RESOURCE(OpenSHC::Game::Resources::RT_PITCH, pitch)
                GIVE_BACK_RESOURCE(OpenSHC::Game::Resources::RT_GOLD, gold)
            }
#undef GIVE_BACK_RESOURCE
        }

    }
}
}
