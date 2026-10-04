#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/OnlineQuitGame.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/MenuModalRenderFunction.hpp"

#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/MenuModal_OnlineQuitGame.hpp"
#include "OpenSHC/Globals/Menu_OnlineQuitGame.hpp"

namespace OpenSHC {
namespace Global {

    using UI::Enums::MenuModalType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059BEA0
    void Init::Constructor_MenuModal_OnlineQuitGame()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_OnlineQuitGame::ptr)(
            UI::Enums::MMT_ONLINE_QUIT_GAME, -1, -1, 400, 0xeb, 0x200,
            (int)((int)(COL_WHITE::instance.shortValue)),
            (UI::MenuModalRenderFunction*)MACRO_CALL(
                UI::MenuModals::OnlineQuitGame_Func::MenuModalRenderFunction_OnlineQuitGame),
            Menu_OnlineQuitGame::ptr);
        MACRO_CALL(OS_Func::_atexit)(MACRO_CALL(Meta_Func::Destructor_MenuModal_OnlineQuitGame));
        return;
    }

}
}
