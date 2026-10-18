#include "../../Synchrony.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/string-literals.hpp"

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
        int* _pMatchTime;
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
            (char*)s_Packets_in__005a7488, x, y, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->packetsReceived, x, y, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        iVar4 = x + 0xa;
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            (char*)s_Chores_used__005a7478, iVar4, y, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
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
            (char*)s_Adv__005a7470, x + 0x14, y, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            (int)this->DAT_LagIndicatorPerPlayer[1], x + 0x14, y, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            (int)this->DAT_LagIndicatorPerPlayer[2], x + 0x19, y, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        iVar4 = x + 0x1e;
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            (int)this->DAT_LagIndicatorPerPlayer[3], iVar4, y, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        iVar6 = x + 0x23;
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            (int)this->DAT_LagIndicatorPerPlayer[4], iVar6, y, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        iVar1 = y + 0xe;
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            (char*)s_Timings_005a7464, x, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        for (x = 1, _pMatchTime = this->matchTimes + 1; x < 9; _pMatchTime = _pMatchTime + 1, x = x + 1) {
            if (this->currentPlayerFullIDArray[x] != -1) {
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    (char*)s_p_005a7460, x, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    x, x, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    (char*)s___005a745c, x, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    *_pMatchTime, x, iVar1, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
            }
        }
        bool bVar3 = -1 < this->relativeTickTime;
        iVar1 = iVar2 + 0x1c;
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            (char*)s_Relative_time__005a744c, x, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->relativeTickTime, x, iVar1, Text::TTA_LEFT, (uint)((bVar3 - 1 & 0xffff8000) + 0x80ff), 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            (char*)s_Logical_speed__005a7438, iVar5 + 0x98, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameCore::instance.gameTicksThisLoop, iVar5 + 0x98, iVar1, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        iVar1 = iVar2 + 0x2a;
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            (char*)s_Crcs_005a7430, x, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        for (x = 1, y = 0x1998004; x < 9; y = y + 4, x = x + 1) {
            if (*(int*)(y + -0x7a1f0) != -1) {
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    (char*)s_p_005a7460, x, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    x, x, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    (char*)s___005a745c, x, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    *(uint*)y & 0xfff, x, iVar1, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
            }
        }
        iVar1 = iVar2 + 0x38;
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            (char*)s_Crc_times_005a7424, x, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        for (x = 1, y = 0x1998028; x < 9; y = y + 4, x = x + 1) {
            if (*(int*)(y + -0x7a214) != -1) {
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    (char*)s_p_005a7460, x, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    x, x, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    (char*)s___005a745c, x, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    *(int*)y, x, iVar1, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
            }
        }
        if (!this->syncStatus) {
            if (!this->DAT_GameHalted) {
                color = 0xffffff;
                textAddress = (char*)s_Game_in_sync_005a73e4;
            } else {
                color = 0xff;
                textAddress = (char*)s_GAME_SPLINTERED_005a73f4;
            }
        } else {
            color = 0xff;
            textAddress = (char*)s_GAME_SPLINTERED___Resyncing_005a7408;
        }
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            textAddress, x, iVar2 + 0x46, Text::TTA_LEFT, color, 0x11, FALSE, 0);
        iVar1 = iVar2 + 0x62;
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            (char*)s_CHI__005a73dc, x, iVar1, Text::TTA_LEFT, 0xffffff, 0x13, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameSynchronyState::instance.DAT_PlayerMatchTimes[this->currentPlayerSlotID * 0xc + 9] & 0xfff, x,
            iVar1, Text::TTA_LEFT, 0x80ff, 0x13, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            (char*)s_STR__005a73d4, x, iVar1, Text::TTA_LEFT, 0xffffff, 0x13, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameSynchronyState::instance.DAT_PlayerMatchTimes[this->currentPlayerSlotID * 0xc + 10] & 0xfff, x,
            iVar1, Text::TTA_LEFT, 0x80ff, 0x13, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            (char*)s_VEG__005a73cc, x, iVar1, Text::TTA_LEFT, 0xffffff, 0x13, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameSynchronyState::instance.DAT_PlayerMatchTimes[this->currentPlayerSlotID * 0xc + 0xb] & 0xfff, x,
            iVar1, Text::TTA_LEFT, 0x80ff, 0x13, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            (char*)s_TRI__005a73c4, x, iVar1, Text::TTA_LEFT, 0xffffff, 0x13, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameSynchronyState::instance.DAT_PlayerMatchTimes[this->currentPlayerSlotID * 0xc + 0xc] & 0xfff, x,
            iVar1, Text::TTA_LEFT, 0x80ff, 0x13, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            (char*)s_PLA__005a73bc, x, iVar1, Text::TTA_LEFT, 0xffffff, 0x13, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameSynchronyState::instance.DAT_PlayerMatchTimes[this->currentPlayerSlotID * 0xc + 0xd] & 0xfff, x,
            iVar1, Text::TTA_LEFT, 0x80ff, 0x13, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            (char*)s_GAM__005a73b4, x, iVar1, Text::TTA_LEFT, 0xffffff, 0x13, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameSynchronyState::instance.DAT_PlayerMatchTimes[this->currentPlayerSlotID * 0xc + 0xe] & 0xfff, x,
            iVar1, Text::TTA_LEFT, 0x80ff, 0x13, TRUE, 0);
        iVar1 = iVar2 + 0x70;
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            (char*)s_LAY__005a73ac, x, iVar1, Text::TTA_LEFT, 0xffffff, 0x13, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameSynchronyState::instance.DAT_PlayerMatchTimes[this->currentPlayerSlotID * 0xc + 0xf] & 0xfff, x,
            iVar1, Text::TTA_LEFT, 0x80ff, 0x13, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            (char*)s_FLY__005a73a4, x, iVar1, Text::TTA_LEFT, 0xffffff, 0x13, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameSynchronyState::instance.DAT_PlayerMatchTimes[this->currentPlayerSlotID * 0xc + 0x10] & 0xfff, x,
            iVar1, Text::TTA_LEFT, 0x80ff, 0x13, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            (char*)s_MOAT__005a739c, x, iVar1, Text::TTA_LEFT, 0xffffff, 0x13, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameSynchronyState::instance.DAT_PlayerMatchTimes[this->currentPlayerSlotID * 0xc + 0x11] & 0xfff, x,
            iVar1, Text::TTA_LEFT, 0x80ff, 0x13, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            (char*)s_TELE__005a7394, x, iVar1, Text::TTA_LEFT, 0xffffff, 0x13, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameSynchronyState::instance.DAT_PlayerMatchTimes[this->currentPlayerSlotID * 0xc + 0x12] & 0xfff, x,
            iVar1, Text::TTA_LEFT, 0x80ff, 0x13, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            (char*)s_PIDI__005a738c, x, iVar1, Text::TTA_LEFT, 0xffffff, 0x13, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameSynchronyState::instance.DAT_PlayerMatchTimes[this->currentPlayerSlotID * 0xc + 0x13] & 0xfff, x,
            iVar1, Text::TTA_LEFT, 0x80ff, 0x13, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            (char*)s_ZONE__005a7384, x, iVar1, Text::TTA_LEFT, 0xffffff, 0x13, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameSynchronyState::instance.DAT_PlayerMatchTimes[this->currentPlayerSlotID * 0xc + 0x14] & 0xfff, x,
            iVar1, Text::TTA_LEFT, 0x80ff, 0x13, TRUE, 0);
        iVar1 = iVar2 + 0x7e;
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            (char*)s_Chimps__005a7378, x, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_UnitsState::instance.unitCount, x, iVar1, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            (char*)s_Structs__005a736c, x, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_BuildingsState::instance.structCount, x, iVar1, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            (char*)s_id_count__005a7360, x, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameCore::instance.uniqueGameObjectTracker, x, iVar1, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            (char*)s_random_no__005a7354, x, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            (int)SEC_RNG::instance.currentNumber2, x, iVar1, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        iVar1 = iVar2 + 0x8c;
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            (char*)s_chore_latency__005a7344, x, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->commandDelay, x, iVar1, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            (char*)s_pending_chores__005a7330, x, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
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
            (char*)s_cl_time_diff__005a7320, x, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->clTimeDiff, x, iVar1, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            (char*)s_Clans__005a7318, x, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_TribesState::instance.clans, x, iVar1, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        iVar2 = iVar2 + 0xa8;
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            (char*)s_Battle_Level__005a7308, x, iVar2, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameCore::instance.battleLevel, x, iVar2, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            (char*)s___005a7304, x, iVar2, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameCore::instance.battleLevel2, x, iVar2, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            (char*)s_Multi_Op__005a72f8, iVar4, iVar2, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameSynchronyState::instance.currentGameMode, iVar4, iVar2, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            (char*)s_GT__005a72f0, iVar6, iVar2, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameCore::instance.gameMode_2, iVar6, iVar2, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
    }

}
}
