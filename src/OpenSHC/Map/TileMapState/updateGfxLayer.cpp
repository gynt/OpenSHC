#include "../../Map.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/GMTotalPicturesProcessed.hpp"
#include "OpenSHC/Globals/PTR_ARRAY_00510d94.hpp"

namespace OpenSHC {
namespace Map {

    using Game::GameMode2;
    using Map::Buildings::BuildingType;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00509180
    void TileMapState::updateGfxLayer()
    {
        BuildingTypeShort BVar1;
        ushort uVar2;
        ushort uVar3;
        short sVar4;
        short sVar5;
        byte bVar6;
        byte bVar7;
        short sVar8;
        bool bVar10;
        int bVar9;
        BOOLEnum BVar11;
        uint uVar12;
        int iVar13;
        int iVar14;
        uint uVar15;
        byte bVar16;
        int iVar17;
        uint* puVar18;
        byte bVar19;
        int local_d4;
        uint local_c0;
        int local_b8;
        int local_b4;
        short local_b0;
        int local_ac;
        int local_a4;
        int local_a0;
        short local_9c;
        int local_94;
        uint local_74;
        int local_70;
        int local_68;
        int local_60;
        int local_54;
        uint local_48;
        short local_44;
        int local_38;
        int local_30;
        int local_24;
        int local_18;
        int local_14;
        int local_10;
        int local_c;
        int local_8;
        sVar8 = 0;
        if (0 < this->forceUpdateTextureTilemap) {
            this->forceUpdateTextureTilemap = this->forceUpdateTextureTilemap + -1;
            local_c = DAT_PathFindingState::instance.mappingYRelated % 10;
            for (local_18 = this->someIndex; local_18 <= this->someLimit; local_18 = local_18 + 1) {
                for (local_10 = this->someYLike; local_10 <= this->someYLikeLimit; local_10 = local_10 + 1) {
                    if (*(char*)(local_18 * 0x28 + 0x1f93438 + local_10) != '\0') {
                        local_24 = local_c;
                        local_c = 0;
                        for (; local_24 < 10; local_24 = local_24 + 1) {
                            this->DAT_SomeY = local_18 * 10 + local_24;
                            this->DAT_SomeX = local_10 * 10;
                            for (local_30 = 0; local_30 < 10; local_30 = local_30 + 1) {
                                bVar9 = MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::xyAreValid,
                                    DAT_ViewportRenderState::ptr)(this->DAT_SomeX, (uint)((int)(this->DAT_SomeY)));
                                if ((bVar9)
                                    && (this->DAT_SomeTile
                                        = MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::translateXYToTile,
                                            DAT_ViewportRenderState::ptr)(this->DAT_SomeX, this->DAT_SomeY),
                                        this->ChangedLayer[this->DAT_SomeTile] != 0)) {
                                    if (this->BuildingLayer[this->DAT_SomeTile] == 0) {
                                        MACRO_CALL_MEMBER(Map::TileMapState_Func::computeTileLuminescence,
                                            this)(this->DAT_SomeTile, this->DAT_SomeY);
                                        iVar17 = this->DAT_SomeX;
                                        this->FloatingLayer[this->DAT_SomeTile] = 0;
                                        this->MiscDisplayLayer[this->DAT_SomeTile]
                                            = this->MiscDisplayLayer[this->DAT_SomeTile] & 0xfc3f;
                                        this->MiscDisplayLayer[this->DAT_SomeTile]
                                            = this->MiscDisplayLayer[this->DAT_SomeTile] & 0xf7ff;
                                        if (!(this->LogicLayer[this->DAT_SomeTile] & L_RIVER)) {
                                            if (!(this->LogicLayer[this->DAT_SomeTile] & L_FORD)) {
                                                if (!(this->LogicLayer[this->DAT_SomeTile] & L_FARM_FIELD_WHEAT)) {
                                                    if (!(this->LogicLayer[this->DAT_SomeTile] & L_FARM_FIELD_HOP)) {
                                                        if (!(this->LogicLayer[this->DAT_SomeTile] & L_FARM_FIELD_APPLE
                                                                | L_FARM_FIELD_DAIRY)) {
                                                            if (((!(this->LogicLayer[this->DAT_SomeTile]
                                                                         & L_WALL_OR_GATEHOUSE
                                                                     | L_BUILDING | L_KEEP_NON_MANOR_HOUSE))
                                                                    && (this->BuildingWasLayer[this->DAT_SomeTile]
                                                                        != '\0'))
                                                                && ((this->MiscDisplayLayer[this->DAT_SomeTile]
                                                                    & 0x10))) {
                                                                local_44 = 0;
                                                                switch (this->BuildingWasLayer[this->DAT_SomeTile]) {
                                                                case '\t':
                                                                case '\n':
                                                                case '\v':
                                                                case '\x18':
                                                                case '\x19':
                                                                case '$':
                                                                case '%':
                                                                case '&':
                                                                case '(':
                                                                case ')':
                                                                case '*':
                                                                case '+':
                                                                case ',':
                                                                case '-':
                                                                case '.':
                                                                case '0':
                                                                case '4':
                                                                case 'J':
                                                                case 'K':
                                                                case 'L':
                                                                case 'M':
                                                                case 'N':
                                                                case 'Z':
                                                                case 'j':
                                                                    local_44 = 0xc;
                                                                }
                                                                if (!(this->MiscDisplayLayer[this->DAT_SomeTile]
                                                                        & 0x2000)) {
                                                                    this->GfxLayer[this->DAT_SomeTile]
                                                                        = (short)
                                                                              GMTotalPicturesProcessed::instance[0x95]
                                                                        + local_44 + 4
                                                                        + (this->RandomLayer[this->DAT_SomeTile] & 7);
                                                                } else {
                                                                    this->GfxLayer[this->DAT_SomeTile]
                                                                        = (short)
                                                                              GMTotalPicturesProcessed::instance[0x95]
                                                                        + local_44
                                                                        + (this->RandomLayer[this->DAT_SomeTile] & 7);
                                                                }
                                                            } else if (!(this->LogicLayer[this->DAT_SomeTile]
                                                                           & L_WALL_OR_GATEHOUSE)) {
                                                                if (!(this->LogicLayer[this->DAT_SomeTile] & L_SEA
                                                                        | L_ROCKY | L_WALL_OR_GATEHOUSE | L_BUILDING
                                                                        | L_BOULDERS | L_PEBBLES | L_IRON | L_RIVER
                                                                        | L_FARM_FIELD_WHEAT | L_FARM_FIELD_HOP
                                                                        | L_FARM_FIELD_APPLE | L_FARM_FIELD_DAIRY
                                                                        | L_KEEP_NON_MANOR_HOUSE | L_MARSH | L_OIL)) {
                                                                    local_48 = 0;
                                                                    this->WallOwnerLayer[this->DAT_SomeTile]
                                                                        = this->WallOwnerLayer[this->DAT_SomeTile]
                                                                        & 0xf7;
                                                                    bVar19 = 0;
                                                                    if ((*(uint*)(this->ptr_LogicLayer
                                                                             + this->DAT_SomeTile * 4 + 4)
                                                                            & L_WALL_OR_GATEHOUSE)) {
                                                                        bVar19 = 0x20;
                                                                    }
                                                                    if ((*(uint*)(this->ptr_LogicLayer
                                                                             + this->DAT_SomeTile * 4 + -4)
                                                                            & L_WALL_OR_GATEHOUSE)) {
                                                                        bVar19 = bVar19 | 2;
                                                                    }
                                                                    puVar18 = (uint*)(this->ptr_LogicLayer
                                                                        + *(int*)(this->ptr_MovementDirectionTranslationMatrix
                                                                              + this->DAT_SomeY * 0x20)
                                                                            * 4
                                                                        + this->DAT_SomeTile * 4);
                                                                    if ((puVar18[-1] & L_WALL_OR_GATEHOUSE)) {
                                                                        bVar19 = bVar19 | 1;
                                                                    }
                                                                    if ((puVar18[1] & L_WALL_OR_GATEHOUSE)) {
                                                                        bVar19 = bVar19 | 0x40;
                                                                    }
                                                                    if ((*puVar18 & L_WALL_OR_GATEHOUSE)) {
                                                                        bVar19 = bVar19 | 0x80;
                                                                    }
                                                                    puVar18 = (uint*)(this->ptr_LogicLayer
                                                                        + *(int*)((int)(this->ptr_MovementDirectionTranslationMatrix
                                                                                      + this->DAT_SomeY * 0x20)
                                                                              + 0x10)
                                                                            * 4
                                                                        + this->DAT_SomeTile * 4);
                                                                    if ((puVar18[-1] & L_WALL_OR_GATEHOUSE)) {
                                                                        bVar19 = bVar19 | 4;
                                                                    }
                                                                    if ((puVar18[1] & L_WALL_OR_GATEHOUSE)) {
                                                                        bVar19 = bVar19 | 0x10;
                                                                    }
                                                                    if ((*puVar18 & L_WALL_OR_GATEHOUSE)) {
                                                                        bVar19 = bVar19 | 8;
                                                                    }
                                                                    this->bitFlag = 0;
                                                                    if ((*(uint*)(this->ptr_LogicLayer
                                                                             + this->DAT_SomeTile * 4 + 4)
                                                                            & 2)) {
                                                                        this->bitFlag = 0x20;
                                                                    }
                                                                    if ((*(uint*)(this->ptr_LogicLayer
                                                                             + this->DAT_SomeTile * 4 + -4)
                                                                            & 2)) {
                                                                        this->bitFlag = this->bitFlag | 2;
                                                                    }
                                                                    puVar18 = (uint*)(this->ptr_LogicLayer
                                                                        + *(int*)(this->ptr_MovementDirectionTranslationMatrix
                                                                              + this->DAT_SomeY * 0x20)
                                                                            * 4
                                                                        + this->DAT_SomeTile * 4);
                                                                    if ((puVar18[-1] & L_STOCKPILEUnk)) {
                                                                        this->bitFlag = this->bitFlag | 1;
                                                                    }
                                                                    if ((puVar18[1] & L_STOCKPILEUnk)) {
                                                                        this->bitFlag = this->bitFlag | 0x40;
                                                                    }
                                                                    if ((*puVar18 & L_STOCKPILEUnk)) {
                                                                        this->bitFlag = this->bitFlag | 0x80;
                                                                    }
                                                                    puVar18 = (uint*)(this->ptr_LogicLayer
                                                                        + *(int*)((int)(this->ptr_MovementDirectionTranslationMatrix
                                                                                      + this->DAT_SomeY * 0x20)
                                                                              + 0x10)
                                                                            * 4
                                                                        + this->DAT_SomeTile * 4);
                                                                    if ((puVar18[-1] & L_STOCKPILEUnk)) {
                                                                        this->bitFlag = this->bitFlag | 4;
                                                                    }
                                                                    if ((puVar18[1] & L_STOCKPILEUnk)) {
                                                                        this->bitFlag = this->bitFlag | 0x10;
                                                                    }
                                                                    if ((*puVar18 & L_STOCKPILEUnk)) {
                                                                        this->bitFlag = this->bitFlag | 8;
                                                                    }
                                                                    bVar19 = ~this->bitFlag & bVar19;
                                                                    if (bVar19) {
                                                                        switch (bVar19 & 0xaa) {
                                                                        case 10:
                                                                            local_48 = 2;
                                                                            if ((bVar19 & 0x15) == 0x15) {
                                                                                local_48 = 0;
                                                                            }
                                                                            break;
                                                                        case 0x28:
                                                                            local_48 = (uint)((bVar19 & 0x54) != 0x54);
                                                                            break;
                                                                        case 0x82:
                                                                            local_48 = 3;
                                                                            if ((bVar19 & 0x45) == 0x45) {
                                                                                local_48 = 0;
                                                                            }
                                                                            break;
                                                                        case 0xa0:
                                                                            local_48 = 4;
                                                                            if ((bVar19 & 0x41) == 0x15) {
                                                                                local_48 = 0;
                                                                            }
                                                                        }
                                                                        if (local_48) {
                                                                            this->bitFlag = 0;
                                                                            if ((*(uint*)(this->ptr_LogicLayer
                                                                                     + this->DAT_SomeTile * 4 + 4)
                                                                                    & 0x800)) {
                                                                                this->bitFlag = 0x20;
                                                                            }
                                                                            if ((*(uint*)(this->ptr_LogicLayer
                                                                                     + this->DAT_SomeTile * 4 + -4)
                                                                                    & 0x800)) {
                                                                                this->bitFlag = this->bitFlag | 2;
                                                                            }
                                                                            puVar18 = (uint*)(this->ptr_LogicLayer
                                                                                + *(int*)(this->ptr_MovementDirectionTranslationMatrix
                                                                                      + this->DAT_SomeY * 0x20)
                                                                                    * 4
                                                                                + this->DAT_SomeTile * 4);
                                                                            if ((puVar18[-1] & L_STAIRS)) {
                                                                                this->bitFlag = this->bitFlag | 1;
                                                                            }
                                                                            if ((puVar18[1] & L_STAIRS)) {
                                                                                this->bitFlag = this->bitFlag | 0x40;
                                                                            }
                                                                            if ((*puVar18 & L_STAIRS)) {
                                                                                this->bitFlag = this->bitFlag | 0x80;
                                                                            }
                                                                            puVar18 = (uint*)(this->ptr_LogicLayer
                                                                                + *(int*)((int)(this->ptr_MovementDirectionTranslationMatrix
                                                                                              + this->DAT_SomeY * 0x20)
                                                                                      + 0x10)
                                                                                    * 4
                                                                                + this->DAT_SomeTile * 4);
                                                                            if ((puVar18[-1] & L_STAIRS)) {
                                                                                this->bitFlag = this->bitFlag | 4;
                                                                            }
                                                                            if ((puVar18[1] & L_STAIRS)) {
                                                                                this->bitFlag = this->bitFlag | 0x10;
                                                                            }
                                                                            if ((*puVar18 & L_STAIRS)) {
                                                                                this->bitFlag = this->bitFlag | 8;
                                                                            }
                                                                            if (this->bitFlag) {
                                                                                local_48 = 0;
                                                                            }
                                                                        }
                                                                        if (local_48) {
                                                                            if (local_48 - 1 < 4) {
                                                                                ((void (*)())PTR_ARRAY_00510d94::instance
                                                                                        [local_48 - 1])();
                                                                                return;
                                                                            }
                                                                            bVar19 = this->HeightLayer[local_68];
                                                                            bVar16 = this->HeightLayer[local_60];
                                                                            bVar7 = this->HeightLayer[local_54];
                                                                            if (!(this->LogicLayer[local_54]
                                                                                    & 0x100U)) {
                                                                                bVar7 = bVar16;
                                                                            }
                                                                            bVar6 = bVar16;
                                                                            if (bVar19 < bVar16) {
                                                                                bVar6 = bVar19;
                                                                            }
                                                                            if ((bVar6 < bVar7)
                                                                                && (bVar7 = bVar16, bVar19 < bVar16)) {
                                                                                bVar7 = bVar19;
                                                                            }
                                                                            if (this->HeightLayer[this->DAT_SomeTile]
                                                                                < bVar7) {
                                                                                this->WallGFXLayer[this->DAT_SomeTile]
                                                                                    = (ushort)bVar7;
                                                                                if (((this->DamageLayer[local_68] != 0)
                                                                                        || (this->DamageLayer[local_60]
                                                                                            != 0))
                                                                                    || ((
                                                                                        this->DamageLayer[local_54] != 0
                                                                                        && ((this->LogicLayer[local_54]
                                                                                            & 0x100U))))) {
                                                                                    this->WallOwnerLayer[this
                                                                                            ->DAT_SomeTile]
                                                                                        = this->WallOwnerLayer[this
                                                                                                  ->DAT_SomeTile]
                                                                                        | 8;
                                                                                }
                                                                            } else {
                                                                                local_48 = 0;
                                                                            }
                                                                            if (local_48) {
                                                                                uVar12 = (local_48 + 3)
                                                                                        - this->mapOrientation / 2
                                                                                    & 0x80000003;
                                                                                if ((int)uVar12 < 0) {
                                                                                    uVar12
                                                                                        = (uVar12 - 1 | 0xfffffffc) + 1;
                                                                                }
                                                                                switch (uVar12) {
                                                                                case 0:
                                                                                    this->MiscDisplayLayer[this
                                                                                            ->DAT_SomeTile]
                                                                                        = this->MiscDisplayLayer[this
                                                                                                  ->DAT_SomeTile]
                                                                                        | 0x40;
                                                                                    this->AlphaGFXLayer[this
                                                                                            ->DAT_SomeTile] = 0x2f;
                                                                                    break;
                                                                                case 1:
                                                                                    this->MiscDisplayLayer[this
                                                                                            ->DAT_SomeTile]
                                                                                        = this->MiscDisplayLayer[this
                                                                                                  ->DAT_SomeTile]
                                                                                        | 0x200;
                                                                                    this->AlphaGFXLayer[this
                                                                                            ->DAT_SomeTile] = 0x2e;
                                                                                    break;
                                                                                case 2:
                                                                                    this->MiscDisplayLayer[this
                                                                                            ->DAT_SomeTile]
                                                                                        = this->MiscDisplayLayer[this
                                                                                                  ->DAT_SomeTile]
                                                                                        | 0x80;
                                                                                    this->AlphaGFXLayer[this
                                                                                            ->DAT_SomeTile] = 0x31;
                                                                                    break;
                                                                                case 3:
                                                                                    this->MiscDisplayLayer[this
                                                                                            ->DAT_SomeTile]
                                                                                        = this->MiscDisplayLayer[this
                                                                                                  ->DAT_SomeTile]
                                                                                        | 0x100;
                                                                                    this->AlphaGFXLayer[this
                                                                                            ->DAT_SomeTile] = 0x30;
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            } else {
                                                                this->wallCornerRotation = MACRO_CALL_MEMBER(
                                                                    Map::TileMapState_Func::
                                                                        computeWallCornerRenderRotation,
                                                                    this)(iVar17);
                                                                this->WallGFXLayer[this->DAT_SomeTile]
                                                                    = (short)GMTotalPicturesProcessed::instance[10] + -1
                                                                    + (short)this->wallCornerRotation;
                                                                sVar4 = (short)GMTotalPicturesProcessed::instance[0xc];
                                                                if (this->DamageLayer[this->DAT_SomeTile] == 0) {
                                                                    if (!(this->LogicLayer[this->DAT_SomeTile]
                                                                            & 0x200U)) {
                                                                        if (!(this->LogicLayer[this->DAT_SomeTile]
                                                                                & 0x800U)) {
                                                                            if (this->LuminesenceLayer[this
                                                                                        ->DAT_SomeTile]
                                                                                < 4) {
                                                                                this->GfxLayer[this->DAT_SomeTile]
                                                                                    = sVar4 + 0x60
                                                                                    + (this->RandomLayer[this
                                                                                               ->DAT_SomeTile]
                                                                                        & 7);
                                                                            } else {
                                                                                this->GfxLayer[this->DAT_SomeTile]
                                                                                    = sVar4 + 0x68
                                                                                    + (this->RandomLayer[this
                                                                                               ->DAT_SomeTile]
                                                                                        & 7);
                                                                            }
                                                                        } else {
                                                                            BVar11 = MACRO_CALL_MEMBER(
                                                                                Map::TileMapState_Func::
                                                                                    hasHigherNeighborWithStairs,
                                                                                this)(
                                                                                this->DAT_SomeTile, this->DAT_SomeY, 0);
                                                                            if (!BVar11) {
                                                                                BVar11 = MACRO_CALL_MEMBER(
                                                                                    Map::TileMapState_Func::
                                                                                        hasHigherNeighborWithStairs,
                                                                                    this)(this->DAT_SomeTile,
                                                                                    this->DAT_SomeY, 2);
                                                                                if (!BVar11) {
                                                                                    BVar11 = MACRO_CALL_MEMBER(
                                                                                        Map::TileMapState_Func::
                                                                                            hasHigherNeighborWithStairs,
                                                                                        this)(this->DAT_SomeTile,
                                                                                        this->DAT_SomeY, 4);
                                                                                    if (!BVar11) {
                                                                                        BVar11 = MACRO_CALL_MEMBER(
                                                                                            Map::TileMapState_Func::
                                                                                                hasHigherNeighborWithStairs,
                                                                                            this)(this->DAT_SomeTile,
                                                                                            this->DAT_SomeY, 6);
                                                                                        if (!BVar11) {
                                                                                            BVar11 = MACRO_CALL_MEMBER(
                                                                                                Map::
                                                                                                    TileMapState_Func::
                                                                                                        hasHigherPlainNeighborWithWallOrGatehouse,
                                                                                                this)(
                                                                                                this->DAT_SomeTile,
                                                                                                this->DAT_SomeY, 0);
                                                                                            if (!BVar11) {
                                                                                                BVar11 = MACRO_CALL_MEMBER(
                                                                                                    Map::
                                                                                                        TileMapState_Func::
                                                                                                            hasHigherPlainNeighborWithWallOrGatehouse,
                                                                                                    this)(
                                                                                                    this->DAT_SomeTile,
                                                                                                    this->DAT_SomeY, 2);
                                                                                                if (!BVar11) {
                                                                                                    BVar11 = MACRO_CALL_MEMBER(
                                                                                                        Map::
                                                                                                            TileMapState_Func::
                                                                                                                hasHigherPlainNeighborWithWallOrGatehouse,
                                                                                                        this)(
                                                                                                        this->DAT_SomeTile,
                                                                                                        this->DAT_SomeY,
                                                                                                        4);
                                                                                                    if (!BVar11) {
                                                                                                        BVar11 = MACRO_CALL_MEMBER(
                                                                                                            Map::
                                                                                                                TileMapState_Func::
                                                                                                                    hasHigherPlainNeighborWithWallOrGatehouse,
                                                                                                            this)(
                                                                                                            this->DAT_SomeTile,
                                                                                                            this->DAT_SomeY,
                                                                                                            6);
                                                                                                        if (!BVar11) {
                                                                                                            this->GfxLayer
                                                                                                                [this->DAT_SomeTile]
                                                                                                                = (short)GMTotalPicturesProcessed::
                                                                                                                      instance
                                                                                                                          [0xc]
                                                                                                                + 0x68;
                                                                                                        } else {
                                                                                                            this->GfxLayer
                                                                                                                [this->DAT_SomeTile]
                                                                                                                = (short)GMTotalPicturesProcessed::
                                                                                                                      instance
                                                                                                                          [0xc]
                                                                                                                + 0x85;
                                                                                                        }
                                                                                                    } else {
                                                                                                        this->GfxLayer
                                                                                                            [this->DAT_SomeTile]
                                                                                                            = (short)GMTotalPicturesProcessed::
                                                                                                                  instance
                                                                                                                      [0xc]
                                                                                                            + 0x88;
                                                                                                    }
                                                                                                } else {
                                                                                                    this->GfxLayer[this
                                                                                                            ->DAT_SomeTile]
                                                                                                        = (short)GMTotalPicturesProcessed::
                                                                                                              instance
                                                                                                                  [0xc]
                                                                                                        + 0x87;
                                                                                                }
                                                                                            } else {
                                                                                                this->GfxLayer[this
                                                                                                        ->DAT_SomeTile]
                                                                                                    = (short)
                                                                                                          GMTotalPicturesProcessed::
                                                                                                              instance
                                                                                                                  [0xc]
                                                                                                    + 0x86;
                                                                                            }
                                                                                        } else {
                                                                                            this->GfxLayer[this
                                                                                                    ->DAT_SomeTile]
                                                                                                = (short)
                                                                                                      GMTotalPicturesProcessed::
                                                                                                          instance[0xc]
                                                                                                + 0x85;
                                                                                        }
                                                                                    } else {
                                                                                        this->GfxLayer[this
                                                                                                ->DAT_SomeTile]
                                                                                            = (short)
                                                                                                  GMTotalPicturesProcessed::
                                                                                                      instance[0xc]
                                                                                            + 0x88;
                                                                                    }
                                                                                } else {
                                                                                    this->GfxLayer[this->DAT_SomeTile]
                                                                                        = (short)
                                                                                              GMTotalPicturesProcessed::
                                                                                                  instance[0xc]
                                                                                        + 0x87;
                                                                                }
                                                                            } else {
                                                                                this->GfxLayer[this->DAT_SomeTile]
                                                                                    = (short)GMTotalPicturesProcessed::
                                                                                          instance[0xc]
                                                                                    + 0x86;
                                                                            }
                                                                        }
                                                                    } else {
                                                                        BVar11 = MACRO_CALL_MEMBER(
                                                                            Map::TileMapState_Func::
                                                                                isWallCornerForCardinalDirection,
                                                                            this)(
                                                                            this->DAT_SomeTile, this->DAT_SomeY, 0);
                                                                        if (!BVar11) {
                                                                            BVar11 = MACRO_CALL_MEMBER(
                                                                                Map::TileMapState_Func::
                                                                                    isWallCornerForCardinalDirection,
                                                                                this)(
                                                                                this->DAT_SomeTile, this->DAT_SomeY, 2);
                                                                            if (!BVar11) {
                                                                                uVar12 = MACRO_CALL_MEMBER(
                                                                                    Map::TileMapState_Func::
                                                                                        isWallCornerForDiagonalDirection,
                                                                                    this)(this->DAT_SomeTile,
                                                                                    this->DAT_SomeY, 1);
                                                                                if (!uVar12) {
                                                                                    uVar12 = MACRO_CALL_MEMBER(
                                                                                        Map::TileMapState_Func::
                                                                                            isWallCornerForDiagonalDirection,
                                                                                        this)(this->DAT_SomeTile,
                                                                                        this->DAT_SomeY, 3);
                                                                                    if (!uVar12) {
                                                                                        uVar12 = MACRO_CALL_MEMBER(
                                                                                            Map::TileMapState_Func::
                                                                                                isWallCornerForDiagonalDirection,
                                                                                            this)(this->DAT_SomeTile,
                                                                                            this->DAT_SomeY, 5);
                                                                                        if (!uVar12) {
                                                                                            uVar12 = MACRO_CALL_MEMBER(
                                                                                                Map::
                                                                                                    TileMapState_Func::
                                                                                                        isWallCornerForDiagonalDirection,
                                                                                                this)(
                                                                                                this->DAT_SomeTile,
                                                                                                this->DAT_SomeY, 7);
                                                                                            sVar4 = (short)
                                                                                                GMTotalPicturesProcessed::
                                                                                                    instance[0xc];
                                                                                            if (!uVar12) {
                                                                                                this->GfxLayer[this
                                                                                                        ->DAT_SomeTile]
                                                                                                    = sVar4 + 0x84;
                                                                                                this->LogicLayer[this
                                                                                                        ->DAT_SomeTile]
                                                                                                    = this->LogicLayer
                                                                                                          [this->DAT_SomeTile]
                                                                                                    | 0x400000;
                                                                                            } else {
                                                                                                if (!this
                                                                                                        ->mapOrientation) {
                                                                                                    this->GfxLayer[this
                                                                                                            ->DAT_SomeTile]
                                                                                                        = sVar4 + 0x81;
                                                                                                } else if (
                                                                                                    this->mapOrientation
                                                                                                    == 2) {
                                                                                                    this->GfxLayer[this
                                                                                                            ->DAT_SomeTile]
                                                                                                        = sVar4 + 0x80;
                                                                                                } else if (
                                                                                                    this->mapOrientation
                                                                                                    == 4) {
                                                                                                    this->GfxLayer[this
                                                                                                            ->DAT_SomeTile]
                                                                                                        = sVar4 + 0x83;
                                                                                                } else if (
                                                                                                    this->mapOrientation
                                                                                                    == 6) {
                                                                                                    this->GfxLayer[this
                                                                                                            ->DAT_SomeTile]
                                                                                                        = sVar4 + 0x82;
                                                                                                }
                                                                                                this->LogicLayer[this
                                                                                                        ->DAT_SomeTile]
                                                                                                    = this->LogicLayer
                                                                                                          [this->DAT_SomeTile]
                                                                                                    | 0x400000;
                                                                                            }
                                                                                        } else {
                                                                                            sVar4 = (short)
                                                                                                GMTotalPicturesProcessed::
                                                                                                    instance[0xc];
                                                                                            if (!this->mapOrientation) {
                                                                                                this->GfxLayer[this
                                                                                                        ->DAT_SomeTile]
                                                                                                    = sVar4 + 0x80;
                                                                                            } else if (
                                                                                                this->mapOrientation
                                                                                                == 2) {
                                                                                                this->GfxLayer[this
                                                                                                        ->DAT_SomeTile]
                                                                                                    = sVar4 + 0x83;
                                                                                            } else if (
                                                                                                this->mapOrientation
                                                                                                == 4) {
                                                                                                this->GfxLayer[this
                                                                                                        ->DAT_SomeTile]
                                                                                                    = sVar4 + 0x82;
                                                                                            } else if (
                                                                                                this->mapOrientation
                                                                                                == 6) {
                                                                                                this->GfxLayer[this
                                                                                                        ->DAT_SomeTile]
                                                                                                    = sVar4 + 0x81;
                                                                                            }
                                                                                            this->LogicLayer[this
                                                                                                    ->DAT_SomeTile]
                                                                                                = this->LogicLayer[this
                                                                                                          ->DAT_SomeTile]
                                                                                                | 0x400000;
                                                                                        }
                                                                                    } else {
                                                                                        sVar4 = (short)
                                                                                            GMTotalPicturesProcessed::
                                                                                                instance[0xc];
                                                                                        if (!this->mapOrientation) {
                                                                                            this->GfxLayer[this
                                                                                                    ->DAT_SomeTile]
                                                                                                = sVar4 + 0x83;
                                                                                        } else if (this->mapOrientation
                                                                                            == 2) {
                                                                                            this->GfxLayer[this
                                                                                                    ->DAT_SomeTile]
                                                                                                = sVar4 + 0x82;
                                                                                        } else if (this->mapOrientation
                                                                                            == 4) {
                                                                                            this->GfxLayer[this
                                                                                                    ->DAT_SomeTile]
                                                                                                = sVar4 + 0x81;
                                                                                        } else if (this->mapOrientation
                                                                                            == 6) {
                                                                                            this->GfxLayer[this
                                                                                                    ->DAT_SomeTile]
                                                                                                = sVar4 + 0x80;
                                                                                        }
                                                                                        this->LogicLayer[this
                                                                                                ->DAT_SomeTile]
                                                                                            = this->LogicLayer[this
                                                                                                      ->DAT_SomeTile]
                                                                                            | 0x400000;
                                                                                    }
                                                                                } else {
                                                                                    sVar4 = (short)
                                                                                        GMTotalPicturesProcessed::
                                                                                            instance[0xc];
                                                                                    if (!this->mapOrientation) {
                                                                                        this->GfxLayer[this
                                                                                                ->DAT_SomeTile]
                                                                                            = sVar4 + 0x82;
                                                                                    } else if (this->mapOrientation
                                                                                        == 2) {
                                                                                        this->GfxLayer[this
                                                                                                ->DAT_SomeTile]
                                                                                            = sVar4 + 0x81;
                                                                                    } else if (this->mapOrientation
                                                                                        == 4) {
                                                                                        this->GfxLayer[this
                                                                                                ->DAT_SomeTile]
                                                                                            = sVar4 + 0x80;
                                                                                    } else if (this->mapOrientation
                                                                                        == 6) {
                                                                                        this->GfxLayer[this
                                                                                                ->DAT_SomeTile]
                                                                                            = sVar4 + 0x83;
                                                                                    }
                                                                                    this->LogicLayer[this->DAT_SomeTile]
                                                                                        = this->LogicLayer[this
                                                                                                  ->DAT_SomeTile]
                                                                                        | 0x400000;
                                                                                }
                                                                            } else {
                                                                                sVar4
                                                                                    = (short)GMTotalPicturesProcessed::
                                                                                        instance[0xc];
                                                                                if ((!this->mapOrientation)
                                                                                    || (this->mapOrientation == 4)) {
                                                                                    if (!(this->LogicLayer[this
                                                                                                  ->DAT_SomeTile]
                                                                                            & 0x400000U)) {
                                                                                        this->GfxLayer[this
                                                                                                ->DAT_SomeTile] = sVar4
                                                                                            + 0x70
                                                                                            + (this->RandomLayer[this
                                                                                                       ->DAT_SomeTile]
                                                                                                & 3);
                                                                                    } else {
                                                                                        this->GfxLayer[this
                                                                                                ->DAT_SomeTile] = sVar4
                                                                                            + 0x78
                                                                                            + (this->RandomLayer[this
                                                                                                       ->DAT_SomeTile]
                                                                                                & 3);
                                                                                    }
                                                                                } else if (!(this->LogicLayer[this
                                                                                                     ->DAT_SomeTile]
                                                                                               & 0x400000U)) {
                                                                                    this->GfxLayer[this->DAT_SomeTile]
                                                                                        = sVar4 + 0x74
                                                                                        + (this->RandomLayer[this
                                                                                                   ->DAT_SomeTile]
                                                                                            & 3);
                                                                                } else {
                                                                                    this->GfxLayer[this->DAT_SomeTile]
                                                                                        = sVar4 + 0x7c
                                                                                        + (this->RandomLayer[this
                                                                                                   ->DAT_SomeTile]
                                                                                            & 3);
                                                                                }
                                                                            }
                                                                        } else {
                                                                            sVar4 = (short)
                                                                                GMTotalPicturesProcessed::instance[0xc];
                                                                            if ((!this->mapOrientation)
                                                                                || (this->mapOrientation == 4)) {
                                                                                if (!(this->LogicLayer[this
                                                                                              ->DAT_SomeTile]
                                                                                        & 0x400000U)) {
                                                                                    this->GfxLayer[this->DAT_SomeTile]
                                                                                        = sVar4 + 0x74
                                                                                        + (this->RandomLayer[this
                                                                                                   ->DAT_SomeTile]
                                                                                            & 3);
                                                                                } else {
                                                                                    this->GfxLayer[this->DAT_SomeTile]
                                                                                        = sVar4 + 0x7c
                                                                                        + (this->RandomLayer[this
                                                                                                   ->DAT_SomeTile]
                                                                                            & 3);
                                                                                }
                                                                            } else if (!(this->LogicLayer[this
                                                                                                 ->DAT_SomeTile]
                                                                                           & 0x400000U)) {
                                                                                this->GfxLayer[this->DAT_SomeTile]
                                                                                    = sVar4 + 0x70
                                                                                    + (this->RandomLayer[this
                                                                                               ->DAT_SomeTile]
                                                                                        & 3);
                                                                            } else {
                                                                                this->GfxLayer[this->DAT_SomeTile]
                                                                                    = sVar4 + 0x78
                                                                                    + (this->RandomLayer[this
                                                                                               ->DAT_SomeTile]
                                                                                        & 3);
                                                                            }
                                                                        }
                                                                    }
                                                                } else {
                                                                    this->GfxLayer[this->DAT_SomeTile] = sVar4 + 0x8a
                                                                        + (this->RandomLayer[this->DAT_SomeTile] & 7);
                                                                }
                                                            }
                                                        }
                                                    } else {
                                                        MACRO_CALL_MEMBER(
                                                            Map::TileMapState_Func::computeClimbRampRotation,
                                                            this)(this->DAT_SomeTile, (uint)((int)(iVar17)),
                                                            (uint)((int)(this->DAT_SomeY)));
                                                        this->PillarGFXLayer[this->DAT_SomeTile]
                                                            = (short)GMTotalPicturesProcessed::instance[9] + -1
                                                            + (short)this->wallCornerRotation;
                                                        this->MiscDisplayLayer[this->DAT_SomeTile]
                                                            = this->MiscDisplayLayer[this->DAT_SomeTile] | 0x800;
                                                        this->GfxLayer[this->DAT_SomeTile]
                                                            = (short)GMTotalPicturesProcessed::instance[0xe] + 0x25
                                                            + (this->RandomLayer[this->DAT_SomeTile] & 1) * 9;
                                                        DAT_BuildingsState::instance.field14_0x18e024 = 1;
                                                    }
                                                } else {
                                                    MACRO_CALL_MEMBER(
                                                        Map::TileMapState_Func::computeClimbRampRotation,
                                                        this)(this->DAT_SomeTile, (uint)((int)(iVar17)),
                                                        (uint)((int)(this->DAT_SomeY)));
                                                    this->PillarGFXLayer[this->DAT_SomeTile]
                                                        = (short)GMTotalPicturesProcessed::instance[9] + -1
                                                        + (short)this->wallCornerRotation;
                                                    this->MiscDisplayLayer[this->DAT_SomeTile]
                                                        = this->MiscDisplayLayer[this->DAT_SomeTile] | 0x800;
                                                    this->GfxLayer[this->DAT_SomeTile]
                                                        = (this->RandomLayer[this->DAT_SomeTile] & 3)
                                                        + (short)GMTotalPicturesProcessed::instance[0xe];
                                                    DAT_BuildingsState::instance.field14_0x18e024 = 1;
                                                }
                                            } else {
                                                BVar11 = MACRO_CALL_MEMBER(
                                                    Map::TileMapState_Func::isTileSuitableForBrushPlacement,
                                                    this)(this->DAT_SomeTile, (uint)((int)(iVar17)),
                                                    (uint)((int)(this->DAT_SomeY)));
                                                if (!BVar11) {
                                                    this->PillarGFXLayer[this->DAT_SomeTile] = 0x20;
                                                } else {
                                                    this->PillarGFXLayer[this->DAT_SomeTile]
                                                        = (this->RandomLayer[this->DAT_SomeTile] & 0xf) + 0x23;
                                                }
                                                this->GfxLayer[this->DAT_SomeTile]
                                                    = (short)GMTotalPicturesProcessed::instance[5] + 0x29c;
                                            }
                                        } else {
                                            BVar11 = MACRO_CALL_MEMBER(
                                                Map::TileMapState_Func::isTileSuitableForBrushPlacement, this)(
                                                this->DAT_SomeTile, (uint)((int)(iVar17)),
                                                (uint)((int)(this->DAT_SomeY)));
                                            if (!BVar11) {
                                                this->PillarGFXLayer[this->DAT_SomeTile] = 0x20;
                                            } else {
                                                this->PillarGFXLayer[this->DAT_SomeTile]
                                                    = (this->RandomLayer[this->DAT_SomeTile] & 0xf) + 0x23;
                                            }
                                            this->GfxLayer[this->DAT_SomeTile]
                                                = (short)GMTotalPicturesProcessed::instance[5] + 0x214;
                                        }
                                    } else if (DAT_BuildingsState::instance
                                                   .buildings[this->BuildingLayer[this->DAT_SomeTile]]
                                                   .buildingType
                                        == Map::Buildings::BT_DRAWBRIDGE) {
                                        MACRO_CALL_MEMBER(Map::TileMapState_Func::computeTileLuminescence,
                                            this)(this->DAT_SomeTile, this->DAT_SomeY);
                                    }
                                }
                                this->DAT_SomeX = this->DAT_SomeX + 1;
                            }
                        }
                    }
                }
            }
            local_c = DAT_PathFindingState::instance.mappingYRelated % 10;
            for (local_18 = this->someIndex; local_18 <= this->someLimit; local_18 = local_18 + 1) {
                for (local_10 = this->someYLike; local_10 <= this->someYLikeLimit; local_10 = local_10 + 1) {
                    if (*(char*)(local_18 * 0x28 + 0x1f93438 + local_10) != '\0') {
                        local_24 = local_c;
                        local_c = 0;
                        for (; local_24 < 10; local_24 = local_24 + 1) {
                            this->DAT_SomeY = local_18 * 10 + local_24;
                            this->DAT_SomeX = local_10 * 10;
                            for (local_30 = 0; local_30 < 10; local_30 = local_30 + 1) {
                                BVar11 = MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::xyAreValid,
                                    DAT_ViewportRenderState::ptr)(this->DAT_SomeX, (uint)((int)(this->DAT_SomeY)));
                                if ((((BVar11)
                                         && (this->DAT_SomeTile
                                             = MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::translateXYToTile,
                                                 DAT_ViewportRenderState::ptr)(this->DAT_SomeX, this->DAT_SomeY),
                                             (this->LogicLayer[this->DAT_SomeTile] & 0x100201U) != 0))
                                        && (this->ChangedLayer[this->DAT_SomeTile] != 0))
                                    && ((this->BuildingLayer[this->DAT_SomeTile] == 0
                                        && (!(this->LogicLayer[this->DAT_SomeTile] & 0x10000030U))))) {
                                    if (!(this->LogicLayer[this->DAT_SomeTile] & 1U)) {
                                        if ((this->LogicLayer[this->DAT_SomeTile] & 0x100000U)) {
                                            MACRO_CALL_MEMBER(
                                                Map::TileMapState_Func::computeTileCliffEdgeFlags, this)(
                                                this->DAT_SomeTile, this->DAT_SomeX, this->DAT_SomeY);
                                        }
                                    } else {
                                        this->MiscDisplayLayer[this->DAT_SomeTile]
                                            = this->MiscDisplayLayer[this->DAT_SomeTile] & 0xfffc;
                                        iVar17 = this->DAT_SomeTile
                                            + this->directionTranslationMatrix[this->DAT_SomeY][this->mapOrientation];
                                        this->gfxTileHeight = (ushort)this->HeightLayer[iVar17];
                                        if ((this->LogicLayer[iVar17] & 1U)) {
                                            this->gfxTileHeight = 0;
                                        }
                                        if ((this->LogicLayer[iVar17] & 0x80U)) {
                                            this->gfxTileHeight = 0x14;
                                        }
                                        if (0x13 < this->gfxTileHeight) {
                                            sVar4 = (short)GMTotalPicturesProcessed::instance[0xa6];
                                            if (this->gfxTileHeight < 0x5b) {
                                                if (this->gfxTileHeight < 0x29) {
                                                    this->GfxLayer[this->DAT_SomeTile] = sVar4 + 0x5dc;
                                                } else {
                                                    this->GfxLayer[this->DAT_SomeTile] = sVar4 + 0x5e2;
                                                }
                                            } else {
                                                this->GfxLayer[this->DAT_SomeTile] = sVar4 + 0x5ee;
                                            }
                                            this->PillarGFXLayer[this->DAT_SomeTile]
                                                = (ushort)GMTotalPicturesProcessed::instance[9];
                                            this->MiscDisplayLayer[this->DAT_SomeTile]
                                                = this->MiscDisplayLayer[this->DAT_SomeTile] | 0x40;
                                        }
                                        local_74 = 0;
                                        this->bitFlag = 0;
                                        for (local_70 = 0; local_70 < 8; local_70 = local_70 + 1) {
                                            iVar17 = this->DAT_SomeTile
                                                + this->directionTranslationMatrix[this->DAT_SomeY][local_70];
                                            if (this->HeightLayer[iVar17] < 0x14) {
                                                if (!(this->LogicLayer[iVar17] & 0x100031U)) {
                                                    this->bitFlag
                                                        = this->bitFlag | (byte)(0x80 >> ((byte)local_70 & 0x1f));
                                                }
                                                if ((!(this->LogicLayer[iVar17] & 0x100001U))
                                                    && ((this->Logic2Layer[iVar17] & 0x20))) {
                                                    local_74 = 0x80 >> ((byte)local_70 & 0x1f) | local_74;
                                                }
                                            }
                                        }
                                        if (this->bitFlag) {
                                            this->MiscDisplayLayer[this->DAT_SomeTile]
                                                = this->MiscDisplayLayer[this->DAT_SomeTile] | 0x100;
                                            this->CertainPathLayer[this->DAT_SomeTile]
                                                = (ushort)this->bitFlag | (ushort)(local_74 << 8);
                                        }
                                    }
                                    if ((this->LogicLayer[this->DAT_SomeTile] & 0x200U)) {
                                        uVar12 = this->screenSouthEastDirection + 7U & 0x80000007;
                                        if ((int)uVar12 < 0) {
                                            uVar12 = (uVar12 - 1 | 0xfffffff8) + 1;
                                        }
                                        iVar17 = this->DAT_SomeTile
                                            + this->directionTranslationMatrix[this->DAT_SomeY][uVar12];
                                        uVar12 = this->screenSouthEastDirection + 1U & 0x80000007;
                                        if ((int)uVar12 < 0) {
                                            uVar12 = (uVar12 - 1 | 0xfffffff8) + 1;
                                        }
                                        iVar13 = this->DAT_SomeTile
                                            + this->directionTranslationMatrix[this->DAT_SomeY][uVar12];
                                        if (((!((this->LogicLayer[iVar17] | this->LogicLayer[iVar13]) & 1U))
                                                && ((this->MiscDisplayLayer[iVar17] & 0x3c0)))
                                            && ((this->MiscDisplayLayer[iVar13] & 0x3c0))) {
                                            if (this->LuminesenceLayer[this->DAT_SomeTile] < 4) {
                                                this->GfxLayer[this->DAT_SomeTile]
                                                    = (short)GMTotalPicturesProcessed::instance[0xc] + 0x60
                                                    + (this->RandomLayer[this->DAT_SomeTile] & 7);
                                            } else {
                                                this->GfxLayer[this->DAT_SomeTile]
                                                    = (short)GMTotalPicturesProcessed::instance[0xc] + 0x68
                                                    + (this->RandomLayer[this->DAT_SomeTile] & 7);
                                            }
                                        }
                                        uVar12 = this->screenSouthEastDirection + 1U & 0x80000007;
                                        if ((int)uVar12 < 0) {
                                            uVar12 = (uVar12 - 1 | 0xfffffff8) + 1;
                                        }
                                        iVar17 = this->DAT_SomeTile
                                            + this->directionTranslationMatrix[this->DAT_SomeY][uVar12];
                                        uVar12 = this->screenSouthEastDirection + 3U & 0x80000007;
                                        if ((int)uVar12 < 0) {
                                            uVar12 = (uVar12 - 1 | 0xfffffff8) + 1;
                                        }
                                        iVar13 = this->DAT_SomeTile
                                            + this->directionTranslationMatrix[this->DAT_SomeY][uVar12];
                                        if (((!((this->LogicLayer[iVar17] | this->LogicLayer[iVar13]) & 1U))
                                                && ((this->MiscDisplayLayer[iVar17] & 0x3c0)))
                                            && ((this->MiscDisplayLayer[iVar13] & 0x3c0))) {
                                            if (!(this->DAT_SomeY & 1U)) {
                                                this->GfxLayer[this->DAT_SomeTile]
                                                    = (short)GMTotalPicturesProcessed::instance[0xc] + 0x138;
                                            } else {
                                                this->GfxLayer[this->DAT_SomeTile]
                                                    = (short)GMTotalPicturesProcessed::instance[0xc] + 0x137;
                                            }
                                            this->MiscDisplayLayer[this->DAT_SomeTile]
                                                = this->MiscDisplayLayer[this->DAT_SomeTile] | 0x3c0;
                                        }
                                        uVar12 = this->screenSouthEastDirection + 5U & 0x80000007;
                                        if ((int)uVar12 < 0) {
                                            uVar12 = (uVar12 - 1 | 0xfffffff8) + 1;
                                        }
                                        iVar17 = this->DAT_SomeTile
                                            + this->directionTranslationMatrix[this->DAT_SomeY][uVar12];
                                        uVar12 = this->screenSouthEastDirection + 7U & 0x80000007;
                                        if ((int)uVar12 < 0) {
                                            uVar12 = (uVar12 - 1 | 0xfffffff8) + 1;
                                        }
                                        iVar13 = this->DAT_SomeTile
                                            + this->directionTranslationMatrix[this->DAT_SomeY][uVar12];
                                        if (((!((this->LogicLayer[iVar17] | this->LogicLayer[iVar13]) & 1U))
                                                && ((this->MiscDisplayLayer[iVar17] & 0x3c0)))
                                            && ((this->MiscDisplayLayer[iVar13] & 0x3c0))) {
                                            if (!(this->DAT_SomeY & 1U)) {
                                                this->GfxLayer[this->DAT_SomeTile]
                                                    = (short)GMTotalPicturesProcessed::instance[0xc] + 0x13a;
                                            } else {
                                                this->GfxLayer[this->DAT_SomeTile]
                                                    = (short)GMTotalPicturesProcessed::instance[0xc] + 0x139;
                                            }
                                            this->MiscDisplayLayer[this->DAT_SomeTile]
                                                = this->MiscDisplayLayer[this->DAT_SomeTile] | 0x3c0;
                                        }
                                        uVar12 = this->screenSouthEastDirection + 3U & 0x80000007;
                                        if ((int)uVar12 < 0) {
                                            uVar12 = (uVar12 - 1 | 0xfffffff8) + 1;
                                        }
                                        iVar17 = this->DAT_SomeTile
                                            + this->directionTranslationMatrix[this->DAT_SomeY][uVar12];
                                        uVar12 = this->screenSouthEastDirection + 5U & 0x80000007;
                                        if ((int)uVar12 < 0) {
                                            uVar12 = (uVar12 - 1 | 0xfffffff8) + 1;
                                        }
                                        iVar13 = this->DAT_SomeTile
                                            + this->directionTranslationMatrix[this->DAT_SomeY][uVar12];
                                        if (((!((this->LogicLayer[iVar17] | this->LogicLayer[iVar13]) & 1U))
                                                && ((this->MiscDisplayLayer[iVar17] & 0x3c0)))
                                            && ((this->MiscDisplayLayer[iVar13] & 0x3c0))) {
                                            uVar12 = this->DAT_SomeY & 0x80000007;
                                            if ((int)uVar12 < 0) {
                                                uVar12 = (uVar12 - 1 | 0xfffffff8) + 1;
                                            }
                                            this->GfxLayer[this->DAT_SomeTile]
                                                = (short)GMTotalPicturesProcessed::instance[0xc] + 0x12f
                                                + (short)uVar12;
                                            this->MiscDisplayLayer[this->DAT_SomeTile]
                                                = this->MiscDisplayLayer[this->DAT_SomeTile] | 0x3c0;
                                        }
                                    }
                                }
                                this->DAT_SomeX = this->DAT_SomeX + 1;
                            }
                        }
                    }
                }
            }
            local_c = DAT_PathFindingState::instance.mappingYRelated % 10;
            for (local_18 = this->someIndex; local_18 <= this->someLimit; local_18 = local_18 + 1) {
                for (local_10 = this->someYLike; local_10 <= this->someYLikeLimit; local_10 = local_10 + 1) {
                    if (*(char*)(local_18 * 0x28 + 0x1f93438 + local_10) != '\0') {
                        local_24 = local_c;
                        local_c = 0;
                        for (; local_24 < 10; local_24 = local_24 + 1) {
                            this->DAT_SomeY = local_18 * 10 + local_24;
                            this->DAT_SomeX = local_10 * 10;
                            for (local_30 = 0; local_30 < 10; local_30 = local_30 + 1) {
                                BVar11 = MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::xyAreValid,
                                    DAT_ViewportRenderState::ptr)(this->DAT_SomeX, (uint)((int)(this->DAT_SomeY)));
                                if (((BVar11)
                                        && (this->DAT_SomeTile
                                            = MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::translateXYToTile,
                                                DAT_ViewportRenderState::ptr)(this->DAT_SomeX, this->DAT_SomeY),
                                            (this->LogicLayer[this->DAT_SomeTile] & 1U) != 0))
                                    && (((this->ChangedLayer[this->DAT_SomeTile] != 0
                                             && ((!(this->LogicLayer[this->DAT_SomeTile] & 0x10000030U)
                                                 && (this->BuildingLayer[this->DAT_SomeTile] == 0))))
                                        && (!(this->MiscDisplayLayer[this->DAT_SomeTile] & 0x40))))) {
                                    bVar19 = 0;
                                    if ((*(uint*)(this->ptr_MiscDisplayLayer + this->DAT_SomeTile * 2 + 2) & 0x80)) {
                                        bVar19 = 0x20;
                                    }
                                    if ((*(uint*)(this->ptr_MiscDisplayLayer + this->DAT_SomeTile * 2 + -2) & 0x80)) {
                                        bVar19 = bVar19 | 2;
                                    }
                                    puVar18 = (uint*)(this->ptr_MiscDisplayLayer
                                        + *(int*)(this->ptr_MovementDirectionTranslationMatrix + this->DAT_SomeY * 0x20)
                                            * 2
                                        + this->DAT_SomeTile * 2);
                                    if ((*(uint*)((int)puVar18 + -2) & 0x80)) {
                                        bVar19 = bVar19 | 1;
                                    }
                                    if ((*(uint*)((int)puVar18 + 2) & 0x80)) {
                                        bVar19 = bVar19 | 0x40;
                                    }
                                    if ((*puVar18 & 0x80)) {
                                        bVar19 = bVar19 | 0x80;
                                    }
                                    bVar16 = 0;
                                    if ((*(uint*)(this->ptr_MiscDisplayLayer + this->DAT_SomeTile * 2 + 2) & 0x40)) {
                                        bVar16 = 0x20;
                                    }
                                    if ((*(uint*)(this->ptr_MiscDisplayLayer + this->DAT_SomeTile * 2 + -2) & 0x40)) {
                                        bVar16 = bVar16 | 2;
                                    }
                                    puVar18 = (uint*)(this->ptr_MiscDisplayLayer
                                        + *(int*)(this->ptr_MovementDirectionTranslationMatrix + this->DAT_SomeY * 0x20)
                                            * 2
                                        + this->DAT_SomeTile * 2);
                                    if ((*(uint*)((int)puVar18 + -2) & 0x40)) {
                                        bVar16 = bVar16 | 1;
                                    }
                                    if ((*(uint*)((int)puVar18 + 2) & 0x40)) {
                                        bVar16 = bVar16 | 0x40;
                                    }
                                    if ((*puVar18 & 0x40)) {
                                        bVar16 = bVar16 | 0x80;
                                    }
                                    this->bitFlag = bVar16 & ~bVar19;
                                    if (this->bitFlag) {
                                        this->GfxLayer[this->DAT_SomeTile]
                                            = (short)GMTotalPicturesProcessed::instance[0xa6] + 0x5d0;
                                        this->PillarGFXLayer[this->DAT_SomeTile]
                                            = (ushort)GMTotalPicturesProcessed::instance[9];
                                        this->MiscDisplayLayer[this->DAT_SomeTile]
                                            = this->MiscDisplayLayer[this->DAT_SomeTile] | 0x80;
                                    }
                                }
                                this->DAT_SomeX = this->DAT_SomeX + 1;
                            }
                        }
                    }
                }
            }
            local_c = DAT_PathFindingState::instance.mappingYRelated % 10;
            for (local_18 = this->someIndex; local_18 <= this->someLimit; local_18 = local_18 + 1) {
                for (local_10 = this->someYLike; local_10 <= this->someYLikeLimit; local_10 = local_10 + 1) {
                    if (*(char*)(local_18 * 0x28 + 0x1f93438 + local_10) != '\0') {
                        local_24 = local_c;
                        local_c = 0;
                        for (; local_24 < 10; local_24 = local_24 + 1) {
                            this->DAT_SomeY = local_18 * 10 + local_24;
                            this->DAT_SomeX = local_10 * 10;
                            for (local_30 = 0; local_30 < 10; local_30 = local_30 + 1) {
                                BVar11 = MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::xyAreValid,
                                    DAT_ViewportRenderState::ptr)(this->DAT_SomeX, (uint)((int)(this->DAT_SomeY)));
                                if (((BVar11)
                                        && (this->DAT_SomeTile
                                            = MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::translateXYToTile,
                                                DAT_ViewportRenderState::ptr)(this->DAT_SomeX, this->DAT_SomeY),
                                            (this->LogicLayer[this->DAT_SomeTile] & L_BORDER | L_BORDER_EDGE) == 0))
                                    && (this->ChangedLayer[this->DAT_SomeTile] != 0)) {
                                    this->ChangedLayer[this->DAT_SomeTile] = this->ChangedLayer[this->DAT_SomeTile] - 1;
                                    iVar17 = this->DAT_SomeX;
                                    if (!(this->LogicLayer[this->DAT_SomeTile] & L_SEA)) {
                                        if (!(this->LogicLayer[this->DAT_SomeTile] & L_RIVER)) {
                                            if (!(this->LogicLayer[this->DAT_SomeTile] & L_FORD)) {
                                                if (!(this->LogicLayer[this->DAT_SomeTile] & L_PLAIN2_AND_PITCH)) {
                                                    if (this->BuildingLayer[this->DAT_SomeTile] != 0) {
                                                        iVar13 = (int)this->BuildingLayer[this->DAT_SomeTile];
                                                        if (DAT_BuildingsState::instance.buildings[iVar13].buildingType
                                                            == Map::Buildings::BT_STOCKPILE) {
                                                            this->wallCornerRotation
                                                                = MACRO_CALL_MEMBER(Map::TileMapState_Func::
                                                                                        computeWallCornerRenderRotation,
                                                                    this)(this->DAT_SomeX);
                                                            this->WallGFXLayer[this->DAT_SomeTile]
                                                                = (short)GMTotalPicturesProcessed::instance[10] + -1
                                                                + (short)this->wallCornerRotation;
                                                        }
                                                        iVar14 = MACRO_CALL_MEMBER(
                                                            Map::TileMapState_Func::computeClimbRampRotation,
                                                            this)(this->DAT_SomeTile, (uint)((int)(iVar17)),
                                                            (uint)((int)(this->DAT_SomeY)));
                                                        BVar1 = DAT_BuildingsState::instance.buildings[iVar13]
                                                                    .buildingType;
                                                        if (((BVar1 == Map::Buildings::BT_FIREBALLISTA)
                                                                || ((0x4f < (short)BVar1 && ((short)BVar1 < 0x55))))
                                                            && (!iVar14)) {
                                                            this->PillarGFXLayer[this->DAT_SomeTile]
                                                                = (short)(((((int)(uint)this
                                                                                    ->HeightLayer[this->DAT_SomeTile]
                                                                                >> 3)
                                                                               + -1)
                                                                              * 0x40)
                                                                      / 2)
                                                                + (short)GMTotalPicturesProcessed::instance[3]
                                                                + (ushort)this->LuminesenceLayer[this->DAT_SomeTile] * 4
                                                                + (this->RandomLayer[this->DAT_SomeTile] & 3);
                                                        } else {
                                                            this->PillarGFXLayer[this->DAT_SomeTile]
                                                                = (short)GMTotalPicturesProcessed::instance[9] + -1
                                                                + (short)this->wallCornerRotation;
                                                            this->MiscDisplayLayer[this->DAT_SomeTile]
                                                                = this->MiscDisplayLayer[this->DAT_SomeTile] | 0x800;
                                                        }
                                                        if (((DAT_BuildingsState::instance.buildings[iVar13]
                                                                     .buildingType
                                                                 == Map::Buildings::BT_KILLINGPIT)
                                                                && (DAT_BuildingsState::instance.buildings[iVar13].state
                                                                    < 1))
                                                            && ((BVar11 = MACRO_CALL_MEMBER(
                                                                     Game::GameStateStructures_Func::isSameTeam,
                                                                     DAT_GameState::ptr)(
                                                                     (int)DAT_BuildingsState::instance.buildings[iVar13]
                                                                         .owner,
                                                                     (int)((int)(DAT_GameSynchronyState::instance
                                                                             .currentPlayerSlotID))),
                                                                !BVar11
                                                                    && (DAT_GameCore::instance.gameMode_2
                                                                        != Game::GM_EDITOR)))) {
                                                            if (!(this->LogicLayer[this->DAT_SomeTile]
                                                                    & L_DEFAULT_EARTH_OR_TEXTURE))
                                                                goto LAB_00510585;
                                                            this->GfxLayer[this->DAT_SomeTile] = 0;
                                                        } else {
                                                            if (DAT_BuildingsState::instance.buildings[iVar13]
                                                                    .buildingType
                                                                == Map::Buildings::BT_SIEGETOWER_PLACED)
                                                                goto LAB_00510585;
                                                            if (DAT_BuildingsState::instance.buildings[iVar13]
                                                                    .currentTilePositionAdjusted
                                                                == this->DAT_SomeTile) {
                                                                MACRO_CALL_MEMBER(Map::TileMapState_Func::
                                                                                      updateBuildingGraphicsLayer,
                                                                    this)(iVar13);
                                                                goto LAB_005109e8;
                                                            }
                                                        }
                                                        goto LAB_0050c199;
                                                    }
                                                    if (!(this->LogicLayer[this->DAT_SomeTile]
                                                            & L_KEEP_NON_MANOR_HOUSE)) {
                                                        if ((!(this->LogicLayer[this->DAT_SomeTile] & L_ROCKY))
                                                            || ((this->LogicLayer[this->DAT_SomeTile]
                                                                & L_WALL_OR_GATEHOUSE))) {
                                                            if (!(this->LogicLayer[this->DAT_SomeTile] & L_BOULDERS)) {
                                                                if (!(this->LogicLayer[this->DAT_SomeTile]
                                                                        & L_PEBBLES)) {
                                                                    if (!(this->LogicLayer[this->DAT_SomeTile]
                                                                            & L_IRON)) {
                                                                        if (!(this->LogicLayer[this->DAT_SomeTile]
                                                                                & L_OIL)) {
                                                                            if (!(this->LogicLayer[this->DAT_SomeTile]
                                                                                    & L_MOAT)) {
                                                                                if ((!(this->LogicLayer[this
                                                                                               ->DAT_SomeTile]
                                                                                            & L_WALL_OR_GATEHOUSE
                                                                                        | L_FARM_FIELD_WHEAT
                                                                                        | L_FARM_FIELD_HOP
                                                                                        | L_FARM_FIELD_APPLE
                                                                                        | L_FARM_FIELD_DAIRY))
                                                                                    || ((this->LogicLayer[this
                                                                                                 ->DAT_SomeTile]
                                                                                        & L_FARM_FIELD_APPLE))) {
                                                                                    sVar8 = 0;
                                                                                    if ((this->WallOwnerLayer[this
                                                                                                 ->DAT_SomeTile]
                                                                                            & 8)) {
                                                                                        sVar8 = 0x2d;
                                                                                    }
                                                                                    if ((this->MiscDisplayLayer[this
                                                                                                 ->DAT_SomeTile]
                                                                                            & 0x80))
                                                                                        goto LAB_0050ffbc;
                                                                                    if ((((this->LogicLayer[this
                                                                                                   ->DAT_SomeTile]
                                                                                                 & L_WALL_OR_GATEHOUSE
                                                                                             | L_BUILDING
                                                                                             | L_KEEP_NON_MANOR_HOUSE))
                                                                                            || (this->BuildingWasLayer
                                                                                                    [this->DAT_SomeTile]
                                                                                                == '\0'))
                                                                                        || (!(
                                                                                            this->MiscDisplayLayer[this
                                                                                                    ->DAT_SomeTile]
                                                                                            & 0x10)))
                                                                                        goto LAB_00510585;
                                                                                }
                                                                            } else {
                                                                                this->bitFlag = 0;
                                                                                for (local_d4 = 0; local_d4 < 8;
                                                                                    local_d4 = local_d4 + 2) {
                                                                                    iVar13 = this->DAT_SomeTile
                                                                                        + this->directionTranslationMatrix
                                                                                              [this->DAT_SomeY]
                                                                                              [local_d4];
                                                                                    if (!(this->LogicLayer[iVar13]
                                                                                            & L_MOAT)) {
                                                                                        if (((this->BuildingLayer
                                                                                                     [iVar13]
                                                                                                 != 0)
                                                                                                && (DAT_BuildingsState::instance
                                                                                                        .buildings[this->BuildingLayer
                                                                                                                [iVar13]]
                                                                                                        .buildingType
                                                                                                    == Map::
                                                                                                        Buildings::
                                                                                                            BT_DRAWBRIDGE))
                                                                                            && (iVar13
                                                                                                = MACRO_CALL_MEMBER(
                                                                                                    Map::
                                                                                                        TileMapState_Func::
                                                                                                            returnOwnedMoatAtTile,
                                                                                                    this)(iVar13),
                                                                                                iVar13 != 0)) {
                                                                                            this->bitFlag
                                                                                                = this->bitFlag
                                                                                                | (byte)(0x80
                                                                                                    >> ((byte)local_d4
                                                                                                        & 0x1f));
                                                                                        }
                                                                                    } else {
                                                                                        this->bitFlag = this->bitFlag
                                                                                            | (byte)(0x80
                                                                                                >> ((byte)local_d4
                                                                                                    & 0x1f));
                                                                                    }
                                                                                }
                                                                                this->bitFlag = ~this->bitFlag & 0xaa;
                                                                                if (!this->bitFlag) {
                                                                                    this->bitFlag = 0;
                                                                                    for (local_d4 = 1; local_d4 < 8;
                                                                                        local_d4 = local_d4 + 2) {
                                                                                        iVar13 = this->DAT_SomeTile
                                                                                            + this->directionTranslationMatrix
                                                                                                  [this->DAT_SomeY]
                                                                                                  [local_d4];
                                                                                        if (!(this->LogicLayer[iVar13]
                                                                                                & L_MOAT)) {
                                                                                            if (((this->BuildingLayer
                                                                                                         [iVar13]
                                                                                                     != 0)
                                                                                                    && (DAT_BuildingsState::instance
                                                                                                            .buildings
                                                                                                                [this->BuildingLayer
                                                                                                                        [iVar13]]
                                                                                                            .buildingType
                                                                                                        == Map::
                                                                                                            Buildings::
                                                                                                                BT_DRAWBRIDGE))
                                                                                                && (iVar13
                                                                                                    = MACRO_CALL_MEMBER(
                                                                                                        Map::
                                                                                                            TileMapState_Func::
                                                                                                                returnOwnedMoatAtTile,
                                                                                                        this)(iVar13),
                                                                                                    iVar13 != 0)) {
                                                                                                this->bitFlag
                                                                                                    = this->bitFlag
                                                                                                    | (byte)(0x80
                                                                                                        >> ((byte)
                                                                                                                local_d4
                                                                                                            & 0x1f));
                                                                                            }
                                                                                        } else {
                                                                                            this->bitFlag
                                                                                                = this->bitFlag
                                                                                                | (byte)(0x80
                                                                                                    >> ((byte)local_d4
                                                                                                        & 0x1f));
                                                                                        }
                                                                                    }
                                                                                    this->bitFlag
                                                                                        = ~this->bitFlag & 0x55;
                                                                                }
                                                                                if (!this->mapOrientation) {
                                                                                    this->bitFlag = MACRO_CALL_MEMBER(
                                                                                        Map::Navigation::
                                                                                            DirectionAlgorithmState_Func::
                                                                                                rotateByteLeft,
                                                                                        DAT_DirectionAlgorithmState::
                                                                                            ptr)(this->bitFlag, 0);
                                                                                } else if (this->mapOrientation == 2) {
                                                                                    this->bitFlag = MACRO_CALL_MEMBER(
                                                                                        Map::Navigation::
                                                                                            DirectionAlgorithmState_Func::
                                                                                                rotateByteLeft,
                                                                                        DAT_DirectionAlgorithmState::
                                                                                            ptr)(this->bitFlag, 2);
                                                                                } else if (this->mapOrientation == 4) {
                                                                                    this->bitFlag = MACRO_CALL_MEMBER(
                                                                                        Map::Navigation::
                                                                                            DirectionAlgorithmState_Func::
                                                                                                rotateByteLeft,
                                                                                        DAT_DirectionAlgorithmState::
                                                                                            ptr)(this->bitFlag, 4);
                                                                                } else if (this->mapOrientation == 6) {
                                                                                    this->bitFlag = MACRO_CALL_MEMBER(
                                                                                        Map::Navigation::
                                                                                            DirectionAlgorithmState_Func::
                                                                                                rotateByteLeft,
                                                                                        DAT_DirectionAlgorithmState::
                                                                                            ptr)(this->bitFlag, 6);
                                                                                }
                                                                                this->GfxLayer[this->DAT_SomeTile]
                                                                                    = (short)GMTotalPicturesProcessed::
                                                                                          instance[5]
                                                                                    + 0xcc
                                                                                    + (ushort)this->LuminesenceLayer
                                                                                            [this->DAT_SomeTile]
                                                                                        * 4
                                                                                    + (this->RandomLayer[this
                                                                                               ->DAT_SomeTile]
                                                                                        & 3);
                                                                                for (local_14 = 0; local_14 < 7;
                                                                                    local_14 = local_14 + 1) {
                                                                                    if (DAT_TerrainDefinedData::instance
                                                                                            .TerrainFlagGraphicLookup
                                                                                                [local_14]
                                                                                            .unk1
                                                                                        == this->bitFlag) {
                                                                                        sVar4 = (short)
                                                                                            GMTotalPicturesProcessed::
                                                                                                instance[5];
                                                                                        if (local_14 < 4) {
                                                                                            this->GfxLayer[this
                                                                                                    ->DAT_SomeTile]
                                                                                                = sVar4 + 0xec
                                                                                                + (ushort)this->LuminesenceLayer
                                                                                                        [this->DAT_SomeTile]
                                                                                                    * 4
                                                                                                + (ushort)DAT_TerrainDefinedData::
                                                                                                      instance
                                                                                                          .TerrainFlagGraphicLookup
                                                                                                              [local_14]
                                                                                                          .unk2;
                                                                                        } else if (local_14 == 4) {
                                                                                            this->GfxLayer[this
                                                                                                    ->DAT_SomeTile]
                                                                                                = sVar4 + 0x10c
                                                                                                + (ushort)this->LuminesenceLayer
                                                                                                        [this->DAT_SomeTile]
                                                                                                    * 4
                                                                                                + (this->RandomLayer[this
                                                                                                           ->DAT_SomeTile]
                                                                                                    & 3);
                                                                                        } else if (local_14 == 5) {
                                                                                            this->GfxLayer[this
                                                                                                    ->DAT_SomeTile]
                                                                                                = sVar4 + 300
                                                                                                + (ushort)this->LuminesenceLayer
                                                                                                        [this->DAT_SomeTile]
                                                                                                    * 4
                                                                                                + (this->RandomLayer[this
                                                                                                           ->DAT_SomeTile]
                                                                                                    & 3);
                                                                                        } else if (local_14 == 6) {
                                                                                            this->GfxLayer[this
                                                                                                    ->DAT_SomeTile]
                                                                                                = sVar4 + 0x14c
                                                                                                + (ushort)this->LuminesenceLayer
                                                                                                      [this->DAT_SomeTile];
                                                                                        }
                                                                                        break;
                                                                                    }
                                                                                }
                                                                                if ((this->MiscDisplayLayer[this
                                                                                             ->DAT_SomeTile]
                                                                                        & 0x80)) {
                                                                                LAB_0050ffbc:
                                                                                    uVar12 = 0xdU - this->mapOrientation
                                                                                        & 0x80000007;
                                                                                    if ((int)uVar12 < 0) {
                                                                                        uVar12
                                                                                            = (uVar12 - 1 | 0xfffffff8)
                                                                                            + 1;
                                                                                    }
                                                                                    uVar15 = 9U - this->mapOrientation
                                                                                        & 0x80000007;
                                                                                    if ((int)uVar15 < 0) {
                                                                                        uVar15
                                                                                            = (uVar15 - 1 | 0xfffffff8)
                                                                                            + 1;
                                                                                    }
                                                                                    iVar13 = this->DAT_SomeTile
                                                                                        + this->directionTranslationMatrix
                                                                                              [this->DAT_SomeY][uVar15];
                                                                                    uVar2 = (ushort)iVar17;
                                                                                    uVar3 = (ushort)this->DAT_SomeY;
                                                                                    if (!(this->MiscDisplayLayer
                                                                                                [this->DAT_SomeTile
                                                                                                    + this->directionTranslationMatrix
                                                                                                        [this->DAT_SomeY]
                                                                                                        [uVar12]]
                                                                                            & 0x80)) {
                                                                                        if (!(this->MiscDisplayLayer
                                                                                                    [iVar13]
                                                                                                & 0x80)) {
                                                                                            this->AlphaGFXLayer[this
                                                                                                    ->DAT_SomeTile]
                                                                                                = this->AlphaGFXLayer[this
                                                                                                          ->DAT_SomeTile]
                                                                                                + ((uVar2 ^ uVar3) & 1);
                                                                                        } else if (
                                                                                            (!this->mapOrientation)
                                                                                            || (this->mapOrientation
                                                                                                == 4)) {
                                                                                            this->AlphaGFXLayer[this
                                                                                                    ->DAT_SomeTile]
                                                                                                = ((uVar2 ^ uVar3) & 1)
                                                                                                + 0x33 + sVar8;
                                                                                        } else {
                                                                                            this->AlphaGFXLayer[this
                                                                                                    ->DAT_SomeTile]
                                                                                                = ((uVar2 ^ uVar3) & 1)
                                                                                                + 0x35 + sVar8;
                                                                                        }
                                                                                    } else if (!(this->MiscDisplayLayer
                                                                                                       [iVar13]
                                                                                                   & 0x80)) {
                                                                                        if ((!this->mapOrientation)
                                                                                            || (this->mapOrientation
                                                                                                == 4)) {
                                                                                            this->AlphaGFXLayer[this
                                                                                                    ->DAT_SomeTile]
                                                                                                = ((uVar2 ^ uVar3) & 1)
                                                                                                + 0x35 + sVar8;
                                                                                        } else {
                                                                                            this->AlphaGFXLayer[this
                                                                                                    ->DAT_SomeTile]
                                                                                                = ((uVar2 ^ uVar3) & 1)
                                                                                                + 0x33 + sVar8;
                                                                                        }
                                                                                    } else if ((!this->mapOrientation)
                                                                                        || (this->mapOrientation
                                                                                            == 6)) {
                                                                                        uVar12 = this->DAT_SomeY
                                                                                            & 0x80000007;
                                                                                        if ((int)uVar12 < 0) {
                                                                                            uVar12 = (uVar12 - 1
                                                                                                         | 0xfffffff8)
                                                                                                + 1;
                                                                                        }
                                                                                        this->AlphaGFXLayer[this
                                                                                                ->DAT_SomeTile]
                                                                                            = (0x3e - (short)uVar12)
                                                                                            + sVar8;
                                                                                    } else {
                                                                                        uVar12 = this->DAT_SomeY
                                                                                            & 0x80000007;
                                                                                        if ((int)uVar12 < 0) {
                                                                                            uVar12 = (uVar12 - 1
                                                                                                         | 0xfffffff8)
                                                                                                + 1;
                                                                                        }
                                                                                        this->AlphaGFXLayer[this
                                                                                                ->DAT_SomeTile]
                                                                                            = (short)uVar12 + 0x37
                                                                                            + sVar8;
                                                                                    }
                                                                                    this->bitFlag = 0;
                                                                                    if ((*(uint*)(this->ptr_LogicLayer
                                                                                             + this->DAT_SomeTile * 4
                                                                                             + 4)
                                                                                            & 0x200)) {
                                                                                        this->bitFlag = 0x20;
                                                                                    }
                                                                                    if ((*(uint*)(this->ptr_LogicLayer
                                                                                             + this->DAT_SomeTile * 4
                                                                                             + -4)
                                                                                            & 0x200)) {
                                                                                        this->bitFlag
                                                                                            = this->bitFlag | 2;
                                                                                    }
                                                                                    puVar18 = (uint*)(this->ptr_LogicLayer
                                                                                        + *(int*)(this->ptr_MovementDirectionTranslationMatrix
                                                                                              + this->DAT_SomeY * 0x20)
                                                                                            * 4
                                                                                        + this->DAT_SomeTile * 4);
                                                                                    if ((puVar18[-1] & 0x200)) {
                                                                                        this->bitFlag
                                                                                            = this->bitFlag | 1;
                                                                                    }
                                                                                    if ((puVar18[1] & 0x200)) {
                                                                                        this->bitFlag
                                                                                            = this->bitFlag | 0x40;
                                                                                    }
                                                                                    if ((*puVar18 & 0x200)) {
                                                                                        this->bitFlag
                                                                                            = this->bitFlag | 0x80;
                                                                                    }
                                                                                    puVar18 = (uint*)(this->ptr_LogicLayer
                                                                                        + *(int*)((int)(this->ptr_MovementDirectionTranslationMatrix
                                                                                                      + this->DAT_SomeY
                                                                                                          * 0x20)
                                                                                              + 0x10)
                                                                                            * 4
                                                                                        + this->DAT_SomeTile * 4);
                                                                                    if ((puVar18[-1] & 0x200)) {
                                                                                        this->bitFlag
                                                                                            = this->bitFlag | 4;
                                                                                    }
                                                                                    if ((puVar18[1] & 0x200)) {
                                                                                        this->bitFlag
                                                                                            = this->bitFlag | 0x10;
                                                                                    }
                                                                                    if ((*puVar18 & 0x200)) {
                                                                                        this->bitFlag
                                                                                            = this->bitFlag | 8;
                                                                                    }
                                                                                    if (this->bitFlag) {
                                                                                        switch (this->mapOrientation) {
                                                                                        case 0:
                                                                                            if ((this->bitFlag & 0x82)
                                                                                                == 0x82) {
                                                                                                this->AlphaGFXLayer[this
                                                                                                        ->DAT_SomeTile]
                                                                                                    = this->AlphaGFXLayer
                                                                                                          [this->DAT_SomeTile]
                                                                                                    + 0xe;
                                                                                            }
                                                                                            break;
                                                                                        case 2:
                                                                                            if ((this->bitFlag & 0xa0)
                                                                                                == 0xa0) {
                                                                                                this->AlphaGFXLayer[this
                                                                                                        ->DAT_SomeTile]
                                                                                                    = this->AlphaGFXLayer
                                                                                                          [this->DAT_SomeTile]
                                                                                                    + 0xe;
                                                                                            }
                                                                                            break;
                                                                                        case 4:
                                                                                            if ((this->bitFlag & 0x28)
                                                                                                == 0x28) {
                                                                                                this->AlphaGFXLayer[this
                                                                                                        ->DAT_SomeTile]
                                                                                                    = this->AlphaGFXLayer
                                                                                                          [this->DAT_SomeTile]
                                                                                                    + 0xe;
                                                                                            }
                                                                                            break;
                                                                                        case 6:
                                                                                            if ((this->bitFlag & 10)
                                                                                                == 10) {
                                                                                                this->AlphaGFXLayer[this
                                                                                                        ->DAT_SomeTile]
                                                                                                    = this->AlphaGFXLayer
                                                                                                          [this->DAT_SomeTile]
                                                                                                    + 0xe;
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                    if (!(this->LogicLayer[this
                                                                                                  ->DAT_SomeTile]
                                                                                                & L_PLAIN2_AND_PITCH
                                                                                            | L_MOAT))
                                                                                        goto LAB_00510585;
                                                                                }
                                                                            }
                                                                        } else {
                                                                            this->PillarGFXLayer[this
                                                                                    ->DAT_SomeTile] = (ushort)
                                                                                GMTotalPicturesProcessed::instance[9];
                                                                            this->wallCornerRotation
                                                                                = (int)(short)this
                                                                                      ->RandomLayer[this->DAT_SomeTile]
                                                                                & 7;
                                                                            this->GfxLayer[this->DAT_SomeTile]
                                                                                = (short)GMTotalPicturesProcessed::
                                                                                      instance[0x37]
                                                                                + 0x428
                                                                                + (short)(this->wallCornerRotation << 4);
                                                                            sVar4 = (short)this->DAT_SomeY;
                                                                            sVar5 = (short)this->DAT_SomeX;
                                                                            if (!this->wallCornerRotation) {
                                                                                this->WallGFXLayer[this->DAT_SomeTile]
                                                                                    = this->RandomLayer[this
                                                                                              ->DAT_SomeTile]
                                                                                        + sVar5 + sVar4
                                                                                    & 0x1ff;
                                                                            } else if (this->wallCornerRotation == 1) {
                                                                                this->WallGFXLayer[this->DAT_SomeTile]
                                                                                    = this->RandomLayer[this
                                                                                              ->DAT_SomeTile]
                                                                                        + sVar5 + sVar4
                                                                                    & 0x1ff;
                                                                            } else if (this->wallCornerRotation == 2) {
                                                                                this->WallGFXLayer[this->DAT_SomeTile]
                                                                                    = this->RandomLayer[this
                                                                                              ->DAT_SomeTile]
                                                                                        + sVar5 + sVar4
                                                                                    & 0x7f;
                                                                            } else if (this->wallCornerRotation == 3) {
                                                                                this->WallGFXLayer[this->DAT_SomeTile]
                                                                                    = this->RandomLayer[this
                                                                                              ->DAT_SomeTile]
                                                                                        + sVar5 + sVar4
                                                                                    & 0x7f;
                                                                            } else if (this->wallCornerRotation == 4) {
                                                                                this->WallGFXLayer[this->DAT_SomeTile]
                                                                                    = this->RandomLayer[this
                                                                                              ->DAT_SomeTile]
                                                                                        + sVar5 + sVar4
                                                                                    & 0xff;
                                                                            } else if (this->wallCornerRotation == 5) {
                                                                                this->WallGFXLayer[this->DAT_SomeTile]
                                                                                    = this->RandomLayer[this
                                                                                              ->DAT_SomeTile]
                                                                                        + sVar5 + sVar4
                                                                                    & 0xff;
                                                                            } else if (this->wallCornerRotation == 6) {
                                                                                this->WallGFXLayer[this->DAT_SomeTile]
                                                                                    = this->RandomLayer[this
                                                                                              ->DAT_SomeTile]
                                                                                        + sVar5 + sVar4
                                                                                    & 0x7f;
                                                                            } else if (this->wallCornerRotation == 7) {
                                                                                this->WallGFXLayer[this->DAT_SomeTile]
                                                                                    = this->RandomLayer[this
                                                                                              ->DAT_SomeTile]
                                                                                        + sVar5 + sVar4
                                                                                    & 0x7f;
                                                                            }
                                                                        }
                                                                    } else {
                                                                        MACRO_CALL_MEMBER(
                                                                            Map::TileMapState_Func::
                                                                                computeClimbRampRotation,
                                                                            this)(this->DAT_SomeTile,
                                                                            (uint)((int)(this->DAT_SomeX)),
                                                                            (uint)((int)(this->DAT_SomeY)));
                                                                        this->PillarGFXLayer[this->DAT_SomeTile]
                                                                            = (short)
                                                                                  GMTotalPicturesProcessed::instance[9]
                                                                            + -1 + (short)this->wallCornerRotation;
                                                                        this->MiscDisplayLayer[this->DAT_SomeTile]
                                                                            = this->MiscDisplayLayer[this->DAT_SomeTile]
                                                                            | 0x800;
                                                                        this->wallCornerRotation
                                                                            = (int)(short)this
                                                                                  ->RandomLayer[this->DAT_SomeTile]
                                                                            & 0xf;
                                                                        this->GfxLayer[this->DAT_SomeTile]
                                                                            = (short)GMTotalPicturesProcessed::instance
                                                                                  [0xc]
                                                                            + 0xee + (short)this->wallCornerRotation;
                                                                    }
                                                                } else {
                                                                    MACRO_CALL_MEMBER(Map::TileMapState_Func::
                                                                                          computeClimbRampRotation,
                                                                        this)(this->DAT_SomeTile,
                                                                        (uint)((int)(this->DAT_SomeX)),
                                                                        (uint)((int)(this->DAT_SomeY)));
                                                                    this->PillarGFXLayer[this->DAT_SomeTile]
                                                                        = (short)GMTotalPicturesProcessed::instance[9]
                                                                        + -1 + (short)this->wallCornerRotation;
                                                                    this->MiscDisplayLayer[this->DAT_SomeTile]
                                                                        = this->MiscDisplayLayer[this->DAT_SomeTile]
                                                                        | 0x800;
                                                                    this->wallCornerRotation
                                                                        = (int)(short)this
                                                                              ->RandomLayer[this->DAT_SomeTile]
                                                                        & 0xf;
                                                                    if (this->LuminesenceLayer[this->DAT_SomeTile]
                                                                        < 6) {
                                                                        this->GfxLayer[this->DAT_SomeTile]
                                                                            = (short)GMTotalPicturesProcessed::instance
                                                                                  [0xc]
                                                                            + 0x20 + (short)this->wallCornerRotation;
                                                                    } else {
                                                                        this->GfxLayer[this->DAT_SomeTile]
                                                                            = (short)GMTotalPicturesProcessed::instance
                                                                                  [0xc]
                                                                            + 0x30 + (short)this->wallCornerRotation;
                                                                    }
                                                                }
                                                            } else {
                                                                MACRO_CALL_MEMBER(Map::TileMapState_Func::
                                                                                      computeClimbRampRotation,
                                                                    this)(this->DAT_SomeTile,
                                                                    (uint)((int)(this->DAT_SomeX)),
                                                                    (uint)((int)(this->DAT_SomeY)));
                                                                this->PillarGFXLayer[this->DAT_SomeTile]
                                                                    = (short)GMTotalPicturesProcessed::instance[9] + -1
                                                                    + (short)this->wallCornerRotation;
                                                                this->MiscDisplayLayer[this->DAT_SomeTile]
                                                                    = this->MiscDisplayLayer[this->DAT_SomeTile]
                                                                    | 0x800;
                                                                this->wallCornerRotation
                                                                    = (int)(short)this->RandomLayer[this->DAT_SomeTile]
                                                                    & 0xf;
                                                                if (this->LuminesenceLayer[this->DAT_SomeTile] < 6) {
                                                                    this->GfxLayer[this->DAT_SomeTile]
                                                                        = (short)GMTotalPicturesProcessed::instance[0xc]
                                                                        + 0x40 + (short)this->wallCornerRotation;
                                                                } else {
                                                                    this->GfxLayer[this->DAT_SomeTile]
                                                                        = (short)GMTotalPicturesProcessed::instance[0xc]
                                                                        + 0x50 + (short)this->wallCornerRotation;
                                                                }
                                                            }
                                                        } else {
                                                            MACRO_CALL_MEMBER(Map::TileMapState_Func::
                                                                                  computeClimbRampRotation,
                                                                this)(this->DAT_SomeTile,
                                                                (uint)((int)(this->DAT_SomeX)),
                                                                (uint)((int)(this->DAT_SomeY)));
                                                            this->PillarGFXLayer[this->DAT_SomeTile]
                                                                = (short)GMTotalPicturesProcessed::instance[9] + -1
                                                                + (short)this->wallCornerRotation;
                                                            this->MiscDisplayLayer[this->DAT_SomeTile]
                                                                = this->MiscDisplayLayer[this->DAT_SomeTile] | 0x800;
                                                            iVar13 = (int)this->OrganismLayer[this->DAT_SomeTile];
                                                            if (1999 < iVar13) {
                                                                if (*(int*)(&DAT_LandscapeState::instance.trees[0x635]
                                                                                .unknownDistanceRelatedToCrow
                                                                        + iVar13 * 0x10)
                                                                    == this->DAT_SomeTile) {
                                                                    MACRO_CALL_MEMBER(Map::TileMapState_Func::
                                                                                          applyRockGraphicsToFootprint,
                                                                        this)(iVar13 + -2000);
                                                                }
                                                                goto LAB_0050c199;
                                                            }
                                                            this->wallCornerRotation
                                                                = (int)(short)this->RandomLayer[this->DAT_SomeTile] & 7;
                                                            this->GfxLayer[this->DAT_SomeTile]
                                                                = (short)GMTotalPicturesProcessed::instance[0x38]
                                                                + (ushort)this->LuminesenceLayer[this->DAT_SomeTile] * 8
                                                                + (short)this->wallCornerRotation;
                                                        }
                                                    } else {
                                                        if (DAT_BuildingsState::instance
                                                                .buildings[this->BuildingLayer[this->DAT_SomeTile]]
                                                                .currentTilePositionAdjusted
                                                            != this->DAT_SomeTile)
                                                            goto LAB_0050c199;
                                                        MACRO_CALL_MEMBER(Map::TileMapState_Func::
                                                                              updateBuildingGraphicsLayer,
                                                            this)((int)this->BuildingLayer[this->DAT_SomeTile]);
                                                    }
                                                } else {
                                                    this->MiscDisplayLayer[this->DAT_SomeTile]
                                                        = this->MiscDisplayLayer[this->DAT_SomeTile] & 0xdfff;
                                                    iVar13 = MACRO_CALL_MEMBER(
                                                        Map::TileMapState_Func::getPitchDitchIDForTile, this)(
                                                        this->DAT_SomeTile);
                                                    if (iVar13) {
                                                        if (((this->pitchDitches[iVar13].state < 2)
                                                                && (BVar11 = MACRO_CALL_MEMBER(
                                                                        Game::GameStateStructures_Func::isSameTeam,
                                                                        DAT_GameState::ptr)(
                                                                        (int)this->pitchDitches[iVar13].owner,
                                                                        (int)((int)(DAT_GameSynchronyState::instance
                                                                                .currentPlayerSlotID))),
                                                                    !BVar11))
                                                            && (DAT_GameCore::instance.gameMode_2 != Game::GM_EDITOR)) {
                                                            if (!(this->LogicLayer[this->DAT_SomeTile]
                                                                    & L_DEFAULT_EARTH_OR_TEXTURE))
                                                                goto LAB_00510585;
                                                            this->GfxLayer[this->DAT_SomeTile] = 0;
                                                        } else {
                                                            MACRO_CALL_MEMBER(Map::TileMapState_Func::
                                                                                  computeClimbRampRotation,
                                                                this)(this->DAT_SomeTile, (uint)((int)(iVar17)),
                                                                (uint)((int)(this->DAT_SomeY)));
                                                            this->PillarGFXLayer[this->DAT_SomeTile]
                                                                = (short)GMTotalPicturesProcessed::instance[9] + -1
                                                                + (short)this->wallCornerRotation;
                                                            this->MiscDisplayLayer[this->DAT_SomeTile]
                                                                = this->MiscDisplayLayer[this->DAT_SomeTile] | 0x800;
                                                            this->GfxLayer[this->DAT_SomeTile]
                                                                = (this->pitchDitches[iVar13].rng & 7U)
                                                                + (short)GMTotalPicturesProcessed::instance[0x8c];
                                                            this->MiscDisplayLayer[this->DAT_SomeTile]
                                                                = this->MiscDisplayLayer[this->DAT_SomeTile] | 0x2000;
                                                            if ((this->MiscDisplayLayer[this->DAT_SomeTile] & 0x80))
                                                                goto LAB_0050ffbc;
                                                        }
                                                        goto LAB_0050c199;
                                                    }
                                                LAB_00510585:
                                                    uVar12
                                                        = ((int)(uint)this->HeightLayer[this->DAT_SomeTile] >> 3) - 1U
                                                        & 0x8000000f;
                                                    if ((int)uVar12 < 0) {
                                                        uVar12 = (uVar12 - 1 | 0xfffffff0) + 1;
                                                    }
                                                    local_8 = uVar12 * 0x40 + 1;
                                                    iVar13 = MACRO_CALL_MEMBER(
                                                        Map::TileMapState_Func::computeClimbRampRotation,
                                                        this)(this->DAT_SomeTile, (uint)((int)(iVar17)),
                                                        (uint)((int)(this->DAT_SomeY)));
                                                    if ((this->HeightLayer[this->DAT_SomeTile] < 0x88) && (!iVar13)) {
                                                        if (local_8 < 1) {
                                                            local_8 = 1;
                                                        }
                                                        this->PillarGFXLayer[this->DAT_SomeTile]
                                                            = (short)((local_8 + -1) / 2)
                                                            + (short)GMTotalPicturesProcessed::instance[3]
                                                            + (ushort)this->LuminesenceLayer[this->DAT_SomeTile] * 4
                                                            + (this->RandomLayer[this->DAT_SomeTile] & 3);
                                                        BVar11 = MACRO_CALL_MEMBER(
                                                            Map::TileMapState_Func::isCliffDropInDirection,
                                                            this)(this->DAT_SomeTile, (undefined4)((int)(iVar17)),
                                                            this->DAT_SomeY);
                                                        if (!BVar11) {
                                                            bVar10 = false;
                                                        } else {
                                                            bVar10 = true;
                                                        }
                                                    } else {
                                                        this->PillarGFXLayer[this->DAT_SomeTile]
                                                            = (short)GMTotalPicturesProcessed::instance[9] + -1
                                                            + (short)this->wallCornerRotation;
                                                        this->MiscDisplayLayer[this->DAT_SomeTile]
                                                            = this->MiscDisplayLayer[this->DAT_SomeTile] | 0x800;
                                                        bVar10 = true;
                                                    }
                                                    if (!(this->Logic2Layer[this->DAT_SomeTile] & 0x20)) {
                                                        if (this->HeightLayer[this->DAT_SomeTile] < 8) {
                                                            if (!(this->Logic2Layer[this->DAT_SomeTile] & 2)) {
                                                                this->GfxLayer[this->DAT_SomeTile]
                                                                    = (short)GMTotalPicturesProcessed::instance[2]
                                                                    + (ushort)this->LuminesenceLayer[this->DAT_SomeTile]
                                                                        * 4
                                                                    + (this->RandomLayer[this->DAT_SomeTile] & 3);
                                                            } else {
                                                                this->GfxLayer[this->DAT_SomeTile]
                                                                    = (short)GMTotalPicturesProcessed::instance[0x37]
                                                                    + 0xb4
                                                                    + (this->RandomLayer[this->DAT_SomeTile] & 7);
                                                            }
                                                        } else if (!(this->LogicLayer[this->DAT_SomeTile]
                                                                       & L_DEFAULT_EARTH_OR_TEXTURE)) {
                                                            if ((bVar10)
                                                                && (DAT_GameCore::instance.gameMode_2
                                                                    == Game::GM_EDITOR)) {
                                                                this->LogicLayer[this->DAT_SomeTile]
                                                                    = this->LogicLayer[this->DAT_SomeTile] | 128;
                                                                this->GfxLayer[this->DAT_SomeTile]
                                                                    = (short)GMTotalPicturesProcessed::instance[0x38]
                                                                    + (ushort)this->LuminesenceLayer[this->DAT_SomeTile]
                                                                        * 8
                                                                    + (this->RandomLayer[this->DAT_SomeTile] & 7);
                                                            } else {
                                                                this->GfxLayer[this->DAT_SomeTile]
                                                                    = (short)GMTotalPicturesProcessed::instance[2]
                                                                    + ((short)((int)(uint)this
                                                                                   ->HeightLayer[this->DAT_SomeTile]
                                                                           >> 3)
                                                                          + -1)
                                                                        * 0x20
                                                                    + (ushort)this->LuminesenceLayer[this->DAT_SomeTile]
                                                                        * 4
                                                                    + (this->RandomLayer[this->DAT_SomeTile] & 3);
                                                            }
                                                        } else {
                                                            /*
                                                              sets section 1001 after placing oasis grass for example
                                                             */
                                                            this->GfxLayer[this->DAT_SomeTile] = 0;
                                                        }
                                                    } else {
                                                        this->GfxLayer[this->DAT_SomeTile] = 0;
                                                    }
                                                }
                                            } else {
                                                bVar19 = 0;
                                                if ((*(uint*)(this->ptr_LogicLayer + this->DAT_SomeTile * 4 + 4)
                                                            & L_RIVER
                                                        | L_FORD)) {
                                                    bVar19 = 0x20;
                                                }
                                                if ((*(uint*)(this->ptr_LogicLayer + this->DAT_SomeTile * 4 + -4)
                                                            & L_RIVER
                                                        | L_FORD)) {
                                                    bVar19 = bVar19 | 2;
                                                }
                                                if ((*(uint*)(this->ptr_LogicLayer
                                                         + *(int*)(this->ptr_MovementDirectionTranslationMatrix
                                                               + this->DAT_SomeY * 0x20)
                                                             * 4
                                                         + this->DAT_SomeTile * 4)
                                                            & L_RIVER
                                                        | L_FORD)) {
                                                    bVar19 = bVar19 | 0x80;
                                                }
                                                if ((*(uint*)(this->ptr_LogicLayer
                                                         + *(int*)((int)(this->ptr_MovementDirectionTranslationMatrix
                                                                       + this->DAT_SomeY * 0x20)
                                                               + 0x10)
                                                             * 4
                                                         + this->DAT_SomeTile * 4)
                                                            & L_RIVER
                                                        | L_FORD)) {
                                                    bVar19 = bVar19 | 8;
                                                }
                                                this->bitFlag = ~bVar19 & 0xaa;
                                                if (!this->bitFlag) {
                                                    bVar19 = (*(uint*)(this->ptr_LogicLayer
                                                                  + *(int*)(this->ptr_MovementDirectionTranslationMatrix
                                                                        + this->DAT_SomeY * 0x20)
                                                                      * 4
                                                                  + this->DAT_SomeTile * 4 + -4)
                                                                     & L_RIVER
                                                                 | L_FORD)
                                                        != 0;
                                                    if ((*(uint*)(this->ptr_LogicLayer
                                                             + *(int*)(this->ptr_MovementDirectionTranslationMatrix
                                                                   + this->DAT_SomeY * 0x20)
                                                                 * 4
                                                             + this->DAT_SomeTile * 4 + 4)
                                                            & 0x300000)) {
                                                        bVar19 = bVar19 | 0x40;
                                                    }
                                                    if ((*(uint*)(this->ptr_LogicLayer
                                                             + *(int*)((int)(this->ptr_MovementDirectionTranslationMatrix
                                                                           + this->DAT_SomeY * 0x20)
                                                                   + 0x10)
                                                                 * 4
                                                             + this->DAT_SomeTile * 4 + -4)
                                                            & 0x300000)) {
                                                        bVar19 = bVar19 | 4;
                                                    }
                                                    if ((*(uint*)(this->ptr_LogicLayer
                                                             + *(int*)((int)(this->ptr_MovementDirectionTranslationMatrix
                                                                           + this->DAT_SomeY * 0x20)
                                                                   + 0x10)
                                                                 * 4
                                                             + this->DAT_SomeTile * 4 + 4)
                                                            & 0x300000)) {
                                                        bVar19 = bVar19 | 0x10;
                                                    }
                                                    this->bitFlag = ~bVar19 & 0x55;
                                                }
                                                if (!this->mapOrientation) {
                                                    this->bitFlag = MACRO_CALL_MEMBER(
                                                        Map::Navigation::DirectionAlgorithmState_Func::
                                                            rotateByteLeft,
                                                        DAT_DirectionAlgorithmState::ptr)(this->bitFlag, 0);
                                                } else if (this->mapOrientation == 2) {
                                                    this->bitFlag = MACRO_CALL_MEMBER(
                                                        Map::Navigation::DirectionAlgorithmState_Func::
                                                            rotateByteLeft,
                                                        DAT_DirectionAlgorithmState::ptr)(this->bitFlag, 2);
                                                } else if (this->mapOrientation == 4) {
                                                    this->bitFlag = MACRO_CALL_MEMBER(
                                                        Map::Navigation::DirectionAlgorithmState_Func::
                                                            rotateByteLeft,
                                                        DAT_DirectionAlgorithmState::ptr)(this->bitFlag, 4);
                                                } else if (this->mapOrientation == 6) {
                                                    this->bitFlag = MACRO_CALL_MEMBER(
                                                        Map::Navigation::DirectionAlgorithmState_Func::
                                                            rotateByteLeft,
                                                        DAT_DirectionAlgorithmState::ptr)(this->bitFlag, 6);
                                                }
                                                this->GfxLayer[this->DAT_SomeTile]
                                                    = (short)GMTotalPicturesProcessed::instance[5] + 0x29c
                                                    + (ushort)this->LuminesenceLayer[this->DAT_SomeTile] * 8
                                                    + (this->RandomLayer[this->DAT_SomeTile] & 7);
                                                for (local_14 = 0; local_14 < 7; local_14 = local_14 + 1) {
                                                    if (DAT_TerrainDefinedData::instance
                                                            .TerrainFlagGraphicLookup[local_14]
                                                            .unk1
                                                        == this->bitFlag) {
                                                        sVar4 = (short)GMTotalPicturesProcessed::instance[5];
                                                        if (local_14 < 4) {
                                                            this->GfxLayer[this->DAT_SomeTile] = sVar4 + 0x234
                                                                + (ushort)this->LuminesenceLayer[this->DAT_SomeTile] * 4
                                                                + (ushort)DAT_TerrainDefinedData::instance
                                                                      .TerrainFlagGraphicLookup[local_14]
                                                                      .unk2;
                                                        } else if (local_14 == 4) {
                                                            this->GfxLayer[this->DAT_SomeTile] = sVar4 + 0x254
                                                                + (ushort)this->LuminesenceLayer[this->DAT_SomeTile] * 4
                                                                + (this->RandomLayer[this->DAT_SomeTile] & 3);
                                                        } else if (local_14 == 5) {
                                                            this->GfxLayer[this->DAT_SomeTile] = sVar4 + 0x274
                                                                + (ushort)this->LuminesenceLayer[this->DAT_SomeTile] * 4
                                                                + (this->RandomLayer[this->DAT_SomeTile] & 3);
                                                        } else if (local_14 == 6) {
                                                            this->GfxLayer[this->DAT_SomeTile] = sVar4 + 0x294
                                                                + (ushort)this->LuminesenceLayer[this->DAT_SomeTile];
                                                        }
                                                        break;
                                                    }
                                                }
                                            }
                                        } else {
                                            this->Logic2Layer[this->DAT_SomeTile]
                                                = this->Logic2Layer[this->DAT_SomeTile] & 0xf7;
                                            bVar19 = 0;
                                            if ((*(uint*)(this->ptr_LogicLayer + this->DAT_SomeTile * 4 + 4) & 1)) {
                                                bVar19 = 0x20;
                                            }
                                            if ((*(uint*)(this->ptr_LogicLayer + this->DAT_SomeTile * 4 + -4) & 1)) {
                                                bVar19 = bVar19 | 2;
                                            }
                                            if ((*(uint*)(this->ptr_LogicLayer
                                                     + *(int*)(this->ptr_MovementDirectionTranslationMatrix
                                                           + this->DAT_SomeY * 0x20)
                                                         * 4
                                                     + this->DAT_SomeTile * 4)
                                                    & 1)) {
                                                bVar19 = bVar19 | 0x80;
                                            }
                                            if ((*(uint*)(this->ptr_LogicLayer
                                                     + *(int*)((int)(this->ptr_MovementDirectionTranslationMatrix
                                                                   + this->DAT_SomeY * 0x20)
                                                           + 0x10)
                                                         * 4
                                                     + this->DAT_SomeTile * 4)
                                                    & 1)) {
                                                bVar19 = bVar19 | 8;
                                            }
                                            if ((bVar19)
                                                && (this->Logic2Layer[this->DAT_SomeTile]
                                                    = this->Logic2Layer[this->DAT_SomeTile] | 8,
                                                    (this->Logic2Layer[this->DAT_SomeTile] & 0x20) != 0)) {
                                                this->Logic2Layer[this->DAT_SomeTile]
                                                    = this->Logic2Layer[this->DAT_SomeTile] & 0xdf;
                                                this->WallGFXLayer[this->DAT_SomeTile]
                                                    = this->RandomLayer[this->DAT_SomeTile] & 7;
                                            }
                                            bVar19 = 0;
                                            if ((*(uint*)(this->ptr_LogicLayer + this->DAT_SomeTile * 4 + 4)
                                                    & 0x100031)) {
                                                bVar19 = 0x20;
                                            }
                                            if ((*(uint*)(this->ptr_LogicLayer + this->DAT_SomeTile * 4 + -4)
                                                    & 0x100031)) {
                                                bVar19 = bVar19 | 2;
                                            }
                                            if ((*(uint*)(this->ptr_LogicLayer
                                                     + *(int*)(this->ptr_MovementDirectionTranslationMatrix
                                                           + this->DAT_SomeY * 0x20)
                                                         * 4
                                                     + this->DAT_SomeTile * 4)
                                                    & 0x100031)) {
                                                bVar19 = bVar19 | 0x80;
                                            }
                                            if ((*(uint*)(this->ptr_LogicLayer
                                                     + *(int*)((int)(this->ptr_MovementDirectionTranslationMatrix
                                                                   + this->DAT_SomeY * 0x20)
                                                           + 0x10)
                                                         * 4
                                                     + this->DAT_SomeTile * 4)
                                                    & 0x100031)) {
                                                bVar19 = bVar19 | 8;
                                            }
                                            this->bitFlag = ~bVar19 & 0xaa;
                                            if (!this->bitFlag) {
                                                bVar19 = (*(uint*)(this->ptr_LogicLayer
                                                              + *(int*)(this->ptr_MovementDirectionTranslationMatrix
                                                                    + this->DAT_SomeY * 0x20)
                                                                  * 4
                                                              + this->DAT_SomeTile * 4 + -4)
                                                             & 0x100031)
                                                    != 0;
                                                if ((*(uint*)(this->ptr_LogicLayer
                                                         + *(int*)(this->ptr_MovementDirectionTranslationMatrix
                                                               + this->DAT_SomeY * 0x20)
                                                             * 4
                                                         + this->DAT_SomeTile * 4 + 4)
                                                        & 0x100031)) {
                                                    bVar19 = bVar19 | 0x40;
                                                }
                                                if ((*(uint*)(this->ptr_LogicLayer
                                                         + *(int*)((int)(this->ptr_MovementDirectionTranslationMatrix
                                                                       + this->DAT_SomeY * 0x20)
                                                               + 0x10)
                                                             * 4
                                                         + this->DAT_SomeTile * 4 + -4)
                                                        & 0x100031)) {
                                                    bVar19 = bVar19 | 4;
                                                }
                                                if ((*(uint*)(this->ptr_LogicLayer
                                                         + *(int*)((int)(this->ptr_MovementDirectionTranslationMatrix
                                                                       + this->DAT_SomeY * 0x20)
                                                               + 0x10)
                                                             * 4
                                                         + this->DAT_SomeTile * 4 + 4)
                                                        & 0x100031)) {
                                                    bVar19 = bVar19 | 0x10;
                                                }
                                                this->bitFlag = ~bVar19 & 0x55;
                                            }
                                            if (!this->mapOrientation) {
                                                this->bitFlag = MACRO_CALL_MEMBER(
                                                    Map::Navigation::DirectionAlgorithmState_Func::
                                                        rotateByteLeft,
                                                    DAT_DirectionAlgorithmState::ptr)(this->bitFlag, 0);
                                            } else if (this->mapOrientation == 2) {
                                                this->bitFlag = MACRO_CALL_MEMBER(
                                                    Map::Navigation::DirectionAlgorithmState_Func::
                                                        rotateByteLeft,
                                                    DAT_DirectionAlgorithmState::ptr)(this->bitFlag, 2);
                                            } else if (this->mapOrientation == 4) {
                                                this->bitFlag = MACRO_CALL_MEMBER(
                                                    Map::Navigation::DirectionAlgorithmState_Func::
                                                        rotateByteLeft,
                                                    DAT_DirectionAlgorithmState::ptr)(this->bitFlag, 4);
                                            } else if (this->mapOrientation == 6) {
                                                this->bitFlag = MACRO_CALL_MEMBER(
                                                    Map::Navigation::DirectionAlgorithmState_Func::
                                                        rotateByteLeft,
                                                    DAT_DirectionAlgorithmState::ptr)(this->bitFlag, 6);
                                            }
                                            MACRO_CALL_MEMBER(
                                                Map::TileMapState_Func::propagateCliffEdgeFlagFromNeighbor,
                                                this)(this->DAT_SomeTile, iVar17, this->DAT_SomeY);
                                            if (this->Logic2Layer[this->DAT_SomeTile] == 0) {
                                                this->GfxLayer[this->DAT_SomeTile]
                                                    = (short)GMTotalPicturesProcessed::instance[5] + 0x214
                                                    + (ushort)this->LuminesenceLayer[this->DAT_SomeTile] * 4
                                                    + (this->RandomLayer[this->DAT_SomeTile] & 3);
                                                for (local_14 = 0; local_14 < 7; local_14 = local_14 + 1) {
                                                    if (DAT_TerrainDefinedData::instance
                                                            .TerrainFlagGraphicLookup[local_14]
                                                            .unk1
                                                        == this->bitFlag) {
                                                        this->bitFlag = 0;
                                                        if ((*(uint*)(this->ptr_LogicLayer + this->DAT_SomeTile * 4 + 4)
                                                                & 0x200000)) {
                                                            this->bitFlag = 0x20;
                                                        }
                                                        if ((*(uint*)(this->ptr_LogicLayer + this->DAT_SomeTile * 4
                                                                 + -4)
                                                                & 0x200000)) {
                                                            this->bitFlag = this->bitFlag | 2;
                                                        }
                                                        if ((*(uint*)(this->ptr_LogicLayer
                                                                 + *(int*)(this->ptr_MovementDirectionTranslationMatrix
                                                                       + this->DAT_SomeY * 0x20)
                                                                     * 4
                                                                 + this->DAT_SomeTile * 4)
                                                                & 0x200000)) {
                                                            this->bitFlag = this->bitFlag | 0x80;
                                                        }
                                                        if ((*(uint*)(this->ptr_LogicLayer
                                                                 + *(int*)((int)(this->ptr_MovementDirectionTranslationMatrix
                                                                               + this->DAT_SomeY * 0x20)
                                                                       + 0x10)
                                                                     * 4
                                                                 + this->DAT_SomeTile * 4)
                                                                & 0x200000)) {
                                                            this->bitFlag = this->bitFlag | 8;
                                                        }
                                                        sVar4 = (short)GMTotalPicturesProcessed::instance[5];
                                                        if (local_14 < 4) {
                                                            if (!this->bitFlag) {
                                                                this->GfxLayer[this->DAT_SomeTile] = sVar4 + 0x234
                                                                    + (ushort)this->LuminesenceLayer[this->DAT_SomeTile]
                                                                        * 4
                                                                    + (ushort)DAT_TerrainDefinedData::instance
                                                                          .TerrainFlagGraphicLookup[local_14]
                                                                          .unk2;
                                                            } else {
                                                                this->GfxLayer[this->DAT_SomeTile] = sVar4 + 0x2dc
                                                                    + (ushort)this->LuminesenceLayer[this->DAT_SomeTile]
                                                                        * 4
                                                                    + (ushort)DAT_TerrainDefinedData::instance
                                                                          .TerrainFlagGraphicLookup[local_14]
                                                                          .unk2;
                                                            }
                                                        } else if (!this->bitFlag) {
                                                            if (local_14 == 4) {
                                                                this->GfxLayer[this->DAT_SomeTile] = sVar4 + 0x254
                                                                    + (ushort)this->LuminesenceLayer[this->DAT_SomeTile]
                                                                        * 4
                                                                    + (this->RandomLayer[this->DAT_SomeTile] & 3);
                                                            } else if (local_14 == 5) {
                                                                this->GfxLayer[this->DAT_SomeTile] = sVar4 + 0x274
                                                                    + (ushort)this->LuminesenceLayer[this->DAT_SomeTile]
                                                                        * 4
                                                                    + (this->RandomLayer[this->DAT_SomeTile] & 3);
                                                            } else if (local_14 == 6) {
                                                                this->GfxLayer[this->DAT_SomeTile] = sVar4 + 0x294
                                                                    + (ushort)this
                                                                          ->LuminesenceLayer[this->DAT_SomeTile];
                                                            }
                                                        }
                                                        break;
                                                    }
                                                }
                                            }
                                            if ((this->Logic2Layer[this->DAT_SomeTile] & 0x20)) {
                                                sVar4 = (this->WallGFXLayer[this->DAT_SomeTile] & 8) * 8 + 0x38d;
                                                sVar5 = (short)GMTotalPicturesProcessed::instance[5];
                                                if (!this->mapOrientation) {
                                                    this->GfxLayer[this->DAT_SomeTile] = sVar5 + sVar4 + -1
                                                        + (short)((int)(this->WallGFXLayer[this->DAT_SomeTile] & 0x3e0)
                                                              >> 5)
                                                            * 8;
                                                } else if (this->mapOrientation == 2) {
                                                    this->GfxLayer[this->DAT_SomeTile] = sVar5 + sVar4 + -1
                                                        + ((short)((int)(this->WallGFXLayer[this->DAT_SomeTile] & 0x3e0)
                                                               >> 5)
                                                                  - 2U
                                                              & 7)
                                                            * 8;
                                                } else if (this->mapOrientation == 4) {
                                                    this->GfxLayer[this->DAT_SomeTile] = sVar5 + sVar4 + -1
                                                        + ((short)((int)(this->WallGFXLayer[this->DAT_SomeTile] & 0x3e0)
                                                               >> 5)
                                                                  - 4U
                                                              & 7)
                                                            * 8;
                                                } else {
                                                    this->GfxLayer[this->DAT_SomeTile] = sVar5 + sVar4 + -1
                                                        + ((short)((int)(this->WallGFXLayer[this->DAT_SomeTile] & 0x3e0)
                                                               >> 5)
                                                                  - 6U
                                                              & 7)
                                                            * 8;
                                                }
                                            }
                                            sVar4 = (short)GMTotalPicturesProcessed::instance[5];
                                            if (!(this->Logic2Layer[this->DAT_SomeTile] & 0x50)) {
                                                if (!((int)(char)this->Logic2Layer[this->DAT_SomeTile] & 0x88U)) {
                                                    if (!(this->Logic2Layer[this->DAT_SomeTile] & 1)) {
                                                        if (!(this->Logic2Layer[this->DAT_SomeTile] & 2)) {
                                                            if ((this->Logic2Layer[this->DAT_SomeTile] & 4)) {
                                                                this->GfxLayer[this->DAT_SomeTile] = sVar4 + 0x41c;
                                                            }
                                                        } else {
                                                            this->GfxLayer[this->DAT_SomeTile] = sVar4 + 0x414;
                                                        }
                                                    } else {
                                                        this->GfxLayer[this->DAT_SomeTile] = sVar4 + 0x40c;
                                                    }
                                                } else {
                                                    bVar19 = 0;
                                                    if ((*(uint*)(this->ptr_LogicLayer + this->DAT_SomeTile * 4 + 4)
                                                            & 1)) {
                                                        bVar19 = 0x20;
                                                    }
                                                    if ((*(uint*)(this->ptr_LogicLayer + this->DAT_SomeTile * 4 + -4)
                                                            & 1)) {
                                                        bVar19 = bVar19 | 2;
                                                    }
                                                    puVar18 = (uint*)(this->ptr_LogicLayer
                                                        + *(int*)(this->ptr_MovementDirectionTranslationMatrix
                                                              + this->DAT_SomeY * 0x20)
                                                            * 4
                                                        + this->DAT_SomeTile * 4);
                                                    if ((puVar18[-1] & 1)) {
                                                        bVar19 = bVar19 | 1;
                                                    }
                                                    if ((puVar18[1] & 1)) {
                                                        bVar19 = bVar19 | 0x40;
                                                    }
                                                    if ((*puVar18 & 1)) {
                                                        bVar19 = bVar19 | 0x80;
                                                    }
                                                    puVar18 = (uint*)(this->ptr_LogicLayer
                                                        + *(int*)((int)(this->ptr_MovementDirectionTranslationMatrix
                                                                      + this->DAT_SomeY * 0x20)
                                                              + 0x10)
                                                            * 4
                                                        + this->DAT_SomeTile * 4);
                                                    if ((puVar18[-1] & 1)) {
                                                        bVar19 = bVar19 | 4;
                                                    }
                                                    if ((puVar18[1] & 1)) {
                                                        bVar19 = bVar19 | 0x10;
                                                    }
                                                    if ((*puVar18 & 1)) {
                                                        bVar19 = bVar19 | 8;
                                                    }
                                                    bVar16 = 0;
                                                    if ((*(uint*)(this->ptr_TerrainTypeTileMap + this->DAT_SomeTile + 1)
                                                            & 0x50)) {
                                                        bVar16 = 0x20;
                                                    }
                                                    if ((*(uint*)(this->ptr_TerrainTypeTileMap + this->DAT_SomeTile
                                                             + -1)
                                                            & 0x50)) {
                                                        bVar16 = bVar16 | 2;
                                                    }
                                                    puVar18 = (uint*)(this->ptr_TerrainTypeTileMap
                                                        + *(int*)(this->ptr_MovementDirectionTranslationMatrix
                                                            + this->DAT_SomeY * 0x20)
                                                        + this->DAT_SomeTile);
                                                    if ((*(uint*)((int)puVar18 + -1) & 0x50)) {
                                                        bVar16 = bVar16 | 1;
                                                    }
                                                    if ((*(uint*)((int)puVar18 + 1) & 0x50)) {
                                                        bVar16 = bVar16 | 0x40;
                                                    }
                                                    if ((*puVar18 & 0x50)) {
                                                        bVar16 = bVar16 | 0x80;
                                                    }
                                                    puVar18 = (uint*)(this->ptr_TerrainTypeTileMap
                                                        + *(int*)((int)(this->ptr_MovementDirectionTranslationMatrix
                                                                      + this->DAT_SomeY * 0x20)
                                                            + 0x10)
                                                        + this->DAT_SomeTile);
                                                    if ((*(uint*)((int)puVar18 + -1) & 0x50)) {
                                                        bVar16 = bVar16 | 4;
                                                    }
                                                    if ((*(uint*)((int)puVar18 + 1) & 0x50)) {
                                                        bVar16 = bVar16 | 0x10;
                                                    }
                                                    if ((*puVar18 & 0x50)) {
                                                        bVar16 = bVar16 | 8;
                                                    }
                                                    this->bitFlag = bVar16 | bVar19;
                                                    local_c0 = 0xffffffff;
                                                    if (!this->bitFlag) {
                                                        this->bitFlag = 0;
                                                        if ((*(uint*)(this->ptr_LogicLayer + this->DAT_SomeTile * 4 + 4)
                                                                & 0x100000)) {
                                                            this->bitFlag = 0x20;
                                                        }
                                                        if ((*(uint*)(this->ptr_LogicLayer + this->DAT_SomeTile * 4
                                                                 + -4)
                                                                & 0x100000)) {
                                                            this->bitFlag = this->bitFlag | 2;
                                                        }
                                                        puVar18 = (uint*)(this->ptr_LogicLayer
                                                            + *(int*)(this->ptr_MovementDirectionTranslationMatrix
                                                                  + this->DAT_SomeY * 0x20)
                                                                * 4
                                                            + this->DAT_SomeTile * 4);
                                                        if ((puVar18[-1] & 0x100000)) {
                                                            this->bitFlag = this->bitFlag | 1;
                                                        }
                                                        if ((puVar18[1] & 0x100000)) {
                                                            this->bitFlag = this->bitFlag | 0x40;
                                                        }
                                                        if ((*puVar18 & 0x100000)) {
                                                            this->bitFlag = this->bitFlag | 0x80;
                                                        }
                                                        puVar18 = (uint*)(this->ptr_LogicLayer
                                                            + *(int*)((int)(this->ptr_MovementDirectionTranslationMatrix
                                                                          + this->DAT_SomeY * 0x20)
                                                                  + 0x10)
                                                                * 4
                                                            + this->DAT_SomeTile * 4);
                                                        if ((puVar18[-1] & 0x100000)) {
                                                            this->bitFlag = this->bitFlag | 4;
                                                        }
                                                        if ((puVar18[1] & 0x100000)) {
                                                            this->bitFlag = this->bitFlag | 0x10;
                                                        }
                                                        if ((*puVar18 & 0x100000)) {
                                                            this->bitFlag = this->bitFlag | 8;
                                                        }
                                                        if (this->bitFlag) {
                                                            for (local_14 = 0; local_14 < 8; local_14 = local_14 + 1) {
                                                                if ((((uint)this->bitFlag
                                                                        & 1 << ((byte)local_14 & 0x1f)))
                                                                    && (this->HeightLayer[this->DAT_SomeTile
                                                                            + this->directionTranslationMatrix
                                                                                [this->DAT_SomeY]
                                                                                [DAT_TerrainDefinedData::instance
                                                                                        .field2475_0x370c[local_14]]]
                                                                        <= this->HeightLayer[this->DAT_SomeTile])) {
                                                                    this->bitFlag = this->bitFlag
                                                                        & ~(byte)(1 << ((byte)local_14 & 0x1f));
                                                                }
                                                            }
                                                            if (this->bitFlag) {
                                                                if (!(this->bitFlag & 0x80)) {
                                                                    if (!(this->bitFlag & 0x20)) {
                                                                        if (!(this->bitFlag & 8)) {
                                                                            if (!(this->bitFlag & 2)) {
                                                                                if (this->bitFlag == 0x41) {
                                                                                    local_c0 = 4;
                                                                                } else if (this->bitFlag == 0x50) {
                                                                                    local_c0 = 6;
                                                                                } else if (this->bitFlag == 0x14) {
                                                                                    local_c0 = 0;
                                                                                } else if (this->bitFlag == 5) {
                                                                                    local_c0 = 2;
                                                                                } else if (!(this->bitFlag & 0x40)) {
                                                                                    if (!(this->bitFlag & 1)) {
                                                                                        if (!(this->bitFlag & 4)) {
                                                                                            if ((this->bitFlag
                                                                                                    & 0x10)) {
                                                                                                local_c0 = 7;
                                                                                            }
                                                                                        } else {
                                                                                            local_c0 = 1;
                                                                                        }
                                                                                    } else {
                                                                                        local_c0 = 3;
                                                                                    }
                                                                                } else {
                                                                                    local_c0 = 5;
                                                                                }
                                                                            } else if (!(this->bitFlag & 0x80)) {
                                                                                if (!(this->bitFlag & 8)) {
                                                                                    if ((this->bitFlag & 5) == 5) {
                                                                                        local_c0 = 2;
                                                                                    } else {
                                                                                        local_c0 = 2;
                                                                                    }
                                                                                } else {
                                                                                    local_c0 = 1;
                                                                                }
                                                                            } else {
                                                                                local_c0 = 3;
                                                                            }
                                                                        } else if (!(this->bitFlag & 2)) {
                                                                            if (!(this->bitFlag & 0x20)) {
                                                                                if ((this->bitFlag & 0x14) == 0x14) {
                                                                                    local_c0 = 0;
                                                                                } else {
                                                                                    local_c0 = 0;
                                                                                }
                                                                            } else {
                                                                                local_c0 = 7;
                                                                            }
                                                                        } else {
                                                                            local_c0 = 1;
                                                                        }
                                                                    } else if (!(this->bitFlag & 8)) {
                                                                        if (!(this->bitFlag & 0x80)) {
                                                                            if ((this->bitFlag & 0x50) == 0x50) {
                                                                                local_c0 = 6;
                                                                            } else {
                                                                                local_c0 = 6;
                                                                            }
                                                                        } else {
                                                                            local_c0 = 5;
                                                                        }
                                                                    } else {
                                                                        local_c0 = 7;
                                                                    }
                                                                } else if (!(this->bitFlag & 0x20)) {
                                                                    if (!(this->bitFlag & 2)) {
                                                                        if ((this->bitFlag & 0x41) == 0x41) {
                                                                            local_c0 = 4;
                                                                        } else {
                                                                            local_c0 = 4;
                                                                        }
                                                                    } else {
                                                                        local_c0 = 3;
                                                                    }
                                                                } else {
                                                                    local_c0 = 5;
                                                                }
                                                                local_c0 = (local_c0 - this->mapOrientation) + 8
                                                                    & 0x80000007;
                                                                if ((int)local_c0 < 0) {
                                                                    local_c0 = (local_c0 - 1 | 0xfffffff8) + 1;
                                                                }
                                                                this->GfxLayer[this->DAT_SomeTile]
                                                                    = sVar4 + 0x30c + (short)(local_c0 << 4);
                                                            }
                                                        }
                                                        if (local_c0 == 0xffffffff) {
                                                            this->GfxLayer[this->DAT_SomeTile]
                                                                = (short)GMTotalPicturesProcessed::instance[5] + 0x214
                                                                + (ushort)this->LuminesenceLayer[this->DAT_SomeTile] * 4
                                                                + (this->RandomLayer[this->DAT_SomeTile] & 3);
                                                            this->Logic2Layer[this->DAT_SomeTile]
                                                                = this->Logic2Layer[this->DAT_SomeTile] & 0x7f;
                                                        }
                                                    } else {
                                                        if (!(this->bitFlag & 0x80)) {
                                                            if (!(this->bitFlag & 0x20)) {
                                                                if (!(this->bitFlag & 8)) {
                                                                    if (!(this->bitFlag & 2)) {
                                                                        if (this->bitFlag == 0x40) {
                                                                            local_c0 = 5;
                                                                        } else if (this->bitFlag == 1) {
                                                                            local_c0 = 3;
                                                                        } else if (this->bitFlag == 4) {
                                                                            local_c0 = 1;
                                                                        } else if (this->bitFlag == 0x10) {
                                                                            local_c0 = 7;
                                                                        } else if (this->bitFlag == 0x41) {
                                                                            local_c0 = 4;
                                                                        } else if (this->bitFlag == 0x50) {
                                                                            local_c0 = 6;
                                                                        } else if (this->bitFlag == 0x14) {
                                                                            local_c0 = 0;
                                                                        } else if (this->bitFlag == 5) {
                                                                            local_c0 = 2;
                                                                        }
                                                                    } else if (!(this->bitFlag & 0x80)) {
                                                                        if (!(this->bitFlag & 8)) {
                                                                            if ((this->bitFlag & 5) == 5) {
                                                                                local_c0 = 2;
                                                                            } else {
                                                                                local_c0 = 2;
                                                                            }
                                                                        } else {
                                                                            local_c0 = 1;
                                                                        }
                                                                    } else {
                                                                        local_c0 = 3;
                                                                    }
                                                                } else if (!(this->bitFlag & 2)) {
                                                                    if (!(this->bitFlag & 0x20)) {
                                                                        if ((this->bitFlag & 0x14) == 0x14) {
                                                                            local_c0 = 0;
                                                                        } else {
                                                                            local_c0 = 0;
                                                                        }
                                                                    } else {
                                                                        local_c0 = 7;
                                                                    }
                                                                } else {
                                                                    local_c0 = 1;
                                                                }
                                                            } else if (!(this->bitFlag & 8)) {
                                                                if (!(this->bitFlag & 0x80)) {
                                                                    if ((this->bitFlag & 0x50) == 0x50) {
                                                                        local_c0 = 6;
                                                                    } else {
                                                                        local_c0 = 6;
                                                                    }
                                                                } else {
                                                                    local_c0 = 5;
                                                                }
                                                            } else {
                                                                local_c0 = 7;
                                                            }
                                                        } else if (!(this->bitFlag & 0x20)) {
                                                            if (!(this->bitFlag & 2)) {
                                                                if ((this->bitFlag & 0x41) == 0x41) {
                                                                    local_c0 = 4;
                                                                } else {
                                                                    local_c0 = 4;
                                                                }
                                                            } else {
                                                                local_c0 = 3;
                                                            }
                                                        } else {
                                                            local_c0 = 5;
                                                        }
                                                        if (local_c0 == 0xffffffff) {
                                                            this->GfxLayer[this->DAT_SomeTile] = sVar4 + 0x214
                                                                + (ushort)this->LuminesenceLayer[this->DAT_SomeTile] * 4
                                                                + (this->RandomLayer[this->DAT_SomeTile] & 3);
                                                            this->Logic2Layer[this->DAT_SomeTile]
                                                                = this->Logic2Layer[this->DAT_SomeTile] & 0x7f;
                                                        } else {
                                                            uVar12 = (local_c0 - this->mapOrientation) + 8 & 0x80000007;
                                                            if ((int)uVar12 < 0) {
                                                                uVar12 = (uVar12 - 1 | 0xfffffff8) + 1;
                                                            }
                                                            this->GfxLayer[this->DAT_SomeTile]
                                                                = sVar4 + 0x30c + (short)(uVar12 << 4);
                                                        }
                                                    }
                                                }
                                            } else {
                                                this->GfxLayer[this->DAT_SomeTile] = sVar4 + 0x2fc;
                                            }
                                        }
                                    LAB_005109e8:
                                        if ((this->LogicLayer[this->DAT_SomeTile] & 0x10000100U)) {
                                            bVar19 = this->DefaultHeightLayer[this->DAT_SomeTile];
                                            iVar17 = MACRO_CALL_MEMBER(
                                                Map::TileMapState_Func::computeClimbRampRotation, this)(
                                                this->DAT_SomeTile, (uint)((int)(iVar17)),
                                                (uint)((int)(this->DAT_SomeY)));
                                            sVar5 = (short)GMTotalPicturesProcessed::instance[9];
                                            sVar4 = (short)this->wallCornerRotation;
                                            if (this->DefaultHeightLayer[this->DAT_SomeTile] < 0x88) {
                                                if (!iVar17) {
                                                    if (!(this->Logic2Layer[this->DAT_SomeTile] & 2)) {
                                                        this->PillarGFXLayer[this->DAT_SomeTile]
                                                            = (short)(((((int)(uint)bVar19 >> 3) + -1) * 0x40) / 2)
                                                            + (short)GMTotalPicturesProcessed::instance[3]
                                                            + (ushort)this->LuminesenceLayer[this->DAT_SomeTile] * 4
                                                            + (this->RandomLayer[this->DAT_SomeTile] & 3);
                                                    } else {
                                                        this->PillarGFXLayer[this->DAT_SomeTile] = sVar5 + -1 + sVar4;
                                                        this->MiscDisplayLayer[this->DAT_SomeTile]
                                                            = this->MiscDisplayLayer[this->DAT_SomeTile] | 0x800;
                                                    }
                                                } else {
                                                    this->PillarGFXLayer[this->DAT_SomeTile] = sVar5 + -1 + sVar4;
                                                    this->MiscDisplayLayer[this->DAT_SomeTile]
                                                        = this->MiscDisplayLayer[this->DAT_SomeTile] | 0x800;
                                                }
                                            } else {
                                                this->PillarGFXLayer[this->DAT_SomeTile] = sVar5 + -1 + sVar4;
                                                this->MiscDisplayLayer[this->DAT_SomeTile]
                                                    = this->MiscDisplayLayer[this->DAT_SomeTile] | 0x800;
                                            }
                                        }
                                    } else {
                                        this->Logic2Layer[this->DAT_SomeTile]
                                            = this->Logic2Layer[this->DAT_SomeTile] & 0xf7;
                                        this->bitFlag = 0;
                                        if ((*(uint*)(this->ptr_LogicLayer + this->DAT_SomeTile * 4 + 4) & 0x100000)) {
                                            this->bitFlag = 0x20;
                                        }
                                        if ((*(uint*)(this->ptr_LogicLayer + this->DAT_SomeTile * 4 + -4) & 0x100000)) {
                                            this->bitFlag = this->bitFlag | 2;
                                        }
                                        if ((*(uint*)(this->ptr_LogicLayer
                                                 + *(int*)(this->ptr_MovementDirectionTranslationMatrix
                                                       + this->DAT_SomeY * 0x20)
                                                     * 4
                                                 + this->DAT_SomeTile * 4)
                                                & 0x100000)) {
                                            this->bitFlag = this->bitFlag | 0x80;
                                        }
                                        if ((*(uint*)(this->ptr_LogicLayer
                                                 + *(int*)((int)(this->ptr_MovementDirectionTranslationMatrix
                                                               + this->DAT_SomeY * 0x20)
                                                       + 0x10)
                                                     * 4
                                                 + this->DAT_SomeTile * 4)
                                                & 0x100000)) {
                                            this->bitFlag = this->bitFlag | 8;
                                        }
                                        if (!this->bitFlag) {
                                            if (!(this->MiscDisplayLayer[this->DAT_SomeTile] & 0xc0)) {
                                                bVar19 = 0;
                                                if ((*(uint*)(this->ptr_MiscDisplayLayer + this->DAT_SomeTile * 2 + 2)
                                                        & 0x40)) {
                                                    bVar19 = 0x20;
                                                }
                                                if ((*(uint*)(this->ptr_MiscDisplayLayer + this->DAT_SomeTile * 2 + -2)
                                                        & 0x40)) {
                                                    bVar19 = bVar19 | 2;
                                                }
                                                puVar18 = (uint*)(this->ptr_MiscDisplayLayer
                                                    + *(int*)(this->ptr_MovementDirectionTranslationMatrix
                                                          + this->DAT_SomeY * 0x20)
                                                        * 2
                                                    + this->DAT_SomeTile * 2);
                                                if ((*(uint*)((int)puVar18 + -2) & 0x40)) {
                                                    bVar19 = bVar19 | 1;
                                                }
                                                if ((*(uint*)((int)puVar18 + 2) & 0x40)) {
                                                    bVar19 = bVar19 | 0x40;
                                                }
                                                if ((*puVar18 & 0x40)) {
                                                    bVar19 = bVar19 | 0x80;
                                                }
                                                bVar16 = 0;
                                                if ((*(uint*)(this->ptr_MiscDisplayLayer + this->DAT_SomeTile * 2 + 2)
                                                        & 0x80)) {
                                                    bVar16 = 0x20;
                                                }
                                                if ((*(uint*)(this->ptr_MiscDisplayLayer + this->DAT_SomeTile * 2 + -2)
                                                        & 0x80)) {
                                                    bVar16 = bVar16 | 2;
                                                }
                                                puVar18 = (uint*)(this->ptr_MiscDisplayLayer
                                                    + *(int*)(this->ptr_MovementDirectionTranslationMatrix
                                                          + this->DAT_SomeY * 0x20)
                                                        * 2
                                                    + this->DAT_SomeTile * 2);
                                                if ((*(uint*)((int)puVar18 + -2) & 0x80)) {
                                                    bVar16 = bVar16 | 1;
                                                }
                                                if ((*(uint*)((int)puVar18 + 2) & 0x80)) {
                                                    bVar16 = bVar16 | 0x40;
                                                }
                                                if ((*puVar18 & 0x80)) {
                                                    bVar16 = bVar16 | 0x80;
                                                }
                                                this->bitFlag = bVar16 & ~bVar19;
                                                if (this->bitFlag) {
                                                    this->GfxLayer[this->DAT_SomeTile]
                                                        = (short)GMTotalPicturesProcessed::instance[0xa6] + 0x5c4;
                                                    this->PillarGFXLayer[this->DAT_SomeTile]
                                                        = (ushort)GMTotalPicturesProcessed::instance[9];
                                                    this->MiscDisplayLayer[this->DAT_SomeTile]
                                                        = this->MiscDisplayLayer[this->DAT_SomeTile] | 0xc0;
                                                }
                                            }
                                            if (2 < this->LuminesenceLayer[this->DAT_SomeTile]) {
                                                this->MiscDisplayLayer[this->DAT_SomeTile]
                                                    = this->MiscDisplayLayer[this->DAT_SomeTile] & 0xffbf;
                                                this->MiscDisplayLayer[this->DAT_SomeTile]
                                                    = this->MiscDisplayLayer[this->DAT_SomeTile] & 0xff7f;
                                            }
                                            local_38 = this->LuminesenceLayer[this->DAT_SomeTile] - 2;
                                            if (local_38 < 0) {
                                                local_38 = 0;
                                            }
                                            sVar4 = (short)local_38;
                                            if (!(this->MiscDisplayLayer[this->DAT_SomeTile] & 0xc0)) {
                                                if (!(this->MiscDisplayLayer[this->DAT_SomeTile] & 0x100)) {
                                                    this->bitFlag = 0;
                                                    if ((*(uint*)(this->ptr_MiscDisplayLayer + this->DAT_SomeTile * 2
                                                             + 2)
                                                            & 0x100)) {
                                                        this->bitFlag = 0x20;
                                                    }
                                                    if ((*(uint*)(this->ptr_MiscDisplayLayer + this->DAT_SomeTile * 2
                                                             + -2)
                                                            & 0x100)) {
                                                        this->bitFlag = this->bitFlag | 2;
                                                    }
                                                    puVar18 = (uint*)(this->ptr_MiscDisplayLayer
                                                        + *(int*)(this->ptr_MovementDirectionTranslationMatrix
                                                              + this->DAT_SomeY * 0x20)
                                                            * 2
                                                        + this->DAT_SomeTile * 2);
                                                    if ((*(uint*)((int)puVar18 + -2) & 0x100)) {
                                                        this->bitFlag = this->bitFlag | 1;
                                                    }
                                                    if ((*(uint*)((int)puVar18 + 2) & 0x100)) {
                                                        this->bitFlag = this->bitFlag | 0x40;
                                                    }
                                                    if ((*puVar18 & 0x100)) {
                                                        this->bitFlag = this->bitFlag | 0x80;
                                                    }
                                                    puVar18 = (uint*)(this->ptr_MiscDisplayLayer
                                                        + *(int*)((int)(this->ptr_MovementDirectionTranslationMatrix
                                                                      + this->DAT_SomeY * 0x20)
                                                              + 0x10)
                                                            * 2
                                                        + this->DAT_SomeTile * 2);
                                                    if ((*(uint*)((int)puVar18 + -2) & 0x100)) {
                                                        this->bitFlag = this->bitFlag | 4;
                                                    }
                                                    if ((*(uint*)((int)puVar18 + 2) & 0x100)) {
                                                        this->bitFlag = this->bitFlag | 0x10;
                                                    }
                                                    if ((*puVar18 & 0x100)) {
                                                        this->bitFlag = this->bitFlag | 8;
                                                    }
                                                    if (this->bitFlag) {
                                                        local_ac = 2;
                                                        uVar12 = (uint)this->bitFlag
                                                            << ((byte)this->mapOrientation & 0x1f);
                                                        uVar12 = uVar12 & 0xff | (int)uVar12 >> 8;
                                                        switch (uVar12) {
                                                        case 1:
                                                            local_b0 = 0x1c;
                                                            break;
                                                        case 2:
                                                        case 3:
                                                        case 6:
                                                        case 7:
                                                            local_b0 = 0xc;
                                                            local_ac = 4;
                                                            break;
                                                        case 4:
                                                            local_b0 = 0x1a;
                                                            break;
                                                        default:
                                                            local_b4 = 0;
                                                            for (local_b8 = 0; local_b8 < 8; local_b8 = local_b8 + 1) {
                                                                if ((1 << ((byte)local_b8 & 0x1f) & uVar12)) {
                                                                    local_b4 = local_b4 + 1;
                                                                }
                                                            }
                                                            if (local_b4 < 4) {
                                                                local_b0 = 0x20;
                                                            } else {
                                                                local_b0 = 0x21;
                                                            }
                                                            local_ac = 1;
                                                            break;
                                                        case 8:
                                                        case 0xc:
                                                        case 0x18:
                                                        case 0x1c:
                                                            local_b0 = 8;
                                                            local_ac = 4;
                                                            break;
                                                        case 0xe:
                                                        case 0xf:
                                                        case 0x1e:
                                                        case 0x1f:
                                                            local_b0 = 0x16;
                                                            break;
                                                        case 0x10:
                                                            local_b0 = 0x18;
                                                            break;
                                                        case 0x20:
                                                        case 0x30:
                                                        case 0x60:
                                                        case 0x70:
                                                            local_b0 = 4;
                                                            local_ac = 4;
                                                            break;
                                                        case 0x38:
                                                        case 0x3c:
                                                        case 0x78:
                                                        case 0x7c:
                                                            local_b0 = 0x14;
                                                            break;
                                                        case 0x40:
                                                            local_b0 = 0x1e;
                                                            break;
                                                        case 0x80:
                                                        case 0x81:
                                                        case 0xc0:
                                                        case 0xc1:
                                                            local_b0 = 0;
                                                            local_ac = 4;
                                                            break;
                                                        case 0x83:
                                                        case 0x87:
                                                        case 0xc3:
                                                        case 199:
                                                            local_b0 = 0x10;
                                                            break;
                                                        case 0xe0:
                                                        case 0xe1:
                                                        case 0xf0:
                                                        case 0xf1:
                                                            local_b0 = 0x12;
                                                        }
                                                        this->GfxLayer[this->DAT_SomeTile]
                                                            = (short)GMTotalPicturesProcessed::instance[0xa6]
                                                            + (short)((int)(short)this->RandomLayer[this->DAT_SomeTile]
                                                                % local_ac)
                                                            + local_b0 + 8 + sVar4 * 0xf6;
                                                        this->MiscDisplayLayer[this->DAT_SomeTile]
                                                            = this->MiscDisplayLayer[this->DAT_SomeTile] | 0x200;
                                                    }
                                                } else {
                                                    local_94 = 2;
                                                    uVar15 = (int)this->CertainPathLayer[this->DAT_SomeTile] & 0xff;
                                                    uVar12 = uVar15 << ((byte)this->mapOrientation & 0x1f);
                                                    uVar12 = uVar12 & 0xff | (int)uVar12 >> 8;
                                                    switch (uVar12) {
                                                    case 1:
                                                        local_9c = 0x1c;
                                                        break;
                                                    case 2:
                                                    case 3:
                                                    case 6:
                                                    case 7:
                                                        local_9c = 0xc;
                                                        local_94 = 4;
                                                        break;
                                                    case 4:
                                                        local_9c = 0x1a;
                                                        break;
                                                    default:
                                                        local_a0 = 0;
                                                        for (local_a4 = 0; local_a4 < 8; local_a4 = local_a4 + 1) {
                                                            if ((1 << ((byte)local_a4 & 0x1f) & uVar12)) {
                                                                local_a0 = local_a0 + 1;
                                                            }
                                                        }
                                                        if (local_a0 < 4) {
                                                            local_9c = 0x20;
                                                        } else {
                                                            local_9c = 0x21;
                                                        }
                                                        local_94 = 1;
                                                        break;
                                                    case 8:
                                                    case 0xc:
                                                    case 0x18:
                                                    case 0x1c:
                                                        local_9c = 8;
                                                        local_94 = 4;
                                                        break;
                                                    case 0xe:
                                                    case 0xf:
                                                    case 0x1e:
                                                    case 0x1f:
                                                        local_9c = 0x16;
                                                        break;
                                                    case 0x10:
                                                        local_9c = 0x18;
                                                        break;
                                                    case 0x20:
                                                    case 0x30:
                                                    case 0x60:
                                                    case 0x70:
                                                        local_9c = 4;
                                                        local_94 = 4;
                                                        break;
                                                    case 0x38:
                                                    case 0x3c:
                                                    case 0x78:
                                                    case 0x7c:
                                                        local_9c = 0x14;
                                                        break;
                                                    case 0x40:
                                                        local_9c = 0x1e;
                                                        break;
                                                    case 0x80:
                                                    case 0x81:
                                                    case 0xc0:
                                                    case 0xc1:
                                                        local_9c = 0;
                                                        local_94 = 4;
                                                        break;
                                                    case 0x83:
                                                    case 0x87:
                                                    case 0xc3:
                                                    case 199:
                                                        local_9c = 0x10;
                                                        break;
                                                    case 0xe0:
                                                    case 0xe1:
                                                    case 0xf0:
                                                    case 0xf1:
                                                        local_9c = 0x12;
                                                    }
                                                    local_9c = (short)((int)(short)this->RandomLayer[this->DAT_SomeTile]
                                                                   % local_94)
                                                        + local_9c;
                                                    if (uVar15
                                                        != ((int)this->CertainPathLayer[this->DAT_SomeTile] >> 8
                                                            & 0xffU)) {
                                                        local_9c = local_9c + 0x66;
                                                    }
                                                    this->GfxLayer[this->DAT_SomeTile]
                                                        = (short)GMTotalPicturesProcessed::instance[0xa6] + local_9c
                                                        + 0x2a + sVar4 * 0xf6;
                                                }
                                            }
                                            if (!(this->MiscDisplayLayer[this->DAT_SomeTile] & 0x3c0)) {
                                                this->GfxLayer[this->DAT_SomeTile]
                                                    = (this->RandomLayer[this->DAT_SomeTile] & 7)
                                                    + (short)GMTotalPicturesProcessed::instance[0xa6] + sVar4 * 0xf6;
                                                this->PillarGFXLayer[this->DAT_SomeTile]
                                                    = (ushort)GMTotalPicturesProcessed::instance[9];
                                            }
                                        } else {
                                            this->GfxLayer[this->DAT_SomeTile]
                                                = (short)GMTotalPicturesProcessed::instance[5] + 0x2fc;
                                            this->Logic2Layer[this->DAT_SomeTile]
                                                = this->Logic2Layer[this->DAT_SomeTile] | 8;
                                        }
                                    }
                                }
                            LAB_0050c199:
                                this->DAT_SomeX = this->DAT_SomeX + 1;
                            }
                        }
                    }
                }
            }
        }
        return;
    }

}
}
