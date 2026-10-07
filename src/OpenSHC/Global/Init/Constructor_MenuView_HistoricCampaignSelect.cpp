#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/MenuViews/General.func.hpp"
#include "OpenSHC/UI/MenuViews/HistoricCampaignSelect.func.hpp"
#include "OpenSHC/WindowsHelper/cdeclVoidFunc.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_HistoricCampaignSelect.hpp"

namespace OpenSHC {
namespace Global {

    using UI::Enums::MenuViewType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059A760
    void Init::Constructor_MenuView_HistoricCampaignSelect()
    {
        MACRO_CALL_MEMBER(UI::MenuView_Func::Constructor_MenuView, MenuView_HistoricCampaignSelect::ptr)(
            UI::Enums::MVT_HISTORIC_CAMPAIGN_SELECT,
            MACRO_CALL(UI::MenuViews::HistoricCampaignSelect_Func::MenuView_HistoricCampaignSelect_Prepare),
            MACRO_CALL(UI::MenuViews::General_Func::MenuView_General_DoInitial_BlackBoxDefaultBorderAndPicture),
            MACRO_CALL(UI::MenuViews::HistoricCampaignSelect_Func::MenuView_HistoricCampaignSelect_DoEveryFrame));
        MACRO_CALL(OS_Func::_atexit)(
            MACRO_CALL(Meta_Func::Destructor_MenuView_HistoricCampaignSelect));
        return;
    }

}
}
