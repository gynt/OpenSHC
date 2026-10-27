/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/WallAndPitchState.hpp'
*/

#pragma once

#include "OpenSHC/Map/Walls/WallPlacementInfoElementStruct.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Walls::WallPlacementInfoElementStruct;

#pragma pack(push, 1)

    // SIZE: 0x00000980
    class WallAndPitchState {
    public:
        int countdown; // 0x00000000 length: 4
        int state; // 0x00000004 length: 4
        int id; // 0x00000008 length: 4
        int uid; // 0x0000000C length: 4
        int index; // 0x00000010 length: 4
        int counter; // 0x00000014 length: 4
        int flag; // 0x00000018 length: 4
        WallPlacementInfoElementStruct wallPlacementInfoArray[100]; // 0x0000001C length: 1200
        WallPlacementInfoElementStruct receivedWallPlacementInfoArray[100]; // 0x000004CC length: 1200
        int unused; // 0x0000097C length: 4

    private:
        WallAndPitchState(WallAndPitchState const&);
        void operator=(WallAndPitchState const&);

    public:
        WallAndPitchState() {};
        ~WallAndPitchState() {};

        /**
         * NAME? Called from placeBuilding: opens the 400-tick undo-last-placement window (disabled when gameMode_2
         * is skirmish/multiplayer or Siege That): records the building (id, uid, state 0) in DAT_WallAndPitchState
         * and refreshes the menu; keeps (types 0x28..0x2C) instead close the window (countdown 0).
         * confirmAndQueueDestructionCommand later issues GCT_DESTROY_BUILDING while the window is open and the
         * building is undamaged and empty.
         */
        void startBuildingPlacementUndoWindow(int buildingID);

        /**
         * Called when a pitch-ditch placement command starts: outside skirmish/multiplayer and Siege That modes
         * opens a 400-tick undo window of state 4 (pitch-ditch batch), clears index/counter and refreshes the menu.
         */
        void resetWallAndPitchState();

        /**
         * NAME? Called from CommandSpawnEntity: outside skirmish/multiplayer and Siege That modes opens the
         * 400-tick undo window for the spawned entity (id, uid, state 1) and refreshes the menu.
         */
        void startEntityPlacementUndoWindow(int entityID);

        /**
         * NAME? Called from ClickPlaceSiegeTent: outside skirmish/multiplayer and Siege That modes opens the
         * 400-tick undo window for the placed unit (id, uid, state 2) and refreshes the menu.
         */
        void startUnitPlacementUndoWindow(int unitID);

        /**
         * Called from placeWalls: outside skirmish/multiplayer and Siege That modes opens a 400-tick undo window of
         * state 3 (wall batch), clears index/counter and refreshes the menu.
         */
        void resetWallPlacementInfo();

        /**
         * Called from placeWalls: outside skirmish/multiplayer and Siege That modes appends (tile, height, logic &
         * 0x470B00, damage) of the given tile to wallPlacementInfoArray (max 100 entries) so destroyWall can
         * restore the tile on undo.
         */
        void addWallPlacementInfoForTile(int tile);

        /**
         * NAME? Undo bookkeeping for pitch placement (called from placeBuilding), does not place anything: outside
         * skirmish/multiplayer and Siege That modes, starts a fresh 400-tick undo record if none is active, then
         * appends the pitch-ditch ID to wallPlacementInfoArray (max 100), increments index and counter and
         * refreshes the 400-tick countdown.
         */
        void recordPitchDitchForUndo(int pitchID);

        /**
         * Executes the undo of a wall placement (from the DestroyWallOrPitch command): refunds `amount` stone (wood
         * when the 4th arg is nonzero) to playerID, then for `count` received wall-placement records restores the
         * tile's damage and height, clears logic bits 0x470B00 and ORs back the saved logic bits, updates path
         * linkages and the walk/path layer (x = tile - row start), and finally redraws the minimap.
         */
        void destroyWall(int playerID, int count, int amount, int isWoodenWall);

        /**
         * Executes the undo of a pitch-ditch placement (from the DestroyWallOrPitch command): refunds amount/4
         * pitch to playerID, destroys each of the `count` pitch ditches listed in receivedWallPlacementInfoArray
         * and redraws the minimap. The 4th stack argument is never read.
         */
        void destroyPitch(int playerID, int count, int amount, int unusedFlag);

        /**
         * Per-tick update of the undo-last-placement window: forced to 0 in skirmish/multiplayer and Siege That
         * modes; otherwise decrements the countdown and cancels it (countdown=0, refresh menu) if the recorded
         * object changed: building replaced, damaged or holding any resource (state 0); unit replaced, damaged or
         * with nonzero digTileX/manning count (state 2); no wall records, or a wall tile lost logic 0x100 or got
         * damage (state 3); a pitch ditch ID is 0 or its tile lost logic 8 (state 4). State 1 (entity) is not
         * validated.
         */
        void updatePlacementUndoCountdown();

        /**
         * Undo button handler: if the window is open, re-validates the record via
         * updateDestructionConfirmationCountdown (countdown+1 first so no tick is consumed) and, if still valid,
         * queues the matching command: GCT_DESTROY_BUILDING (29) with id, uid and 100; command 75 (handler
         * RemoveTowerSiegeEngine) with type 1/2 and the entity/unit id; or command 76 (DestroyWallOrPitch) with
         * index, counter, flag and type 3/4. Then clears the countdown and refreshes the menu.
         */
        void confirmAndQueueDestructionCommand();
    };

    static_assert_cpp98_obj(sizeof(WallAndPitchState) == 2432, WallAndPitchState);

#pragma pack(pop)

} // namespace Map
} // namespace OpenSHC
