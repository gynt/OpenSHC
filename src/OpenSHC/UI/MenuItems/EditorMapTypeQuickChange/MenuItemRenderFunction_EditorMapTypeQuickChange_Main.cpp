#include "../EditorMapTypeQuickChange.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/Map/MapLockState.hpp"
#include "OpenSHC/Map/MapLockStateInt.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/string-macros.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Map::MapLockState;
        using OpenSHC::Map::MapLockStateInt;
        using OpenSHC::Rendering::Colors::BGR24;
        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004AC040
        void EditorMapTypeQuickChange::MenuItemRenderFunction_EditorMapTypeQuickChange_Main(int param_1, ...)
        {
            char* textAddress;
            BOOLEnum BVar2 = DAT_ButtonCurrentlyInteracting::instance;
            DAT_ButtonCurrentlyInteracting::instance = FALSE;
            MapLockStateInt MVar1 = DAT_GameCore::instance.U3_mapLockedState;
            if (param_1 < 3) {
            joined_r0x004ac081:
                if (param_1 != MVar1)
                    goto switchD_004ac099_caseD_4;
            } else {
                if (param_1 < 7) {
                    MVar1 = DAT_MapPropertiesState::instance.SEC_U3_MapType2_1
                        + (OpenSHC::Map::MLS_MISSION | OpenSHC::Map::MLS_PLAYABLE);
                    goto joined_r0x004ac081;
                }
                if (param_1 >= 0x14) {
                    switch (param_1) {
                    case 0x14:
                        if (DAT_TileMapState::instance.mapSize != 0xa0)
                            goto switchD_004ac099_caseD_4;
                        break;
                    case 0x15:
                        if (DAT_TileMapState::instance.mapSize != 200)
                            goto switchD_004ac099_caseD_4;
                        break;
                    case 0x16:
                        if (DAT_TileMapState::instance.mapSize != 300)
                            goto switchD_004ac099_caseD_4;
                        break;
                    case 0x17:
                        if (DAT_TileMapState::instance.mapSize != 400)
                            goto switchD_004ac099_caseD_4;
                        break;
                    default:
                        goto switchD_004ac099_caseD_4;
                    }
                } else {
                    if (param_1 == 0xc) {
                        if (DAT_GameCore::instance.U2_mapType_singleOrMulti == 0) {
                            DAT_ButtonCurrentlyInteracting::instance = FALSE;
                        }
                        if (DAT_GameCore::instance.mapU4Int0 == 0)
                            goto switchD_004ac099_caseD_4;
                    } else if (param_1 == 10) {
                        if (DAT_GameCore::instance.U2_mapType_singleOrMulti != 0)
                            goto switchD_004ac099_caseD_4;
                    } else if (param_1 != 0xb || (int)DAT_GameCore::instance.U2_mapType_singleOrMulti <= 0)
                        goto switchD_004ac099_caseD_4;
                }
            }
            DAT_ButtonCurrentlyInteracting::instance = TRUE;
        switchD_004ac099_caseD_4:
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
            textAddress = "";
            switch (param_1) {
            case 0:
                textAddress = S_EDITABLE_005A7660;
                break;
            case 1:
                textAddress = S_PLAYABLE_005A7654;
                break;
            case 2:
                textAddress = S_MISSION_005A764C;
                break;
            case 3:
                textAddress = S_SIEGE_005A7644;
                break;
            case 4:
                textAddress = S_INVASION_005A7638;
                break;
            case 5:
                textAddress = S_ECONOMIC_005A762C;
                break;
            case 6:
                textAddress = S_JUST_BUILD_005A7620;
                break;
            case 10:
                textAddress = S_SINGLE_005A7618;
                break;
            case 0xb:
                textAddress = S_MULTI_005A7610;
                break;
            case 0xc:
                textAddress = S_KING_OF_THE_HILL_005A75FC;
                break;
            case 0x14:
                textAddress = S_160X160_005A75F4;
                break;
            case 0x15:
                textAddress = S_200X200_005A75EC;
                break;
            case 0x16:
                textAddress = S_300X300_005A75E4;
                break;
            case 0x17:
                textAddress = S_400X400_005A75DC;
            }
            if (BVar2 != FALSE) {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    textAddress, (int)((int)DAT_ButtonW::instance / 2 + DAT_ButtonX::instance),
                    (int)(DAT_ButtonY::instance + 4), OpenSHC::Text::TTA_CENTER, 0xccfaff, 0x11, FALSE, 0);
            } else {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    textAddress, (int)((int)DAT_ButtonW::instance / 2 + DAT_ButtonX::instance),
                    (int)(DAT_ButtonY::instance + 4), OpenSHC::Text::TTA_CENTER, 0xc2f0eb, 0x11, FALSE, 0);
            }
        }

    }
}
}
