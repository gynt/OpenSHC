#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Text::TextAlignment;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00518C50
        void TroopValueState::renderAttackInfoDebugOverlay(int x, int y, int width, int height)
        {
            char text[1000];
            x += 2;

            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_Biggest_zone__005abb48, x, y, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_TroopValueState::instance.attackInfo.biggestZone, x, y, OpenSHC::Text::TTA_LEFT, 0x80ff, 0x12,
                TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_Start_zone__005abb38, x + 10, y, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_TroopValueState::instance.attackInfo.startZone, x + 10, y, OpenSHC::Text::TTA_LEFT, 0x80ff, 0x12,
                TRUE, 0);

            int rowY = y + 16;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_Scale_zone__005abb28, x, rowY, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_TroopValueState::instance.attackInfo.scaleZone, x, rowY, OpenSHC::Text::TTA_LEFT, 0x80ff, 0x12,
                TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_keep_POS__005abb1c, x + 10, rowY, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .keep.yEntry,
                x + 10, rowY, OpenSHC::Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);

            rowY = y + 32;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_nof_fpoints__005abb0c, x, rowY, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_TroopValueState::instance.attackInfo.nof_fpoints, x, rowY, OpenSHC::Text::TTA_LEFT, 0x80ff,
                0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_inv_count__005abb00, x + 10, rowY, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_TroopValueState::instance.attackInfo.currentAttackWaveSlot, x + 10, rowY, OpenSHC::Text::TTA_LEFT,
                0x80ff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_nof_tribes__005abaf0, x + 20, rowY, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                (char)DAT_TroopValueState::instance.attackInfo
                    .waveTribeCountThisTick[DAT_TroopValueState::instance.attackInfo.currentAttackWaveSlot],
                x + 20, rowY, OpenSHC::Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);

            rowY = y + 48;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_Start_con__005abae4, x, rowY, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_TroopValueState::instance.attackInfo.startCon, x, rowY, OpenSHC::Text::TTA_LEFT, 0x80ff, 0x12,
                TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_Keep_con__005abad8, x + 10, rowY, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_TroopValueState::instance.attackInfo.keepCon, x + 10, rowY, OpenSHC::Text::TTA_LEFT, 0x80ff, 0x12,
                TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_cas_dis__005abacc, x + 20, rowY, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_TroopValueState::instance.attackInfo.casDis, x + 20, rowY, OpenSHC::Text::TTA_LEFT, 0x80ff, 0x12,
                TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_zone_size__005abac0, x + 30, rowY, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_TroopValueState::instance.attackInfo.zoneSize, x + 30, rowY, OpenSHC::Text::TTA_LEFT, 0x80ff, 0x12,
                TRUE, 0);

            // The per-player siege target lists are stored for players 1..8 in playerInfo[0..7].
            MACRO_CALL(OpenSHC::OS_Func::_sprintf)(text, s_Hack_d_d_d__Scale_d_d_d__005aba94,
                DAT_TroopValueState::instance.attackInfo.playerInfo[DAT_TroopValueState::instance.attackInfo.attacker - 1]
                    .hack1,
                DAT_TroopValueState::instance.attackInfo.playerInfo[DAT_TroopValueState::instance.attackInfo.attacker - 1]
                    .hack2,
                DAT_TroopValueState::instance.attackInfo.playerInfo[DAT_TroopValueState::instance.attackInfo.attacker - 1]
                    .hack3,
                DAT_TroopValueState::instance.attackInfo.playerInfo[DAT_TroopValueState::instance.attackInfo.attacker - 1]
                    .scale1,
                DAT_TroopValueState::instance.attackInfo.playerInfo[DAT_TroopValueState::instance.attackInfo.attacker - 1]
                    .scale2,
                DAT_TroopValueState::instance.attackInfo.playerInfo[DAT_TroopValueState::instance.attackInfo.attacker - 1]
                    .scale3,
                DAT_TroopValueState::instance.attackInfo.playerInfo[DAT_TroopValueState::instance.attackInfo.attacker - 1]
                    .stone1);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                text, x, y + 64, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);

            MACRO_CALL(OpenSHC::OS_Func::_sprintf)(text, s_Town_d_d__Gate_d_d__Moat_d__005aba60,
                DAT_TroopValueState::instance.attackInfo.playerInfo[DAT_TroopValueState::instance.attackInfo.attacker - 1]
                    .town1,
                DAT_TroopValueState::instance.attackInfo.playerInfo[DAT_TroopValueState::instance.attackInfo.attacker - 1]
                    .town2,
                DAT_TroopValueState::instance.attackInfo.playerInfo[DAT_TroopValueState::instance.attackInfo.attacker - 1]
                    .gate1,
                DAT_TroopValueState::instance.attackInfo.playerInfo[DAT_TroopValueState::instance.attackInfo.attacker - 1]
                    .gate2,
                DAT_TroopValueState::instance.attackInfo.playerInfo[DAT_TroopValueState::instance.attackInfo.attacker - 1]
                    .moat1,
                DAT_TroopValueState::instance.attackInfo.playerInfo[DAT_TroopValueState::instance.attackInfo.attacker - 1]
                    .moat2,
                DAT_TroopValueState::instance.attackInfo.enemyLordTileCount,
                DAT_TroopValueState::instance.attackInfo.lordTargetsAvailable);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                text, x, y + 80, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);

            MACRO_CALL(OpenSHC::OS_Func::_sprintf)(text, s_High_d_d_d__Arch_d_d_d__P_005aba2c,
                DAT_TroopValueState::instance.attackInfo.high1, DAT_TroopValueState::instance.attackInfo.high2,
                DAT_TroopValueState::instance.attackInfo.high3, DAT_TroopValueState::instance.attackInfo.arch1,
                DAT_TroopValueState::instance.attackInfo.arch2, DAT_TroopValueState::instance.attackInfo.arch3,
                DAT_TroopValueState::instance.attackInfo.people1, DAT_TroopValueState::instance.attackInfo.peopleTargetCount,
                DAT_TroopValueState::instance.attackInfo.peopleTargetsAvailable);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                text, x, y + 96, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);

            MACRO_CALL(OpenSHC::OS_Func::_sprintf)(text, s_Wide_d_d_d__005aba1c,
                DAT_TroopValueState::instance.attackInfo.playerInfo[DAT_TroopValueState::instance.attackInfo.attacker - 1]
                    .wide1,
                DAT_TroopValueState::instance.attackInfo.playerInfo[DAT_TroopValueState::instance.attackInfo.attacker - 1]
                    .wide2,
                DAT_TroopValueState::instance.attackInfo.playerInfo[DAT_TroopValueState::instance.attackInfo.attacker - 1]
                    .wide3);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                text, x, y + 112, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);

            MACRO_CALL(OpenSHC::OS_Func::_sprintf)(text, s_Archer_points_d__Next_d_005aba00,
                DAT_TroopValueState::instance.attackInfo.archerPoints,
                DAT_TroopValueState::instance.attackInfo.archerPointsNext);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                text, x, y + 128, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);

            MACRO_CALL(OpenSHC::OS_Func::_sprintf)(text, s_Support_points_d__Next_d_005ab9e4,
                DAT_TroopValueState::instance.attackInfo.supportPoints,
                DAT_TroopValueState::instance.attackInfo.supportPointsNext);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                text, x, y + 144, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);

            MACRO_CALL(OpenSHC::OS_Func::_sprintf)(text, s_Tent_points_d__Next_d_005ab9c8,
                DAT_TroopValueState::instance.attackInfo.tentPoints, DAT_TroopValueState::instance.attackInfo.tentPointsNext);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                text, x, y + 160, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);

            MACRO_CALL(OpenSHC::OS_Func::_sprintf)(text, s_ai_troops__A_d_X_d_S_d_P_d_M_005ab988,
                DAT_TroopValueState::instance.attackInfo.aiTribeSizesPerTribeType.aiTroops_A,
                DAT_TroopValueState::instance.attackInfo.aiTribeSizesPerTribeType.aiTroops_X,
                DAT_TroopValueState::instance.attackInfo.aiTribeSizesPerTribeType.aiTroops_S,
                DAT_TroopValueState::instance.attackInfo.aiTribeSizesPerTribeType.aiTroops_P,
                DAT_TroopValueState::instance.attackInfo.aiTribeSizesPerTribeType.aiTroops_M,
                DAT_TroopValueState::instance.attackInfo.aiTribeSizesPerTribeType.aiTroops_S2,
                DAT_TroopValueState::instance.attackInfo.aiTribeSizesPerTribeType.aiTroops_K,
                DAT_TroopValueState::instance.attackInfo.aiTribeSizesPerTribeType.aiTroops_L,
                DAT_TroopValueState::instance.attackInfo.aiTribeSizesPerTribeType.aiTroops_E,
                DAT_TroopValueState::instance.attackInfo.aiTribeSizesPerTribeType.aiTroops_T);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                text, x, y + 176, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);

            MACRO_CALL(OpenSHC::OS_Func::_sprintf)(text, s_killed_d_lost_d_AI_troops_d_005ab968,
                DAT_GameState::instance.playerDataArray[1].troopsKilled,
                DAT_GameState::instance.playerDataArray[1].troopsLost, DAT_TroopValueState::instance.attackInfo.aiTroops);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                text, x, y + 192, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);

            MACRO_CALL(OpenSHC::OS_Func::_sprintf)(text, s_Points___d___d___d___d___d___d____005ab93c,
                DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[0],
                DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[1],
                DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[2],
                DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[3],
                DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[4],
                DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[5],
                DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[6],
                DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[7],
                DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[8]);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                text, x, y + 208, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        }

    }
}
}
