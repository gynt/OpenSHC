#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/EnterTitleOnGameStart.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/MenuModalRenderFunction.hpp"

#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/MenuModal_EnterTitleOnGameStart.hpp"
#include "OpenSHC/Globals/Menu_EnterTitleOnGameStart.hpp"

namespace OpenSHC {
namespace Global {

    using OpenSHC::UI::Enums::MenuModalType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059B6A0
    void Init::Constructor_MenuModal_EnterTitleOnGameStart()
    {
        MACRO_CALL_MEMBER(OpenSHC::UI::MenuModal_Func::Constructor_MenuModal, MenuModal_EnterTitleOnGameStart::ptr)(
            OpenSHC::UI::Enums::MMT_ENTER_TITLE_ON_GAME_START, -1, 100, 500, 200, 0x200,
            (int)((int)(COL_WHITE::instance.shortValue)),
            (OpenSHC::UI::MenuModalRenderFunction*)MACRO_CALL(
                OpenSHC::UI::MenuModals::EnterTitleOnGameStart_Func::MenuModalRenderFunction_EnterTitleOnGameStart),
            Menu_EnterTitleOnGameStart::ptr);
        MACRO_CALL(OpenSHC::OS_Func::_atexit)(
            MACRO_CALL(OpenSHC::Meta_Func::Destructor_MenuModal_EnterTitleOnGameStart));
        return;
    }

}
}
