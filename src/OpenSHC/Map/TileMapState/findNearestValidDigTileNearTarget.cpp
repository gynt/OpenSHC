#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00500980
    undefined4 TileMapState::findApproachTileNextToTarget(uint x1, uint y1, uint x2, uint y2)
    {
        if (x1 > 399 || y1 > 399) {
            return 0;
        }
        if (DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y1 * 400 + x1] == 0) {
            return 0;
        }
        if (x2 <= 399 && y2 <= 399 && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y2 * 400 + x2] != 0) {
            int area = (short)this->PathConnectionLayer[DAT_ViewportRenderState::instance.translationMatrix[y1].addXgetTile + x1];
            int targetTile = DAT_ViewportRenderState::instance.translationMatrix[y2].addXgetTile + x2;
            int bestDistance = 10000;
            int bestIndex = -1;
            int targetHeight = this->HeightLayer[targetTile];
            int targetBuildingID = this->BuildingLayer[targetTile];
            if (targetBuildingID != 0) {
                targetHeight = targetHeight
                    + MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                        DAT_BuildingsState::ptr)(targetBuildingID);
            }

            for (int index = 0; index < 4; index++) {
                int fromXPosition = DAT_TerrainDefinedData::instance.approachOffsetsDist2[index].x + x2;
                int fromYPosition = DAT_TerrainDefinedData::instance.approachOffsetsDist2[index].y + y2;
                int tile = DAT_ViewportRenderState::instance.translationMatrix[fromYPosition].addXgetTile + fromXPosition;
                if ((short)this->PathConnectionLayer[tile] != area) {
                    continue;
                }
                int height = this->HeightLayer[tile];
                int buildingID = this->BuildingLayer[tile];
                if (buildingID != 0) {
                    height = height
                        + MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                            DAT_BuildingsState::ptr)(buildingID);
                }
                if (height >= targetHeight + 0x10 || height <= targetHeight - 0x10) {
                    continue;
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                    DAT_DirectionAlgorithmState::ptr)(x1, y1, fromXPosition, fromYPosition);
                if (DAT_DirectionAlgorithmState::instance.distanceHigh < bestDistance) {
                    bestDistance = DAT_DirectionAlgorithmState::instance.distanceHigh;
                    bestIndex = index;
                }
            }

            if (bestIndex <= -1) {
                this->approachTileX = x2;
                this->approachTileY = y2;
            } else {
                this->approachTileX = DAT_TerrainDefinedData::instance.approachOffsetsDist2[bestIndex].x + x2;
                this->approachTileY = DAT_TerrainDefinedData::instance.approachOffsetsDist2[bestIndex].y + y2;
                return 1;
            }
        }
        return 0;
    }

}
}