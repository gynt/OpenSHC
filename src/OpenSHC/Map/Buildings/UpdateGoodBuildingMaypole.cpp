#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"

namespace OpenSHC {
namespace Map {

    // randomSeed % 9 is signed (cdq; idiv at 0x418756); animated while fearFactorLevel > 0 (setg at 0x4187BA);
    // idle table while popularity < (randomSeed & 0xff) + 5000 (signed jge at 0x4187EE); frame tables are signed
    // bytes (movsx). FX_MAYPOLE every 8th finished dance cycle (test byte, 7 at 0x418851).
    // FUNCTION: STRONGHOLDCRUSADER 0x00418740
    void Buildings::UpdateGoodBuildingMaypole()
    {
        int buildingID = DAT_CurrentBuildingID::instance;
        int owner = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].ownerColorIndex
            = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].randomSeed % 9;
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(buildingID);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        buildingID = DAT_CurrentBuildingID::instance;
        DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha = 0;
        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updateWorkshopProgressSign,
            DAT_BuildingsState::ptr)(buildingID, 1);
        short* renderPtr = &DAT_BuildingsState::instance.buildings[buildingID].renderAnimation;
        *renderPtr = DAT_GameState::instance.playerDataArray[owner].fearFactorLevel > 0;
        DAT_BuildingsState::instance.buildings[buildingID].spriteOffetX = -0x23;
        DAT_BuildingsState::instance.buildings[buildingID].spriteOffetY = -0x4f;
        int* seedPtr = &DAT_BuildingsState::instance.buildings[buildingID].randomSeed;
        if (DAT_GameState::instance.playerDataArray[owner].popularity < (*seedPtr & 0xff) + 5000) {
            int idleFrame = (char)DAT_BuildingDefinedData::instance
                                .maypoleIdleFrames[DAT_BuildingsState::instance.buildings[buildingID].animationIndex]
                + 0x20;
            DAT_BuildingsState::instance.buildings[buildingID].animationFrame = idleFrame;
            if (idleFrame <= 0x20) {
                DAT_BuildingsState::instance.buildings[buildingID].animationIndex = 0;
                DAT_BuildingsState::instance.buildings[buildingID].animationFrame = 0x21;
                return;
            }
        } else {
            int danceFrame = (char)DAT_BuildingDefinedData::instance
                                 .maypoleDanceFrames[DAT_BuildingsState::instance.buildings[buildingID].animationIndex];
            DAT_BuildingsState::instance.buildings[buildingID].animationFrame = danceFrame;
            if (danceFrame <= 0) {
                int* cycleCountPtr = &DAT_BuildingsState::instance.buildings[buildingID].workCycleCount;
                *cycleCountPtr += 1;
                DAT_BuildingsState::instance.buildings[buildingID].animationIndex = 0;
                DAT_BuildingsState::instance.buildings[buildingID].animationFrame = 1;
                if ((*cycleCountPtr & 7) == 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[buildingID].x,
                        DAT_BuildingsState::instance.buildings[buildingID].y, OpenSHC::DE::SHCDE::FX_MAYPOLE);
                }
            }
        }
    }

}
}
