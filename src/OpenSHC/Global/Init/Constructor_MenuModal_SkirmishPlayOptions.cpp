#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/SkirmishPlayOptions.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/MenuModalRenderFunction.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/MenuModal_SkirmishPlayOptions.hpp"
#include "OpenSHC/Globals/Menu_SkirmishPlayOptions.hpp"

namespace OpenSHC {
namespace Global {

    using UI::Enums::MenuModalType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059BE60
    void Init::Constructor_MenuModal_SkirmishPlayOptions()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_SkirmishPlayOptions::ptr)(
            UI::Enums::MMT_SKIRMISH_PLAY_OPTIONS, -1, -1, 0x198, 0x172, 0x200,
            (int)((int)(COL_BLACK::instance.shortValue)),
            (UI::MenuModalRenderFunction*)MACRO_CALL(
                UI::MenuModals::SkirmishPlayOptions_Func::MenuModalRenderFunction_SkirmishPlayOptions),
            Menu_SkirmishPlayOptions::ptr);
        MACRO_CALL(OS_Func::_atexit)(MACRO_CALL(Meta_Func::Destructor_MenuModal_SkirmishPlayOptions));
        return;
    }

}
}
