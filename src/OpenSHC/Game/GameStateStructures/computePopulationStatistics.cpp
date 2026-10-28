#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_UIDragDropDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::Game::GameMode2;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Type propagation algorithm not settling
     */
    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0045AF30
    void GameStateStructures::computePopulationStatistics()
    {
        for (int playerID = 1; playerID < 9; playerID++) {
            this->playerDataArray[playerID].currentPopulation
                = ((this->playerDataArray[playerID].liveUnitCount
                       - this->playerDataArray[playerID].nonInteractiveUnitCountThisTick)
                      - this->playerDataArray[playerID].drunkardUpdateCount)
                - this->playerDataArray[playerID].armySize;
            if ((this->playerDataArray[playerID].lordID != 0)
                && (DAT_UnitsState::instance.units[this->playerDataArray[playerID].lordID].uid
                    == this->playerDataArray[playerID].lordUID)) {
                this->playerDataArray[playerID].currentPopulation
                    = this->playerDataArray[playerID].currentPopulation - 1;
            }
            if ((this->playerDataArray[playerID].ladyUnitID != 0)
                && (DAT_UnitsState::instance.units[this->playerDataArray[playerID].ladyUnitID].uid
                    == this->playerDataArray[playerID].ladyUnitUID)) {
                this->playerDataArray[playerID].currentPopulation
                    = this->playerDataArray[playerID].currentPopulation - 1;
            }
            if ((this->playerDataArray[playerID].jesterUnitID != 0)
                && (DAT_UnitsState::instance.units[this->playerDataArray[playerID].jesterUnitID].uid
                    == this->playerDataArray[playerID].jesterUnitUID)) {
                this->playerDataArray[playerID].currentPopulation
                    = this->playerDataArray[playerID].currentPopulation - 1;
            }
            this->playerDataArray[playerID].populationRelatedCrowdingCountUnk
                = this->playerDataArray[playerID].currentPopulation_2
                - this->playerDataArray[playerID].availablePeasantsOrHousedPeasants;
            if (this->playerDataArray[playerID].blessedUnitCount <= 0) {
                this->playerDataArray[playerID].blessedPeoplePercentage = 0;
            } else {
                int blessedPercentage;
                if (this->playerDataArray[playerID].unblessedBlessableUnitCount
                        + this->playerDataArray[playerID].blessedUnitCount
                    == 0) {
                    blessedPercentage = 100;
                } else {
                    blessedPercentage = (this->playerDataArray[playerID].blessedUnitCount * 100)
                        / (this->playerDataArray[playerID].unblessedBlessableUnitCount
                            + this->playerDataArray[playerID].blessedUnitCount);
                }
                this->playerDataArray[playerID].blessedPeoplePercentage = blessedPercentage;
            }
            if (this->mapAndTime.startOfDay != FALSE) {
                this->playerDataArray[playerID]
                    .populationGrowth[this->playerDataArray[playerID].populationGrowthStatisticCounter]
                    = this->playerDataArray[playerID].availablePeasantsOrHousedPeasants;
                this->playerDataArray[playerID].populationGrowthStatisticCounter
                    = this->playerDataArray[playerID].populationGrowthStatisticCounter + 1;
                if (this->playerDataArray[playerID].populationGrowthStatisticCounter >= 8) {
                    this->playerDataArray[playerID].populationGrowthStatisticCounter = 0;
                }
                int growthSum = 0;
                for (int sample = 0; sample < 8; sample++) {
                    growthSum += this->playerDataArray[playerID].populationGrowth[sample];
                }
                this->playerDataArray[playerID].averageAvailablePeasants = growthSum / 8;
            }
            if (this->mapAndTime.monthChanged != 0) {
                if (this->mapAndTime.populationIndex < 300) {
                    this->mapAndTime.playerPopulationStatistics[playerID][this->mapAndTime.populationIndex]
                        = (short)this->playerDataArray[playerID].currentPopulation;
                } else {
                    /*
                      Running average move values
                     */
                    for (int sample = 0; sample < 299; sample++) {
                        this->mapAndTime.playerPopulationStatistics[playerID][sample]
                            = this->mapAndTime.playerPopulationStatistics[playerID][sample + 1];
                    }
                    this->mapAndTime.playerPopulationStatistics[playerID][299]
                        = (short)this->playerDataArray[playerID].currentPopulation;
                }
            }
            if (this->playerDataArray[playerID].currentPopulation
                > DAT_GameSynchronyState::instance.finalResults.finalMaxPopulation[playerID]) {
                DAT_GameSynchronyState::instance.finalResults.finalMaxPopulation[playerID]
                    = (short)this->playerDataArray[playerID].currentPopulation;
            }
            if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR) {
                if (this->playerDataArray[playerID].tacticalPowersBarLevel < 7000) {
                    this->playerDataArray[playerID].tacticalPowersBarLevel
                        = this->playerDataArray[playerID].tacticalPowersBarLevel + 1;
                }
                if (this->playerDataArray[playerID].goldDonation > 0) {
                    int goldIncrement = this->playerDataArray[playerID].goldDonation;
                    if (goldIncrement > 10) {
                        goldIncrement = 10;
                    }
                    this->playerDataArray[playerID].currentResources[15]
                        = this->playerDataArray[playerID].currentResources[15] + goldIncrement;
                    this->playerDataArray[playerID].goldDonation
                        = this->playerDataArray[playerID].goldDonation - goldIncrement;
                    if (playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                        DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial = TRUE;
                        DAT_WindowAndDirectDraw::instance.pendingOverlayBltMode = 1;
                    }
                }
            }
        }
        if (this->mapAndTime.monthChanged != 0) {
            this->mapAndTime.populationIndex = this->mapAndTime.populationIndex + 1;
        }
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::updateFoodTypesInStockForAllPlayers, this)();
    }
}
}
