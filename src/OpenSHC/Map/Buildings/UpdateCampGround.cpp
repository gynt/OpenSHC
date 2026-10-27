#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_SFX_Interval_Campfire.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    // DAT_SFX_Interval_Campfire and stateTimer are compared signed (the headers type them unsigned). The building ID
    // is re-read from DAT_CurrentBuildingID after every call.
    // FUNCTION: STRONGHOLDCRUSADER 0x00418100
    void Buildings::UpdateCampGround()
    {
        int owner = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIncrement = 1;
        if ((char)DAT_BuildingDefinedData::instance
                .campfireFrames[DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex]
            <= 0) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workCycleCount += 1;
            DAT_SFX_Interval_Campfire::instance += 1;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workCycleJustEnded = 1;
            if ((int)DAT_SFX_Interval_Campfire::instance >= 1) {
                DAT_SFX_Interval_Campfire::instance = 0;
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                    OpenSHC::DE::SHCDE::FX_CAMPFIRE);
            }
        }
        int hoverTile = DAT_ViewportRenderState::instance.viewportState.mouseAtomRefFloorTile;
        if (hoverTile != 0 && DAT_TileMapState::instance.BuildingLayer[hoverTile] == DAT_CurrentBuildingID::instance) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].showOverlays = 1;
        } else {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].showOverlays = 0;
        }
        int vclock = DAT_GameState::instance.playerDataArray[owner].vclock;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayAnimIndex0 = vclock;
        if (vclock < 0) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayAnimIndex0 = 0;
        } else if (vclock > 4000) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayAnimIndex0 = 4000;
        }
        int level = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayAnimIndex0 / 40 - 50;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayAnimIndex0 = level;
        if (level < 0) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayFrame0
                = DAT_BuildingDefinedData::instance.field416_0xa46c[-level] + 0x33;
        } else {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayFrame0
                = DAT_BuildingDefinedData::instance.field415_0xa39c[level];
        }
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campIdlePeasantCount != 0) {
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation == 0) {
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayFrame15 >= 40) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 1;
                }
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayFrame15 += 1;
            } else {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayFrame15 = 40;
            }
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame
                = (char)DAT_BuildingDefinedData::instance.campfireFrames
                      [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex]
                + 0xb;
        } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campArrivingPeasantCount != 0) {
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation == 0) {
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayFrame15 >= 40) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 1;
                }
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayFrame15 += 1;
            } else {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayFrame15 = 40;
            }
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame
                = (char)DAT_BuildingDefinedData::instance.campfireFrames
                      [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex]
                + 0xb;
        } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation != 0) {
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayFrame15 <= 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 0;
            }
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayFrame15 -= 1;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame
                = (char)DAT_BuildingDefinedData::instance.campfireFrames
                      [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex]
                + 0xb;
        } else {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayFrame15 = 0;
        }
        short idleCount = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campIdlePeasantCount;
        if (idleCount <= 1) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campActivityState = 1;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campPrevActivityState = 1;
        } else if (idleCount <= 4) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campActivityState = 3;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campPrevActivityState = 3;
        } else {
            short activity = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campActivityState;
            if (activity == 3) {
                if ((int)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].stateTimer > 1000) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].stateTimer = 0;
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campPrevActivityState
                        = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campActivityState;
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campActivityState = 5;
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingProgress = 0;
                }
            } else if (activity == 2) {
                if ((int)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].stateTimer > 200) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].stateTimer = 0;
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campPrevActivityState
                        = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campActivityState;
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campActivityState = 4;
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingProgress = 0;
                }
            } else if (activity == 4) {
                if ((int)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].stateTimer > 600) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].stateTimer = 0;
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campPrevActivityState
                        = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campActivityState;
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campActivityState = 3;
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingProgress = 0;
                }
            } else if (activity == 5) {
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].stateTimer == 1) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::updatePeasantSeatingAtBuilding,
                        DAT_TribesState::ptr)(DAT_CurrentBuildingID::instance, idleCount, 1);
                } else if ((int)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].stateTimer > 300) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].stateTimer = 0;
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingProgress += 1;
                    int next;
                    if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingProgress > 5) {
                        next = 6;
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingProgress = 0;
                    } else {
                        next = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campActivityState;
                    }
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campPrevActivityState
                        = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campActivityState;
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campActivityState = next;
                }
            } else if (activity == 6) {
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].stateTimer == 1) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::updatePeasantSeatingAtBuilding,
                        DAT_TribesState::ptr)(DAT_CurrentBuildingID::instance, idleCount, 100);
                } else if ((int)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].stateTimer > 80) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].stateTimer = 0;
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingProgress += 1;
                    int next;
                    if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingProgress > 12) {
                        next = 2;
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingProgress = 0;
                    } else {
                        next = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campActivityState;
                    }
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campPrevActivityState
                        = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campActivityState;
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campActivityState = next;
                }
            }
        }
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campIdlePeasantCount = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campArrivingPeasantCount = 0;
    }

}
}
