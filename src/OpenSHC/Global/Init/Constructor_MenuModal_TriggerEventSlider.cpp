#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/TriggerEventSlider.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/MenuModalRenderFunction.hpp"

#include "OpenSHC/Globals/MenuModal_TriggerEventSlider.hpp"
#include "OpenSHC/Globals/Menu_TriggerEventSlider.hpp"

namespace OpenSHC {
namespace Global {

    using UI::Enums::MenuModalType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059BFE0
    void Init::Constructor_MenuModal_TriggerEventSlider()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_TriggerEventSlider::ptr)(
            UI::Enums::MMT_TRIGGER_EVENT_SLIDER, -1, -1, 0x198, 0xa8, 0x200, 6,
            (UI::MenuModalRenderFunction*)MACRO_CALL(
                UI::MenuModals::TriggerEventSlider_Func::MenuModalRenderFunction_TriggerEventSlider),
            Menu_TriggerEventSlider::ptr);
        MACRO_CALL(OS_Func::_atexit)(MACRO_CALL(Meta_Func::Destructor_MenuModal_TriggerEventSlider));
        return;
    }

}
}
