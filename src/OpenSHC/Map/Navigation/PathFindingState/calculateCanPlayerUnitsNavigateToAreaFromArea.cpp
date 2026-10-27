#include "../PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        /*
          maybe fromArea is the third argument, and toArea is the second?   decompilerscript: committed: 2025-01-30
          21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A5320
        int PathFindingState::calculateCanPlayerUnitsNavigateToAreaFromArea(
            int playerID, dword fromArea, dword toArea, int permitClimb)
        {
            int count;
            int readIndex;
            dword areaQueue[200];
            int candidates[400]; // pairs of { climb data index, already expanded }
            if (fromArea == toArea) {
                return (int)(fromArea);
            }
            if (toArea == 0 || fromArea == 0) {
                return 0;
            }
            int i = 1;
            this->areaRouteSearchCount = this->areaRouteSearchCount + 1;
            count = 0;
            readIndex = 0;
            for (; i < this->maxClimbDataCount; i++) {
                if (this->climbData[i].canBeUsed == 1 && this->climbData[i].isRecognizedByPathfinding != 0) {
                    if (!(this->climbData[i].type == 1 ? permitClimb == 0 : permitClimb == 2)
                        && (playerID == 0
                            || DAT_GameState::instance.mapAndTime.playerTeams[this->climbData[i].owner]
                                == DAT_GameState::instance.mapAndTime.playerTeams[playerID]
                            || DAT_BuildingsState::instance.buildings[this->climbData[i].buildingID].capturedByPlayerID
                                != 0)) {
                        candidates[count * 2 + 1] = 0;
                        candidates[count * 2] = i;
                        count = count + 1;
                    }
                }
            }
            int queued = 0;
            /*
              first pass: no ladders
             */
            this->areaSearchLadderPass = 0;
            if (0 < count) {
                for (int k = 0; k < count; k++) {
                    if (this->climbData[candidates[k * 2]].type == 1)
                        continue;
                    ClimbData* climb = &this->climbData[candidates[k * 2]];
                    dword area = climb->area;
                    if (area == toArea) {
                        dword top = climb->topArea;
                        if (top == fromArea) {
                            return (int)(toArea);
                        }
                        dword building = climb->buildingArea;
                        if (building == fromArea) {
                            return (int)(toArea);
                        }
                        areaQueue[queued] = top;
                        queued = queued + 1;
                        candidates[k * 2 + 1] = 1;
                        if (0 < (int)building) {
                            areaQueue[queued] = building;
                            queued = queued + 1;
                        }
                    } else {
                        dword top = climb->topArea;
                        if (top == toArea) {
                            if (area == fromArea) {
                                return (int)(toArea);
                            }
                            dword building = climb->buildingArea;
                            if (building == fromArea) {
                                return (int)(toArea);
                            }
                            areaQueue[queued] = area;
                            queued = queued + 1;
                            candidates[k * 2 + 1] = 1;
                            if (0 < (int)building) {
                                areaQueue[queued] = building;
                                queued = queued + 1;
                            }
                        } else if (climb->buildingArea == toArea) {
                            if (area == fromArea) {
                                return (int)(toArea);
                            }
                            if (top == fromArea) {
                                return (int)(toArea);
                            }
                            areaQueue[queued] = area;
                            queued = queued + 1;
                            candidates[k * 2 + 1] = 1;
                            areaQueue[queued] = top;
                            queued = queued + 1;
                        }
                    }
                }
                if (0 < queued) {
                    do {
                        dword current = areaQueue[readIndex];
                        readIndex = readIndex + 1;
                        for (int k = 0; k < count; k++) {
                            if (candidates[k * 2 + 1] == 1)
                                continue;
                            if (this->climbData[candidates[k * 2]].type == 1)
                                continue;
                            ClimbData* climb = &this->climbData[candidates[k * 2]];
                            dword area = climb->area;
                            if (area == current) {
                                dword top = climb->topArea;
                                if (top == fromArea) {
                                    return (int)(current);
                                }
                                dword building = climb->buildingArea;
                                if (building == fromArea) {
                                    return (int)(current);
                                }
                                areaQueue[queued] = top;
                                queued = queued + 1;
                                candidates[k * 2 + 1] = 1;
                                if (0 < (int)building) {
                                    areaQueue[queued] = building;
                                    queued = queued + 1;
                                }
                            } else {
                                dword top = climb->topArea;
                                if (top == current) {
                                    if (area == fromArea) {
                                        return (int)(current);
                                    }
                                    dword building = climb->buildingArea;
                                    if (building == fromArea) {
                                        return (int)(current);
                                    }
                                    areaQueue[queued] = area;
                                    queued = queued + 1;
                                    candidates[k * 2 + 1] = 1;
                                    if (0 < (int)building) {
                                        areaQueue[queued] = building;
                                        queued = queued + 1;
                                    }
                                } else if (climb->buildingArea == current) {
                                    if (area == fromArea) {
                                        return (int)(current);
                                    }
                                    if (top == fromArea) {
                                        return (int)(current);
                                    }
                                    areaQueue[queued] = area;
                                    queued = queued + 1;
                                    candidates[k * 2 + 1] = 1;
                                    areaQueue[queued] = top;
                                    queued = queued + 1;
                                }
                            }
                        }
                    } while (readIndex < queued);
                }
            }
            /*
              second pass: ladders allowed
             */
            this->areaSearchLadderPass = 1;
            DAT_PathFindingState::instance.areaRouteNeedsLadders = 1;
            for (int k = 0; k < count; k++) {
                candidates[k * 2 + 1] = 0;
                ClimbData* climb = &this->climbData[candidates[k * 2]];
                dword area = climb->area;
                if (area == toArea) {
                    dword top = climb->topArea;
                    if (top == fromArea) {
                        return (int)(toArea);
                    }
                    dword building = climb->buildingArea;
                    if (building == fromArea) {
                        return (int)(toArea);
                    }
                    areaQueue[queued] = top;
                    queued = queued + 1;
                    candidates[k * 2 + 1] = 1;
                    if (0 < (int)building) {
                        areaQueue[queued] = building;
                        queued = queued + 1;
                    }
                } else {
                    dword top = climb->topArea;
                    if (top == toArea) {
                        if (area == fromArea) {
                            return (int)(toArea);
                        }
                        dword building = climb->buildingArea;
                        if (building == fromArea) {
                            return (int)(toArea);
                        }
                        areaQueue[queued] = area;
                        queued = queued + 1;
                        candidates[k * 2 + 1] = 1;
                        if (0 < (int)building) {
                            areaQueue[queued] = building;
                            queued = queued + 1;
                        }
                    } else if (climb->buildingArea == toArea) {
                        if (area == fromArea) {
                            return (int)(toArea);
                        }
                        if (top == fromArea) {
                            return (int)(toArea);
                        }
                        areaQueue[queued] = area;
                        queued = queued + 1;
                        candidates[k * 2 + 1] = 1;
                        areaQueue[queued] = top;
                        queued = queued + 1;
                    }
                }
            }
            if (readIndex < queued) {
                do {
                    dword current = areaQueue[readIndex];
                    readIndex = readIndex + 1;
                    for (int k = 0; k < count; k++) {
                        if (candidates[k * 2 + 1] == 1)
                            continue;
                        ClimbData* climb = &this->climbData[candidates[k * 2]];
                        dword area = climb->area;
                        if (area == current) {
                            dword top = climb->topArea;
                            if (top == fromArea) {
                                return (int)(current);
                            }
                            dword building = climb->buildingArea;
                            if (building == fromArea) {
                                return (int)(current);
                            }
                            areaQueue[queued] = top;
                            queued = queued + 1;
                            candidates[k * 2 + 1] = 1;
                            if (0 < (int)building) {
                                areaQueue[queued] = building;
                                queued = queued + 1;
                            }
                        } else {
                            dword top = climb->topArea;
                            if (top == current) {
                                if (area == fromArea) {
                                    return (int)(current);
                                }
                                dword building = climb->buildingArea;
                                if (building == fromArea) {
                                    return (int)(current);
                                }
                                areaQueue[queued] = area;
                                queued = queued + 1;
                                candidates[k * 2 + 1] = 1;
                                if (0 < (int)building) {
                                    areaQueue[queued] = building;
                                    queued = queued + 1;
                                }
                            } else if (climb->buildingArea == current) {
                                if (area == fromArea) {
                                    return (int)(current);
                                }
                                if (top == fromArea) {
                                    return (int)(current);
                                }
                                areaQueue[queued] = area;
                                queued = queued + 1;
                                candidates[k * 2 + 1] = 1;
                                areaQueue[queued] = top;
                                queued = queued + 1;
                            }
                        }
                    }
                } while (readIndex < queued);
            }
            DAT_PathFindingState::instance.areaRouteNeedsLadders = 0;
            return 0;
        }

    }
}
}
