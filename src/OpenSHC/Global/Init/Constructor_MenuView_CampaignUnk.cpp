#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/MenuViews/CampaignUnk.func.hpp"
#include "OpenSHC/WindowsHelper/cdeclVoidFunc.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_CampaignUnk.hpp"

namespace OpenSHC {
namespace Global {

    using UI::Enums::MenuViewType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059A5E0
    void Init::Constructor_MenuView_CampaignUnk()
    {
        MACRO_CALL_MEMBER(UI::MenuView_Func::Constructor_MenuView, MenuView_CampaignUnk::ptr)(
            UI::Enums::MVT_UNKNOWN_27_CAMPAIGNUnk,
            MACRO_CALL(UI::MenuViews::CampaignUnk_Func::MenuView_CampaignUnk_Prepare),
            MACRO_CALL(UI::MenuViews::CampaignUnk_Func::MenuView_CampaignUnk_DoInitial),
            MACRO_CALL(UI::MenuViews::CampaignUnk_Func::MenuView_CampaignUnk_DoEveryFrame));
        MACRO_CALL(OS_Func::_atexit)(MACRO_CALL(Meta_Func::Destructor_MenuView_CampaignUnk));
        return;
    }

}
}
