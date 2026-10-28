#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    // Same code as UpdateGateHouseLarge except accessTileX = x + 3 and only overlayFrame2/3 (0xB / 0xC by facing)
    // are set as static sub-sprites (asm compared line by line with 0x4238B0).
    // FUNCTION: STRONGHOLDCRUSADER 0x00423CD0
    void Buildings::UpdateGateHouseSmall()
    {
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        int variant = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingVariation;
        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updateGateDrawBridgeOpenCloseLogic,
            DAT_BuildingsState::ptr)();
        int buildingID = DAT_CurrentBuildingID::instance;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].accessTileX
            = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x + 3;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].accessTileY
            = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y + 2;
        if (DAT_TileMapState::instance.mapOrientation == 2 || DAT_TileMapState::instance.mapOrientation == 6) {
            variant = variant + 1;
        }
        if (variant > 0x51) {
            variant = 0x50;
        }
        DAT_BuildingsState::instance.buildings[buildingID].renderAnimation = 0;
        DAT_BuildingsState::instance.buildings[buildingID].showOverlays = 1;
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame0 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame1 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame2 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame3 = 0;
        if (variant == 0x50) {
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame2 = 0xb;
        } else {
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame3 = 0xc;
        }
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame8 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame9 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame10 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame11 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame12 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame13 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame14 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame15 = 0;
        int decals[4];
        decals[0] = decals[1] = decals[2] = decals[3] = 0;
        int damage = 5
            - DAT_BuildingsState::instance.buildings[buildingID].currentHealth * 5
                / DAT_BuildingsState::instance.buildings[buildingID].maxHealth;
        if (damage > 4) {
            damage = 4;
        }
        if (damage != 0) {
            if (damage > 0) {
                int seed = DAT_BuildingsState::instance.buildings[buildingID].randomSeed;
                int slotSeed = seed >> 8;
                do {
                    decals[slotSeed & 3] = (seed & 0xf) + 1;
                    seed = seed + 1;
                    slotSeed = slotSeed + 1;
                    damage = damage - 1;
                } while (damage != 0);
            }
            if (variant == 0x50) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame8 = decals[0];
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame9 = decals[1];
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame10 = decals[2];
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame11 = decals[3];
            } else {
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame12 = decals[0];
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame13 = decals[1];
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame14 = decals[2];
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame15 = decals[3];
            }
        }
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame4 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame5 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].animationIncrement = 1;
        DAT_BuildingsState::instance.buildings[buildingID].renderAnimation = 1;
        byte phase = DAT_BuildingsState::instance.buildings[buildingID].gateOpenState;
        if (phase == 0) {
            if (DAT_BuildingsState::instance.buildings[buildingID].gateState == 10) {
                DAT_BuildingsState::instance.buildings[buildingID].gateOpenState = 1;
                DAT_BuildingsState::instance.buildings[buildingID].gateState = 0xc;
                DAT_BuildingsState::instance.buildings[buildingID].animationIndex = 0;
            }
        } else if (phase == 2) {
            if (DAT_BuildingsState::instance.buildings[buildingID].gateState == 0xb) {
                DAT_BuildingsState::instance.buildings[buildingID].gateOpenState = 3;
                DAT_BuildingsState::instance.buildings[buildingID].gateState = 0xc;
                DAT_BuildingsState::instance.buildings[buildingID].animationIndex = 0;
            }
            if (variant == 0x50) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame4 = 0xc;
            } else {
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame5 = 6;
            }
        } else if (phase == 1) {
            if (DAT_BuildingsState::instance.buildings[buildingID].animationActive != 0) {
                if (DAT_BuildingsState::instance.buildings[buildingID].animationIndex == 1) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[buildingID].x,
                        DAT_BuildingsState::instance.buildings[buildingID].y, OpenSHC::DE::SHCDE::FX_PC_DROP);
                }
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 0x14) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_PC_SLAM);
                }
            }
            buildingID = DAT_CurrentBuildingID::instance;
            char frame = DAT_BuildingDefinedData::instance
                             .gatehouseCloseFrames[DAT_BuildingsState::instance.buildings[buildingID].animationIndex];
            if (frame <= 0) {
                DAT_BuildingsState::instance.buildings[buildingID].gateOpenState = 2;
                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkageTileMapRelatedToGates,
                    DAT_PathFindingState::ptr)(buildingID);
                if (variant == 0x50) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayFrame4 = 0xc;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayFrame5 = 6;
                }
            } else if (variant == 0x50) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame4 = frame + 6;
            } else {
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame5 = frame;
            }
        } else if (phase == 3) {
            if (DAT_BuildingsState::instance.buildings[buildingID].animationActive != 0
                && DAT_BuildingsState::instance.buildings[buildingID].animationIndex == 1) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_BuildingsState::instance.buildings[buildingID].x,
                    DAT_BuildingsState::instance.buildings[buildingID].y, OpenSHC::DE::SHCDE::FX_PC_LIFT);
            }
            buildingID = DAT_CurrentBuildingID::instance;
            char frame = DAT_BuildingDefinedData::instance
                             .gatehouseOpenFrames[DAT_BuildingsState::instance.buildings[buildingID].animationIndex];
            if (frame <= 0) {
                DAT_BuildingsState::instance.buildings[buildingID].gateOpenState = 0;
                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkageTileMapRelatedToGates,
                    DAT_PathFindingState::ptr)(buildingID);
            } else if (variant == 0x50) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame4 = frame + 6;
            } else {
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame5 = frame;
            }
        }
    }

}
}
