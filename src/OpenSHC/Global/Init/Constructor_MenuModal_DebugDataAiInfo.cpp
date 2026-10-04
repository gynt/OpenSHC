#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/DebugDataAiInfo.func.hpp"
#include "OpenSHC/UI/MenuModalRenderFunction.hpp"

#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/MenuModal_DebugDataAiInfo.hpp"
#include "OpenSHC/Globals/Menu_DebugModals.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059B1E0
    void Init::Constructor_MenuModal_DebugDataAiInfo()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_DebugDataAiInfo::ptr)(
            (UI::Enums::MenuModalType)203, 10, 3, 0x30c, 0xf0, 0xe,
            (int)((int)(COL_WHITE::instance.shortValue)),
            (UI::MenuModalRenderFunction*)MACRO_CALL(
                UI::MenuModals::DebugDataAiInfo_Func::MenuModalRenderFunction_DebugDataAiInfo),
            Menu_DebugModals::ptr);
        MACRO_CALL(OS_Func::_atexit)(MACRO_CALL(Meta_Func::Destructor_MenuModal_DebugDataAiInfo));
        return;
    }

}
}
