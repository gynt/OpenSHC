#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/DebugDataMapData.func.hpp"
#include "OpenSHC/UI/MenuModalRenderFunction.hpp"

#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/MenuModal_DebugDataMapData.hpp"
#include "OpenSHC/Globals/Menu_DebugModals.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059B360
    void Init::Constructor_MenuModal_DebugDataMapData()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_DebugDataMapData::ptr)(
            (UI::Enums::MenuModalType)201, 4, 4, 600, 0x19e, 0xe, (int)((int)(COL_WHITE::instance.shortValue)),
            MACRO_CALL(UI::MenuModals::DebugDataMapData_Func::MenuModalRenderFunction_DebugDataMapData),
            Menu_DebugModals::ptr);
        MACRO_CALL(OS_Func::_atexit)(MACRO_CALL(Meta_Func::Destructor_MenuModal_DebugDataMapData));
        return;
    }

}
}
