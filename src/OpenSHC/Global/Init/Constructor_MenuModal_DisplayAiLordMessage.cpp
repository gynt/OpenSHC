#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/DisplayAiLordMessage.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/MenuModalRenderFunction.hpp"

#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/MenuModal_DisplayAiLordMessage.hpp"
#include "OpenSHC/Globals/Menu_DisplayAiLordMessage.hpp"

namespace OpenSHC {
namespace Global {

    using OpenSHC::UI::Enums::MenuModalType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059B860
    void Init::Constructor_MenuModal_DisplayAiLordMessage()
    {
        MACRO_CALL_MEMBER(OpenSHC::UI::MenuModal_Func::Constructor_MenuModal, MenuModal_DisplayAiLordMessage::ptr)(
            OpenSHC::UI::Enums::MMT_DISPLAY_AI_LORD_MESSAGE, 0, 0, 0, 0, 0x40,
            (int)((int)(COL_WHITE::instance.shortValue)),
            (OpenSHC::UI::MenuModalRenderFunction*)MACRO_CALL(
                OpenSHC::UI::MenuModals::DisplayAiLordMessage_Func::MenuModalRenderFunction_DisplayAiLordMessage),
            Menu_DisplayAiLordMessage::ptr);
        MACRO_CALL(OpenSHC::OS_Func::_atexit)(
            MACRO_CALL(OpenSHC::Meta_Func::Destructor_MenuModal_DisplayAiLordMessage));
        return;
    }

}
}
