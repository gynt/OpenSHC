#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {

#define QUARRY_SFX(id, sound) \
    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)( \
        DAT_BuildingsState::instance.buildings[id].x, DAT_BuildingsState::instance.buildings[id].y, sound)

    // Every 2nd tick in GM_SOLITARY, every tick otherwise (tickDivider == 1 returns only in solitary, 0x41D5A5).
    // workers[1] = puller (layer A: state), workers[0] = pryer (layer C: subAnimState2), workers[2] = mason
    // (layer D: subAnimState3); layer B (subAnimState1, the stone block) has no worker check. Layers A, C and D
    // freeze on a fixed frame while fewer than 3 workers are present. All frame tests are signed bytes (jg).
    // The pryer picks its next lever cycle from (byte)SEC_RNG.currentNumber2 & 3 read at entry; after cycle 11
    // it restarts only while linkedBuildingID's stockpile holds < 47 stone (jge 0x41DEAF). A finished mason
    // cycle (states 1..4, jg 0x41E1A6) adds 1 stone to the linked stockpile.
    // FUNCTION: STRONGHOLDCRUSADER 0x0041D510
    void Buildings::UpdateQuarry()
    {
        int rngBits = (byte)SEC_RNG::instance.currentNumber2 & 3;
        int buildingID = DAT_CurrentBuildingID::instance;
        OpenSHC::Map::Buildings::Building* quarry = &DAT_BuildingsState::instance.buildings[buildingID];
        int stockpileID = (short)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].linkedBuildingID;
        DAT_GameState::instance.playerDataArray[DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner]
            .countStoneQuarries
            += 1;
        int workerCount = 0;
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(buildingID);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        buildingID = DAT_CurrentBuildingID::instance;
        quarry = &DAT_BuildingsState::instance.buildings[buildingID];
        quarry->renderAnimation = 0;
        quarry->showOverlays = 1;
        DAT_BuildingsState::instance.buildings[buildingID].tickDivider += 1;
        if (DAT_BuildingsState::instance.buildings[buildingID].tickDivider > 1) {
            DAT_BuildingsState::instance.buildings[buildingID].tickDivider = 0;
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].tickDivider == 1
            && DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY) {
            return;
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].workers[0] != 0) {
            workerCount += 1;
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].workers[1] != 0) {
            workerCount += 1;
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].workers[2] != 0) {
            workerCount += 1;
        }

        // Layer A: the puller.
        int finished = 0;
        char frame;
        if (DAT_BuildingsState::instance.buildings[buildingID].workers[1] == 0) {
            quarry->state = 0;
            DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0 = 0;
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame0 = 0;
            goto layerB;
        }
        if (workerCount < 3) {
            quarry->state = 0;
            DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0 = 0;
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame0 = 1;
            goto layerB;
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].state == 0) {
            DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0 = 0;
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame0 = 1;
            goto resetA;
        } else if (DAT_BuildingsState::instance.buildings[buildingID].state == 1) {
            DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0 += 1;
            frame = (char)DAT_BuildingDefinedData::instance
                        .quarryPullerLowerFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0];
            if (frame <= 0) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0 = 0;
                finished = 1;
            } else {
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame0 = frame;
            }
            if (DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0 == 1) {
                QUARRY_SFX(buildingID, OpenSHC::DE::SHCDE::FX_PULLER_LOWER);
            }
        } else if (DAT_BuildingsState::instance.buildings[buildingID].state == 2) {
            DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0 = 0;
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame0 = 0x21;
            goto resetA;
        } else if (DAT_BuildingsState::instance.buildings[buildingID].state == 3) {
            DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0 += 1;
            frame = (char)DAT_BuildingDefinedData::instance
                        .quarryPullerStrainFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0];
            if (frame <= 0) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0 = 0;
                finished = 1;
            } else {
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame0 = frame + 1;
            }
            if (DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0 == 3) {
                QUARRY_SFX(buildingID, OpenSHC::DE::SHCDE::FX_PULLER_STRAIN);
            }
            buildingID = DAT_CurrentBuildingID::instance;
            quarry = &DAT_BuildingsState::instance.buildings[buildingID];
            if (DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0 == 0x38) {
                QUARRY_SFX(buildingID, OpenSHC::DE::SHCDE::FX_PULLER_IMPACT);
            }
        } else if (DAT_BuildingsState::instance.buildings[buildingID].state == 4) {
            DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0 = 0;
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame0 = 0x12;
            goto resetA;
        } else if (DAT_BuildingsState::instance.buildings[buildingID].state == 5) {
            DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0 += 1;
            frame = (char)DAT_BuildingDefinedData::instance
                        .quarryPullerRockFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0];
            if (frame <= 0) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0 = 0;
                finished = 1;
            } else {
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame0 = frame + 1;
            }
            if (DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0 == 1) {
                QUARRY_SFX(buildingID, OpenSHC::DE::SHCDE::FX_PULLER_ROCK);
            }
        } else if (DAT_BuildingsState::instance.buildings[buildingID].state == 6) {
            DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0 += 1;
            frame = (char)DAT_BuildingDefinedData::instance
                        .quarryPullerReturnFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0];
            if (frame <= 0) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0 = 0;
                finished = 1;
            } else {
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame0 = frame + 1;
            }
            if (DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0 == 1) {
                QUARRY_SFX(buildingID, OpenSHC::DE::SHCDE::FX_PULLER_RETURN);
            }
        } else {
            goto layerB;
        }
        if (finished == 0) {
            goto layerB;
        }
    resetA:
        buildingID = DAT_CurrentBuildingID::instance;
        quarry = &DAT_BuildingsState::instance.buildings[buildingID];
        if (DAT_BuildingsState::instance.buildings[buildingID].state == 0) {
            if (DAT_BuildingsState::instance.buildings[buildingID].subAnimState2 == 7) {
                DAT_BuildingsState::instance.buildings[buildingID].state = 1;
            }
        } else if (DAT_BuildingsState::instance.buildings[buildingID].state == 1) {
            DAT_BuildingsState::instance.buildings[buildingID].state = 2;
        } else if (DAT_BuildingsState::instance.buildings[buildingID].state == 2) {
            if (DAT_BuildingsState::instance.buildings[buildingID].subAnimState2 == 9) {
                DAT_BuildingsState::instance.buildings[buildingID].state = 3;
            }
        } else if (DAT_BuildingsState::instance.buildings[buildingID].state == 3) {
            DAT_BuildingsState::instance.buildings[buildingID].state = 4;
        } else if (DAT_BuildingsState::instance.buildings[buildingID].state == 4) {
            if (DAT_BuildingsState::instance.buildings[buildingID].subAnimState3 == 0) {
                DAT_BuildingsState::instance.buildings[buildingID].state = 5;
            }
        } else if (DAT_BuildingsState::instance.buildings[buildingID].state == 5) {
            DAT_BuildingsState::instance.buildings[buildingID].state = 6;
        } else if (DAT_BuildingsState::instance.buildings[buildingID].state == 6) {
            DAT_BuildingsState::instance.buildings[buildingID].state = 0;
        }

    layerB:
        // Layer B: the stone block.
        buildingID = DAT_CurrentBuildingID::instance;
        quarry = &DAT_BuildingsState::instance.buildings[buildingID];
        if (DAT_BuildingsState::instance.buildings[buildingID].subAnimState1 == 0) {
            quarry->overlayAnimIndex1 = 0;
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame1 = 0x7a;
            goto resetB;
        } else if (DAT_BuildingsState::instance.buildings[buildingID].subAnimState1 == 1) {
            DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex1 += 1;
            frame = (char)DAT_BuildingDefinedData::instance
                        .quarryBlockPhase1Frames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex1];
            if (frame > 0) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame1 = frame + 0x3d;
                goto layerC;
            }
            goto blockFinished;
        } else if (DAT_BuildingsState::instance.buildings[buildingID].subAnimState1 == 2) {
            quarry->overlayAnimIndex1 = 0;
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame1 = 0x55;
            goto resetB;
        } else if (DAT_BuildingsState::instance.buildings[buildingID].subAnimState1 == 3) {
            DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex1 += 1;
            frame = (char)DAT_BuildingDefinedData::instance
                        .quarryBlockPhase3Frames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex1];
            if (frame > 0) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame1 = frame + 0x53;
                goto layerC;
            }
            goto blockFinished;
        } else if (DAT_BuildingsState::instance.buildings[buildingID].subAnimState1 == 4) {
            quarry->overlayAnimIndex1 = 0;
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame1 = 0x66;
            goto resetB;
        } else if (DAT_BuildingsState::instance.buildings[buildingID].subAnimState1 == 5) {
            DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex1 += 1;
            frame = (char)DAT_BuildingDefinedData::instance
                        .quarryBlockAnimState5Frames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex1];
            if (frame > 0) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame1 = frame + 0x66;
                goto layerC;
            }
            goto blockFinished;
        } else if (DAT_BuildingsState::instance.buildings[buildingID].subAnimState1 == 6) {
            DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex1 += 1;
            frame = (char)DAT_BuildingDefinedData::instance
                        .quarryBlockPhase6Frames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex1];
            if (frame > 0) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame1 = frame + 0x6c;
                goto layerC;
            }
            goto blockFinished;
        } else {
            goto layerC;
        }
    blockFinished:
        DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex1 = 0;
    resetB:
        if (DAT_BuildingsState::instance.buildings[buildingID].subAnimState1 == 0) {
            if (DAT_BuildingsState::instance.buildings[buildingID].subAnimState2 == 7) {
                DAT_BuildingsState::instance.buildings[buildingID].subAnimState1 = 1;
            }
        } else if (DAT_BuildingsState::instance.buildings[buildingID].subAnimState1 == 1) {
            DAT_BuildingsState::instance.buildings[buildingID].subAnimState1 = 2;
        } else if (DAT_BuildingsState::instance.buildings[buildingID].subAnimState1 == 2) {
            if (DAT_BuildingsState::instance.buildings[buildingID].subAnimState2 == 9) {
                DAT_BuildingsState::instance.buildings[buildingID].subAnimState1 = 3;
            }
        } else if (DAT_BuildingsState::instance.buildings[buildingID].subAnimState1 == 3) {
            DAT_BuildingsState::instance.buildings[buildingID].subAnimState1 = 4;
        } else if (DAT_BuildingsState::instance.buildings[buildingID].subAnimState1 == 4) {
            if (DAT_BuildingsState::instance.buildings[buildingID].subAnimState3 == 0) {
                DAT_BuildingsState::instance.buildings[buildingID].subAnimState1 = 5;
            }
        } else if (DAT_BuildingsState::instance.buildings[buildingID].subAnimState1 == 5) {
            DAT_BuildingsState::instance.buildings[buildingID].subAnimState1 = 6;
        } else if (DAT_BuildingsState::instance.buildings[buildingID].subAnimState1 == 6) {
            DAT_BuildingsState::instance.buildings[buildingID].subAnimState1 = 0;
        }

    layerC:
        // Layer C: the pryer.
        finished = 0;
        if (DAT_BuildingsState::instance.buildings[buildingID].workers[0] == 0) {
            quarry->subAnimState2 = 0;
            DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2 = 0;
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame2 = 0;
            goto layerD;
        }
        if (workerCount < 3) {
            quarry->subAnimState2 = 0;
            DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2 = 0;
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame2 = 0x7b;
            goto layerD;
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].subAnimState2 == 0) {
            DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2 += 1;
            frame = (char)DAT_BuildingDefinedData::instance
                        .quarryPryerIdleFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2];
            if (frame <= 0) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2 = 0;
                goto resetC;
            }
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame2 = frame + 0x7a;
            goto layerD;
        } else if (DAT_BuildingsState::instance.buildings[buildingID].subAnimState2 == 1) {
            DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2 += 1;
            frame = (char)DAT_BuildingDefinedData::instance
                        .quarryPryerPhase1Frames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2];
            if (frame <= 0) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2 = 0;
                goto resetC;
            }
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame2 = frame + 0x7a;
            goto layerD;
        } else if (DAT_BuildingsState::instance.buildings[buildingID].subAnimState2 == 2) {
            DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2 += 1;
            frame = (char)DAT_BuildingDefinedData::instance
                        .quarryPryerPhase2Frames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2];
            if (frame <= 0) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2 = 0;
                goto resetC;
            }
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame2 = frame + 0x7a;
            goto layerD;
        } else if (DAT_BuildingsState::instance.buildings[buildingID].subAnimState2 == 3) {
            DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2 += 1;
            frame = (char)DAT_BuildingDefinedData::instance
                        .quarryPryerLever3Frames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2];
            if (frame <= 0) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2 = 0;
                finished = 1;
            } else {
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame2 = frame + 0x86;
            }
            if (DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2 == 1) {
                QUARRY_SFX(buildingID, OpenSHC::DE::SHCDE::FX_PRYER_LEVER);
            }
        } else if (DAT_BuildingsState::instance.buildings[buildingID].subAnimState2 == 4) {
            DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2 += 1;
            frame = (char)DAT_BuildingDefinedData::instance
                        .quarryPryerLever4Frames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2];
            if (frame <= 0) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2 = 0;
                finished = 1;
            } else {
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame2 = frame + 0x86;
            }
            if (DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2 == 1) {
                QUARRY_SFX(buildingID, OpenSHC::DE::SHCDE::FX_PRYER_LEVER);
            }
            buildingID = DAT_CurrentBuildingID::instance;
            quarry = &DAT_BuildingsState::instance.buildings[buildingID];
            if (DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2 == 0x17) {
                QUARRY_SFX(buildingID, OpenSHC::DE::SHCDE::FX_PRYER_LEVER);
            }
        } else if (DAT_BuildingsState::instance.buildings[buildingID].subAnimState2 == 5) {
            DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2 += 1;
            frame = (char)DAT_BuildingDefinedData::instance
                        .quarryPryerLever5Frames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2];
            if (frame <= 0) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2 = 0;
                finished = 1;
            } else {
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame2 = frame + 0x86;
            }
            if (DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2 == 1) {
                QUARRY_SFX(buildingID, OpenSHC::DE::SHCDE::FX_PRYER_LEVER);
            }
            buildingID = DAT_CurrentBuildingID::instance;
            quarry = &DAT_BuildingsState::instance.buildings[buildingID];
            if (DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2 == 0x17) {
                QUARRY_SFX(buildingID, OpenSHC::DE::SHCDE::FX_PRYER_LEVER);
            }
            buildingID = DAT_CurrentBuildingID::instance;
            quarry = &DAT_BuildingsState::instance.buildings[buildingID];
            if (DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2 == 0x2d) {
                QUARRY_SFX(buildingID, OpenSHC::DE::SHCDE::FX_PRYER_LEVER);
            }
        } else if (DAT_BuildingsState::instance.buildings[buildingID].subAnimState2 == 6) {
            DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2 += 1;
            frame = (char)DAT_BuildingDefinedData::instance
                        .quarryPryerLever6Frames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2];
            if (frame <= 0) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2 = 0;
                finished = 1;
            } else {
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame2 = frame + 0x86;
            }
            if (DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2 == 0x18) {
                QUARRY_SFX(buildingID, OpenSHC::DE::SHCDE::FX_PRYER_LEVER);
            }
            buildingID = DAT_CurrentBuildingID::instance;
            quarry = &DAT_BuildingsState::instance.buildings[buildingID];
            if (DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2 == 0x38) {
                QUARRY_SFX(buildingID, OpenSHC::DE::SHCDE::FX_PRYER_LEVER);
            }
        } else if (DAT_BuildingsState::instance.buildings[buildingID].subAnimState2 == 7) {
            quarry->overlayAnimIndex2 = 0;
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame2 = 0x8d;
            goto resetC;
        } else if (DAT_BuildingsState::instance.buildings[buildingID].subAnimState2 == 8) {
            DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2 += 1;
            frame = (char)DAT_BuildingDefinedData::instance
                        .quarryPryerPhase8Frames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2];
            if (frame <= 0) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2 = 0;
                goto resetC;
            }
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame2 = frame + 0x8d;
            goto layerD;
        } else if (DAT_BuildingsState::instance.buildings[buildingID].subAnimState2 == 9) {
            DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2 += 1;
            frame = (char)DAT_BuildingDefinedData::instance
                        .quarryPryerPhase9Frames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2];
            if (frame <= 0) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2 = 0;
                goto resetC;
            }
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame2 = frame + 0xa5;
            goto layerD;
        } else if (DAT_BuildingsState::instance.buildings[buildingID].subAnimState2 == 10) {
            DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2 += 1;
            frame = (char)DAT_BuildingDefinedData::instance
                        .quarryPryerPhase10Frames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2];
            if (frame <= 0) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2 = 0;
                goto resetC;
            }
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame2 = frame + 0xb9;
            goto layerD;
        } else if (DAT_BuildingsState::instance.buildings[buildingID].subAnimState2 == 11) {
            DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2 += 1;
            if (DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2 >= 10) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2 = 0;
                finished = 1;
            }
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame2 = 0xbf;
        } else {
            goto layerD;
        }
        if (finished == 0) {
            goto layerD;
        }
    resetC: {
        buildingID = DAT_CurrentBuildingID::instance;
        quarry = &DAT_BuildingsState::instance.buildings[buildingID];
        short pryerState = DAT_BuildingsState::instance.buildings[buildingID].subAnimState2;
        if (pryerState < 3) {
            DAT_BuildingsState::instance.buildings[buildingID].subAnimState2 = (short)(rngBits + 3);
        } else if (pryerState < 7) {
            DAT_BuildingsState::instance.buildings[buildingID].subAnimState2 = 7;
        } else if (pryerState < 8) {
            if (DAT_BuildingsState::instance.buildings[buildingID].subAnimState1 == 2) {
                DAT_BuildingsState::instance.buildings[buildingID].subAnimState2 = 8;
            }
        } else if (pryerState < 9) {
            DAT_BuildingsState::instance.buildings[buildingID].subAnimState2 = 9;
        } else if (pryerState < 10) {
            DAT_BuildingsState::instance.buildings[buildingID].subAnimState2 = 10;
        } else if (pryerState < 11) {
            DAT_BuildingsState::instance.buildings[buildingID].subAnimState2 = 11;
        } else if (pryerState < 12) {
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingResourceAmountByUid,
                    DAT_BuildingsState::ptr)(stockpileID, DAT_BuildingsState::instance.buildings[stockpileID].uid,
                    OpenSHC::Game::Resources::RT_STONE)
                < 0x2f) {
                if (rngBits == 0) {
                    DAT_BuildingsState::instance.buildings[buildingID].subAnimState2 = 0;
                } else {
                    DAT_BuildingsState::instance.buildings[buildingID].subAnimState2 = (rngBits == 1) ? 2 : 1;
                }
            }
        }
    }

    layerD:
        // Layer D: the mason.
        buildingID = DAT_CurrentBuildingID::instance;
        quarry = &DAT_BuildingsState::instance.buildings[buildingID];
        finished = 0;
        if (DAT_BuildingsState::instance.buildings[buildingID].workers[2] == 0) {
            quarry->subAnimState3 = 0;
            DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex3 = 0;
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame3 = 0;
            goto ownerFlag;
        }
        if (workerCount < 3) {
            quarry->subAnimState3 = 0;
            quarry->overlayAnimIndex3 = 0;
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame3 = 0xc1;
            goto ownerFlag;
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].subAnimState3 == 0) {
            quarry->overlayAnimIndex3 = 0;
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame3 = 0xc1;
            goto resetD;
        } else if (DAT_BuildingsState::instance.buildings[buildingID].subAnimState3 == 1) {
            DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex3 += 1;
            frame = (char)DAT_BuildingDefinedData::instance
                        .quarryMasonChipFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex3];
            if (frame <= 0) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex3 = 0;
                finished = 1;
            } else {
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame3 = frame + 0xc1;
            }
            if (DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex3 == 0x2a) {
                QUARRY_SFX(buildingID, OpenSHC::DE::SHCDE::FX_MASON_CHIP);
                buildingID = DAT_CurrentBuildingID::instance;
                quarry = &DAT_BuildingsState::instance.buildings[buildingID];
            }
            if (DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex3 == 0x34) {
                QUARRY_SFX(buildingID, OpenSHC::DE::SHCDE::FX_MASON_CHIP);
                buildingID = DAT_CurrentBuildingID::instance;
                quarry = &DAT_BuildingsState::instance.buildings[buildingID];
            }
            if (DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex3 == 0x41) {
                QUARRY_SFX(buildingID, OpenSHC::DE::SHCDE::FX_MASON_CRUMBLE);
                buildingID = DAT_CurrentBuildingID::instance;
                quarry = &DAT_BuildingsState::instance.buildings[buildingID];
            }
            if (DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex3 == 0x64) {
                QUARRY_SFX(buildingID, OpenSHC::DE::SHCDE::FX_MASON_CHIP);
                buildingID = DAT_CurrentBuildingID::instance;
                quarry = &DAT_BuildingsState::instance.buildings[buildingID];
            }
            if (DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex3 == 0x73) {
                QUARRY_SFX(buildingID, OpenSHC::DE::SHCDE::FX_MASON_CRUMBLE);
                buildingID = DAT_CurrentBuildingID::instance;
                quarry = &DAT_BuildingsState::instance.buildings[buildingID];
            }
            if (DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex3 == 0x8e) {
                QUARRY_SFX(buildingID, OpenSHC::DE::SHCDE::FX_MASON_CHIP);
                buildingID = DAT_CurrentBuildingID::instance;
                quarry = &DAT_BuildingsState::instance.buildings[buildingID];
            }
            if (DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex3 == 0x96) {
                QUARRY_SFX(buildingID, OpenSHC::DE::SHCDE::FX_MASON_CRUMBLE);
                buildingID = DAT_CurrentBuildingID::instance;
                quarry = &DAT_BuildingsState::instance.buildings[buildingID];
            }
            if (finished == 0) {
                goto ownerFlag;
            }
            goto resetD;
        } else if (DAT_BuildingsState::instance.buildings[buildingID].subAnimState3 == 2) {
            DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex3 += 1;
            frame = (char)DAT_BuildingDefinedData::instance
                        .quarryMasonPhase2Frames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex3];
            if (frame <= 0) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex3 = 0;
                goto resetD;
            }
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame3 = frame + 0xc1;
            goto ownerFlag;
        } else if (DAT_BuildingsState::instance.buildings[buildingID].subAnimState3 == 3) {
            DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex3 += 1;
            frame = (char)DAT_BuildingDefinedData::instance
                        .quarryMasonPhase3Frames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex3];
            if (frame <= 0) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex3 = 0;
                goto resetD;
            }
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame3 = frame + 0xc1;
            goto ownerFlag;
        } else if (DAT_BuildingsState::instance.buildings[buildingID].subAnimState3 == 4) {
            DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex3 += 1;
            frame = (char)DAT_BuildingDefinedData::instance
                        .quarryMasonPhase4Frames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex3];
            if (frame <= 0) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex3 = 0;
                goto resetD;
            }
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame3 = frame + 0xc1;
            goto ownerFlag;
        } else {
            goto ownerFlag;
        }
    resetD: {
        short masonState = DAT_BuildingsState::instance.buildings[buildingID].subAnimState3;
        if (masonState == 0) {
            if (DAT_BuildingsState::instance.buildings[buildingID].subAnimState1 == 6) {
                DAT_BuildingsState::instance.buildings[buildingID].subAnimState3 = 1;
            }
        } else if (masonState <= 4) {
            DAT_BuildingsState::instance.buildings[buildingID].subAnimState3 = 0;
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::addResourceToStockpile,
                DAT_BuildingsState::ptr)(stockpileID, DAT_BuildingsState::instance.buildings[stockpileID].uid,
                OpenSHC::Game::Resources::RT_STONE, 1, 0x30, 1);
            buildingID = DAT_CurrentBuildingID::instance;
            quarry = &DAT_BuildingsState::instance.buildings[buildingID];
        }
    }

    ownerFlag:
        if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY) {
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame13 += 1;
            if ((char)DAT_BuildingDefinedData::instance
                    .ownerFlagFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayFrame13 / 2]
                <= 0) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame13 = 0;
            }
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame14 = (char)DAT_BuildingDefinedData::instance
                .ownerFlagFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayFrame13 / 2];
        } else {
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame14 = 0;
        }
    }

#undef QUARRY_SFX

}
}
