#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/AttackInfoSubElement.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/TileMapState/NeighbourFlagsAsm.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

// The neighbour gathering into TileMapState.specialAreasArray is handwritten assembly in the original (push/pop esi,
// "add esi, ecx" pairs instead of a scaled index; the instruction stream exists only in this function). Three shapes:
//
//   PATHCON_4    east -> [2], west -> [6], north -> [0], south -> [4] of PathConnectionLayer (0x0051E611)
//   PATHCON_DIAG north-east -> [1], north-west -> [7], south-east -> [3], south-west -> [5] (0x0051ED8A)
//   AIZONE_4     the same as PATHCON_4 but on the byte layer AIZoneLayer with unchanged 16-bit loads and stores at
//                byte offsets, so it fills [1], [3], [0], [2] with two-byte reads, and it scales curTileY by 16
//                instead of 32, i.e. it reads the north/south deltas of the wrong directionTranslationMatrix row
//                (0x0051EB3A). The scan that follows reads [0], [2], [4], [6], so [4] and [6] are left over from an
//                earlier gather. Kept as is.
//
// They clobber eax, ebx, ecx, edx, esi and edi.

// clang-format off
#define RAI_TMS ds:[NEIGHBOUR_FLAGS_TILEMAPSTATE]TileMapState

#define MACRO_RAI_GATHER_PATHCON_4                                                    \
    __asm mov edi, dword ptr RAI_TMS.ptr_MovementDirectionTranslationMatrix           \
    __asm mov esi, dword ptr RAI_TMS.ptr_PathConnectionLayer                          \
    __asm mov edx, dword ptr RAI_TMS.ptr_SpecialAreasArray                            \
    __asm mov eax, dword ptr RAI_TMS.curTileIndex                                     \
    __asm shl eax, 0x1                                                                \
    __asm add esi, eax                                                                \
    __asm push esi                                                                    \
    __asm mov eax, dword ptr RAI_TMS.curTileY                                         \
    __asm shl eax, 0x5                                                                \
    __asm add edi, eax                                                                \
    __asm mov bx, word ptr [esi + 0x2]                                                \
    __asm mov ax, word ptr [esi - 0x2]                                                \
    __asm mov word ptr [edx + 0x4], bx                                                \
    __asm mov word ptr [edx + 0xc], ax                                                \
    __asm mov ecx, dword ptr [edi]                                                    \
    __asm add esi, ecx                                                                \
    __asm add esi, ecx                                                                \
    __asm mov bx, word ptr [esi]                                                      \
    __asm mov ecx, dword ptr [edi + 0x10]                                             \
    __asm pop esi                                                                     \
    __asm add esi, ecx                                                                \
    __asm add esi, ecx                                                                \
    __asm mov ax, word ptr [esi]                                                      \
    __asm mov word ptr [edx], bx                                                      \
    __asm mov word ptr [edx + 0x8], ax

#define MACRO_RAI_GATHER_PATHCON_DIAG                                                 \
    __asm mov edi, dword ptr RAI_TMS.ptr_MovementDirectionTranslationMatrix           \
    __asm mov esi, dword ptr RAI_TMS.ptr_PathConnectionLayer                          \
    __asm mov edx, dword ptr RAI_TMS.ptr_SpecialAreasArray                            \
    __asm mov eax, dword ptr RAI_TMS.curTileIndex                                     \
    __asm shl eax, 0x1                                                                \
    __asm add esi, eax                                                                \
    __asm push esi                                                                    \
    __asm mov eax, dword ptr RAI_TMS.curTileY                                         \
    __asm shl eax, 0x5                                                                \
    __asm add edi, eax                                                                \
    __asm mov ecx, dword ptr [edi]                                                    \
    __asm add esi, ecx                                                                \
    __asm add esi, ecx                                                                \
    __asm mov bx, word ptr [esi + 0x2]                                                \
    __asm mov ax, word ptr [esi - 0x2]                                                \
    __asm mov word ptr [edx + 0x2], bx                                                \
    __asm mov word ptr [edx + 0xe], ax                                                \
    __asm mov ecx, dword ptr [edi + 0x10]                                             \
    __asm pop esi                                                                     \
    __asm add esi, ecx                                                                \
    __asm add esi, ecx                                                                \
    __asm mov bx, word ptr [esi + 0x2]                                                \
    __asm mov ax, word ptr [esi - 0x2]                                                \
    __asm mov word ptr [edx + 0x6], bx                                                \
    __asm mov word ptr [edx + 0xa], ax

#define MACRO_RAI_GATHER_AIZONE_4                                                     \
    __asm mov edi, dword ptr RAI_TMS.ptr_MovementDirectionTranslationMatrix           \
    __asm mov esi, dword ptr RAI_TMS.ptr_AIZoneLayer                                  \
    __asm mov edx, dword ptr RAI_TMS.ptr_SpecialAreasArray                            \
    __asm mov eax, dword ptr RAI_TMS.curTileIndex                                     \
    __asm add esi, eax                                                                \
    __asm push esi                                                                    \
    __asm mov eax, dword ptr RAI_TMS.curTileY                                         \
    __asm shl eax, 0x4                                                                \
    __asm add edi, eax                                                                \
    __asm mov bx, word ptr [esi + 0x1]                                                \
    __asm mov ax, word ptr [esi - 0x1]                                                \
    __asm mov word ptr [edx + 0x2], bx                                                \
    __asm mov word ptr [edx + 0x6], ax                                                \
    __asm mov ecx, dword ptr [edi]                                                    \
    __asm add esi, ecx                                                                \
    __asm mov bx, word ptr [esi]                                                      \
    __asm mov ecx, dword ptr [edi + 0x10]                                             \
    __asm pop esi                                                                     \
    __asm add esi, ecx                                                                \
    __asm mov ax, word ptr [esi]                                                      \
    __asm mov word ptr [edx], bx                                                      \
    __asm mov word ptr [edx + 0x4], ax
// clang-format on

namespace OpenSHC {
namespace Map {
    namespace Units {

        // Only the people block compares against a local copy of startCon (0x0051E4BE); every other use reads the
        // global again. AIZone value 10 is written on the hack neighbour tile (0x0051F031).
        // FUNCTION: STRONGHOLDCRUSADER 0x0051E300
        void TroopValueState::recomputeAttackInfo(int playerID, int attackedPlayerID)
        {
            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].hack1 = 0;
            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].scale1 = 0;
            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].hack2 = 0;
            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].scale2 = 0;
            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].stone1 = 0;
            DAT_TroopValueState::instance.attackInfo.high1 = 0;
            DAT_TroopValueState::instance.attackInfo.arch1 = 0;
            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].gate1 = 0;
            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].wide1 = 0;
            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].town1 = 0;
            DAT_TroopValueState::instance.attackInfo.people1 = 0;
            DAT_TroopValueState::instance.attackInfo.enemyLordTileCount = 0;
            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].some1000ArrayIndex_2 = 0;
            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].wide2 = 0;
            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].some1000ArrayIndex = 0;
            DAT_TroopValueState::instance.attackInfo.peopleTargetCount = 0;
            DAT_TroopValueState::instance.attackInfo.lordTargetCount = 0;
            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].moat1 = 0;
            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].field89_0xfa88 = 0;
            DAT_TroopValueState::instance.attackInfo.high2 = 0;
            DAT_TroopValueState::instance.attackInfo.arch2 = 0;
            DAT_TroopValueState::instance.attackInfo.scaleZone = 1000;
            DAT_TroopValueState::instance.attackInfo.lordConnectionArea = 0;
            DAT_TroopValueState::instance.attackInfo.recomputeResetUnk2c85c = 0;
            if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY) {
                DAT_TroopValueState::instance.attackInfo.someDistanceLimit = 4;
            }
            else {
                DAT_TroopValueState::instance.attackInfo.someDistanceLimit
                    = DAT_TroopValueState::instance.attackInfo.zoneSize < 3000 ? 10 : 4;
            }
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                16000, 0, DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].field4_0x10);
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                16000, 0, DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].field31_0x3ebc);
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                16000, 0, DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].some1000Array);
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                16000, 0, DAT_TroopValueState::instance.attackInfo.peopleValuesArray);
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                16000, 0, DAT_TroopValueState::instance.attackInfo.lordValuesArray);
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                16000, 0, DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].field71_0xbbf4);
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                16000, 0, DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].wideEntries);
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                16000, 0, DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].moatEntries);
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                16000, 0, DAT_TroopValueState::instance.attackInfo.high2ValuesArray);
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                16000, 0, DAT_TroopValueState::instance.attackInfo.arch2ValuesArray);
            int const startCon = DAT_TroopValueState::instance.attackInfo.startCon;
            for (int tile = 0; tile < 80400; ++tile) {
                int height;
                short const unitID = (short)DAT_TileMapState::instance.UnitLayer[tile];
                int const logic = DAT_TileMapState::instance.LogicLayer[tile];
                if (unitID == 0 && (logic & 0x50000700) == 0) {
                    continue;
                }
                short const buildingID = DAT_TileMapState::instance.BuildingLayer[tile];
                if (buildingID != 0) {
                    if (DAT_BuildingsState::instance.buildings[buildingID].buildingType == Buildings::BT_GATEHOUSELARGE) {
                        height = (int)MACRO_CALL_MEMBER(Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                                     DAT_BuildingsState::ptr)(buildingID)
                            + DAT_TileMapState::instance.DefaultHeightLayer[tile];
                    }
                    else if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                        == Buildings::BT_GATEHOUSESMALL) {
                        height = (int)MACRO_CALL_MEMBER(Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                                     DAT_BuildingsState::ptr)(buildingID)
                            + DAT_TileMapState::instance.DefaultHeightLayer[tile];
                    }
                    else {
                        height = (int)MACRO_CALL_MEMBER(Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                                     DAT_BuildingsState::ptr)(buildingID)
                            + DAT_TileMapState::instance.HeightLayer[tile];
                    }
                }
                else {
                    height = DAT_TileMapState::instance.HeightLayer[tile];
                }
                if (unitID != 0
                    && MACRO_CALL_MEMBER(Game::GameStateStructures_Func::getTeamsDifferent, DAT_GameState::ptr)(
                           DAT_UnitsState::instance.units[unitID].owner, playerID)
                        != FALSE) {
                    if (DAT_TileMapState::instance.aiZoneDistanceLayers[attackedPlayerID][tile] <= 0) {
                        continue;
                    }
                    if ((short)DAT_TileMapState::instance.PathConnectionLayer[tile] == startCon
                        && DAT_UnitsState::instance.units[unitID].isAnimalOrAmbient == 0
                        && DAT_UnitsState::instance.units[unitID].isSelectable_OR_matchTime != 0) {
                        DAT_TroopValueState::instance.attackInfo.people1++;
                        DAT_TileMapState::instance.curTileIndex = tile;
                        DAT_TileMapState::instance.curTileY
                            = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
                        MACRO_RAI_GATHER_PATHCON_4
                        for (int i = 0; i < 8; i += 2) {
                            if (DAT_TileMapState::instance.specialAreasArray[i] != startCon) {
                                continue;
                            }
                            if (DAT_TroopValueState::instance.attackInfo.peopleTargetCount >= 1000
                                || MACRO_CALL_MEMBER(TroopValueState_Func::getTileInTargetedBuildingTiles, this)(tile)
                                    != FALSE) {
                                break;
                            }
                            int const neighbourHeight = (int)MACRO_CALL_MEMBER(
                                TileMapState_Func::getTotalHeightAtTile, DAT_TileMapState::ptr)(
                                DAT_TileMapState::instance.directionTranslationMatrix[DAT_TileMapState::instance.curTileY][i]
                                + tile);
                            if (height > neighbourHeight + 16 || height < neighbourHeight - 16) {
                                continue;
                            }
                            DAT_TroopValueState::instance.attackInfo
                                .peopleValuesArray[DAT_TroopValueState::instance.attackInfo.peopleTargetCount]
                                .tile
                                = tile;
                            DAT_TroopValueState::instance.attackInfo
                                .peopleValuesArray[DAT_TroopValueState::instance.attackInfo.peopleTargetCount]
                                .tile2
                                = DAT_TileMapState::instance.directionTranslationMatrix[DAT_TileMapState::instance.curTileY][i]
                                + tile;
                            DAT_TroopValueState::instance.attackInfo.peopleTargetCount++;
                        }
                    }
                    if (DAT_UnitsState::instance.units[unitID].unitType == UT_LORD) {
                        DAT_TroopValueState::instance.attackInfo.enemyLordTileCount++;
                        DAT_TroopValueState::instance.attackInfo.lordConnectionArea
                            = (short)DAT_TileMapState::instance.PathConnectionLayer[tile];
                        if (DAT_TroopValueState::instance.attackInfo.lordConnectionArea
                            == DAT_TroopValueState::instance.attackInfo.startCon) {
                            DAT_TileMapState::instance.curTileY
                                = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
                            for (int dir = 0; dir < 8; ++dir) {
                                int const neighbour
                                    = DAT_TileMapState::instance.directionTranslationMatrix[DAT_TileMapState::instance.curTileY][dir]
                                    + tile;
                                if (DAT_TileMapState::instance.PathConnectionLayer[neighbour] == 0) {
                                    continue;
                                }
                                if (DAT_TroopValueState::instance.attackInfo.lordTargetCount >= 1000) {
                                    break;
                                }
                                DAT_TroopValueState::instance.attackInfo
                                    .lordValuesArray[DAT_TroopValueState::instance.attackInfo.lordTargetCount]
                                    .tile
                                    = tile;
                                DAT_TroopValueState::instance.attackInfo
                                    .lordValuesArray[DAT_TroopValueState::instance.attackInfo.lordTargetCount]
                                    .tile2
                                    = neighbour;
                                DAT_TroopValueState::instance.attackInfo.lordTargetCount++;
                            }
                        }
                    }
                }
                if (buildingID != 0 && DAT_BuildingsState::instance.buildings[buildingID].owner == attackedPlayerID) {
                    height = DAT_TileMapState::instance.DefaultHeightLayer[tile];
                    if (DAT_BuildingDefinedData::instance
                            .IsGateOrTowerArray[DAT_BuildingsState::instance.buildings[buildingID].buildingType]
                        != FALSE) {
                        if (DAT_TileMapState::instance.aiZoneDistanceLayers[attackedPlayerID][tile] <= 0) {
                            continue;
                        }
                        DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].gate1++;
                        DAT_TileMapState::instance.curTileY
                            = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
                        DAT_TileMapState::instance.curTileIndex = tile;
                        DAT_TileMapState::instance.curTileX = tile
                            - DAT_ViewportRenderState::instance.translationMatrix[DAT_TileMapState::instance.curTileY]
                                  .addXgetTile;
                        MACRO_RAI_GATHER_PATHCON_4
                        for (int i = 0; i < 8; i += 2) {

                            if (DAT_TileMapState::instance.specialAreasArray[i]
                                != DAT_TroopValueState::instance.attackInfo.startCon) {
                                continue;
                            }
                            if (DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].some1000ArrayIndex_2
                                    >= 1000
                                || MACRO_CALL_MEMBER(TroopValueState_Func::getTileInTargetedBuildingTiles, this)(tile)
                                    != FALSE) {
                                break;
                            }
                            int const neighbour
                                = DAT_TileMapState::instance.directionTranslationMatrix[DAT_TileMapState::instance.curTileY][i]
                                + tile;
                            if ((DAT_TileMapState::instance.LogicLayer[neighbour] & 0x10000100) != 0) {
                                continue;
                            }
                            int const neighbourHeight = (int)MACRO_CALL_MEMBER(
                                TileMapState_Func::getTotalHeightAtTile, DAT_TileMapState::ptr)(neighbour);
                            if (height > neighbourHeight + 16 || height < neighbourHeight - 16) {
                                continue;
                            }
                            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].field71_0xbbf4
                                [DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].some1000ArrayIndex_2][0]
                                = tile;
                            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].field71_0xbbf4
                                [DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].some1000ArrayIndex_2][1]
                                = DAT_TileMapState::instance.directionTranslationMatrix[DAT_TileMapState::instance.curTileY][i]
                                + tile;
                            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].some1000ArrayIndex_2++;
                            if (DAT_TileMapState::instance.AIZoneLayer[tile] != 0) {
                                DAT_TileMapState::instance.curTileX = tile
                                    - DAT_ViewportRenderState::instance
                                          .translationMatrix[DAT_TileMapState::instance.curTileY]
                                          .addXgetTile;
                                MACRO_CALL_MEMBER(Navigation::PathFindingState_Func::floodFillAIZoneFlag,
                                    DAT_PathFindingState::ptr)(DAT_TroopValueState::instance.attackInfo.someDistanceLimit,
                                    DAT_TileMapState::instance.curTileX, DAT_TileMapState::instance.curTileY, 1);
                            }
                            break;
                        }
                    }
                    else if (DAT_BuildingDefinedData::instance
                                 .BuildingTypeHasHealth[DAT_BuildingsState::instance.buildings[buildingID].buildingType]
                        != 0) {
                        if ((DAT_TileMapState::instance.LogicLayer[tile] & 0xf000000) != 0) {
                            continue;
                        }
                        DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].town1++;
                        DAT_TileMapState::instance.curTileIndex = tile;
                        DAT_TileMapState::instance.curTileY
                            = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
                        MACRO_RAI_GATHER_PATHCON_4
                        for (int i = 0; i < 8; i += 2) {
                            if (DAT_TileMapState::instance.specialAreasArray[i]
                                != DAT_TroopValueState::instance.attackInfo.startCon) {
                                continue;
                            }
                            if (DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].some1000ArrayIndex
                                    >= 1000
                                || MACRO_CALL_MEMBER(TroopValueState_Func::getTileInTargetedBuildingTiles, this)(tile)
                                    != FALSE) {
                                break;
                            }
                            int const neighbourHeight = (int)MACRO_CALL_MEMBER(
                                TileMapState_Func::getTotalHeightAtTile, DAT_TileMapState::ptr)(
                                DAT_TileMapState::instance.directionTranslationMatrix[DAT_TileMapState::instance.curTileY][i]
                                + tile);
                            if (height > neighbourHeight + 16 || height < neighbourHeight - 16) {
                                continue;
                            }
                            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1]
                                .some1000Array[DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1]
                                                   .some1000ArrayIndex]
                                .tile
                                = tile;
                            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1]
                                .some1000Array[DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1]
                                                   .some1000ArrayIndex]
                                .field1_0x4
                                = DAT_TileMapState::instance.directionTranslationMatrix[DAT_TileMapState::instance.curTileY][i]
                                + tile;
                            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].some1000ArrayIndex++;
                            break;
                        }
                    }
                    else {
                        if ((logic & 0x10000000) == 0) {
                            continue;
                        }
                        int const connection = (short)DAT_TileMapState::instance.PathConnectionLayer[tile];
                        if (DAT_TileMapState::instance.aiZoneDistanceLayers[attackedPlayerID][tile] <= 0) {
                            continue;
                        }
                        int const targetBuildingID = DAT_TileMapState::instance.BuildingLayer[tile];
                        if (MACRO_CALL_MEMBER(TroopValueState_Func::attackInfoHasHigh2Building, this)(targetBuildingID)
                                != FALSE
                            || MACRO_CALL_MEMBER(TroopValueState_Func::attackInfoHasArch2Building, this)(targetBuildingID)
                                != FALSE) {
                            continue;
                        }
                        DAT_TileMapState::instance.curTileIndex = tile;
                        DAT_TileMapState::instance.curTileY
                            = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
                        MACRO_RAI_GATHER_AIZONE_4
                        int zone = 0;
                        for (int i = 0; i < 8; i += 2) {
                            if (DAT_TileMapState::instance.specialAreasArray[i] != 0) {
                                zone = DAT_TileMapState::instance.specialAreasArray[i];
                            }
                        }
                        if (zone <= 0) {
                            continue;
                        }
                        DAT_BuildingsState::instance.buildings[targetBuildingID].adjacentAIZoneValue = (short)zone;
                        if (MACRO_CALL_MEMBER(Buildings::BuildingsState_Func::hasHumanPlayerUnitsOnBuilding,
                                DAT_BuildingsState::ptr)(targetBuildingID)
                            != FALSE) {
                            DAT_TroopValueState::instance.attackInfo.high1++;
                            if (DAT_TroopValueState::instance.attackInfo.high2 >= 1000
                                || MACRO_CALL_MEMBER(
                                       Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea,
                                       DAT_PathFindingState::ptr)(
                                       playerID, DAT_TroopValueState::instance.attackInfo.startCon, connection, 0)
                                    == 0) {
                                continue;
                            }
                            DAT_TroopValueState::instance.attackInfo
                                .high2ValuesArray[DAT_TroopValueState::instance.attackInfo.high2]
                                .buildingID
                                = targetBuildingID;
                            DAT_TroopValueState::instance.attackInfo
                                .high2ValuesArray[DAT_TroopValueState::instance.attackInfo.high2]
                                .tile2
                                = tile;
                            DAT_TroopValueState::instance.attackInfo
                                .high2ValuesArray[DAT_TroopValueState::instance.attackInfo.high2]
                                .tile
                                = tile;
                            DAT_TroopValueState::instance.attackInfo.high2++;
                        }
                        else {
                            DAT_TroopValueState::instance.attackInfo.arch1++;
                            if (DAT_TroopValueState::instance.attackInfo.arch2 >= 1000
                                || MACRO_CALL_MEMBER(
                                       Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea,
                                       DAT_PathFindingState::ptr)(
                                       playerID, DAT_TroopValueState::instance.attackInfo.startCon, connection, 0)
                                    == 0) {
                                continue;
                            }
                            DAT_TroopValueState::instance.attackInfo
                                .arch2ValuesArray[DAT_TroopValueState::instance.attackInfo.arch2]
                                .buildingID
                                = targetBuildingID;
                            DAT_TroopValueState::instance.attackInfo
                                .arch2ValuesArray[DAT_TroopValueState::instance.attackInfo.arch2]
                                .tile2
                                = tile;
                            DAT_TroopValueState::instance.attackInfo
                                .arch2ValuesArray[DAT_TroopValueState::instance.attackInfo.arch2]
                                .tile
                                = tile;
                            DAT_TroopValueState::instance.attackInfo.arch2++;
                        }
                    }
                }
                else if ((logic & 0x300) != 0 && (logic & 2) == 0) {
                    if (DAT_TileMapState::instance.aiZoneDistanceLayers[attackedPlayerID][tile] <= 0
                        || (DAT_TileMapState::instance.WallOwnerLayer[tile] & 7) + 1 != attackedPlayerID) {
                        continue;
                    }
                    height = DAT_TileMapState::instance.DefaultHeightLayer[tile];
                    if (DAT_TileMapState::instance.HeightLayer[tile] - height <= 20 || buildingID != 0) {
                        continue;
                    }
                    DAT_TileMapState::instance.curTileIndex = tile;
                    DAT_TileMapState::instance.curTileY
                        = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
                    MACRO_RAI_GATHER_PATHCON_4
                    MACRO_RAI_GATHER_PATHCON_DIAG
                    for (int i = 0; i < 8; i += 2) {
                        if (MACRO_CALL_MEMBER(
                                Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea,
                                DAT_PathFindingState::ptr)(playerID, DAT_TroopValueState::instance.attackInfo.startCon,
                                DAT_TileMapState::instance.specialAreasArray[i], 0)
                            == 0) {
                            continue;
                        }
                        int previous = i - 1;
                        if (previous < 0) {
                            previous = 7;
                        }
                        if (MACRO_CALL_MEMBER(
                                Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea,
                                DAT_PathFindingState::ptr)(playerID, DAT_TroopValueState::instance.attackInfo.startCon,
                                DAT_TileMapState::instance.specialAreasArray[i + 1], 0)
                                == 0
                            || MACRO_CALL_MEMBER(
                                   Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea,
                                   DAT_PathFindingState::ptr)(playerID, DAT_TroopValueState::instance.attackInfo.startCon,
                                   DAT_TileMapState::instance.specialAreasArray[previous], 0)
                                == 0
                            || (DAT_TileMapState::instance.AIInfoLayer[tile] & 0x20) != 0) {
                            continue;
                        }
                        if (DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].wide2 >= 1000
                            || MACRO_CALL_MEMBER(TroopValueState_Func::getTileInTargetedBuildingTiles, this)(tile)
                                != FALSE) {
                            break;
                        }
                        int const neighbour
                            = DAT_TileMapState::instance.directionTranslationMatrix[DAT_TileMapState::instance.curTileY][i]
                            + tile;
                        if ((DAT_TileMapState::instance.LogicLayer[neighbour] & 0x10000100) != 0) {
                            continue;
                        }
                        int const neighbourHeight = (int)MACRO_CALL_MEMBER(
                            TileMapState_Func::getTotalHeightAtTile, DAT_TileMapState::ptr)(neighbour);
                        if (height > neighbourHeight + 16 || height < neighbourHeight - 16) {
                            continue;
                        }
                        DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1]
                            .wideEntries[DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].wide2][0]
                            = tile;
                        DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1]
                            .wideEntries[DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].wide2][1]
                            = DAT_TileMapState::instance.directionTranslationMatrix[DAT_TileMapState::instance.curTileY][i]
                            + tile;
                        DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].wide2++;
                        DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].wide1++;
                        DAT_TileMapState::instance.curTileX = tile
                            - DAT_ViewportRenderState::instance.translationMatrix[DAT_TileMapState::instance.curTileY]
                                  .addXgetTile;
                        MACRO_CALL_MEMBER(Navigation::PathFindingState_Func::updateAIZoneWithFloodFill0x20,
                            DAT_PathFindingState::ptr)(
                            4, DAT_TileMapState::instance.curTileX, DAT_TileMapState::instance.curTileY);
                        goto nextTile;
                    }
                    DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].stone1++;
                    for (int i = 0; i < 8; i += 2) {
                        if (MACRO_CALL_MEMBER(
                                Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea,
                                DAT_PathFindingState::ptr)(playerID, DAT_TroopValueState::instance.attackInfo.startCon,
                                DAT_TileMapState::instance.specialAreasArray[i], 0)
                            == 0) {
                            continue;
                        }
                        if (DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].hack2 >= 1000
                            || MACRO_CALL_MEMBER(TroopValueState_Func::getTileInTargetedBuildingTiles, this)(tile)
                                != FALSE) {
                            break;
                        }
                        int const neighbour
                            = DAT_TileMapState::instance.directionTranslationMatrix[DAT_TileMapState::instance.curTileY][i]
                            + tile;
                        if ((DAT_TileMapState::instance.LogicLayer[neighbour] & 0x10000100) != 0) {
                            continue;
                        }
                        int const neighbourHeight = (int)MACRO_CALL_MEMBER(
                            TileMapState_Func::getTotalHeightAtTile, DAT_TileMapState::ptr)(neighbour);
                        if (height > neighbourHeight + 16 || height < neighbourHeight - 16) {
                            continue;
                        }
                        DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1]
                            .field4_0x10[DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].hack2 * 4]
                            = tile;
                        DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1]
                            .field4_0x10[DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].hack2 * 4 + 1]
                            = DAT_TileMapState::instance.directionTranslationMatrix[DAT_TileMapState::instance.curTileY][i]
                            + tile;
                        DAT_TileMapState::instance.AIZoneLayer[DAT_TroopValueState::instance.attackInfo
                                .playerInfo[playerID - 1]
                                .field4_0x10[DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].hack2 * 4
                                    + 1]]
                            = 10;
                        DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].hack2++;
                        if (DAT_TileMapState::instance.AIZoneLayer[tile] != 0) {
                            DAT_TileMapState::instance.curTileX = tile
                                - DAT_ViewportRenderState::instance.translationMatrix[DAT_TileMapState::instance.curTileY]
                                      .addXgetTile;
                            MACRO_CALL_MEMBER(Navigation::PathFindingState_Func::floodFillAIZoneFlag,
                                DAT_PathFindingState::ptr)(DAT_TroopValueState::instance.attackInfo.someDistanceLimit,
                                DAT_TileMapState::instance.curTileX, DAT_TileMapState::instance.curTileY, 1);
                        }
                        break;
                    }
                    DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].hack1++;
                    if ((logic & 0x400000) != 0) {
                        continue;
                    }
                    int const zone = (char)DAT_TileMapState::instance.AIZoneLayer[tile];
                    DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].scale1++;
                    if (zone != 0 && zone < DAT_TroopValueState::instance.attackInfo.scaleZone) {
                        DAT_TroopValueState::instance.attackInfo.scaleZone = zone;
                    }
                    for (int i = 0; i < 8; i += 2) {
                        if (MACRO_CALL_MEMBER(
                                Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea,
                                DAT_PathFindingState::ptr)(playerID, DAT_TroopValueState::instance.attackInfo.startCon,
                                DAT_TileMapState::instance.specialAreasArray[i], 0)
                            == 0) {
                            continue;
                        }
                        if (DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].scale2 >= 1000
                            || MACRO_CALL_MEMBER(TroopValueState_Func::getTileInTargetedBuildingTiles, this)(tile)
                                != FALSE) {
                            break;
                        }
                        int const neighbour
                            = DAT_TileMapState::instance.directionTranslationMatrix[DAT_TileMapState::instance.curTileY][i]
                            + tile;
                        if ((DAT_TileMapState::instance.LogicLayer[neighbour] & 0x10000100) != 0) {
                            continue;
                        }
                        int const neighbourHeight = (int)MACRO_CALL_MEMBER(
                            TileMapState_Func::getTotalHeightAtTile, DAT_TileMapState::ptr)(neighbour);
                        if (height > neighbourHeight + 16 || height < neighbourHeight - 16) {
                            continue;
                        }
                        DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1]
                            .field31_0x3ebc[DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].scale2][0]
                            = tile;
                        DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1]
                            .field31_0x3ebc[DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].scale2][1]
                            = DAT_TileMapState::instance.directionTranslationMatrix[DAT_TileMapState::instance.curTileY][i]
                            + tile;
                        DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].scale2++;
                        if (DAT_TileMapState::instance.AIZoneLayer[tile] != 0) {
                            DAT_TileMapState::instance.curTileX = tile
                                - DAT_ViewportRenderState::instance.translationMatrix[DAT_TileMapState::instance.curTileY]
                                      .addXgetTile;
                            MACRO_CALL_MEMBER(Navigation::PathFindingState_Func::floodFillAIZoneFlag,
                                DAT_PathFindingState::ptr)(DAT_TroopValueState::instance.attackInfo.someDistanceLimit,
                                DAT_TileMapState::instance.curTileX, DAT_TileMapState::instance.curTileY, 1);
                        }
                        break;
                    }
                }
                else {
                    if ((logic & 0x40000000) == 0
                        || DAT_TileMapState::instance.aiZoneDistanceLayers[attackedPlayerID][tile] <= 0) {
                        continue;
                    }
                    height = DAT_TileMapState::instance.DefaultHeightLayer[tile];
                    DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].moat1++;
                    DAT_TileMapState::instance.curTileIndex = tile;
                    DAT_TileMapState::instance.curTileY
                        = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
                    MACRO_RAI_GATHER_PATHCON_4
                    for (int i = 0; i < 8; i += 2) {
                        if (MACRO_CALL_MEMBER(
                                Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea,
                                DAT_PathFindingState::ptr)(playerID, DAT_TroopValueState::instance.attackInfo.startCon,
                                DAT_TileMapState::instance.specialAreasArray[i], 0)
                            == 0) {
                            continue;
                        }
                        if (DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].field89_0xfa88 >= 1000
                            || MACRO_CALL_MEMBER(TroopValueState_Func::getTileInTargetedBuildingTiles, this)(tile)
                                != FALSE) {
                            break;
                        }
                        int const neighbour
                            = DAT_TileMapState::instance.directionTranslationMatrix[DAT_TileMapState::instance.curTileY][i]
                            + tile;
                        if ((DAT_TileMapState::instance.LogicLayer[neighbour] & 0x10000100) != 0) {
                            continue;
                        }
                        int const neighbourHeight = (int)MACRO_CALL_MEMBER(
                            TileMapState_Func::getTotalHeightAtTile, DAT_TileMapState::ptr)(neighbour);
                        if (height > neighbourHeight + 16 || height < neighbourHeight - 16) {
                            continue;
                        }
                        DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].moatEntries
                            [DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].field89_0xfa88][0]
                            = tile;
                        DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].moatEntries
                            [DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].field89_0xfa88][1]
                            = DAT_TileMapState::instance.directionTranslationMatrix[DAT_TileMapState::instance.curTileY][i]
                            + tile;
                        DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].field89_0xfa88++;
                        if (DAT_TileMapState::instance.AIZoneLayer[tile] != 0) {
                            DAT_TileMapState::instance.curTileX = tile
                                - DAT_ViewportRenderState::instance.translationMatrix[DAT_TileMapState::instance.curTileY]
                                      .addXgetTile;
                            MACRO_CALL_MEMBER(Navigation::PathFindingState_Func::floodFillAIZoneFlag,
                                DAT_PathFindingState::ptr)(
                                1, DAT_TileMapState::instance.curTileX, DAT_TileMapState::instance.curTileY, 1);
                        }
                        break;
                    }
                }
            nextTile:;
            }
        }

    }
}
}
