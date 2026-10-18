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
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

#include "string.h"

namespace OpenSHC {
namespace Synchrony {

    using AI::AIV::AIVSpec;
    using Commands::GameCommandType;
    using Map::ClimbData;
    using Map::Moat;
    using Map::PitchDitch;
    using Map::Entities::Entity;
    using Map::Units::Unit;

    // FUNCTION: STRONGHOLDCRUSADER 0x0048CC90
    void GameSynchronyState::recomputeHashesAndSendResync(int dontSendSyncCommand)
    {
        int* piVar1;
        int* piVar2;
        int* piVar3;
        int* piVar4;
        Entity* address;
        int sVar5;
        int sVar6;
        int sVar7;
        int sVar8;
        int sVar9;
        int sVar10;
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
        int _climbIndex;
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
        if (this->DAT_GameHalted) {
            return;
        }
        if (this->DAT_HashCountdown) {
            this->DAT_HashCountdown = this->DAT_HashCountdown + -1;
            return;
        }
        this->HASH_HashTotal[this->currentPlayerSlotID] = 0;
        this->DAT_PlayerMatchTimes[this->currentPlayerSlotID] = DAT_GameCore::instance.mapTimeInTicks;
        _hashSubTotal = 0;
        for (_unitIndex = 0; _unitIndex < 2500; _unitIndex = _unitIndex + 1) {
            iVar39 = DAT_UnitsState::instance.units[_unitIndex].field309_0x420;
            iVar45 = DAT_UnitsState::instance.units[_unitIndex].field308_0x41c;
            DAT_UnitsState::instance.units[_unitIndex].field309_0x420 = 0;
            DAT_UnitsState::instance.units[_unitIndex].field308_0x41c = 0;
            uVar19 = MACRO_CALL_MEMBER(Map::Navigation::DirectionAlgorithmState_Func::computeHash,
                DAT_DirectionAlgorithmState::ptr)(1028, (int*)&DAT_UnitsState::instance.units[_unitIndex].logicalState);
            iVar20 = uVar19 + DAT_UnitsState::instance.units[_unitIndex].animationLeapTicksTotal
                + DAT_UnitsState::instance.units[_unitIndex].animationSpeed
                + DAT_UnitsState::instance.units[_unitIndex].animationTicker;
            _hashSubTotal = _hashSubTotal + iVar20;
            this->HASH_Units[this->currentPlayerSlotID][_unitIndex] = iVar20;
            DAT_UnitsState::instance.units[_unitIndex].field308_0x41c = iVar45;
            DAT_UnitsState::instance.units[_unitIndex].field309_0x420 = iVar39;
        }
        this->DAT_PlayerMatchTimes[this->currentPlayerSlotID * 0xc + 9] = _hashSubTotal;
        this->HASH_HashTotal[this->currentPlayerSlotID]
            = this->HASH_HashTotal[this->currentPlayerSlotID] + _hashSubTotal;
        _hashSubTotal = 0;
        for (_buildingIndex = 0; _buildingIndex < 2000; _buildingIndex = _buildingIndex + 1) {
            sVar5 = *(short*)DAT_BuildingsState::instance.buildings[_buildingIndex].padding_0x2fc;
            *(short*)DAT_BuildingsState::instance.buildings[_buildingIndex].padding_0x2fc = 0;
            uVar19 = MACRO_CALL_MEMBER(
                Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(
                0x25c, (int*)&DAT_BuildingsState::instance.buildings[_buildingIndex].logicalState);
            *(short*)DAT_BuildingsState::instance.buildings[_buildingIndex].padding_0x2fc = sVar5;
            sVar6 = DAT_BuildingsState::instance.buildings[_buildingIndex].animationIndex;
            iVar39 = (int)sVar6 + uVar19 + DAT_BuildingsState::instance.buildings[_buildingIndex].extraAnimationFrame3
                + DAT_BuildingsState::instance.buildings[_buildingIndex].extraAnimationFrame2
                + DAT_BuildingsState::instance.buildings[_buildingIndex].extraAnimationFrame1
                + DAT_BuildingsState::instance.buildings[_buildingIndex].campgroundVclock
                + DAT_BuildingsState::instance.buildings[_buildingIndex].animAdvanceThrottle;
            _hashSubTotal = _hashSubTotal + iVar39;
            this->HASH_Buildings[this->currentPlayerSlotID][_buildingIndex] = iVar39;
        }
        this->DAT_PlayerMatchTimes[this->currentPlayerSlotID * 0xc + 10] = _hashSubTotal;
        this->HASH_HashTotal[this->currentPlayerSlotID]
            = this->HASH_HashTotal[this->currentPlayerSlotID] + _hashSubTotal;
        iVar39 = 0;
        for (_treeIndex = 0; _treeIndex < 2000; _treeIndex = _treeIndex + 1) {
            uVar19 = MACRO_CALL_MEMBER(Map::Navigation::DirectionAlgorithmState_Func::computeHash,
                DAT_DirectionAlgorithmState::ptr)(88, (int*)&DAT_LandscapeState::instance.trees[_treeIndex].state);
            iVar39 = iVar39 + uVar19;
            this->HASH_Trees[this->currentPlayerSlotID][_treeIndex] = uVar19;
        }
        this->DAT_PlayerMatchTimes[this->currentPlayerSlotID * 0xc + 0xb] = iVar39;
        this->HASH_HashTotal[this->currentPlayerSlotID] = this->HASH_HashTotal[this->currentPlayerSlotID] + iVar39;
        iVar39 = 0;
        for (_tribeIndex = 0; _tribeIndex < 1250; _tribeIndex = _tribeIndex + 1) {
            uVar19 = MACRO_CALL_MEMBER(Map::Navigation::DirectionAlgorithmState_Func::computeHash,
                DAT_DirectionAlgorithmState::ptr)(816, &DAT_TribesState::instance.tribes[_tribeIndex].owner);
            iVar39 = iVar39 + uVar19;
            this->HASH_Tribes[this->currentPlayerSlotID][_tribeIndex] = uVar19;
        }
        this->DAT_PlayerMatchTimes[this->currentPlayerSlotID * 0xc + 0xc] = iVar39;
        this->HASH_HashTotal[this->currentPlayerSlotID] = this->HASH_HashTotal[this->currentPlayerSlotID] + iVar39;
        _hashSubTotal = 0;
        for (_playerDataIndex = 0; _playerDataIndex < 9; _playerDataIndex = _playerDataIndex + 1) {
            iVar39 = DAT_GameState::instance.playerDataArray[_playerDataIndex].someAiCountdown5;
            iVar45 = DAT_GameState::instance.playerDataArray[_playerDataIndex].someAiCountdown4;
            iVar20 = DAT_GameState::instance.playerDataArray[_playerDataIndex].someAiCountdown6;
            iVar17 = DAT_GameState::instance.playerDataArray[_playerDataIndex].someAiCountdown3;
            uVar18 = DAT_GameState::instance.playerDataArray[_playerDataIndex].ignitionTime;
            DAT_GameState::instance.playerDataArray[_playerDataIndex].ignitionTime = 0;
            memset(&DAT_GameState::instance.playerDataArray[_playerDataIndex].someAiCountdown3, 0, 16);
            uVar19 = MACRO_CALL_MEMBER(
                Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(
                14748, (int*)DAT_GameState::instance.playerDataArray[_playerDataIndex].padding_0x58);
            _hashSubTotal = _hashSubTotal + uVar19;
            this->HASH_PlayerDatas[this->currentPlayerSlotID][_playerDataIndex] = uVar19;
            DAT_GameState::instance.playerDataArray[_playerDataIndex].someAiCountdown4 = iVar45;
            DAT_GameState::instance.playerDataArray[_playerDataIndex].someAiCountdown3 = iVar17;
            DAT_GameState::instance.playerDataArray[_playerDataIndex].someAiCountdown5 = iVar39;
            DAT_GameState::instance.playerDataArray[_playerDataIndex].someAiCountdown6 = iVar20;
            DAT_GameState::instance.playerDataArray[_playerDataIndex].ignitionTime = uVar18;
        }
        this->DAT_PlayerMatchTimes[this->currentPlayerSlotID * 0xc + 0xd] = _hashSubTotal;
        this->HASH_HashTotal[this->currentPlayerSlotID]
            = this->HASH_HashTotal[this->currentPlayerSlotID] + _hashSubTotal;
        iVar39 = 0;
        for (iVar45 = 0; iVar45 < 18; iVar45 = iVar45 + 1) {
            uVar19 = MACRO_CALL_MEMBER(
                Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(
                14566, (int*)((int)&DAT_GameState::instance.mapAndTime.syncedStateBase + iVar45 * 14566));
            iVar39 = iVar39 + uVar19;
            this->HASH_Section1023[this->currentPlayerSlotID][iVar45] = uVar19;
        }
        iVar45 = 17;
        uVar19 = MACRO_CALL_MEMBER(
            Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(
            0x10, (int*)((int)(((int)DAT_GameState::instance.mapAndTime.signpostsMapEdge + iVar45 * 0x38e6 + 0x1022))));
        this->HASH_Section1023[this->currentPlayerSlotID][iVar45 + 1] = uVar19;
        uVar21 = MACRO_CALL_MEMBER(
            Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(
            0x330, (int*)((int)(&DAT_AIVState::instance.mapExtraInfo.totalWoodAvailable)));
        iVar39 = iVar39 + uVar19 + uVar21;
        this->HASH_Section1023[this->currentPlayerSlotID][0x13] = uVar21;
        this->DAT_PlayerMatchTimes[this->currentPlayerSlotID * 0xc + 0xe] = iVar39;
        this->HASH_HashTotal[this->currentPlayerSlotID] = this->HASH_HashTotal[this->currentPlayerSlotID] + iVar39;
        iVar45 = 0;
        for (iVar39 = 0; iVar39 < 128; iVar39 = iVar39 + 1) {
            uVar19 = MACRO_CALL_MEMBER(Map::Navigation::DirectionAlgorithmState_Func::computeHash,
                DAT_DirectionAlgorithmState::ptr)(2512, DAT_TileMapState::instance.LogicLayer + iVar39 * 0x274);
            iVar45 = iVar45 + uVar19;
            this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[0].componentArray[iVar39] = uVar19;
        }
        for (iVar39 = 0; iVar39 < 128; iVar39 = iVar39 + 1) {
            this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[1].componentArray[iVar39] = 0;
            this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[2].componentArray[iVar39] = 0;
            /*
              tree and rock id tile map
             */
            uVar19 = MACRO_CALL_MEMBER(
                Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(
                2512, (int*)(DAT_TileMapState::instance.OrganismLayer + iVar39 * 0x4e8));
            this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[3].componentArray[iVar39] = uVar19;
            /*
              building id tile map
             */
            uVar21 = MACRO_CALL_MEMBER(
                Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(
                0x9d0, (int*)(DAT_TileMapState::instance.BuildingLayer + iVar39 * 0x4e8));
            this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[4].componentArray[iVar39] = uVar21;
            /*
              unit id tile map
             */
            uVar22 = MACRO_CALL_MEMBER(Map::Navigation::DirectionAlgorithmState_Func::computeHash,
                DAT_DirectionAlgorithmState::ptr)(0x9d0, (int*)(DAT_TileMapState::instance.UnitLayer + iVar39 * 0x4e8));
            this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[5].componentArray[iVar39] = uVar22;
            /*
              entity id tile map
             */
            uVar23 = MACRO_CALL_MEMBER(
                Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(
                0x9d0, (int*)(DAT_TileMapState::instance.EntityLayer + iVar39 * 0x4e8));
            this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[6].componentArray[iVar39] = uVar23;
            this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[7].componentArray[iVar39] = 0;
            /*
              area id tile map
             */
            uVar24 = MACRO_CALL_MEMBER(
                Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(
                0x9d0, (int*)(DAT_TileMapState::instance.PathConnectionLayer + iVar39 * 0x4e8));
            this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[8].componentArray[iVar39] = uVar24;
            iVar45 = iVar45 + uVar19 + uVar21 + uVar22 + uVar23 + uVar24;
            this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[9].componentArray[iVar39] = 0;
        }
        for (iVar39 = 0; iVar39 < 128; iVar39 = iVar39 + 1) {
            uVar19 = MACRO_CALL_MEMBER(
                Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(
                0x9d0, (int*)(DAT_TileMapState::instance.DamageLayer + iVar39 * 0x9d0));
            this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[10].componentArray[iVar39] = uVar19;
            this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[0xb].componentArray[iVar39] = 0;
            uVar21 = MACRO_CALL_MEMBER(Map::Navigation::DirectionAlgorithmState_Func::computeMaskedBitAccumulator,
                DAT_DirectionAlgorithmState::ptr)(
                2512, (uint*)(DAT_TileMapState::instance.WallOwnerLayer + iVar39 * 0x9d0), 0x7070707);
            this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[0xc].componentArray[iVar39] = uVar21;
            uVar22 = MACRO_CALL_MEMBER(
                Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(
                0x9d0, (int*)(DAT_TileMapState::instance.PathLinkageLayer + iVar39 * 0x9d0));
            this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[0xd].componentArray[iVar39] = uVar22;
            uVar23 = MACRO_CALL_MEMBER(
                Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(
                0x9d0, (int*)(DAT_TileMapState::instance.OccupancyLayer + iVar39 * 0x9d0));
            this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[0xe].componentArray[iVar39] = uVar23;
            uVar24 = MACRO_CALL_MEMBER(
                Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(
                0x9d0, (int*)(DAT_TileMapState::instance.HeightLayer + iVar39 * 0x9d0));
            this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[0xf].componentArray[iVar39] = uVar24;
            uVar25 = MACRO_CALL_MEMBER(
                Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(
                0x9d0, (int*)(DAT_TileMapState::instance.AIInfoLayer + iVar39 * 0x9d0));
            this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[0x10].componentArray[iVar39] = uVar25;
            uVar26 = MACRO_CALL_MEMBER(
                Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(
                0x9d0, (int*)(DAT_TileMapState::instance.AIZoneLayer + iVar39 * 0x9d0));
            this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[0x11].componentArray[iVar39] = uVar26;
            uVar27 = MACRO_CALL_MEMBER(
                Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(
                0x9d0, (int*)(DAT_TileMapState::instance.SEC_TileMap1104 + iVar39 * 0x9d0));
            this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[0x12].componentArray[iVar39] = uVar27;
            uVar28 = MACRO_CALL_MEMBER(
                Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(
                0x9d0, (int*)(DAT_TileMapState::instance.unitDeathHeatMap + iVar39 * 0x9d0));
            this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[0x13].componentArray[iVar39] = uVar28;
            uVar29 = MACRO_CALL_MEMBER(
                Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(
                0x9d0, (int*)(DAT_TileMapState::instance.SEC_PathfindingCostTileMap1105 + iVar39 * 0x9d0));
            this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[0x14].componentArray[iVar39] = uVar29;
            uVar30 = MACRO_CALL_MEMBER(
                Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(
                0x9d0, (int*)(DAT_TileMapState::instance.SEC_PathfindingCostTileMap1105 + 0x13a10 + iVar39 * 0x9d0));
            this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[0x15].componentArray[iVar39] = uVar30;
            uVar31 = MACRO_CALL_MEMBER(
                Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(
                0x9d0, (int*)(DAT_TileMapState::instance.SEC_PathfindingCostTileMap1105 + 0x27420 + iVar39 * 0x9d0));
            this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[0x16].componentArray[iVar39] = uVar31;
            uVar32 = MACRO_CALL_MEMBER(
                Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(
                0x9d0, (int*)(DAT_TileMapState::instance.SEC_PathfindingCostTileMap1105 + 0x3ae30 + iVar39 * 0x9d0));
            this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[0x17].componentArray[iVar39] = uVar32;
            uVar33 = MACRO_CALL_MEMBER(
                Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(
                0x9d0, (int*)(DAT_TileMapState::instance.SEC_PathfindingCostTileMap1105 + 0x4e840 + iVar39 * 0x9d0));
            this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[0x18].componentArray[iVar39] = uVar33;
            uVar34 = MACRO_CALL_MEMBER(
                Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(
                0x9d0, (int*)(DAT_TileMapState::instance.SEC_PathfindingCostTileMap1105 + 0x62250 + iVar39 * 0x9d0));
            this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[0x19].componentArray[iVar39] = uVar34;
            uVar35 = MACRO_CALL_MEMBER(
                Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(
                0x9d0, (int*)(DAT_TileMapState::instance.SEC_PathfindingCostTileMap1105 + 0x75c60 + iVar39 * 0x9d0));
            this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[0x1a].componentArray[iVar39] = uVar35;
            uVar36 = MACRO_CALL_MEMBER(
                Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(
                0x9d0, (int*)(DAT_TileMapState::instance.SEC_PathfindingCostTileMap1105 + 0x89670 + iVar39 * 0x9d0));
            this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[0x1b].componentArray[iVar39] = uVar36;
            uVar37 = MACRO_CALL_MEMBER(
                Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(
                0x9d0, (int*)(DAT_TileMapState::instance.SEC_PathfindingCostTileMap1105 + 0x9d080 + iVar39 * 0x9d0));
            iVar45 = iVar45 + uVar19 + uVar21 + uVar22 + uVar23 + uVar24 + uVar25 + uVar26 + uVar27 + uVar28 + uVar29
                + uVar30 + uVar31 + uVar32 + uVar33 + uVar34 + uVar35 + uVar36 + uVar37;
            this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[0x1c].componentArray[iVar39] = uVar37;
        }
        this->DAT_PlayerMatchTimes[this->currentPlayerSlotID * 0xc + 0xf] = iVar45;
        this->HASH_HashTotal[this->currentPlayerSlotID] = this->HASH_HashTotal[this->currentPlayerSlotID] + iVar45;
        _hashSubTotal = 0;
        _entityIndex = 25;
        address = DAT_EntityState::instance.entityArray + 0x19;
        do {
            sVar5 = address->screenDirection;
            sVar6 = address->x1;
            sVar7 = address->y1;
            sVar8 = address->originX;
            sVar9 = address->originY;
            sVar10 = address->imageID;
            sVar11 = address->field82_0xbe;
            iVar39 = address->graphicType2;
            iVar45 = address->displayValue;
            sVar12 = address->field83_0xc0;
            sVar13 = address->field86_0xc8;
            sVar14 = address->field87_0xca;
            sVar15 = address->field88_0xcc;
            sVar16 = address->field89_0xce;
            address->screenDirection = 0;
            address->x1 = 0;
            address->y1 = 0;
            address->originX = 0;
            address->originY = 0;
            address->graphicType2 = 0;
            address->imageID = 0;
            memset(&address->field86_0xc8, 0, 8);
            address->displayValue = 0;
            memset(&address->field82_0xbe, 0, 4);
            uVar19 = MACRO_CALL_MEMBER(Map::Navigation::DirectionAlgorithmState_Func::computeHash,
                DAT_DirectionAlgorithmState::ptr)(0xe8, (int*)address);
            address->screenDirection = (short)sVar5;
            address->x1 = (short)sVar6;
            address->y1 = (short)sVar7;
            address->originX = (short)sVar8;
            address->originY = (short)sVar9;
            address->graphicType2 = iVar39;
            address->imageID = (short)sVar10;
            address->field82_0xbe = sVar11;
            _hashSubTotal = _hashSubTotal + uVar19;
            address->displayValue = iVar45;
            address->field83_0xc0 = sVar12;
            address->field88_0xcc = sVar15;
            address->field86_0xc8 = sVar13;
            address->field89_0xce = sVar16;
            address->field87_0xca = sVar14;
            this->HASH_Entities[this->currentPlayerSlotID][_entityIndex] = uVar19;
            _entityIndex = _entityIndex + 1;
            address = address + 1;
        } while (address < DAT_EntityState::instance.entityArray + 3000);
        this->DAT_PlayerMatchTimes[this->currentPlayerSlotID * 0xc + 0x10] = _hashSubTotal;
        this->HASH_HashTotal[this->currentPlayerSlotID]
            = this->HASH_HashTotal[this->currentPlayerSlotID] + _hashSubTotal;
        _hashSubTotal = 0;
        for (_moatIndex = 0; _moatIndex < 160; _moatIndex = _moatIndex + 1) {
            uVar21 = MACRO_CALL_MEMBER(Map::Navigation::DirectionAlgorithmState_Func::computeHash,
                DAT_DirectionAlgorithmState::ptr)(1600, (int*)(DAT_TileMapState::instance.moats + _moatIndex * 100));
            _hashSubTotal = _hashSubTotal + uVar21;
            this->HASH_Moats[this->currentPlayerSlotID][_moatIndex] = uVar21;
        }
        this->DAT_PlayerMatchTimes[this->currentPlayerSlotID * 0xc + 0x11] = _hashSubTotal;
        this->HASH_HashTotal[this->currentPlayerSlotID]
            = this->HASH_HashTotal[this->currentPlayerSlotID] + _hashSubTotal;
        _hashSubTotal = 0;
        for (_climbIndex = 0; _climbIndex < 200; _climbIndex = _climbIndex + 1) {
            uVar19 = MACRO_CALL_MEMBER(
                Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(
                516, (int*)&DAT_PathFindingState::instance.climbData[_climbIndex].canBeUsed);
            _hashSubTotal = _hashSubTotal + uVar19;
            this->HASH_ClimbData[this->currentPlayerSlotID][_climbIndex] = uVar19;
        }
        this->DAT_PlayerMatchTimes[this->currentPlayerSlotID * 0xc + 0x12] = _hashSubTotal;
        this->HASH_HashTotal[this->currentPlayerSlotID]
            = this->HASH_HashTotal[this->currentPlayerSlotID] + _hashSubTotal;
        _hashSubTotal = 0;
        for (_pitchDitchIndex = 0; _pitchDitchIndex < 40; _pitchDitchIndex = _pitchDitchIndex + 1) {
            uVar19 = MACRO_CALL_MEMBER(
                Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(
                2000, (int*)&DAT_TileMapState::instance.pitchDitches[_pitchDitchIndex * 100].tile);
            _hashSubTotal = _hashSubTotal + uVar19;
            this->HASH_PitchDitches[this->currentPlayerSlotID][_pitchDitchIndex] = uVar19;
        }
        this->DAT_PlayerMatchTimes[this->currentPlayerSlotID * 0xc + 0x13] = _hashSubTotal;
        this->HASH_HashTotal[this->currentPlayerSlotID]
            = this->HASH_HashTotal[this->currentPlayerSlotID] + _hashSubTotal;
        for (iVar39 = 0; iVar39 < 40; iVar39 = iVar39 + 1) {
            this->HASH_Unknown2[this->currentPlayerSlotID][iVar39] = 0;
        }
        this->DAT_PlayerMatchTimes[this->currentPlayerSlotID * 0xc + 0x14] = 0;
        _hashSubTotal = 0;
        for (_aivIndex = 0; _aivIndex < 9; _aivIndex = _aivIndex + 1) {
            uVar19 = MACRO_CALL_MEMBER(Map::Navigation::DirectionAlgorithmState_Func::computeHash,
                DAT_DirectionAlgorithmState::ptr)(28056, (int*)&DAT_AIVState::instance.aivs[_aivIndex].playerID);
            _hashSubTotal = _hashSubTotal + uVar19;
            this->HASH_AIVS[this->currentPlayerSlotID][_aivIndex] = uVar19;
        }
        this->DAT_PlayerMatchTimes[this->currentPlayerSlotID * 0xc + 0x15] = _hashSubTotal;
        this->HASH_HashTotal[this->currentPlayerSlotID]
            = this->HASH_HashTotal[this->currentPlayerSlotID] + _hashSubTotal;
        _hashSubTotal = 0;
        for (iVar39 = 0; iVar39 < 80; iVar39 = iVar39 + 1) {
            /*
              fixme: it is wasteful to network latency to send the heatmap because it is a   derivative of the
              map state, as long as the map and tree state is correct,   this is unnecessary
             */
            uVar19 = MACRO_CALL_MEMBER(Map::Navigation::DirectionAlgorithmState_Func::computeHash,
                DAT_DirectionAlgorithmState::ptr)(3840, (int*)DAT_AIVState::instance.heatMaps[iVar39]);
            _hashSubTotal = _hashSubTotal + uVar19;
            this->HASH_HeatMaps[this->currentPlayerSlotID][iVar39] = uVar19;
        }
        this->DAT_PlayerMatchTimes[this->currentPlayerSlotID * 0xc + 0x16] = _hashSubTotal;
        this->HASH_HashTotal[this->currentPlayerSlotID]
            = this->HASH_HashTotal[this->currentPlayerSlotID] + _hashSubTotal;
        if (!dontSendSyncCommand) {
            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                Commands::GCT_ANNOUNCE_PLAYER_INFORMATION_AVAILABLE_AIVSSPECIALTRANSMITLOGIC);
        }
    }

}
}
