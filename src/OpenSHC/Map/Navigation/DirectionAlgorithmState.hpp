/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Navigation/DirectionAlgorithmState.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Navigation {

#pragma pack(push, 1)

        // SIZE: 0x00000014
        class DirectionAlgorithmState {
        public:
            int distanceX; // 0x00000000 length: 4
            int distanceY; // 0x00000004 length: 4
            int distanceLow; // 0x00000008 length: 4
            int distanceHigh; // 0x0000000C length: 4
            int orientation; // 0x00000010 length: 4

        private:
            DirectionAlgorithmState(DirectionAlgorithmState const&);
            void operator=(DirectionAlgorithmState const&);

        public:
            DirectionAlgorithmState() {};
            ~DirectionAlgorithmState() {};

            /**
             * Returns health*100/maxHealth, or 100 if maxHealth is 0. (Generic percentage helper placed in
             * DirectionAlgorithmState; used for unit/building health.)
             */
            int computeHealthPercentage(int health, int maxHealth);

            /**
             * Computes the 8-way direction from current to destination position and stores it in
             * DAT_DirectionAlgorithmState.orientation: 0=north (y decreasing), clockwise 1..7 (2=east, 4=south,
             * 6=west), 15 if both positions are equal.
             */
            void calculateOrientation(
                int currentXPosition, int currentYPosition, int destinationXPosition, int destinationYPosition);

            /**
             * Converts two tile indices to (x,y) using the viewport translation tables and calls
             * calculateOrientation from the first to the second; result in DAT_DirectionAlgorithmState.orientation.
             */
            void calculateOrientationFromTiles(int fromTile, int toTile);

            /**
             * Computes an 8-way direction (0=north, clockwise) from (fromX,fromY) to (toX,toY) with wider axis
             * cones: a pure axis direction is chosen when one delta exceeds twice the other, otherwise a diagonal;
             * 15 when the points coincide. Stores |dx|,|dy| and orientation in DAT_DirectionAlgorithmState.
             */
            void calculatePreferredRelativeOrientation(int fromX, int fromY, int toX, int toY);

            /**
             * NAME? Computes a 16-way projectile facing from (x,y) to (target): uses the minor/major axis ratio in
             * percent (<26 axis, <75 intermediate, else diagonal) to pick an orientation code 0x3C..0x4B, or 0x4C
             * when the points coincide; stores |dx|,|dy| and orientation in DAT_DirectionAlgorithmState. Better
             * name: calculateProjectileOrientation16.
             */
            void somethingWithProjectileDistance(int x, int y, int targetX, int targetY);

            /**
             * Stores |dx| and |dy| between the two points into DAT_DirectionAlgorithmState.distanceX/Y, the smaller
             * into distanceLow and the larger into distanceHigh, and returns the Manhattan distance dx+dy.
             */
            int setAxisBasedDistanceResult(
                int destinationXPosition, int destinationYPosition, int fromXPosition, int fromYPosition);

            /**
             * For a right-drag camera scroll in axis direction orientation (0,2,4,6) returns how far the mouse
             * moved from the stored screen position along that direction, or 0 if it moved the other way or
             * orientation is diagonal.
             */
            int getMouseVectorLengthBasedOnDirection(
                int storedScreenSpaceX, int storedScreenSpaceY, int screenSpaceX, int screenSpaceY, int orientation);

            /**
             * Synchrony checksum over byteCount bytes of int words: hash = rotl1(hash + word) for each word
             * (16-word unrolled loop then remainder). Used to compare unit arrays for multiplayer resync.
             */
            uint computeHash(int byteCount, int* address);

            /**
             * Masked variant of computeHash: for each 32-bit word of the buffer (byteCount/4 words) hash =
             * rotl1(hash + (word & mask)); returns the hash. Used by recomputeHashesAndSendResync.
             */
            uint computeMaskedBitAccumulator(int byteCount, uint* address, uint mask);

            /**
             * Rotates an 8-bit value left by bits (1..7); other values return it unchanged.
             */
            byte rotateByteLeft(byte value, int bits);
        };

        static_assert_cpp98_obj(sizeof(DirectionAlgorithmState) == 20, DirectionAlgorithmState);

#pragma pack(pop)

    } // namespace Navigation
} // namespace Map
} // namespace OpenSHC
