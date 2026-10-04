#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/NewEventCondition.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/MenuModalRenderFunction.hpp"

#include "OpenSHC/Globals/MenuModal_NewEventCondition.hpp"
#include "OpenSHC/Globals/Menu_NewEventCondition.hpp"

namespace OpenSHC {
namespace Global {

    using UI::Enums::MenuModalType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059BAE0
    void Init::Constructor_MenuModal_NewEventCondition()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_NewEventCondition::ptr)(
            UI::Enums::MMT_NEW_EVENT_CONDITION, -1, -1, 700, 0x21c, 0x200, 6,
            MACRO_CALL(UI::MenuModals::NewEventCondition_Func::MenuModalRenderFunction_NewEventCondition),
            Menu_NewEventCondition::ptr);
        MACRO_CALL(OS_Func::_atexit)(MACRO_CALL(Meta_Func::Destructor_MenuModal_NewEventCondition));
        return;
    }

}
}
