#include "../../Map.func.hpp"
#include "../Version.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00501490
    void Version::UpgradeMapLogicToVersion_102()
    {
        uint uVar1;
        int* _ptrLogicLayer;
        ushort* _ptrNext;
        ushort auStack_27424[80402];
        _ptrNext = auStack_27424;
        uVar1 = MSVC_SecurityCookie::instance ^ (uint)auStack_27424;
        MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::copyData, DAT_LowLevelMemory::ptr)(
            160800, (void*)((int)(DAT_TileMapState::instance.LogicLayer)), (void*)((int)(auStack_27424)));
        _ptrLogicLayer = DAT_TileMapState::instance.LogicLayer;
        do {
            *_ptrLogicLayer = (uint)*_ptrNext;
            _ptrLogicLayer = _ptrLogicLayer + 1;
            _ptrNext = _ptrNext + 1;
        } while ((int)_ptrLogicLayer < 0x1c46ba8);
        ;
    }

}
}
