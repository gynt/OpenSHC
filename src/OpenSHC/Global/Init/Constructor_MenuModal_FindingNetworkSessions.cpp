#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/FindingNetworkSessions.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/MenuModalRenderFunction.hpp"

#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/MenuModal_FindingNetworkSessions.hpp"
#include "OpenSHC/Globals/Menu_FindingNetworkSessions.hpp"

namespace OpenSHC {
namespace Global {

    using UI::Enums::MenuModalType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059B820
    void Init::Constructor_MenuModal_FindingNetworkSessions()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_FindingNetworkSessions::ptr)(
            UI::Enums::MMT_FINDING_NETWORK_SESSIONS, -1, -1, 500, 0x168, 0x200,
            (int)((int)(COL_WHITE::instance.shortValue)),
            MACRO_CALL(UI::MenuModals::FindingNetworkSessions_Func::MenuModalRenderFunction_FindingNetworkSessions),
            Menu_FindingNetworkSessions::ptr);
        MACRO_CALL(OS_Func::_atexit)(
            MACRO_CALL(Meta_Func::Destructor_MenuModal_FindingNetworkSessions));
        return;
    }

}
}
