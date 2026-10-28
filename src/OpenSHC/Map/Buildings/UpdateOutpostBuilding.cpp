#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {

    // The first-tick scan checks the tile-valid map at [x*400 + x] for every y of the column (row pointer
    // 0x21aec98 + x*0x191, not advanced by the inner loop at 0x411688) and only range-checks x (cmp esi, 0x18f).
    // Archer count order is insideUnitIDs[0], workerID[0], insideUnitIDs[1], ... (0x411778..0x4118BE); the slot
    // loop at 0x411B00 tries insideUnitIDs[i] before workerID[i]. Engineers per siege unit come from the switch
    // table at 0x41231C/0x412330 (catapult/fire ballista 2, trebuchet 3, tower/ram 4, shield 1).
    // FUNCTION: STRONGHOLDCRUSADER 0x00411540
    void Buildings::UpdateOutpostBuilding()
    {
        int buildingID = DAT_CurrentBuildingID::instance;
        int owner = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        DAT_GameState::instance.playerDataArray[owner].militaryBuildingScore += 10;
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(buildingID);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        buildingID = DAT_CurrentBuildingID::instance;
        int gameMode = DAT_GameSynchronyState::instance.currentGameMode;
        if (gameMode != Game::GM_SOLITARY) {
            DAT_BuildingsState::instance.buildings[buildingID].showOverlays = 1;
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame13 += 1;
            if ((char)DAT_BuildingDefinedData::instance
                    .ownerFlagFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayFrame13 / 2]
                <= 0) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame13 = 0;
            }
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame14 = (char)DAT_BuildingDefinedData::instance
                .ownerFlagFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayFrame13 / 2];
        } else {
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame14 = 0;
        }
        if (DAT_GameCore::instance.gameMode_2 == Game::GM_EDITOR) {
            return;
        }
        if (gameMode != Game::GM_SOLITARY && gameMode != Game::GM_SKIRMISH_SINGLE_PLAYER
            && DAT_GameState::instance.mapAndTime.skirmishNoRushTicksLeft != 0) {
            return;
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].outpostInitDone == 0) {
            DAT_BuildingsState::instance.buildings[buildingID].outpostInitDone = 1;
            int half = (int)DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight / 2;
            int centerX = DAT_BuildingsState::instance.buildings[buildingID].x + half;
            int centerY = half + DAT_BuildingsState::instance.buildings[buildingID].y;
            int endX = centerX + 8;
            int endY = centerY + 8;
            for (int tileX = centerX - 8; tileX < endX; tileX++) {
                for (int tileY = centerY - 8; tileY < endY; tileY++) {
                    if ((uint)tileX < 400
                        && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[tileX * 400 + tileX] != 0) {
                        int unitID = (short)DAT_TileMapState::instance
                                         .UnitLayer[DAT_ViewportRenderState::instance.translationMatrix[tileY].addXgetTile
                                             + tileX];
                        if (unitID != 0) {
                            do {
                                if (DAT_UnitsState::instance.units[unitID].owner
                                    == DAT_BuildingsState::instance.buildings[buildingID].owner) {
                                    DAT_UnitsState::instance.units[unitID].aiUnitBehaviourType = 0x32;
                                }
                                unitID = (short)DAT_UnitsState::instance.units[unitID].nextUnitOnTheSameTile;
                            } while (unitID != 0);
                        }
                    }
                }
            }
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].outpostAttackDelay > 0) {
            DAT_BuildingsState::instance.buildings[buildingID].outpostAttackDelay
                = DAT_BuildingsState::instance.buildings[buildingID].outpostAttackDelay - 1;
        }
        int tribeID = DAT_BuildingsState::instance.buildings[buildingID].tribeID;
        int tableIndex = DAT_BuildingsState::instance.buildings[buildingID].raidTroopTableIndex;
        if (tribeID != 0
            && DAT_TribesState::instance.tribes[tribeID].uid != DAT_BuildingsState::instance.buildings[buildingID].tribeUID) {
            tribeID = 0;
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].horsesInUseOrOutpostArcherCap <= 0) {
            DAT_BuildingsState::instance.buildings[buildingID].horsesInUseOrOutpostArcherCap
                = (char)(SEC_RNG::instance.currentNumber2 % 2) + 6;
            MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].typeSpecificTimer = 0x4b0;
        } else {
            DAT_BuildingsState::instance.buildings[buildingID].typeSpecificTimer += -1;
            if (DAT_BuildingsState::instance.buildings[buildingID].typeSpecificTimer < 0) {
                int curID = DAT_CurrentBuildingID::instance;
                DAT_BuildingsState::instance.buildings[buildingID].typeSpecificTimer = 0x4b0;
                int archerCount = 0;
                for (int slot = 0; slot < 4; slot++) {
                    short insideID = DAT_BuildingsState::instance.buildings[curID].insideUnitIDs[slot];
                    if (insideID > 0
                        && DAT_UnitsState::instance.units[insideID].uid
                            == DAT_BuildingsState::instance.buildings[curID].insideUnitUIDs[slot]) {
                        archerCount += 1;
                    }
                    short workerID = DAT_BuildingsState::instance.buildings[curID].workerID[slot];
                    if (workerID > 0
                        && DAT_UnitsState::instance.units[workerID].uid
                            == DAT_BuildingsState::instance.buildings[curID].workerUID[slot]) {
                        archerCount += 1;
                    }
                }
                if (archerCount < DAT_BuildingsState::instance.buildings[buildingID].horsesInUseOrOutpostArcherCap) {
                    OpenSHC::Map::Units::UnitType archerType = OpenSHC::Map::Units::UT_E_ARCHER;
                    if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                        == OpenSHC::Map::Buildings::BT_OUTPOST_ARABIAN) {
                        archerType = OpenSHC::Map::Units::UT_A_ARCHER;
                    }
                    int archerOwner = DAT_BuildingsState::instance.buildings[buildingID].owner;
                    int unitID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(
                        archerOwner, archerOwner, DAT_BuildingsState::instance.buildings[buildingID].buildingEntryX * 8,
                        DAT_BuildingsState::instance.buildings[buildingID].buildingEntryY * 8, 8, archerType);
                    if (unitID != 0) {
                        DAT_UnitsState::instance.units[unitID].aiUnitBehaviourType = 0x32;
                        DAT_UnitsState::instance.units[unitID].goToRallyPoint = 0;
                        DAT_UnitsState::instance.units[unitID].state.generic
                            = OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION;
                        int destX = -1;
                        int destY = -1;
                        for (int attempt = 0; attempt < 0xf; attempt++) {
                            int baseX = (int)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                                            .widthOrHeight
                                    / 2
                                + DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x;
                            int candX = baseX + SEC_RNG::instance.currentNumber2 % 0xe - 7;
                            MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
                            int baseY = (int)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                                            .widthOrHeight
                                    / 2
                                + DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y;
                            int candY = baseY + SEC_RNG::instance.currentNumber2 % 0xe - 7;
                            MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
                            if ((uint)candX < 400 && (uint)candY < 400
                                && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[candY * 400 + candX] != 0) {
                                int unitArea = (short)DAT_TileMapState::instance.PathConnectionLayer
                                                   [DAT_ViewportRenderState::instance
                                                           .translationMatrix[DAT_UnitsState::instance.units[unitID].y]
                                                           .addXgetTile
                                                       + DAT_UnitsState::instance.units[unitID].x];
                                int tile = DAT_ViewportRenderState::instance.translationMatrix[candY].addXgetTile + candX;
                                int candArea = (short)DAT_TileMapState::instance.PathConnectionLayer[tile];
                                if (unitArea == candArea
                                    || MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                                             calculateCanPlayerUnitsNavigateToAreaFromArea,
                                           DAT_PathFindingState::ptr)(DAT_UnitsState::instance.units[unitID].owner,
                                           unitArea, candArea, DAT_UnitsState::instance.units[unitID].unitCanClimb)
                                        != 0) {
                                    if (destX < 0) {
                                        destX = candX;
                                        destY = candY;
                                    }
                                    if ((DAT_TileMapState::instance.LogicLayer[tile] & 0x10000000) != 0) {
                                        destX = candX;
                                        destY = candY;
                                        break;
                                    }
                                }
                            }
                        }
                        if (destX >= 0) {
                            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit,
                                DAT_UnitsState::ptr)(unitID, destX, destY, 0);
                        }
                        for (int slot = 0; slot < 4; slot++) {
                            short insideID
                                = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].insideUnitIDs[slot];
                            if (insideID <= 0
                                || DAT_UnitsState::instance.units[insideID].uid
                                    != DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                                           .insideUnitUIDs[slot]) {
                                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].insideUnitIDs[slot]
                                    = (short)unitID;
                                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].insideUnitUIDs[slot]
                                    = DAT_UnitsState::instance.units[unitID].uid;
                                break;
                            }
                            short workerID
                                = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerID[slot];
                            if (workerID <= 0
                                || DAT_UnitsState::instance.units[workerID].uid
                                    != DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                                           .workerUID[slot]) {
                                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerID[slot]
                                    = (short)unitID;
                                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerUID[slot]
                                    = DAT_UnitsState::instance.units[unitID].uid;
                                break;
                            }
                        }
                    }
                }
            }
        }
        if (tribeID == 0) {
            int raidInterval = 2000 - DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].raidIntervalReduction;
            if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY
                && DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SKIRMISH_SINGLE_PLAYER
                && raidInterval < 400) {
                raidInterval = 400;
            } else if (raidInterval < 100) {
                raidInterval = 100;
            }
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].raidTimer += 1;
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].raidTimer < raidInterval) {
                return;
            }
            ushort mask = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].outpostTroopTableMask;
            ushort bit1 = mask & 1;
            int enabledCount = 0;
            if (bit1 != 0) {
                enabledCount = 1;
            }
            ushort bit2 = mask & 2;
            if (bit2 != 0) {
                enabledCount += 1;
            }
            ushort bit4 = mask & 4;
            if (bit4 != 0) {
                enabledCount += 1;
            }
            ushort bit8 = mask & 8;
            if (bit8 != 0) {
                enabledCount += 1;
            }
            ushort bit10 = mask & 0x10;
            if (bit10 != 0) {
                enabledCount += 1;
            }
            ushort bit20 = mask & 0x20;
            if (bit20 != 0) {
                enabledCount += 1;
            }
            ushort bit40 = mask & 0x40;
            if (bit40 != 0) {
                enabledCount += 1;
            }
            ushort bit80 = mask & 0x80;
            if (bit80 != 0) {
                enabledCount += 1;
            }
            if (enabledCount == 0) {
                return;
            }
            int pick = SEC_RNG::instance.currentNumber2 % enabledCount;
            MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
            int curID = DAT_CurrentBuildingID::instance;
            int position = 0;
            if (bit1 != 0) {
                if (pick == 0) {
                    DAT_BuildingsState::instance.buildings[curID].raidTroopTableIndex = (short)pick;
                }
                position = 1;
            }
            if (bit2 != 0) {
                if (pick == position) {
                    DAT_BuildingsState::instance.buildings[curID].raidTroopTableIndex = 1;
                }
                position += 1;
            }
            if (bit4 != 0) {
                if (pick == position) {
                    DAT_BuildingsState::instance.buildings[curID].raidTroopTableIndex = 2;
                }
                position += 1;
            }
            if (bit8 != 0) {
                if (pick == position) {
                    DAT_BuildingsState::instance.buildings[curID].raidTroopTableIndex = 3;
                }
                position += 1;
            }
            if (bit10 != 0) {
                if (pick == position) {
                    DAT_BuildingsState::instance.buildings[curID].raidTroopTableIndex = 4;
                }
                position += 1;
            }
            if (bit20 != 0) {
                if (pick == position) {
                    DAT_BuildingsState::instance.buildings[curID].raidTroopTableIndex = 5;
                }
                position += 1;
            }
            if (bit40 != 0) {
                if (pick == position) {
                    DAT_BuildingsState::instance.buildings[curID].raidTroopTableIndex = 6;
                }
                position += 1;
            }
            if (bit80 != 0 && pick == position) {
                DAT_BuildingsState::instance.buildings[curID].raidTroopTableIndex = 7;
            }
            if (DAT_BuildingsState::instance.buildings[curID].buildingType == OpenSHC::Map::Buildings::BT_OUTPOST_ARABIAN) {
                DAT_BuildingsState::instance.buildings[curID].raidTroopTableIndex += 8;
            }
            tableIndex = DAT_BuildingsState::instance.buildings[curID].raidTroopTableIndex;
            tribeID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::createTribeForPlayer, DAT_TribesState::ptr)(
                DAT_BuildingsState::instance.buildings[curID].owner);
            if (tribeID <= 0) {
                return;
            }
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].tribeID = (short)tribeID;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].tribeUID
                = DAT_TribesState::instance.tribes[tribeID].uid;
            DAT_TribesState::instance.tribes[tribeID].unitStance = OpenSHC::Map::Units::Behavior::USE_AGGRESSIVE;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].raidTargetSize
                = ((short)(SEC_RNG::instance.currentNumber2
                               % DAT_BuildingDefinedData::instance.outpostRaidTroopTables[tableIndex][3])
                      + (short)DAT_BuildingDefinedData::instance.outpostRaidTroopTables[tableIndex][2])
                * (short)(DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].outpostStrengthLevel + 1);
            MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].raidCatapultPending = 1;
            DAT_TribesState::instance.tribes[tribeID].tribeSubtype1
                = (short)DAT_BuildingDefinedData::instance.outpostRaidTroopTables[tableIndex][0xc];
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].raidTimer = 2000;
        }
        int curID = DAT_CurrentBuildingID::instance;
        int spawnPeriod = DAT_BuildingDefinedData::instance.outpostRaidTroopTables[tableIndex][0]
            - DAT_BuildingsState::instance.buildings[curID].troopSpawnIntervalReduction;
        if (spawnPeriod < DAT_BuildingDefinedData::instance.outpostRaidTroopTables[tableIndex][1]) {
            spawnPeriod = DAT_BuildingDefinedData::instance.outpostRaidTroopTables[tableIndex][1];
        }
        if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY
            && DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SKIRMISH_SINGLE_PLAYER && spawnPeriod < 0x32) {
            spawnPeriod = 0x32;
        }
        int strength = DAT_BuildingsState::instance.buildings[curID].outpostStrengthLevel;
        DAT_BuildingsState::instance.buildings[curID].raidTimer += 1;
        if (DAT_BuildingsState::instance.buildings[curID].raidTimer < ((100 - strength * 15) * spawnPeriod) / 100) {
            return;
        }
        DAT_BuildingsState::instance.buildings[curID].raidTimer = SEC_RNG::instance.currentNumber2 % 0x28;
        MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
        short attackDelay = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].outpostAttackDelay;
        if (attackDelay > 0
            && DAT_TribesState::instance.tribes[tribeID].size
                >= DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].raidTargetSize - 1) {
            return;
        }
        int typeCount = 0;
        if (DAT_BuildingDefinedData::instance.outpostRaidTroopTables[tableIndex][4] != 0) {
            typeCount = 1;
        }
        if (DAT_BuildingDefinedData::instance.outpostRaidTroopTables[tableIndex][5] != 0) {
            typeCount += 1;
        }
        if (DAT_BuildingDefinedData::instance.outpostRaidTroopTables[tableIndex][6] != 0) {
            typeCount += 1;
        }
        if (DAT_BuildingDefinedData::instance.outpostRaidTroopTables[tableIndex][7] != 0) {
            typeCount += 1;
        }
        if (DAT_BuildingDefinedData::instance.outpostRaidTroopTables[tableIndex][8] != 0) {
            typeCount += 1;
        }
        if (DAT_BuildingDefinedData::instance.outpostRaidTroopTables[tableIndex][9] != 0) {
            typeCount += 1;
        }
        if (DAT_BuildingDefinedData::instance.outpostRaidTroopTables[tableIndex][10] != 0) {
            typeCount += 1;
        }
        if (DAT_BuildingDefinedData::instance.outpostRaidTroopTables[tableIndex][0xb] != 0) {
            typeCount += 1;
        }
        if ((tableIndex == 7 || tableIndex == 6)
            && ((attackDelay == 0 && DAT_TribesState::instance.tribes[tribeID].size == 0)
                || (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].raidCatapultPending != 0
                    && DAT_TribesState::instance.tribes[tribeID].size > 0))) {
            typeCount = 1;
        }
        OpenSHC::Map::Units::UnitType unitType = (OpenSHC::Map::Units::UnitType)DAT_BuildingDefinedData::instance
                                                     .outpostRaidTroopTables[tableIndex][SEC_RNG::instance.currentNumber2 % typeCount + 4];
        MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
        int spawnCount = 1;
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].outpostAttackDelay > 0
            && DAT_TribesState::instance.tribes[tribeID].size == 0
            && DAT_GameState::instance.playerDataArray[owner].aiType != OpenSHC::AI::AIT_NULL) {
            spawnCount = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].raidTargetSize / 2;
            if (spawnCount == 0) {
                spawnCount = 1;
            }
            if ((tableIndex == 7 || tableIndex == 6) && spawnCount > 1 && unitType == OpenSHC::Map::Units::UT_S_CATAPULT) {
                unitType = (OpenSHC::Map::Units::UnitType)DAT_BuildingDefinedData::instance
                               .outpostRaidTroopTables[tableIndex][5];
            }
        }
        if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY
            && DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SKIRMISH_SINGLE_PLAYER
            && DAT_GameState::instance.playerDataArray[owner].peasantsBeingRecruitedAsTroops
                    + DAT_GameState::instance.playerDataArray[owner].armySize
                >= DAT_GameState::instance.mapAndTime.armySizeLimit) {
            return;
        }
        for (int spawned = 0; spawned < spawnCount; spawned++) {
            int raidOwner = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
            int unitID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(
                raidOwner, raidOwner, DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingEntryX * 8,
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingEntryY * 8, 8, unitType);
            if (unitID == 0) {
                return;
            }
            if (unitType == OpenSHC::Map::Units::UT_S_CATAPULT) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].raidCatapultPending = 0;
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::addUnitToTribe, DAT_TribesState::ptr)(unitID, tribeID);
            int engineerCount;
            switch (unitType) {
            case OpenSHC::Map::Units::UT_S_CATAPULT:
            case OpenSHC::Map::Units::UT_S_FBALLISTA:
                engineerCount = 2;
                break;
            case OpenSHC::Map::Units::UT_S_TREBUCHET:
                engineerCount = 3;
                break;
            case OpenSHC::Map::Units::UT_S_TOWER:
            case OpenSHC::Map::Units::UT_S_BATTERINGRAM:
                engineerCount = 4;
                break;
            case OpenSHC::Map::Units::UT_S_SHIELD:
                engineerCount = 1;
                break;
            default:
                goto noEngineers;
            }
            do {
                int engineerOwner = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
                int engineerID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(
                    engineerOwner, engineerOwner,
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingEntryX * 8,
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingEntryY * 8, 8,
                    OpenSHC::Map::Units::UT_E_ENGINEER);
                if (engineerID != 0) {
                    DAT_UnitsState::instance.units[engineerID].targetingType_OR_performanceStep
                        = OpenSHC::Map::Units::UIT_MAN_SIEGE_EQUIPMENT;
                    DAT_UnitsState::instance.units[engineerID].targetUnitId = (short)unitID;
                }
                engineerCount -= 1;
            } while (engineerCount != 0);
        noEngineers:
            DAT_UnitsState::instance.units[unitID].aiUnitBehaviourType = 0x32;
            DAT_UnitsState::instance.units[unitID].goToRallyPoint = 0;
        }
        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(tribeID,
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingEntryX,
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingEntryY, 0, 0,
            OpenSHC::Map::Units::Instructions::UMSE_0);
        if (DAT_TribesState::instance.tribes[tribeID].size
                >= DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].raidTargetSize
            && DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].outpostAttackDelay <= 0) {
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::aiRegisterTribeAndAssignTarget, DAT_AICState::ptr)(
                tribeID, DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].tribeUID);
            int releasedID = DAT_CurrentBuildingID::instance;
            DAT_BuildingsState::instance.buildings[releasedID].tribeID = 0;
            DAT_BuildingsState::instance.buildings[releasedID].raidIntervalReduction += 100;
            DAT_BuildingsState::instance.buildings[releasedID].troopSpawnIntervalReduction += 4;
        }
    }

}
}
