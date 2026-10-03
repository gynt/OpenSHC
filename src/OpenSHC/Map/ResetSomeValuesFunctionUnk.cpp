#include "../Map.func.hpp"

#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition2.hpp"
#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_VideoBikQueue.hpp"
#include "OpenSHC/Globals/DWORD_00eb0b18.hpp"

namespace OpenSHC {

using OpenSHC::Commands::MappersEnum;
using OpenSHC::UI::Enums::DisplayElementID;
using OpenSHC::UI::Enums::MenuModalType;
using OpenSHC::WindowsHelper::Enums::BOOLEnum;

// FUNCTION: STRONGHOLDCRUSADER 0x00431990
void Map::ResetSomeValuesFunctionUnk()
{
    DAT_GameCore::instance.isBinkVideoPlaying = 0;
    DAT_BuildingsState::instance.DAT_IsBuildingOrPeasantBinkPlaying = FALSE;
    DAT_BuildingsState::instance.field28_0x18e05c = 0;
    DAT_BuildingsState::instance.field29_0x18e060 = 0;
    MACRO_CALL(OpenSHC::UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
        OpenSHC::UI::Enums::DEID_KEEP_AND_GRANERY_PLACEMENT_INFO, 0);
    MACRO_CALL(OpenSHC::UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
        OpenSHC::UI::Enums::DEID_PLAYER_INFO_ON_HOVER, 0);
    MACRO_CALL(OpenSHC::UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
        OpenSHC::UI::Enums::DEID_MISSION_WIN_DEFEAT_BANNER, 0);
    MACRO_CALL(OpenSHC::UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
        OpenSHC::UI::Enums::DEID_WIN_DEFEAT_WINDOW, 0);
    MACRO_CALL(OpenSHC::UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
        OpenSHC::UI::Enums::DEID_UNKNOWN_25, 0);
    MACRO_CALL(OpenSHC::UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
        OpenSHC::UI::Enums::DEID_SOME_MULTIPLAYER_INFO_Unk_19, 0);
    MACRO_CALL(OpenSHC::UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
        OpenSHC::UI::Enums::DEID_TIME_UNTIL_VICTORY, 0);
    MACRO_CALL(OpenSHC::UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
        OpenSHC::UI::Enums::DEID_TIME_UNTIL_DEFEAT, 0);
    MACRO_CALL(OpenSHC::UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
        OpenSHC::UI::Enums::DEID_SOME_MULTIPLAYER_INFO_Unk_28, 0);
    MACRO_CALL(OpenSHC::UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
        OpenSHC::UI::Enums::DEID_PEOPLE_LEFT_TO_PLACE, 0);
    if (DAT_MenuModalComposition2::instance.activeModalDialogID == OpenSHC::UI::Enums::MMT_DISPLAY_AI_LORD_MESSAGE) {
        MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog, DAT_MenuModalComposition2::ptr)(
            OpenSHC::UI::Enums::MMT_NONE, FALSE);
    }
    DAT_VideoBikQueue::instance.storedMessages_0x924 = 0;
    DAT_GameCore::instance.section1076 = 0;
    DAT_TileMapState::instance.currentMapperCommand = OpenSHC::Commands::M_MAPPER_NULL;
    DAT_GameCore::instance.gamePausedLogical = 0;
    MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::resetMouseCursorState, DAT_MouseState::ptr)();
    DAT_GameCore::instance.viewportFocusBeforeBarracksHotkey = -1;
    DAT_GameCore::instance.viewportFocusBeforeMercenaryHotkey = -1;
    DAT_GameCore::instance.viewportFocusBeforeGranaryHotkey = -1;
    DAT_GameCore::instance.viewportFocusBeforeMarketHotkey = -1;
    DAT_GameCore::instance.viewportFocusBeforeKeepHotkey = -1;
    DAT_GameCore::instance.viewportFocusBeforeArmoryHotkey = -1;
    DAT_BuildingsState::instance.siegeEngineCreationRelated01 = 0;
    DAT_MinimapViewState::instance.spawnMomentCount = 0;
    DAT_GameCore::instance.field29_0x80 = 0;
    DAT_GameCore::instance.section1095 = 0;
    DAT_GameCore::instance.solitaryAltUDungeon = FALSE;
    DWORD_00eb0b18::instance = 0;
}

}
