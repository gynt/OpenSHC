#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/MenuViews/General.func.hpp"
#include "OpenSHC/UI/MenuViews/HistoricMissionPicture.func.hpp"
#include "OpenSHC/WindowsHelper/cdeclVoidFunc.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_HistoricMissionPicture.hpp"

namespace OpenSHC {
namespace Global {

    using UI::Enums::MenuViewType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059A880
    void Init::Constructor_MenuView_HistoricMissionPicture()
    {
        MACRO_CALL_MEMBER(UI::MenuView_Func::Constructor_MenuView, MenuView_HistoricMissionPicture::ptr)(
            UI::Enums::MVT_HISTORIC_MISSION_PICTURE,
            MACRO_CALL(UI::MenuViews::HistoricMissionPicture_Func::MenuView_HistoricMissionPicture_Prepare),
            MACRO_CALL(UI::MenuViews::General_Func::MenuView_General_DoInitial_BlackBorderAndGfx),
            MACRO_CALL(UI::MenuViews::HistoricMissionPicture_Func::MenuView_HistoricMissionPicture_DoEveryFrame));
        MACRO_CALL(OS_Func::_atexit)(
            MACRO_CALL(Meta_Func::Destructor_MenuView_HistoricMissionPicture));
        return;
    }

}
}
