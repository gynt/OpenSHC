#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/AI/Tribes/AITribeType.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_AttackInfoDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Commands::MappersEnum;
        using OpenSHC::Map::Units::UnitInstructionType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051B710
        void TroopValueState::placeSiegeTentsAndAssignEngineers(int attackWave, int useAttackAngle)
        {
            int attackerPlayerID = (char)DAT_TroopValueState::instance.attackInfo.attackWavePlayerIDArray[attackWave];
            if (attackerPlayerID == 0) {
                attackerPlayerID = 2;
            }
            if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CUSTOM_MAP
                && DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == OpenSHC::Map::MT_SIEGE) {
                attackerPlayerID = 2;
            }

            // siege engine types 0..4, then type 8
            int engineersNeeded = 0;
            DAT_TroopValueState::instance.attackInfo.createTribeAmount = 0;
            for (uint type = 0; type <= 4; ++type) {
                MappersEnum const buildingType = DAT_AttackInfoDefinedData::instance.siegeEngineMapperTypes[type];
                int const engineers = DAT_AttackInfoDefinedData::instance.engineersPerSiegeEngine[type];
                int const count
                    = (char)DAT_TroopValueState::instance.attackInfo.waveSiegeEngineCounts[attackWave][type];
                for (int i = 0; i < count; ++i) {
                    DAT_TroopValueState::instance.attackInfo
                        .siegeTentPlan[DAT_TroopValueState::instance.attackInfo.createTribeAmount]
                        .engineerBuildingType = buildingType;
                    DAT_TroopValueState::instance.attackInfo
                        .siegeTentPlan[DAT_TroopValueState::instance.attackInfo.createTribeAmount]
                        .engineerCount = engineers;
                    DAT_TroopValueState::instance.attackInfo.createTribeAmount++;
                    engineersNeeded += engineers;
                    if (DAT_TroopValueState::instance.attackInfo.createTribeAmount >= 250) {
                        break;
                    }
                }
            }
            int const count = (char)DAT_TroopValueState::instance.attackInfo.waveSiegeEngineCounts[attackWave][8];
            MappersEnum const buildingType = DAT_AttackInfoDefinedData::instance.siegeEngineMapperTypes[8];
            int const engineers = DAT_AttackInfoDefinedData::instance.engineersPerSiegeEngine[8];
            for (int i = 0; i < count; ++i) {
                if (DAT_TroopValueState::instance.attackInfo.createTribeAmount >= 250) {
                    break;
                }
                DAT_TroopValueState::instance.attackInfo
                    .siegeTentPlan[DAT_TroopValueState::instance.attackInfo.createTribeAmount]
                    .engineerBuildingType = buildingType;
                DAT_TroopValueState::instance.attackInfo
                    .siegeTentPlan[DAT_TroopValueState::instance.attackInfo.createTribeAmount]
                    .engineerCount = engineers;
                DAT_TroopValueState::instance.attackInfo.createTribeAmount++;
                engineersNeeded += engineers;
            }

            // collect the wave's engineer tribes
            int tribeID = 1;
            DAT_TroopValueState::instance.attackInfo.tribeIDArraySize = 0;
            for (; tribeID < 1250; ++tribeID) {
                if (DAT_TribesState::instance.tribes[tribeID].tribeState != 0
                    && DAT_TribesState::instance.tribes[tribeID].owner == attackerPlayerID
                    && DAT_TribesState::instance.tribes[tribeID].attackWave == attackWave
                    && DAT_TribesState::instance.tribes[tribeID].tribeType == OpenSHC::AI::Tribes::AITT_ENGINEERS) {
                    DAT_TroopValueState::instance.attackInfo
                        .tribeIDArray[DAT_TroopValueState::instance.attackInfo.tribeIDArraySize] = tribeID;
                    DAT_TroopValueState::instance.attackInfo.tribeIDArraySize++;
                }
            }
            if (DAT_TroopValueState::instance.attackInfo.tribeIDArraySize == 0) {
                return;
            }

            // take the needed engineers out of them
            for (int i = 0; i < DAT_TroopValueState::instance.attackInfo.tribeIDArraySize; ++i) {
                tribeID = DAT_TroopValueState::instance.attackInfo.tribeIDArray[i];
                for (; DAT_TribesState::instance.tribes[tribeID].size != 0; engineersNeeded--) {
                    if (engineersNeeded <= 0) {
                        break;
                    }
                    MACRO_CALL_MEMBER(TribesState_Func::popUnitFromTribe, DAT_TribesState::ptr)(tribeID);
                }
            }

            // one new engineer tribe per planned tent
            int unitID = 0;
            for (attackWave = 0; attackWave < DAT_TroopValueState::instance.attackInfo.createTribeAmount;
                ++attackWave) {
                int engineersLeft = DAT_TroopValueState::instance.attackInfo.siegeTentPlan[attackWave].engineerCount;
                int const newTribeID = MACRO_CALL_MEMBER(TribesState_Func::createTribe, DAT_TribesState::ptr)(
                    DAT_TribesState::instance.tribes[tribeID].owner, 0);
                DAT_TribesState::instance.tribes[newTribeID].tribeType = OpenSHC::AI::Tribes::AITT_ENGINEERS;
                DAT_TribesState::instance.tribes[newTribeID].tribeBehaviorType
                    = STBT_0x410_SIEGE_EQUIPMENT_CONSTRUCTION;
                DAT_TribesState::instance.tribes[newTribeID].attackWave
                    = DAT_TribesState::instance.tribes[tribeID].attackWave;
                DAT_TribesState::instance.tribes[newTribeID].attackInfo_someCounter1
                    = DAT_TribesState::instance.tribes[tribeID].attackInfo_someCounter1;
                bool done = false;
                for (; unitID < (int)DAT_UnitsState::instance.maxUnitCount; ++unitID) {
                    if (DAT_UnitsState::instance.units[unitID].logicalState == ULS_NORMAL
                        && DAT_UnitsState::instance.units[unitID].owner == attackerPlayerID
                        && DAT_UnitsState::instance.units[unitID].dying == 0
                        && DAT_UnitsState::instance.units[unitID].unitType == UT_E_ENGINEER
                        && DAT_UnitsState::instance.units[unitID].tribeID == 0) {
                        MACRO_CALL_MEMBER(TribesState_Func::addUnitToTribe, DAT_TribesState::ptr)(unitID, newTribeID);
                        engineersLeft--;
                        if (engineersLeft <= 0) {
                            done = true;
                            break;
                        }
                    }
                }
                if (!done) {
                    return;
                }
                unitID++;
                if (unitID >= (int)DAT_UnitsState::instance.maxUnitCount) {
                    return;
                }
                if (useAttackAngle != 0) {
                    MACRO_CALL_MEMBER(TroopValueState_Func::placeSiegeTentAtAttackAngle, this)(newTribeID,
                        DAT_TroopValueState::instance.attackInfo.siegeTentPlan[attackWave].engineerBuildingType);
                } else {
                    MACRO_CALL_MEMBER(TroopValueState_Func::placeSiegeTentOrTunnelAtSuitableLocationAndAssignEngineers,
                        this)(newTribeID,
                        DAT_TroopValueState::instance.attackInfo.siegeTentPlan[attackWave].engineerBuildingType, 0,
                        UIT_CONSTRUCT_SIEGE_EQUIPMENTOIL_DUTYENGINEERRELATED);
                }
            }
        }

    }
}
}
