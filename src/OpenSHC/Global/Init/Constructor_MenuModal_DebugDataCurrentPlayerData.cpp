#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/DebugDataCurrentPlayerData.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/MenuModalRenderFunction.hpp"

#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/MenuModal_DebugDataCurrentPlayerData.hpp"
#include "OpenSHC/Globals/Menu_DebugModals.hpp"

namespace OpenSHC {
namespace Global {

    using UI::Enums::MenuModalType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059B1A0
    void Init::Constructor_MenuModal_DebugDataCurrentPlayerData()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal,
            MenuModal_DebugDataCurrentPlayerData::ptr)(UI::Enums::MMT_DEBUG_DATA_CURRENT_PLAYER_DATA, 0x10b, 3,
            400, 0xf2, 0xe, (int)((int)(COL_WHITE::instance.shortValue)),
            (UI::MenuModalRenderFunction*)MACRO_CALL(UI::MenuModals::DebugDataCurrentPlayerData_Func::
                    MenuModalRenderFunction_DebugDataCurrentPlayerData),
            Menu_DebugModals::ptr);
        MACRO_CALL(OS_Func::_atexit)(
            MACRO_CALL(Meta_Func::Destructor_MenuModal_DebugDataCurrentPlayerData));
        return;
    }

}
}
