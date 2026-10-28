#include "../GameStateStructures.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Game/TrailType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueDefinedData.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::Game::GameMode;
    using OpenSHC::Game::GameMode2;
    using OpenSHC::Game::TrailType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00455E10
    void GameStateStructures::resetVariousCountsAndStatisticsAndStartGoodsAndResources()
    {
        for (int playerID = 1; playerID < 9; playerID++) {
            this->playerDataArray[playerID].weeksWithoutFood = 0;
            this->playerDataArray[playerID].foodTypesCurrentlyEaten = 0;
            this->playerDataArray[playerID].worstPopularityFactor = 0;
            this->playerDataArray[playerID].foodStorageLevelLastLastMonth = 0;
            this->playerDataArray[playerID].foodStorageLevelLastMonth = 0;
            this->playerDataArray[playerID].vclock = 2000;
            this->playerDataArray[playerID].someCount43 = 0;
            int startingPopularity = this->mapAndTime.startingPopularity * 10;
            this->playerDataArray[playerID].popularity = startingPopularity;
            this->playerDataArray[playerID].previousWeekPopularity = startingPopularity;
            this->playerDataArray[playerID].lastAnnouncedPopularity = (short)startingPopularity;
            this->playerDataArray[playerID].taxesSetting = 3;
            this->playerDataArray[playerID].rationsSetting = 2;
            this->playerDataArray[playerID].rationsLevel = this->playerDataArray[playerID].rationsSetting2
                = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                      .rationsSetting;
            this->playerDataArray[playerID].startGoodsBannerMode = 1;
            this->playerDataArray[playerID].noEnemyThreatSkirmish = 1;
            this->playerDataArray[playerID].startGoodsBannerScrollX = 0;
            this->playerDataArray[playerID].startGoodsListOffsetY = 0x3c;
            this->playerDataArray[playerID].goodsDeliveryDelay = 0;
            this->playerDataArray[playerID].gameOutcome = 0;
            this->playerDataArray[playerID].previousBlessedPeoplePercentage = 0;
            this->playerDataArray[playerID].popularityReligionBasedDiv25 = 0;
            this->playerDataArray[playerID].popularityEventWeeksLeft = 0;
            this->playerDataArray[playerID].lionsEventCountdown = 0;
            this->playerDataArray[playerID].banditsEventCountdown = 0;
            this->playerDataArray[playerID].fireEventCountdown = 0;
            this->playerDataArray[playerID].marriageEventCountdown = 0;
            this->playerDataArray[playerID].jesterEventCountdown = 0;
            this->playerDataArray[playerID].plaguePopularityEffect = 0;
            this->playerDataArray[playerID].lionAttackPopularityEffect = 0;
            this->playerDataArray[playerID].banditsPopularityEffect = 0;
            this->playerDataArray[playerID].firePopularityEffect = 0;
            this->playerDataArray[playerID].marriagePopularityEffect = 0;
            this->playerDataArray[playerID].jesterPopularityEffect = 0;
            this->playerDataArray[playerID].plagueCureProgress = 0;
            this->playerDataArray[playerID].keepEnclosementRelatedCountdown = 0;
            this->playerDataArray[playerID].defensesDamagedByPlayer = 0;
            for (int resourceType = 0; resourceType < 25; resourceType++) {
                this->playerDataArray[playerID].pendingResources[resourceType]
                    = this->mapAndTime.startGoods[resourceType];
            }
            MACRO_CALL(OpenSHC::OS_Func::_memset)(this->playerDataArray[playerID].snoozedBuildings, 0, 100);
            this->playerDataArray[playerID].troopsKilled = 0;
            this->playerDataArray[playerID].troopsLost = 0;
            this->playerDataArray[playerID].weightedLosses = 0;
            this->playerDataArray[playerID].popularityFallingAnnounced = 0;
            this->playerDataArray[playerID].lastMigrationWasEmigration = 0;
            if (this->mapAndTime.editScenarioExtraOptions != 0) {
                this->playerDataArray[playerID].taxesSetting = this->mapAndTime.scenarioTaxesSetting;
                this->playerDataArray[playerID].rationsSetting = this->playerDataArray[playerID].rationsLevel
                    = this->playerDataArray[playerID].rationsSetting2 = this->mapAndTime.scenarioRationsSetting;
                this->playerDataArray[playerID].currentResources[0xf] = this->mapAndTime.scenarioGold;
            }
            if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
                int gameTypeMultiplier = 1;
                if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SKIRMISH_AND_MULTIPLAYER)
                    && (DAT_GameCore::instance.isSkirmishTrail == TRUE)
                    && (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_EXTREME)) {
                    gameTypeMultiplier = 3;
                }
                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] != -1) {
                    this->playerDataArray[playerID].pendingResources[0xf]
                        = DAT_TroopValueDefinedData::instance
                              .skirmishStartGoldTable[(DAT_GameSynchronyState::instance.skirmishCurrentAdvantageBalance
                                                    + DAT_GameSynchronyState::instance.skirmishGameIntensityType * 5)
                                      * 2
                                  + 0xc]
                        * gameTypeMultiplier;
                } else if (DAT_GameSynchronyState::instance.currentAIArray[playerID] != 0) {
                    this->playerDataArray[playerID].pendingResources[0xf]
                        = DAT_TroopValueDefinedData::instance
                              .skirmishStartGoldTable[(DAT_GameSynchronyState::instance.skirmishCurrentAdvantageBalance
                                                    + DAT_GameSynchronyState::instance.skirmishGameIntensityType * 5)
                                      * 2
                                  + 0xd]
                        * gameTypeMultiplier;
                }
            }
            DAT_GameState::instance.mapAndTime.populationIndex = 0;
            this->playerDataArray[playerID].beforeLastMonthsGold
                = (short)this->playerDataArray[playerID].currentResources[0xf];
            this->playerDataArray[playerID].lastMonthsGold
                = (short)this->playerDataArray[playerID].currentResources[0xf];
            this->playerDataArray[playerID].aiControlStatusRelated = -1000;
            for (int foodType = 0; foodType < 4; foodType++) {
                this->playerDataArray[playerID].isFoodTypeBanned[foodType] = 0;
            }
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::setCurrentAttackStrength, DAT_AICState::ptr)(playerID);
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::setCurrentAttackRaidParameter, DAT_AICState::ptr)(playerID);
            DAT_GameState::instance.playerDataArray[playerID].nervousBikCountdown = 0x30;
            this->playerDataArray[playerID].tacticalPowersBarLevel = 0;
            this->playerDataArray[playerID].goldDonation = 0;
        }
    }
}
}
