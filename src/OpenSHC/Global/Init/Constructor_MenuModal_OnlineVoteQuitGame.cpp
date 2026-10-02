#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/OnlineVoteQuitGame.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/MenuModalRenderFunction.hpp"

#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/MenuModal_OnlineVoteQuitGame.hpp"
#include "OpenSHC/Globals/Menu_OnlineVoteQuitGame.hpp"

namespace OpenSHC {
namespace Global {

    using OpenSHC::UI::Enums::MenuModalType;

    /*
      decompilerscript: committed: 2026-05-02 18:15:17.059000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0059BEE0
    void Init::Constructor_MenuModal_OnlineVoteQuitGame()
    {
        MACRO_CALL_MEMBER(OpenSHC::UI::MenuModal_Func::Constructor_MenuModal, MenuModal_OnlineVoteQuitGame::ptr)(
            OpenSHC::UI::Enums::MMT_ONLINE_VOTE_QUIT_GAME, -1, 10, 400, 200, 0x200,
            (int)((int)(COL_WHITE::instance.shortValue)),
            (OpenSHC::UI::MenuModalRenderFunction*)MACRO_CALL(
                OpenSHC::UI::MenuModals::OnlineVoteQuitGame_Func::MenuModalRenderFunction_OnlineVoteQuitGame),
            Menu_OnlineVoteQuitGame::ptr);
        MACRO_CALL(OpenSHC::OS_Func::_atexit)(MACRO_CALL(OpenSHC::Meta_Func::Destructor_MenuModal_OnlineVoteQuitGame));
        return;
    }

}
}
