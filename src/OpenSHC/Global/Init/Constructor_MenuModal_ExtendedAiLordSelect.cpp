#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/AiLordSelect.func.hpp"
#include "OpenSHC/UI/MenuModalRenderFunction.hpp"

#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/MenuModal_ExtendedAiLordSelect.hpp"
#include "OpenSHC/Globals/Menu_ExtendedAiLordSelect.hpp"

namespace OpenSHC {
namespace Global {

    /*
      decompilerscript: committed: 2026-05-02 18:15:17.059000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0059C0F0
    void Init::Constructor_MenuModal_ExtendedAiLordSelect()
    {
        MACRO_CALL_MEMBER(OpenSHC::UI::MenuModal_Func::Constructor_MenuModal, MenuModal_ExtendedAiLordSelect::ptr)(
            (OpenSHC::UI::Enums::MenuModalType)119, (int)((int)(200)), (int)((int)(200)), (int)((int)(648)),
            (int)((int)(364)), (int)((int)(4160)), (int)((int)(COL_WHITE::instance.shortValue)),
            (OpenSHC::UI::MenuModalRenderFunction*)MACRO_CALL(
                OpenSHC::UI::MenuModals::AiLordSelect_Func::MenuModalRenderFunction_AiLordSelect),
            Menu_ExtendedAiLordSelect::ptr);
        MACRO_CALL(OpenSHC::OS_Func::_atexit)(
            MACRO_CALL(OpenSHC::Meta_Func::Destructor_MenuModal_ExtendedAiLordSelect));
        return;
    }

}
}
