#include "../../Synchrony.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Synchrony {

    using Rendering::Colors::BGR24;
    using Text::TextAlignment;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00488540
    void GameSynchronyState::renderDebugDataNetwork(int x, int y, int width, int height)
    {
        char* textAddress;
        int iVar4;
        int iVar5;
        int iVar6;
        TextAlignment TVar7;
        uint uVar8;
        BGR24 color;
        int iVar9;
        BOOLEnum BVar10;
        int iVar11;
        int blendStrength;
        int iVar2 = y;
        iVar5 = x;
        x = x + 2;
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "Packets in: ", x, y, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->packetsReceived, x, y, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        iVar4 = x + 0xa;
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "Chores used: ", iVar4, y, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
        iVar11 = 0;
        BVar10 = TRUE;
        iVar9 = 0x12;
        uVar8 = 0x80ff;
        TVar7 = Text::TTA_LEFT;
        iVar6 = y;
        int iVar1 = MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::getGameCommandArrayIndex, this)();
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            iVar1, iVar4, iVar6, TVar7, uVar8, iVar9, BVar10, iVar11);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            " Adv: ", x + 0x14, y, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            (int)this->DAT_LagIndicatorPerPlayer[1], x + 0x14, y, Text::TTA_LEFT, 0x80ff,
            0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            (int)this->DAT_LagIndicatorPerPlayer[2], x + 0x19, y, Text::TTA_LEFT, 0x80ff,
            0x12, TRUE, 0);
        iVar4 = x + 0x1e;
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            (int)this->DAT_LagIndicatorPerPlayer[3], iVar4, y, Text::TTA_LEFT, 0x80ff, 0x12,
            TRUE, 0);
        iVar6 = x + 0x23;
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            (int)this->DAT_LagIndicatorPerPlayer[4], iVar6, y, Text::TTA_LEFT, 0x80ff, 0x12,
            TRUE, 0);
        iVar1 = y + 0xe;
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "Timings ", x, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        x = 1;
        y = 0x1997fe0;
        do {
            if (*(int*)(y + -0x7a1cc) != -1) {
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    " p", x, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    x, x, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    ":", x, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    *(int*)y, x, iVar1, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
            }
            y = y + 4;
            x = x + -1;
        } while (x < 9);
        bool bVar3 = -1 < this->relativeTickTime;
        iVar1 = iVar2 + 0x1c;
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "Relative time: ", x, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->relativeTickTime, x, iVar1, Text::TTA_LEFT,
            (uint)((bVar3 - 1 & 0xffff8000) + 0x80ff), 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            " Logical speed: ", iVar5 + 0x98, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameCore::instance.gameTicksThisLoop, iVar5 + 0x98, iVar1, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        iVar1 = iVar2 + 0x2a;
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "Crcs ", x, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        x = 1;
        y = 0x1998004;
        do {
            if (*(int*)(y + -0x7a1f0) != -1) {
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    " p", x, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    x, x, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    ":", x, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    *(uint*)y & 0xfff, x, iVar1, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
            }
            y = y + 4;
            x = x + -1;
        } while (x < 9);
        iVar1 = iVar2 + 0x38;
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "Crc times ", x, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        x = 1;
        y = 0x1998028;
        do {
            if (*(int*)(y + -0x7a214) != -1) {
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    " p", x, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    x, x, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    ":", x, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    *(int*)y, x, iVar1, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
            }
            y = y + 4;
            x = x + -1;
        } while (x < 9);
        if (!this->syncStatus) {
            if (!this->DAT_GameHalted) {
                color = 0xffffff;
                textAddress = "Game in sync";
            } else {
                color = 0xff;
                textAddress = "GAME SPLINTERED ";
            }
        } else {
            color = 0xff;
            textAddress = "GAME SPLINTERED - Resyncing";
        }
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            textAddress, x, iVar2 + 0x46, Text::TTA_LEFT, color, 0x11, FALSE, 0);
        iVar1 = iVar2 + 0x62;
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "CHI:", x, iVar1, Text::TTA_LEFT, 0xffffff, 0x13, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameSynchronyState::instance
                    .DAT_PlayerMatchTimes[this->currentPlayerSlotID * 0xc + 9]
                & 0xfff,
            x, iVar1, Text::TTA_LEFT, 0x80ff, 0x13, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "  STR:", x, iVar1, Text::TTA_LEFT, 0xffffff, 0x13, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameSynchronyState::instance
                    .DAT_PlayerMatchTimes[this->currentPlayerSlotID * 0xc + 10]
                & 0xfff,
            x, iVar1, Text::TTA_LEFT, 0x80ff, 0x13, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "  VEG:", x, iVar1, Text::TTA_LEFT, 0xffffff, 0x13, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameSynchronyState::instance
                    .DAT_PlayerMatchTimes[this->currentPlayerSlotID * 0xc + 0xb]
                & 0xfff,
            x, iVar1, Text::TTA_LEFT, 0x80ff, 0x13, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "  TRI:", x, iVar1, Text::TTA_LEFT, 0xffffff, 0x13, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameSynchronyState::instance
                    .DAT_PlayerMatchTimes[this->currentPlayerSlotID * 0xc + 0xc]
                & 0xfff,
            x, iVar1, Text::TTA_LEFT, 0x80ff, 0x13, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "  PLA:", x, iVar1, Text::TTA_LEFT, 0xffffff, 0x13, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameSynchronyState::instance
                    .DAT_PlayerMatchTimes[this->currentPlayerSlotID * 0xc + 0xd]
                & 0xfff,
            x, iVar1, Text::TTA_LEFT, 0x80ff, 0x13, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "GAM:", x, iVar1, Text::TTA_LEFT, 0xffffff, 0x13, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameSynchronyState::instance
                    .DAT_PlayerMatchTimes[this->currentPlayerSlotID * 0xc + 0xe]
                & 0xfff,
            x, iVar1, Text::TTA_LEFT, 0x80ff, 0x13, TRUE, 0);
        iVar1 = iVar2 + 0x70;
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "  LAY:", x, iVar1, Text::TTA_LEFT, 0xffffff, 0x13, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameSynchronyState::instance
                    .DAT_PlayerMatchTimes[this->currentPlayerSlotID * 0xc + 0xf]
                & 0xfff,
            x, iVar1, Text::TTA_LEFT, 0x80ff, 0x13, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "  FLY:", x, iVar1, Text::TTA_LEFT, 0xffffff, 0x13, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameSynchronyState::instance
                    .DAT_PlayerMatchTimes[this->currentPlayerSlotID * 0xc + 0x10]
                & 0xfff,
            x, iVar1, Text::TTA_LEFT, 0x80ff, 0x13, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "  MOAT:", x, iVar1, Text::TTA_LEFT, 0xffffff, 0x13, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameSynchronyState::instance
                    .DAT_PlayerMatchTimes[this->currentPlayerSlotID * 0xc + 0x11]
                & 0xfff,
            x, iVar1, Text::TTA_LEFT, 0x80ff, 0x13, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "  TELE:", x, iVar1, Text::TTA_LEFT, 0xffffff, 0x13, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameSynchronyState::instance
                    .DAT_PlayerMatchTimes[this->currentPlayerSlotID * 0xc + 0x12]
                & 0xfff,
            x, iVar1, Text::TTA_LEFT, 0x80ff, 0x13, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "  PIDI:", x, iVar1, Text::TTA_LEFT, 0xffffff, 0x13, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameSynchronyState::instance
                    .DAT_PlayerMatchTimes[this->currentPlayerSlotID * 0xc + 0x13]
                & 0xfff,
            x, iVar1, Text::TTA_LEFT, 0x80ff, 0x13, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "  ZONE:", x, iVar1, Text::TTA_LEFT, 0xffffff, 0x13, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameSynchronyState::instance
                    .DAT_PlayerMatchTimes[this->currentPlayerSlotID * 0xc + 0x14]
                & 0xfff,
            x, iVar1, Text::TTA_LEFT, 0x80ff, 0x13, TRUE, 0);
        iVar1 = iVar2 + 0x7e;
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "Chimps: ", x, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_UnitsState::instance.unitCount, x, iVar1, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "Structs: ", x, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_BuildingsState::instance.structCount, x, iVar1, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "id_count: ", x, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameCore::instance.uniqueGameObjectTracker, x, iVar1, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "random no: ", x, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            (int)SEC_RNG::instance.currentNumber2, x, iVar1, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        iVar1 = iVar2 + 0x8c;
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "chore_latency: ", x, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->commandDelay, x, iVar1, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "pending_chores: ", x, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
        blendStrength = 0;
        BVar10 = TRUE;
        iVar11 = 0x12;
        uVar8 = 0x80ff;
        TVar7 = Text::TTA_LEFT;
        iVar5 = x;
        iVar9 = MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::getPendingGameCommandsCount, this)();
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            iVar9, iVar5, iVar1, TVar7, uVar8, iVar11, BVar10, blendStrength);
        iVar1 = iVar2 + 0x9a;
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "cl time_diff: ", x, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->clTimeDiff, x, iVar1, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "Clans: ", x, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_TribesState::instance.clans, x, iVar1, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        iVar2 = iVar2 + 0xa8;
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "Battle Level: ", x, iVar2, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameCore::instance.battleLevel, x, iVar2, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            ", ", x, iVar2, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameCore::instance.battleLevel2, x, iVar2, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "Multi Op: ", iVar4, iVar2, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->currentGameMode, iVar4, iVar2, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "GT: ", iVar6, iVar2, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameCore::instance.gameMode_2, iVar6, iVar2, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
    }

}
}
