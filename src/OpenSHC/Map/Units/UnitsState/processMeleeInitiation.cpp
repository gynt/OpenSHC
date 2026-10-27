#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/TileMapState/NeighbourFlagsAsm.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Game::GameMode;
        using OpenSHC::Map::Units::UnitLogicState;
        using OpenSHC::Map::Units::UnitType;
        using OpenSHC::Map::Units::States::UnitState;

        // FUNCTION: STRONGHOLDCRUSADER 0x00549C70
        void UnitsState::processMeleeInitiation(int unitID)

        {
            int _neighbourHeights[8];
            int _totalHeight;
            int _adjacentTiles[24];
            int _otherUnitID;
            if (this->units[unitID].canMelee != 0 && this->units[unitID].isHiddenInBuilding == 0
                && this->units[unitID].unknownMovementRelated_0x2d2 == 0
                && this->units[unitID].logicalState == OpenSHC::Map::Units::ULS_NORMAL && this->units[unitID].dying == 0
                && this->units[unitID].moveRelatedFlag != 1) {
                int _distanceThreshold;
                if (this->units[unitID].stateBasedSpeed > 0) {
                    _distanceThreshold = 270;
                } else {
                    /*
                      50 or 150 depending on selectable
                     */

                    if (this->units[unitID].isSelectable_OR_matchTime != 0) {
                        _distanceThreshold = 150;
                    } else {
                        _distanceThreshold = 50;
                    }
                }
                if (this->units[unitID].closestEnemyMicroDistance <= _distanceThreshold
                    || this->units[unitID].meleeOpponentUnitID != 0
                    || this->units[unitID].unitType == OpenSHC::Map::Units::UT_LIONSHWOLF
                    || (this->units[unitID].isAnimalOrAmbient != 0
                        && (((DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY
                                 || (100 < (int)this->unitCount))
                            && (((this->units[unitID].fixedRng ^ DAT_GameState::instance.mapAndTime.totalGameTicks)
                                    & 0xf)
                                == 0))))) {
                    _totalHeight
                        = (int)this->units[unitID].buildingHeight + (int)this->units[unitID].terrainOrClimbHeight;
                    int _playerID = (int)this->units[unitID].owner;
                    DAT_TileMapState::instance.curTileIndex = this->units[unitID].tile;
                    DAT_TileMapState::instance.curTileY
                        = (int)DAT_ViewportRenderState::instance
                              .tileTranslationMatrix_YComponent[DAT_TileMapState::instance.curTileIndex];
                    int _hasEnemyOnOwnTile = 0;
                    uint _teamBitFlags = MACRO_CALL_MEMBER(
                        OpenSHC::Game::GameStateStructures_Func::getEnemyPlayerMaskForUnit, DAT_GameState::ptr)(unitID);
                    // Handwritten assembly (0x00549D9D-0x00549F3F): "mov edx, 0", the row pointer kept on the stack with
                    // three "push esi", one-byte occupancy elements read as dwords at +/-1 and +/-2. Gathers the 5x5
                    // neighbourhood of curTileIndex whose occupancy matches _teamBitFlags into meleeNeighbourMask.
                    __asm {
                        mov edi, dword ptr ds:[NEIGHBOUR_FLAGS_TILEMAPSTATE]TileMapState.ptr_MovementDirectionTranslationMatrix
                        mov esi, dword ptr ds:[NEIGHBOUR_FLAGS_TILEMAPSTATE]TileMapState.ptr_OccupancyLayer
                        mov eax, dword ptr ds:[NEIGHBOUR_FLAGS_TILEMAPSTATE]TileMapState.curTileIndex
                        add esi, eax
                        push esi
                        push esi
                        push esi
                        mov eax, dword ptr ds:[NEIGHBOUR_FLAGS_TILEMAPSTATE]TileMapState.curTileY
                        shl eax, 0x5
                        add edi, eax
                        mov edx, 0x0
                        mov eax, dword ptr [esi + 0x1]
                        mov ebx, dword ptr [esi - 0x1]
                        and eax, _teamBitFlags
                        jz melee_e1_done
                        or edx, 0x20
                    melee_e1_done:
                        and ebx, _teamBitFlags
                        jz melee_w1_done
                        or edx, 0x2
                    melee_w1_done:
                        mov eax, dword ptr [esi + 0x2]
                        mov ebx, dword ptr [esi - 0x2]
                        and eax, _teamBitFlags
                        jz melee_e2_done
                        or edx, 0x80000
                    melee_e2_done:
                        and ebx, _teamBitFlags
                        jz melee_w2_done
                        or edx, 0x800
                    melee_w2_done:
                        mov ecx, dword ptr [edi]
                        add esi, ecx
                        mov eax, dword ptr [esi - 0x1]
                        mov ebx, dword ptr [esi + 0x1]
                        mov ecx, dword ptr [esi]
                        and eax, _teamBitFlags
                        jz melee_n1w1_done
                        or edx, 0x1
                    melee_n1w1_done:
                        and ebx, _teamBitFlags
                        jz melee_n1e1_done
                        or edx, 0x40
                    melee_n1e1_done:
                        and ecx, _teamBitFlags
                        jz melee_n1_done
                        or edx, 0x80
                    melee_n1_done:
                        mov eax, dword ptr [esi - 0x2]
                        mov ebx, dword ptr [esi + 0x2]
                        and eax, _teamBitFlags
                        jz melee_n1w2_done
                        or edx, 0x400
                    melee_n1w2_done:
                        and ebx, _teamBitFlags
                        jz melee_n1e2_done
                        or edx, 0x100000
                    melee_n1e2_done:
                        mov ecx, dword ptr [edi + 0x10]
                        pop esi
                        add esi, ecx
                        mov eax, dword ptr [esi - 0x1]
                        mov ebx, dword ptr [esi + 0x1]
                        mov ecx, dword ptr [esi]
                        and eax, _teamBitFlags
                        jz melee_s1w1_done
                        or edx, 0x4
                    melee_s1w1_done:
                        and ebx, _teamBitFlags
                        jz melee_s1e1_done
                        or edx, 0x10
                    melee_s1e1_done:
                        and ecx, _teamBitFlags
                        jz melee_s1_done
                        or edx, 0x8
                    melee_s1_done:
                        mov eax, dword ptr [esi - 0x2]
                        mov ebx, dword ptr [esi + 0x2]
                        and eax, _teamBitFlags
                        jz melee_s1w2_done
                        or edx, 0x1000
                    melee_s1w2_done:
                        and ebx, _teamBitFlags
                        jz melee_s1e2_done
                        or edx, 0x40000
                    melee_s1e2_done:
                        mov edi, dword ptr ds:[NEIGHBOUR_FLAGS_TILEMAPSTATE]TileMapState.ptr_MovementDirectionTranslationMatrix
                        pop esi
                        mov ebx, dword ptr ds:[NEIGHBOUR_FLAGS_TILEMAPSTATE]TileMapState.curTileY
                        shl ebx, 0x5
                        mov ecx, dword ptr [edi + ebx]
                        add esi, ecx
                        sub ebx, 0x20
                        mov ecx, dword ptr [edi + ebx]
                        add esi, ecx
                        mov eax, dword ptr [esi - 0x1]
                        mov ebx, dword ptr [esi + 0x1]
                        mov ecx, dword ptr [esi]
                        and eax, _teamBitFlags
                        jz melee_n2w1_done
                        or edx, 0x100
                    melee_n2w1_done:
                        and ebx, _teamBitFlags
                        jz melee_n2e1_done
                        or edx, 0x400000
                    melee_n2e1_done:
                        and ecx, _teamBitFlags
                        jz melee_n2_done
                        or edx, 0x800000
                    melee_n2_done:
                        mov eax, dword ptr [esi - 0x2]
                        mov ebx, dword ptr [esi + 0x2]
                        and eax, _teamBitFlags
                        jz melee_n2w2_done
                        or edx, 0x200
                    melee_n2w2_done:
                        and ebx, _teamBitFlags
                        jz melee_n2e2_done
                        or edx, 0x200000
                    melee_n2e2_done:
                        pop esi
                        mov ebx, dword ptr ds:[NEIGHBOUR_FLAGS_TILEMAPSTATE]TileMapState.curTileY
                        shl ebx, 0x5
                        mov ecx, dword ptr [edi + ebx + 0x10]
                        add esi, ecx
                        add ebx, 0x20
                        mov ecx, dword ptr [edi + ebx + 0x10]
                        add esi, ecx
                        mov eax, dword ptr [esi - 0x1]
                        mov ebx, dword ptr [esi + 0x1]
                        mov ecx, dword ptr [esi]
                        and eax, _teamBitFlags
                        jz melee_s2w1_done
                        or edx, 0x4000
                    melee_s2w1_done:
                        and ebx, _teamBitFlags
                        jz melee_s2e1_done
                        or edx, 0x10000
                    melee_s2e1_done:
                        and ecx, _teamBitFlags
                        jz melee_s2_done
                        or edx, 0x8000
                    melee_s2_done:
                        mov eax, dword ptr [esi - 0x2]
                        mov ebx, dword ptr [esi + 0x2]
                        and eax, _teamBitFlags
                        jz melee_s2w2_done
                        or edx, 0x2000
                    melee_s2w2_done:
                        and ebx, _teamBitFlags
                        jz melee_s2e2_done
                        or edx, 0x20000
                    melee_s2e2_done:
                        mov dword ptr ds:[NEIGHBOUR_FLAGS_TILEMAPSTATE]TileMapState.meleeNeighbourMask, edx
                    }
                    for (_otherUnitID
                        = (short)DAT_TileMapState::instance.UnitLayer[DAT_TileMapState::instance.curTileIndex];
                        _otherUnitID > 0; _otherUnitID = (short)this->units[_otherUnitID].nextUnitOnTheSameTile) {
                        if (_otherUnitID != unitID) {
                            if (this->units[unitID].owner == 0) {
                                if (this->units[unitID].unitType != this->units[_otherUnitID].unitType) {
                                    _hasEnemyOnOwnTile = 1;
                                    break;
                                }
                            } else if (DAT_GameState::instance.mapAndTime.playerTeams[_playerID]
                                != DAT_GameState::instance.mapAndTime.playerTeams[this->units[_otherUnitID].owner]) {
                                _hasEnemyOnOwnTile = 1;
                                break;
                            }
                        }
                    }
                    if ((DAT_TileMapState::instance.meleeNeighbourMask != 0) || (_hasEnemyOnOwnTile != 0)) {
                        for (int i = 0; i < 24; ++i) {
                            _adjacentTiles[i] = 0;
                        }
                        if ((DAT_TileMapState::instance.meleeNeighbourMask & 1) != 0) {
                            _adjacentTiles[0] = DAT_TileMapState::instance
                                                    .directionTranslationMatrix[DAT_TileMapState::instance.curTileY][7]
                                + this->units[unitID].tile;
                        }
                        if ((DAT_TileMapState::instance.meleeNeighbourMask & 2) != 0) {
                            _adjacentTiles[1] = DAT_TileMapState::instance
                                                    .directionTranslationMatrix[DAT_TileMapState::instance.curTileY][6]
                                + this->units[unitID].tile;
                        }
                        if ((DAT_TileMapState::instance.meleeNeighbourMask & 4) != 0) {
                            _adjacentTiles[2] = DAT_TileMapState::instance
                                                    .directionTranslationMatrix[DAT_TileMapState::instance.curTileY][5]
                                + this->units[unitID].tile;
                        }
                        if ((DAT_TileMapState::instance.meleeNeighbourMask & 8) != 0) {
                            _adjacentTiles[3] = DAT_TileMapState::instance
                                                    .directionTranslationMatrix[DAT_TileMapState::instance.curTileY][4]
                                + this->units[unitID].tile;
                        }
                        if ((DAT_TileMapState::instance.meleeNeighbourMask & 0x10) != 0) {
                            _adjacentTiles[4] = DAT_TileMapState::instance
                                                    .directionTranslationMatrix[DAT_TileMapState::instance.curTileY][3]
                                + this->units[unitID].tile;
                        }
                        if ((DAT_TileMapState::instance.meleeNeighbourMask & 0x20) != 0) {
                            _adjacentTiles[5] = DAT_TileMapState::instance
                                                    .directionTranslationMatrix[DAT_TileMapState::instance.curTileY][2]
                                + this->units[unitID].tile;
                        }
                        if ((DAT_TileMapState::instance.meleeNeighbourMask & 0x40) != 0) {
                            _adjacentTiles[6] = DAT_TileMapState::instance
                                                    .directionTranslationMatrix[DAT_TileMapState::instance.curTileY][1]
                                + this->units[unitID].tile;
                        }
                        if ((DAT_TileMapState::instance.meleeNeighbourMask & 0x80) != 0) {
                            _adjacentTiles[7] = DAT_TileMapState::instance
                                                    .directionTranslationMatrix[DAT_TileMapState::instance.curTileY][0]
                                + this->units[unitID].tile;
                        }
                        _neighbourHeights[0] = MACRO_CALL_MEMBER(
                            OpenSHC::Map::TileMapState_Func::getTotalHeightAtTile, DAT_TileMapState::ptr)(
                            DAT_TileMapState::instance
                                .directionTranslationMatrix[DAT_TileMapState::instance.curTileY][7]
                            + this->units[unitID].tile);
                        _neighbourHeights[1] = MACRO_CALL_MEMBER(
                            OpenSHC::Map::TileMapState_Func::getTotalHeightAtTile, DAT_TileMapState::ptr)(
                            DAT_TileMapState::instance
                                .directionTranslationMatrix[DAT_TileMapState::instance.curTileY][6]
                            + this->units[unitID].tile);
                        _neighbourHeights[2] = MACRO_CALL_MEMBER(
                            OpenSHC::Map::TileMapState_Func::getTotalHeightAtTile, DAT_TileMapState::ptr)(
                            DAT_TileMapState::instance
                                .directionTranslationMatrix[DAT_TileMapState::instance.curTileY][5]
                            + this->units[unitID].tile);
                        _neighbourHeights[3] = MACRO_CALL_MEMBER(
                            OpenSHC::Map::TileMapState_Func::getTotalHeightAtTile, DAT_TileMapState::ptr)(
                            DAT_TileMapState::instance
                                .directionTranslationMatrix[DAT_TileMapState::instance.curTileY][4]
                            + this->units[unitID].tile);
                        _neighbourHeights[4] = MACRO_CALL_MEMBER(
                            OpenSHC::Map::TileMapState_Func::getTotalHeightAtTile, DAT_TileMapState::ptr)(
                            DAT_TileMapState::instance
                                .directionTranslationMatrix[DAT_TileMapState::instance.curTileY][3]
                            + this->units[unitID].tile);
                        _neighbourHeights[5] = MACRO_CALL_MEMBER(
                            OpenSHC::Map::TileMapState_Func::getTotalHeightAtTile, DAT_TileMapState::ptr)(
                            DAT_TileMapState::instance
                                .directionTranslationMatrix[DAT_TileMapState::instance.curTileY][2]
                            + this->units[unitID].tile);
                        _neighbourHeights[6] = MACRO_CALL_MEMBER(
                            OpenSHC::Map::TileMapState_Func::getTotalHeightAtTile, DAT_TileMapState::ptr)(
                            DAT_TileMapState::instance
                                .directionTranslationMatrix[DAT_TileMapState::instance.curTileY][1]
                            + this->units[unitID].tile);
                        _neighbourHeights[7] = MACRO_CALL_MEMBER(
                            OpenSHC::Map::TileMapState_Func::getTotalHeightAtTile, DAT_TileMapState::ptr)(
                            DAT_TileMapState::instance
                                .directionTranslationMatrix[DAT_TileMapState::instance.curTileY][0]
                            + this->units[unitID].tile);
                        if ((DAT_TileMapState::instance.meleeNeighbourMask & 0x100) != 0) {
                            _adjacentTiles[8] = DAT_MinimapViewState::instance
                                                    .spawnMoment[DAT_TileMapState::instance.curTileY * 8 + 0x14]
                                + this->units[unitID].tile
                                + DAT_TileMapState::instance
                                      .directionTranslationMatrix[DAT_TileMapState::instance.curTileY][0];
                        }
                        if ((DAT_TileMapState::instance.meleeNeighbourMask & 0x200) != 0) {
                            _adjacentTiles[9] = DAT_MinimapViewState::instance
                                                    .spawnMoment[DAT_TileMapState::instance.curTileY * 8 + 0x13]
                                + DAT_MinimapViewState::instance
                                      .spawnMoment[DAT_TileMapState::instance.curTileY * 8 + 0x14]
                                + this->units[unitID].tile
                                + DAT_TileMapState::instance
                                      .directionTranslationMatrix[DAT_TileMapState::instance.curTileY][0];
                        }
                        if ((DAT_TileMapState::instance.meleeNeighbourMask & 0x400) != 0) {
                            _adjacentTiles[10]
                                = DAT_TileMapState::instance
                                      .directionTranslationMatrix[DAT_TileMapState::instance.curTileY][6]
                                + DAT_TileMapState::instance
                                      .directionTranslationMatrix[DAT_TileMapState::instance.curTileY][7]
                                + this->units[unitID].tile;
                        }
                        if ((DAT_TileMapState::instance.meleeNeighbourMask & 0x800) != 0) {
                            _adjacentTiles[0xb] = this->units[unitID].tile
                                + DAT_TileMapState::instance
                                        .directionTranslationMatrix[DAT_TileMapState::instance.curTileY][6]
                                    * 2;
                        }
                        if ((DAT_TileMapState::instance.meleeNeighbourMask & 0x1000) != 0) {
                            _adjacentTiles[0xc]
                                = DAT_TileMapState::instance
                                      .directionTranslationMatrix[DAT_TileMapState::instance.curTileY][5]
                                + DAT_TileMapState::instance
                                      .directionTranslationMatrix[DAT_TileMapState::instance.curTileY][6]
                                + this->units[unitID].tile;
                        }
                        if ((DAT_TileMapState::instance.meleeNeighbourMask & 0x2000) != 0) {
                            _adjacentTiles[0xd]
                                = DAT_TileMapState::instance
                                      .directionTranslationMatrix[DAT_TileMapState::instance.curTileY + 1][6]
                                + DAT_TileMapState::instance
                                      .directionTranslationMatrix[DAT_TileMapState::instance.curTileY + 1][5]
                                + DAT_TileMapState::instance
                                      .directionTranslationMatrix[DAT_TileMapState::instance.curTileY][4]
                                + this->units[unitID].tile;
                        }
                        if ((DAT_TileMapState::instance.meleeNeighbourMask & 0x4000) != 0) {
                            _adjacentTiles[0xe]
                                = DAT_TileMapState::instance
                                      .directionTranslationMatrix[DAT_TileMapState::instance.curTileY + 1][5]
                                + DAT_TileMapState::instance
                                      .directionTranslationMatrix[DAT_TileMapState::instance.curTileY][4]
                                + this->units[unitID].tile;
                        }
                        if ((DAT_TileMapState::instance.meleeNeighbourMask & 0x8000) != 0) {
                            _adjacentTiles[0xf]
                                = DAT_TileMapState::instance
                                      .directionTranslationMatrix[DAT_TileMapState::instance.curTileY + 1][4]
                                + DAT_TileMapState::instance
                                      .directionTranslationMatrix[DAT_TileMapState::instance.curTileY][4]
                                + this->units[unitID].tile;
                        }
                        if ((DAT_TileMapState::instance.meleeNeighbourMask & 0x10000) != 0) {
                            _adjacentTiles[0x10]
                                = DAT_TileMapState::instance
                                      .directionTranslationMatrix[DAT_TileMapState::instance.curTileY + 1][3]
                                + DAT_TileMapState::instance
                                      .directionTranslationMatrix[DAT_TileMapState::instance.curTileY][4]
                                + this->units[unitID].tile;
                        }
                        if ((DAT_TileMapState::instance.meleeNeighbourMask & 0x20000) != 0) {
                            _adjacentTiles[0x11]
                                = DAT_TileMapState::instance
                                      .directionTranslationMatrix[DAT_TileMapState::instance.curTileY + 1][2]
                                + DAT_TileMapState::instance
                                      .directionTranslationMatrix[DAT_TileMapState::instance.curTileY + 1][3]
                                + DAT_TileMapState::instance
                                      .directionTranslationMatrix[DAT_TileMapState::instance.curTileY][4]
                                + this->units[unitID].tile;
                        }
                        if ((DAT_TileMapState::instance.meleeNeighbourMask & 0x40000) != 0) {
                            _adjacentTiles[0x12]
                                = DAT_TileMapState::instance
                                      .directionTranslationMatrix[DAT_TileMapState::instance.curTileY][2]
                                + DAT_TileMapState::instance
                                      .directionTranslationMatrix[DAT_TileMapState::instance.curTileY][3]
                                + this->units[unitID].tile;
                        }
                        if ((DAT_TileMapState::instance.meleeNeighbourMask & 0x80000) != 0) {
                            _adjacentTiles[0x13] = this->units[unitID].tile
                                + DAT_TileMapState::instance
                                        .directionTranslationMatrix[DAT_TileMapState::instance.curTileY][2]
                                    * 2;
                        }
                        if ((DAT_TileMapState::instance.meleeNeighbourMask & 0x100000) != 0) {
                            _adjacentTiles[0x14]
                                = DAT_TileMapState::instance
                                      .directionTranslationMatrix[DAT_TileMapState::instance.curTileY][1]
                                + DAT_TileMapState::instance
                                      .directionTranslationMatrix[DAT_TileMapState::instance.curTileY][2]
                                + this->units[unitID].tile;
                        }
                        if ((DAT_TileMapState::instance.meleeNeighbourMask & 0x200000) != 0) {
                            _adjacentTiles[0x15] = DAT_MinimapViewState::instance
                                                       .spawnMoment[DAT_TileMapState::instance.curTileY * 8 + 0xe]
                                + DAT_MinimapViewState::instance
                                      .spawnMoment[DAT_TileMapState::instance.curTileY * 8 + 0xf]
                                + this->units[unitID].tile
                                + DAT_TileMapState::instance
                                      .directionTranslationMatrix[DAT_TileMapState::instance.curTileY][0];
                        }
                        if ((DAT_TileMapState::instance.meleeNeighbourMask & 0x400000) != 0) {
                            _adjacentTiles[0x16] = DAT_MinimapViewState::instance
                                                       .spawnMoment[DAT_TileMapState::instance.curTileY * 8 + 0xe]
                                + this->units[unitID].tile
                                + DAT_TileMapState::instance
                                      .directionTranslationMatrix[DAT_TileMapState::instance.curTileY][0];
                        }
                        if ((DAT_TileMapState::instance.meleeNeighbourMask & 0x800000) != 0) {
                            _adjacentTiles[0x17] = DAT_MinimapViewState::instance
                                                       .spawnMoment[DAT_TileMapState::instance.curTileY * 8 + 0xd]
                                + this->units[unitID].tile
                                + DAT_TileMapState::instance
                                      .directionTranslationMatrix[DAT_TileMapState::instance.curTileY][0];
                        }
                        if (this->units[unitID].meleeOpponentUnitID != 0) {
                            _otherUnitID = this->units[unitID].meleeOpponentUnitID;
                            if (this->units[_otherUnitID].uid == this->units[unitID].attackedUnitUID
                                && this->units[_otherUnitID].logicalState == OpenSHC::Map::Units::ULS_NORMAL
                                && this->units[_otherUnitID].dying == 0) {
                                /* -- CHECK 24 TILES AROUND UNIT -- is the unit we already fight still in reach? */
                                for (int _slot = -1; _slot < 24; ++_slot) {
                                    int _candidateTile;
                                    if (_slot == -1) {
                                        if (_hasEnemyOnOwnTile == 0) {
                                            continue;
                                        }
                                        _candidateTile = this->units[unitID].tile;
                                    } else {
                                        _candidateTile = _adjacentTiles[DAT_UnitPropertiesDefinedData::instance
                                                .meleeScanOrderByFacing[this->units[unitID].facingDirection][_slot]];
                                    }
                                    if (_candidateTile == 0) {
                                        continue;
                                    }
                                    if (abs(_totalHeight
                                            - MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getTotalHeightAtTile,
                                                DAT_TileMapState::ptr)(_candidateTile))
                                        >= 0x20) {
                                        continue;
                                    }
                                    if (_otherUnitID
                                        == MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::getEnemyUnitIDNearby,
                                            this)(unitID, _candidateTile, _totalHeight)) {
                                        MACRO_CALL_MEMBER(
                                            OpenSHC::Map::Units::UnitsState_Func::setFacingDirectionTowardUnitMicro,
                                            DAT_UnitsState::ptr)(unitID, _otherUnitID);
                                        goto _engageMelee;
                                    }
                                }
                            }
                            this->units[unitID].meleeOpponentUnitID = 0;
                            this->units[unitID].attackedUnitUID = 0;
                            this->units[unitID].pendingMeleeEngage = 0;
                        }
                        /* -- CHECK 24 TILES AROUND UNIT -- look for someone new to fight */
                        for (int _slot = -1; _slot < 24; ++_slot) {
                            int _candidateTile;
                            int _tileSlot;
                            if (_slot == -1) {
                                if (_hasEnemyOnOwnTile == 0) {
                                    continue;
                                }
                                _tileSlot = this->units[unitID].facingDirection;
                                _candidateTile = this->units[unitID].tile;
                            } else {
                                _tileSlot = DAT_UnitPropertiesDefinedData::instance
                                                .meleeScanOrderByFacing[this->units[unitID].facingDirection][_slot];
                                _candidateTile = _adjacentTiles[_tileSlot];
                            }
                            if (_candidateTile == 0) {
                                continue;
                            }
                            if (_tileSlot >= 8) {
                                if (abs(_totalHeight
                                        - _neighbourHeights
                                            [DAT_UnitPropertiesDefinedData::instance.meleeReachViaTiles[_tileSlot].x])
                                    > 0x20) {
                                    continue;
                                }
                                int _secondHeightIndex
                                    = DAT_UnitPropertiesDefinedData::instance.meleeReachViaTiles[_tileSlot].y;
                                if (_secondHeightIndex != -1) {
                                    if (abs(_totalHeight - _neighbourHeights[_secondHeightIndex]) > 0x20) {
                                        continue;
                                    }
                                }
                            }
                            _otherUnitID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::getEnemyUnitIDNearby,
                                this)(unitID, _candidateTile, _totalHeight);
                            if (_otherUnitID <= 0) {
                                continue;
                            }
                            if (this->units[_otherUnitID].logicalState != OpenSHC::Map::Units::ULS_NORMAL) {
                                continue;
                            }
                            if (this->units[_otherUnitID].dying != 0) {
                                continue;
                            }
                            if (abs((_totalHeight - this->units[_otherUnitID].buildingHeight)
                                    - this->units[_otherUnitID].terrainOrClimbHeight)
                                > 0x20) {
                                continue;
                            }
                            if ((this->units[unitID].unitType == OpenSHC::Map::Units::UT_LIONSHWOLF
                                    || this->units[unitID].unitType == OpenSHC::Map::Units::UT_CAGEDOG)
                                && this->units[_otherUnitID].isAnimalOrAmbient != 0 && _slot >= 8) {
                                continue;
                            }
                            this->units[unitID].meleeOpponentUnitID = (short)_otherUnitID;
                            this->units[unitID].attackedUnitUID = this->units[_otherUnitID].uid;
                            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setFacingDirectionTowardUnitMicro,
                                DAT_UnitsState::ptr)(unitID, _otherUnitID);
                            break;
                        }
                        if (this->units[unitID].meleeOpponentUnitID == 0) {
                        _clearMeleeEngagement:
                            this->units[unitID].pendingMeleeEngage = 0;
                            this->units[unitID].meleeOpponentUnitID = 0;
                            this->units[unitID].attackedUnitUID = 0;
                            return;
                        }
                        if (this->units[_otherUnitID].canMelee != 0
                            && this->units[_otherUnitID].meleeOpponentUnitID == 0
                            && this->units[_otherUnitID].unknownMovementRelated_0x2d2 == 0) {
                            this->units[_otherUnitID].meleeOpponentUnitID = (short)unitID;
                            this->units[_otherUnitID].attackedUnitUID = this->units[unitID].uid;
                            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setFacingDirectionTowardUnitMicro,
                                DAT_UnitsState::ptr)(_otherUnitID, unitID);
                        }
                    _engageMelee:
                        if (this->units[unitID].state.generic != OpenSHC::Map::Units::States::US_MELEE_ATTACK) {
                            if (this->units[unitID].subTileStepProgress == 8) {
                                MACRO_CALL_MEMBER(
                                    OpenSHC::Map::Units::UnitsState_Func::saveUnitStateBeforeInterruption, this)(
                                    unitID);
                                this->units[unitID].subTileStepProgress = 8;
                                this->units[unitID].state.generic = OpenSHC::Map::Units::States::US_MELEE_ATTACK;
                                this->units[unitID].SA = 0;
                                this->units[unitID].animationCycleNumber = 0;
                                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate = 0;
                            } else {
                                this->units[unitID].pendingMeleeEngage = 1;
                            }
                        }
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::processUnitAttackOtherUnit, this)(
                            DAT_CurrentUnitSlotID::instance, this->units[unitID].meleeOpponentUnitID);
                        return;
                    }
                    goto _clearMeleeEngagement;
                }
            }
            this->units[unitID].attackedUnitUID = 0;
            this->units[unitID].meleeOpponentUnitID = 0;
            this->units[unitID].pendingMeleeEngage = 0;
        }

    }
}
}
