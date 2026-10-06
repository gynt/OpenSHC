#include "../../Map.func.hpp"
#include "../MapPropertiesState.func.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004BB900
    void MapPropertiesState::resetEuroUnitRestrictions()
    {
        int* piVar1;
        short* psVar2;
        int iVar3;
        iVar3 = 0;
        if (0 < this->eventsCount) {
            piVar1 = &this->scenarioEvents[0].data.invasion.repeatMonths;
            do {
                if ((piVar1[-0x1e] == 1) && (*piVar1 != 0)) {
                    *piVar1 = *piVar1 * 0xc;
                }
                iVar3 = iVar3 + 1;
                piVar1 = piVar1 + 0x39;
            } while (iVar3 < this->eventsCount);
        }
        this->SEC_XbowProducible_save = 1;
        this->SEC_BowProducible_save = 1;
        this->SEC_PikeProducible_save = 1;
        this->SEC_SpearProducible_save = 1;
        this->SEC_SwordProducible_save = 1;
        this->SEC_MaceProducible_save = 1;
        psVar2 = this->SEC_MercRecruitable;
        iVar3 = 7;
        do {
            (((BarracksRecruitabilityShort*)(psVar2 + -7))->recruitability).archers = 1;
            *psVar2 = 1;
            psVar2 = psVar2 + 1;
            iVar3 = iVar3 + -1;
        } while (iVar3);
    }

}
}
