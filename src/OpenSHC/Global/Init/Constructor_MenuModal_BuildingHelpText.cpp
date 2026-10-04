#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/TextEditor.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/MenuModalRenderFunction.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/MenuModal_BuildingHelpText.hpp"
#include "OpenSHC/Globals/Menu_BuildingHelpText.hpp"

namespace OpenSHC {
namespace Global {

    using UI::Enums::MenuModalType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059B720
    void Init::Constructor_MenuModal_BuildingHelpText()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_BuildingHelpText::ptr)(
            UI::Enums::MMT_BUILDING_HELP_TEXT, -1, -1, 0x2c0, 0x150, 0x20,
            (int)((int)(COL_BLACK::instance.shortValue)),
            (UI::MenuModalRenderFunction*)MACRO_CALL(
                UI::MenuModals::TextEditor_Func::MenuModalRenderFunction_TextEditor),
            Menu_BuildingHelpText::ptr);
        MACRO_CALL(OS_Func::_atexit)(MACRO_CALL(Meta_Func::Destructor_MenuModal_BuildingHelpText));
        return;
    }

}
}
