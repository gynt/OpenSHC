#include "../../Map.func.hpp"

#include "OpenSHC/Map/WildlifeState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Game::GameMode;

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0052E020
    void WildlifeState::updateSection1034Info()
    {
        int iVar1;
        int iVar2;
        WildlifeGridElement* piVar3;
        int* piVar5;
        WildlifeGridElement* piVar4;
        int iVar6;
        int* piVar7;
        int local_4;
        if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY) {
            local_4 = 0;
            do {
                iVar2 = 0;
                piVar3 = &this->grid[0][0];
                do {
                    iVar6 = 0;
                    piVar4 = piVar3;
                    do {
                        piVar4->unknownNonZero01 = 0;
                        piVar4->field27_0x6c = 0;
                        if ((piVar4->castlebuildings != 0)
                            && (iVar1
                                = MACRO_CALL_MEMBER(OpenSHC::Map::WildlifeState_Func::hasAdjacentCellWithField24Or25,
                                    this)(iVar6, iVar2),
                                iVar1 != 0)) {
                            piVar4->field25_0x64 = piVar4->field25_0x64 + 1;
                        }
                        iVar6 = iVar6 + 1;
                        piVar4 = piVar4 + 0x640;
                    } while (iVar6 < 0x28);
                    iVar2 = iVar2 + 1;
                    piVar3 = piVar3 + 0x28;
                } while (iVar2 < 0x28);
                local_4 = local_4 + 1;
            } while (local_4 < 0x14);
            iVar2 = 0;
            piVar5 = &this->grid[0][0].field25_0x64;
            do {
                iVar6 = 0;
                piVar7 = piVar5;
                do {
                    if ((piVar7[-1] != 0) || (*piVar7 != 0)) {
                        MACRO_CALL_MEMBER(OpenSHC::Map::WildlifeState_Func::floodFillUnknownNonZero01FromCell, this)(
                            iVar6, iVar2, 6);
                    }
                    iVar6 = iVar6 + 1;
                    piVar7 = piVar7 + 0x640;
                } while (iVar6 < 0x28);
                iVar2 = iVar2 + 1;
                piVar5 = piVar5 + 0x28;
            } while (iVar2 < 0x28);
            iVar2 = 0;
            piVar5 = &this->grid[0][0].field27_0x6c;
            do {
                iVar6 = 0;
                piVar7 = piVar5;
                do {
                    if ((piVar7[-1] == 0)
                        && (iVar1 = MACRO_CALL_MEMBER(
                                OpenSHC::Map::WildlifeState_Func::isSuitableWildlifeSpawnCell, this)(iVar6, iVar2),
                            iVar1 != 0)) {
                        *piVar7 = *piVar7 + 1;
                    }
                    iVar6 = iVar6 + 1;
                    piVar7 = piVar7 + 0x640;
                } while (iVar6 < 0x28);
                iVar2 = iVar2 + 1;
                piVar5 = piVar5 + 0x28;
            } while (iVar2 < 0x28);
        }
    }

}
}
