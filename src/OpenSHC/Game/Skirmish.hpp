/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Game/Skirmish.hpp'
*/

#pragma once

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
namespace OpenSHC {
namespace Game {
    namespace Skirmish {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /**
         * Derives skirmish start settings from skirmishTechLevel (0-4): sets
         * skirmishGameIntensityType/IntensityType2 and (only for valid levels) default popularity 80 plus
         * skirmishUnknownSetting1[0],[1],[3] = 1; copies a 20-entry row from
         * RenderingDefinedData.skirmishStartLevelTable[intensity-1][techLevel] and a 10-entry row from
         * SkirmishIntensityRelatedArray2[(type2-1)*5+techLevel] (or zeros for type2 0) into GameSynchronyState,
         * then queues GCT_CHANGE_GAME_INTENSITY_OR_BALANCE and resets two fields to -1.
         */
        void __cdecl SetupSkirmishBalanceAndOrIntensity();

        /**
         * Rebuilds the local player's ally list: for every other slot 1-8 that is occupied (human id != -1 or AI
         * set) and on the same team (playerTeams) stores the player id in DAT_AllyPlayerIDs, at most
         * 6 entries, count in DAT_AlliesCount. Only once more than 400 ticks have passed since GameCore.mapStartTick
         * are lords checked: then it returns early (count 0) if the local lord is dead and skips allies without a
         * living lord. Finally clamps DAT_SelectedAllyIndex into [0, count-1].
         */
        void __cdecl RecalculateAllies();

        /**
         * Sets up a single-player skirmish-trail mission (index param; record taken from the
         * normal/Extreme/Warchest trail table by GameCore.currentTrailType): resets the lobby, makes the local
         * player host in slot 1 with the user's name, copies AI types for slots 2..numberOfPlayers, start
         * positions, teams (0xff beyond numberOfPlayers), map name, fairness and start levels from the
         * CampaignTrailMission record, records the trail progress, launches the game with the mission's AIV list
         * and then sets start year/month (also in finalResults) from the trail's start-date table.
         */
        void __cdecl SetupSkirmishMode(int skirmishTrailMission);

        /**
         * Calls GetLocalTime and stores wDay/wMonth/wYear into DAT_SkMasterDataEntry.localTimeDay/Month/Year, plus
         * the game duration in minutes (GameCore.gameDuration / 60000) and the map tick counter. Disassembly
         * confirms the day field gets wDay ([esp+6]); the decompiled local_10/local_e split is a Ghidra stack
         * artifact. Effectively void: the int return is the leftover low half of the /60000 magic multiply.
         */
        int __cdecl StoreLocalTime();

        /**
         * Fills the temporary DAT_SkMasterDataEntry for the just-finished skirmish: score param, map name, SkMaster
         * score of the local player, activePlayerCount (consecutive active slots from slot 1, stopping at the first
         * inactive one), per-slot groups, AI types and alive flags, local lord type, local time/duration
         * (StoreLocalTime) and a copy of the final SkirmishStatistics (0x1de dwords). Always returns TRUE.
         */
        BOOLEnum __cdecl StoreCurrentGameIntoTemporarySKMasterEntry(int score);

        /**
         * Records the finished game in the SkMasters2 table (max 250 entries, sorted by skMasterScore descending):
         * builds the entry via StoreCurrentGameIntoTemporarySKMasterEntry, inserts before the first entry with a
         * lower skMasterScore (or appends), aborts if the table is full and the new score ranks last, shifts later
         * entries down (a full table drops its last entry), copies the entry in, bumps the count if below 250 and
         * saves with IO::WriteSkMasters2.
         */
        void __cdecl StoreGameIntoSKMasters(int score);

        /**
         * Deletes SkMasters2 leaderboard entry `index` (if in range) by shifting all following 0xBF0-byte entries
         * up one slot, decrementing DAT_SkMasters2Data_Count and saving via IO::WriteSkMasters2.
         */
        void __cdecl SkirmishLeaderboard_DeleteEntry(int index);

        /**
         * Sorts the leaderboard display list: selection-sorts the g_leaderboardEntryCount candidate entry indices
         * (g_leaderboardCandidateIndices) by their keys (g_leaderboardSortKeys, largest unsigned first) into g_leaderboardSortedIndices;
         * for sortColumn 2 (name) outside filter mode 1 additionally bubble-sorts adjacent entries by mapName
         * ascending (stricmp, max 2500 passes; the DAT_ArrayOfStoredMenuStrings[0x20]+... expression is
         * g_leaderboardSortedIndices[i-1], 0xeb96d4 in disassembly). Reverses the list when the parameter is 0 (callers
         * pass DAT_MissionDefinedData.descending, so the param name reverseOrder is inverted).
         */
        void __cdecl sortSkMastersRecordList(int reverseOrder);

        /**
         * Builds the leaderboard (SkMasters2) display order: marks all entries visible, then filter
         * g_leaderboardSortMode 1 hides score==0 and 2 hides score!=0 entries. sortColumn<2: lists visible entries
         * in table order (descending==1) or reversed (descending==0). Otherwise builds keys and calls
         * sortSkMastersRecordList: column 2 = name (mode 1: key 0x50-score; else trail entries get their stored
         * mapName overwritten with TEXT_TRAIL_NAMES_CRU[score], key = ~(lowercase first two chars)), 3 = ~duration,
         * 4 = date ((year-2000)*16+month)*32+day.
         */
        void __cdecl Skirmish_PrepareLeaderboardView();

    } // namespace Skirmish
} // namespace Game
} // namespace OpenSHC
