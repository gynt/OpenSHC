/**
  path: 'OpenSHC/UI/BottomLeftTextDisplayState.func.hpp'
*/

#include "OpenSHC/UI/BottomLeftTextDisplayState.hpp"
#include "OpenSHC/UI/TextMessageBLLookupStructUnion.hpp"
namespace OpenSHC {
namespace UI {
    namespace BottomLeftTextDisplayState_Func {

        using OpenSHC::UI::TextMessageBLLookupStructUnion;

        MACRO_FUNCTION_RESOLVER(
            void (BottomLeftTextDisplayState::*)(int, int, int, int, int, int), false,
            Address::SHC_3BB0A8C1_0x004F4E00, &BottomLeftTextDisplayState::setBottomLeftTextDisplayText)
        setBottomLeftTextDisplayText;

        MACRO_FUNCTION_RESOLVER(void (BottomLeftTextDisplayState::*)(), false, Address::SHC_3BB0A8C1_0x004F4EF0,
            &BottomLeftTextDisplayState::tickTextExpiry)
        tickTextExpiry;

        MACRO_FUNCTION_RESOLVER(void (BottomLeftTextDisplayState::*)(int), false, Address::SHC_3BB0A8C1_0x004F4F60,
            &BottomLeftTextDisplayState::renderCurrentlyDisplayedText)
        renderCurrentlyDisplayedText;

    } // namespace BottomLeftTextDisplayState_Func
} // namespace UI
} // namespace OpenSHC
