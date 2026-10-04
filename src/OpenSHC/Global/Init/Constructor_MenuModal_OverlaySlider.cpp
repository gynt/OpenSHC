#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/OverlaySlider.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/MenuModalRenderFunction.hpp"

#include "OpenSHC/Globals/MenuModal_OverlaySlider.hpp"
#include "OpenSHC/Globals/Menu_OverlaySlider.hpp"

namespace OpenSHC {
namespace Global {

    using UI::Enums::MenuModalType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059B120
    void Init::Constructor_MenuModal_OverlaySlider()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_OverlaySlider::ptr)(
            UI::Enums::MMT_OVERLAY_SLIDER, 0, 0, 0xcc, 0x11, 0, 0,
            (UI::MenuModalRenderFunction*)MACRO_CALL(
                UI::MenuModals::OverlaySlider_Func::MenuModalRenderFunction_OverlaySlider),
            Menu_OverlaySlider::ptr);
        MACRO_CALL(OS_Func::_atexit)(MACRO_CALL(Meta_Func::Destructor_MenuModal_OverlaySlider));
        return;
    }

}
}
