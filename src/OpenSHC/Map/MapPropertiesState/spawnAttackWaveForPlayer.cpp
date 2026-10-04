#include "../../Map.func.hpp"
#include "../MapPropertiesState.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {

    using Map::Units::UnitType;

    /*
      Allocates a new attack wave slot (inv_count, wrapping at 50), maps unit type codes   (param_2/param_4) to internal
      unit type enums and group sizes, scales quantity (param_3/param_5)   by difficulty (50/100/140/200%), then
      distributes units across map edge signpost positions via   TribesState::FUN_00522f70. Handles both primary and
      secondary unit types. Siege engines and   special units (catapult, trebuchet, tower, etc.) are scored separately
      rather than spawned   directly.      renamed by: Claude Sonnet 4.6
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004BC1C0
    void MapPropertiesState::spawnAttackWaveForPlayer(
        int param_1, int param_2, int param_3, int param_4, int param_5, undefined4 param_6)
    {
        byte(*pabVar1)[10];
        byte* pbVar2;
        int iVar3;
        int iVar4;
        int iVar5;
        char cVar6;
        int iVar7;
        int iVar8;
        UnitType UVar9;
        int local_10;
        int local_c;
        int local_8;
        iVar3 = DAT_GameState::instance.mapAndTime.signpostsMapEdgeDataCounter;
        DAT_TroopValueState::instance.attackInfo.inv_count = DAT_TroopValueState::instance.attackInfo.inv_count + 1;
        local_c = 0;
        if (0x31 < DAT_TroopValueState::instance.attackInfo.inv_count) {
            DAT_TroopValueState::instance.attackInfo.inv_count = 1;
        }
        MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::initializeAttackWaveSlot,
            DAT_TroopValueState::ptr)(DAT_TroopValueState::instance.attackInfo.inv_count, 0);
        local_8 = 0;
        DAT_TroopValueState::instance.attackInfo
            .attackWavePlayerIDArray[DAT_TroopValueState::instance.attackInfo.inv_count] = (byte)param_1;
        iVar7 = param_1;
        iVar8 = param_1;
        UVar9 = (Map::Units::UnitType)param_1;
        do {
            iVar4 = param_2;
            iVar5 = param_3;
            if ((local_8 != 0) && (iVar4 = param_4, iVar5 = param_5, param_4 < 1)) {}
            switch (iVar4) {
            case 5:
                iVar8 = 2;
                UVar9 = Map::Units::UT_TUNNELER;
                break;
            default:
                goto switchD_004bc254_caseD_6;
            case 0x16:
                iVar8 = 3;
                UVar9 = Map::Units::UT_E_ARCHER;
                break;
            case 0x17:
                iVar8 = 7;
                UVar9 = Map::Units::UT_E_XBOW;
                break;
            case 0x18:
                iVar8 = 5;
                UVar9 = Map::Units::UT_E_SPEAR;
                break;
            case 0x19:
                iVar8 = 6;
                UVar9 = Map::Units::UT_E_PIKE;
                break;
            case 0x1a:
                iVar8 = 9;
                UVar9 = Map::Units::UT_E_MACE;
                break;
            case 0x1b:
                iVar8 = 8;
                UVar9 = Map::Units::UT_E_SWORD;
                break;
            case 0x1c:
                iVar8 = 10;
                UVar9 = Map::Units::UT_E_KNIGHT;
                iVar7 = 10;
                goto switchD_004bc254_caseD_6;
            case 0x1d:
                iVar8 = 4;
                UVar9 = Map::Units::UT_E_LADDER;
                break;
            case 0x1e:
                iVar8 = 0xb;
                UVar9 = Map::Units::UT_E_ENGINEER;
                break;
            case 0x25:
                iVar8 = 0xc;
                UVar9 = Map::Units::UT_E_MONK;
                break;
            case 0x27:
                iVar8 = 0x16;
                UVar9 = Map::Units::UT_S_CATAPULT;
                break;
            case 0x28:
                iVar8 = 0x17;
                UVar9 = Map::Units::UT_S_TREBUCHET;
                break;
            case 0x3a:
                iVar8 = 0x14;
                UVar9 = Map::Units::UT_S_TOWER;
                break;
            case 0x3b:
                iVar8 = 0x13;
                UVar9 = Map::Units::UT_S_BATTERINGRAM;
                break;
            case 0x3c:
                iVar8 = 0x15;
                UVar9 = Map::Units::UT_S_SHIELD;
                break;
            case 0x46:
                iVar8 = 0x19;
                UVar9 = Map::Units::UT_A_ARCHER;
                break;
            case 0x47:
                iVar8 = 0x1a;
                UVar9 = Map::Units::UT_A_SLAVE;
                iVar7 = 0x14;
                goto switchD_004bc254_caseD_6;
            case 0x48:
                iVar8 = 0x1b;
                UVar9 = Map::Units::UT_A_SLINGER;
                iVar7 = 0x14;
                goto switchD_004bc254_caseD_6;
            case 0x49:
                iVar8 = 0x1c;
                UVar9 = Map::Units::UT_A_ASSASSIN;
                iVar7 = 2;
                goto switchD_004bc254_caseD_6;
            case 0x4a:
                iVar8 = 0x1d;
                UVar9 = Map::Units::UT_A_HARCHER;
                break;
            case 0x4b:
                iVar8 = 0x1e;
                UVar9 = Map::Units::UT_A_SWORDSMAN;
                iVar7 = 8;
                goto switchD_004bc254_caseD_6;
            case 0x4c:
                iVar8 = 0x1f;
                UVar9 = Map::Units::UT_A_FIRETHROWER;
                iVar7 = 4;
                goto switchD_004bc254_caseD_6;
            case 0x4d:
                iVar8 = 0x18;
                UVar9 = Map::Units::UT_S_FBALLISTA;
            }
            iVar7 = 10;
        switchD_004bc254_caseD_6:
            iVar4 = 100;
            if (DAT_GameState::instance.mapAndTime.difficulty == 0) {
                iVar4 = 0x32;
            } else if (DAT_GameState::instance.mapAndTime.difficulty == 2) {
                iVar4 = 0x8c;
            } else if (DAT_GameState::instance.mapAndTime.difficulty == 3) {
                iVar4 = 200;
            }
            iVar4 = (iVar4 * iVar5) / 100;
            cVar6 = (char)iVar4;
            if (iVar8 == 0x16) {
                pabVar1 = DAT_TroopValueState::instance.attackInfo.someSinglePlayerScore
                    + DAT_TroopValueState::instance.attackInfo.inv_count;
                (*pabVar1)[0] = (*pabVar1)[0] + cVar6;
            } else if (iVar8 == 0x17) {
                pbVar2 = DAT_TroopValueState::instance.attackInfo
                             .someSinglePlayerScore[DAT_TroopValueState::instance.attackInfo.inv_count]
                    + 1;
                *pbVar2 = *pbVar2 + cVar6;
            } else if (iVar8 == 0x13) {
                pbVar2 = DAT_TroopValueState::instance.attackInfo
                             .someSinglePlayerScore[DAT_TroopValueState::instance.attackInfo.inv_count]
                    + 2;
                *pbVar2 = *pbVar2 + cVar6;
            } else if (iVar8 == 0x14) {
                pbVar2 = DAT_TroopValueState::instance.attackInfo
                             .someSinglePlayerScore[DAT_TroopValueState::instance.attackInfo.inv_count]
                    + 3;
                *pbVar2 = *pbVar2 + cVar6;
            } else if (iVar8 == 0x15) {
                pbVar2 = DAT_TroopValueState::instance.attackInfo
                             .someSinglePlayerScore[DAT_TroopValueState::instance.attackInfo.inv_count]
                    + 4;
                *pbVar2 = *pbVar2 + cVar6;
            } else if (iVar8 == 0x18) {
                pbVar2 = DAT_TroopValueState::instance.attackInfo
                             .someSinglePlayerScore[DAT_TroopValueState::instance.attackInfo.inv_count]
                    + 8;
                *pbVar2 = *pbVar2 + cVar6;
            } else {
                local_10 = iVar4 / (iVar4 / iVar7 + 1);
                while (0 < iVar4) {
                    if (iVar4 < local_10) {
                        local_10 = iVar4;
                    }
                    iVar5 = (&DAT_TroopValueState::instance.attackInfo
                            .unknownSignpostRelatedArray)[DAT_TroopValueState::instance.attackInfo.inv_count];
                    MACRO_CALL_MEMBER(
                        Map::Units::TribesState_Func::spawnUnitsForAITribe, DAT_TribesState::ptr)(iVar8,
                        DAT_GameState::instance.mapAndTime.signpostsMapEdge[iVar5][local_c].x,
                        DAT_GameState::instance.mapAndTime.signpostsMapEdge[iVar5][local_c].y, param_1, UVar9, local_10,
                        param_6);
                    iVar4 = iVar4 - local_10;
                    local_c = local_c + 1;
                    if (iVar3 <= local_c) {
                        local_c = 0;
                    }
                }
            }
            local_8 = local_8 + 1;
            if (1 < local_8) {}
        } while (true);
    }

}
}
