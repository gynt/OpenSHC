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

    using UI::Enums::MenuModalType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059BBA0
    void Init::Constructor_MenuModal_BuildingAvailability()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_BuildingAvailability::ptr)(
            UI::Enums::MMT_BUILDING_AVAILABILITY, -1, -1, 700, 0x21c, 0x200, 6,
            (UI::MenuModalRenderFunction*)MACRO_CALL(
                UI::MenuModals::BuildingAvailability_Func::MenuModalRenderFunction_BuildingAvailability),
            Menu_BuildingAvailability::ptr);
        MACRO_CALL(OS_Func::_atexit)(
            MACRO_CALL(Meta_Func::Destructor_MenuModal_BuildingAvailability));
        return;
    }

}
}
