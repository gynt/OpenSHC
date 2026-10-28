#include "OpenSHC/Map/Entities.func.hpp"

#include "OpenSHC/AI/AIRecruitUnitChoice.hpp"
#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityDefinedData.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00402900
    void Entities::UpdateFlag_1_2_4_Entity()
    {
        int frameOffset;
        int nextFlagState = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].animState;
        int ownerID = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].owner;
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2
            = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2RelatedOffset;
        if ((int)((byte)DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].yPosition & 0x1f)
            >= DAT_LandscapeState::instance.wind.countdown) {
            nextFlagState = DAT_LandscapeState::instance.wind.value;
        }
        if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY
            && DAT_GameSynchronyState::instance.currentPlayerFullIDArray[ownerID] == -1
            && DAT_GameSynchronyState::instance.currentAIArray[ownerID] != 0) {
            if (DAT_GameState::instance.playerDataArray[ownerID].aiBuildingDestroyChoiceTracker != 0) {
                nextFlagState = 3;
            }
            else if (DAT_GameState::instance.playerDataArray[ownerID].aiNervousActionsTracker != 0) {
                nextFlagState = 3;
            }
            else {
                int recruitChoice = DAT_GameState::instance.playerDataArray[ownerID].aiRecruitUnitChoiceState;
                nextFlagState = 0;
                if (recruitChoice != OpenSHC::AI::AIRUC_DEFENSIVE) {
                    nextFlagState = (recruitChoice != OpenSHC::AI::AIRUC_RAIDING) + 1;
                }
            }
        }
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].ticksPerAnimFrame = 3;
        switch (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].animState) {
        case 0:
            frameOffset = DAT_EntityDefinedData::instance
                              .flagWaveFramesState0[DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance]
                                                        .animFrameCounter];
            break;
        case 1:
            frameOffset = DAT_EntityDefinedData::instance
                              .flagWaveFramesState1[DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance]
                                                        .animFrameCounter];
            break;
        case 3:
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].ticksPerAnimFrame = 1;
            // fall through
        case 2:
            frameOffset = DAT_EntityDefinedData::instance
                              .flagWaveFramesState23[DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance]
                                                         .animFrameCounter];
            break;
        default:
            return;
        }
        if (frameOffset <= 0) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].animFrameCounter = 0;
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].animState = (short)nextFlagState;
            return;
        }
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2 += frameOffset - 1;
    }

}
}
