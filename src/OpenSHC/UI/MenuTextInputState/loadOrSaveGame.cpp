#include "../MenuTextInputState.func.hpp"

#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MenuItems/SaveLoadMap.func.hpp"
#include "OpenSHC/UI/MenuTextInputState.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"
#include "OpenSHC/Globals/INT_00b95b64.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

namespace OpenSHC {
namespace UI {

    using Commands::GameCommandType;
    using Game::GameMode;
    using UI::Enums::MenuModalType;

    // FUNCTION: STRONGHOLDCRUSADER 0x004968A0
    void MenuTextInputState::loadOrSaveGame(int action)
    {
        int iVar1;
        int iVar2;
        undefined4* puVar5;
        int iVar6;
        if ((((DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY)
                 || (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SKIRMISH_SINGLE_PLAYER))
                || (DAT_GameSynchronyState::instance.saveRelated != 1))
            || (action != 10)) {
            DAT_MouseState::instance.waitCursorToggle = 1;
            MACRO_CALL(UI::Helpers_Func::SetCursorDependingOnProgramState)();
            MACRO_CALL(OS_Func::_memset)(DAT_MinimapViewState::instance.loadedMiniMap, 0, 80000);
            INT_00b95b64::instance = 1;
            if ((DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY)
                || (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SKIRMISH_SINGLE_PLAYER)) {
                std::string _savesPath = MACRO_CALL_MEMBER(
                    IO::ResourceManager_Func::paths_getSavesPath, DAT_ResourceManager::ptr)(true);
                _savesPath.append("*.sav", 5);
                MACRO_CALL_MEMBER(IO::ResourceManager_Func::discoverMapFiles, DAT_ResourceManager::ptr)(
                    _savesPath.c_str());
                this->field32_0x74 = DAT_ResourceManager::instance.mapFileCounter;
                for (int _mapIndex = 0; _mapIndex < DAT_ResourceManager::instance.mapFileCounter; _mapIndex++) {
                    (&this->DAT_MapSelectionPreloadMapIndexMapping)[_mapIndex] = _mapIndex;
                }
            } else {
                std::string _savesPath = MACRO_CALL_MEMBER(
                    IO::ResourceManager_Func::paths_getSavesPath, DAT_ResourceManager::ptr)(true);
                _savesPath.append("*.msv", 5);
                MACRO_CALL_MEMBER(IO::ResourceManager_Func::discoverMapFiles, DAT_ResourceManager::ptr)(
                    _savesPath.c_str());
                this->field32_0x74 = DAT_ResourceManager::instance.mapFileCounter;
                iVar6 = 0;
                if (0 < DAT_ResourceManager::instance.mapFileCounter) {
                    puVar5 = this->DAT_ArrayOfMapIndices + 499;
                    do {
                        puVar5[-500] = iVar6;
                        *puVar5 = 1;
                        if (action != 10) {
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = iVar6;
                            MACRO_CALL_MEMBER(
                                Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                                (Commands::GameCommandType)(Commands::GCT_LOAD_MAP_HEADER
                                    | Commands::GCT_MULTIPLAYER_INITIATE_ANNOUNCE_HOST));
                        }
                        iVar6 = iVar6 + 1;
                        puVar5 = puVar5 + 1;
                    } while (iVar6 < DAT_ResourceManager::instance.mapFileCounter);
                }
            }
            DAT_MouseState::instance.waitCursorToggle = 0;
            this->field33_0x78 = 0;
            this->DAT_MenuLoadGameRelativeSelectionOffset = 0;
            if (this->field32_0x74 == 0) {
                this->DAT_MenuLoadGameRelativeSelectionIndex = -1;
            } else {
                this->DAT_MenuLoadGameRelativeSelectionIndex = 0;
            }
            this->field39_0x90 = 0;
            this->field38_0x8c = 0xffffffff;
            this->field49_0xac = 0;
            this->field43_0xa0 = 0xffffffff;
            this->field36_0x84 = 0x10;
            if (action == 9) {
                MACRO_CALL_MEMBER(UI::MenuTextInputState_Func::activateModalDialogAndClearText, this)(
                    UI::Enums::MMT_LOAD_MAP);
                this->field0_0x0 = 1;
                iVar6 = this->field1_0x4;
                iVar1 = this->field2_0x8;
                iVar2 = this->field3_0xc;
            } else {
                MACRO_CALL_MEMBER(UI::MenuTextInputState_Func::activateModalDialogAndClearText, this)(
                    UI::Enums::MMT_SAVE_MAP);
                DAT_UserTextHandlerState::instance.allowUserTextInput = 0;
                MACRO_CALL_MEMBER(Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(
                    2);
                MACRO_CALL_MEMBER(
                    Text::UserTextHandler_Func::moveCursorToEnd, DAT_UserTextHandlerState::ptr)();
                DAT_UserTextHandlerState::instance.allowUserTextInput = 1;
                this->field0_0x0 = 3;
                iVar6 = this->field4_0x10;
                iVar1 = this->field5_0x14;
                iVar2 = this->field6_0x18;
            }
            if ((this->DAT_MenuLoadGameRelativeSelectionIndex != -1)
                && (this->field33_0x78 = iVar2, this->DAT_MenuLoadGameRelativeSelectionIndex = iVar1,
                    this->DAT_MenuLoadGameRelativeSelectionOffset = iVar6, this->field32_0x74 <= iVar6 + iVar1)) {
                this->DAT_MenuLoadGameRelativeSelectionIndex = 0;
                this->DAT_MenuLoadGameRelativeSelectionOffset = 0;
            }
            MACRO_CALL(UI::MenuItems::SaveLoadMap_Func::MenuItemActionHandler_SaveLoadMap_TableHeader)(
                -1 - this->field33_0x78);
        } else {
            MACRO_CALL_MEMBER(UI::MenuTextInputState_Func::clearAnyOtherModalDialogs, this)();
        };
        return;
    }

}
}
