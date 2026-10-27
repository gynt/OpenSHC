#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/DisplayElement.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/placementWarningVoicePlayed.hpp"

namespace OpenSHC {
namespace UI {
    namespace DisplayElements {

        using OpenSHC::UI::DisplayElement;
        using OpenSHC::UI::Enums::DisplayElementID;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004AF650
        void CheckDisplayElementByIDAndSetForUnlimitedDisplay(DisplayElementID displayElementID, dword elementState)
        {
            DisplayElement* const displayElement
                = MACRO_CALL(OpenSHC::UI::DisplayElements_Func::FindDisplayElementWithID)(displayElementID);
            if (displayElement != NULL) {
                if (displayElement->displayState_0xc != elementState) {
                    placementWarningVoicePlayed::instance = FALSE;
                }
                displayElement->displayState_0xc = elementState;
                displayElement->displayDuration_0x14 = -1;
            }
        }

    }
}
}
