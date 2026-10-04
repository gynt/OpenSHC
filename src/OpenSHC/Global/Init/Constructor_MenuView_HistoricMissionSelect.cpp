#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/MenuViews/General.func.hpp"
#include "OpenSHC/UI/MenuViews/HistoricMissionSelect.func.hpp"
#include "OpenSHC/UI/MenuViews/MissionSelect.func.hpp"
#include "OpenSHC/WindowsHelper/cdeclVoidFunc.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_HistoricMissionSelect.hpp"

namespace OpenSHC {
namespace Global {

    using UI::Enums::MenuViewType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059A1C0
    void Init::Constructor_MenuView_HistoricMissionSelect()
    {
        MACRO_CALL_MEMBER(UI::MenuView_Func::Constructor_MenuView, MenuView_HistoricMissionSelect::ptr)(
            UI::Enums::MVT_HISTORIC_MISSION_SELECT,
            MACRO_CALL(UI::MenuViews::HistoricMissionSelect_Func::MenuView_HistoricMissionSelect_Prepare),
            MACRO_CALL(UI::MenuViews::General_Func::MenuView_General_DoInitial_DefaultMainMenuStructure),
            MACRO_CALL(UI::MenuViews::MissionSelect_Func::MenuView_MissionSelect_DoEveryFrame));
        MACRO_CALL(OS_Func::_atexit)(
            MACRO_CALL(Meta_Func::Destructor_MenuView_HistoricMissionSelect));
        return;
    }

}
}
