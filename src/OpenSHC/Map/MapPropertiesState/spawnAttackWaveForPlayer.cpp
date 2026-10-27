#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/AI/Tribes/AITribeType.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {

    using namespace OpenSHC::AI::Tribes;
    using namespace OpenSHC::Map::Units;

    // tribeKind / unitType / maxGroupSize start as playerID (0x4BC208..0x4BC214): an unknown type code keeps them.
    // FUNCTION: STRONGHOLDCRUSADER 0x004BC1C0
    void MapPropertiesState::spawnAttackWaveForPlayer(
        int playerID, int unitType1, int count1, int unitType2, int count2, undefined4 calcOwnerPlayerIndex)
    {
        int signpostCount = DAT_GameState::instance.mapAndTime.signpostsMapEdgeDataCounter;
        int signpostSlot = 0;
        DAT_TroopValueState::instance.attackInfo.currentAttackWaveSlot += 1;
        if (DAT_TroopValueState::instance.attackInfo.currentAttackWaveSlot >= 50) {
            DAT_TroopValueState::instance.attackInfo.currentAttackWaveSlot = 1;
        }
        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TroopValueState_Func::initializeAttackWaveSlot,
            DAT_TroopValueState::ptr)(DAT_TroopValueState::instance.attackInfo.currentAttackWaveSlot, 0);
        DAT_TroopValueState::instance.attackInfo
            .attackWavePlayerIDArray[DAT_TroopValueState::instance.attackInfo.currentAttackWaveSlot]
            = (byte)playerID;

        int unitType = playerID;
        int maxGroupSize = playerID;
        int tribeKind = playerID;
        for (int pass = 0; pass < 2; ++pass) {
            int typeCode;
            int count;
            if (pass == 0) {
                typeCode = unitType1;
                count = count1;
            }
            else {
                if (unitType2 <= 0) {
                    return;
                }
                typeCode = unitType2;
                count = count2;
            }
            switch (typeCode) {
            case UT_E_ARCHER:
                tribeKind = AITT_ARCHERS;
                unitType = UT_E_ARCHER;
                maxGroupSize = 10;
                break;
            case UT_E_XBOW:
                tribeKind = AITT_CROSSBOWMEN;
                unitType = UT_E_XBOW;
                maxGroupSize = 10;
                break;
            case UT_E_SPEAR:
                tribeKind = AITT_SPEARMEN;
                unitType = UT_E_SPEAR;
                maxGroupSize = 10;
                break;
            case UT_E_PIKE:
                tribeKind = AITT_PIKEMEN;
                unitType = UT_E_PIKE;
                maxGroupSize = 10;
                break;
            case UT_E_MACE:
                tribeKind = AITT_MACEMEN;
                unitType = UT_E_MACE;
                maxGroupSize = 10;
                break;
            case UT_E_SWORD:
                tribeKind = AITT_SWORDSMEN;
                unitType = UT_E_SWORD;
                maxGroupSize = 10;
                break;
            case UT_E_KNIGHT:
                tribeKind = AITT_KNIGHTS;
                unitType = UT_E_KNIGHT;
                maxGroupSize = 10;
                break;
            case UT_E_LADDER:
                tribeKind = AITT_LADDERMEN;
                unitType = UT_E_LADDER;
                maxGroupSize = 10;
                break;
            case UT_E_ENGINEER:
                tribeKind = AITT_ENGINEERS;
                unitType = UT_E_ENGINEER;
                maxGroupSize = 10;
                break;
            case UT_S_CATAPULT:
                tribeKind = AITT_CATAPULTS;
                unitType = UT_S_CATAPULT;
                maxGroupSize = 10;
                break;
            case UT_S_TREBUCHET:
                tribeKind = AITT_TREBUCHETS;
                unitType = UT_S_TREBUCHET;
                maxGroupSize = 10;
                break;
            case UT_S_BATTERINGRAM:
                tribeKind = AITT_BATTERING_RAMS;
                unitType = UT_S_BATTERINGRAM;
                maxGroupSize = 10;
                break;
            case UT_S_TOWER:
                tribeKind = AITT_SIEGE_TOWERS;
                unitType = UT_S_TOWER;
                maxGroupSize = 10;
                break;
            case UT_S_SHIELD:
                tribeKind = AITT_PORTABLE_SHIELDS;
                unitType = UT_S_SHIELD;
                maxGroupSize = 10;
                break;
            case UT_E_MONK:
                tribeKind = AITT_MONKS;
                unitType = UT_E_MONK;
                maxGroupSize = 10;
                break;
            case UT_TUNNELER:
                tribeKind = AITT_TUNNELERS;
                unitType = UT_TUNNELER;
                maxGroupSize = 10;
                break;
            case UT_A_ARCHER:
                tribeKind = AITT_ARAB_ARCHERS;
                unitType = UT_A_ARCHER;
                maxGroupSize = 10;
                break;
            case UT_A_SLAVE:
                tribeKind = AITT_SLAVES;
                unitType = UT_A_SLAVE;
                maxGroupSize = 20;
                break;
            case UT_A_SLINGER:
                tribeKind = AITT_SLINGERS;
                unitType = UT_A_SLINGER;
                maxGroupSize = 20;
                break;
            case UT_A_ASSASSIN:
                tribeKind = AITT_ASSASSINS;
                unitType = UT_A_ASSASSIN;
                maxGroupSize = 2;
                break;
            case UT_A_HARCHER:
                tribeKind = AITT_HORSE_ARCHERS;
                unitType = UT_A_HARCHER;
                maxGroupSize = 10;
                break;
            case UT_A_SWORDSMAN:
                tribeKind = AITT_ARAB_SWORDSMEN;
                unitType = UT_A_SWORDSMAN;
                maxGroupSize = 8;
                break;
            case UT_A_FIRETHROWER:
                tribeKind = AITT_FIRE_THROWERS;
                unitType = UT_A_FIRETHROWER;
                maxGroupSize = 4;
                break;
            case UT_S_FBALLISTA:
                tribeKind = AITT_FIRE_BALLISTAS;
                unitType = UT_S_FBALLISTA;
                maxGroupSize = 10;
                break;
            }

            int percent = 100;
            switch (DAT_GameState::instance.mapAndTime.difficulty) {
            case 0:
                percent = 50;
                break;
            case 2:
                percent = 140;
                break;
            case 3:
                percent = 200;
                break;
            }
            count = percent * count / 100;

            if (tribeKind == AITT_CATAPULTS) {
                DAT_TroopValueState::instance.attackInfo
                    .waveSiegeEngineCounts[DAT_TroopValueState::instance.attackInfo.currentAttackWaveSlot][0]
                    += (byte)count;
            }
            else if (tribeKind == AITT_TREBUCHETS) {
                DAT_TroopValueState::instance.attackInfo
                    .waveSiegeEngineCounts[DAT_TroopValueState::instance.attackInfo.currentAttackWaveSlot][1]
                    += (byte)count;
            }
            else if (tribeKind == AITT_BATTERING_RAMS) {
                DAT_TroopValueState::instance.attackInfo
                    .waveSiegeEngineCounts[DAT_TroopValueState::instance.attackInfo.currentAttackWaveSlot][2]
                    += (byte)count;
            }
            else if (tribeKind == AITT_SIEGE_TOWERS) {
                DAT_TroopValueState::instance.attackInfo
                    .waveSiegeEngineCounts[DAT_TroopValueState::instance.attackInfo.currentAttackWaveSlot][3]
                    += (byte)count;
            }
            else if (tribeKind == AITT_PORTABLE_SHIELDS) {
                DAT_TroopValueState::instance.attackInfo
                    .waveSiegeEngineCounts[DAT_TroopValueState::instance.attackInfo.currentAttackWaveSlot][4]
                    += (byte)count;
            }
            else if (tribeKind == AITT_FIRE_BALLISTAS) {
                DAT_TroopValueState::instance.attackInfo
                    .waveSiegeEngineCounts[DAT_TroopValueState::instance.attackInfo.currentAttackWaveSlot][8]
                    += (byte)count;
            }
            else {
                int groupSize = count / (count / maxGroupSize + 1);
                while (count > 0) {
                    if (groupSize > count) {
                        groupSize = count;
                    }
                    int signpostSet = (&DAT_TroopValueState::instance.attackInfo.attackWaveSignpostIndex)
                        [DAT_TroopValueState::instance.attackInfo.currentAttackWaveSlot];
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::spawnUnitsForAITribe,
                        DAT_TribesState::ptr)(tribeKind,
                        DAT_GameState::instance.mapAndTime.signpostsMapEdge[signpostSet][signpostSlot].x,
                        DAT_GameState::instance.mapAndTime.signpostsMapEdge[signpostSet][signpostSlot].y, playerID,
                        (UnitType)unitType, groupSize, calcOwnerPlayerIndex);
                    count -= groupSize;
                    signpostSlot += 1;
                    if (signpostSlot >= signpostCount) {
                        signpostSlot = 0;
                    }
                }
            }
        }
    }

}
}
