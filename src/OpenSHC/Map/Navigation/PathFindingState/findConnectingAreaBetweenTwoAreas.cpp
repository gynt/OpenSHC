#include "../PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        /*
          Graph search over active, recognised climb data entries to determine whether two path-connection   areas
          (param_2 and param_3) are reachable from each other via intermediate wall or building   areas. Returns the
          connecting intermediate area ID if a path exists, param_2 if they are directly   adjacent, or 0 if no
          connection is found. Used to decide if units can navigate between   disconnected areas via climbing
          structures.      renamed by: Claude Sonnet 4.6
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A58A0
        dword PathFindingState::findConnectingAreaBetweenTwoAreas(int param_1, dword param_2, dword param_3)
        {
            int count;
            int readIndex;
            int queued;
            dword areaQueue[200];
            int candidates[400]; // pairs of { climb data index, already expanded }
            if (param_2 == param_3) {
                return (dword)(param_2);
            }
            int i = 1;
            this->nonLadderAreaRouteSearchCount = this->nonLadderAreaRouteSearchCount + 1;
            count = 0;
            readIndex = 0;
            queued = 0;
            for (; i < this->maxClimbDataCount; i++) {
                if (this->climbData[i].canBeUsed == 1 && this->climbData[i].isRecognizedByPathfinding != 0
                    && this->climbData[i].type != 1
                    && (param_1 == 0
                        || DAT_GameState::instance.mapAndTime.playerTeams[this->climbData[i].owner]
                            == DAT_GameState::instance.mapAndTime.playerTeams[param_1]
                        || DAT_BuildingsState::instance.buildings[this->climbData[i].buildingID].capturedByPlayerID != 0)) {
                    candidates[count * 2 + 1] = 0;
                    candidates[count * 2] = i;
                    count = count + 1;
                }
            }
            if (0 < count) {
                for (int k = 0; k < count; k++) {
                    int index = candidates[k * 2];
                    dword area = this->climbData[index].area;
                    if (area == param_3) {
                        dword top = this->climbData[index].topArea;
                        if (top == param_2) {
                            return (dword)(param_3);
                        }
                        dword building = this->climbData[index].buildingArea;
                        if (building == param_2) {
                            return (dword)(param_3);
                        }
                        areaQueue[queued] = top;
                        queued = queued + 1;
                        candidates[k * 2 + 1] = 1;
                        if (0 < (int)building) {
                            areaQueue[queued] = building;
                            queued = queued + 1;
                        }
                    } else {
                        dword top = this->climbData[index].topArea;
                        if (top == param_3) {
                            if (area == param_2) {
                                return (dword)(param_3);
                            }
                            dword building = this->climbData[index].buildingArea;
                            if (building == param_2) {
                                return (dword)(param_3);
                            }
                            areaQueue[queued] = area;
                            queued = queued + 1;
                            candidates[k * 2 + 1] = 1;
                            if (0 < (int)building) {
                                areaQueue[queued] = building;
                                queued = queued + 1;
                            }
                        } else if (this->climbData[index].buildingArea == param_3) {
                            if (area == param_2) {
                                return (dword)(param_3);
                            }
                            if (top == param_2) {
                                return (dword)(param_3);
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
                            int index = candidates[k * 2];
                            dword area = this->climbData[index].area;
                            if (area == current) {
                                dword top = this->climbData[index].topArea;
                                if (top == param_2) {
                                    return (dword)(current);
                                }
                                dword building = this->climbData[index].buildingArea;
                                if (building == param_2) {
                                    return (dword)(current);
                                }
                                areaQueue[queued] = top;
                                queued = queued + 1;
                                candidates[k * 2 + 1] = 1;
                                if (0 < (int)building) {
                                    areaQueue[queued] = building;
                                    queued = queued + 1;
                                }
                            } else {
                                dword top = this->climbData[index].topArea;
                                if (top == current) {
                                    if (area == param_2) {
                                        return (dword)(current);
                                    }
                                    dword building = this->climbData[index].buildingArea;
                                    if (building == param_2) {
                                        return (dword)(current);
                                    }
                                    areaQueue[queued] = area;
                                    queued = queued + 1;
                                    candidates[k * 2 + 1] = 1;
                                    if (0 < (int)building) {
                                        areaQueue[queued] = building;
                                        queued = queued + 1;
                                    }
                                } else if (this->climbData[index].buildingArea == current) {
                                    if (area == param_2) {
                                        return (dword)(current);
                                    }
                                    if (top == param_2) {
                                        return (dword)(current);
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
            return (dword)(0);
        }

    }
}
}
