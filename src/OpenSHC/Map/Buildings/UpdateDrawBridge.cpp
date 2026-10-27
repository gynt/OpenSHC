#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    // relativeRotation = buildingVariation - mapOrientation (+8 when negative); frame base table indexed by
    // relativeRotation / 2 (signed). Phase is tested 0, 2, 1, 3 in that order. Raise/lower frame tables are signed
    // bytes (entry <= 0 ends the phase). The building ID is re-read from DAT_CurrentBuildingID after every call.
    // FUNCTION: STRONGHOLDCRUSADER 0x00417B90
    void Buildings::UpdateDrawBridge()
    {
        int owner = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        int rotation = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingVariation
            - DAT_TileMapState::instance.mapOrientation;
        if (rotation < 0) {
            rotation += 8;
        }
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].showOverlays = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayFrame0 = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayFrame1 = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayFrame2 = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayFrame3 = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIncrement = 1;
        char phase = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].drawbridgePhase;
        if (phase == 0) {
            int baseFrame = DAT_BuildingDefinedData::instance.drawbridgeBaseFrameByRotation[rotation / 2];
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 1;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = baseFrame;
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].drawbridgeCommand == 10
                && MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isUnitBlockingSizeFiveFootprint,
                       DAT_TileMapState::ptr)(DAT_CurrentBuildingID::instance)
                    == FALSE) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].drawbridgePhase = 1;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex = 0;
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::floodMoatUnderRaisingDrawbridge,
                    DAT_TileMapState::ptr)(DAT_CurrentBuildingID::instance);
                DAT_GameState::instance.playerDataArray[owner].notLoweredDrawbridgeCount += 1;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].drawbridgeCommand = 12;
            }
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].showOverlays = 1;
            if (rotation == 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayFrame0 = 0x4f;
            } else if (rotation == 2) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayFrame1 = 0x50;
            } else if (rotation == 4) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayFrame2 = 0x4d;
            } else if (rotation == 6) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayFrame3 = 0x4e;
            }
        } else if (phase == 2) {
            DAT_GameState::instance.playerDataArray[owner].notLoweredDrawbridgeCount += 1;
            int baseFrame = DAT_BuildingDefinedData::instance.drawbridgeBaseFrameByRotation[rotation / 2];
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 1;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = baseFrame + 7;
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].drawbridgeCommand == 11) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].drawbridgePhase = 3;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex = 0;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].drawbridgeCommand = 12;
            }
        } else if (phase == 1) {
            DAT_GameState::instance.playerDataArray[owner].notLoweredDrawbridgeCount += 1;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 1;
            char frame = DAT_BuildingDefinedData::instance.drawbridgeRaiseFrames
                             [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex];
            if (frame <= 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].drawbridgePhase = 2;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex = 0;
            } else {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame
                    = frame + DAT_BuildingDefinedData::instance.drawbridgeBaseFrameByRotation[rotation / 2];
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 1
                    && DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationActive != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_DRAWBRIDGE_RAISING);
                }
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 0x18
                    && DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationActive != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_DRAWBRIDGE_RAISED);
                }
            }
        } else if (phase == 3) {
            DAT_GameState::instance.playerDataArray[owner].notLoweredDrawbridgeCount += 1;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 1;
            char frame = DAT_BuildingDefinedData::instance.drawbridgeLowerFrames
                             [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex];
            if (frame <= 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex = 0;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].drawbridgePhase = 0;
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::createWaterForDrawBridge, DAT_TileMapState::ptr)(
                    DAT_CurrentBuildingID::instance);
            } else {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame
                    = frame + DAT_BuildingDefinedData::instance.drawbridgeBaseFrameByRotation[rotation / 2];
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 1
                    && DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationActive != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_DRAWBRIDGE_CONTROL);
                }
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 5
                    && DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationActive != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_DRAWBRIDGE_LOWERING);
                }
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 0x1c
                    && DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationActive != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_DRAWBRIDGE_LOWERED);
                }
            }
        }
        if (rotation == 0) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteOffetX = -0x59;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteOffetY = -0x9a;
        } else if (rotation == 2) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteOffetX = -0x57;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteOffetY = -0x98;
        } else if (rotation == 4) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteOffetX = -0x65;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteOffetY = -0x99;
        } else if (rotation == 6) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteOffetX = -0x62;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteOffetY = -0x9c;
        }
    }

}
}
