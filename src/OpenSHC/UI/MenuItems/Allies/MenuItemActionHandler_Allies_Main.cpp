#include "../Allies.func.hpp"

#include "OpenSHC/Game/Skirmish.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/g_allyHasPendingGoodsRequest.hpp"
#include "OpenSHC/Globals/DAT_AlliesCount.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SelectedAllyIndex.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_AllyMenuSelectionArray.hpp"
#include "OpenSHC/Globals/DAT_SentOrRequestedGoodsAmount.hpp"
#include "OpenSHC/Globals/DAT_AllyPlayerIDs.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Commands::GameCommandType;
        using OpenSHC::UI::Enums::MenuModalType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004B12D0
        void Allies::MenuItemActionHandler_Allies_Main(int param_1, ...)
        {
            short sVar1;
            if ((param_1 == -1) || (param_1 == 100)) {
                DAT_MenuModalComposition1::instance.activeModalDialogID = OpenSHC::UI::Enums::MMT_NONE;
            } else {
                if (6 < param_1) {
                    if (param_1 == 0x14) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                            DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_ALLIES_ORDER, FALSE);
                        return; // 0x4B131D ret
                    }
                    if (param_1 != 0x15) {
                        if (param_1 == 0x16) {
                            DAT_AllyMenuSelectionArray::instance[0] = -1;
                            DAT_SentOrRequestedGoodsAmount::instance = 0;
                            MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                                DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_ALLIES_REQUEST_GOODS, FALSE);
                            return; // 0x4B13B0 ret
                        }
                        if (param_1 == 0x6e) {
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 4;
                        } else {
                            if (param_1 != 0x6f) {
                                return; // 0x4B13C5 -> ret 0x4B1402
                            }
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 5;
                        }
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam1
                            = DAT_AllyPlayerIDs::instance[DAT_SelectedAllyIndex::instance];
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam4
                            = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                            DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_SEND_PLAYER_TO_PLAYER_REQUEST);
                        return; // 0x4B13FB ret
                    }
                    DAT_AllyMenuSelectionArray::instance[0] = -1;
                    sVar1
                        = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                              .requestedGoodsTypeByPlayer
                                  [DAT_AllyPlayerIDs::instance[DAT_SelectedAllyIndex::instance]];
                    DAT_SentOrRequestedGoodsAmount::instance = 0;
                    if (1 < sVar1) {
                        DAT_SentOrRequestedGoodsAmount::instance
                            = (int)DAT_GameState::instance
                                  .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                  .requestedGoodsAmountByPlayer
                                      [DAT_AllyPlayerIDs::instance[DAT_SelectedAllyIndex::instance]];
                        DAT_AllyMenuSelectionArray::instance[0] = sVar1 + -1;
                    }
                    g_allyHasPendingGoodsRequest::instance = (uint)(1 < sVar1);
                    MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                        DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_ALLIES_SEND_GOODS, FALSE);
                    return; // 0x4B138F ret
                }
                MACRO_CALL(OpenSHC::Game::Skirmish_Func::RecalculateAllies)();
                if (param_1 + -1 < (int)DAT_AlliesCount::instance) { // 0x4B12FC signed jge
                    DAT_SelectedAllyIndex::instance = param_1 + -1;
                }
            }
        }

    }
}
}
