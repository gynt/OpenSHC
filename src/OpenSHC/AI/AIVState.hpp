/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/AI/AIVState.hpp'
*/

#pragma once

#include "OpenSHC/AI/AIGridComputationResourceType.hpp"
#include "OpenSHC/AI/AIMapExtraInfo.hpp"
#include "OpenSHC/AI/AIV/AIVBuildingType2.hpp"
#include "OpenSHC/AI/AIV/AIVBuildingType2Short.hpp"
#include "OpenSHC/AI/AIV/AIVSpec.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Game/Player/PlayerID.hpp"
#include "OpenSHC/Map/HeatMap.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AIGridComputationResourceType;
    using OpenSHC::AI::AIMapExtraInfo;
    using OpenSHC::AI::AIV::AIVBuildingType2;
    using OpenSHC::AI::AIV::AIVBuildingType2Short;
    using OpenSHC::AI::AIV::AIVSpec;
    using OpenSHC::Commands::MappersEnum;
    using OpenSHC::Game::Player::PlayerID;
    using OpenSHC::Map::HeatMap;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

    // SIZE: 0x000B6C70
    class AIVState {
    public:
        int totalSteps; // 0x00000000 length: 4
        AIVSpec aivs[9]; // 0x00000004 length: 252504
        int aivFileHash[16][8]; // 0x0003DA5C length: 512
        int aivFilePresent[16][8]; // 0x0003DC5C length: 512
        int receivedAIVFileHash[9][16][8]; // 0x0003DE5C length: 4608
        int aivFileAvailabilityPerAIArray[20]; // 0x0003F05C length: 80
        int numberOfAIsWithAIV; // 0x0003F0AC length: 4
        int keepX; // 0x0003F0B0 length: 4
        int keepY; // 0x0003F0B4 length: 4
        int counter; // 0x0003F0B8 length: 4
        undefined1 typeInfo; // 0x0003F0BC length: 1
        undefined1 defensesHeightAndEdgeInformation; // 0x0003F0BD length: 1
        undefined1 unusedUnk; // 0x0003F0BE length: 1
        undefined1 noise; // 0x0003F0BF length: 1
        AIVBuildingType2Short constructions[10000]; // 0x0003F0C0 length: 20000
        int steps[100][100]; // 0x00043EE0 length: 40000
        short rotatedConstructions[100][100]; // 0x0004DB20 length: 20000
        int rotatedSteps[100][100]; // 0x00052940 length: 40000
        int pauses[20]; // 0x0005C580 length: 80
        int unusedPauses[30]; // 0x0005C5D0 length: 120
        int pauseDelay; // 0x0005C648 length: 4
        int unitLocations[24][10]; // 0x0005C64C length: 960
        undefined4 buildingCounter; // 0x0005CA0C length: 4
        undefined4 invalidTileCounter; // 0x0005CA10 length: 4
        AIMapExtraInfo mapExtraInfo; // 0x0005CA14 length: 816
        HeatMap heatMaps[80][80]; // 0x0005CD44 length: 307200
        int visitCount; // 0x000A7D44 length: 4
        // index of the next cell dequeued from heatMapX/YArray, wraps at 0x1900 (review 310)
        undefined4 bfsQueueHead; // 0x000A7D48 length: 4
        // enqueue index of the same BFS queue; search ends when head == tail (review 310)
        undefined4 bfsQueueTail; // 0x000A7D4C length: 4
        int heatMapXArray[6400]; // 0x000A7D50 length: 25600
        int heatMapYArray[6400]; // 0x000AE150 length: 25600
        int buildingApproriateGridXPosition; // 0x000B4550 length: 4
        int buildingAppropriateGridYPosition; // 0x000B4554 length: 4
        byte isHandled[10000]; // 0x000B4558 length: 10000
        int aivCount; // 0x000B6C68 length: 4
        int unused01; // 0x000B6C6C length: 4

    private:
        AIVState(AIVState const&);
        void operator=(AIVState const&);

    public:
        AIVState() {};
        ~AIVState() {};

        // Constructor
        /**
         * Constructor of the global AIVState: wipes AIV records and heat maps and returns &DAT_AIVState.
         */
        AIVState* Constructor_AIVState();

        /**
         * At startup, hashes (sum of first 1024 bytes) each of the 8 AIV castle files for every AI lord into
         * aivFileHash (-1 = missing), stores per-AI available castle counts and builds the list of AI lord IDs that
         * have at least one AIV (numberOfAIsWithAIV).
         */
        void setAvailableAIV();

        /**
         * Rebuilds the list of selectable AI lords. Single player (solitary/skirmish): every AI with local AIV
         * files. Multiplayer host: only AIs for which every connected player reported AIVs (players without a
         * report ignored, own data used for the host slot); AI slots using a no-longer-available lord are removed
         * (RemovePositionOfPlayer, queues GCT_HOST_REMOVE_PLAYER_BY_SLOT, reorders teams, reparseMaps) and the
         * lobby lord-select dialog is switched between basic (<=8) and extended (>8) variants. Non-host clients do
         * nothing.
         */
        void hostChecksLobbyAIVAvailability();

        /**
         * Fills aivFilePresent[16][8]: all 1 in single-player skirmish; otherwise a castle is marked present only
         * if every connected player has the same, non-missing (-1) file hash for it (0 if no player is connected).
         */
        void setAIVFilePresenceByFileHashArray();

        /**
         * For each AI-controlled slot 1-8 (no human, AI assigned) copies the name string from
         * GameSynchronyState.finalResults.names into the player-name array at 0x1A2347E (stride 0xFA) and refreshes
         * its AIV spec's build interval from the AIC. Note: copy direction is finalResults -> player names, the
         * plate comment has it reversed.
         */
        void syncAIPlayerNamesAndBuildIntervals();

        /**
         * Allocates the first free AIV spec slot (1-8) for a player: stores playerID and aiType, resets step
         * goal/poor counter/subtype, sets the AIC build interval, increments aivCount and returns the slot index (0
         * if none free).
         */
        int setupAIVMetadata(int playerID);

        /**
         * Stores the keep position of an AIV spec and its 100x100 layout origin (keep - 43), and derives the castle
         * orientation from the keep's direction toward map center (200,200), low bit cleared, with 2 and 6 swapped.
         */
        void setKeepOffsetAndOrientation(int aiID, int keepX, int keepY);

        /**
         * Maps an AIV building type to the placement (Mappers) building type: walls, crenels, stairs, moats and
         * pitch ditch explicitly; tower and later types via an 80-entry lookup table at AIVDefinedData+0xF4 indexed
         * from AIVBT_TOWER1; out of range -> M_MAPPER_GENERIC.
         */
        MappersEnum convertAIVBuildingTypeToCommandBuildingType(AIVBuildingType2 aivBuildingType);

        /**
         * Rotates the loaded 100x100 AIV grids (constructions: shorts, steps: ints) by orientation 2/4/6 (quarter
         * turn / half turn / opposite quarter turn) into the rotated buffers, then copies them back over the
         * originals; orientation 0 is a no-op.
         */
        void rotateAIV(int orientation);

        /**
         * Spawns the AI's flag entity (entity type = AIC flagType of the player's aiType) at the centre of each of
         * the 10 AIV flag slots (location type 0x15) whose tile has positive total height and does not already hold
         * an entity of that type.
         */
        void aiPlaceFlag(PlayerID playerID);

        /**
         * Spawns a brazier entity on each of the 10 AIV brazier slots (location type 0x14) whose tile has positive
         * total height and no brazier already.
         */
        void aiPlaceBrazier(PlayerID playerID);

        /**
         * Outside GM_SOLITARY, increments the structureCount of the AIV heat-map cell covering tile (x,y) (5x5-tile
         * cells).
         */
        void incrementStructureHeatMapTile(int x, int y);

        /**
         * Tries to execute one build step of the player's AIV castle layout (aivBuildingSteps[step]); while
         * isPausing only hovel steps are allowed. Skips disabled/no-room steps, counts down the step's wait timer,
         * checks resources and many AICState veto checks, then plans moats / places pitch ditches (both always
         * return FALSE), places walls and stairs tile by tile (TRUE unless illegalBuild), or places a normal
         * building with an orientation derived from the AIV keep orientation (barracks/guilds/oil smelter also
         * prepare their extra part tiles). An already-built building step is only re-placed when the building at
         * its location is no longer of that type. Afterwards wait = 10 on success / 16 on failure and buildStatus
         * becomes built, insufficient_roomUnk (farms) or insufficient_resources; returns TRUE if placement
         * succeeded. The step parameter is reused as the building orientation after the step index is copied to a
         * local; isPausing is reused as the wall-tile loop counter.
         */
        BOOLEnum aiPlaceAIVBuilding(PlayerID playerID, int stepThenOrientation, int isPausingThenWallTileIdx);

        /**
         * Zeroes the whole AIV heat-map grid (0x4B000 bytes at 0x18C37F4, i.e. DAT_AIVState.heatMaps).
         */
        void clearTheHeatmaps();

        /**
         * Sets destructionBasedPlacementCooldown = 10 in the heat-map cell (5x5-tile grid) containing tile (x, y);
         * the grid-location searches skip cells whose cooldown is nonzero. Called when the AI destroys/loses a
         * building.
         */
        void resetCountdownInHeatMap(int x, int y);

        /**
         * Counts how many map tiles belong to each path-connection region (TileMapState.PathConnectionLayer, ids >
         * 0) into a 10000-entry stack array and returns the id of the region with the most tiles, i.e. the largest
         * connected area.
         */
        int computeLargestSeparateArea();

        /**
         * If the player has fewer farms than available oasis grid cells and the oasis search cooldown has expired,
         * runs a BFS over the 80x80 AIV heat map (4 neighbour directions, depth <= 40) starting at the campground
         * cell and places the farm in the first fully reachable cell without structures/trees/cooldown and with
         * enough oasis scrub (at cell*5 + placement nudge). The incoming 'commandBuildingType' is really a
         * BuildingType (aiPlaceFarm passes its buildingType; hence the odd MappersEnum decodes) and is mapped here
         * to the WHEAT/HOPS/APPLE/CATTLE farm mapper. Returns 1 if a farm was placed (cell structureCount set to
         * 1); on failure sets algoOasisCooldownUnk = 5, while the cooldown is running it is decremented.
         */
        int findSuitableFarmLocationAndPlaceFarm(PlayerID playerID, MappersEnum commandBuildingType);

        /**
         * BFS (4 directions, depth <= 40) over the AIV heat map from the player's campground cell, scoring
         * reachable cells with trees: score = 5*treeCount - 3*depth (worsened when woodRelatedCountdownTo0 is set)
         * and keeping the best one. Once enough tree cells were seen (>10, or >5 beyond depth 20, or >0 beyond
         * depth 30) each further tree cell aborts the expansion of the current cell (it does not end the whole
         * BFS). Stores the best cell in buildingApproriateGridX/YPosition (else -1); while algoTreeCooldownUnk > 0
         * it is only decremented, and it is set to 5 if no tree cell was found. The playerID param is reused as the
         * direction-table pointer.
         */
        void findAppropriateWoodCutterGridLocation(int playerID);

        /**
         * For oil, iron or boulder placement: returns (result -1) if the player already has at least as many pitch
         * rigs/iron mines/quarries as available grid cells, or decrements the per-resource cooldown if it is
         * running. Otherwise BFS (4 directions, depth <= 40) from the campground cell and picks the first cell with
         * enough resource tiles (oil>=3 and marsh>=10, iron>=7, boulders>=8), no structures or destruction
         * cooldown, owner none or same team, its non-largest-area tiles all impassable (iron tolerates up to 4
         * others) and a height span < 12 (boulders < 40). Result in buildingApproriateGridX/YPosition; if nothing
         * is found the resource cooldown is set to 5.
         */
        void findAppropriateGridLocationForResourceTypeBuilding(
            int playerID, AIGridComputationResourceType resourceTypeNumber);

        /**
         * At skirmish start: BFS (4 directions, depth <= 40) over the AIV heat map from the player's campground
         * cell and counts reachable cells suitable for oil, iron, boulders, trees or oasis farms into the player's
         * available*GridTiles (each cell is classified at most once, first matching type in that priority order,
         * and needs a small height span). Resets each algo*Cooldown to -1 and then to 0 for resource types that
         * have at least one cell.
         */
        void recomputeAIAvailableGridTiles(int playerID);

        /**
         * BFS (8 neighbour directions, no depth limit) over the AIV heat map starting at grid cell (gridX, gridY)
         * and stores in buildingApproriateGridX/YPosition the first neighbour cell found that is flat, fully in the
         * largest area, not at the map edge and free of structures, trees, boulders and destruction cooldown (-1 if
         * none, or if the start cell is out of range / at the edge). The start cell itself is never chosen.
         */
        void findSuitableGridLocationFittingCriteria(uint gridX, uint gridY);

        /**
         * BFS (8 neighbour directions) from grid cell (gridX, gridY) over the 80x80 AIV heat map looking for a
         * dequeued cell that lies fully in the largest area and whose 8 neighbours are all free (flat, no
         * structures/trees/boulders/cooldown, not near the edge, in largest area); on success stores that cell +
         * direction offset [7] into buildingApproriateGridX/YPosition, else leaves -1. The gridX parameter is
         * reused as the free-cell counter (success when it reaches 9). ECX (= &DAT_AIVState) is preserved for the
         * caller, which only reads the stored position; the returned pointer is leftover EAX (input X, queue index
         * or result Y) and carries no meaning.
         */
        void findAppropriateGridLocationForBuilding(uint gridXOrFreeCellCount, uint gridY);

        /**
         * Resets the AIV state: aivCount = 0, zeroes the 9 loaded AIV records (0x6D98 bytes each starting at
         * 0x1866AB4) and clears the heat maps.
         */
        void wipeAIVsAndHeatMaps();

        /**
         * Loads and rotates the AIV castle layout for AIV slot playerIDUnk, then converts its 100x100 construction
         * grid into build steps: the first keep tile sets keepX/keepY; each other single building gets one step
         * (quantity 1, tile location) at its first valid tile; walls/moats/pitch ditches are collected in repeated
         * grid passes, one step number per pass, appending their tile indices to the AIV locationsArray
         * (step.location = start index, quantity = tile count). Then decodes the 22x10 AIV unit-location slots
         * (encoded row*100+col, rotated by keepOrientation 0/2/4/6, 5 per unrolled iteration) into tile indices in
         * playerDataArray[playerID2Unk].aivUnitLocationSlots and counts the valid ones per group (groups 9, 11, 18
         * skipped, count 0), copies pauses/pause delay (default 100) and disables steps whose type is
         * null/keep/pond. playerIDUnk is the AIV index (later reused as a pointer to the per-group count),
         * playerID2Unk the player index.
         */
        void applyAIV(int aivIndexThenGroupCountPtr, int playerID2Unk);

        /**
         * Test-places the loaded AIV layout at the AIV keep offset of aivs[playerID]: for every construction tile
         * of type >= 2 that maps to a valid map tile it sets the building's height limits, stores the tile's
         * min/max height and calls isBuildingPlacementBlockedAtTile; blocked tiles are marked handled, counted in
         * invalidTileCounter and the smallest build-step number among them is tracked (type-1 tiles are just marked
         * handled). Returns that minimum step - 1 (999999 if nothing is blocked), i.e. how many steps can be built
         * before the first obstruction. The local typeRowStartOrResult is actually the grid column counter.
         */
        int computeAIVPlacementFit(int playerID);

        /**
         * AI farm placement: returns FALSE for buildingType < 1; converts the BuildingType to its mapper type,
         * checks (or plans to buy) the required resources, then calls findSuitableFarmLocationAndPlaceFarm with the
         * raw BuildingType. Returns TRUE if a farm was placed.
         */
        BOOLEnum aiPlaceFarm(int playerID, MappersEnum buildingType);

        /**
         * AI woodcutter placement: if the woodcutter's hut resources are available (or planned) and
         * BuildingsState.unknownCountdown01 > 19, finds the best tree cell, marks it with woodRelatedCountdownTo0 =
         * 4, BFS-searches a free grid cell from there and places the hut at that cell's top-left tile (cell*5),
         * incrementing the cell's structureCount.
         */
        void aiPlaceWoodcuttershut(int playerID);

        /**
         * If the player owns a valid engineer's guild, BFS-searches a free heat-map cell starting from the guild's
         * cell and reserves it (structureCount++). Returns TRUE if a spot was found (left in
         * buildingApproriateGridX/YPosition).
         */
        BOOLEnum findSpotNearEngineersGuild(int playerID);

        /**
         * If ox-tether resources are available and BuildingsState.unknownCountdown01 > 19, places an extra ox
         * tether in a free cell found near the player's highestLoadedQuarryUnk quarry (search start nudged by one
         * of 9 offsets) and links it without checking placement success: stores the tether ID in the first free of
         * the quarry's 3 quarryLinkedOxTethers slots and the quarry ID in the tether. If all 3 slots are full only
         * the tether-to-quarry link is set.
         */
        void aiPlaceAdditionalOxtether(PlayerID playerID);

        /**
         * AI pitch rig placement: if resources allow and BuildingsState.unknownCountdown01 > 19, searches an oil
         * grid cell via findAppropriateGridLocationForResourceTypeBuilding(AIGCRT_OIL), reserves it
         * (structureCount++) and places a pitch rig at the cell's top-left tile.
         */
        void aiPlacePitchrig(int playerID);

        /**
         * AI iron mine placement: if resources allow and BuildingsState.unknownCountdown01 > 19, searches an iron
         * grid cell via findAppropriateGridLocationForResourceTypeBuilding(AIGCRT_IRON), reserves it
         * (structureCount++) and places an iron mine at the cell's top-left tile.
         */
        void aiPlaceIronMine(int playerID);

        /**
         * AI quarry placement: finds a boulder grid cell, reserves it and places a quarry there (nudged by one of 9
         * offsets); if that succeeded, BFS-searches a nearby free cell and tries the side offsets until an ox
         * tether is placed (returns if none fits), then links quarry slot 0 and the tether to each other.
         */
        void aiPlaceQuarryAndOxtether(int playerID);

        /**
         * Fallback building logic for AI lords without an AIV layout (aivSubType 0, called from
         * aiDecideOnNewBuildings). Sets per-lord quotas (stockpiles, hovels, granary, market, two barracks types,
         * workshops, chapels, inns, guilds, stables, cathedral) by aiType, then walks build steps
         * 0..min(currentStepGoal, 49): a disabled step is assigned the next building type whose quota is left (and
         * set unbuilt), every non-disabled step reduces its type's quota. The first step that is unbuilt or whose
         * building is gone and passes the checks (only hovels while param_2/isPausing, enemy not within 120 of the
         * lord, resources, unknownCountdown01 > 19, wood available for woodcutters, granary only when almost full,
         * AICState vetoes) is placed: stockpiles at fixed campground offsets chosen by the remaining stockpile
         * quota, barracks/guilds/cathedral via findAppropriateGridLocationForBuilding, others via
         * findSuitableGridLocationFittingCriteria from the campground cell. Returns TRUE once a building is placed;
         * a failed placement moves on to the next step.
         */
        BOOLEnum executeDefaultCastleAIV(PlayerID playerID, int isPausing);

        /**
         * Rebuilds the 80x80 AIV heat map (5x5 tiles per cell) in non-solitary games. initialize != 0: clears
         * everything, sets lowestTerrainHeight = 250 and the edge flag on all cells, clears the flag for cells
         * 1..78 that contain map tiles, computes the largest connected area, then scans all 0x13A10 tiles counting
         * tiles outside the largest area, min/max height of non-water tiles (terrainDiffHigherThan12), oil, marsh,
         * iron, boulders, structures, impassable tiles, oasis scrub and harvestable adult trees (+3 each, also
         * totalWoodAvailable). initialize == 0 (from the game tick when monthTicks == 10): zeroes
         * treeCount/structureCount/tileOwnership/impassableCount, decrements woodRelatedCountdownTo0 and
         * destructionBasedPlacementCooldown, then recounts impassable tiles, structures with their owner and trees.
         * Tile scans run only if a largest area exists.
         */
        void recomputeHeatmaps(int initialize);

        /**
         * Starting after a random castle slot ((rng & 7) + 1, wrapping 0-7), tries every available AIV castle for
         * the AI type: unpacks it, rotates to keepOrientation and computes the placement fit. A perfect fit
         * (999999) is chosen immediately (aivSubType 2); otherwise the castle with the highest positive fit is
         * chosen with aivSubType 1. The decompiler shows the AIV index as the uninitialised local '_tries' (really
         * a register parameter) and the best castle as unaff_EBP.
         */
        void selectBestAIVwithRandomStart(int playerID);

        /**
         * Unpacks and rotates a specific AIV castle for an AI and computes its fit; returns -3 if the AIV cannot be
         * loaded, -2 if fit < 1; otherwise stores castleID and returns 100 for a perfect fit (aivSubType 2), else
         * sets aivSubType 1 and returns the percentage of buildable tiles ((buildingCounter - invalidTileCounter) *
         * 100 / buildingCounter, 100 if the counter is 0). Castle ID and AIV index appear as unaff_EBX/unaff_EBP
         * (register params).
         */
        int tryPlaceAIVAndReturnFitPercentage(int playerID, int castleID);

        /**
         * Per-AI building decision tick (only for players with an AIV id > 0): honours resourceRebuildDelay and,
         * while gold <= 5000, the aivPoorCounter limit; then rotates aiResourceBuildingFocusIndicator 0..4 to try
         * one resource building (woodcutter, farm, quarry/ox tether, iron mine, pitch rig). AIV pauses: when the
         * next pause step is reached a pause starts and the function returns; during a pause only hovels may be
         * built and rich lords (gold > 16000) end it at once; otherwise currentStepGoal advances by 1 (2 when gold
         * > 16000). Then runs executeDefaultCastleAIV (aivSubType 0) or, unless destroyHouse acts, tries AIV build
         * steps 1..min(goal, totalSteps) until one is placed, and finally places flags and braziers. The playerID
         * parameter is reused as the step increment.
         */
        void aiDecideOnNewBuildings(PlayerID playerID);

        /**
         * AI/building part of the game tick (non-solitary modes). At start of day: advances
         * algBuildingPlacementNudge (0..30), resets AIVState.counter and, for each active player, sets the keep-
         * enclosure countdown to 5 while the keep is enclosed or decrements it otherwise; when it reaches 0 for an
         * enemy of the local player whose following field equals the local player slot, plays Genie_35.wav. Monthly
         * recomputes stocks, always updates AI behaviour; weekly updates path linkage and, for living AI players,
         * updates the heat map from building accessibility and removes units that cannot reach the keep. Calls
         * aiDecideOnNewBuildings + planToBuyWhenLowOnResourceAndSnoozeBuildings for the living AI whose index
         * equals dayTicks, applies snoozed states on dayTicks 8 and calls recomputeHeatmaps(0) when monthTicks ==
         * 10.
         */
        void updateBuildingsStateAndUpdateAIBuildingDecisions();
    };

    static_assert_cpp98_obj(sizeof(AIVState) == 748656, AIVState);

#pragma pack(pop)

} // namespace AI
} // namespace OpenSHC
