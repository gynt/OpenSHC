#include "../PathFindingState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00498FD0
        uint PathFindingState::commitUnitPathPlanUsingWalkLayer(uint param_1, int param_2, int param_3)
        {
            int x = this->unitX;
            int y = this->unitY;
            int descending = 0;
            if ((uint)x > 399 || (uint)y > 399
                || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] == '\0') {
                return 0;
            }
            int tile = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
            if (DAT_TileMapState::instance.PathConnectionLayer[tile] == 0) {
                return 0;
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::findPathWithBudget,
                DAT_PathFindingState::ptr)(x, y, -1, -1,
                param_1 == 0       ? 80
                    : param_1 == 1 ? 200
                    : param_1 == 2 ? 500
                    : param_1 == 3 ? 1000
                                   : 2000,
                0);
            int generation = DAT_TileMapState::instance.SearchGenerationLayer[tile];
            int rng = SEC_RNG::instance.currentNumber2;
            this->searchQueue.pathPlanIndex = 0;
            int lastDirection = 10;
            int distance = 1;
            for (;;) {
                if (descending != 0 && distance <= 1) {
                    break;
                }
                int threshold = distance;
                int bestScore = distance;
                int bestDirection = 8;
                for (int direction = 0; direction < 8; direction++) {
                    int candidate = DAT_TileMapState::instance.directionTranslationMatrix[y][direction] + tile;
                    if (DAT_TileMapState::instance.SearchGenerationLayer[candidate] != generation)
                        continue;
                    int candidateDistance = DAT_TileMapState::instance.SearchDistanceLayer[candidate];
                    if (descending == 0) {
                        if ((candidateDistance & 0x8000) != 0)
                            continue;
                        candidateDistance = candidateDistance & 0x3fff;
                        if (candidateDistance < threshold)
                            continue;
                        if (param_3 != 0 && candidateDistance == threshold)
                            continue;
                        int score = ((DAT_TileMapState::instance.RandomLayer[candidate] ^ rng) & 7) + candidateDistance;
                        int weighted = score;
                        if (direction == lastDirection) {
                            weighted = score + 1;
                        }
                        if (weighted > bestScore) {
                            distance = candidateDistance;
                            bestScore = score;
                            bestDirection = direction;
                        }
                    } else if (descending == 1) {
                        if ((candidateDistance & 0x4000) != 0)
                            continue;
                        candidateDistance = candidateDistance & 0x3fff;
                        if (candidateDistance > threshold)
                            continue;
                        if (param_3 != 0 && candidateDistance == threshold)
                            continue;
                        int score = candidateDistance - ((DAT_TileMapState::instance.RandomLayer[candidate] ^ rng) & 7);
                        int weighted = score;
                        if (direction == lastDirection) {
                            weighted = score - 1;
                        }
                        if (weighted < bestScore) {
                            distance = candidateDistance;
                            bestScore = score;
                            bestDirection = direction;
                        }
                    } else {
                        continue;
                    }
                    rng = ((rng >> 1) & 0x7fff) | ((rng & 1) << 15);
                }
                if (descending == 0) {
                    DAT_TileMapState::instance.SearchDistanceLayer[tile] |= 0x8000;
                } else {
                    DAT_TileMapState::instance.SearchDistanceLayer[tile] |= 0x4000;
                }
                if (bestDirection == 8) {
                    if (param_2 == 0 || descending != 0) {
                        break;
                    }
                    descending = 1;
                    continue;
                }
                tile = tile + DAT_TileMapState::instance.directionTranslationMatrix[y][bestDirection];
                y = y + DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[bestDirection].int_.yOffset;
                lastDirection = bestDirection;
                if ((this->searchQueue.pathPlanIndex & 1) == 0) {
                    this->searchQueue.ptrPathPlan[(int)this->searchQueue.pathPlanIndex / 2] = (byte)bestDirection;
                } else {
                    this->searchQueue.ptrPathPlan[(int)this->searchQueue.pathPlanIndex / 2]
                        = this->searchQueue.ptrPathPlan[(int)this->searchQueue.pathPlanIndex / 2] & 0xf;
                    this->searchQueue.ptrPathPlan[(int)this->searchQueue.pathPlanIndex / 2]
                        = this->searchQueue.ptrPathPlan[(int)this->searchQueue.pathPlanIndex / 2]
                        + (byte)bestDirection * '\x10';
                }
                this->searchQueue.pathPlanIndex = this->searchQueue.pathPlanIndex + 1;
                if ((int)this->searchQueue.pathPlanIndex >= 800) {
                    break;
                }
            }
            return (uint)(this->searchQueue.pathPlanIndex);
        }

    }
}
}
