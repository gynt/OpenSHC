/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Navigation.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        /**
         * Fast integer approximation of Euclidean distance between (x1,y1) and (x2,y2): max(dx,dy) +
         * (2*min/5)*min/max. Returns 0 when both deltas are zero.
         */
        int __cdecl calcApproxEuclideanDistance(int x1, int x2, int y1, int y2);

        /**
         * Per-type climbData updater for type 1 (ladder placed by a ladderman unit), dispatched by table for
         * DAT_CurrentClimbDataID. If the source unit still has the same UID, generic state 3 and is not dying,
         * marks the entry recognized by pathfinding, takes the unit's facing as ladder direction, computes top
         * position/tile = bottom + direction offset and the path-connection areas of bottom and top; otherwise
         * marks the climb data unusable.
         */
        void __cdecl UpdateClimbDataState01();

        /**
         * Per-type climbData updater (type 3) for a building-based passage: links the building to the climb data,
         * invalidates it on building UID mismatch, copies owner, sets pathfinding recognition unless
         * pathLinkageRelated2==2. For direction 2/0 places bottom at (x+7,y+3)/(x+3,y+7) and top one tile outside
         * the opposite edge (x-1 / y-1) - a 7-tile footprint (likely large gatehouse) - then computes tiles and
         * path-connection areas of bottom, top and building interior (x+1,y+1).
         */
        void __cdecl UpdateClimbDataState03();

        /**
         * Per-type climbData updater (type 4); same as type 3 but for a 5-tile footprint: bottom at
         * (x+5,y+2)/(x+2,y+5) depending on direction 2/0, top one tile outside the opposite edge. Updates tiles,
         * owner, pathfinding flag and bottom/top/building path-connection areas.
         */
        void __cdecl UpdateClimbDataState04();

        /**
         * Per-type climbData updater (type 5); same as types 3/4 but for a 3-tile footprint: bottom at
         * (x+3,y+1)/(x+1,y+3) depending on direction 2/0, top one tile outside the opposite edge. Updates tiles,
         * owner, pathfinding flag and bottom/top/building path-connection areas.
         */
        void __cdecl UpdateClimbDataState05();

        /**
         * Per-type climbData updater (type 7): invalidates the entry if the source building's UID changed, marks it
         * recognized by pathfinding, sets the top point two tiles north of the bottom (same x, y-2), recomputes the
         * top tile and the path-connection areas of bottom and top; buildingArea = -1.
         */
        void __cdecl updateClimbDataType07BuildingLink();

        /**
         * Called when a ladderman reaches position: sets bit 0x800000 in the LogicLayer of the unit's tile, creates
         * a type-1 climbData entry for the unit and sets its laddermanIsInPosition flag.
         */
        void __cdecl UpdateLadderman_SetClimbData(int unitID);

    } // namespace Navigation
} // namespace Map
} // namespace OpenSHC
