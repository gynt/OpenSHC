#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/DebugDataZoneDataUnk.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/MenuModalRenderFunction.hpp"

#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/MenuModal_DebugDataZoneDataUnk.hpp"
#include "OpenSHC/Globals/Menu_DebugModals.hpp"

namespace OpenSHC {
namespace Global {

    using OpenSHC::UI::Enums::MenuModalType;

    /*
      decompilerscript: committed: 2026-05-02 18:15:17.059000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0059B260
    void Init::Constructor_MenuModal_DebugDataZoneDataUnk()
    {
        MACRO_CALL_MEMBER(OpenSHC::UI::MenuModal_Func::Constructor_MenuModal, MenuModal_DebugDataZoneDataUnk::ptr)(
            OpenSHC::UI::Enums::MMT_DEBUG_DATA_ZONE_DATAUnk, 0x10b, 3, 400, 200, 0xe,
            (int)((int)(COL_WHITE::instance.shortValue)),
            (OpenSHC::UI::MenuModalRenderFunction*)MACRO_CALL(
                OpenSHC::UI::MenuModals::DebugDataZoneDataUnk_Func::MenuModalRenderFunction_DebugDataZoneDataUnk),
            Menu_DebugModals::ptr);
        MACRO_CALL(OpenSHC::OS_Func::_atexit)(
            MACRO_CALL(OpenSHC::Meta_Func::Destructor_MenuModal_DebugDataZoneDataUnk));
        return;
    }

}
}
