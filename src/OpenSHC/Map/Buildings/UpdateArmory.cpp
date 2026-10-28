#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    // Every 4th tick moves one of each starting weapon/armour (resources 0x11..0x18) from pendingResources into
    // the armory. For metal armour the original stores currentResources[0x18] = 1, not += 1
    // (mov [esi+0x115c328], ebx with ebx = 1 at 0x412A2F). The building id is not reloaded after
    // getArmoryIDIfSpaceLeft (edi kept). The pile sprite starts as 1 (mov [esp+0x30], 1 at 0x412757) and the
    // pile loop returns when no kind was found (test ecx, ecx; jle at 0x412C7A).
    // FUNCTION: STRONGHOLDCRUSADER 0x00412730
    void Buildings::UpdateArmory()
    {
        int owner = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        int delivered = 0;
        int pileSprite = 1;
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(
            DAT_CurrentBuildingID::instance);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        int buildingID = DAT_CurrentBuildingID::instance;
        if (DAT_TileMapState::instance.currentMapperCommand == OpenSHC::Commands::M_MAPPER_NULL) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].pendingResourceLossPreview = 0;
        }
        if ((DAT_GameCore::instance.mapTimeInTicks & 3) == 0 && DAT_GameCore::instance.gameMode_2 != Game::GM_EDITOR
            && DAT_GameCore::instance.gameMode_2 != Game::GM_SIEGE_THAT && DAT_GameState::instance.playerDataArray[owner].goodsDeliveryDelay == 0) {
            int bowStart = DAT_GameState::instance.playerDataArray[owner].pendingResources[0x11];
            if (bowStart > 0 && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getArmoryIDIfSpaceLeft, DAT_BuildingsState::ptr)(buildingID, 0x11, owner, 1) != 0) {
                delivered = 1;
                int* counterPtr = &DAT_GameState::instance.playerDataArray[owner].currentResources[0x11];
                *counterPtr = *counterPtr + 1;
                DAT_BuildingsState::instance.buildings[buildingID].resources[0x11] += 1;
                DAT_GameState::instance.playerDataArray[owner].pendingResources[0x11] = bowStart - 1;
                DAT_BuildingsState::instance.buildings[buildingID].deliveryActivityCountdown = 100;
            }
            if (DAT_GameState::instance.playerDataArray[owner].pendingResources[0x12] > 0 && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getArmoryIDIfSpaceLeft, DAT_BuildingsState::ptr)(buildingID, 0x12, owner, 1) != 0) {
                int startAmount = DAT_GameState::instance.playerDataArray[owner].pendingResources[0x12];
                int* counterPtr = &DAT_GameState::instance.playerDataArray[owner].currentResources[0x12];
                *counterPtr = *counterPtr + 1;
                DAT_GameState::instance.playerDataArray[owner].pendingResources[0x12] = startAmount - 1;
                DAT_BuildingsState::instance.buildings[buildingID].resources[0x12] += 1;
                DAT_BuildingsState::instance.buildings[buildingID].deliveryActivityCountdown = 100;
                delivered = 1;
            }
            if (DAT_GameState::instance.playerDataArray[owner].pendingResources[0x13] > 0 && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getArmoryIDIfSpaceLeft, DAT_BuildingsState::ptr)(buildingID, 0x13, owner, 1) != 0) {
                int startAmount = DAT_GameState::instance.playerDataArray[owner].pendingResources[0x13];
                int* counterPtr = &DAT_GameState::instance.playerDataArray[owner].currentResources[0x13];
                *counterPtr = *counterPtr + 1;
                DAT_GameState::instance.playerDataArray[owner].pendingResources[0x13] = startAmount - 1;
                DAT_BuildingsState::instance.buildings[buildingID].resources[0x13] += 1;
                DAT_BuildingsState::instance.buildings[buildingID].deliveryActivityCountdown = 100;
                delivered = 1;
            }
            if (DAT_GameState::instance.playerDataArray[owner].pendingResources[0x14] > 0 && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getArmoryIDIfSpaceLeft, DAT_BuildingsState::ptr)(buildingID, 0x14, owner, 1) != 0) {
                int startAmount = DAT_GameState::instance.playerDataArray[owner].pendingResources[0x14];
                int* counterPtr = &DAT_GameState::instance.playerDataArray[owner].currentResources[0x14];
                *counterPtr = *counterPtr + 1;
                DAT_GameState::instance.playerDataArray[owner].pendingResources[0x14] = startAmount - 1;
                DAT_BuildingsState::instance.buildings[buildingID].resources[0x14] += 1;
                DAT_BuildingsState::instance.buildings[buildingID].deliveryActivityCountdown = 100;
                delivered = 1;
            }
            if (DAT_GameState::instance.playerDataArray[owner].pendingResources[0x15] > 0 && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getArmoryIDIfSpaceLeft, DAT_BuildingsState::ptr)(buildingID, 0x15, owner, 1) != 0) {
                int startAmount = DAT_GameState::instance.playerDataArray[owner].pendingResources[0x15];
                int* counterPtr = &DAT_GameState::instance.playerDataArray[owner].currentResources[0x15];
                *counterPtr = *counterPtr + 1;
                DAT_GameState::instance.playerDataArray[owner].pendingResources[0x15] = startAmount - 1;
                DAT_BuildingsState::instance.buildings[buildingID].resources[0x15] += 1;
                DAT_BuildingsState::instance.buildings[buildingID].deliveryActivityCountdown = 100;
                delivered = 1;
            }
            if (DAT_GameState::instance.playerDataArray[owner].pendingResources[0x16] > 0 && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getArmoryIDIfSpaceLeft, DAT_BuildingsState::ptr)(buildingID, 0x16, owner, 1) != 0) {
                int startAmount = DAT_GameState::instance.playerDataArray[owner].pendingResources[0x16];
                int* counterPtr = &DAT_GameState::instance.playerDataArray[owner].currentResources[0x16];
                *counterPtr = *counterPtr + 1;
                DAT_GameState::instance.playerDataArray[owner].pendingResources[0x16] = startAmount - 1;
                DAT_BuildingsState::instance.buildings[buildingID].resources[0x16] += 1;
                DAT_BuildingsState::instance.buildings[buildingID].deliveryActivityCountdown = 100;
                delivered = 1;
            }
            if (DAT_GameState::instance.playerDataArray[owner].pendingResources[0x17] > 0 && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getArmoryIDIfSpaceLeft, DAT_BuildingsState::ptr)(buildingID, 0x17, owner, 1) != 0) {
                int startAmount = DAT_GameState::instance.playerDataArray[owner].pendingResources[0x17];
                int* counterPtr = &DAT_GameState::instance.playerDataArray[owner].currentResources[0x17];
                *counterPtr = *counterPtr + 1;
                DAT_GameState::instance.playerDataArray[owner].pendingResources[0x17] = startAmount - 1;
                DAT_BuildingsState::instance.buildings[buildingID].resources[0x17] += 1;
                DAT_BuildingsState::instance.buildings[buildingID].deliveryActivityCountdown = 100;
                delivered = 1;
            }
            if (DAT_GameState::instance.playerDataArray[owner].pendingResources[0x18] > 0 && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getArmoryIDIfSpaceLeft, DAT_BuildingsState::ptr)(buildingID, 0x18, owner, 1) != 0) {
                DAT_GameState::instance.playerDataArray[owner].pendingResources[0x18] = DAT_GameState::instance.playerDataArray[owner].pendingResources[0x18] - 1;
                DAT_BuildingsState::instance.buildings[buildingID].resources[0x18] += 1;
                DAT_GameState::instance.playerDataArray[owner].currentResources[0x18] = 1;
                DAT_BuildingsState::instance.buildings[buildingID].deliveryActivityCountdown = 100;
            } else if (delivered == 0) {
                goto afterDelivery;
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::countPlayerResources, DAT_BuildingsState::ptr)(owner);
        }
    afterDelivery:
        if ((int)MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::computeResourceSumForBuilding,
                DAT_BuildingsState::ptr)(buildingID)
            < 10) {
            DAT_GameState::instance.playerDataArray[owner].isArmouryAlmostFilledUp = 0;
        }
        {
            short buildingOwner = DAT_BuildingsState::instance.buildings[buildingID].owner;
            if (DAT_GameState::instance.mapAndTime.playerTeams[buildingOwner]
                    == DAT_GameState::instance.mapAndTime
                           .playerTeams[(int)DAT_GameSynchronyState::instance.currentPlayerSlotID]
                || (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[buildingOwner] == -1
                    && DAT_GameSynchronyState::instance.currentAIArray[buildingOwner] != 0)) {
                if (DAT_BuildingsState::instance.buildings[buildingID].deliveryActivityCountdown != 0) {
                    DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive = 1;
                    DAT_BuildingsState::instance.buildings[buildingID].deliveryActivityCountdown -= 1;
                } else if (DAT_BuildingsState::instance.isFirstTickInLoop != 0) {
                    DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive = 0;
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updateVisuallyActiveState, DAT_BuildingsState::ptr)(
                    buildingID);
            }
        }
        DAT_BuildingsState::instance.buildings[buildingID].renderAnimation = 0;
        DAT_BuildingsState::instance.buildings[buildingID].showOverlays = 0;
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame4 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame6 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame12 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame14 = 0;
        int crossbowCount = DAT_BuildingsState::instance.buildings[buildingID].resources[0x12];
        int spearCount = DAT_BuildingsState::instance.buildings[buildingID].resources[0x13];
        int pikeCount = DAT_BuildingsState::instance.buildings[buildingID].resources[0x14];
        int bowCount = DAT_BuildingsState::instance.buildings[buildingID].resources[0x11];
        int maceCount = DAT_BuildingsState::instance.buildings[buildingID].resources[0x15];
        int swordCount = DAT_BuildingsState::instance.buildings[buildingID].resources[0x16];
        int leatherArmorCount = DAT_BuildingsState::instance.buildings[buildingID].resources[0x17];
        int metalArmorCount = DAT_BuildingsState::instance.buildings[buildingID].resources[0x18];
        if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY) {
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame11 = 0;
        } else {
            DAT_BuildingsState::instance.buildings[buildingID].showOverlays = 1;
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame13 += 1;
            if ((char)DAT_BuildingDefinedData::instance.ownerFlagFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayFrame13 / 2] <= 0) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame13 = 0;
            }
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame11 = (char)DAT_BuildingDefinedData::instance.ownerFlagFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayFrame13 / 2];
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive != DAT_BuildingsState::instance.buildings[buildingID].oldVisualActiveState) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                buildingID);
            buildingID = DAT_CurrentBuildingID::instance;
            DAT_BuildingsState::instance.buildings[buildingID].oldVisualActiveState = DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive;
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive != 0) {
            DAT_BuildingsState::instance.buildings[buildingID].showOverlays = 1;
            for (int pileSlot = 0; pileSlot < 4; pileSlot++) {
                int pileKind = 0;
                int pileAmount = 0;
                if (bowCount > 0) {
                    pileKind = 1;
                    pileAmount = bowCount;
                }
                if (crossbowCount > pileAmount) {
                    pileKind = 2;
                    pileAmount = crossbowCount;
                }
                if (spearCount > pileAmount) {
                    pileKind = 3;
                    pileAmount = spearCount;
                }
                if (pikeCount > pileAmount) {
                    pileKind = 4;
                    pileAmount = pikeCount;
                }
                if (maceCount > pileAmount) {
                    pileKind = 5;
                    pileAmount = maceCount;
                }
                if (swordCount > pileAmount) {
                    pileKind = 6;
                    pileAmount = swordCount;
                }
                if (metalArmorCount > pileAmount) {
                    pileKind = 7;
                    pileAmount = metalArmorCount;
                }
                if (leatherArmorCount > pileAmount) {
                    pileKind = 8;
                    pileAmount = leatherArmorCount;
                } else if (pileKind <= 0) {
                    return;
                }
                if (pileAmount > 0x10) {
                    pileAmount = 0x10;
                }
                if (pileKind == 1) {
                    bowCount -= pileAmount;
                    pileSprite = pileAmount + 0x20;
                } else if (pileKind == 2) {
                    crossbowCount -= pileAmount;
                    pileSprite = pileAmount + 0x30;
                } else if (pileKind == 3) {
                    spearCount -= pileAmount;
                    pileSprite = pileAmount + 0x40;
                } else if (pileKind == 4) {
                    pikeCount -= pileAmount;
                    pileSprite = pileAmount + 0x50;
                } else if (pileKind == 5) {
                    maceCount -= pileAmount;
                    pileSprite = pileAmount + 0x60;
                } else if (pileKind == 6) {
                    swordCount -= pileAmount;
                    pileSprite = pileAmount + 0x70;
                } else if (pileKind == 7) {
                    metalArmorCount -= pileAmount;
                    pileSprite = pileAmount;
                } else if (pileKind == 8) {
                    leatherArmorCount -= pileAmount;
                    pileSprite = pileAmount + 0x80;
                }
                if (pileSlot == 0) {
                    DAT_BuildingsState::instance.buildings[buildingID].overlayFrame4 = pileSprite;
                } else if (pileSlot == 1) {
                    DAT_BuildingsState::instance.buildings[buildingID].overlayFrame6 = pileSprite;
                } else if (pileSlot == 2) {
                    DAT_BuildingsState::instance.buildings[buildingID].overlayFrame12 = pileSprite;
                } else if (pileSlot == 3) {
                    DAT_BuildingsState::instance.buildings[buildingID].overlayFrame14 = pileSprite;
                }
            }
        }
    }

}
}