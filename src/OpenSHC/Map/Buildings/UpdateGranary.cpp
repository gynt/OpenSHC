#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    // computeResourceSumForBuilding (declared uint) is compared signed (cmp eax, 0xfa; jge at 0x4151C2 and
    // cmp eax, 0xe6; jge at 0x4152F9) -> (int) casts. The team test uses the local owner for playerTeams and the
    // building's owner for the AI arrays (0x41530F / 0x415330). The pile sprite starts as 1 (stack slot set at
    // 0x41514B); the pile loop returns when no kind was found (test ecx, ecx; jle at 0x415556), the chunk is capped
    // first (bread 32, cheese/meat 16, apples 8) and then taken from the chosen stock.
    // FUNCTION: STRONGHOLDCRUSADER 0x00415110
    void Buildings::UpdateGranary()
    {
        int delivered = 0;
        int edibleTotal = 0;
        int bread = 0;
        int cheese = 0;
        int meat = 0;
        int apples = 0;
        int owner = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        int pileFrame = 1;
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(
            DAT_CurrentBuildingID::instance);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        int buildingID = DAT_CurrentBuildingID::instance;
        if ((DAT_GameCore::instance.mapTimeInTicks & 3) == 0 && DAT_GameCore::instance.gameMode_2 != Game::GM_EDITOR
            && DAT_GameCore::instance.gameMode_2 != Game::GM_SIEGE_THAT
            && DAT_GameState::instance.playerDataArray[owner].goodsDeliveryDelay == 0) {
            int pending = DAT_GameState::instance.playerDataArray[owner].pendingResources[10];
            if (pending > 0
                && (int)MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::computeResourceSumForBuilding,
                       DAT_BuildingsState::ptr)(buildingID)
                    < 0xfa) {
                delivered = 1;
                DAT_GameState::instance.playerDataArray[owner].currentResources[10] += 1;
                DAT_BuildingsState::instance.buildings[buildingID].resources[10] += 1;
                DAT_GameState::instance.playerDataArray[owner].pendingResources[10] = pending - 1;
                DAT_BuildingsState::instance.buildings[buildingID].deliveryActivityCountdown = 100;
            }
            pending = DAT_GameState::instance.playerDataArray[owner].pendingResources[11];
            if (pending > 0
                && (int)MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::computeResourceSumForBuilding,
                       DAT_BuildingsState::ptr)(buildingID)
                    < 0xfa) {
                DAT_GameState::instance.playerDataArray[owner].pendingResources[11] = pending - 1;
                DAT_GameState::instance.playerDataArray[owner].currentResources[11] += 1;
                DAT_BuildingsState::instance.buildings[buildingID].resources[11] += 1;
                DAT_BuildingsState::instance.buildings[buildingID].deliveryActivityCountdown = 100;
                delivered = 1;
            }
            if (DAT_GameState::instance.playerDataArray[owner].pendingResources[12] > 0
                && (int)MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::computeResourceSumForBuilding,
                       DAT_BuildingsState::ptr)(buildingID)
                    < 0xfa) {
                int amount = DAT_GameState::instance.playerDataArray[owner].pendingResources[12];
                DAT_GameState::instance.playerDataArray[owner].currentResources[12] += 1;
                DAT_GameState::instance.playerDataArray[owner].pendingResources[12] = amount - 1;
                DAT_BuildingsState::instance.buildings[buildingID].resources[12] += 1;
                DAT_BuildingsState::instance.buildings[buildingID].deliveryActivityCountdown = 100;
                delivered = 1;
            }
            if (DAT_GameState::instance.playerDataArray[owner].pendingResources[13] > 0
                && (int)MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::computeResourceSumForBuilding,
                       DAT_BuildingsState::ptr)(buildingID)
                    < 0xfa) {
                int amount = DAT_GameState::instance.playerDataArray[owner].pendingResources[13];
                DAT_GameState::instance.playerDataArray[owner].currentResources[13] += 1;
                DAT_GameState::instance.playerDataArray[owner].pendingResources[13] = amount - 1;
                DAT_BuildingsState::instance.buildings[buildingID].resources[13] += 1;
                DAT_BuildingsState::instance.buildings[buildingID].deliveryActivityCountdown = 100;
            } else if (delivered == 0) {
                goto afterDelivery;
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::countPlayerResources, DAT_BuildingsState::ptr)(
                owner);
        }
    afterDelivery:
        if ((int)MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::computeResourceSumForBuilding,
                DAT_BuildingsState::ptr)(buildingID)
            < 0xe6) {
            DAT_GameState::instance.playerDataArray[owner].granaryIsAlmostFilledUp = FALSE;
        }
        if (DAT_GameState::instance.mapAndTime.playerTeams[owner]
                == DAT_GameState::instance.mapAndTime.playerTeams[(int)DAT_GameSynchronyState::instance.currentPlayerSlotID]
            || (DAT_GameSynchronyState::instance
                        .currentPlayerFullIDArray[DAT_BuildingsState::instance.buildings[buildingID].owner]
                    == -1
                && DAT_GameSynchronyState::instance.currentAIArray[DAT_BuildingsState::instance.buildings[buildingID].owner]
                    != 0)) {
            if (DAT_BuildingsState::instance.buildings[buildingID].deliveryActivityCountdown != 0) {
                DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive = 1;
                DAT_BuildingsState::instance.buildings[buildingID].deliveryActivityCountdown -= 1;
            } else if (DAT_BuildingsState::instance.isFirstTickInLoop != 0) {
                DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive = 0;
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updateVisuallyActiveState, DAT_BuildingsState::ptr)(
                buildingID);
        }
        DAT_BuildingsState::instance.buildings[buildingID].renderAnimation = 0;
        DAT_BuildingsState::instance.buildings[buildingID].showOverlays = 0;
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame0 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame1 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame2 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame3 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame4 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame5 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame6 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame7 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame8 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame9 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame10 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame11 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame12 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame13 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame14 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame15 = 0;
        if (DAT_GameState::instance.playerDataArray[owner].isFoodTypeBanned[0] == 0) {
            bread = DAT_BuildingsState::instance.buildings[buildingID].resources[10];
            if (bread != 0) {
                edibleTotal += bread;
            }
        }
        if (DAT_GameState::instance.playerDataArray[owner].isFoodTypeBanned[1] == 0) {
            cheese = DAT_BuildingsState::instance.buildings[buildingID].resources[11];
            if (cheese != 0) {
                edibleTotal += cheese;
            }
        }
        if (DAT_GameState::instance.playerDataArray[owner].isFoodTypeBanned[2] == 0) {
            meat = DAT_BuildingsState::instance.buildings[buildingID].resources[12];
            if (meat != 0) {
                edibleTotal += meat;
            }
        }
        if (DAT_GameState::instance.playerDataArray[owner].isFoodTypeBanned[3] == 0) {
            apples = DAT_BuildingsState::instance.buildings[buildingID].resources[13];
            if (apples != 0) {
                edibleTotal += apples;
            }
        }
        DAT_GameState::instance.playerDataArray[owner].cheeseCount += cheese;
        DAT_GameState::instance.playerDataArray[owner].appleCount += apples;
        DAT_GameState::instance.playerDataArray[owner].breadCount += bread;
        DAT_GameState::instance.playerDataArray[owner].meatCount += meat;
        DAT_GameState::instance.playerDataArray[owner].totalFood += edibleTotal;
        apples = DAT_BuildingsState::instance.buildings[buildingID].resources[13];
        meat = DAT_BuildingsState::instance.buildings[buildingID].resources[12];
        cheese = DAT_BuildingsState::instance.buildings[buildingID].resources[11];
        bread = DAT_BuildingsState::instance.buildings[buildingID].resources[10];
        if (DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive
            != DAT_BuildingsState::instance.buildings[buildingID].oldVisualActiveState) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                buildingID);
            buildingID = DAT_CurrentBuildingID::instance;
            DAT_BuildingsState::instance.buildings[buildingID].oldVisualActiveState
                = DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive;
        }
        if (apples + meat + cheese + bread > 0
            && DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive != 0) {
            DAT_BuildingsState::instance.buildings[buildingID].showOverlays = 1;
            for (int slot = 0; slot < 0x10; slot++) {
                int kind = 0;
                int largest = 0;
                if (bread > 0) {
                    kind = 1;
                    largest = bread;
                }
                if (cheese > largest) {
                    kind = 2;
                    largest = cheese;
                }
                if (meat > largest) {
                    kind = 3;
                    largest = meat;
                }
                if (apples > largest) {
                    kind = 4;
                    largest = apples;
                }
                if (kind <= 0) {
                    return;
                }
                if (kind == 1) {
                    if (largest > 0x20) {
                        largest = 0x20;
                    }
                } else if (kind == 2) {
                    if (largest > 0x10) {
                        largest = 0x10;
                    }
                } else if (kind == 3) {
                    if (largest > 0x10) {
                        largest = 0x10;
                    }
                } else if (kind == 4) {
                    if (largest > 8) {
                        largest = 8;
                    }
                }
                if (kind == 1) {
                    bread -= largest;
                    pileFrame = largest;
                } else if (kind == 2) {
                    cheese -= largest;
                    pileFrame = largest + 0xa0;
                } else if (kind == 3) {
                    meat -= largest;
                    pileFrame = largest + 0xb0;
                } else if (kind == 4) {
                    apples -= largest;
                    pileFrame = largest + 0x98;
                }
                if (slot == 0) {
                    DAT_BuildingsState::instance.buildings[buildingID].overlayFrame0 = pileFrame;
                } else if (slot == 1) {
                    DAT_BuildingsState::instance.buildings[buildingID].overlayFrame1 = pileFrame;
                } else if (slot == 2) {
                    DAT_BuildingsState::instance.buildings[buildingID].overlayFrame2 = pileFrame;
                } else if (slot == 3) {
                    DAT_BuildingsState::instance.buildings[buildingID].overlayFrame3 = pileFrame;
                } else if (slot == 4) {
                    DAT_BuildingsState::instance.buildings[buildingID].overlayFrame4 = pileFrame;
                } else if (slot == 5) {
                    DAT_BuildingsState::instance.buildings[buildingID].overlayFrame5 = pileFrame;
                } else if (slot == 6) {
                    DAT_BuildingsState::instance.buildings[buildingID].overlayFrame6 = pileFrame;
                } else if (slot == 7) {
                    DAT_BuildingsState::instance.buildings[buildingID].overlayFrame7 = pileFrame;
                } else if (slot == 8) {
                    DAT_BuildingsState::instance.buildings[buildingID].overlayFrame8 = pileFrame;
                } else if (slot == 9) {
                    DAT_BuildingsState::instance.buildings[buildingID].overlayFrame9 = pileFrame;
                } else if (slot == 10) {
                    DAT_BuildingsState::instance.buildings[buildingID].overlayFrame10 = pileFrame;
                } else if (slot == 11) {
                    DAT_BuildingsState::instance.buildings[buildingID].overlayFrame11 = pileFrame;
                } else if (slot == 12) {
                    DAT_BuildingsState::instance.buildings[buildingID].overlayFrame12 = pileFrame;
                } else if (slot == 13) {
                    DAT_BuildingsState::instance.buildings[buildingID].overlayFrame13 = pileFrame;
                } else if (slot == 14) {
                    DAT_BuildingsState::instance.buildings[buildingID].overlayFrame14 = pileFrame;
                } else if (slot == 15) {
                    DAT_BuildingsState::instance.buildings[buildingID].overlayFrame15 = pileFrame;
                }
            }
        }
    }

}
}
