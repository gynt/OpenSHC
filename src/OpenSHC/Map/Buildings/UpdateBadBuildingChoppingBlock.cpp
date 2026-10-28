#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {

    // Every second tick (tickDivider > 1, signed jle at 0x4193D4): showOverlays = fearFactorLevel <= -4 (setle),
    // overlayAnimIndex0 steps through choppingBlockFrames (signed bytes, jg at 0x41940F) into overlayFrame0.
    // FUNCTION: STRONGHOLDCRUSADER 0x00419370
    void Buildings::UpdateBadBuildingChoppingBlock()
    {
        int buildingID = DAT_CurrentBuildingID::instance;
        int owner = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].ownerColorIndex = 0;
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(buildingID);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        buildingID = DAT_CurrentBuildingID::instance;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 0;
        DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha = 0;
        int* counterPtr = &DAT_BuildingsState::instance.buildings[buildingID].tickDivider;
        *counterPtr += 1;
        if (DAT_BuildingsState::instance.buildings[buildingID].tickDivider > 1) {
            int fear = DAT_GameState::instance.playerDataArray[owner].fearFactorLevel;
            DAT_BuildingsState::instance.buildings[buildingID].tickDivider = 0;
            DAT_BuildingsState::instance.buildings[buildingID].showOverlays = fear <= -4;
            counterPtr = &DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0;
            *counterPtr += 1;
            int frame = (char)DAT_BuildingDefinedData::instance
                            .choppingBlockFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0];
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame0 = frame;
            if (frame <= 0) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0 = 0;
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame0 = 1;
            }
        }
    }

}
}
