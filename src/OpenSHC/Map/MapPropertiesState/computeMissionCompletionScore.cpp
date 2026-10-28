#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MissionAestheticsDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    using namespace OpenSHC::Game::Resources;
    using OpenSHC::Game::ScenarioEvents::InGameEventUnionVersion;

// One goods goal of the scored victory event: goods type is the signed condition subType (movsx, 0x4BDF0A).
#define SCORE_GOODS_GOAL(cond)                                                                                         \
    if (ev->data.scenario.conditions[cond].enabled != 0) {                                                             \
        this->scoreGoalGoodsType[this->scoreGoalBonusCount] = (char)ev->data.scenario.conditions[cond].subType;        \
        int slot = this->scoreGoalBonusCount;                                                                          \
        int required = MACRO_CALL_MEMBER(MapPropertiesState_Func::getDifficultyMultipliedValue, this)(                 \
            ev->data.scenario.conditions[cond].value);                                                                 \
        this->scoreGoalSurplus[slot]                                                                                   \
            = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]            \
                  .currentResources[this->scoreGoalGoodsType[slot]]                                                    \
            - required;                                                                                                \
        switch (this->scoreGoalGoodsType[this->scoreGoalBonusCount]) {                                                 \
        case RT_WOOD:                                                                                                  \
        case RT_BREAD:                                                                                                 \
        case RT_CHEESE:                                                                                                \
        case RT_MEAT:                                                                                                  \
        case RT_APPLE:                                                                                                 \
            this->scoreGoalPoints[this->scoreGoalBonusCount] = this->scoreGoalSurplus[this->scoreGoalBonusCount] * 5;  \
            break;                                                                                                     \
        case RT_BOW:                                                                                                   \
        case RT_CROSSBOW:                                                                                              \
        case RT_SPEAR:                                                                                                 \
        case RT_PIKE:                                                                                                  \
        case RT_MACE:                                                                                                  \
        case RT_SWORD:                                                                                                 \
        case RT_LEATHERARMOR:                                                                                          \
        case RT_IRONARMOR:                                                                                             \
            this->scoreGoalPoints[this->scoreGoalBonusCount] = this->scoreGoalSurplus[this->scoreGoalBonusCount] * 50; \
            break;                                                                                                     \
        case RT_IRON:                                                                                                  \
            this->scoreGoalPoints[this->scoreGoalBonusCount] = this->scoreGoalSurplus[this->scoreGoalBonusCount] * 20; \
            break;                                                                                                     \
        default:                                                                                                       \
            this->scoreGoalPoints[this->scoreGoalBonusCount] = this->scoreGoalSurplus[this->scoreGoalBonusCount] * 10; \
            break;                                                                                                     \
        }                                                                                                              \
        if (this->scoreGoalSurplus[this->scoreGoalBonusCount] > 0) {                                                   \
            this->scoreGoalBonusCount = this->scoreGoalBonusCount + 1;                                                 \
        }                                                                                                              \
    }

    // FUNCTION: STRONGHOLDCRUSADER 0x004BDE40
    void MapPropertiesState::computeMissionCompletionScore()
    {
        int deadlineMonth = 0;
        int deadlineYear = 0;
        this->missionScore = -1;
        this->scoreGoalBonusCount = 0;
        for (int i = 0; i < this->eventsCount; ++i) {
            InGameEventUnionVersion* ev = &this->scenarioEvents[i];
            if (ev->header.tl_type == 3
                && (ev->data.scenario.ScenarioEventType == 1 || ev->data.scenario.ScenarioEventType == 0x1B)
                && ev->data.scenario.conditions[0].enabled != 0) {
                deadlineMonth = ev->header.month;
                deadlineYear = ev->header.year;
            }
            if (ev->header.tl_type != 3
                || (ev->data.scenario.ScenarioEventType != 0 && ev->data.scenario.ScenarioEventType != 0x1A)) {
                continue;
            }
            // only the last victory-condition event is scored
            for (int later = i + 1; later < this->eventsCount; ++later) {
                if (this->scenarioEvents[later].header.tl_type == 3
                    && (this->scenarioEvents[later].data.scenario.ScenarioEventType == 0
                        || this->scenarioEvents[later].data.scenario.ScenarioEventType == 0x1A)) {
                    goto nextEvent;
                }
            }
            SCORE_GOODS_GOAL(6)
            SCORE_GOODS_GOAL(17)
            SCORE_GOODS_GOAL(5)
            SCORE_GOODS_GOAL(7)
            if (ev->data.scenario.conditions[4].enabled != 0) {
                this->scoreGoalGoodsType[this->scoreGoalBonusCount] = RT_GOLD;
                this->scoreGoalSurplus[this->scoreGoalBonusCount]
                    = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                          .currentResources[RT_GOLD]
                    - MACRO_CALL_MEMBER(MapPropertiesState_Func::getDifficultyMultipliedValue, this)(
                        ev->data.scenario.conditions[4].value);
                this->scoreGoalPoints[this->scoreGoalBonusCount] = this->scoreGoalSurplus[this->scoreGoalBonusCount];
                if (this->scoreGoalSurplus[this->scoreGoalBonusCount] > 0) {
                    this->scoreGoalBonusCount = this->scoreGoalBonusCount + 1;
                }
            }
            if (ev->data.scenario.conditions[1].enabled != 0) {
                this->scoreGoalGoodsType[this->scoreGoalBonusCount] = -1;
                this->scoreGoalSurplus[this->scoreGoalBonusCount]
                    = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                          .currentPopulation
                    - MACRO_CALL_MEMBER(MapPropertiesState_Func::getDifficultyMultipliedValue, this)(
                        ev->data.scenario.conditions[1].value);
                this->scoreGoalPoints[this->scoreGoalBonusCount] = this->scoreGoalSurplus[this->scoreGoalBonusCount];
                if (this->scoreGoalSurplus[this->scoreGoalBonusCount] > 0) {
                    this->scoreGoalBonusCount = this->scoreGoalBonusCount + 1;
                }
            }
        nextEvent:;
        }

        this->scoreMonthsEarly = 0;
        this->scoreTimeBonus = 0;
        if (deadlineYear != 0) {
            int monthsLeft = (deadlineYear - DAT_GameState::instance.mapAndTime.year) * 12
                - DAT_GameState::instance.mapAndTime.month + deadlineMonth;
            this->scoreMonthsEarly = monthsLeft > 0 ? monthsLeft : 0;
            this->scoreTimeBonus = this->scoreMonthsEarly * 100;
        }
        this->missionScore = this->scoreTimeBonus;
        this->missionScore = DAT_MissionAestheticsDefinedData::instance
                                 .missionScoreBasePerDifficulty[DAT_GameState::instance.mapAndTime.difficulty]
            + this->missionScore;
        for (int k = 0; k < (int)this->scoreGoalBonusCount; ++k) {
            this->missionScore += this->scoreGoalPoints[k];
        }

        this->scoreTroopSurvivalBonus = 0;
        if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CAMPAIGN_MISSION
            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CUSTOM_MAP
                && (int)DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 < 2)) {
            int aliveValue = 0;
            for (int u = 1; u < 2500; ++u) {
                if (DAT_UnitsState::instance.units[u].logicalState != OpenSHC::Map::Units::ULS_INVISIBLE
                    && DAT_UnitsState::instance.units[u].owner == DAT_GameSynchronyState::instance.currentPlayerSlotID
                    && DAT_UnitsState::instance.units[u].isSelectable_OR_matchTime != 0) {
                    aliveValue += MACRO_CALL_MEMBER(
                        OpenSHC::Map::Units::TroopValueState_Func::getValueOfTroopType, DAT_TroopValueState::ptr)(
                        (OpenSHC::Map::Units::UnitType)DAT_UnitsState::instance.units[u].unitType);
                }
            }
            int losses
                = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                      .weightedLosses;
            int total = losses + aliveValue;
            if (total != 0) {
                this->scoreLossesPercent = losses * 100 / total;
                this->scoreTroopSurvivalBonus = (100 - this->scoreLossesPercent) * 100;
                this->missionScore += this->scoreTroopSurvivalBonus;
            }
        }

        if (DAT_GameCore::instance.mapU4Int1 != 0) {
            int aliveValue = 0;
            for (int u = 1; u < 2500; ++u) {
                if (DAT_UnitsState::instance.units[u].logicalState != OpenSHC::Map::Units::ULS_INVISIBLE
                    && DAT_UnitsState::instance.units[u].owner == 1
                    && DAT_UnitsState::instance.units[u].isSelectable_OR_matchTime != 0) {
                    aliveValue += MACRO_CALL_MEMBER(
                        OpenSHC::Map::Units::TroopValueState_Func::getValueOfTroopType, DAT_TroopValueState::ptr)(
                        (OpenSHC::Map::Units::UnitType)DAT_UnitsState::instance.units[u].unitType);
                }
            }
            this->player1AliveTroopValue = aliveValue;
            this->player2WeightedLosses = DAT_GameState::instance.playerDataArray[2].weightedLosses;
            this->player1AlivePlusPlayer2Losses = DAT_GameState::instance.playerDataArray[2].weightedLosses + aliveValue;
        }
    }

#undef SCORE_GOODS_GOAL

}
}
