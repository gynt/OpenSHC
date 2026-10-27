#include "../GameCore.func.hpp"

#include "OpenSHC/IO/SettingsFileState.func.hpp"
#include "OpenSHC/Map/MapPropertiesState.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_SettingsFileState.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x004718F0
    void GameCore::incrementMissionProgress()
    {
        ++this->missionNumber;
        if (!this->unlockAllHistoricalCampaigns && !DAT_GameCore::instance.isReplayingSelectedMission) {
            if (this->missionNumber <= 6) {
                if (this->missionNumber > this->scenarioProgress.progressCallToArms) {
                    this->scenarioProgress.progressCallToArms = this->missionNumber;
                }
            } else if (this->missionNumber <= 11) {
                if (this->missionNumber > this->scenarioProgress.progressSaladinsConquest) {
                    this->scenarioProgress.progressSaladinsConquest = this->missionNumber;
                }
            } else if (this->missionNumber <= 16) {
                if (this->missionNumber > this->scenarioProgress.progressTheKingsCrusade) {
                    this->scenarioProgress.progressTheKingsCrusade = this->missionNumber;
                }
            } else if (this->missionNumber <= 21) {
                if (this->missionNumber > this->scenarioProgress.progressCrusaderStates) {
                    this->scenarioProgress.progressCrusaderStates = this->missionNumber;
                }
            }
        }
        MACRO_CALL_MEMBER(IO::SettingsFileState_Func::writeUserConfig, DAT_SettingsFileState::ptr)();

        if (!MACRO_CALL_MEMBER(Map::MapPropertiesState_Func::isValueAtMostTwenty, DAT_MapPropertiesState::ptr)(
                this->missionNumber)) {
            MACRO_CALL_MEMBER(GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                UI::Enums::MVT_MISSION_FINISHED_TRANSITION, 0);
            DAT_GameCore::instance.isReplayingSelectedMission = 0;
            DAT_GameCore::instance.forceLocalPlayerVictory = 0;
            return;
        }

        MACRO_CALL_MEMBER(GameCore_Func::removeJesterAndLadyUnitsInCertainMissions, this)();
        DAT_GameSynchronyState::instance.currentPlayerSlotID = 1;
        int const firstMissionOfCampaign = this->historicCampaignNumber * 5 - 4;
        if (this->missionNumber != firstMissionOfCampaign && !DAT_GameCore::instance.isReplayingSelectedMission) {
            MACRO_CALL_MEMBER(GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                UI::Enums::MVT_MISSION_FINISHED_TRANSITION, 0);
            DAT_GameCore::instance.isReplayingSelectedMission = 0;
            DAT_GameCore::instance.forceLocalPlayerVictory = 0;
            return;
        }

        if (DAT_GameCore::instance.isReplayingSelectedMission && this->missionNumber != firstMissionOfCampaign) {
            MACRO_CALL_MEMBER(GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                UI::Enums::MVT_HISTORIC_MISSION_PICTURE, 0);
        } else {
            MACRO_CALL_MEMBER(GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                UI::Enums::MVT_HISTORIC_CAMPAIGN_INTRO, 0);
        }
        DAT_GameCore::instance.briefingOpenedFromInGame = 0;
        DAT_GameCore::instance.isReplayingSelectedMission = 0;
        DAT_GameCore::instance.forceLocalPlayerVictory = 0;
    }

}
}
