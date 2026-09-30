#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0051B290
        void TroopValueState::pruneStaleTentPoints()
        {
            BOOLEnum BVar1;
            int* piVar2;
            piVar2 = &this->attackInfo.tentPointsValues[1].tribeID;
            do {
                if (piVar2[-1] == this->attackInfo.someCounter1) {
                    if (*piVar2 != 0) {
                        BVar1 = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::tribeCorrespondsWithUID,
                            DAT_TribesState::ptr)(*piVar2, (uint)((int)(piVar2[1])));
                        if (BVar1 == FALSE) {
                            MACRO_CALL_MEMBER(
                                OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                                0x20, '\0', (void*)((int)((AttackInfoSubArrayElement3*)(piVar2 + -4))));
                        }
                    }
                    if (0 < piVar2[2]) {
                        piVar2[2] = piVar2[2] + -1;
                    }
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                        0x20, '\0', (void*)((int)((AttackInfoSubArrayElement3*)(piVar2 + -4))));
                }
                piVar2 = piVar2 + 8;
            } while ((int)piVar2 < 0x17a52b4);
        }

    }
}
}
