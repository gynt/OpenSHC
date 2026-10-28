#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"

namespace OpenSHC {
namespace Map {

    // The same four sound checks appear three times in the original (0x410F5A, 0x4110B0, 0x4111C8).
#define PLAY_PITCH_RIG_SOUNDS() \
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationActive != 0) { \
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 3) { \
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)( \
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x, \
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y, \
                    OpenSHC::DE::SHCDE::FX_PITCH_SCOOP); \
            } \
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 0x14) { \
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)( \
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x, \
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y, \
                    OpenSHC::DE::SHCDE::FX_PITCH_POUR); \
            } \
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 1) { \
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)( \
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x, \
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y, \
                    OpenSHC::DE::SHCDE::FX_PITCH_WATERLAP); \
            } \
            short animationIndex = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex; \
            if (animationIndex == 10 || animationIndex == 0x19) { \
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)( \
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x, \
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y, \
                    OpenSHC::DE::SHCDE::FX_MUDBUB); \
            } \
        }

    // Frame tables are signed bytes (cmp al, bl; jg at 0x411043 / 0x411199 / 0x4112B1); animFadeAlpha and
    // animationIndex are signed shorts (jge 0x411076, jl 0x4111B3, jle 0x411347, jge 0x411357).
    // FUNCTION: STRONGHOLDCRUSADER 0x00410EE0
    void Buildings::UpdatePitchRig()
    {
        int buildingID = DAT_CurrentBuildingID::instance;
        int* counterPtr
            = &DAT_GameState::instance
                   .playerDataArray[DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner]
                   .countPitchRigs;
        *counterPtr = *counterPtr + 1;
        int animationEnded = 0;
        DAT_BuildingsState::instance.buildings[buildingID].renderAnimation
            = DAT_BuildingsState::instance.buildings[buildingID].workers[0] != 0;
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(buildingID);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        buildingID = DAT_CurrentBuildingID::instance;
        short state = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state;
        if (state == 0) {
            PLAY_PITCH_RIG_SOUNDS();
            buildingID = DAT_CurrentBuildingID::instance;
            char frame = DAT_BuildingDefinedData::instance
                             .pitchRigPhase0Frames[DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex];
            if (frame <= 0) {
                animationEnded = 1;
            } else {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = frame;
            }
            short animationIndex = DAT_BuildingsState::instance.buildings[buildingID].animationIndex;
            if (animationIndex == 0) {
                DAT_BuildingsState::instance.buildings[buildingID].animationFrame = 0;
                DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha = 0x1f;
            } else if (animationIndex < 0x1e) {
                DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha -= 1;
            } else {
                DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha = 0;
            }
        } else if (state == 1 || state == 2 || state == 3) {
            PLAY_PITCH_RIG_SOUNDS();
            buildingID = DAT_CurrentBuildingID::instance;
            char frame = DAT_BuildingDefinedData::instance
                             .pitchRigPhase123Frames[DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex];
            if (frame <= 0) {
                animationEnded = 1;
            } else {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = frame;
            }
            DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha = 0;
        } else if (state == 4) {
            PLAY_PITCH_RIG_SOUNDS();
            buildingID = DAT_CurrentBuildingID::instance;
            char frame = DAT_BuildingDefinedData::instance
                             .pitchRigPhase4Frames[DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex];
            if (frame <= 0) {
                animationEnded = 1;
            } else {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = frame;
            }
            short animationIndex = DAT_BuildingsState::instance.buildings[buildingID].animationIndex;
            if (animationIndex >= 0x28) {
                DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha = animationIndex - 0x28;
            }
        }
        if (animationEnded) {
            DAT_BuildingsState::instance.buildings[buildingID].animationIndex = 0;
            short phase = DAT_BuildingsState::instance.buildings[buildingID].state;
            if (phase == 0) {
                DAT_BuildingsState::instance.buildings[buildingID].state = 1;
            } else if (phase == 1) {
                DAT_BuildingsState::instance.buildings[buildingID].state = 2;
            } else if (phase == 2) {
                DAT_BuildingsState::instance.buildings[buildingID].state = 3;
            } else if (phase == 3) {
                DAT_BuildingsState::instance.buildings[buildingID].state = 4;
            } else if (phase == 4) {
                DAT_BuildingsState::instance.buildings[buildingID].workCycleCount += 1;
                DAT_BuildingsState::instance.buildings[buildingID].workCycleJustEnded = 1;
                DAT_BuildingsState::instance.buildings[buildingID].state = 0;
            }
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].animationIncrement != 0) {
            short fade = DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha;
            if (fade > 0x1f) {
                DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha = 0x1f;
            } else if (fade < 0) {
                DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha = 0;
            }
        } else {
            DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha = 0;
        }
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame0 = 0;
        if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY) {
            DAT_BuildingsState::instance.buildings[buildingID].showOverlays = 1;
            counterPtr = &DAT_BuildingsState::instance.buildings[buildingID].overlayFrame13;
            *counterPtr = *counterPtr + 1;
            if ((char)DAT_BuildingDefinedData::instance
                    .ownerFlagFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayFrame13 / 2]
                <= 0) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame13 = 0;
            }
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame14 = (char)DAT_BuildingDefinedData::instance
                .ownerFlagFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayFrame13 / 2];
            return;
        }
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame14 = 0;
    }

#undef PLAY_PITCH_RIG_SOUNDS

}
}
