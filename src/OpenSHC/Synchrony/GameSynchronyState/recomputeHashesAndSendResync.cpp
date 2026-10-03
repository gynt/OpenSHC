#include "../../Synchrony.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/AI/AIV/AIVSpec.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/Map/ClimbData.hpp"
#include "OpenSHC/Map/Entities/Entity.hpp"
#include "OpenSHC/Map/Moat.hpp"
#include "OpenSHC/Map/PitchDitch.hpp"
#include "OpenSHC/Map/Units/Unit.hpp"

#include "OpenSHC/Globals/DAT_AIVState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Synchrony {

    using OpenSHC::AI::AIV::AIVSpec;
    using OpenSHC::Commands::GameCommandType;
    using OpenSHC::Map::ClimbData;
    using OpenSHC::Map::Moat;
    using OpenSHC::Map::PitchDitch;
    using OpenSHC::Map::Entities::Entity;
    using OpenSHC::Map::Units::Unit;

    // FUNCTION: STRONGHOLDCRUSADER 0x0048CC90
    void GameSynchronyState::recomputeHashesAndSendResync(int dontSendSyncCommand)
    {
        int* piVar1;
        int* piVar2;
        int* piVar3;
        int* piVar4;
        Entity* address;
        short sVar5;
        short sVar6;
        short sVar7;
        short sVar8;
        short sVar9;
        short sVar10;
        short sVar11;
        short sVar12;
        short sVar13;
        short sVar14;
        short sVar15;
        short sVar16;
        int iVar17;
        undefined4 uVar18;
        uint uVar19;
        int iVar20;
        uint uVar21;
        uint uVar22;
        uint uVar23;
        uint uVar24;
        uint uVar25;
        uint uVar26;
        uint uVar27;
        uint uVar28;
        uint uVar29;
        uint uVar30;
        uint uVar31;
        uint uVar32;
        uint uVar33;
        uint uVar34;
        uint uVar35;
        uint uVar36;
        uint uVar37;
        uint _moatIndex;
        int _treeIndex;
        int _playerDataIndex;
        int _someIndex;
        short* psVar38;
        uint _pitchDitchIndex;
        int _unitIndex;
        int _buildingIndex;
        int iVar39;
        int* piVar41;
        byte* pbVar42;
        Unit* piVar40;
        Unit* piVar44;
        Unit* piVar43;
        int iVar45;
        Moat* address_00;
        ClimbData* address_01;
        PitchDitch* address_02;
        AIVSpec* address_03;
        int _hashSubTotal;
        int _entityIndex;
        int _tribeIndex;
        int _heatMapIndex;
        int _aivIndex;
        if (this->DAT_GameHalted == 0) {
            if (this->DAT_HashCountdown == 0) {
                this->HASH_HashTotal[this->currentPlayerSlotID] = 0;
                this->DAT_PlayerMatchTimes[this->currentPlayerSlotID] = DAT_GameCore::instance.mapTimeInTicks;
                _hashSubTotal = 0;
                _unitIndex = 0;
                piVar40 = &DAT_UnitsState::instance.units[0];
                do {
                    iVar39 = piVar40->field309_0x420;
                    iVar45 = piVar40->field308_0x41c;
                    piVar40->field309_0x420 = 0;
                    piVar40->field308_0x41c = 0;
                    uVar19 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash,
                        DAT_DirectionAlgorithmState::ptr)(1028, (int*)((int)(&piVar40->logicalState)));
                    piVar44 = piVar40 + 0x124;
                    iVar20 = uVar19 + piVar40->animationLeapTicksTotal + piVar40->animationSpeed
                        + piVar40->animationTicker;
                    _hashSubTotal = _hashSubTotal + iVar20;
                    this->HASH_Units[this->currentPlayerSlotID][_unitIndex] = iVar20;
                    piVar40->field308_0x41c = iVar45;
                    piVar40->field309_0x420 = iVar39;
                    _unitIndex = _unitIndex + 1;
                    piVar40 = piVar44;
                } while ((int)piVar44 < 0x16513cc);
                this->DAT_PlayerMatchTimes[this->currentPlayerSlotID * 0xc + 9] = _hashSubTotal;
                this->HASH_HashTotal[this->currentPlayerSlotID]
                    = this->HASH_HashTotal[this->currentPlayerSlotID] + _hashSubTotal;
                _buildingIndex = 0;
                _hashSubTotal = 0;
                psVar38 = &DAT_BuildingsState::instance.buildings[0].animationIndex;
                do {
                    sVar5 = psVar38[0x16e];
                    psVar38[0x16e] = 0;
                    uVar19 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash,
                        DAT_DirectionAlgorithmState::ptr)(0x25c, (int*)((int)((psVar38 + 0x58))));
                    piVar41 = (int*)(psVar38 + 0x1a);
                    piVar1 = (int*)(psVar38 + 0x18);
                    sVar6 = *psVar38;
                    piVar2 = (int*)(psVar38 + 0x16);
                    piVar3 = (int*)(psVar38 + 0x14);
                    psVar38[0x16e] = sVar5;
                    piVar4 = (int*)(psVar38 + -8);
                    psVar38 = psVar38 + 0x196;
                    iVar39 = (int)sVar6 + uVar19 + *piVar41 + *piVar1 + *piVar2 + *piVar3 + *piVar4;
                    _hashSubTotal = _hashSubTotal + iVar39;
                    this->HASH_Buildings[this->currentPlayerSlotID][_buildingIndex] = iVar39;
                    _buildingIndex = _buildingIndex + 1;
                } while ((int)psVar38 < 0x1124d14);
                this->DAT_PlayerMatchTimes[this->currentPlayerSlotID * 0xc + 10] = _hashSubTotal;
                this->HASH_HashTotal[this->currentPlayerSlotID]
                    = this->HASH_HashTotal[this->currentPlayerSlotID] + _hashSubTotal;
                iVar39 = 0;
                _treeIndex = 0;
                psVar38 = &DAT_LandscapeState::instance.trees[0].state;
                do {
                    uVar19 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash,
                        DAT_DirectionAlgorithmState::ptr)(88, (int*)((int)(psVar38)));
                    psVar38 = psVar38 + 0x4e;
                    iVar39 = iVar39 + uVar19;
                    this->HASH_Trees[this->currentPlayerSlotID][_treeIndex] = uVar19;
                    _treeIndex = _treeIndex + 1;
                } while ((int)psVar38 < 0xf78f58);
                this->DAT_PlayerMatchTimes[this->currentPlayerSlotID * 0xc + 0xb] = iVar39;
                this->HASH_HashTotal[this->currentPlayerSlotID]
                    = this->HASH_HashTotal[this->currentPlayerSlotID] + iVar39;
                iVar39 = 0;
                piVar41 = &DAT_TribesState::instance.tribes[0].owner;
                _tribeIndex = 0;
                do {
                    uVar19 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash,
                        DAT_DirectionAlgorithmState::ptr)(816, piVar41);
                    piVar41 = piVar41 + 0xcd;
                    iVar39 = iVar39 + uVar19;
                    this->HASH_Tribes[this->currentPlayerSlotID][_tribeIndex] = uVar19;
                    _tribeIndex = _tribeIndex + 1;
                } while ((int)piVar41 < 0x176238c);
                this->DAT_PlayerMatchTimes[this->currentPlayerSlotID * 0xc + 0xc] = iVar39;
                this->HASH_HashTotal[this->currentPlayerSlotID]
                    = this->HASH_HashTotal[this->currentPlayerSlotID] + iVar39;
                _hashSubTotal = 0;
                piVar43 = (OpenSHC::Map::Units::Unit*)(&DAT_GameState::instance.playerDataArray[0].someAiCountdown3);
                _playerDataIndex = 0;
                do {
                    iVar39 = piVar43->animationFrame;
                    iVar45 = piVar43->animationSpeed;
                    iVar20 = piVar43->woodCutterChopsCount;
                    iVar17 = piVar43->animationTicker;
                    uVar18 = *(undefined4*)(piVar43->pathPlanStart + 0x6e);
                    pbVar42 = piVar43->pathPlanStart;
                    pbVar42[0x6e] = 0;
                    pbVar42[0x6f] = 0;
                    pbVar42[0x70] = 0;
                    pbVar42[0x71] = 0;
                    piVar43->woodCutterChopsCount = 0;
                    piVar43->animationFrame = 0;
                    piVar43->animationSpeed = 0;
                    piVar43->animationTicker = 0;
                    uVar19 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash,
                        DAT_DirectionAlgorithmState::ptr)(14748, (int*)((int)(piVar43 + -0xe13)));
                    _hashSubTotal = _hashSubTotal + uVar19;
                    this->HASH_PlayerDatas[this->currentPlayerSlotID][_playerDataIndex] = uVar19;
                    piVar43->animationSpeed = iVar45;
                    piVar43->animationTicker = iVar17;
                    piVar43->animationFrame = iVar39;
                    piVar43->woodCutterChopsCount = iVar20;
                    *(undefined4*)(piVar43->pathPlanStart + 0x6e) = uVar18;
                    piVar43 = piVar43 + 0xe7d;
                    _playerDataIndex = _playerDataIndex + 1;
                } while ((int)piVar43 < 0x1180030);
                this->DAT_PlayerMatchTimes[this->currentPlayerSlotID * 0xc + 0xd] = _hashSubTotal;
                this->HASH_HashTotal[this->currentPlayerSlotID]
                    = this->HASH_HashTotal[this->currentPlayerSlotID] + _hashSubTotal;
                iVar39 = 0;
                piVar41 = &DAT_GameState::instance.mapAndTime.field192_0x194;
                _someIndex = 0;
                do {
                    iVar45 = _someIndex;
                    uVar19 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash,
                        DAT_DirectionAlgorithmState::ptr)(14566, piVar41);
                    piVar41 = (int*)((int)piVar41 + 14566);
                    iVar39 = iVar39 + uVar19;
                    this->HASH_Section1023[this->currentPlayerSlotID][iVar45] = uVar19;
                    _someIndex = iVar45 + 1;
                } while ((int)piVar41 < 0x11bc94c);
                uVar19 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash,
                    DAT_DirectionAlgorithmState::ptr)(0x10,
                    (int*)((
                        int)(((int)DAT_GameState::instance.mapAndTime.signpostsMapEdge + iVar45 * 0x38e6 + 0x1022))));
                this->HASH_Section1023[this->currentPlayerSlotID][iVar45 + 1] = uVar19;
                uVar21 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash,
                    DAT_DirectionAlgorithmState::ptr)(
                    0x330, (int*)((int)(&DAT_AIVState::instance.mapExtraInfo.totalWoodAvailable)));
                iVar39 = iVar39 + uVar19 + uVar21;
                this->HASH_Section1023[this->currentPlayerSlotID][0x13] = uVar21;
                this->DAT_PlayerMatchTimes[this->currentPlayerSlotID * 0xc + 0xe] = iVar39;
                this->HASH_HashTotal[this->currentPlayerSlotID]
                    = this->HASH_HashTotal[this->currentPlayerSlotID] + iVar39;
                piVar41 = DAT_TileMapState::instance.LogicLayer;
                iVar45 = 0;
                iVar39 = 0;
                do {
                    uVar19 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash,
                        DAT_DirectionAlgorithmState::ptr)(2512, piVar41);
                    piVar41 = piVar41 + 0x274;
                    iVar45 = iVar45 + uVar19;
                    this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[0].componentArray[iVar39]
                        = uVar19;
                    iVar39 = iVar39 + 1;
                } while ((int)piVar41 < 0x1c46b68);
                psVar38 = DAT_TileMapState::instance.BuildingLayer;
                iVar39 = 0;
                do {
                    this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[1].componentArray[iVar39] = 0;
                    this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[2].componentArray[iVar39] = 0;
                    /*
                      tree and rock id tile map
                     */
                    uVar19 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash,
                        DAT_DirectionAlgorithmState::ptr)(2512, (int*)((int)((psVar38 + -0x13a10))));
                    this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[3].componentArray[iVar39]
                        = uVar19;
                    /*
                      building id tile map
                     */
                    uVar21 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash,
                        DAT_DirectionAlgorithmState::ptr)(0x9d0, (int*)((int)(psVar38)));
                    this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[4].componentArray[iVar39]
                        = uVar21;
                    /*
                      unit id tile map
                     */
                    uVar22 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash,
                        DAT_DirectionAlgorithmState::ptr)(0x9d0, (int*)((int)((psVar38 + 0x1d718))));
                    this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[5].componentArray[iVar39]
                        = uVar22;
                    /*
                      entity id tile map
                     */
                    uVar23 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash,
                        DAT_DirectionAlgorithmState::ptr)(0x9d0, (int*)((int)((psVar38 + 0x31128))));
                    this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[6].componentArray[iVar39]
                        = uVar23;
                    this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[7].componentArray[iVar39] = 0;
                    /*
                      area id tile map
                     */
                    uVar24 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash,
                        DAT_DirectionAlgorithmState::ptr)(0x9d0, (int*)((int)((psVar38 + 0xb0a90))));
                    this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[8].componentArray[iVar39]
                        = uVar24;
                    psVar38 = psVar38 + 0x4e8;
                    iVar45 = iVar45 + uVar19 + uVar21 + uVar22 + uVar23 + uVar24;
                    this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[9].componentArray[iVar39] = 0;
                    iVar39 = iVar39 + 1;
                } while ((int)psVar38 < 0x1cbcfb8);
                pbVar42 = DAT_TileMapState::instance.WallOwnerLayer;
                iVar39 = 0;
                do {
                    uVar19 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash,
                        DAT_DirectionAlgorithmState::ptr)(0x9d0, (int*)((int)((pbVar42 + 0x62250))));
                    this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[10].componentArray[iVar39]
                        = uVar19;
                    this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[0xb].componentArray[iVar39] = 0;
                    uVar21 = MACRO_CALL_MEMBER(
                        OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeMaskedBitAccumulator,
                        DAT_DirectionAlgorithmState::ptr)(2512, (uint*)((int)(pbVar42)), 0x7070707);
                    this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[0xc].componentArray[iVar39]
                        = uVar21;
                    uVar22 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash,
                        DAT_DirectionAlgorithmState::ptr)(0x9d0, (int*)((int)((pbVar42 + 0xc44a0))));
                    this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[0xd].componentArray[iVar39]
                        = uVar22;
                    uVar23 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash,
                        DAT_DirectionAlgorithmState::ptr)(0x9d0, (int*)((int)((pbVar42 + 0xd7eb0))));
                    this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[0xe].componentArray[iVar39]
                        = uVar23;
                    uVar24 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash,
                        DAT_DirectionAlgorithmState::ptr)(0x9d0, (int*)((int)((pbVar42 + -0x27420))));
                    this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[0xf].componentArray[iVar39]
                        = uVar24;
                    uVar25 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash,
                        DAT_DirectionAlgorithmState::ptr)(0x9d0, (int*)((int)((pbVar42 + 0x14db10))));
                    this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[0x10].componentArray[iVar39]
                        = uVar25;
                    uVar26 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash,
                        DAT_DirectionAlgorithmState::ptr)(0x9d0, (int*)((int)((pbVar42 + 0x13a100))));
                    this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[0x11].componentArray[iVar39]
                        = uVar26;
                    uVar27 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash,
                        DAT_DirectionAlgorithmState::ptr)(0x9d0, (int*)((int)((pbVar42 + 0x174f30))));
                    this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[0x12].componentArray[iVar39]
                        = uVar27;
                    uVar28 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash,
                        DAT_DirectionAlgorithmState::ptr)(0x9d0, (int*)((int)((pbVar42 + 0x161520))));
                    this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[0x13].componentArray[iVar39]
                        = uVar28;
                    uVar29 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash,
                        DAT_DirectionAlgorithmState::ptr)(0x9d0, (int*)((int)((pbVar42 + 0x188940))));
                    this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[0x14].componentArray[iVar39]
                        = uVar29;
                    uVar30 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash,
                        DAT_DirectionAlgorithmState::ptr)(0x9d0, (int*)((int)((pbVar42 + 0x19c350))));
                    this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[0x15].componentArray[iVar39]
                        = uVar30;
                    uVar31 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash,
                        DAT_DirectionAlgorithmState::ptr)(0x9d0, (int*)((int)((pbVar42 + 0x1afd60))));
                    this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[0x16].componentArray[iVar39]
                        = uVar31;
                    uVar32 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash,
                        DAT_DirectionAlgorithmState::ptr)(0x9d0, (int*)((int)((pbVar42 + 0x1c3770))));
                    this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[0x17].componentArray[iVar39]
                        = uVar32;
                    uVar33 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash,
                        DAT_DirectionAlgorithmState::ptr)(0x9d0, (int*)((int)((pbVar42 + 0x1d7180))));
                    this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[0x18].componentArray[iVar39]
                        = uVar33;
                    uVar34 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash,
                        DAT_DirectionAlgorithmState::ptr)(0x9d0, (int*)((int)((pbVar42 + 0x1eab90))));
                    this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[0x19].componentArray[iVar39]
                        = uVar34;
                    uVar35 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash,
                        DAT_DirectionAlgorithmState::ptr)(0x9d0, (int*)((int)((pbVar42 + 0x1fe5a0))));
                    this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[0x1a].componentArray[iVar39]
                        = uVar35;
                    uVar36 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash,
                        DAT_DirectionAlgorithmState::ptr)(0x9d0, (int*)((int)((pbVar42 + 0x211fb0))));
                    this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[0x1b].componentArray[iVar39]
                        = uVar36;
                    uVar37 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash,
                        DAT_DirectionAlgorithmState::ptr)(0x9d0, (int*)((int)((pbVar42 + 0x2259c0))));
                    pbVar42 = pbVar42 + 0x9d0;
                    iVar45 = iVar45 + uVar19 + uVar21 + uVar22 + uVar23 + uVar24 + uVar25 + uVar26 + uVar27 + uVar28
                        + uVar29 + uVar30 + uVar31 + uVar32 + uVar33 + uVar34 + uVar35 + uVar36 + uVar37;
                    this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[0x1c].componentArray[iVar39]
                        = uVar37;
                    iVar39 = iVar39 + 1;
                } while ((int)pbVar42 < 0x1d6da58);
                this->DAT_PlayerMatchTimes[this->currentPlayerSlotID * 0xc + 0xf] = iVar45;
                this->HASH_HashTotal[this->currentPlayerSlotID]
                    = this->HASH_HashTotal[this->currentPlayerSlotID] + iVar45;
                _hashSubTotal = 0;
                _entityIndex = 25;
                psVar38 = &DAT_EntityState::instance.entityArray[0x19].x1;
                do {
                    sVar5 = psVar38[8];
                    sVar6 = *psVar38;
                    sVar7 = psVar38[1];
                    sVar8 = psVar38[6];
                    sVar9 = psVar38[7];
                    sVar10 = psVar38[10];
                    sVar11 = psVar38[0x59];
                    iVar39 = ((Entity*)(psVar38 + -6))->graphicType2;
                    address = (Entity*)(psVar38 + -6);
                    iVar45 = *(int*)(psVar38 + 0x5c);
                    sVar12 = psVar38[0x5a];
                    sVar13 = psVar38[0x5e];
                    sVar14 = psVar38[0x5f];
                    sVar15 = psVar38[0x60];
                    sVar16 = psVar38[0x61];
                    psVar38[8] = 0;
                    *psVar38 = 0;
                    psVar38[1] = 0;
                    psVar38[6] = 0;
                    psVar38[7] = 0;
                    address->graphicType2 = 0;
                    psVar38[10] = 0;
                    psVar38[0x61] = 0;
                    psVar38[0x60] = 0;
                    psVar38[0x5f] = 0;
                    psVar38[0x5e] = 0;
                    *(int*)(psVar38 + 0x5c) = 0;
                    psVar38[0x5a] = 0;
                    psVar38[0x59] = 0;
                    uVar19 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash,
                        DAT_DirectionAlgorithmState::ptr)(0xe8, (int*)((int)(address)));
                    psVar38[8] = sVar5;
                    *psVar38 = sVar6;
                    psVar38[1] = sVar7;
                    psVar38[6] = sVar8;
                    psVar38[7] = sVar9;
                    address->graphicType2 = iVar39;
                    psVar38[10] = sVar10;
                    psVar38[0x59] = sVar11;
                    _hashSubTotal = _hashSubTotal + uVar19;
                    *(int*)(psVar38 + 0x5c) = iVar45;
                    psVar38[0x5a] = sVar12;
                    psVar38[0x60] = sVar15;
                    psVar38[0x5e] = sVar13;
                    psVar38[0x61] = sVar16;
                    psVar38[0x5f] = sVar14;
                    this->HASH_Entities[this->currentPlayerSlotID][_entityIndex] = uVar19;
                    _entityIndex = _entityIndex + 1;
                    psVar38 = psVar38 + 0x74;
                } while ((int)psVar38 < 0x23fa1e0);
                this->DAT_PlayerMatchTimes[this->currentPlayerSlotID * 0xc + 0x10] = _hashSubTotal;
                this->HASH_HashTotal[this->currentPlayerSlotID]
                    = this->HASH_HashTotal[this->currentPlayerSlotID] + _hashSubTotal;
                _hashSubTotal = 0;
                uVar19 = 0;
                address_00 = DAT_TileMapState::instance.moats;
                do {
                    uVar21 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash,
                        DAT_DirectionAlgorithmState::ptr)(1600, (int*)((int)(address_00)));
                    _hashSubTotal = _hashSubTotal + uVar21;
                    _moatIndex = uVar19 / 100;
                    address_00 = address_00 + 100;
                    uVar19 = uVar19 + 100;
                    this->HASH_Moats[this->currentPlayerSlotID][_moatIndex] = uVar21;
                } while ((int)address_00 < 0x1fd2278);
                this->DAT_PlayerMatchTimes[this->currentPlayerSlotID * 0xc + 0x11] = _hashSubTotal;
                this->HASH_HashTotal[this->currentPlayerSlotID]
                    = this->HASH_HashTotal[this->currentPlayerSlotID] + _hashSubTotal;
                _hashSubTotal = 0;
                address_01 = DAT_PathFindingState::instance.climbData;
                iVar39 = 0;
                do {
                    uVar19 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash,
                        DAT_DirectionAlgorithmState::ptr)(516, (int*)((int)(&address_01->canBeUsed)));
                    _hashSubTotal = _hashSubTotal + uVar19;
                    address_01 = address_01 + 1;
                    this->HASH_ClimbData[this->currentPlayerSlotID][iVar39] = uVar19;
                    iVar39 = iVar39 + 1;
                } while ((int)address_01 < 0x12d5c6c);
                this->DAT_PlayerMatchTimes[this->currentPlayerSlotID * 0xc + 0x12] = _hashSubTotal;
                this->HASH_HashTotal[this->currentPlayerSlotID]
                    = this->HASH_HashTotal[this->currentPlayerSlotID] + _hashSubTotal;
                _hashSubTotal = 0;
                _pitchDitchIndex = 0;
                address_02 = DAT_TileMapState::instance.pitchDitches;
                do {
                    uVar19 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash,
                        DAT_DirectionAlgorithmState::ptr)(2000, (int*)((int)(&address_02->tile)));
                    _hashSubTotal = _hashSubTotal + uVar19;
                    uVar21 = _pitchDitchIndex / 100;
                    address_02 = address_02 + 100;
                    _pitchDitchIndex = _pitchDitchIndex + 100;
                    this->HASH_PitchDitches[this->currentPlayerSlotID][uVar21] = uVar19;
                } while ((int)address_02 < 0x1fe5b0c);
                this->DAT_PlayerMatchTimes[this->currentPlayerSlotID * 0xc + 0x13] = _hashSubTotal;
                this->HASH_HashTotal[this->currentPlayerSlotID]
                    = this->HASH_HashTotal[this->currentPlayerSlotID] + _hashSubTotal;
                iVar39 = 0;
                do {
                    iVar45 = iVar39 + 1;
                    this->HASH_Unknown2[this->currentPlayerSlotID][iVar39] = 0;
                    iVar39 = iVar45;
                } while (iVar45 < 40);
                this->DAT_PlayerMatchTimes[this->currentPlayerSlotID * 0xc + 0x14] = 0;
                _hashSubTotal = 0;
                address_03 = DAT_AIVState::instance.aivs;
                _aivIndex = 0;
                do {
                    uVar19 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash,
                        DAT_DirectionAlgorithmState::ptr)(28056, (int*)((int)(&address_03->playerID)));
                    _hashSubTotal = _hashSubTotal + uVar19;
                    address_03 = address_03 + 1;
                    this->HASH_AIVS[this->currentPlayerSlotID][_aivIndex] = uVar19;
                    _aivIndex = _aivIndex + 1;
                } while ((int)address_03 < 0x18a450c);
                this->DAT_PlayerMatchTimes[this->currentPlayerSlotID * 0xc + 0x15] = _hashSubTotal;
                this->HASH_HashTotal[this->currentPlayerSlotID]
                    = this->HASH_HashTotal[this->currentPlayerSlotID] + _hashSubTotal;
                _hashSubTotal = 0;
                _heatMapIndex = 0x18c37f4;
                iVar39 = 0;
                do {
                    /*
                      fixme: it is wasteful to network latency to send the heatmap because it is a   derivative of the
                      map state, as long as the map and tree state is correct,   this is unnecessary
                     */
                    uVar19 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash,
                        DAT_DirectionAlgorithmState::ptr)(3840, (int*)((int)(_heatMapIndex)));
                    _hashSubTotal = _hashSubTotal + uVar19;
                    _heatMapIndex = _heatMapIndex + 0xf00;
                    this->HASH_HeatMaps[this->currentPlayerSlotID][iVar39] = uVar19;
                    iVar39 = iVar39 + 1;
                } while (_heatMapIndex < 0x190e7f4);
                this->DAT_PlayerMatchTimes[this->currentPlayerSlotID * 0xc + 0x16] = _hashSubTotal;
                this->HASH_HashTotal[this->currentPlayerSlotID]
                    = this->HASH_HashTotal[this->currentPlayerSlotID] + _hashSubTotal;
                if (dontSendSyncCommand == 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, this)(
                        OpenSHC::Commands::GCT_ANNOUNCE_PLAYER_INFORMATION_AVAILABLE_AIVSSPECIALTRANSMITLOGIC);
                }
            } else {
                this->DAT_HashCountdown = this->DAT_HashCountdown + -1;
            }
        }
    }

}
}
