/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/AI/AICState.hpp'
*/

#pragma once

#include "OpenSHC/AI/AIC/AICSpecification.hpp"
#include "OpenSHC/AI/AINervousDestroyBuildingCategory.hpp"
#include "OpenSHC/AI/AIUnitBehaviourType.hpp"
#include "OpenSHC/AI/AIVUnitType.hpp"
#include "OpenSHC/AI/TileDistancePair.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Game/Player/PlayerID.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AINervousDestroyBuildingCategory;
    using OpenSHC::AI::AIUnitBehaviourType;
    using OpenSHC::AI::AIVUnitType;
    using OpenSHC::AI::TileDistancePair;
    using OpenSHC::AI::AIC::AICSpecification;
    using OpenSHC::Commands::MappersEnum;
    using OpenSHC::Game::Player::PlayerID;
    using OpenSHC::Game::Resources::ResourceType;
    using OpenSHC::Map::Units::UnitType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

    // SIZE: 0x00006D90
    class AICState {
    public:
        AICSpecification aics[20]; // 0x00000000 length: 13520
        undefined4 aiBorderTilesIndex; // 0x000034D0 length: 4
        TileDistancePair aiBorderTiles[1000]; // 0x000034D4 length: 8000
        byte unused01[512]; // 0x00005414 length: 512
        short tribeIDArray[1000]; // 0x00005614 length: 2000
        int tribeUIDArray[1000]; // 0x00005DE4 length: 4000
        undefined4 aiTauntResponseTimeWindow; // 0x00006D84 length: 4
        byte unused02[8]; // 0x00006D88 length: 8

    private:
        AICState(AICState const&);
        void operator=(AICState const&);

    public:
        AICState() {};
        ~AICState() {};

        // Constructor
        /**
         * AICState constructor: loads the initial AIC personality table (setInitialAIC) and resets
         * aiTauntResponseTimeWindow.
         */
        AICState* Constructor_AICState();

        /**
         * Zeroes the AIC parameter blocks of the global DAT_AICState: 20 entries of 0x2A4 bytes each (ignores
         * this).
         */
        void wipeAICMemory();

        /**
         * Writes the built-in default AIC (AI character) parameter set #1 into DAT_AICState.aics[aicID]: economy,
         * popularity/tax, trade, recruitment, defense and attack settings; TargetChoice = AITC_PLAYER.
         */
        void setAICParameters_01(int aicID);

        /**
         * Writes the built-in default AIC parameter set #2 into DAT_AICState.aics[aicID] (economy, popularity/tax,
         * trade, recruitment, defense, attack); TargetChoice = AITC_BALANCED.
         */
        void setAICParameters_02(int aicID);

        /**
         * Writes the built-in default AIC parameter set #3 into DAT_AICState.aics[aicID] (economy, popularity/tax,
         * trade, recruitment, defense, siege engines, attack); TargetChoice = AITC_GOLD.
         */
        void setAICParameters_03(int aicID);

        /**
         * Fills the hard-coded default AIC record DAT_AICState.aics[aiCharacterId] (popularity/tax thresholds, farm
         * list, building and stock limits, trade, workshop settings, recruitment, defense, raid, siege and attack
         * parameters); only assigns fields. setInitialAIC calls it with id 4 (readers index aics[aiType-1]); units:
         * crossbowmen/archers defend, horse-archer raids, swordsmen + pikemen main attack, catapult/trebuchet/fire-
         * ballista siege, TargetChoice=AITC_CLOSEST. Lord UNVERIFIED: id 4 = Wolf only per the community AITypeA
         * enum; code (getLordTypeForPlayer) only puts it in the lord-type-0 (European) group.
         */
        void setAICParameters_04(int aiCharacterId);

        /**
         * Fills the default AIC record DAT_AICState.aics[aiCharacterId]; only assigns fields. setInitialAIC calls
         * it with id 5; units: Arabian swordsmen/archers and fire throwers defend, horse-archer raids, Arabian
         * swordsmen main attack, slaves as diggers, fire-ballista/catapult siege, TargetChoice=AITC_GOLD. Lord
         * UNVERIFIED: id 5 = Saladin only per the community AITypeA enum; code (getLordTypeForPlayer) only puts it
         * in the lord-type-1 (Arabian) group.
         */
        void setAICParameters_05(int aiCharacterId);

        /**
         * Fills the default AIC record DAT_AICState.aics[aiCharacterId]; only assigns fields. setInitialAIC calls
         * it with id 6; units: fire throwers (DefUnit1) and Arabian archers defend, slave raids, Arabian swordsmen
         * main attack, three fire ballistas, many sellResource entries, TargetChoice=AITC_BALANCED. Lord
         * UNVERIFIED: id 6 = Caliph only per the community AITypeA enum; code (getLordTypeForPlayer) only puts it
         * in the lord-type-1 (Arabian) group.
         */
        void setAICParameters_06(int aiCharacterId);

        /**
         * Fills the default AIC record DAT_AICState.aics[aiCharacterId]; only assigns fields. setInitialAIC calls
         * it with id 7; units: slingers defend and raid, Arabian swordsmen main attack, no siege engines and
         * AttMaxEngineers=0, sells almost every good (sellResource02..15), TargetChoice=AITC_CLOSEST. Lord
         * UNVERIFIED: id 7 = Sultan only per the community AITypeA enum; code (getLordTypeForPlayer) only puts it
         * in the lord-type-1 (Arabian) group.
         */
        void setAICParameters_07(int aiCharacterId);

        /**
         * Fills the default AIC record DAT_AICState.aics[aiCharacterId]; only assigns fields. setInitialAIC calls
         * it with id 8; units: archers + pikemen defend, archer raids, swordsmen/pikemen main attack, siege list of
         * 3 catapults, a battering ram and 2 trebuchets, 3 tunnelers, TargetChoice=AITC_CLOSEST. Lord UNVERIFIED:
         * id 8 = Richard only per the community AITypeA enum; code (getLordTypeForPlayer) only puts it in the lord-
         * type-0 (European) group.
         */
        void setAICParameters_08(int aiCharacterId);

        /**
         * Fills the default AIC record DAT_AICState.aics[aiCharacterId]; only assigns fields. setInitialAIC calls
         * it with id 9; units: archers/crossbowmen defend, knight raids, swordsmen main attack, six trebuchets,
         * TargetChoice=AITC_GOLD. Lord UNVERIFIED: id 9 = Frederick only per the community AITypeA enum; code
         * (getLordTypeForPlayer) only puts it in the lord-type-0 (European) group.
         */
        void setAICParameters_09(int aiCharacterId);

        /**
         * Fills the default AIC record DAT_AICState.aics[aiCharacterId]; only assigns fields. setInitialAIC calls
         * it with id 10; units: one knight slot plus five archer slots for defense, knight raids, spearmen main
         * attack, no siege engines and AttMaxEngineers=0, TargetChoice=AITC_BALANCED. Lord UNVERIFIED: id 10 =
         * Philipp only per the community AITypeA enum; code (getLordTypeForPlayer) only puts it in the lord-type-0
         * (European) group.
         */
        void setAICParameters_10(int aiCharacterId);

        /**
         * Fills the default AIC record DAT_AICState.aics[aiCharacterId]; only assigns fields. setInitialAIC calls
         * it with id 11; units: Arabian archers + fire throwers defend, horse-archer raids, Arabian swordsmen main
         * attack, trebuchet + fire ballistas, TargetChoice=AITC_BALANCED. Lord UNVERIFIED: id 11 = Wazir only per
         * the community AITypeA enum; code (getLordTypeForPlayer) only puts it in the lord-type-1 (Arabian) group.
         */
        void setAICParameters_11(int aiCharacterId);

        /**
         * Fills the default AIC record DAT_AICState.aics[aiCharacterId]; only assigns fields. setInitialAIC calls
         * it with id 12; units: European + Arabian archers defend, Arabian swordsman raids and main attack,
         * catapults + ballista, TargetChoice=AITC_GOLD. Lord UNVERIFIED: id 12 = Emir only per the community
         * AITypeA enum; code (getLordTypeForPlayer) only puts it in the lord-type-1 (Arabian) group.
         */
        void setAICParameters_12(int aiCharacterId);

        /**
         * Fills the default AIC record DAT_AICState.aics[aiCharacterId]; only assigns fields. setInitialAIC calls
         * it with id 13; units: Arabian archers defend, assassin raids and main attack (AttMaxAssassins=40), a
         * single catapult, TargetChoice=AITC_CLOSEST. Lord UNVERIFIED: id 13 = Nizar only per the community AITypeA
         * enum; code (getLordTypeForPlayer) only puts it in the lord-type-1 (Arabian) group.
         */
        void setAICParameters_13(int aiCharacterId);

        /**
         * Fills the default AIC record DAT_AICState.aics[aiCharacterId]; only assigns fields. setInitialAIC calls
         * it with id 14; units: crossbowmen (plus a fire thrower and an assassin slot) defend, macemen raid and
         * form the main attack, catapults + fire ballistas, TargetChoice=AITC_CLOSEST. Lord UNVERIFIED: id 14 =
         * Sheriff only per the community AITypeA enum; code (getLordTypeForPlayer) only puts it in the lord-type-0
         * (European) group.
         */
        void setAICParameters_14(int aiCharacterId);

        /**
         * Fills the default AIC record DAT_AICState.aics[aiCharacterId]; only assigns fields. setInitialAIC calls
         * it with id 15; units: archers defend, knight raids, swordsmen main attack, trebuchets,
         * TargetChoice=AITC_BALANCED. Lord UNVERIFIED: id 15 = Marshal only per the community AITypeA enum; code
         * (getLordTypeForPlayer) only puts it in the lord-type-0 (European) group.
         */
        void setAICParameters_15(int aiCharacterId);

        /**
         * Fills the default AIC record DAT_AICState.aics[aiCharacterId]; only assigns fields. setInitialAIC calls
         * it with id 16; units: archers defend, monks (UT_E_MONK 0x25) raid and form the main attack, four
         * catapults, TargetChoice=AITC_BALANCED. Lord UNVERIFIED: id 16 = Abbot only per the community AITypeA
         * enum; code (getLordTypeForPlayer) only puts it in the lord-type-0 (European) group.
         */
        void setAICParameters_16(int aiCharacterId);

        /**
         * For each player slot, zeroes the 0xEA4-byte AI part of playerDataArray[i] (starting at aiFarmIndex) when
         * the slot is human (currentPlayerFullIDArray[i] != -1, read as currentAIArray[i-0x1B]) or has no AI
         * (currentAIArray[i] == 0), i.e. resets AI state of slots that are not AI-controlled.
         */
        void clearPlayerDataInformationChunk();

        /**
         * Picks the target player for an AI tribe of `owner` according to its AIC TargetChoice, measuring from the
         * owner's campground entry: AITC_PLAYER = closest human enemy, AITC_CLOSEST = closest enemy, AITC_GOLD =
         * richest enemy, AITC_BALANCED = lowest score (two per-player counters weighted 5x/1x + gold/100 +
         * 2*distance). Only players of another team with a living lord count; if none matched, falls back to the
         * closest such enemy, and writes the result to TribesState.tribes[tribe].targetPlayer_outpost (unchanged if
         * no enemy at all).
         */
        void setTargetForTribeBasedOnTargetChoiceLogic(int owner, int tribe);

        /**
         * AI tax/ration controller: sets aiPopularityDecisionValue to 2 (popularity <= criticalPopularity), 1 (<=
         * lowestPopularity), 0 (>= highestPopularity) or leaves it. 2: taxes=2, rations 0/2/3/4 by food (<1, <5,
         * <=8, >8); 1: taxes step down to taxesMin, rations 0/2/3 (food <1, <11, else); 0: taxes +1 towards
         * taxesMax (set to taxesMax if already >=), but while popularity is below storedPopularityPercent they
         * instead drop by 1 down to a floor of 4-6 (by previousAvailablePeasants); rations 0 if food < 11 else 2.
         * Then (always in case 1, in case 0 only if food >= 11) rations become 4 when doubleRationsFoodThreshold !=
         * 0 and totalFood >= it; finally taxes clamp to 0..11, rations to 0..4.
         */
        void aiUpdateTaxesAndRations(int playerID);

        /**
         * For an AI player, sets resourcesToAcquireArray[r] = AIC tradeAmountFood (+0x98) for each food/farm good
         * whose stock is below the AIC minimum: apples (0xD, minimumApples +0x84), cheese (0xB, +0x88), bread (0xA,
         * +0x8C), wheat (9, +0x90) and hops (3, +0x94). A negative minimum (e.g. -1) disables the item (0 too,
         * except it is not explicitly checked for apples).
         */
        void setFoodBuyPlan(int playerID);

        /**
         * Returns the AIC buildInterval of playerID's AI character (0 for non-AI players). The decompiler resolves
         * the address as DAT_EntityState.seagullArray + aiType*0x2A4 + 0x24E8, which is really
         * DAT_AICState.aics[aiType-1].buildInterval (+0x78).
         */
        int getAIBuildInterval(int playerID);

        /**
         * Returns the AIC resourceRebuildDelay (+0x7C) of the player's AI character (0 for non-AI players); address
         * shown via the mis-resolved DAT_EntityState.seagullArray base.
         */
        int getResourceRebuildDelay(int playerID);

        /**
         * Returns the farm building type at the player's current aiFarmIndex in its AIC farm list (farm1..farm8,
         * +0x30), or 0 for non-AI players. Address expressed via the mis-resolved DAT_EntityState.seagullArray
         * base.
         */
        int aiFarmChoice(PlayerID playerID);

        /**
         * Advances the player's aiFarmIndex (wrapping after 7, or to 0 when the next AIC farm slot is empty) and
         * returns the farm building type in that slot of the AIC farm list (offset 0x30). Returns 0 for non-AI
         * players.
         */
        int setNextFarmTypeToBuild(PlayerID playerID);

        /**
         * Returns TRUE if an AI player should build another farm: always when it has none; otherwise only if farm
         * count < AIC maxFarms and population per farm >= AIC populationPerFarm.
         */
        BOOLEnum aiShouldBuildFarm(int playerID);

        /**
         * Returns TRUE if an AI player should build another woodcutter's hut: needs map wood (totalWoodAvailable >
         * 0) and populationPerWoodcutter > 0; refuses when hut count >= maxWoodcutters, or > 5 huts with map wood <
         * 91, or > 2 huts with map wood < 31; otherwise requires population per hut (count min 1) >=
         * populationPerWoodcutter.
         */
        BOOLEnum aiShouldBuildWoodcutter(int playerID);

        /**
         * Returns nonzero if an AI player should build another quarry: populationPerQuarry > 0, quarry count < AIC
         * maxQuarries (offset 100) and population per quarry (count min 1) >= populationPerQuarry.
         */
        uint aiShouldBuildQuarry(PlayerID playerID);

        /**
         * Decides whether the AI player needs another ox tether (none if it already has >= 10). Clears
         * playerData.quarryNeedingOxTether, walks the player's quarries pruning stale entries from each quarry's 3
         * linked-ox-tether slots, and stores there the quarry to serve: the first one with no valid tether (returns
         * 1), else the one with the highest stockpile-stone per tether if that ratio > 20 (returns 1). Returns 0
         * otherwise. The playerID parameter is reused as the best ratio.
         */
        undefined4 aiRequiresExtraOxtethers(int playerID);

        /**
         * Returns nonzero if an AI player should build another iron mine: populationPerIronmine > 0, mine count <
         * AIC maxIronmines and population per mine (count min 1) >= populationPerIronmine.
         */
        uint aiShouldBuildIronMine(PlayerID playerID);

        /**
         * Returns nonzero if an AI player should build another pitch rig: AIC populationPerPitchrig (+0x60) > 0,
         * pitch-rig count < maxPitchrigs (+0x70) and population per rig (count min 1) >= populationPerPitchrig. The
         * inline decompiler comments mentioning lowest/criticalPopularity are wrong (those fields are at
         * +0x1C/+0x18).
         */
        uint aiShouldBuildPitchrig(PlayerID playerID);

        /**
         * Returns TRUE if the AI should NOT place a hovel now. Only applies to M_MAPPER_HOVEL with populationCap >
         * 12: a hovel is allowed only when population has reached the cap, previousAvailablePeasants < 5,
         * averagePopulationGrowthUnk < 5 and popularity >= 5000; otherwise TRUE. Other building types (or cap <=
         * 12) return FALSE.
         */
        BOOLEnum shouldNotBeBuildingHovel(PlayerID playerID, MappersEnum mapperType);

        /**
         * For negative-fear-factor buildings (gallows, stocks, cess pits, burning stake, gibbet, dungeon, racks,
         * chopping block, dunking stool) returns TRUE (postpone) while popularity < 5000; otherwise increments the
         * per-player aivNegativeFearFactorDelay and keeps returning TRUE until it reaches 100, then resets it and
         * allows building (FALSE). The counter does not advance while popularity < 5000. Other types return FALSE.
         */
        BOOLEnum shouldWaitWithBuildingNegativeFearFactor(int playerID, MappersEnum mapperType);

        /**
         * For positive-fear-factor buildings (gardens, maypole, statues, shrines, dancing bear, ponds) increments
         * aivPositiveFearFactorDelay and returns TRUE (postpone) until it reaches 200, then resets it and returns
         * FALSE. Other types return FALSE.
         */
        BOOLEnum shouldWaitWithBuildingAPositiveFearFactor(int playerID, MappersEnum mapperType);

        /**
         * For an AI player with 8 < population <= populationCap and averagePopulationGrowthUnk > 20, demolishes its
         * first hovel (refunding 50% via giveBackResourceForDestroyedBuilding) and returns TRUE; otherwise (or with
         * no hovel) FALSE.
         */
        BOOLEnum destroyHouse(int playerID);

        /**
         * AI woodcutter cleanup: if the map has no wood left, demolishes the player's first woodcutter's hut;
         * otherwise, when it has >= 21 wood, noLabourerBuildingCount >= 2 and someCount10 >= 25, demolishes the
         * building whose ID is stored in someCount11. Resets the AIV heat-map countdown at the building and refunds
         * 50%. Returns TRUE if something was demolished.
         */
        BOOLEnum tryDestroyWoodcuttersHut(int playerID);

        /**
         * Called from the woodcutter's hut update for AI-owned (non-human, AI slot set, not solitary mode) huts
         * with a positive counter in unknownTickRelatedValue: if the hut has no worker and the counter is >= 20 the
         * hut is demolished (heat-map reset, 50% refund) and 1 is returned; if it has a worker the counter is
         * decremented once when monthTicks == owner. Returns 0 otherwise.
         */
        undefined4 destroyBuildingIfNoWorker(int buildingID);

        /**
         * NAME? Returns TRUE if the AI must not place mapperType now: while aiNervousActionsTracker > 0 everything
         * except trade post, European/Arab barracks, armoury and granary is blocked; otherwise, while
         * aiBuildingDestroyChoiceTracker > 0, everything except trade post and granary is blocked. Those listed
         * buildings are the ones still ALLOWED, so the name is inverted (and there is no mercenary-post check
         * besides BARRACKS_ARAB).
         */
        BOOLEnum shouldNotBuildMarketArmoryGranaryBarracksMercenarypost(int playerID, MappersEnum mapperType);

        /**
         * AI economy guard: updates per-player 'stock empty' counters for wood, iron, flour, hops and ale
         * (wood/iron/flour/hops ones zeroed when no consuming workshop exists) and bumps someResourceCounter, then
         * sets snoozedBuildings[BuildingType]: wells/water pots when no fire, all farms unstaffed and gold < 500;
         * woodcutter, quarry/ox tether, iron mine, pitch rig, hunter, farms and mill while nervous or (some) when
         * population < 10 with food/farm shortages; fletcher/poleturner/blacksmith/armourer/tanner when not nervous
         * and (no armory or their input counter > 36); bakery/brewery/inn when nervous or flour > 36 / hops > 72 /
         * ale > 72. If canStartSpending, plans market purchases of 5 wood, 2 iron, 2 flour or 2 hops when the
         * respective counter exceeds 36 (hops 72) and no purchase of that good is pending.
         */
        void planToBuyWhenLowOnResourceAndSnoozeBuildings(int playerID);

        /**
         * Sets the produced item of a newly placed AI workshop from its AIC setting: blacksmith (blacksmithSetting
         * +0xC8) 0x16 -> sword else mace, fletcher (+0xCC) 0x11 -> bow else crossbow, poleturner (+0xD0) 0x13 ->
         * spear else pike; a setting of -999 lets chooseProductionItemType decide. Writes producedItemType and
         * producedItemTypeNext; other building types are untouched.
         */
        void setupWorkshopProductionType(int playerID, int buildingID);

        /**
         * AI market sale: computes getSellPrice for amount of resourceType, adds it to the player's final-results
         * gold, current gold and marketGold, removes the goods (processResourceLoss) and shows the trade visual
         * effect.
         */
        void sellGoods(int playerID, ResourceType resourceType, int amount);

        /**
         * AI market purchase: if processResourceGain can store amount of resourceType, subtracts getBuyPrice from
         * the player's gold and marketGold, shows the trade visual effect and returns TRUE; otherwise FALSE (no
         * gold spent).
         */
        BOOLEnum buyGoods(int playerID, ResourceType resourceType, int amount);

        /**
         * Clears the 11 attackUnitRequired flags, sets each one whose AIC max for that attack role is not yet
         * reached (engineers capped at min(AttMaxEngineers, 4*currentAttackWave), digging units only if the
         * attacked player owns > 5 moats, assassins, AttUnit2, laddermen, tunnelers, patrol, backup, engage, siege-
         * defense, main/AttMaxDefault), then returns the unitBehaviourType of a random flagged entry
         * (SEC_RNG.currentNumber2 % count). Returns AIUBT_ATTUNITMAIN if none or not an AI.
         */
        AIUnitBehaviourType randomlySelectAttackUnitTypeToRecruit(int playerID);

        /**
         * Maps an AI attack behaviour type to the unit type to recruit: fixed engineer/assassin/ladderman/tunneler,
         * otherwise the AIC AttDiggingUnit/AttUnit2/AttUnitPatrol/Backup/Engage/SiegeDef; for AIUBT_ATTUNITMAIN
         * cycles aiAttUnitMainChoiceIndex through AttUnitMain1..4 (reset to 0 on an empty slot or index > 3). Any
         * other behaviour type returns AttUnitMain1; non-AI players get 0.
         */
        UnitType getUnitTypeForUnitBehaviourType(int playerID, AIUnitBehaviourType unitBehaviourType);

        /**
         * Returns the AIV unit-type index (position in SkirmishDefinedData.SomeAIUnitTypeArray, 0..19) of a unit,
         * using unitTypeToChangeInto for peasants in training. If param_2 is set, the owner is not AIT_CALIPH and
         * the player has locations in AIV slot 13, ranged units (archers, crossbowmen, Arab archers, slingers, fire
         * throwers) are mapped to slot 13 (AIVUT_SLAVE_OR_RANGED). Returns AIVUT_NONE if not found.
         */
        AIVUnitType getUnitTypeIndexForUnitID(int unitID, int useSlot13ForRanged);

        /**
         * When an AI trebuchet (meta index 2) or fire ballista (3) unit is produced by buildingID, finds the first
         * AIV location of that siege type's slot with a positive location value whose
         * aiSiegeCreationInformation[meta][i].buildingID matches, stores the unit ID and uid there and clears the
         * building ID. Skipped for non-AI players, solitary mode and other unit types.
         */
        void generateSiegeCreationInformation(int playerID, int buildingID, int unitID);

        /**
         * If an AI player flagged isEngineerRequired, canStartSpending is set, gold + AIC
         * defSiegeEngineGoldThreshold (+0x118, addressed via the mis-resolved seagullArray base) exceeds 29, and
         * its engineersGuild building is valid, recruits one engineer there (nonEuroRecruit) and clears the flag.
         */
        void aiRecruitEngineers(int playerID);

        /**
         * Creates a new tribe for playerID and moves up to `count` of the player's living (logicalState normal, not
         * dying) engineers into it, removing them from their previous tribe. Eligible engineers have
         * aiUnitBehaviourType neither 0x16 (AIUBT_HARASS_SIEGE) nor 10 (AIUBT_ENGINEERING), engineerRelatedUnk == 0
         * and an idle-like state (0x69, 2 or US_IDLEUnk). Returns the new tribe ID.
         */
        int assignRequiredIdleEngineersToNewTribe(int playerID, int count);

        /**
         * NAME? Creates a new tribe for playerID and adds up to unitCount of its living, tribeless (tribeID == 0)
         * engineers with aiUnitBehaviourType 10 (AIUBT_ENGINEERING) that are not in US_STAND_UPUnk state; returns
         * the tribe ID. It builds a tribe rather than a UI selection.
         */
        int addEngineersToSelection(int playerID, int unitCount);

        /**
         * Moves every living (logicalState normal, not dying) unit of playerID with aiUnitBehaviourType 6 into the
         * AI tribe stored in aiTribeIDs[0xA6] (166), removing it from its current tribe if different.
         */
        void addUnitsToTribe166(int playerID);

        /**
         * Moves every living unit of the player with aiUnitBehaviourType 7 into the AI tribe aiTribeIDs[0xA7],
         * removing it from its current tribe if different. Its only caller is giveMoveCommandToSortieUnits, so type
         * 7 is presumably the sortie group.
         */
        void syncBehaviourType7UnitTribes(int playerID);

        /**
         * Sets the unit's aiUnitBehaviourType to 5, adds it to the owner's AI tribe slot 10 (the moat-digger tribe
         * per the function name; recreated if missing or its uid is stale) and sets that tribe's stance to
         * USE_DEFENSIVE.
         */
        void aiAddUnitToMoatDiggerTribe(int unitID);

        /**
         * Returns TRUE if the unit's type is listed in SkirmishDefinedData.RangedAndArmoredUnits.
         */
        BOOLEnum unitIDIsRangedOrArmored(int unitID);

        /**
         * Returns the cached AI tribe in aiTribeIDs[unitSelectionTypeIndex] if its uid still matches; otherwise
         * creates a new tribe for the player and caches its id/uid.
         */
        int getOrCreateTribeForUnitType(int playerID, int unitSelectionTypeIndex);

        /**
         * Among the player's AI tribes for an AIV unit type (one per AIV location of that type, starting at
         * AITribeIDOffsetForAIVUnitType[type]; for spearmen, macemen and horse archers capped at AIC
         * defWallPatrolGroups +0x114) returns the smallest; a missing/stale slot gets a new tribe immediately.
         * Caches the chosen id/uid; returns 0 for non-AI players or no locations.
         */
        int smallestTribeOfUnitType(int playerID, AIVUnitType aivUnitType);

        /**
         * Returns the smallest of the player's first tribeCount patrol tribes (aiTribeIDs[0xAA+i]); a missing or
         * stale slot gets a newly created tribe instead. Re-caches the chosen id/uid; returns 0 if tribeCount <= 0.
         */
        int getSmallestPatrolTribe(int playerID, int tribeCount);

        /**
         * Finds the unit's type (or unitTypeToChangeInto) in DefenseTribesUnitTypeArray and maps the index range to
         * a defensive AI tribe slot (0xB4..0xB9; per the in-code comments knights, horse archers, other ranged,
         * spear/mace/monk/slave/assassin, swordsmen/pikemen, siege). Returns that tribe, creating and caching a new
         * one if missing or stale; 0 if the type is not listed.
         */
        int getRaidTribeForUnit(int playerID, int unitID);

        /**
         * NAME? Does not add the unit: maps aiUnitBehaviourType to a base tribe slot
         * (AIUnitBehaviourTypeMapping[type-10]) and, if the AIC group count for patrol/backup/siege-def/main (slots
         * 0xF/0xBA/0xBE/0xC0) is > 1, returns the smallest of those tribes (a missing/stale slot gets a new tribe);
         * otherwise returns the single slot's tribe (created if needed). Caches the chosen id/uid. param_2 is
         * unused.
         */
        int addUnitToSmallestBehaviourTypeTribe(
            undefined4 playerID, undefined4 param_2, undefined4 aiUnitBehaviourType);

        /**
         * Scans up to min(maxAmount,10) AI tribe slots starting at AITribeIDOffsetForAIVUnitType[1] for a free or
         * stale slot (tribe id 0 or uid mismatch). If checkOnly, returns 1 when such a slot exists; otherwise
         * creates a new tribe for the player, stores its id/uid in that slot and returns the tribe id. Returns 0 if
         * no free slot.
         */
        int checksAndGenerateAITribesForPlayerIfNotExisting(int playerID, int maxAmount, BOOLEnum checkOnly);

        /**
         * Returns TRUE if the tribe is considered busy: more than 10% of its units moving (only when
         * includeMoving), more than 10% shooting (unless ignoreShooting), or more than 10% attacking.
         */
        BOOLEnum checkTribeActivityPercentages(int tribeID, BOOLEnum ignoreShooting, BOOLEnum includeMoving);

        /**
         * Orders tribe to move to the player's keep (keep building x+3, y+4) if the player has a keep.
         */
        void sendUnitsToKeep(int tribeID, int playerID);

        /**
         * If the player has a campground, orders the tribe to move to its entry tile and sets the tribe stance to
         * aggressive.
         */
        void sendUnitsToCampfire(int tribeID, int playerID);

        /**
         * Controls the player's moat-digging AI tribe (aiTribeIDs[10]): if valid, non-empty and percentageSomething
         * <= 80, sends it back to the keep when no unfinished moat tiles remain, otherwise finds the nearest
         * friendly moat tile to the tribe's lead unit and, if updateTribeRallyFlags returns 0, gives a DIG_MOAT
         * instruction there with stand-ground stance. iVar1 is reused for the moat-tile count, the lead unit id and
         * the rally-flag result.
         */
        void digNearestMoat(int playerID);

        /**
         * Returns TRUE if the tribe owner's units can path from the path-connection area of the tribe's lead unit
         * tile to the area of the target tile.
         */
        BOOLEnum canNavigateUnitsFromTileToTargetTile(int tribeID, int tile);

        /**
         * AI harassing siege engines: requires an AI player with >=500 gold and AIC HarassingSiegeEnginesMax
         * (+0x1EC) > 0; counts down harrasingEngineRecruitTimeout, and acts only while harassingSiegeEnginesCount <
         * max and unknownHarrassingSiegeRelated < 20. If the engineer tribe (slot 0xA5) is missing/has <2 units it
         * recruits an engineer (behaviour 0x16) from the engineers guild into that tribe; otherwise it cycles
         * through AIC HarassingSiegeEngine1..8 (+0x1CC), places that siege tent near the engineers guild and orders
         * the tribe to build it. Afterwards sets siegeTargetPlayerID = attackedPlayerID on every living
         * catapult/fire ballista with aiUnitBehaviourType 0x15 (no owner check) and resets the timeout to 8.
         */
        void recruitHarrassingSiegeEngines(int playerID);

        /**
         * Recruits one ranged sortie unit (AIC SortieUnitRanged +0x150, not engineer/ladderman/tunneler) from
         * barracks (type < 0x46) or mercenary post when SortieUnitRangedMin (+0x14C) >= 0, totalTroopsType6 <
         * unknownCounter_01/2 + SortieUnitRangedMin, an idle peasant exists and canStartSpending; the unit gets
         * behaviour 6 and joins tribe slot 0xA6. On failure due to a missing resource (fail reason 2), sets
         * resourcesToAcquireArray[required] to AIC tradeAmountEquipment (+0x9C) if > 0.
         */
        void aiRecruitSortieRangedUnits(int playerID);

        /**
         * Recruits one melee sortie unit (AIC SortieUnitMelee +0x158, not engineer/ladderman/tunneler) from
         * barracks (type < 0x46) or mercenary post while totalTroopsType7 < SortieUnitMeleeMin (+0x154, must be >=
         * 0), an idle peasant exists and canStartSpending; the unit gets behaviour 7 and joins tribe slot 0xA7. On
         * missing-resource failure (fail reason 2) sets resourcesToAcquireArray[required] to AIC
         * tradeAmountEquipment (+0x9C) if > 0.
         */
        void aiRecruitSortieMeleeUnits(int playerID);

        /**
         * Commands the ranged sortie tribe (slot 0xA6): decays unknownCounter_01 (capped at 50), tops up the tribe
         * if it lags totalTroopsType6 by more than 5. If not nervous or the keep is enclosed: when size <
         * SortieUnitRangedMin (AIC +0x14C) it only sets aggressive stance; otherwise moves it aggressively to
         * someXPosition/someYPosition if set, else sends it to the keep. If nervous and keep not enclosed, sends it
         * to the keep. Stance always ends aggressive. NAME? better commandRangedSortieTribe (0xA6 = 166).
         */
        void instructTribe166ToMove(int playerID);

        /**
         * Commands the melee sortie tribe (slot 0xA7): resyncs it if smaller than totalTroopsType7-1. If the AI is
         * not nervous: with fewer than SortieUnitMeleeMin (AIC +0x154) units it only sets aggressive stance;
         * otherwise moves it aggressively to the last encountered enemy troop unit when that unit is valid and
         * reachable, else sends it to the keep. If nervous, sends it to the keep.
         */
        void giveMoveCommandToSortieUnits(int playerID);

        /**
         * Called from building update functions: outside GM_SOLITARY mode, appends the building to its owner's
         * top100TargetableBuildings list (max 100) if it is not burning.
         */
        void addBuildingToTargetableBuildings(int buildingID);

        /**
         * Walks the player's targetable-building list and returns the building whose type has the best (lowest-
         * index) priority in BuildingTargetPrioritySet1 (46 entries); 0 if none match.
         */
        int selectBuildingFromAListOfBuildingTypes(int playerID);

        /**
         * Like selectBuildingFromAListOfBuildingTypes but the priority list is chosen from the current RNG low 3
         * bits (0-1: Set3, 2-3: Set2, 4-7: Set1; RNG not advanced); returns the targetable building with the best
         * priority in that list. NAME? not uniformly random; picks the best-priority building using a randomly
         * chosen priority set.
         */
        int chooseRandomBuildingIDFromPlayersArrayOfBuildings(int playerID);

        /**
         * Outer-patrol target selection: with AIC OuterPatrolGroupsCount (+0x174) > 0, advances a rotating counter
         * (someCounter2) and scans the targetable building list circularly from (count/groups)*groupIndex +
         * counter, returning the first building whose type appears in BuildingTargetPrioritySet1; 0 if none.
         */
        int getTargetableBuildingForPlayerID(int playerID, int patrolGroupIndex);

        /**
         * Returns a uniformly random entry of the player's targetable-building list (advances RNG); 0 if the list
         * is empty. Second argument is unused. NAME? does not consult any list of building types.
         */
        int selectRandomBuildingIDFromListOfBuildingTypes(int playerID, undefined4 unusedArg);

        /**
         * Decides whether the AI may launch its attack: TRUE if requestStateUnk==1. Zeroes
         * currentWaveRandomAttackingStrength if the attacked player's totalTroopValue <= 100, then requires
         * totalAttackTroops-engineers >= AttForceBase (+0x1F4) + that strength. With coordination level > 0 it
         * checks living AI teammates: any with aiPlayerState != 0 -> TRUE; otherwise counts ready vs unready ones
         * and returns FALSE while ready < coordination level and some are unready and patience (incremented per
         * call) is < 49; in campaign missions patience never runs out.
         */
        BOOLEnum aiShouldAttackOrWaitForTeamCoordination(int playerID);

        /**
         * Starts a new attack wave: increments currentAttackWave and sets currentWaveRandomAttackingStrength =
         * AttForceRandom(+0x1F8)*rand%100/100 + wave*5 (wave*7 if gold > 10000), capped at 200.
         */
        void setCurrentAttackStrength(int playerID);

        /**
         * Sets currentAttackRaidParameter = variance*rand%100/100 where variance is AIC RaidUnitsRandom (+0x1A8): 0
         * if gold < 1000, doubled if gold >= 5000, and -(RaidUnitsBase(+0x1A4)/2) if the raided player
         * (attackedPlayerID_2Unk) has < 500 gold.
         */
        void setCurrentAttackRaidParameter(int playerID);

        /**
         * Fills DAT_TroopValueState.attackInfo with the attack start data: path connection, AI zone and zone size
         * at the player's shortestDistanceTile, sets unknownOne_0x20f90=1, and stores the path connection of the
         * attacked player's campground entry (keepCon).
         */
        void setAttackPrimeInfo(int playerID, int attackedPlayerID);

        /**
         * Records the attacked player id in this player's attackInfo slot, clears the 0x13A10-byte layer at
         * 0x1E94158, recomputes the AI zone layer for the attacked player (flag = keep-to-keep reachable) and calls
         * updateWalkLayerAndAIPathCostLayer(0x6E, borderDistance, connection of the player's campground entry,
         * playerID). borderDistance is 50/70/98 depending on the attacked player's unknownPathBorderDistanceRelated
         * (<91 / <121 / else), or 0 when useBorderDistance is 0.
         */
        void recomputeAIPathCostToAttackedKeep(int playerID, int useBorderDistance);

        /**
         * At skirmish launch, for each player slot 1..8 writes the slot index into attackInfo.playerInfo[i]; for
         * active players (human or AI) it clears the AI zone layer, runs computeAIZoneLayer(player,2,1) and
         * updateWalkLayerAndAIPathCostLayer(0xFC,0,1,player), stores the resulting PathFindingState.distance in the
         * player's unknownPathBorderDistanceRelated and then sets the playerInfo field to 1.
         */
        void recomputeAttackAIZone();

        /**
         * Player-1-only variant of recomputeAttackAIZone (used on map load, ownership switch and in the map
         * editor): clears the AI zone layer, recomputes zone and path cost (0xFC) and stores the distance in player
         * 1's unknownPathBorderDistanceRelated; sets attackInfo.playerInfo[0] field to 1.
         */
        void recomputeAIZonerLayer();

        /**
         * Finds the best approach tile toward the attacked keep: recomputes the path-cost layer (fills
         * aiBorderTiles), scores every border tile by axis distance from the campground entry (x in the local
         * misnamed campYOrBestTile, y in campYOrBestDistance) plus unitDeathHeatMap, picks the minimum (< 100000)
         * and stores it as shortestDistanceTile/X/Y and as the player's signpost entry, removes any tree there and
         * runs a linkage path search (radius 2000), storing the destination options.
         */
        void computeEnemyKeepApproachTile(int playerID);

        /**
         * Removes any tree at the player's shortestDistance tile, runs a linkage path search there (radius 4000)
         * and sets destination pairs for the attack on attackedPlayerID.
         */
        void setNextMoveLocationForUnits(int playerID);

        /**
         * Removes any tree at the shortestDistance tile, runs a linkage path search (radius 10000) and sets move
         * destination pairs toward attackedPlayerID with a per-player attackInfo value plus 8 (Sultan) or 20 (other
         * AIs).
         */
        void removeOrganismsAndSetMoveDestinationPairs(int playerID);

        /**
         * Retreats all AI attack tribes (MaxAttackTribes1 table of type/count pairs) of the player: stance
         * aggressive; tribe type 0xBE and the type shown as SWORDSMEN|SPEARMEN plus horse tribes go to the
         * campfire, everything else to the keep.
         */
        void aiRetreatUnits(int playerID);

        /**
         * Sends all attack tribes of playerID1 (aggressive stance) to playerID2: if playerID1's keep can reach
         * playerID2's keep, to playerID2's campfire (type 0xBE / horses) or keep; otherwise to playerID2's owned
         * gatehouse found from playerID1's campground entry. If no gatehouse exists, resets
         * playerID1.allyOrderState to 0 and returns.
         */
        void sendUnitsToPlayerIDsKeepIfPossible(int playerID1, int playerID2);

        /**
         * For an AI player, clears the rally-related flag on the units of every valid attack tribe listed in the
         * MaxAttackTribes1 type/count table.
         */
        void clearRallyFlagOnAllAIAttackTribes(int playerID);

        /**
         * For an AI player, sets every valid attack tribe (MaxAttackTribes1 type/count table) to defensive stance
         * and moves the n-th valid tribe to aiTribeMoveDestinationXYPairArray1[player*5][n].
         */
        void moveAttackTribesToLocations(int playerID);

        /**
         * Finds the first valid attack tribe of the player and takes its lead unit position, then traces a path
         * from there toward the player's own defenses; stores the resulting tile in someTile/someX/someY (0 if
         * none). Note: reads the unit x/y before checking the lead unit id is non-zero.
         */
        void findAttackTribePositionAndPathToDefenses(int playerID);

        /**
         * If the AI player has a regroup tile (someTile), sets every valid attack tribe to defensive and moves it
         * to someX/someY; tribes whose move order fails are dissolved (removeAllTribeUnits).
         */
        void makeUnitsGoDefensiveAndBackToSomeLocation(int playerID);

        /**
         * Moves every valid attack tribe except types 0x12, 0xBE and the one shown as SWORDSMEN|CROSSBOWMEN to
         * consecutive entries of aiTribeMoveDestinationXYPairArray1[player*5], giving each a stance taken from the
         * RNG low bit (0 or 1; the RNG is not advanced, so all tribes get the same stance in one call).
         */
        void giveMoveCommandToAttackTribes(int playerID);

        /**
         * Returns TRUE if the percentage of the AI player's valid attack tribes that have <20% of units moving is
         * >= AIC AttForceRallyPercentage (+0x200), i.e. the attack force has gathered at the rally point.
         */
        BOOLEnum aiChoiceAttForceRallyPercentage(int playerID);

        /**
         * Same as aiChoiceAttForceRallyPercentage but compares the percentage of attack tribes with <20% of units
         * moving against AIC AttMovingTribesThreshold (+0x204).
         */
        BOOLEnum percentageNonMovingTribesGTEAICSpecified(int playerID);

        /**
         * Sets all valid attack tribes (excluding types 0x12, 0xBE and the SWORDSMEN|CROSSBOWMEN-shown type) to
         * stand-ground and returns TRUE if the percentage of them with <20% of units moving is >=
         * AttForceRallyPercentage (+0x200).
         */
        BOOLEnum processAttForceRallyPercentage(int playerID);

        /**
         * Uses the AI engineer pool tribe (slot 0x12): sums the engineers needed by the AIC SiegeEngine1..8 list
         * (+0x214) while the pool suffices, pops that many units out of the pool tribe, then for each listed engine
         * looks up required engineers and siege tent command-building type, forms an engineer tribe
         * (addEngineersToSelection), marks it ENGINEERS/0x410 with the current attack wave and calls
         * placeSiegeTentOrTunnelAtSuitableLocationAndAssignEngineers (arg 0x3C, CONSTRUCT_SIEGE_EQUIPMENT). Stops
         * at the first empty list entry or when engineers run out. If an engine type is not in the 6-entry table,
         * the previous requiredEngineers/commandBuildingType values are reused.
         */
        void useAITribe_0x12_toPlaceSiegeTentsAndAssignEngineers(int playerID);

        /**
         * Splits the AI tunneler tribe (slot 0xE): every unit is popped into its own new tribe (TUNNELERS,
         * behaviour 0x415, current attack wave) for which
         * placeSiegeTentOrTunnelAtSuitableLocationAndAssignEngineers is called with M_MAPPER_TUNNEL_CONSTRUCTION
         * (arg 0x32, instruction 0x15).
         */
        void useAITribe_0xe_toPlaceTunnels(int playerID);

        /**
         * If the AI tribe in slot 0xD (13) is valid and has a lead unit, sets it defensive and assigns attack
         * targets with behaviour STBT_0x3f4.
         */
        void aiCommandTribe13DefensiveWave(int playerID);

        /**
         * For AI tribe slot 0xC (12): runs a linkage path search from its lead unit (radius 10000), sets it
         * aggressive and, if a destination toward the attacked player with cost below 200/150/100/50 is found,
         * moves the tribe there.
         */
        void aiCommandTribe12AggressiveApproach(int playerID);

        /**
         * If AI tribe slot 0xC is valid with a lead unit, sets it aggressive and assigns attack targets with
         * behaviour STBT_0x3f2.
         */
        void setTribe0xCtoAggressiveAndAttack(int playerID);

        /**
         * AI tribe slot 0xB (11): sets stand-ground stance and moves it to a nearby gatehouse; if none, moves it
         * toward particular enemy units.
         */
        void aiCommandTribe11StandGroundToGate(int playerID);

        /**
         * AI attack patrol tribe (slot 0xF): if valid with a lead unit, sets defensive stance and sends it to the
         * computed patrol destination. Only the first patrol group is handled.
         */
        void sendAITribe_0xf_toAttackPatrol(int playerID);

        /**
         * If the per-player attackInfo value (moat-related, read via moatValuesArray-4) is positive, sets AI tribe
         * slot 0x11 aggressive and assigns attack targets with behaviour STBT_0x3f7.
         */
        void setTribe0x11ToAggressiveAndAttackIfConditionMet(int playerID);

        /**
         * For the 8 AI tribe slots 0xC0..0xC7: each valid tribe with a lead unit is set aggressive and given attack
         * targets (STBT_0x3f2).
         */
        void setEightTribe0xc0TribesToAggressiveAndAttack(int playerID);

        /**
         * For the 2 AI tribe slots 0xBE..0xBF: each valid tribe with a lead unit is set aggressive and given attack
         * targets (STBT_0x3f2).
         */
        void aiCommandWallAssaultTribes(int playerID);

        /**
         * If AI tribe slot 0xB is valid with a lead unit, sets it aggressive and assigns attack targets
         * (STBT_0x3f2).
         */
        void setTribe0xbToAggressiveAndAttack(int playerID);

        /**
         * If AI tribe slot 0xBD is valid with a lead unit, sets it aggressive and assigns attack targets with
         * behaviour STBT_0x3fb.
         */
        void sendTribeToAttack(int playerID);

        /**
         * Moves the valid AI tribes in slots 0xBA..0xBC with stand-ground stance to consecutive entries of
         * aiTribeMoveDestinationXYPairArray1[player*5]. NAME? handles three tribes, not four.
         */
        void commandFourTribesToMove(int playerID);

        /**
         * For an AI player, walks MaxBreachTribes entries 0..10 (skipping 8) and clears tribe id/uid slots whose
         * tribe uid no longer matches (dead/reused tribes).
         */
        void clearOutdatedAITribes(int playerID);

        /**
         * Raid retargeting for a tribe; for tribe types 0xBA, 0x12, 0xE, 0xD it does nothing and returns 0.
         * Otherwise returns 1 if its target building is still valid and not burning; otherwise picks a new building
         * of the owner's attacked player via chooseRandomBuildingIDFromPlayersArrayOfBuildings, queues a disband-
         * and-attack command (9) on it, stores it as target, sets defensive stance and returns 1; returns 0 if
         * none. NAME? better retargetTribeBuilding.
         */
        undefined4 giveSomeRaidCommand(int tribeIndex, int tribeType);

        /**
         * Rebuilds the tribe's rally point list: for every friendly (same team) catapult, trebuchet or fire
         * ballista in state byte 3, computes a rally destination next to it and appends it (stops after 9). Then
         * clamps currentRallyPointIndex into range. NAME? rebuilds rally points from friendly siege engines.
         */
        void addRallyPointForTribe(int tribeID);

        /**
         * For every visible siege unit (catapult, trebuchet, tower, ram, shield, fire ballista) of the player in
         * state byte 3 that is not a harassing engine (behaviour 0x15), orders its tribe to exit the siege
         * equipment and sets the unit state to US_DISAPPEAR.
         */
        void disbandAIPlayerSiegeUnits(int playerID);

        /**
         * Counts the player's visible catapults, trebuchets, siege towers, rams and fire ballistae in state byte 3
         * that are not harassing engines (behaviour 0x15); loop unrolled 3 units at a time.
         */
        int countSiegeEngineUnits(int playerID);

        /**
         * Commands all visible towers, rams and portable shields in unit state byte 3 that are not harassing
         * engines (note: no owner check): towers' tribes get attack targets (STBT_0x414) if this player's
         * attackInfo wideValues entry is set; rams use STBT_0x3f6 if the gateValues entry is set, else STBT_0x413
         * if wideValues is set; the first 3 shields are attached to the valid tribes of slots 0xBA..0xBC (compacted
         * list, missing ones stay 0), moved to that tribe's lead unit tile and given an orientation computed from
         * the lead unit position.
         */
        void aiCommandSiegeEngineTribes(int playerID);

        /**
         * Called by catapult/trebuchet updates: for an AI player with cow throwing enabled and AIC CowThrowInterval
         * != 0 and counter > 0, increments aiCowThrowCounter and returns TRUE (resetting it) once it exceeds
         * CowThrowInterval.
         */
        BOOLEnum yieldCowThrow(int playerID);

        /**
         * Sums the AI player's attack troop counts (patrol, unit2, assassins, max-default, siege-def, engage,
         * backup counted as 1/8 after attackTicker > 16 or > 12, diggers fully only in aiPlayerState 6). Returns
         * TRUE if the sum is <= 1, or <= 4 while half the diggers exceed twice the sum.
         */
        BOOLEnum hasNoTroopsOrAllAreDiggers(int playerID);

        /**
         * Returns FALSE (has supplies) if the player has or can afford (wood) a marketplace and a granary (or has
         * noLabourerBuildingCount >0/>1) and has gold, popularity > 25 or food; otherwise TRUE.
         */
        BOOLEnum hasNotEnoughSupplies(int playerID);

        /**
         * Sets aiAttackCoordinationLevel: chance = AIC AttCoordinationPreference (+0x210) + 4*currentAttackWave
         * (max 90); level 2 if rand%100 < chance/2, 1 if < chance, else 0.
         */
        void setAttackCoordinationLevel(int playerID);

        /**
         * Computes relativeStrengthOfTeamComparedToEnemy = teamTroopValue*100/enemyTroopValue (100 if no enemy) and
         * returns TRUE if weak: keep enclosed -> <50 (<70), first 12000 ticks -> <250 (<300), otherwise <75 (<100),
         * values in parentheses when the flag is TRUE. Without the flag, enemy ranged troop value < 100 returns
         * FALSE.
         */
        BOOLEnum teamIsWeakRelativeToEnemy(int playerID, BOOLEnum useHigherThresholds);

        /**
         * AI nervous action: destroys every building of the player that belongs to the given category (fear-
         * factor/good things, workshops & religious, gatehouses/towers/guilds, barracks/merc post/stables, water,
         * resource buildings, farms), refunding resources with argument 0x32 (likely 50%) before destroying each. A
         * category value outside 1..7 matches every owned building. NAME? destroys all matching buildings, not just
         * one.
         */
        void destroyAnyBuildingInCategory(int playerID, AINervousDestroyBuildingCategory buildingCategory);

        /**
         * For trading with allies: non-AI players always TRUE; gold always FALSE; otherwise TRUE if the AI's stock
         * of the resource >= AIC minimumGoodsRequiredAfterTrade (+0xA4, read through a mis-anchored seagullArray
         * offset) + buffer.
         */
        BOOLEnum isResourceLargerOrEqualThanMinimumGoodsRequiredAfterTrade(
            int playerID, ResourceType resourceType, int buffer);

        /**
         * Returns TRUE if some player slot 1..8 is an active AI whose aiType-1 equals the given index and whose
         * lordKilledByPlayerID (0x3C dwords before aiType) is 0, i.e. lord not killed; used to pick joke videos.
         */
        BOOLEnum aiOfTypeInCurrentGame(int aiTypeIndex);

        /**
         * Collects active (AI or human) teammates of the player whose lord is not killed (loop unrolled 4x), splits
         * the given gold evenly among them, moving gold from the player's to each recipient's treasury; human
         * recipients get a 'Goods received from ally' + '<n> Gold' chat message.
         */
        void shareGoldAmongTeamMembers(int playerID, int gold);

        /**
         * If the player's lord is alive and its attackedPlayerID is the local player, plays a taunt video from it:
         * video 0x17 if on the local player's team, otherwise a random taunt 1-4 (RNG low bits).
         */
        void playTauntToAttackedPlayerBikFromPlayer(int playerID);

        /**
         * If the player's lord is alive, it is an enemy of the local player and is attacking him, plays anger video
         * 5 at most once per 10 minutes (timeGetTime, per-player last-play array).
         */
        void playAnger1BikFromPlayer(int playerID);

        /**
         * Lord-death speech videos: local player killed -> killer plays 0xC; local player is killer -> victim plays
         * 7 and every allied AI with a living lord plays 0x11; victim is the local player's ally -> victim plays
         * 0x10; killer is ally -> victim 7 and killer 0x12; otherwise victim 7 and killer 0xD. Requires the
         * killer's lord alive.
         */
        void playPlayerKilledBiksFromKilledAndKillerPlayer(int killerPlayerID, int killedPlayerID);

        /**
         * If the player's lord is alive and the target is the living local player, plays goods-request video 0xE
         * from the player.
         */
        void playGoodsRequestBikFromPlayerToPlayer(int playerID, int targetPlayerID);

        /**
         * If the player's lord is alive, resets its aiRequestDelay from AIC aiRequestDelay (+0xA0) and, if the
         * target is the living local player, plays thanks video 0xF at most once per 20 minutes (global timestamp).
         */
        void playThanksBikFromPlayerToPlayer(int playerID, int targetPlayerID);

        /**
         * If the player's lord is alive and nervousBikCountdown is 0, restarts the countdown (0x30) and plays
         * nervous video 9 when the player is an enemy of the local player.
         */
        void playNervous2BikFromPlayer(int playerID);

        /**
         * Plays goods-not-sent video 0x1C from the player if its lord is alive.
         */
        void playGoodsNotSentBikFromPlayer(int playerID);

        /**
         * Plays goods-sent video 0x1D from the player if its lord is alive and the target is the local player.
         */
        void playGoodsSentBikFromPlayerToPlayer(int playerID, int targetPlayerID);

        /**
         * Called when buildings are damaged: for an AI player with a living lord and someAiCountdown3 == 0,
         * restarts that countdown (0x60) and, if the attacker target is the local player, plays anger video 6.
         */
        void playAnger2BikFromPlayerToPlayer(int playerID, int targetPlayerID);

        /**
         * If targetPlayerID is an AI and playerID is human, both lords alive and the AI's someAiCountdown4 == 0,
         * restarts it (0x30) and plays victory video 0xB from the AI when playerID is the local player. NAME? the
         * video plays from targetPlayerID to playerID.
         */
        void playVictory2BikFromPlayerToPlayer(int playerID, int targetPlayerID);

        /**
         * If the player's lord is alive and someAiCountdown5 == 0, restarts it (0x30) and plays nervous video 8.
         */
        void playNervous1BikFromPlayer(int playerID);

        /**
         * If the player's lord is alive and someAiCountdown6 == 0, restarts it (0x30) and plays request-help video
         * 0x13 when the player is on the living local player's team.
         */
        void playRequestHelpBikFromPlayer(int playerID);

        /**
         * Plays will-not-help video 0x1A from the player if its lord is alive and the target is the local player.
         */
        void playWillNotHelp1BikFromPlayerToPlayer(int playerID, int targetPlayerID);

        /**
         * Plays will-not-help video 0x1B from the player if its lord is alive and the target is the local player.
         */
        void playWillNotHelp2BikFromPlayerToPlayer(int playerID, int targetPlayerID);

        /**
         * Plays will-help video 0x20 from the player if its lord is alive and the target is the local player.
         */
        void playWillHelpBikFromPlayerToPlayer(int playerID, int targetPlayerID);

        /**
         * Plays will-not-attack video 0x18 from the player if its lord is alive and the target is the local player.
         */
        void playWillNotAttack1BikFromPlayerToPlayer(int playerID, int targetPlayerID);

        /**
         * Plays will-not-attack video 0x19 from the player if its lord is alive and the target is the local player.
         */
        void playWillNotAttack2BikFromPlayerToPlayer(int playerID, int targetPlayerID);

        /**
         * Plays will-attack video 0x21 from the player if its lord is alive and the target is the local player.
         */
        void playWillAttackBikFromPlayerToPlayer(int playerID, int targetPlayerID);

        /**
         * Plays joke video 0x14 of the given AI character from the player if its lord is alive.
         */
        void playJokeBikFromAIToHuman(int playerID, int aiType);

        /**
         * Plays friendly-victory video 10 from the player if its lord is alive.
         */
        void playFriendlyVictoryBikFromPlayer(int playerID);

        /**
         * Plays team-winning video 0x1E from the player if its lord is alive and it has no pending building-destroy
         * choice and no nervous actions.
         */
        void playTeamWinningBikFromPlayer(int playerID);

        /**
         * Plays no-help video 0x1F from the player if its lord is alive.
         */
        void playNoHelpBikFromPlayer(int playerID);

        /**
         * Called from the window procedure (player taunt): when in-game, stores timeGetTime in
         * aiTauntResponseTimeWindow so an AI will answer later.
         */
        void setTriggerForAITauntResponse();

        /**
         * In-game single-player skirmish only: if a taunt time was stored and more than 2 s have passed, collects
         * enemy AI players (AI slots not on the local player's team), picks one with weighted randomness (RNG1;
         * weight and message id per AI character read via an out-of-bounds MaxBreachTribes[aiType+10] index, really
         * SkirmishDefinedData.aiTauntWeightAndMessage) and queues a GCT_TAUNT_OR_CHAT command (message -2-id) from it to
         * players 1..8, then clears aiTauntResponseTimeWindow. Returns early without clearing while the 2 s have
         * not elapsed; clears it in all other cases. NAME? better aiRespondToTaunt.
         */
        void someChatMessageSelection();

        /**
         * Returns the desired raid unit count: AIC RaidUnitsBase + player's currentAttackRaidParameter, scaled by
         * 4/3 on an Extreme skirmish trail.
         */
        int getCurrentDesiredAttackRaidUnitCount(int aiTypeIndex, int playerID);

        /**
         * Debug overlay: for each player 1..8 that is alive (lordKilledByPlayerID and playerDeathRelated 0) and AI
         * or human, prints id, name, strength feeling (Weak/Normal/Strong), 'P:' aivCurrentPause, 'Atk:'
         * attackedPlayerID and 'W:' aiAttackCoordinationLevel, AIV castle (n/a for humans), 'E:' totalTroopsType6
         * vs unknownCounter_01+SortieUnitRangedMin, 'Sg:' attack troops minus engineers vs
         * AttForceBase+currentWaveRandomAttackingStrength when aiPlayerState is 0 (else vs attackTicker in white),
         * 'Hr:' totalRaidingTroopsUnk vs desired raid count and 'Df:' totalDefensiveTroopsUnk vs DefWalls.
         */
        void renderDebugDataAiInfo(int x, int y, int width, int height);

        /**
         * Wipes AIC memory and loads the built-in parameter sets for the 16 AI characters
         * (setAICParameters_01..16).
         */
        void setInitialAIC();

        /**
         * Empty tribes get tribeState 3. For AI-owned tribes, stores tribe id/uid in the first free or stale slot
         * of the 1000-entry AIC tribe registry and sets its target via setTargetForTribeBasedOnTargetChoiceLogic.
         */
        void aiRegisterTribeAndAssignTarget(int tribeID, int tribeUID);

        /**
         * Outpost tribe attack logic: if busy, resets its counter; every (random%6+7) calls it path-finds from its
         * first unit to the target player's castle (incl. moat) and relays instruction 0x23 on the found tile or
         * FILL_MOAT. Otherwise, for subtypes other than 0xB6/0xB9: the later activity checks (incl. the 'keep
         * current target building' branch) repeat the check that already failed at the top, so in practice it picks
         * a random building of the target player and relays ATTACK_BUILDING, or (none) commands the tribe to the
         * target's campground entry if reachable. Subtypes 0xB6/0xB9 go to a random building (entry tile, or
         * attack-pathfinding destination from the lead unit) or the campground entry; if unreachable,
         * sendUnitsToCampfire.
         */
        void decideOnTribeAttackLocation(uint tribeID_OR_moatWasHit);

        /**
         * For an AI player, walks AIResourceTradeAICMapping (game resource -> AIC trade category) and sells at most
         * one resource. Sell threshold = AIC max for the category
         * (maxWood/maxFood/maxStone/maxEquipment/maxBeer/maxResourceOther) + maxResourceVariance, normally +
         * resourcesToAcquire[res]. Nervous (aiNervousActionsTracker > 0) with < 500 gold: food threshold /4,
         * weapons threshold 10000 (kept), every other resource threshold 0 (sold out). Popularity below AIC
         * criticalPopularity (+0x18): food keeps max+variance, weapons go to 0, others /4. Resources listed in AIC
         * sellResource01..15 (+0xD4) get threshold 0 and variance 0 (sell all). The first resource whose stock
         * exceeds the threshold is sold via sellGoods(stock - threshold + variance), i.e. down to max (+toAcquire),
         * and the function returns. NB: the Ghidra plate comment is wrong about the nervous case (weapons are kept,
         * not zeroed) and calls the +0xD4 list a do-not-sell list.
         */
        void sellExcessGoods(int playerID);

        /**
         * AI player asks team players for goods: for every slot 1-8 that is occupied, on the same team and has a
         * living lord, if that player's request slot for this requester (requestedGoodsArray1Unk[playerID]) is
         * empty it writes resourceType there and the amount 10 shorts later, and plays the goods-request Bink. The
         * loop does not exclude the requester itself. Skipped while aiRequestDelay != 0, for wheat/hops/ale, and
         * for bread/cheese/meat/apple unless totalFood < 5.
         */
        void requestGoods(int playerID, ResourceType resourceType, int amount);

        /**
         * AI siege production at a valid engineers guild (canStartSpending set): for each of the 4
         * SiegeEngineMetaInfo entries, iterates up to 3 AIV slots of that entry's slot type. Per slot a tracked
         * unit/tent (aiSiegeCreationInformation) is cleared when its uid no longer matches. Empty slot: entries 0-1
         * need a tower4/tower5 on the slot tile and spawn the engine unit there (cost charged via
         * processPlacementResourceLossForBuildingType); entries 2-3 need an empty tile and place the siege tent
         * (commandBuildingType) via placeBuilding, subtracting gold. Building requires cost <= gold + AIC
         * defSiegeEngineGoldThreshold, after which the per-slot delay is incremented and must reach
         * defSiegeEngineBuildDelay; the delay is reset after the attempt. Tracked tents/engines lacking engineers
         * get a new engineer tribe (construct siege equipment / man siege equipment if reachable), or
         * isEngineerRequired = TRUE when too few engineers. Returns after the first build or engineer assignment.
         */
        void aiCreateSiegeUnits(int playerID);

        /**
         * AI with a valid engineers guild, oil smelter, canStartSpending, >= 30 gold and at least one oil AIV slot:
         * if neither the smelter nor the stockpile has pitch (resource 7) sets resourcesToAcquire[pitch] = 4;
         * otherwise, if one of the first (slotCount+1) oil tribe slots is empty/stale, recruits an engineer at the
         * guild, creates the tribe in that slot, adds the engineer (defensive stance, AITT_ENGINEERS, STBT_0x41d)
         * and orders it to the oil smelter for oil duty.
         */
        void aiRecruitEngineerForOilDuty(int playerID);

        /**
         * Puts a newly recruited AI unit into a tribe and sets aiUnitBehaviourType = 1: determines its AIV unit
         * type (pause-1 variant while AIV pause 1 is active); if the player has AIV slots of that type, adds it to
         * the smallest tribe of that type, otherwise to generic tribe 0 (ranged/armored units) or 1 (others) via
         * getOrCreateTribeForUnitType.
         */
        void assignUnitToATribe(int unitID);

        /**
         * Marks an AI unit as outer-patrol (aiUnitBehaviourType = 4) and adds it to the smallest of the AIC
         * OuterPatrolGroupsCount patrol tribes.
         */
        void addUnitToSmallestPatrolTribe(int unitID);

        /**
         * NAME? Sets aiUnitBehaviourType = 2 and adds the unit to the tribe returned by getDefensiveTribeForUnit,
         * which is one of aiTribeIDs[0xB4..0xB9] - the 6 raid tribes driven by aiGiveRaidInstructions. Its only
         * caller (aiRecruitUnits) uses it for units recruited in the AIRUC_RAIDING state, so this assigns raid
         * recruits to their raid tribe, not defenders.
         */
        void aiAssignUnitToRaidTribe(int unitID);

        /**
         * Sets an AI unit's aiUnitBehaviourType to the given value and adds it to the tribe returned by
         * addUnitToSmallestBehaviourTypeTribe (smallest tribe of that behaviour type), if any.
         */
        void addUnitToItsTribe(int unitID, int aiUnitBehaviourType);

        /**
         * If the player's AI tribe slot 0 holds a valid tribe (uid matches), sends that tribe's units to the keep.
         */
        void ifHasTribe0SendUnitsToKeep(int playerID);

        /**
         * If the player's AI tribe slot 1 holds a valid tribe (uid matches), sends that tribe's units to the
         * campfire.
         */
        void sendTribeAtOffset1ToCampfire(int playerID);

        /**
         * Outer patrol: every AIC OuterPatrolRallyDelay calls, for each of the OuterPatrolGroupsCount tribes
         * (aiTribeIDs[0xAA+]) that is valid and idle (moving/shooting/attacking <= 10%), picks one of the player's
         * own targetable buildings (getTargetableBuildingForPlayerID if OuterPatrolGroupsMove, else / as fallback
         * selectBuildingFromAListOfBuildingTypes) and moves the tribe to its entry tile, or to the campfire if
         * unreachable. Every slot's tribe (even empty/stale ones) gets stance aggressive.
         */
        void aiGiveOuterPatrolCommand(int playerID);

        /**
         * Controls the 6 raid tribes (aiTribeIDs[0xB4..0xB9]), all set aggressive (even slot 0 before the validity
         * check). Advances raidRetargetDelayCounter (wraps at AIC RaidRetargetDelay +0x1F0; new targets only when
         * it is 0) and decrements raidAttackCountdown while raiding troops exist (0 when none). Per valid tribe: if
         * an ally asked for help (allyOrderState == 2, asker's lord alive) it moves to a random building of the
         * asker; else if the countdown is 0 and raiding troops are below getCurrentDesiredAttackRaidUnitCount it
         * gathers at a random building of its own player; else ranged raid tribes (TribeTypeID 0xB5/0xB6) move to a
         * random building of raidTargetPlayerID; other tribes get UIT_ATTACK_BUILDING on a random building of that
         * player (countdown = 100), keeping a still-valid, non-burning target. Unreachable move targets send the
         * tribe to the campfire.
         */
        void aiGiveRaidInstructions(int playerID);

        /**
         * Moves a tribe to the slotIndex-th (0-based) non-empty AIV location slot (of 10) for the given AIV unit
         * type of its owner. If no such slot exists the target tile stays 0 (there is no explicit check); if
         * canNavigateUnitsFromTileToTargetTile fails the tribe is sent to the keep instead.
         */
        void sendTribeToAIVLocationSlot(int tribeID, AIVUnitType aivUnitType, int slotIndex);

        /**
         * Recomputes the AI's attack planning data against its attackedPlayerID: clears a 0x13A10-byte buffer at
         * 0x1EA7B68, sets attack prime info, recomputes targeted building tiles, attack info and siege spot scores,
         * runs the scale/town/gate/wide/moat setters and recalculates attack vectors to the target's campfire.
         */
        void computeAttackPossibilities(int playerID);

        /**
         * For the 2 main attack tribes (aiTribeIDs[0xBE+]) whose units have all reached their destination: sets
         * stance aggressive, adds a rally point, advances to the next rally point (wrapping) and orders a move
         * there if the leader is > 5 tiles away (single rally point) or the leader's closest enemy is > 0x60 away
         * (multiple rally points).
         */
        void moveAttackingUnitsToNextRallyPoint(int playerID);

        /**
         * After the enemy castle is breached: iterates MaxBreachTribes (tribe offset, count), skipping offsets
         * 0x12/0xE/0xD; each valid tribe is first set defensive. The first valid tribe whose offset is not 0xBA is
         * sent to the enemy lord if alive (returns 0 if the move fails). Later tribes (and all if the lord is dead
         * or offset 0xBA) try giveSomeRaidCommand; if that does nothing they become STBT_8/aggressive and move to
         * the next attack vector of the target (0xBA tribes skip 4 vectors), only if more than 4 tiles away.
         * Returns 1 (also for non-AI players).
         */
        undefined4 sendUnitsToAttackBreachedCastle(int attackingPlayerIndex);

        /**
         * Scores an AI player's strength into aiStrengthState (gold >=200: +1, >=2000: +2; population >=15: +1,
         * >=40: +2; totalFood >=20: +1, >=200: +2; attack+raid+defensive troops >=8: +2, >=40: +4) and maps it to
         * aiStrengthFeeling (<=2 weak, <=7 default, else strong; forced weak during AIV pause 1). Then picks
         * aiRecruitUnitChoiceState: before tick 4800 defensive; else roll rand % (RecruitProbDef+Raid+Attack for
         * that feeling) -> defensive / raid / attack; a defensive or raid choice falls back to attack once DefTotal
         * / getCurrentDesiredAttackRaidUnitCount is reached; if all probs are 0 the parameter value itself is used
         * as the choice. A zero parameter (weekly call) only runs on Extreme skirmish trail and stops here. With
         * parameter 1 (monthly): if nervous and the team is no longer weak, clears nervousness; if still weak
         * forces weak/defensive and, with gold <= 500 and nervous tracker 1..7, destroys fear-factor and
         * workshop/religious buildings, or with gold > 2500 shares gold/10 on every second call when relative
         * strength <= 20; then decrements the tracker (min 1). Not nervous: starts nervousness (tracker 8, Bink)
         * when the team is weak, else runs the low-supplies destroy countdown (tracker 8..4: fear-factor,
         * workshops, gatehouses/towers/guilds + barracks/merc/stables + water, resource buildings, farms; forces
         * wood purchase of 20). The 'resource buildings when tracker > 7 and <= 5' branch in the nervous path is
         * dead code (also in the machine code at 0x4D35E8).
         */
        void updateAIStrengthState(int playerID, int aiRecruitUnitChoicePreference);

        /**
         * Compares the AI's troop value within 40 tiles of its own campground
         * (playerTotalTroopValueOfTroopsNearKeep) with totalEnemyTroopValue plus a margin (-20/0/20/100/200/300/500
         * for enemy value <50/<100/<200/<400/<600/<800/>=800). If its own value is not larger it sets
         * isNotNervousByEnemyTroopValue = 1 and, on the 0->1 transition, plays the nervous Bink (if weaker than the
         * local human's troop value) and the request-help Bink; otherwise clears the flag to 0.
         */
        void computeNervousness(int playerID);

        /**
         * AI answer to an ally's defence request: refuses (WillNotHelp1) if its nervous flag
         * (isNotNervousByEnemyTroopValue, actually 1 = nervous) is set, refuses (WillNotHelp2) if totalAttackTroops
         * is below AIC AttForceSupportAllyThreshold (+0x1FC), otherwise plays WillHelp and returns TRUE.
         */
        BOOLEnum determineAIPlayerHelp(int playerID, int requestedByPlayerID);

        /**
         * AI answer to an ally's attack request: refuses (WillNotAttack1) if nervous, refuses (WillNotAttack2) if
         * attack troops minus attacking engineers are below AIC AttForceSupportAllyThreshold (+0x1FC), else plays
         * WillAttack and returns TRUE. The target player argument is not used here (the caller stores it).
         */
        BOOLEnum determineAIPlayerAttackRequestResponse(int playerID, undefined4 targetPlayerID, int requestedByPlayerID);

        /**
         * For each of the 1000 tribe IDs stored in AICState.tribeIDArray whose uid still matches tribeUIDArray,
         * calls decideOnTribeAttackLocation.
         */
        void makeOutpostTribesAttack();

        /**
         * Walks the 25-entry ResourceAcquisitionPreferenceOrder and buys the first resource with a pending
         * resourcesToAcquire amount when popularity is below AIC criticalPopularity (first 4 entries only), the AI
         * is nervous, or canStartSpending is set; nervous AIs skip entries 0-11, and every entry is replaced by
         * wood while the building-destroy tracker runs and wood < 20. If gold is below getBuyPrice it requests
         * double the amount from team players instead; a successful buy clears the request and returns.
         */
        void buyRequiredGoods(int playerIDThenPrefIdx);

        /**
         * AI recruitment tick: unless nervous, waits AIC RecruitInterval[feeling] calls. Needs idle peasants and
         * canStartSpending, and stops when the current choice is satisfied (defensive: DefTotal reached, x4/3 on
         * Extreme, x4 when nervous; raid: desired raid count reached; attack: an attack is already running).
         * Recruits up to 1-2 units (2 if RecruitInterval is 0, +1 on Extreme) or 4 when nervous: moat diggers
         * (DefDiggingUnit; each iteration has a 50% chance to switch to normal recruiting for the rest of the call)
         * while moat tiles remain and the digger tribe is below DefDiggingUnitMax, else the next DefUnit1-8 /
         * RaidUnit1-8 entry or a random attack behaviour's unit type, at engineers/tunnelers guild, cathedral,
         * barracks or mercenary post. A recruit failing for missing equipment sets resourcesToAcquire to AIC
         * tradeAmountEquipment (5 when nervous). Recruits go to the digger tribe, assignUnitToATribe (below
         * DefWalls +0x180) / addUnitToSmallestPatrolTribe (defensive), aiAssignUnitToRaidTribe (raid) or
         * addUnitToItsTribe (attack). The playerID parameter is reused as the recruit loop counter.
         */
        void aiRecruitUnits(int playerIDThenRecruitIdx);

        /**
         * For an AI with totalTroopsType0 > 0, loops all visible, non-dying units of the player that have no AI
         * behaviour type yet (excluding lord, engineer, tunneler and siege engines) and assigns them: to the moat
         * digger tribe when AIC DefDiggingUnitMax != 0, the unit is not an archer/crossbowman and a per-unit flag
         * (+0x2E0 from unitType) is set, otherwise via assignUnitToATribe.
         */
        void aiAssignMoatDiggers(int playerID);

        /**
         * Loops all units; every normal-state, non-dying engineer of the player with aiUnitBehaviourType 10 and no
         * tribe is added to its behaviour-type tribe (addUnitToItsTribe(...,10)).
         */
        void addEngineersToTribe(int playerID);

        /**
         * Loops all units; every normal-state, non-dying tunneler of the player with aiUnitBehaviourType 0xF is
         * removed from its current tribe (if any) and re-added to its behaviour-type tribe.
         */
        void aiReassignTunnelersToTribe(int playerID);

        /**
         * For each ranged AIV unit type (MaxAIVLocationForRangedUnits), sends each valid tribe to its AIV location
         * slot; when the AI is nervous, sends it to the keep instead unless its leader stands on a tile with
         * LogicLayer flags 0x10000100 (then it is left alone).
         */
        void sendRangedUnitTribesToAIVSlotsOrKeepIfNervous(int playerID);

        /**
         * For each ground AIV unit type (MaxAIVLocationForGroundUnits), sends each valid tribe to its AIV slot
         * (stance aggressive) unless the AI is nervous and its keep is not enclosed, in which case the tribe goes
         * to the keep (stance defensive). Stance is written even for empty/stale tribe slots.
         */
        void sendCertainUnitTribesToAIVSlotsOrKeepIfNervousAndNotEnclosed(int playerID);

        /**
         * Wall patrols: for each patrol AIV unit type, uses min(AIC defWallPatrolGroups, slot count) tribes spread
         * evenly over the slots and moves each to slot (defWallPatrolRallyTimeHits + offset) % slotCount, rotating
         * over time; nervous AIs with an unenclosed keep send them to the campfire with defensive stance.
         */
        void sendWallPatrolUnitTribesToAIVLocations(int playerID);

        /**
         * Oil men: for the oil tribes aiTribeIDs[0x47..] (one per oil AIV slot, 10 capped to 9), if the leader
         * carries nothing it is ordered to the oil smelter for oil duty (if a smelter exists); if it carries
         * something its rally flags are cleared and it goes to the matching AIVUT_ENGINEER slot.
         */
        void sendOilMenForOilPickupOrToAIVLocations(int playerID);

        /**
         * Cancels the AI's current attack: removes the siege buildings of the current attack wave, disbands siege
         * units, regroups engineers and tunnelers into their tribes and sets aiPlayerState = 0.
         */
        void abortAttackAndGoIdle(int playerID);

        /**
         * If the AI has attacking engineers, clears the engineer tribe slot (aiTribeIDs[0x12]) when its uid is
         * stale and regroups engineers via addEngineersToTribe.
         */
        void recreateEngineersTribe(int playerID);

        /**
         * Updates nervousness, then chooses the AI's attackedPlayerID: clears requestStateUnk if the asker's lord
         * is dead; none (0) while an ally asked for defence (requestStateUnk==2); the requested target while
         * requestStateUnk==1 and its lord is alive. Otherwise, among enemy-team players with an alive lord, by AIC
         * TargetChoice (closest human, closest, richest, or lowest balanced score from distance and player stats),
         * falling back to the enemy with the closest campground. Writes the result to attackedPlayerID and
         * attackedPlayerID_2Unk.
         */
        void selectAttackTarget(int playerID);

        /**
         * If the AI player has a marketplace, toggles willBuy every call and alternately runs buyRequiredGoods
         * (willBuy TRUE) or sellExcessGoods.
         */
        void aiBuyAndSellGoods(int playerID);

        /**
         * Per-tick AI tribe positioning: advances the wall-patrol rally timer (defWallPatrolRallyTimeHits++ every
         * AIC defWallPatrolRallyTime calls), sends tribe 0 to the keep and tribe 1 to the campfire, digs moat when
         * monthTicks == playerID, then positions ranged, ground, wall-patrol, oil and outer-patrol tribes.
         */
        void updateTribeLocations(int playerID);

        /**
         * AI attack state machine (aiPlayerState). If an ally asked for defence (requestStateUnk==2, asker alive)
         * it clears rally flags and sends units to the asker's keep, nothing else. State 0: if
         * aiShouldAttackOrWaitForTeamCoordination fails, retreats units; else resets attack counters, sets
         * coordination/strength/raid parameters, counts the attack against the target and continues as state 1. Any
         * active state is forced to 8 (retreat) when there are no troops/only diggers (except in 9), when nervous
         * in states < 6, or when attackTicker >= 200. If the target's lord is dead: states < 4 go straight to 9
         * (siege disbanded, units regrouped and sent back), states 4-6 go to 7. Then: 1 regroup engineers, compute
         * keep approach tile -> 2 (or 0 if none); 2 when AttForceRallyPercentage is met -> 3 (siege tents, tunnels,
         * moves, taunt); 3 rally/advance -> 4; 4 siege until AttAssaultDelay (+0x208) is exceeded (forced when no
         * siege engines) -> 5 if keep-to-keep is not navigable (walls) else 6; 5 wall assault every 4th call, -> 6
         * once navigable; 6 attack breached castle (back to 5 if no longer navigable); 7 wait
         * AttUnitPatrolRecommandDelay (+0x20C) -> 9; 8 retreat (Anger Bink unless nervous) -> 9; 9 returning -> 0
         * after 20 ticks, enough non-moving tribes, or no troops. States 5/6 also reset to 0 when
         * shortestDistanceTile < 1.
         */
        void updateAIPlayerState(int playerID);

        /**
         * Top-level AI tick: at dayTicks==10 makes outpost tribes attack; for each AI player 1-8 (skipping two per-
         * player disable flags) runs, staggered by dayTicks/weekTicks/monthTicks == playerID: daily recruitment,
         * siege and engineer building (unless no-rush) plus trading and raids; weekly oil engineer (unless no-
         * rush), tribe positioning, attack state, taxes/rations, food buy plan, updateAIStrengthState(...,0) when
         * it is not also the monthly tick, and decrements 6 per-player cooldowns; monthly moat count, tribe
         * 166/sortie moves, updateAIStrengthState(...,1), target selection and canStartSpending (always when the
         * recruit choice is raiding, else gold > AIC recruitGoldThreshold +0xC4).
         */
        void updateAIBehaviour();

        /**
         * Returns TRUE if the building to place is a granary while the player's granary is not almost full (so no
         * new granary is needed); FALSE otherwise.
         */
        BOOLEnum shouldNotBeBuildingGranary(int playerID, MappersEnum commandBuildingType);

        /**
         * Returns TRUE if the building to place is an armoury while the player's armoury is not almost full; FALSE
         * otherwise.
         */
        BOOLEnum shouldNotBeBuildingArmoury(PlayerID playerID, MappersEnum commandBuildingType);

        /**
         * Returns TRUE if the building to place is a killing pit and the player already has more than 99 killing
         * pits.
         */
        BOOLEnum shouldNotBuildKillingPits(int playerID, MappersEnum commandBuildingType);

        /**
         * Returns TRUE if the building to place is a woodcutter's hut while
         * AIVState.mapExtraInfo.totalWoodAvailable < 1.
         */
        BOOLEnum mapperIsWoodCuttersHutWhileNoWoodAvailable(undefined4 playerID, MappersEnum commandBuildingType);
    };

    static_assert_cpp98_obj(sizeof(AICState) == 28048, AICState);

#pragma pack(pop)

} // namespace AI
} // namespace OpenSHC
