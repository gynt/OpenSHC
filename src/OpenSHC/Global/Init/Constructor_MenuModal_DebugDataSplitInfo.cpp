#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/DebugDataSplitInfo.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/MenuModalRenderFunction.hpp"

#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/MenuModal_DebugDataSplitInfo.hpp"
#include "OpenSHC/Globals/Menu_DebugModals.hpp"

namespace OpenSHC {
namespace Global {

    using UI::Enums::MenuModalType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059B320
    void Init::Constructor_MenuModal_DebugDataSplitInfo()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_DebugDataSplitInfo::ptr)(
            UI::Enums::MMT_DEBUG_DATA_SPLIT_INFO, 0x10b, 3, 500, 0x12e, 0xe,
            (int)((int)(COL_WHITE::instance.shortValue)),
            MACRO_CALL(UI::MenuModals::DebugDataSplitInfo_Func::MenuModalRenderFunction_DebugDataSplitInfo),
            Menu_DebugModals::ptr);
        MACRO_CALL(OS_Func::_atexit)(MACRO_CALL(Meta_Func::Destructor_MenuModal_DebugDataSplitInfo));
        return;
    }

}
}
