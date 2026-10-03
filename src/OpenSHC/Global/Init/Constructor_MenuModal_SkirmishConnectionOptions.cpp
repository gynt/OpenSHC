#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/SkirmishConnectionOptions.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/MenuModalRenderFunction.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/MenuModal_SkirmishConnectionOptions.hpp"
#include "OpenSHC/Globals/Menu_SkirmishConnectionOptions.hpp"

namespace OpenSHC {
namespace Global {

    using OpenSHC::UI::Enums::MenuModalType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059BE20
    void Init::Constructor_MenuModal_SkirmishConnectionOptions()
    {
        MACRO_CALL_MEMBER(OpenSHC::UI::MenuModal_Func::Constructor_MenuModal, MenuModal_SkirmishConnectionOptions::ptr)(
            OpenSHC::UI::Enums::MMT_SKIRMISH_CONNECTION_OPTIONS, -1, -1, 0x198, 200, 0x200,
            (int)((int)(COL_BLACK::instance.shortValue)),
            (OpenSHC::UI::MenuModalRenderFunction*)MACRO_CALL(OpenSHC::UI::MenuModals::SkirmishConnectionOptions_Func::
                    MenuModalRenderFunction_SkirmishConnectionOptions),
            Menu_SkirmishConnectionOptions::ptr);
        MACRO_CALL(OpenSHC::OS_Func::_atexit)(
            MACRO_CALL(OpenSHC::Meta_Func::Destructor_MenuModal_SkirmishConnectionOptions));
        return;
    }

}
}
