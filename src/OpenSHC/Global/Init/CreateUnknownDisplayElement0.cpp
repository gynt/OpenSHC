#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/UI/DisplayElement.func.hpp"
#include "OpenSHC/UI/DisplayElementRenderFunc.hpp"
#include "OpenSHC/DE/SHCDE/eOnScreenText.hpp"
#include "OpenSHC/UI/Enums/DisplayElementPositionModifier.hpp"

#include "OpenSHC/Globals/UnknownDisplayElement0.hpp"

namespace OpenSHC {
namespace Global {

    using OpenSHC::DE::SHCDE::eOnScreenText;
    using OpenSHC::UI::Enums::DisplayElementPositionModifier;

    /*
      decompilerscript: committed: 2026-05-02 18:15:17.059000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0059C3C0
    void Init::CreateUnknownDisplayElement0()
    {
        MACRO_CALL_MEMBER(OpenSHC::UI::DisplayElement_Func::Constructor_DisplayElement, UnknownDisplayElement0::ptr)(
            OpenSHC::DE::SHCDE::OST_CHAT, 4, 0x198, 1,
            (OpenSHC::UI::DisplayElementRenderFunc*)MACRO_CALL(OpenSHC::Global_Func::DoNothing),
            (OpenSHC::UI::Enums::DisplayElementPositionModifier)(OpenSHC::UI::Enums::DEPM_RESOLUTION_X
                | OpenSHC::UI::Enums::DEPM_TOWARDS_MID_Y));
        return;
    }

}
}
