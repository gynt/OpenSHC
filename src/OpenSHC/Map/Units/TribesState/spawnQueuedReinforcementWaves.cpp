#include "../TribesState.func.hpp"

#include "OpenSHC/Game/GameModeInt.hpp"
#include "OpenSHC/Game/TrailType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_SH1_SiegeAdvancedMode.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // The troop queue is the 20 dwords of mapAndTime.siegeInformation (0x117CE50); the skirmish queue is
        // mapAndTime.playerQueuedTroops read as dwords [playerID * 20 + kind] (0x11BC68C, typed byte[80] in the
        // header). Only updateTribeUnitAssignments runs on 'this' (ecx untouched at 0x5274A1); every spawn call and
        // behaviorTickCounter write uses the global DAT_TribesState (ecx = 0x1667F78, 0x1667FCE). Queue kinds
        // without a case (7 in missions/skirmish, 18/19 everywhere) keep the previous tribe/unit type.
        // FUNCTION: STRONGHOLDCRUSADER 0x00527440
        void TribesState::spawnQueuedReinforcementWaves()
        {
            int tribeType = 0;
            int spawnedSkirmishBatch = 0;
            UnitType unitType = UT_NONE;
            int destinationIndex = 0;
            int spawnedMissionBatch = 0;
            if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                return;
            }
            if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY
                && DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_CUSTOM_MAP
                && DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_CRUSADER_TUTORIAL
                && DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .keep.id
                    <= 0) {
                return;
            }
            if (DAT_GameState::instance.mapAndTime.reinforcementSpawnTimer < 0) {
                return;
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::updateTribeUnitAssignments, this)();
            if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_CUSTOM_MAP
                && DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_CRUSADER_TUTORIAL) {
                if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
                    if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER
                        || DAT_GameState::instance.mapAndTime.skirmishNoRushTicksLeft == 0) {
                        ++DAT_GameState::instance.mapAndTime.reinforcementSpawnTimer;
                        int interval = 200;
                        if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SKIRMISH_AND_MULTIPLAYER
                            && DAT_GameCore::instance.isSkirmishTrail == TRUE
                            && DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_EXTREME) {
                            interval = 0x32;
                        }
                        if (DAT_GameState::instance.mapAndTime.reinforcementSpawnTimer > interval) {
                            DAT_GameState::instance.mapAndTime.reinforcementSpawnTimer = 0;
                            int queueOffset = 20;
                            for (int playerID = 1; playerID < 9; ++playerID) {
                                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] != -1
                                    || DAT_GameSynchronyState::instance.currentAIArray[playerID] != 0) {
                                    for (int kind = 0; kind < 20; ++kind) {
                                        if (kind == 7) {
                                            kind = 8;
                                        }
                                        if (((int*)DAT_GameState::instance.mapAndTime.playerQueuedTroops)[queueOffset + kind]
                                            != 0) {
                                            switch (kind) {
                                            case 0:
                                                tribeType = OpenSHC::AI::Tribes::AITT_ARCHERS;
                                                unitType = UT_E_ARCHER;
                                                break;
                                            case 1:
                                                tribeType = OpenSHC::AI::Tribes::AITT_CROSSBOWMEN;
                                                unitType = UT_E_XBOW;
                                                break;
                                            case 2:
                                                tribeType = OpenSHC::AI::Tribes::AITT_SPEARMEN;
                                                unitType = UT_E_SPEAR;
                                                break;
                                            case 3:
                                                tribeType = OpenSHC::AI::Tribes::AITT_PIKEMEN;
                                                unitType = UT_E_PIKE;
                                                break;
                                            case 4:
                                                tribeType = OpenSHC::AI::Tribes::AITT_MACEMEN;
                                                unitType = UT_E_MACE;
                                                break;
                                            case 5:
                                                tribeType = OpenSHC::AI::Tribes::AITT_SWORDSMEN;
                                                unitType = UT_E_SWORD;
                                                break;
                                            case 6:
                                                tribeType = OpenSHC::AI::Tribes::AITT_KNIGHTS;
                                                unitType = UT_E_KNIGHT;
                                                break;
                                            case 8:
                                                tribeType = OpenSHC::AI::Tribes::AITT_ENGINEERS;
                                                unitType = UT_E_ENGINEER;
                                                break;
                                            case 9:
                                                tribeType = OpenSHC::AI::Tribes::AITT_MONKS;
                                                unitType = UT_E_MONK;
                                                break;
                                            case 10:
                                                tribeType = OpenSHC::AI::Tribes::AITT_ARAB_ARCHERS;
                                                unitType = UT_A_ARCHER;
                                                break;
                                            case 11:
                                                tribeType = OpenSHC::AI::Tribes::AITT_SLAVES;
                                                unitType = UT_A_SLAVE;
                                                break;
                                            case 12:
                                                tribeType = OpenSHC::AI::Tribes::AITT_SLINGERS;
                                                unitType = UT_A_SLINGER;
                                                break;
                                            case 13:
                                                tribeType = OpenSHC::AI::Tribes::AITT_ASSASSINS;
                                                unitType = UT_A_ASSASSIN;
                                                break;
                                            case 14:
                                                tribeType = OpenSHC::AI::Tribes::AITT_HORSE_ARCHERS;
                                                unitType = UT_A_HARCHER;
                                                break;
                                            case 15:
                                                tribeType = OpenSHC::AI::Tribes::AITT_ARAB_SWORDSMEN;
                                                unitType = UT_A_SWORDSMAN;
                                                break;
                                            case 16:
                                                tribeType = OpenSHC::AI::Tribes::AITT_FIRE_THROWERS;
                                                unitType = UT_A_FIRETHROWER;
                                                break;
                                            case 17:
                                                tribeType = OpenSHC::AI::Tribes::AITT_FIRE_BALLISTAS;
                                                unitType = UT_S_FBALLISTA;
                                                break;
                                            }
                                            int const queued
                                                = ((int*)DAT_GameState::instance.mapAndTime.playerQueuedTroops)[queueOffset + kind];
                                            int batchSize = queued;
                                            if (batchSize > 9) {
                                                batchSize = 9;
                                            }
                                            ((int*)DAT_GameState::instance.mapAndTime.playerQueuedTroops)[queueOffset + kind]
                                                = queued - batchSize;
                                            dword const tribeID = MACRO_CALL_MEMBER(
                                                OpenSHC::Map::Units::TribesState_Func::spawnUnitsIntoNewTribe,
                                                DAT_TribesState::ptr)(destinationIndex++, tribeType,
                                                DAT_GameState::instance.playerDataArray[playerID].campground.xEntry,
                                                DAT_GameState::instance.playerDataArray[playerID].campground.yEntry, playerID,
                                                unitType, UT_NONE, batchSize, 0);
                                            DAT_TribesState::instance.tribes[tribeID].behaviorTickCounter = 0x32;
                                            spawnedSkirmishBatch = 1;
                                            break;
                                        }
                                    }
                                }
                                queueOffset += 20;
                            }
                            if (spawnedSkirmishBatch == 0) {
                                DAT_GameState::instance.mapAndTime.reinforcementSpawnTimer = -1;
                            }
                        }
                    }
                } else {
                    if (++DAT_GameState::instance.mapAndTime.reinforcementSpawnTimer > 200) {
                        DAT_GameState::instance.mapAndTime.reinforcementSpawnTimer = 0;
                        for (int kind = 0; kind < 10; ++kind) {
                            if (kind == 7) {
                                kind = 8;
                            }
                            if (((int*)&DAT_GameState::instance.mapAndTime.siegeInformation)[kind] != 0) {
                                switch (kind) {
                                case 0:
                                    tribeType = OpenSHC::AI::Tribes::AITT_ARCHERS;
                                    unitType = UT_E_ARCHER;
                                    break;
                                case 1:
                                    tribeType = OpenSHC::AI::Tribes::AITT_CROSSBOWMEN;
                                    unitType = UT_E_XBOW;
                                    break;
                                case 2:
                                    tribeType = OpenSHC::AI::Tribes::AITT_SPEARMEN;
                                    unitType = UT_E_SPEAR;
                                    break;
                                case 3:
                                    tribeType = OpenSHC::AI::Tribes::AITT_PIKEMEN;
                                    unitType = UT_E_PIKE;
                                    break;
                                case 4:
                                    tribeType = OpenSHC::AI::Tribes::AITT_MACEMEN;
                                    unitType = UT_E_MACE;
                                    break;
                                case 5:
                                    tribeType = OpenSHC::AI::Tribes::AITT_SWORDSMEN;
                                    unitType = UT_E_SWORD;
                                    break;
                                case 6:
                                    tribeType = OpenSHC::AI::Tribes::AITT_KNIGHTS;
                                    unitType = UT_E_KNIGHT;
                                    break;
                                case 8:
                                    tribeType = OpenSHC::AI::Tribes::AITT_ENGINEERS;
                                    unitType = UT_E_ENGINEER;
                                    break;
                                case 9:
                                    tribeType = OpenSHC::AI::Tribes::AITT_MONKS;
                                    unitType = UT_E_MONK;
                                    break;
                                }
                                int const queued = ((int*)&DAT_GameState::instance.mapAndTime.siegeInformation)[kind];
                                int batchSize = queued;
                                if (batchSize > 9) {
                                    batchSize = 9;
                                }
                                ((int*)&DAT_GameState::instance.mapAndTime.siegeInformation)[kind] = queued - batchSize;
                                for (int playerID = 1; playerID < 9; ++playerID) {
                                    if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] != -1
                                        || DAT_GameSynchronyState::instance.currentAIArray[playerID] != 0) {
                                        dword const tribeID = MACRO_CALL_MEMBER(
                                            OpenSHC::Map::Units::TribesState_Func::spawnUnitsIntoNewTribe,
                                            DAT_TribesState::ptr)(destinationIndex++, tribeType,
                                            DAT_GameState::instance.playerDataArray[playerID].campground.xEntry,
                                            DAT_GameState::instance.playerDataArray[playerID].campground.yEntry, playerID,
                                            unitType, UT_NONE, batchSize, 0);
                                        DAT_TribesState::instance.tribes[tribeID].behaviorTickCounter = 0x32;
                                        spawnedMissionBatch = 1;
                                    }
                                }
                                break;
                            }
                        }
                        for (int kind = 10; kind < 20; ++kind) {
                            if (((int*)&DAT_GameState::instance.mapAndTime.siegeInformation)[kind] != 0) {
                                switch (kind) {
                                case 10:
                                    tribeType = OpenSHC::AI::Tribes::AITT_ARAB_ARCHERS;
                                    unitType = UT_A_ARCHER;
                                    break;
                                case 11:
                                    tribeType = OpenSHC::AI::Tribes::AITT_SLAVES;
                                    unitType = UT_A_SLAVE;
                                    break;
                                case 12:
                                    tribeType = OpenSHC::AI::Tribes::AITT_SLINGERS;
                                    unitType = UT_A_SLINGER;
                                    break;
                                case 13:
                                    tribeType = OpenSHC::AI::Tribes::AITT_ASSASSINS;
                                    unitType = UT_A_ASSASSIN;
                                    break;
                                case 14:
                                    tribeType = OpenSHC::AI::Tribes::AITT_HORSE_ARCHERS;
                                    unitType = UT_A_HARCHER;
                                    break;
                                case 15:
                                    tribeType = OpenSHC::AI::Tribes::AITT_ARAB_SWORDSMEN;
                                    unitType = UT_A_SWORDSMAN;
                                    break;
                                case 16:
                                    tribeType = OpenSHC::AI::Tribes::AITT_FIRE_THROWERS;
                                    unitType = UT_A_FIRETHROWER;
                                    break;
                                case 17:
                                    tribeType = OpenSHC::AI::Tribes::AITT_FIRE_BALLISTAS;
                                    unitType = UT_S_FBALLISTA;
                                    break;
                                }
                                int const queued = ((int*)&DAT_GameState::instance.mapAndTime.siegeInformation)[kind];
                                int batchSize = queued;
                                if (batchSize > 9) {
                                    batchSize = 9;
                                }
                                ((int*)&DAT_GameState::instance.mapAndTime.siegeInformation)[kind] = queued - batchSize;
                                for (int playerID = 1; playerID < 9; ++playerID) {
                                    if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] != -1
                                        || DAT_GameSynchronyState::instance.currentAIArray[playerID] != 0) {
                                        dword const tribeID = MACRO_CALL_MEMBER(
                                            OpenSHC::Map::Units::TribesState_Func::spawnUnitsIntoNewTribe,
                                            DAT_TribesState::ptr)(destinationIndex++, tribeType,
                                            DAT_GameState::instance.playerDataArray[playerID].campground.xEntry,
                                            DAT_GameState::instance.playerDataArray[playerID].campground.yEntry, playerID,
                                            unitType, UT_NONE, batchSize, 0);
                                        DAT_TribesState::instance.tribes[tribeID].behaviorTickCounter = 0x32;
                                        spawnedMissionBatch = 1;
                                    }
                                }
                                break;
                            }
                        }
                        if (spawnedMissionBatch == 0) {
                            DAT_GameState::instance.mapAndTime.reinforcementSpawnTimer = -1;
                        }
                    }
                }
            } else {
                int const playerSlotID = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                for (int kind = 0; kind < 20; ++kind) {
                    int percent = 100;
                    switch (DAT_GameState::instance.mapAndTime.difficulty) {
                    case 0:
                        if (playerSlotID == 1) {
                            percent = 0x43;
                        } else if (DAT_SH1_SiegeAdvancedMode::instance == 0) {
                            percent = 0xa7;
                        }
                        break;
                    case 2:
                        if (playerSlotID == 1) {
                            percent = 0x85;
                        } else if (DAT_SH1_SiegeAdvancedMode::instance == 0) {
                            percent = 0x4b;
                        }
                        break;
                    case 3:
                        if (playerSlotID == 1) {
                            percent = 0xa7;
                        } else if (DAT_SH1_SiegeAdvancedMode::instance == 0) {
                            percent = 0x32;
                        }
                        break;
                    }
                    ((int*)&DAT_GameState::instance.mapAndTime.siegeInformation)[kind]
                        = ((int*)&DAT_GameState::instance.mapAndTime.siegeInformation)[kind] * percent / 100;
                }
                for (int kind = 0; kind < 20; ++kind) {
                    if (((int*)&DAT_GameState::instance.mapAndTime.siegeInformation)[kind] != 0) {
                        switch (kind) {
                        case 0:
                            tribeType = OpenSHC::AI::Tribes::AITT_ARCHERS;
                            unitType = UT_E_ARCHER;
                            break;
                        case 1:
                            tribeType = OpenSHC::AI::Tribes::AITT_CROSSBOWMEN;
                            unitType = UT_E_XBOW;
                            break;
                        case 2:
                            tribeType = OpenSHC::AI::Tribes::AITT_SPEARMEN;
                            unitType = UT_E_SPEAR;
                            break;
                        case 3:
                            tribeType = OpenSHC::AI::Tribes::AITT_PIKEMEN;
                            unitType = UT_E_PIKE;
                            break;
                        case 4:
                            tribeType = OpenSHC::AI::Tribes::AITT_MACEMEN;
                            unitType = UT_E_MACE;
                            break;
                        case 5:
                            tribeType = OpenSHC::AI::Tribes::AITT_SWORDSMEN;
                            unitType = UT_E_SWORD;
                            break;
                        case 6:
                            tribeType = OpenSHC::AI::Tribes::AITT_KNIGHTS;
                            unitType = UT_E_KNIGHT;
                            break;
                        case 7:
                            tribeType = OpenSHC::AI::Tribes::AITT_LADDERMEN;
                            unitType = UT_E_LADDER;
                            break;
                        case 8:
                            tribeType = OpenSHC::AI::Tribes::AITT_ENGINEERS;
                            unitType = UT_E_ENGINEER;
                            break;
                        case 9:
                            tribeType = OpenSHC::AI::Tribes::AITT_MONKS;
                            unitType = UT_E_MONK;
                            break;
                        case 10:
                            tribeType = OpenSHC::AI::Tribes::AITT_ARAB_ARCHERS;
                            unitType = UT_A_ARCHER;
                            break;
                        case 11:
                            tribeType = OpenSHC::AI::Tribes::AITT_SLAVES;
                            unitType = UT_A_SLAVE;
                            break;
                        case 12:
                            tribeType = OpenSHC::AI::Tribes::AITT_SLINGERS;
                            unitType = UT_A_SLINGER;
                            break;
                        case 13:
                            tribeType = OpenSHC::AI::Tribes::AITT_ASSASSINS;
                            unitType = UT_A_ASSASSIN;
                            break;
                        case 14:
                            tribeType = OpenSHC::AI::Tribes::AITT_HORSE_ARCHERS;
                            unitType = UT_A_HARCHER;
                            break;
                        case 15:
                            tribeType = OpenSHC::AI::Tribes::AITT_ARAB_SWORDSMEN;
                            unitType = UT_A_SWORDSMAN;
                            break;
                        case 16:
                            tribeType = OpenSHC::AI::Tribes::AITT_FIRE_THROWERS;
                            unitType = UT_A_FIRETHROWER;
                            break;
                        case 17:
                            tribeType = OpenSHC::AI::Tribes::AITT_FIRE_BALLISTAS;
                            unitType = UT_S_FBALLISTA;
                            break;
                        }
                        do {
                            int const queued = ((int*)&DAT_GameState::instance.mapAndTime.siegeInformation)[kind];
                            int batchSize = queued;
                            if (batchSize > 9) {
                                batchSize = 9;
                            }
                            ((int*)&DAT_GameState::instance.mapAndTime.siegeInformation)[kind] = queued - batchSize;
                            int pairIndex = destinationIndex;
                            if (pairIndex > 0x27) {
                                pairIndex = 0;
                            }
                            dword const tribeID = MACRO_CALL_MEMBER(
                                OpenSHC::Map::Units::TribesState_Func::createTribeWithSpawnedUnit,
                                DAT_TribesState::ptr)((short)destinationIndex++, tribeType,
                                DAT_GameState::instance.mapAndTime.unitMoveDestinationXYPairs[0][pairIndex].x,
                                DAT_GameState::instance.mapAndTime.unitMoveDestinationXYPairs[0][pairIndex].y, 2,
                                unitType, batchSize);
                            DAT_TribesState::instance.tribes[tribeID].behaviorTickCounter = 0x32;
                        } while (((int*)&DAT_GameState::instance.mapAndTime.siegeInformation)[kind] != 0);
                    }
                }
                int tunnelersLeft = DAT_MapPropertiesState::instance.SEC_Section1067.tunnelersCount;
                while (tunnelersLeft != 0) {
                    int batchSize = tunnelersLeft;
                    if (batchSize > 9) {
                        batchSize = 9;
                    }
                    tunnelersLeft -= batchSize;
                    int pairIndex = destinationIndex;
                    if (pairIndex > 0x27) {
                        pairIndex = 0;
                    }
                    dword const tribeID = MACRO_CALL_MEMBER(
                        OpenSHC::Map::Units::TribesState_Func::createTribeWithSpawnedUnit, DAT_TribesState::ptr)(
                        (short)destinationIndex++, OpenSHC::AI::Tribes::AITT_TUNNELERS,
                        DAT_GameState::instance.mapAndTime.unitMoveDestinationXYPairs[0][pairIndex].x,
                        DAT_GameState::instance.mapAndTime.unitMoveDestinationXYPairs[0][pairIndex].y, 2, UT_TUNNELER,
                        batchSize);
                    DAT_TribesState::instance.tribes[tribeID].behaviorTickCounter = 0x32;
                }
                DAT_GameState::instance.mapAndTime.reinforcementSpawnTimer = -1;
            }
        }

    }
}
}
