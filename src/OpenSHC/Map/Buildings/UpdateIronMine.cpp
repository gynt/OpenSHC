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

namespace OpenSHC {
namespace Map {

#define IRON_MINE_SFX(id, sound) \
    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)( \
        DAT_BuildingsState::instance.buildings[id].x, DAT_BuildingsState::instance.buildings[id].y, sound)

#define IRON_MINE_BLEND(frame) \
    if ((frame) < 4) { \
        DAT_BuildingsState::instance.buildings[buildingID].ironMinerBlendLevel = 0x18; \
    } else if ((frame) < 8) { \
        DAT_BuildingsState::instance.buildings[buildingID].ironMinerBlendLevel = 0x14; \
    } else if ((frame) < 0xc) { \
        DAT_BuildingsState::instance.buildings[buildingID].ironMinerBlendLevel = 0x10; \
    } else if ((frame) < 0x10) { \
        DAT_BuildingsState::instance.buildings[buildingID].ironMinerBlendLevel = 0xc; \
    } else if ((frame) < 0x14) { \
        DAT_BuildingsState::instance.buildings[buildingID].ironMinerBlendLevel = 0x10; \
    } else { \
        DAT_BuildingsState::instance.buildings[buildingID].ironMinerBlendLevel = ((frame) < 0x18) ? 0x14 : 0x18; \
    }
    // Runs every 2nd tick (tickDivider <= 1 returns, signed jle 0x41CCDF). Four independent animation layers:
    // A = state (0x41CD10), B = subAnimState2 (0x41CF96), C = subAnimState1 smelter with sounds (0x41D0BA),
    // D = subAnimState3 pour (0x41D39A); D's last step adds 1 iron (addResourceToStockpile at 0x41D43E).
    // Every frame-table test is a signed byte compare (jg). Layer A state 5/6 goes back to 0 when the stockpile
    // holds < 7 iron, else to 6 (setl at 0x41CEA7). ironMinerBlendLevel follows the signed frame value
    // (jge chain at 0x41D2B7). Iron pile overlay: resources[RT_IRON] <= 0 -> 0, >= 8 -> 0xaa, else + 0xa2.
    // FUNCTION: STRONGHOLDCRUSADER 0x0041CC70
    void Buildings::UpdateIronMine()
    {
        int buildingID = DAT_CurrentBuildingID::instance;
        OpenSHC::Map::Buildings::Building* mine = &DAT_BuildingsState::instance.buildings[buildingID];
        DAT_GameState::instance.playerDataArray[DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner]
            .countIronMines
            += 1;
        DAT_BuildingsState::instance.buildings[buildingID].renderAnimation = 0;
        DAT_BuildingsState::instance.buildings[buildingID].showOverlays = 1;
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(buildingID);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        buildingID = DAT_CurrentBuildingID::instance;
        mine = &DAT_BuildingsState::instance.buildings[buildingID];
        DAT_BuildingsState::instance.buildings[buildingID].tickDivider += 1;
        if (DAT_BuildingsState::instance.buildings[buildingID].tickDivider <= 1) {
            return;
        }
        DAT_BuildingsState::instance.buildings[buildingID].tickDivider = 0;

        // Layer A: the miner.
        if (DAT_BuildingsState::instance.buildings[buildingID].workers[0] == 0) {
            DAT_BuildingsState::instance.buildings[buildingID].state = 0;
            DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0 = 0;
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame0 = 0;
        } else {
            short state = DAT_BuildingsState::instance.buildings[buildingID].state;
            if (state == 0) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0 += 1;
                if ((char)DAT_BuildingDefinedData::instance
                        .ironMinePhase0Frames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0]
                    > 0) {
                    goto displayA;
                }
            } else if (state == 1) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0 += 1;
                if ((char)DAT_BuildingDefinedData::instance
                        .ironMinePhase1Frames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0]
                    > 0) {
                    goto displayA;
                }
            } else if (state == 2) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0 += 1;
                if ((char)DAT_BuildingDefinedData::instance
                        .ironMinePhase2Frames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0]
                    > 0) {
                    goto displayA;
                }
            } else if (state == 3) {
                int index = DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0;
                if (index == 0 || index == 0x18 || index == 0x30 || index == 0x48) {
                    IRON_MINE_SFX(buildingID, OpenSHC::DE::SHCDE::FX_IRON_PULL);
                    buildingID = DAT_CurrentBuildingID::instance;
                    mine = &DAT_BuildingsState::instance.buildings[buildingID];
                }
                DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0 += 1;
                if ((char)DAT_BuildingDefinedData::instance
                        .ironMinePullFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0]
                    > 0) {
                    goto displayA;
                }
            } else if (state != 4) {
                if (state == 5) {
                    DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0 += 1;
                    if ((char)DAT_BuildingDefinedData::instance
                            .ironMinePhase5Frames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0]
                        > 0) {
                        goto displayA;
                    }
                } else {
                    if (state != 6) {
                        goto displayA;
                    }
                    DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0 += 1;
                    if ((char)DAT_BuildingDefinedData::instance
                            .ironMineIdleFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0]
                        > 0) {
                        goto displayA;
                    }
                }
            }
            mine->overlayAnimIndex0 = 0;
            state = DAT_BuildingsState::instance.buildings[buildingID].state;
            if (state == 0) {
                DAT_BuildingsState::instance.buildings[buildingID].state = 1;
            } else if (state == 1) {
                DAT_BuildingsState::instance.buildings[buildingID].state = 2;
            } else if (state == 2) {
                DAT_BuildingsState::instance.buildings[buildingID].state = 3;
            } else if (state == 3) {
                DAT_BuildingsState::instance.buildings[buildingID].state = 4;
            } else if (state == 4) {
                if (DAT_BuildingsState::instance.buildings[buildingID].subAnimState1 == 1) {
                    DAT_BuildingsState::instance.buildings[buildingID].state = 5;
                }
            } else if (state == 5) {
                DAT_BuildingsState::instance.buildings[buildingID].state
                    = (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingResourceAmountByUid,
                           DAT_BuildingsState::ptr)(buildingID, DAT_BuildingsState::instance.buildings[buildingID].uid,
                           OpenSHC::Game::Resources::RT_IRON)
                          < 7)
                    ? 0
                    : 6;
            } else if (state == 6) {
                DAT_BuildingsState::instance.buildings[buildingID].state
                    = (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingResourceAmountByUid,
                           DAT_BuildingsState::ptr)(buildingID, DAT_BuildingsState::instance.buildings[buildingID].uid,
                           OpenSHC::Game::Resources::RT_IRON)
                          < 7)
                    ? 0
                    : 6;
            }
        displayA:
            state = DAT_BuildingsState::instance.buildings[buildingID].state;
            if (state == 0) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame0 = (char)DAT_BuildingDefinedData::instance
                    .ironMinePhase0Frames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0];
            } else if (state == 1) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame0
                    = (char)DAT_BuildingDefinedData::instance
                          .ironMinePhase1Frames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0]
                    + 0x76;
            } else if (state == 2) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame0 = (char)DAT_BuildingDefinedData::instance
                    .ironMinePhase2Frames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0];
            } else if (state == 3) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame0
                    = (char)DAT_BuildingDefinedData::instance
                          .ironMinePullFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0]
                    + 0x26;
            } else if (state == 4) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame0 = 0x3b;
            } else if (state == 5) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame0
                    = (char)DAT_BuildingDefinedData::instance
                          .ironMinePhase5Frames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0]
                    + 0x3a;
            } else if (state == 6) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame0
                    = (char)DAT_BuildingDefinedData::instance
                          .ironMineIdleFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0]
                    + 0x4e;
            }
        }

        // Layer B.
        if (DAT_BuildingsState::instance.buildings[buildingID].workers[0] == 0) {
            DAT_BuildingsState::instance.buildings[buildingID].subAnimState2 = 0;
            DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2 = 0;
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame2 = 0;
        } else {
            short state = DAT_BuildingsState::instance.buildings[buildingID].subAnimState2;
            if (state != 0) {
                if (state == 1) {
                    DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2 += 1;
                    if ((char)DAT_BuildingDefinedData::instance
                            .ironMineLayer2Phase1Frames[DAT_BuildingsState::instance.buildings[buildingID]
                                    .overlayAnimIndex2]
                        > 0) {
                        goto displayB;
                    }
                } else if (state != 2) {
                    if (state != 3) {
                        goto displayB;
                    }
                    DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2 += 1;
                    if ((char)DAT_BuildingDefinedData::instance
                            .ironMineLayer2Phase3Frames[DAT_BuildingsState::instance.buildings[buildingID]
                                    .overlayAnimIndex2]
                        > 0) {
                        goto displayB;
                    }
                }
            }
            mine->overlayAnimIndex2 = 0;
            state = DAT_BuildingsState::instance.buildings[buildingID].subAnimState2;
            if (state == 0) {
                if (DAT_BuildingsState::instance.buildings[buildingID].state == 3
                    && DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0 == 0x50) {
                    DAT_BuildingsState::instance.buildings[buildingID].subAnimState2 = 1;
                }
            } else if (state == 1) {
                DAT_BuildingsState::instance.buildings[buildingID].subAnimState2 = 2;
            } else if (state == 2) {
                if (DAT_BuildingsState::instance.buildings[buildingID].state == 0) {
                    DAT_BuildingsState::instance.buildings[buildingID].subAnimState2 = 3;
                }
            } else if (state == 3) {
                DAT_BuildingsState::instance.buildings[buildingID].subAnimState2 = 0;
            }
        displayB:
            state = DAT_BuildingsState::instance.buildings[buildingID].subAnimState2;
            if (state == 0) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame2 = 0;
            } else if (state == 1) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame2
                    = (char)DAT_BuildingDefinedData::instance
                          .ironMineLayer2Phase1Frames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2]
                    + 0x32;
            } else if (state == 2) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame2 = 0;
            } else if (state == 3) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame2
                    = (char)DAT_BuildingDefinedData::instance
                          .ironMineLayer2Phase3Frames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2]
                    + 0x32;
            }
        }

        // Layer C: the smelter.
        if (DAT_BuildingsState::instance.buildings[buildingID].workers[0] == 0) {
            DAT_BuildingsState::instance.buildings[buildingID].subAnimState1 = 0;
            DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex1 = 0;
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame1 = 0;
        } else {
            short state = DAT_BuildingsState::instance.buildings[buildingID].subAnimState1;
            if (state == 0) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex1 += 1;
                if ((char)DAT_BuildingDefinedData::instance
                        .ironMineSmeltPhase0Frames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex1]
                    > 0) {
                    goto displayC;
                }
            } else if (state == 1) {
                if (DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex1 == 0x14) {
                    IRON_MINE_SFX(buildingID, OpenSHC::DE::SHCDE::FX_IRON_STRAIN);
                }
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayAnimIndex1 == 0x37) {
                    IRON_MINE_SFX(DAT_CurrentBuildingID::instance, OpenSHC::DE::SHCDE::FX_IRON_DUMP);
                }
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayAnimIndex1 == 0x41) {
                    IRON_MINE_SFX(DAT_CurrentBuildingID::instance, OpenSHC::DE::SHCDE::FX_IRON_LDUMP);
                }
                int index = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayAnimIndex1;
                if (index == 100 || index == 0xbe || index == 0x118 || index == 0x172) {
                    IRON_MINE_SFX(DAT_CurrentBuildingID::instance, OpenSHC::DE::SHCDE::FX_IRON_BOIL);
                }
                buildingID = DAT_CurrentBuildingID::instance;
                mine = &DAT_BuildingsState::instance.buildings[buildingID];
                DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex1 += 1;
                if ((char)DAT_BuildingDefinedData::instance
                        .ironMineSmeltPhase1Frames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex1]
                    > 0) {
                    goto displayC;
                }
            } else {
                if (state != 2) {
                    goto displayC;
                }
                DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex1 += 1;
                if ((char)DAT_BuildingDefinedData::instance
                        .ironMineSmeltPhase2Frames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex1]
                    > 0) {
                    goto displayC;
                }
            }
            mine->overlayAnimIndex1 = 0;
            state = DAT_BuildingsState::instance.buildings[buildingID].subAnimState1;
            if (state == 0) {
                if (DAT_BuildingsState::instance.buildings[buildingID].state == 4) {
                    DAT_BuildingsState::instance.buildings[buildingID].subAnimState1 = 1;
                }
            } else if (state == 1) {
                DAT_BuildingsState::instance.buildings[buildingID].subAnimState1 = 2;
            } else if (state == 2) {
                DAT_BuildingsState::instance.buildings[buildingID].subAnimState1 = 0;
            }
        displayC:
            state = DAT_BuildingsState::instance.buildings[buildingID].subAnimState1;
            if (state == 0) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame1
                    = (char)DAT_BuildingDefinedData::instance
                          .ironMineSmeltPhase0Frames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex1]
                    + 0x7e;
            } else if (state == 1) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame1
                    = (char)DAT_BuildingDefinedData::instance
                          .ironMineSmeltPhase1Frames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex1]
                    + 0x86;
            } else if (state == 2) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame1
                    = (char)DAT_BuildingDefinedData::instance
                          .ironMineSmeltPhase2Frames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex1]
                    + 0x86;
            }
            // The original repeats the blend-level chain for each table (0x41D2B5 and 0x41D327).
            state = DAT_BuildingsState::instance.buildings[buildingID].subAnimState1;
            if (state == 1) {
                char frame = (char)DAT_BuildingDefinedData::instance
                                 .ironMineSmeltPhase1Frames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex1];
                IRON_MINE_BLEND(frame);
            } else if (state == 2) {
                char frame = (char)DAT_BuildingDefinedData::instance
                                 .ironMineSmeltPhase2Frames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex1];
                IRON_MINE_BLEND(frame);
            }
        }

        // Layer D: pouring the iron.
        if (DAT_BuildingsState::instance.buildings[buildingID].workers[0] == 0) {
            DAT_BuildingsState::instance.buildings[buildingID].subAnimState3 = 0;
            DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex3 = 0;
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame3 = 0;
        } else {
            short state = DAT_BuildingsState::instance.buildings[buildingID].subAnimState3;
            if (state != 0) {
                if (state != 1) {
                    goto displayD;
                }
                if (DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex3 == 0) {
                    IRON_MINE_SFX(buildingID, OpenSHC::DE::SHCDE::FX_IRON_POUR);
                }
                buildingID = DAT_CurrentBuildingID::instance;
                mine = &DAT_BuildingsState::instance.buildings[buildingID];
                DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex3 += 1;
                if ((char)DAT_BuildingDefinedData::instance
                        .ironMinePourFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex3]
                    > 0) {
                    goto displayD;
                }
            }
            mine->overlayAnimIndex3 = 0;
            state = DAT_BuildingsState::instance.buildings[buildingID].subAnimState3;
            if (state == 0) {
                if (DAT_BuildingsState::instance.buildings[buildingID].subAnimState1 == 2) {
                    DAT_BuildingsState::instance.buildings[buildingID].subAnimState3 = 1;
                }
            } else if (state == 1) {
                DAT_BuildingsState::instance.buildings[buildingID].subAnimState3 = 0;
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::addResourceToStockpile,
                    DAT_BuildingsState::ptr)(DAT_CurrentBuildingID::instance,
                    DAT_BuildingsState::instance.buildings[buildingID].uid, OpenSHC::Game::Resources::RT_IRON, 1, 8, 1);
            }
        displayD:
            buildingID = DAT_CurrentBuildingID::instance;
            mine = &DAT_BuildingsState::instance.buildings[buildingID];
            state = DAT_BuildingsState::instance.buildings[buildingID].subAnimState3;
            if (state == 0) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame3 = 0;
            } else if (state == 1) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame3
                    = (char)DAT_BuildingDefinedData::instance
                          .ironMinePourFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex3]
                    + 0x5e;
            }
        }

        int iron = DAT_BuildingsState::instance.buildings[buildingID].resources[OpenSHC::Game::Resources::RT_IRON];
        if (iron <= 0) {
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame4 = 0;
        } else if (iron >= 8) {
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame4 = 0xaa;
        } else {
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame4 = iron + 0xa2;
        }
        if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY) {
            DAT_BuildingsState::instance.buildings[buildingID].showOverlays = 1;
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

#undef IRON_MINE_SFX
#undef IRON_MINE_BLEND

}
}
