#include "../../Map.func.hpp"
#include "../MapPropertiesState.func.hpp"

#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"

namespace OpenSHC {
namespace Map {

    /*
      Iterates all map events and for any event of type 3 (scenario) whose ScenarioEventType is 0, 1,   0x1a, or 0x1b,
      sets its active flag (offset -2 as undefined2) to 1. Used during map load to   activate the relevant scenario-type
      events.      renamed by: Claude Sonnet 4.6
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004B7930
    void MapPropertiesState::activateScenarioTypeEvents()
    {
        int iVar1;
        int* piVar2;
        int iVar3;
        iVar3 = 0;
        if (0 < DAT_MapPropertiesState::instance.eventsCount) {
            piVar2 = &DAT_MapPropertiesState::instance.scenarioEvents[0].data.scenario.ScenarioEventType;
            do {
                if ((piVar2[-3] == 3)
                    && ((((iVar1 = *piVar2, iVar1 == 1 || (iVar1 == 0x1b)) || (iVar1 == 0)) || (iVar1 == 0x1a)))) {
                    *(undefined2*)(piVar2 + -2) = 1;
                }
                iVar3 = iVar3 + 1;
                piVar2 = piVar2 + 0x39;
            } while (iVar3 < DAT_MapPropertiesState::instance.eventsCount);
        }
    }

}
}
