/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/MapPropertiesState.hpp'
*/

#pragma once

#include "OpenSHC/AI/Siege/SiegeUnitCounts.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Game/Scenario/BarracksRecruitabilityShort.hpp"
#include "OpenSHC/Game/ScenarioEvents/InGameEventExtra.hpp"
#include "OpenSHC/Game/ScenarioEvents/InGameEventUnionVersion.hpp"
#include "OpenSHC/Game/ScenarioEvents/IngameEventHeader.hpp"
#include "OpenSHC/Game/ScenarioEvents/IngameInvasionEventItemContent.hpp"
#include "OpenSHC/Game/Siege/SiegeGameModeRelatedSection.hpp"
#include "OpenSHC/Game/TradeableResourcesSection.hpp"
#include "OpenSHC/Map/MapType2Int.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::AI::Siege::SiegeUnitCounts;
    using OpenSHC::Commands::MappersEnum;
    using OpenSHC::Game::TradeableResourcesSection;
    using OpenSHC::Game::Scenario::BarracksRecruitabilityShort;
    using OpenSHC::Game::ScenarioEvents::InGameEventExtra;
    using OpenSHC::Game::ScenarioEvents::IngameEventHeader;
    using OpenSHC::Game::ScenarioEvents::InGameEventUnionVersion;
    using OpenSHC::Game::ScenarioEvents::IngameInvasionEventItemContent;
    using OpenSHC::Game::Siege::SiegeGameModeRelatedSection;
    using OpenSHC::Map::MapType2Int;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

    // SIZE: 0x000146A0
    class MapPropertiesState {
    public:
        uchar SEC_Section1089[128]; // 0x00000000 length: 128
        int SEC_StartingYear; // 0x00000080 length: 4
        int SEC_StartingMonth; // 0x00000084 length: 4
        int SEC_StartingResources[25]; // 0x00000088 length: 100
        SiegeUnitCounts SEC_SiegeInformation; // 0x000000EC length: 80
        SiegeGameModeRelatedSection SEC_Section1067; // 0x0000013C length: 28
        int SEC_StartingPopularity; // 0x00000158 length: 4
        short buildingAvailability[100]; // 0x0000015C length: 200
        // Number of building-availability groups in BuildingNameRelatedStructArray minus 2 (set by
        // commitBuildingAvailability); editor availability list scrollbar max = value - 19
        undefined4 availabilityListCount; // 0x00000224 length: 4
        short buildingAvailabilityRelatedFlags[380]; // 0x00000228 length: 760
        short buildingAvailabilityArray2[49]; // 0x00000520 length: 98
        BarracksRecruitabilityShort barracksRecruitability; // 0x00000582 length: 14
        short SEC_MercRecruitable[7]; // 0x00000590 length: 14
        short SEC_XbowProducible_save; // 0x0000059E length: 2
        short SEC_BowProducible_save; // 0x000005A0 length: 2
        short SEC_PikeProducible_save; // 0x000005A2 length: 2
        short SEC_SpearProducible_save; // 0x000005A4 length: 2
        short SEC_SwordProducible_save; // 0x000005A6 length: 2
        short SEC_MaceProducible_save; // 0x000005A8 length: 2
        undefined1 padding_0x5aa[2]; // 0x000005AA length: 2
        int eventsCount; // 0x000005AC length: 4
        InGameEventUnionVersion scenarioEvents[200]; // 0x000005B0 length: 45600
        InGameEventExtra SEC_EventsExtra[200]; // 0x0000B7D0 length: 32000
        TradeableResourcesSection SEC_Section1065; // 0x000134D0 length: 100
        int scenarionMissionType; // 0x00013534 length: 4
        MapType2Int SEC_U3_MapType2_1; // 0x00013538 length: 4
        MapType2Int scenarioMissionSiegeOrInvasion; // 0x0001353C length: 4
        // Copy of initial victory ticks; denominator of Time Until Victory bar. SEC_ prefix kept.
        undefined4 SEC_VictoryTicksTotal; // 0x00013540 length: 4
        // Victory timer: init value*800, decremented per tick, condition met at <1; progress bar numerator. SEC_
        // prefix kept.
        undefined4 SEC_VictoryTicksLeft; // 0x00013544 length: 4
        // [081 0x004C31A0] Set to 1 while all other conditions of an event with condition 0x27 (time until victory)
        // hold; toggles DEID_TIME_UNTIL_VICTORY display.
        undefined4 victoryTimerActive; // 0x00013548 length: 4
        undefined1 padding_0x1354c[4]; // 0x0001354C length: 4
        // accessed by 0x4bad9b, 0x4badcd, 0x4badf8
        int field_0x13550; // 0x00013550 length: 4
        undefined1 padding_0x13554[8]; // 0x00013554 length: 8
        // First visible row in the editor scenario event/invasion list
        int eventListScrollOffset; // 0x0001355C length: 4
        // Selected visible row in the event list (-1 = none)
        int eventListSelectedRow; // 0x00013560 length: 4
        undefined4 currentEventID; // 0x00013564 length: 4
        // Type (tl_type) of the event being edited: 1 = invasion, 3 = event
        undefined4 editedEventType; // 0x00013568 length: 4
        // accessed by 0x4b857b, 0x4b8bc1
        int field_0x1356c; // 0x0001356C length: 4
        // [228 0x004C0040] 0x01666DC8 reset to 0 right before opening MMT_NEW_EVENT_CONDITION; the condition dialog
        // uses it as index of the selected condition slot
        undefined4 selectedConditionIndex; // 0x00013570 length: 4
        int DAT_BuildingAvailabilityScrollbarOffset; // 0x00013574 length: 4
        undefined4 flag; // 0x00013578 length: 4
        undefined4 offset; // 0x0001357C length: 4
        undefined4 indexStored; // 0x00013580 length: 4
        // accessed by 0x4bf74d
        int field_0x13584; // 0x00013584 length: 4
        // accessed by 0x4bf753
        dword field_0x13588; // 0x00013588 length: 4
        undefined4 value; // 0x0001358C length: 4
        // Used: selects highlighted category tab (buttons 4..8) and visible button set; 'unused' is wrong. Selected
        // category (0..4) in the unused create-message-event dialog
        undefined4 messageEventCategory; // 0x00013590 length: 4
        // accessed by 0x4ba9fd, 0x4baa2a
        int field_0x13594; // 0x00013594 length: 4
        // accessed by 0x4baa08
        int field_0x13598; // 0x00013598 length: 4
        undefined4 total; // 0x0001359C length: 4
        int unknownArray_01[1000]; // 0x000135A0 length: 4000
        undefined4 year_copy; // 0x00014540 length: 4
        undefined4 DAT_MapEditorUnitPointsSum; // 0x00014544 length: 4
        undefined4 DAT_InvasionEventItemUnitCountSum; // 0x00014548 length: 4
        undefined1 padding_0x1454c[8]; // 0x0001454C length: 8
        // Total mission completion score (difficulty base + time bonus + goal bonuses + survival bonus); written to
        // scores file; -1 at start
        undefined4 missionScore; // 0x00014554 length: 4
        // Months remaining before the deadline at mission end (clamped >= 0)
        undefined4 scoreMonthsEarly; // 0x00014558 length: 4
        // Time bonus = scoreMonthsEarly * 100
        undefined4 scoreTimeBonus; // 0x0001455C length: 4
        // Number of surplus-goal bonus entries computed by computeMissionCompletionScore
        undefined4 scoreGoalBonusCount; // 0x00014560 length: 4
        // computeMissionCompletionScore indexes it by scoreGoalBonusCount ([esi+idx*4+0x14564]); capacity 7 from
        // the 0x1C spacing of the three arrays.
        int scoreGoalSurplus[7]; // 0x00014564 length: 28
        // computeMissionCompletionScore indexes it by scoreGoalBonusCount ([esi+idx*4+0x14580]); capacity 7 from
        // the 0x1C spacing of the three arrays.
        int scoreGoalPoints[7]; // 0x00014580 length: 28
        // computeMissionCompletionScore indexes it by scoreGoalBonusCount ([esi+idx*4+0x1459C]); capacity 7 from
        // the 0x1C spacing of the three arrays.
        int scoreGoalGoodsType[7]; // 0x0001459C length: 28
        // (100 - lossesPercent) * 100, campaign/limited builder missions
        undefined4 scoreTroopSurvivalBonus; // 0x000145B8 length: 4
        // weightedLosses * 100 / (losses + surviving troop value)
        undefined4 scoreLossesPercent; // 0x000145BC length: 4
        // Only when GameCore.mapU4Int1: playerDataArray[2].weightedLosses + troop value of player 1's surviving
        // units
        undefined4 player1AlivePlusPlayer2Losses; // 0x000145C0 length: 4
        // Only when GameCore.mapU4Int1: sum of getValueOfTroopType over player 1's surviving units (owner == 1, not
        // the local-player slot)
        undefined4 player1AliveTroopValue; // 0x000145C4 length: 4
        // Only when GameCore.mapU4Int1: copy of playerDataArray[2].weightedLosses
        undefined4 player2WeightedLosses; // 0x000145C8 length: 4
        // accessed by 0x4b9d51, 0x4c0118, 0x4c0a0c, 0x4c0a15
        undefined1 field_0x145cc[4]; // 0x000145CC length: 4
        // Screen X (button X + 0x3a) of the overlay slider opened by the new-event-action menu
        undefined4 eventSliderPosX; // 0x000145D0 length: 4
        // Screen Y (button Y + 0x1c) of the overlay slider
        undefined4 eventSliderPosY; // 0x000145D4 length: 4
        undefined1 padding_0x145d8[4]; // 0x000145D8 length: 4
        undefined4 eventType; // 0x000145DC length: 4
        IngameEventHeader invasionEvent; // 0x000145E0 length: 16
        IngameInvasionEventItemContent invasionEventContent; // 0x000145F0 length: 176

    private:
        MapPropertiesState(MapPropertiesState const&);
        void operator=(MapPropertiesState const&);

    public:
        MapPropertiesState() {};
        ~MapPropertiesState() {};

        /**
         * NAME? Returns (value - 1 < 20) using a SIGNED compare (setl at 0x4B77EC), so it returns TRUE for every
         * value <= 20, including 0 and negative values, not only for 1..20.
         */
        BOOLEnum isValueAtMostTwenty(int value);

        /**
         * Initialises trading for a new map. Resets the trader counters (traderRelated1=10,
         * traderRelatedCounter2=6, others 0). For each of the 25 resources it copies the default buy/sell price
         * from RenderingDefinedData into copyOfBuyAndSalesPrice[i] and [i+25], clears unknownResouceFlagArray1/2[i]
         * and copies isResourceTradeable[i] from map section 1065.
         */
        void importTradingCosts();

        /**
         * Returns TRUE if any map event has header.tl_type 1. Type-1 events are invasions: they carry
         * data.invasion, as resetEuroUnitRestrictions shows.
         */
        BOOLEnum mapHasCertainEvent();

        /**
         * In campaign mission, economic campaign and builder modes, returns the index of the first scenario event
         * (tl_type 3) that has ScenarioEventType 1 or 0x1B and its first condition byte (data+0xF) set. This is the
         * event whose deadline the 'time until defeat' display shows. Otherwise returns -1.
         */
        int getEventIDForTimeUntilDefeatEventType();

        /**
         * NAME? For every scenario event (tl_type 3) with ScenarioEventType 0, 1, 0x1A or 0x1B, it sets header.done
         * to 1. The written short is 8 bytes before ScenarioEventType, i.e. header.done (0x4B795B). This marks the
         * events as already done, so it deactivates them rather than activating them. Called when launching a
         * multiplayer game.
         */
        void markScenarioGoalEventsDone();

        /**
         * Classifies the edited map's mission type. The map is military if there is a tl_type-1 (invasion) event,
         * any visible unit (state != ULS_INVISIBLE) owned by a player > 1, or, on siege maps, any non-zero
         * SEC_SiegeInformation or Section1067 count. Military gives scenarionMissionType 2 on siege maps and 3
         * otherwise. A non-military map gets 1 if a tl_type-3 event has ScenarioEventType 0, 1 or 0x1A, else 0. It
         * also copies the starting month/year into game time and clears done and pre_done of all events.
         */
        void determineScenarioMissionTypeAndResetEvents();

        /**
         * Returns value * DifficultyEventMultipliers[difficulty] / 100. In campaign mission 8 it returns value
         * unchanged.
         */
        int getDifficultyMultipliedValue(int value);

        /**
         * Sums the 20 siege attacker unit counts (SEC_SiegeInformation) and the 6 counts of section 1067. Stores
         * the total in DAT_MapEditorUnitPointsSum and returns it.
         */
        int sumUnitPoints();

        /**
         * Sums the 25 per-unit-type counts of the current event's invasion data into
         * DAT_InvasionEventItemUnitCountSum. Returns nothing.
         */
        void sumUnitCounts();

        /**
         * Bubble-sorts the map's events (0xE4 bytes each) in place, ascending by year, then month, then
         * header.tl_type. Swaps go through a 57-dword stack copy.
         */
        void sortEventsByDate();

        /**
         * Decrements eventsCount, then deletes the event at eventIndex by shifting all following events down one
         * slot.
         */
        void removeEventAtIndex(int eventIndex);

        /**
         * Rebuilds availability flags from the map's per-group buildingAvailability settings. First it sets all 380
         * buildingAvailabilityRelatedFlags (per mapper) to 1, buildingAvailabilityArray2[0..9] to 1 and [10..48] to
         * 0. Then it walks the groups of BuildingNameRelatedStructArray (40-byte entries, ending at
         * nameNumberInTextGroup == -1). For each group it reads up to 9 IDs, stopping at 0. A positive ID copies
         * the group's enabled state to flags[id]. A negative ID sets Array2[-id] = 1, but only if the group is
         * enabled. Finally it forces Array2[10,20,25,28,30,40] = 1 and stores (group count - 2) in field8_0x224.
         */
        void commitBuildingAvailability();

        /**
         * Returns whether a mapper (buildable item) is available in the build menu. Outposts are only available in
         * the editor. In the editor, everything else is TRUE, except that on multiplayer-type maps
         * (U2_mapType_singleOrMulti > 0) keep 1 and mappers 0x3E-0x40 are FALSE. Outside the editor, dog cages are
         * FALSE when the no-dogs option is set and the mode is neither solitary nor single-player skirmish, and
         * hunters are FALSE in non-solitary modes when rawDeerCount is 0. Otherwise it returns
         * buildingAvailabilityRelatedFlags[mapper].
         */
        BOOLEnum isMapperAvailable(MappersEnum mapper);

        /**
         * Returns 1 in the editor, otherwise buildingAvailabilityArray2[index] (MapPropertiesState+0x520, filled by
         * commitBuildingAvailability). The index is used directly, not offset by 0x38 as the old plate comment
         * claimed.
         */
        int isMercRecruitableForBuildingType(int index);

        /**
         * NAME? Map-version migration. It multiplies data.invasion.repeatMonths by 12 (years to months) for type-1
         * (invasion) events with a non-zero value. It then sets the 6 European troop *Producible_save flags, the 7
         * barracks-recruitability shorts and the 7 SEC_MercRecruitable shorts to 1.
         */
        void resetEuroUnitRestrictions();

        /**
         * For each scenario event (tl_type 3), if its first condition byte (data+0xF) is set and any of the next 39
         * condition bytes (stride 4, data+0x13..) is also set, it clears the first byte. The first condition, which
         * is the one getEventIDForTimeUntilDefeatEventType tests, is only kept when it is the only condition set.
         */
        void pruneInvalidEventTriggerLinks();

        /**
         * Stores the requested event type, resets the scratch invasion event and opens the trigger-event/invasion
         * modal text-input dialog.
         */
        void openEventTriggerMenu(undefined4 eventType);

        /**
         * Sums the 25 per-unit-type counts of invasionEventContent (5 x 5 dwords up to 0x1667EBC) into
         * DAT_InvasionEventItemUnitCountSum and returns the sum.
         */
        int sumInvasionEventUnitCount();

        /**
         * Copies the game month and year into monthCopy and yearCopy and clears field3179/3180/3183. For campaign
         * missions 17, 18, 19 and 20 it adds 1, 1, 6 and 3 months to monthCopy. Then, except for mission 18, if the
         * real mapAndTime.month (not monthCopy) is > 11 it wraps month and year, so monthCopy itself is never
         * normalised.
         */
        void adjustEventMonthAndYearForSection1047();

        /**
         * Creates a new attack wave slot for playerID (currentAttackWaveSlot incremented, wrapping to 1 at 50, slot
         * re-initialised and tagged with playerID). Spawns up to two unit groups (unitType1/count1, then
         * unitType2/count2 if unitType2 >= 1), each count scaled by difficulty (50/100/140/200%). Siege engines
         * (catapult, trebuchet, ram, tower, shield, fire ballista) are only added to the wave's
         * waveSiegeEngineCounts; other units are spawned via TribesState::spawnUnitsForAITribe in chunks of
         * count/(count/maxGroupSize+1) cycling over the wave's map-edge signposts (maxGroupSize 10 default;
         * slaves/slingers 20, Arab swordsmen 8, firethrowers 4, assassins 2). An unknown type code keeps the
         * previous kind/unit type/group size (all = playerID on the first pass, register setup at 0x4BC208). The
         * last argument is forwarded to spawnUnitsForAITribe, which stores it in each spawned unit's
         * calculatedOwnerPlayerIndex.
         */
        void spawnAttackWaveForPlayer(
            int param_1, int param_2, int param_3, int param_4, int param_5, undefined4 param_6);

        /**
         * Appends a new event (sets currentEventID and field50_0x13568=3, then initializeScenarioEvent) dated next
         * month, wrapping into the next year. It sets ScenarioEventType 1, clears the short at data+8, sets
         * condition byte data+0x17 (condition index 2) and re-sorts the events by date.
         */
        void createScenarioEventForNextMonth();

        /**
         * Mode 2: appends event A (ScenarioEventType 1, condition byte data+0x3F; data+8 not cleared) and event B
         * (ScenarioEventType 0, data+8 cleared, bytes data+0x1B and data+0x4B set). Mode 1: appends event A (type
         * 1, data+8 cleared, bytes data+0x17 and data+0x3F) and event B (type 0, data+8 cleared, byte data+0x4B).
         * Both events are dated next month. It then re-sorts events by date; other modes only re-sort.
         */
        void createChainedMissionOutcomeEvents(int outcomeMode);

        /**
         * Computes the end-of-mission score for the local player. Only the last type-3 scenario event with subtype
         * 0/0x1a (victory conditions) is scored; the deadline month/year comes from the last enabled type-3 event
         * with subtype 1/0x1b. Each enabled goods goal (4 slots), gold and population goal stores goods type,
         * surplus = current - difficulty-scaled required amount and points = surplus * factor (5 for goods
         * 2,10..13; 20 for 6; 50 for 0x11..0x18; 10 for other goods; 1 for gold/population); a goal occupies a slot
         * only if surplus > 0. Score = per-difficulty base + 100 * months left before the deadline (clamped >= 0) +
         * goal points; for campaign missions and builder maps with SEC_U3_MapType2_1 < 2 adds (100 - loss%) * 100,
         * loss% = weightedLosses*100/(weightedLosses + alive troop value). If mapU4Int1 is set also records player
         * 1's alive troop value, player 2's weightedLosses and their sum.
         */
        void computeMissionCompletionScore();

        /**
         * Resets scenario properties to defaults: starting year 1181 (also game year), month 0, all 25 starting
         * resources 0 and all tradeable, no events, siege info and Section1067 cleared, starting popularity 100,
         * writes the year into user text slot 10, makes all 100 building availability entries 1 and commits them.
         */
        void setStartingYearAndStartingResources();

        /**
         * Scenario-editor prepare: forces SEC_StartingYear to 1181 if < 1000, writes it into user text slot 10 and
         * year_copy, resets field47/field48, then for every event whose header field at year+4 == 1 and field at
         * year+0x7c != 0 and whose date satisfies (eventYear < gameYear) or (eventYear == gameYear and gameMonth <
         * eventMonth) - note the same-year test selects events later in the year, verified in machine code at
         * 0x4BEBB8..0x4BEBC7 - it saves the event year into year+0x78 if that is 0, else restores the year from it.
         * Finally commits building availability.
         */
        void updateEventYearsAndCommitBuildingAvailability();

        /**
         * Legacy save/map upgrade (its callers run it for versions < 0x9A): for every scenario event with header
         * type 3, copies the first 0xBC bytes of the event to the stack, clears its 40 condition slots ({short
         * value, byte subType, byte enabled}) and refills the first 20 from the old split layout (enabled flags at
         * copy+0x1C+4i, value/subType at copy+0x6C/+0x6E+4i); then calls pruneInvalidEventTriggerLinks.
         */
        void upgradeLegacyScenarioEventConditions();

        /**
         * Spawns the manually triggered invasion: advances attackInfo.currentAttackWaveSlot (wraps to 1 after 49), initialises
         * that attack-wave slot, owner = crusaderArabian+2, then for slider indices 0..24 of
         * invasionEventContent.unitCountsPerUnitType: infantry is spawned via spawnUnitsIntoNewTribe in groups of
         * count/(count/10+1) at map-edge signpost unknownSignpostRelatedArray[wave], cycling through its spawn
         * points; catapult/trebuchet/ram/siege tower/shield/fire ballista counts are only added to the wave's byte
         * counters (indices 0,1,2,3,4,8). Plays the European/Arabian attack video+sound for crusaderArabian 0/1 and
         * on every path sets eventsCount (this+0x5AC) = 0. Slider index 24 has no unit type: a nonzero value there
         * would divide by zero.
         */
        void spawnInvasionEventAttackWave();

        /**
         * Per-tick script for the Stronghold-1-style military campaign missions 16-20 (missionNumber 0x10-0x14;
         * Rat/Snake/Pig/Wolf dialogue), apparently an unreachable SH1 leftover in normal Crusader play (its only
         * caller enters it for GM_CAMPAIGN_MISSION outside GM_SOLITARY). If the local player's gameOutcome is set
         * it counts down missionEndCountdown (paused while a Bink video or queued message plays) and at 0 closes
         * dialogs and, in GM_CAMPAIGN_MISSION, advances the mission (win) or shows the game-lost view (loss). If
         * the local lord was killed it sets gameOutcome=2, AI control, countdown 240 (640 on builder siege maps)
         * and the defeat banner. Otherwise runs the per-mission state machine in militaryMissionScriptStage (dated
         * triggers via scriptTriggerMonth/Year, Bink+WAV dialogue, spawnAttackWaveForPlayer waves, AI-lord-killed /
         * aiPlayerState / enemyHitCountByPlayer checks; mission 20 tracks the three rodent lords with
         * militaryMissionScriptFlags) and finally sets gameOutcome=1, countdown 240 and the victory banner.
         * Original bug: after scheduling scriptTriggerMonth = month+N the December-wrap test and fix-up use the
         * live month/year (always 0..11) instead of the trigger, so the fix-up never runs and an exact-date trigger
         * scheduled past December (month 12..14) never matches; only stages with the 'year > scriptTriggerYear'
         * fallback still advance.
         */
        void updateMilitaryCampaignMissionState();

        /**
         * Resolves the map file name via ResourceManager (FRT_MAPS) and reads map header sections 0x427, 0x426,
         * 0x428, 0x420 and 0x421 (siege/scenario header info) through FilePackager. If the file version is below
         * 0x9a (154) it upgrades legacy scenario event conditions (upgradeLegacyScenarioEventConditions).
         */
        void loadMapSiegeHeaderSections(char* mapFileName);

        /**
         * Per-tick scenario-event driver. With currentGameMode == GM_SOLITARY it runs the scenario logic (not in
         * GM_EDITOR/GM_SIEGE_THAT; tutorial step update in GM_CRUSADER_TUTORIAL; nothing while section1095 == 1);
         * otherwise it only tail-jumps to updateMilitaryCampaignMissionState when gameMode_2 == GM_CAMPAIGN_MISSION
         * (0x4C31B3/0x4C31CD). While the local player's gameOutcome is 0 it ticks down SEC_VictoryTicksLeft (if
         * victoryTimerActive) and, at start of day: forces a win if forceLocalPlayerVictory is set; ages
         * recentEventTimer[] (reset after 1200); one year after the start warns once about missing wells if a fire
         * event (type 0x1E) exists; then walks the date-sorted due scenarioEvents: tl_type 1 invasions spawn
         * difficulty-scaled troops (50/100/140/200%) as new tribes at the wave's map-edge signposts (siege engines
         * only add to waveSiegeEngineCounts), announce once per faction unless suppressed and reschedule by
         * invasion.repeatMonths; tl_type 2 is just marked done; tl_type 3 evaluates its 40 conditions and fires
         * when all enabled ones are met (or any one when the all/any word is 0), running the action (win unless a
         * later due win event exists, lose, fair, plague, crop/tree disasters, rabbits, lions, bandits, outlaws,
         * marriage, jester, food theft, fire, time halt, xbow unlock, invasion warnings on/off, delayed win/lose
         * next month, ...) and rescheduling repeatable ones (interval + random quarter for > 3 months, repeatCount
         * 10 = forever). Afterwards it plays 'sands of time' warnings (size-dependent text/WAV) for invasions due 3
         * months ahead, marking pre_done, and on tick 0x97 of week 3 sets invasionNextMonthCountdown = 40 if an
         * invasion is due next month. Once won/lost it counts down missionEndCountdown (paused while a video or
         * queued message plays) and then, depending on gameMode_2, advances the campaign/mission, shows the lost
         * screen, or opens the finish/quit dialog.
         */
        void processSingleplayerEvents();

        /**
         * Loads a map/scenario by name: saves mission number, game mode, difficulty, the six unit-producible flags,
         * player slot, jester/lady flags and two mapAndTime fields, resets teams and map sections, reads the .map
         * file via FilePackager, then restores them (currentPlayerFullIDArray reset to -1 except the own slot = 1).
         * Mission 1: sets a field of up to 8 non-invisible UT_E_ARCHER units (short at unitType+8 == 1) to 3.
         * Copies mapName into DAT_MapPropertiesState, removes jester/lady for campaign modes, zeroes the 8000-dword
         * events-extra table, sets start month/year; only if month/year are still the map's start values (missions
         * 16-20 may adjust them) copies starting goods, siege info, popularity*10. Then rebuilds map/AI/selection
         * state, recruitability (euro/merc) and trade costs, finally overwrites the producible flags with the map's
         * *_save values and resets game timers.
         */
        void loadMap(char* mapName);

        /**
         * For a 1-based mission number (1..20) looks up the mission's map file name in
         * DAT_MissionAestheticsDefinedData and calls loadMapSiegeHeaderSections on it; does nothing for numbers
         * above 20. The four range branches are identical. Note field15_0x3c[mission-1] is the same memory as
         * field14_0x38[mission] used by loadMissionMapAndSetLord.
         */
        void loadMapSiegeHeaderForMissionIndex(char* missionNumber);

        /**
         * Loads the map of a 1-based campaign mission (1..20) via loadMap using the mission map-name table in
         * DAT_MissionAestheticsDefinedData, then always calls UnitsState::setMissionNumberSpecificLord for that
         * mission (even if the number was out of range and no map was loaded).
         */
        void loadMissionMapAndSetLord(int missionNumber);
    };

    static_assert_cpp98_obj(sizeof(MapPropertiesState) == 83616, MapPropertiesState);

#pragma pack(pop)

} // namespace Map
} // namespace OpenSHC
