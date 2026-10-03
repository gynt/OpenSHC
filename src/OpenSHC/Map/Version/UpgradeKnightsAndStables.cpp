#include "../../Map.func.hpp"
#include "../Version.func.hpp"

#include "OpenSHC/Map/Units/Unit.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Units::UnitType;
    using OpenSHC::Map::Units::Unit;

    // FUNCTION: STRONGHOLDCRUSADER 0x0041A650
    void Version::UpgradeKnightsAndStables()
    {
        char* pcVar1;
        int iVar2;
        int iVar3;
        Unit* psVar4;
        short sVar4;
        int iVar5;
        int iVar6;
        int local_4;
        iVar3 = 0;
        iVar6 = 0;
        local_4 = 0;
        iVar5 = 0;
        do {
            if (*(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar3 + -0x4e) == 0x23) {
                sVar4 = 0;
                *(undefined1*)((int)DAT_BuildingsState::instance.buildings[0].quarryLinkedOxTethers + iVar3 + -0x23)
                    = 0;
                psVar4 = &DAT_UnitsState::instance.units[0];
                do {
                    if (((psVar4->unitType == OpenSHC::Map::Units::UT_E_KNIGHT)
                            && (psVar4->horseOriginStablesBuildingIndexUnk == local_4))
                        && (*(int*)&psVar4->horseOriginStableIDUnk
                            == *(int*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar3 + -0x48))) {
                        iVar2 = psVar4->uid;
                        DAT_BuildingsState::instance.buildings[0].quarryLinkedOxTethers
                            [*(char*)((int)DAT_BuildingsState::instance.buildings[0].quarryLinkedOxTethers + iVar3
                                 + -0x23)
                                + iVar5 + 0xb] = sVar4;
                        *(int*)(DAT_BuildingsState::instance.buildings[0].quarryLinkedOxTethers
                            + (*(char*)((int)DAT_BuildingsState::instance.buildings[0].quarryLinkedOxTethers + iVar3
                                   + -0x23)
                                  + iVar6)
                                * 2
                            + 0xf) = iVar2;
                        pcVar1 = (char*)((int)DAT_BuildingsState::instance.buildings[0].quarryLinkedOxTethers + iVar3
                            + -0x23);
                        *pcVar1 = *pcVar1 + '\x01';
                        if ('\x03' < *(char*)((int)DAT_BuildingsState::instance.buildings[0].quarryLinkedOxTethers
                                + iVar3 + -0x23))
                            break;
                    }
                    psVar4 = psVar4 + 0x248;
                    sVar4 = sVar4 + 1;
                } while ((int)psVar4 < 0x1651762);
            }
            local_4 = local_4 + 1;
            iVar3 = iVar3 + 0x32c;
            iVar5 = iVar5 + 0x196;
            iVar6 = iVar6 + 0xcb;
            if (0x18c7bf < iVar3) {}
        } while (true);
    }

}
}
