#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/AI/Tribes/AITribeType.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051BA30
        void TroopValueState::placeTunnelForEveryTunneler(int attackWaveThenLoopIdx)
        {
            int attackerPlayerID
                = (char)DAT_TroopValueState::instance.attackInfo.attackWavePlayerIDArray[attackWaveThenLoopIdx];
            int tunnelerCount = 0;
            if (attackerPlayerID == 0) {
                attackerPlayerID = 2;
            }
            if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CUSTOM_MAP
                && DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == OpenSHC::Map::MT_SIEGE) {
                attackerPlayerID = 2;
            }
            for (int i = 1; i < (int)DAT_UnitsState::instance.maxUnitCount; ++i) {
                if (DAT_UnitsState::instance.units[i].logicalState == ULS_NORMAL
                    && DAT_UnitsState::instance.units[i].owner == attackerPlayerID
                    && DAT_UnitsState::instance.units[i].dying == 0
                    && DAT_UnitsState::instance.units[i].unitType == UT_TUNNELER) {
                    tunnelerCount++;
                }
            }

            // collect the wave's tunneler tribes
            int tribeID = 1;
            DAT_TroopValueState::instance.attackInfo.tribeIDArraySize = 0;
            for (; tribeID < 1250; ++tribeID) {
                if (DAT_TribesState::instance.tribes[tribeID].tribeState != 0
                    && DAT_TribesState::instance.tribes[tribeID].owner == attackerPlayerID
                    && DAT_TribesState::instance.tribes[tribeID].attackWave == attackWaveThenLoopIdx
                    && DAT_TribesState::instance.tribes[tribeID].tribeType == OpenSHC::AI::Tribes::AITT_TUNNELERS) {
                    DAT_TroopValueState::instance.attackInfo
                        .tribeIDArray[DAT_TroopValueState::instance.attackInfo.tribeIDArraySize] = tribeID;
                    DAT_TroopValueState::instance.attackInfo.tribeIDArraySize++;
                }
            }
            if (DAT_TroopValueState::instance.attackInfo.tribeIDArraySize == 0) {
                return;
            }

            // empty them
            for (int i = 0; i < DAT_TroopValueState::instance.attackInfo.tribeIDArraySize; ++i) {
                tribeID = DAT_TroopValueState::instance.attackInfo.tribeIDArray[i];
                while (DAT_TribesState::instance.tribes[tribeID].size != 0) {
                    MACRO_CALL_MEMBER(TribesState_Func::popUnitFromTribe, DAT_TribesState::ptr)(tribeID);
                }
            }

            // one single-unit tribe and tunnel per tunneler
            int unitID = 0;
            for (attackWaveThenLoopIdx = 0; attackWaveThenLoopIdx < tunnelerCount; ++attackWaveThenLoopIdx) {
                int const newTribeID
                    = MACRO_CALL_MEMBER(TribesState_Func::createTribe, DAT_TribesState::ptr)(attackerPlayerID, 0);
                DAT_TribesState::instance.tribes[newTribeID].tribeType = OpenSHC::AI::Tribes::AITT_TUNNELERS;
                DAT_TribesState::instance.tribes[newTribeID].tribeBehaviorType = STBT_0x415;
                DAT_TribesState::instance.tribes[newTribeID].attackWave
                    = DAT_TribesState::instance.tribes[tribeID].attackWave;
                DAT_TribesState::instance.tribes[newTribeID].attackInfo_someCounter1
                    = DAT_TribesState::instance.tribes[tribeID].attackInfo_someCounter1;
                bool found = false;
                for (; unitID < (int)DAT_UnitsState::instance.maxUnitCount; ++unitID) {
                    if (DAT_UnitsState::instance.units[unitID].logicalState == ULS_NORMAL
                        && DAT_UnitsState::instance.units[unitID].owner == attackerPlayerID
                        && DAT_UnitsState::instance.units[unitID].dying == 0
                        && DAT_UnitsState::instance.units[unitID].unitType == UT_TUNNELER
                        && DAT_UnitsState::instance.units[unitID].tribeID == 0) {
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    return;
                }
                MACRO_CALL_MEMBER(TribesState_Func::addUnitToTribe, DAT_TribesState::ptr)(unitID, newTribeID);
                unitID++;
                if (unitID >= (int)DAT_UnitsState::instance.maxUnitCount) {
                    return;
                }
                MACRO_CALL_MEMBER(TroopValueState_Func::placeTunnelEntrances, this)(newTribeID);
            }
        }

    }
}
}
