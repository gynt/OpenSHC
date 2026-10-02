#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/TextEditor.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/MenuModalRenderFunction.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/MenuModal_MapDescriptionEditor.hpp"
#include "OpenSHC/Globals/Menu_MapDescriptionEditor.hpp"

namespace OpenSHC {
namespace Global {

    using OpenSHC::UI::Enums::MenuModalType;

    /*
      decompilerscript: committed: 2026-05-02 18:15:17.059000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0059B7A0
    void Init::Constructor_MenuModal_MapDescriptionEditor()
    {
        MACRO_CALL_MEMBER(OpenSHC::UI::MenuModal_Func::Constructor_MenuModal, MenuModal_MapDescriptionEditor::ptr)(
            OpenSHC::UI::Enums::MMT_MAP_DESCRIPTION_EDITOR, -1, -1, 400, 0xe6, 0x20,
            (int)((int)(COL_BLACK::instance.shortValue)),
            (OpenSHC::UI::MenuModalRenderFunction*)MACRO_CALL(
                OpenSHC::UI::MenuModals::TextEditor_Func::MenuModalRenderFunction_TextEditor),
            Menu_MapDescriptionEditor::ptr);
        MACRO_CALL(OpenSHC::OS_Func::_atexit)(
            MACRO_CALL(OpenSHC::Meta_Func::Destructor_MenuModal_MapDescriptionEditor));
        return;
    }

}
}
