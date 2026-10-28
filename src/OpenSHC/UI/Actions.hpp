/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/Actions.hpp'
*/

#pragma once

#include "OpenSHC/Game/Resources/ResourceType.hpp"
namespace OpenSHC {
namespace UI {
    namespace Actions {

        using OpenSHC::Game::Resources::ResourceType;

        /**
         * Starts a single-player map. Sets section1066, queues GCT_ASK_FOR_SLOT_ASSIGNMENT, then loads
         * '<GameCore.standaloneFilename>.map' if useStandaloneFilename is set, else the map selected in the map
         * list (whose name is afterwards stored in standaloneFilename). Forces all troops producible/recruitable,
         * stores the difficulty per mission type and copies recruitability into game state. Mission type 2 (siege):
         * creates the chained outcome events, kills wildlife, sets slot colours, and if the local player is slot 1
         * adds an attack wave for player 4 whose siege-engine counts are SEC_Section1067 scaled by 66/100/133/166%
         * per difficulty; in normal mode a local slot-2 player gets startGoods[25..44] = 70% of the map's values
         * and tunnelersCount cut to 70%, in advanced mode the siege troop counts come from
         * DAT_SiegeInformationArray (index 10 goes to both siegeInformation.arabianArchers and tunnelersCount, see
         * BUG?); then all peasants are deleted. Mission type 3 with difficulty>0 (and no special map event):
         * deletes every 4th/3rd/2nd own unit (up to 3 passes) until 1/4, 1/3 or 1/2 of the army value is removed.
         * Other types clear the siege info. Finally removes jester/lady (type 0), for a local slot-2 player moves
         * pending gold into current gold, sets gold 600 if mapU4Int1, sets missionNumber=28, focuses the camera on
         * player 1's keep or signpost 0, clears obstacles around signposts if mapU4Int1, and switches to the build
         * menu (or the scenario description for invasions not started with param 1). BUG? (likely): in advanced
         * siege mode the tunneler count chosen in the siege setup (array index 10, initialised from
         * tunnelersCount*7/10 by the map-choice menu) is also written to siegeInformation.arabianArchers, which the
         * siege spawner turns into Arabian archers.
         */
        void __cdecl LaunchStandaloneMapGame(int useStandaloneFilename);

        /**
         * Map editor 'place people' tool. Maps the current mapper command to a unit type, tribe type, body sprite
         * and optional top sprite. While the mouse is not released it only draws a ghost preview, tinted when the
         * tile's LogicLayer is blocked or (Siege That mode) the start-gold budget is short. On release it pays the
         * gold cost in Siege That mode, then spawns either a single siege engine/shield (spawnUnit, no tribe type)
         * or a new tribe of DAT_TileMapState.placeUnitCount soldiers. Engineers placed with the pots variant get
         * resourceToDeposit=1.
         */
        void __cdecl PlaceUnit();

        /**
         * Starts a skirmish/multiplayer game from the lobby settings. Backs up state the .map load would overwrite
         * (lobby structure, AI variations, teams, groups, lord types, RNG seed, slot id, points, fog, autosave,
         * final results, trail progress), loads '<mapName>.map', then restores it. Removes pre-placed keeps and
         * lords, recording their positions per map slot in the reused _playerTeams stack area (x/y of slot k at
         * _playerTeams[2k]/[2k+1]); if there are fewer players than keeps, every map slot whose start position has
         * no player assigned (playerPositionsArray[slot-1] < 0, shown as kickRequestedPerPlayer[slot+8]) and that
         * had a keep is destroyed. Swaps ownership so each player gets his start position (_storedLordTypes reused
         * as the position-swap map), then places keeps: AI players get an AIV castle (whichCastle is really a
         * pointer to per-player AIV choices indexed by slot-1, NULL = best AIV with random start; default keep if
         * no AIV fits), humans a default keep, plus a flag entity; the camera focuses on the local player's keep.
         * In King-of-the-Hill mode the first empty slot gets a keep at pos5KeepX/Y. Then sets start goods (start
         * gold from SkirmishStartGoldByIntensity), start troops by advantage balance/lord type, popularity, date
         * 6/1181, default prices, tradeability (resource 16 disabled below tech level 3), recruitability and final
         * statistics, recomputes AI heatmaps and switches to the build menu. The local named groupLoopPlayer
         * actually holds the stack security cookie.
         */
        void __cdecl LaunchSkirmishGame(int aivChoicesPtr);

        /**
         * Records why a market buy/sell or ally goods transfer failed for the local player and timestamps it
         * (timeStorageMarketFailState = timeGetTime()). For state 3 (no storage building) and 4 (storage full) the
         * stored code depends on the storage building of the resource: stockpile 6/9, granary 5/8, armory 7/10
         * (other storage types store nothing). Any other state (e.g. 2 = not enough goods) is stored as is. The
         * decompiler's 'unaff_retaddr' is the 'state' argument: it wrongly assumed
         * getBuildingStorageTypeForResourceType leaves its argument on the stack.
         */
        void __cdecl SetStorageMarketFailState(int state, ResourceType resource);

    } // namespace Actions
} // namespace UI
} // namespace OpenSHC
