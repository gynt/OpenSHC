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

    using UI::Enums::MenuModalType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059B6A0
    void Init::Constructor_MenuModal_EnterTitleOnGameStart()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_EnterTitleOnGameStart::ptr)(
            UI::Enums::MMT_ENTER_TITLE_ON_GAME_START, -1, 100, 500, 200, 0x200,
            (int)((int)(COL_WHITE::instance.shortValue)),
            (UI::MenuModalRenderFunction*)MACRO_CALL(
                UI::MenuModals::EnterTitleOnGameStart_Func::MenuModalRenderFunction_EnterTitleOnGameStart),
            Menu_EnterTitleOnGameStart::ptr);
        MACRO_CALL(OS_Func::_atexit)(
            MACRO_CALL(Meta_Func::Destructor_MenuModal_EnterTitleOnGameStart));
        return;
    }

}
}
