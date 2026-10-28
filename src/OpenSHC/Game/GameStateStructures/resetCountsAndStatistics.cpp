#include "../GameStateStructures.func.hpp"

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004560F0
    void GameStateStructures::resetCountsAndStatistics()
    {
        this->mapAndTime.statCounter198 = 0;
        this->mapAndTime.deerCount = 0;
        this->mapAndTime.rabbitCount = 0;
        this->mapAndTime.camelCount = 0;
        this->mapAndTime.lionCount = 0;
        this->mapAndTime.cageDogCount = 0;
        for (int playerID = 1; playerID < 9; playerID++) {
            if (this->playerDataArray[playerID].goodsDeliveryDelay > 0) {
                this->playerDataArray[playerID].goodsDeliveryDelay = this->playerDataArray[playerID].goodsDeliveryDelay - 1;
            }
            this->playerDataArray[playerID].previousAvailablePeasants
                = this->playerDataArray[playerID].availablePeasantsOrHousedPeasants;
            this->playerDataArray[playerID].previousArmySize = this->playerDataArray[playerID].armySize;
            this->playerDataArray[playerID].previousSiegeWeaponsCount
                = this->playerDataArray[playerID].currentSiegeWeaponCount;
            this->playerDataArray[playerID].previousBlessedPeoplePercentage
                = (short)this->playerDataArray[playerID].blessedPeoplePercentage;
            this->playerDataArray[playerID].totalNeededWorkers = 0;
            this->playerDataArray[playerID].populationCap = 0;
            this->playerDataArray[playerID].liveUnitCount = 0;
            this->playerDataArray[playerID].availablePeasantsAtFire = 0;
            this->playerDataArray[playerID].availablePeasantsOrHousedPeasants = 0;
            this->playerDataArray[playerID].peasantsArrivingAtCampfire = 0;
            this->playerDataArray[playerID].currentPopulation_2 = 0;
            this->playerDataArray[playerID].nonInteractiveUnitCountThisTick = 0;
            this->playerDataArray[playerID].chickenCount2 = 0;
            this->playerDataArray[playerID].motherCountThisTick = 0;
            this->playerDataArray[playerID].childCountThisTick = 0;
            this->playerDataArray[playerID].militaryBuildingScore = 0;
            this->playerDataArray[playerID].armySize = 0;
            this->playerDataArray[playerID].peasantsBeingRecruitedAsTroops = 0;
            this->playerDataArray[playerID].currentSiegeWeaponCount = 0;
            this->playerDataArray[playerID].workingInnsCount = 0;
            this->playerDataArray[playerID].countInns = 0;
            this->playerDataArray[playerID].drunkardUpdateCount = 0;
            this->playerDataArray[playerID].blessedUnitCount = 0;
            this->playerDataArray[playerID].unblessedBlessableUnitCount = 0;
            this->playerDataArray[playerID].priestCount = 0;
            this->playerDataArray[playerID].breadCount = 0;
            this->playerDataArray[playerID].cheeseCount = 0;
            this->playerDataArray[playerID].meatCount = 0;
            this->playerDataArray[playerID].appleCount = 0;
            this->playerDataArray[playerID].totalFood = 0;
            this->playerDataArray[playerID].foodTypesInStock = 0;
            this->playerDataArray[playerID].blessedPeoplePercentage = 0;
            this->playerDataArray[playerID].hasInitialResourceRecievingStarted = 0;
            this->playerDataArray[playerID].areCarnivalUnitsPresent = FALSE;
            this->playerDataArray[playerID].granaryIsAlmostFilledUp = TRUE;
            this->playerDataArray[playerID].isArmouryAlmostFilledUp = 1;
            this->playerDataArray[playerID].farmsWithoutWorkers = 0;
            this->playerDataArray[playerID].countFarms = 0;
            this->playerDataArray[playerID].countWoodcutters = 0;
            this->playerDataArray[playerID].noLabourerBuildingCount = 0;
            this->playerDataArray[playerID].someCount10 = 0;
            this->playerDataArray[playerID].aiBuildingToDemolishID = 0;
            this->playerDataArray[playerID].countIronMines = 0;
            this->playerDataArray[playerID].countPitchRigs = 0;
            this->playerDataArray[playerID].countStoneQuarries = 0;
            this->playerDataArray[playerID].someCount12 = 0;
            this->playerDataArray[playerID].someCount13 = 0;
            this->playerDataArray[playerID].countFletchersPoleturners = 0;
            this->playerDataArray[playerID].countArmorersAndBlacksmiths = 0;
            this->playerDataArray[playerID].countBakers = 0;
            this->playerDataArray[playerID].countBrewers = 0;
            for (int targetSlot = 0; targetSlot < 100; targetSlot++) {
                this->playerDataArray[playerID].ownTargetableBuildings[targetSlot] = 0;
            }
            this->playerDataArray[playerID].top100TargetableBuildingsTracker = 0;
            /*
              clears the 20 counters from rallySearchOffsetsUnk up to and including someCount26 as one array,
              exactly as the original binary does
             */
            for (int counterIndex = 0; counterIndex < 20; counterIndex++) {
                this->playerDataArray[playerID].rallyWaitingCountPerClass[counterIndex] = 0;
            }
            /*
              clears the 10 troop counters from currentArchers up to and including currentTunnelers as one array
             */
            for (int troopIndex = 0; troopIndex < 10; troopIndex++) {
                (&this->playerDataArray[playerID].currentArchers)[troopIndex] = 0;
            }
            this->playerDataArray[playerID].engineerGuildAssemblyCount = 0;
            this->playerDataArray[playerID].laddermanAssemblyCount = 0;
            this->playerDataArray[playerID].tunnelerAssemblyCount = 0;
            this->playerDataArray[playerID].monkAssemblyCount = 0;
            this->playerDataArray[playerID].notLoweredDrawbridgeCount = 0;
            this->playerDataArray[playerID].currentResources[0] = 1;
            if (this->playerDataArray[playerID].aleRate <= 0) {
                this->playerDataArray[playerID].aleRate = 30;
            }
            if (this->playerDataArray[playerID].popupEntity40Cooldown != 0) {
                this->playerDataArray[playerID].popupEntity40Cooldown = this->playerDataArray[playerID].popupEntity40Cooldown - 1;
            }
            if (this->playerDataArray[playerID].popupEntity41Cooldown != 0) {
                this->playerDataArray[playerID].popupEntity41Cooldown = this->playerDataArray[playerID].popupEntity41Cooldown - 1;
            }
        }
    }
}
}
