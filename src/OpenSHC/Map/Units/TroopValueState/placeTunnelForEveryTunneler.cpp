#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/AI/Tribes/AITribeType.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::AI::Tribes::AITribeType;
        using OpenSHC::Game::GameMode2;
        using OpenSHC::Map::MapType2;
        using OpenSHC::Map::Units::SomeTribeBehaviorType;
        using OpenSHC::Map::Units::UnitLogicState;
        using OpenSHC::Map::Units::UnitType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051BA30
        void TroopValueState::placeTunnelForEveryTunneler(int attackWave)
        {
            short sVar1;
            uint uVar2;
            Unit* psVar3;
            Tribe* piVar3;
            int _tribe;
            Unit* psVar4;
            int iVar3;
            int iVar4;
            int _nTunnelers;
            int iVar5;
            uint unitID;
            int local_c;
            int _nTunnels;
            local_c = (int)(char)DAT_TroopValueState::instance.attackInfo.attackWavePlayerIDArray[attackWave];
            _nTunnelers = 0;
            _nTunnels = 0;
            if (local_c == 0) {
                local_c = 2;
            }
            if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_BUILDERUnk)
                && (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == OpenSHC::Map::MT_SIEGE)) {
                local_c = 2;
            }
            if (1 < (int)DAT_UnitsState::instance.maxUnitCount) {
                psVar3 = &DAT_UnitsState::instance.units[1];
                iVar3 = DAT_UnitsState::instance.maxUnitCount - 1;
                do {
                    if ((((psVar3->logicalState == OpenSHC::Map::Units::ULS_NORMAL) && (psVar3->owner == local_c))
                            && (psVar3->dying == 0))
                        && (psVar3->unitType == OpenSHC::Map::Units::UT_TUNNELER)) {
                        _nTunnelers = _nTunnelers + 1;
                    }
                    psVar3 = psVar3 + 0x248;
                    iVar3 = iVar3 + -1;
                    _nTunnels = _nTunnelers;
                } while (iVar3 != 0);
            }
            iVar4 = 0;
            iVar3 = 1;
            DAT_TroopValueState::instance.attackInfo.tribeIDArraySize = 0;
            piVar3 = &DAT_TribesState::instance.tribes[1];
            do {
                if (((piVar3->tribeState != 0) && (piVar3->owner == local_c))
                    && ((piVar3->attackWave == attackWave
                        && (piVar3->tribeType == OpenSHC::AI::Tribes::AITT_TUNNELERS)))) {
                    DAT_TroopValueState::instance.attackInfo.tribeIDArray[iVar4] = iVar3;
                    iVar4 = DAT_TroopValueState::instance.attackInfo.tribeIDArraySize + 1;
                    DAT_TroopValueState::instance.attackInfo.tribeIDArraySize = iVar4;
                }
                piVar3 = piVar3 + 0xcd;
                iVar3 = iVar3 + 1;
            } while ((int)piVar3 < 0x176238c);
            if (iVar4 != 0) {
                iVar5 = 0;
                if (0 < iVar4) {
                    do {
                        iVar3 = DAT_TroopValueState::instance.attackInfo.tribeIDArray[iVar5];
                        sVar1 = DAT_TribesState::instance.tribes[iVar3].size;
                        while (sVar1 != 0) {
                            MACRO_CALL_MEMBER(
                                OpenSHC::Map::Units::TribesState_Func::popUnitFromTribe, DAT_TribesState::ptr)(iVar3);
                            iVar4 = DAT_TroopValueState::instance.attackInfo.tribeIDArraySize;
                            sVar1 = DAT_TribesState::instance.tribes[iVar3].size;
                        }
                        iVar5 = iVar5 + 1;
                    } while (iVar5 < iVar4);
                }
                unitID = 0;
                attackWave = 0;
                if (0 < _nTunnels) {
                    do {
                        _tribe = MACRO_CALL_MEMBER(
                            OpenSHC::Map::Units::TribesState_Func::createTribe, DAT_TribesState::ptr)(local_c, 0);
                        DAT_TribesState::instance.tribes[_tribe].tribeType = OpenSHC::AI::Tribes::AITT_TUNNELERS;
                        DAT_TribesState::instance.tribes[_tribe].tribeBehaviorType = OpenSHC::Map::Units::STBT_0x415;
                        DAT_TribesState::instance.tribes[_tribe].attackWave
                            = DAT_TribesState::instance.tribes[iVar3].attackWave;
                        uVar2 = DAT_UnitsState::instance.maxUnitCount;
                        DAT_TribesState::instance.tribes[_tribe].attackInfo_someCounter1
                            = DAT_TribesState::instance.tribes[iVar3].attackInfo_someCounter1;
                        if ((int)uVar2 <= (int)unitID) {}
                        psVar4 = &DAT_UnitsState::instance.units[unitID];
                        while (((psVar4->logicalState != OpenSHC::Map::Units::ULS_NORMAL || (psVar4->owner != local_c))
                            || ((psVar4->dying != 0
                                || ((psVar4->unitType != OpenSHC::Map::Units::UT_TUNNELER
                                    || (psVar4->tribeID != 0))))))) {
                            unitID = unitID + 1;
                            psVar4 = psVar4 + 0x248;
                            if ((int)uVar2 <= (int)unitID) {}
                        }
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::addUnitToTribe, DAT_TribesState::ptr)(
                            unitID, _tribe);
                        unitID = unitID + 1;
                        if ((int)DAT_UnitsState::instance.maxUnitCount <= (int)unitID) {}
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TroopValueState_Func::placeTunnelEntrances, this)(
                            _tribe);
                        attackWave = attackWave + 1;
                    } while (attackWave < _nTunnels);
                }
            }
        }

    }
}
}
