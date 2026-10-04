#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/AiLordSelect.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/MenuModalRenderFunction.hpp"

#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/MenuModal_BasicAiLordSelect.hpp"
#include "OpenSHC/Globals/Menu_BasicAiLordSelect.hpp"

namespace OpenSHC {
namespace Global {

    using UI::Enums::MenuModalType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C0A0
    void Init::Constructor_MenuModal_BasicAiLordSelect()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_BasicAiLordSelect::ptr)(
            UI::Enums::MMT_BASIC_AI_LORD_SELECT, 200, 200, 0x288, 0x120, 0x1040,
            (int)((int)(COL_WHITE::instance.shortValue)),
            (UI::MenuModalRenderFunction*)MACRO_CALL(
                UI::MenuModals::AiLordSelect_Func::MenuModalRenderFunction_AiLordSelect),
            Menu_BasicAiLordSelect::ptr);
        MACRO_CALL(OS_Func::_atexit)(MACRO_CALL(Meta_Func::Destructor_MenuModal_BasicAiLordSelect));
        return;
    }

}
}
