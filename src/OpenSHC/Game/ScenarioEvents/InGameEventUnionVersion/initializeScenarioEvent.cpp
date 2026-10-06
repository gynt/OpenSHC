#include "../../../Game.func.hpp"
#include "../InGameEventUnionVersion.func.hpp"

namespace OpenSHC {
namespace Game {
    namespace ScenarioEvents {

        // FUNCTION: STRONGHOLDCRUSADER 0x004B77A0
        ScenarioEventCondition* InGameEventUnionVersion::initializeScenarioEvent()
        {
            ScenarioEventCondition* pSVar1;
            int iVar2;
            (this->header).month = 0;
            (this->header).year = 1181;
            (this->header).tl_type = 3;
            (this->data).scenario.ScenarioEventType = 0;
            (this->data).scenario.actionData = 0;
            *(undefined2*)((int)&this->data + 8) = 1;
            (this->data).scenario.repeat = 0;
            pSVar1 = (this->data).scenario.conditions;
            iVar2 = 40;
            do {
                pSVar1->enabled = 0;
                pSVar1->value = 0;
                pSVar1->subType = 0;
                pSVar1 = pSVar1 + 1;
                iVar2 = iVar2 + -1;
            } while (iVar2);
            return pSVar1;
        }

    }
}
}
