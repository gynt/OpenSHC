#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/BuildingAvailability.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/MenuModalRenderFunction.hpp"

#include "OpenSHC/Globals/MenuModal_BuildingAvailability.hpp"
#include "OpenSHC/Globals/Menu_BuildingAvailability.hpp"

namespace OpenSHC {
namespace Global {

    using OpenSHC::UI::Enums::MenuModalType;

    /*
      decompilerscript: committed: 2026-05-02 18:15:17.059000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0059BBA0
    void Init::Constructor_MenuModal_BuildingAvailability()
    {
        MACRO_CALL_MEMBER(OpenSHC::UI::MenuModal_Func::Constructor_MenuModal, MenuModal_BuildingAvailability::ptr)(
            OpenSHC::UI::Enums::MMT_BUILDING_AVAILABILITY, -1, -1, 700, 0x21c, 0x200, 6,
            (OpenSHC::UI::MenuModalRenderFunction*)MACRO_CALL(
                OpenSHC::UI::MenuModals::BuildingAvailability_Func::MenuModalRenderFunction_BuildingAvailability),
            Menu_BuildingAvailability::ptr);
        MACRO_CALL(OpenSHC::OS_Func::_atexit)(
            MACRO_CALL(OpenSHC::Meta_Func::Destructor_MenuModal_BuildingAvailability));
        return;
    }

}
}
