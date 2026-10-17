#include "../../Synchrony.func.hpp"
#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Game/Player/PlayerData.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Synchrony {

    using Commands::MappersEnum;
    using Game::GameMode;
    using Game::GameMode2;
    using Game::Player::PlayerData;
    using UI::Enums::BuildingsAndStatusMenuTabType;
    using UI::Enums::DisplayElementID;
    using UI::Enums::MenuViewType;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00486600
    void GameSynchronyState::checkSkirmishGameDefeat()
    {
        int* piVar3;
        int iVar4;
        int _deadPlayerID;
        int iVar5;
        int iVar7;
        int iVar8;
        int iVar10;
        int local_48[18];
        if (this->currentGameMode != Game::GM_SOLITARY) {
            for (_deadPlayerID = 1; _deadPlayerID < 9; _deadPlayerID = _deadPlayerID + 1) {
                if (0 < DAT_GameState::instance.playerDataArray[_deadPlayerID].commemorationShrinePlacementCountdown) {
                    DAT_GameState::instance.playerDataArray[_deadPlayerID].commemorationShrinePlacementCountdown
                        = DAT_GameState::instance.playerDataArray[_deadPlayerID].commemorationShrinePlacementCountdown
                        + -1;
                    if (!DAT_GameState::instance.playerDataArray[_deadPlayerID].commemorationShrinePlacementCountdown) {
                        MACRO_CALL_MEMBER(
                            Map::Navigation::PathFindingState_Func::placeCommemoratingStatueAtGoodLocation,
                            DAT_PathFindingState::ptr)(_deadPlayerID);
                    }
                }
            }
            if ((DAT_GameCore::instance.gameMode_2 != Game::GM_CAMPAIGN_MISSION)
                && (!DAT_GameState::instance.mapAndTime.gameOver)) {
                if (DAT_GameCore::instance.unknownAlwaysZero) {
                    DAT_GameCore::instance.unknownAlwaysZero = 0;
                    for (_deadPlayerID = 1; _deadPlayerID < 9; _deadPlayerID = _deadPlayerID + 1) {
                        DAT_GameState::instance.mapAndTime.playerIsAlive[_deadPlayerID] = 0;
                        DAT_GameState::instance.playerDataArray[_deadPlayerID].playerDeathRelated = 1;
                    }
                    DAT_GameState::instance.mapAndTime.gameOver = TRUE;
                    DAT_GameState::instance.mapAndTime.gameOverTime = timeGetTime();
                    DAT_GameState::instance.mapAndTime
                        .playerIsAlive[DAT_GameSynchronyState::instance.currentPlayerSlotID] = 1;
                    DAT_GameCore::instance.skipStoreSKMasters = 0;
                    MACRO_CALL(UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                        UI::Enums::DEID_WIN_DEFEAT_WINDOW, 1);
                    return;
                }
                for (_deadPlayerID = 1; _deadPlayerID < 9; _deadPlayerID = _deadPlayerID + 1) {
                    local_48[_deadPlayerID * 2] = 0;
                    local_48[_deadPlayerID * 2 + 1] = 0;
                }
                for (_deadPlayerID = 1; _deadPlayerID < 9; _deadPlayerID = _deadPlayerID + 1) {
                    if ((this->currentPlayerFullIDArray[_deadPlayerID] != -1)
                        || (this->currentAIArray[_deadPlayerID] != 0)) {
                        iVar7 = DAT_GameState::instance.mapAndTime.playerTeams[_deadPlayerID];
                        local_48[iVar7 * 2] = local_48[iVar7 * 2] + 1;
                        if (DAT_GameState::instance.playerDataArray[_deadPlayerID].lordKilledByPlayerID != 0) {
                            local_48[iVar7 * 2 + 1] = local_48[iVar7 * 2 + 1] + 1;
                        }
                    }
                }
                iVar7 = 0;
                iVar5 = 0;
                iVar10 = 0;
                for (iVar4 = 1; iVar4 < 9; iVar4 = iVar4 + 1) {
                    if (local_48[iVar4 * 2] != 0) {
                        iVar10 = iVar10 + 1;
                        if (local_48[iVar4 * 2 + 1] == local_48[iVar4 * 2]) {
                            iVar5 = iVar5 + 1;
                        } else {
                            iVar7 = iVar4;
                        }
                    }
                }
                for (_deadPlayerID = 0; _deadPlayerID < 8; _deadPlayerID = _deadPlayerID + 1) {
                    local_48[_deadPlayerID + 1] = 0;
                }
                if (iVar5 < iVar10 + -1) {
                    if (!DAT_GameCore::instance.mapU4Int0) {
                        return;
                    }
                    bool bVar1 = false;
                    for (_deadPlayerID = 1; _deadPlayerID < 9; _deadPlayerID = _deadPlayerID + 1) {
                        if (((this->currentPlayerFullIDArray[_deadPlayerID] != -1)
                                || (this->currentAIArray[_deadPlayerID] != 0))
                            && DAT_GameState::instance.playerDataArray[_deadPlayerID].lordKilledByPlayerID == 0) {
                            iVar7 = DAT_GameState::instance.mapAndTime.playerTeams[_deadPlayerID];
                            bVar1 = true;
                        }
                    }
                    if (!bVar1) {
                        return;
                    }
                } else {
                    DAT_GameCore::instance.unknownAlwaysZero = 0;
                }
                for (iVar4 = 1; iVar4 < 9; iVar4 = iVar4 + 1) {
                    if (((this->currentPlayerFullIDArray[iVar4] != -1) || (this->currentAIArray[iVar4] != 0))
                        && DAT_GameState::instance.mapAndTime.playerTeams[iVar4] == iVar7) {
                        local_48[iVar4] = 1;
                    }
                }
                for (_deadPlayerID = 1; _deadPlayerID < 9; _deadPlayerID = _deadPlayerID + 1) {
                    if ((this->currentPlayerFullIDArray[_deadPlayerID] != -1)
                        || (this->currentAIArray[_deadPlayerID] != 0)) {
                        DAT_GameState::instance.mapAndTime.playerIsAlive[_deadPlayerID]
                            = (short)local_48[_deadPlayerID];
                        DAT_GameState::instance.mapAndTime.gameOver = TRUE;
                        DAT_GameState::instance.playerDataArray[_deadPlayerID].playerDeathRelated = 1;
                        DAT_GameState::instance.mapAndTime.gameOverTime = timeGetTime();
                        DAT_GameCore::instance.skipStoreSKMasters = 0;
                        MACRO_CALL(UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                            UI::Enums::DEID_WIN_DEFEAT_WINDOW, 1);
                        if ((DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType
                                == UI::Enums::BASMTT_SIEGETENT_BATTERINGRAM)
                            || (DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType
                                == UI::Enums::BASMTT_SIEGETENT_SHIELD)) {
                            DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.buildMenuTab
                                = DAT_GameCore::instance.tabTypeSiegeSubset;
                            MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                                UI::Enums::MVT_BUILD_MENU, 0);
                        }
                        DAT_TileMapState::instance.currentMapperCommand = Commands::M_MAPPER_NULL;
                        if (0 < DAT_UnitsState::instance.totalUnitsInSelection) {
                            MACRO_CALL_MEMBER(
                                Map::Units::UnitsState_Func::deselectAllUnitsOneByOne, DAT_UnitsState::ptr)();
                            MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::queueEscapeCommand, DAT_UnitsState::ptr)();
                            MACRO_CALL_MEMBER(Input::MouseState_Func::resetMouseCursorState, DAT_MouseState::ptr)();
                        }
                    }
                }
            }
        }
    }

}
}
