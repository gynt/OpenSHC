#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/LoadMap.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/MenuModalRenderFunction.hpp"

#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/MenuModal_LoadMap.hpp"
#include "OpenSHC/Globals/Menu_LoadMap.hpp"

namespace OpenSHC {
namespace Global {

    using OpenSHC::UI::Enums::MenuModalType;

    /*
      decompilerscript: committed: 2026-05-02 18:15:17.059000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0059B4A0
    void Init::Constructor_MenuModal_LoadMap()
    {
        MACRO_CALL_MEMBER(OpenSHC::UI::MenuModal_Func::Constructor_MenuModal, MenuModal_LoadMap::ptr)(
            OpenSHC::UI::Enums::MMT_LOAD_MAP, -1, -1, 700, 0x18d, 0x200, (int)((int)(COL_WHITE::instance.shortValue)),
            (OpenSHC::UI::MenuModalRenderFunction*)MACRO_CALL(
                OpenSHC::UI::MenuModals::LoadMap_Func::MenuModalRenderFunction_LoadMap),
            Menu_LoadMap::ptr);
        MACRO_CALL(OpenSHC::OS_Func::_atexit)(MACRO_CALL(OpenSHC::Meta_Func::Destructor_MenuModal_LoadMap));
        return;
    }

}
}
