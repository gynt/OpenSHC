#include "../EntityState.func.hpp"

#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x00402E20
        uint EntityState::computeLineOfSightDistance(
            int x, int y, int height, int targetX, int targetY, int targetHeight, int skipObstacleChecks)
        {
            int prevTile = -1;
            int startBuildingID = -1;
            int clearance = 0;
            int stepCount = 100000;
            int obstacleHeight = 0;
            int checksToSkip = 0;
            int stillOnStartStructure = 1;
            int obstacleHeightValid = 0;
            int tile;
            if (height > targetHeight + 54) {
                clearance = 100;
                checksToSkip = 100;
            }
            int tileY = y / 8;
            int tileX = x / 8;
            tile = DAT_ViewportRenderState::instance.translationMatrix[tileY].addXgetTile + tileX;
            int curX = x;
            int curY = y;
            if ((DAT_TileMapState::instance.LogicLayer[tile] & 0x10000000) != 0) {
                height += 10;
            }
            if (DAT_TileMapState::instance.BuildingLayer[tile] != 0) {
                startBuildingID = DAT_TileMapState::instance.BuildingLayer[tile];
            }
            int absDy = y > targetY ? y - targetY : targetY - y;
            int absDx = x > targetX ? x - targetX : targetX - x;
            int stepX = x <= targetX ? 1 : -1;
            int stepY = y <= targetY ? 1 : -1;

            int incMinor;
            int incMajor;
            int error;
            if (absDx == 0) {
                if (absDy != 0) {
                    // vertical line
                    if (clearance >= 28) {
                        clearance = 28;
                    }
                    this->lineOfSightClearanceSteps = clearance;
                    checksToSkip = clearance / 2;
                    stepCount = 0;
                    do {
                        curY += stepY;
                        if ((stepCount & 1) != 0 && skipObstacleChecks == 0) {
                            tile = DAT_ViewportRenderState::instance.translationMatrix[curY / 8].addXgetTile + tileX;
                            if ((DAT_TileMapState::instance.LogicLayer[tile] & 0x400300) == 0) {
                                stillOnStartStructure = 0;
                                this->lineOfSightClearanceSteps = stepCount;
                            }
                            if (checksToSkip != 0) {
                                checksToSkip--;
                            }
                            else if (prevTile == tile) {
                                if (obstacleHeightValid
                                    && abs(curY - y) * (targetHeight - height) / absDy + height < obstacleHeight) {
                                    return 0;
                                }
                            }
                            else {
                                obstacleHeightValid = 0;
                                if ((char)DAT_TileMapState::instance.LogicLayer[tile] < 0
                                    || (startBuildingID != DAT_TileMapState::instance.BuildingLayer[tile]
                                        && (!stillOnStartStructure
                                            || (DAT_TileMapState::instance.LogicLayer[tile] & 0x400200) == 0))) {
                                    obstacleHeightValid = 1;
                                    obstacleHeight = MACRO_CALL_MEMBER(
                                        OpenSHC::Map::TileMapState_Func::getObstacleTopHeightAtTile, DAT_TileMapState::ptr)(
                                        tile, 1);
                                    if (abs(curY - y) * (targetHeight - height) / absDy + height < obstacleHeight) {
                                        return 0;
                                    }
                                }
                            }
                            prevTile = tile;
                        }
                        if (curX == targetX && curY == targetY) {
                            break;
                        }
                        stepCount++;
                    } while (stepCount < 1000);
                }
            }
            else if (absDy == 0) {
                // horizontal line
                if (clearance >= 28) {
                    clearance = 28;
                }
                this->lineOfSightClearanceSteps = clearance;
                checksToSkip = clearance / 2;
                stepCount = 0;
                do {
                    curX += stepX;
                    if ((stepCount & 1) != 0 && skipObstacleChecks == 0) {
                        tile = DAT_ViewportRenderState::instance.translationMatrix[tileY].addXgetTile + curX / 8;
                        if ((DAT_TileMapState::instance.LogicLayer[tile] & 0x400300) == 0) {
                            stillOnStartStructure = 0;
                            this->lineOfSightClearanceSteps = stepCount;
                        }
                        if (checksToSkip != 0) {
                            checksToSkip--;
                        }
                        else if (prevTile == tile) {
                            if (obstacleHeightValid
                                && abs(curX - x) * (targetHeight - height) / absDx + height < obstacleHeight) {
                                return 0;
                            }
                        }
                        else {
                            obstacleHeightValid = 0;
                            if ((char)DAT_TileMapState::instance.LogicLayer[tile] < 0
                                || (startBuildingID != DAT_TileMapState::instance.BuildingLayer[tile]
                                    && (!stillOnStartStructure
                                        || (DAT_TileMapState::instance.LogicLayer[tile] & 0x400200) == 0))) {
                                obstacleHeightValid = 1;
                                obstacleHeight = MACRO_CALL_MEMBER(
                                    OpenSHC::Map::TileMapState_Func::getObstacleTopHeightAtTile, DAT_TileMapState::ptr)(
                                    tile, 1);
                                if (abs(curX - x) * (targetHeight - height) / absDx + height < obstacleHeight) {
                                    return 0;
                                }
                            }
                        }
                        prevTile = tile;
                    }
                    if (curX == targetX && curY == targetY) {
                        break;
                    }
                    stepCount++;
                } while (stepCount < 1000);
            }
            else if (absDy > absDx) {
                // y-major line
                incMinor = absDx * 2;
                error = incMinor - absDy;
                incMajor = incMinor - absDy * 2;
                if (height > targetHeight && checksToSkip != 0) {
                    int probeCount = abs(targetY - y) / 8 - 1;
                    if (probeCount > 4) {
                        probeCount = 4;
                    }
                    for (int i = 1; i < probeCount; i++) {
                        obstacleHeight = MACRO_CALL_MEMBER(
                            OpenSHC::Map::TileMapState_Func::getObstacleTopHeightAtTile, DAT_TileMapState::ptr)(
                            DAT_ViewportRenderState::instance.translationMatrix[targetY / 8 - i * stepY].addXgetTile
                                + targetX / 8,
                            1);
                        if (obstacleHeight > targetHeight) {
                            checksToSkip = 28;
                        }
                    }
                }
                this->lineOfSightClearanceSteps = checksToSkip;
                checksToSkip = checksToSkip / 2;
                stepCount = 0;
                do {
                    curY += stepY;
                    if (error > 0) {
                        curX += stepX;
                        error += incMajor;
                    }
                    else {
                        error += incMinor;
                    }
                    if ((stepCount & 1) != 0 && skipObstacleChecks == 0) {
                        tile = DAT_ViewportRenderState::instance.translationMatrix[curY / 8].addXgetTile + curX / 8;
                        if ((DAT_TileMapState::instance.LogicLayer[tile] & 0x400300) == 0) {
                            stillOnStartStructure = 0;
                            this->lineOfSightClearanceSteps = stepCount;
                        }
                        if (checksToSkip != 0) {
                            checksToSkip--;
                        }
                        else if (prevTile == tile) {
                            if (obstacleHeightValid
                                && abs(curY - y) * (targetHeight - height) / absDy + height < obstacleHeight) {
                                return 0;
                            }
                        }
                        else {
                            obstacleHeightValid = 0;
                            if ((char)DAT_TileMapState::instance.LogicLayer[tile] < 0
                                || (startBuildingID != DAT_TileMapState::instance.BuildingLayer[tile]
                                    && (!stillOnStartStructure
                                        || (DAT_TileMapState::instance.LogicLayer[tile] & 0x400200) == 0))) {
                                obstacleHeightValid = 1;
                                obstacleHeight = MACRO_CALL_MEMBER(
                                    OpenSHC::Map::TileMapState_Func::getObstacleTopHeightAtTile, DAT_TileMapState::ptr)(
                                    tile, 1);
                                if (abs(curY - y) * (targetHeight - height) / absDy + height < obstacleHeight) {
                                    return 0;
                                }
                            }
                        }
                        prevTile = tile;
                    }
                    if (curX == targetX && curY == targetY) {
                        break;
                    }
                    stepCount++;
                } while (stepCount < 1000);
            }
            else {
                // x-major line
                incMinor = absDy * 2;
                incMajor = incMinor - absDx * 2;
                error = incMinor - absDx;
                if (height > targetHeight && clearance != 0) {
                    int probeCount = abs(targetX - x) / 8 - 1;
                    if (probeCount > 4) {
                        probeCount = 4;
                    }
                    for (int i = 1; i < probeCount; i++) {
                        obstacleHeight = MACRO_CALL_MEMBER(
                            OpenSHC::Map::TileMapState_Func::getObstacleTopHeightAtTile, DAT_TileMapState::ptr)(
                            targetX / 8 - i * stepX
                                + DAT_ViewportRenderState::instance.translationMatrix[targetY / 8].addXgetTile,
                            1);
                        if (obstacleHeight > targetHeight) {
                            clearance = 28;
                        }
                    }
                }
                this->lineOfSightClearanceSteps = clearance;
                checksToSkip = clearance / 2;
                stepCount = 0;
                do {
                    curX += stepX;
                    if (error > 0) {
                        curY += stepY;
                        error += incMajor;
                    }
                    else {
                        error += incMinor;
                    }
                    if ((stepCount & 1) != 0 && skipObstacleChecks == 0) {
                        tile = DAT_ViewportRenderState::instance.translationMatrix[curY / 8].addXgetTile + curX / 8;
                        if ((DAT_TileMapState::instance.LogicLayer[tile] & 0x400300) == 0) {
                            stillOnStartStructure = 0;
                            this->lineOfSightClearanceSteps = stepCount;
                        }
                        if (checksToSkip != 0) {
                            checksToSkip--;
                        }
                        else if (prevTile == tile) {
                            if (obstacleHeightValid
                                && abs(curX - x) * (targetHeight - height) / absDx + height < obstacleHeight) {
                                return 0;
                            }
                        }
                        else {
                            obstacleHeightValid = 0;
                            if ((char)DAT_TileMapState::instance.LogicLayer[tile] < 0
                                || (startBuildingID != DAT_TileMapState::instance.BuildingLayer[tile]
                                    && (!stillOnStartStructure
                                        || (DAT_TileMapState::instance.LogicLayer[tile] & 0x400200) == 0))) {
                                obstacleHeightValid = 1;
                                obstacleHeight = MACRO_CALL_MEMBER(
                                    OpenSHC::Map::TileMapState_Func::getObstacleTopHeightAtTile, DAT_TileMapState::ptr)(
                                    tile, 1);
                                if (abs(curX - x) * (targetHeight - height) / absDx + height < obstacleHeight) {
                                    return 0;
                                }
                            }
                        }
                        prevTile = tile;
                    }
                    if (curX == targetX && curY == targetY) {
                        break;
                    }
                    stepCount++;
                } while (stepCount < 1000);
            }
            return stepCount;
        }

    }
}
}
