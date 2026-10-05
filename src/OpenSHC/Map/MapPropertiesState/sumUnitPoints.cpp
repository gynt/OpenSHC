#include "../../Map.func.hpp"
#include "../MapPropertiesState.func.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004B7FA0
    int MapPropertiesState::sumUnitPoints()
    {
        int _total;
        SiegeUnitCounts* piVar1;
        int iVar1;
        _total = 0;
        iVar1 = 4;
        piVar1 = &this->SEC_SiegeInformation;
        do {
            _total = _total + piVar1->archers + piVar1->crossbowmen + piVar1->spearmen + piVar1->macemen
                + piVar1->pikemen;
            piVar1 = (AI::Siege::SiegeUnitCounts*)(&piVar1->swordsmen);
            iVar1 = iVar1 + -1;
        } while (iVar1 != 0);
        this->DAT_MapEditorUnitPointsSum = _total + this->SEC_Section1067.field5_0x14
            + this->SEC_Section1067.field4_0x10 + this->SEC_Section1067.field3_0xc + this->SEC_Section1067.field2_0x8
            + this->SEC_Section1067.field1_0x4 + this->SEC_Section1067.field0_0x0;
        return (int)(this->DAT_MapEditorUnitPointsSum);
    }

}
}
