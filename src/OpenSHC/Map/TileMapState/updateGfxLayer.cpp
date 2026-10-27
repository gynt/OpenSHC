
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/TileMapState/NeighbourFlagsAsm.hpp"
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
#include "OpenSHC/Globals/GMFirstPictureIndex.hpp"

// masks for the handwritten neighbour-flag macro; MASM has no "|", so these must be literals
#define NEIGHBOUR_FLAGS_MASK_RIVER_OR_FORD 0x300000 // L_RIVER | L_FORD
#define NEIGHBOUR_FLAGS_MASK_WALL_OR_GATEHOUSE 0x100 // L_WALL_OR_GATEHOUSE

/* the original was built without optimisation: frame pointer, locals off ebp, sub esp, 0x118 */
#pragma optimize("", off)

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_BORDER;
    using OpenSHC::Map::LogicHelpers::L_BORDER_EDGE;
    using OpenSHC::Map::LogicHelpers::L_BOULDERS;
    using OpenSHC::Map::LogicHelpers::L_BUILDING;
    using OpenSHC::Map::LogicHelpers::L_DEFAULT_EARTH_OR_TEXTURE;
    using OpenSHC::Map::LogicHelpers::L_FARM_FIELD_APPLE;
    using OpenSHC::Map::LogicHelpers::L_FARM_FIELD_DAIRY;
    using OpenSHC::Map::LogicHelpers::L_FARM_FIELD_HOP;
    using OpenSHC::Map::LogicHelpers::L_FARM_FIELD_WHEAT;
    using OpenSHC::Map::LogicHelpers::L_FORD;
    using OpenSHC::Map::LogicHelpers::L_IRON;
    using OpenSHC::Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE;
    using OpenSHC::Map::LogicHelpers::L_MARSH;
    using OpenSHC::Map::LogicHelpers::L_MOAT;
    using OpenSHC::Map::LogicHelpers::L_OIL;
    using OpenSHC::Map::LogicHelpers::L_PEBBLES;
    using OpenSHC::Map::LogicHelpers::L_PLAIN2_AND_PITCH;
    using OpenSHC::Map::LogicHelpers::L_RIVER;
    using OpenSHC::Map::LogicHelpers::L_ROCKY;
    using OpenSHC::Map::LogicHelpers::L_SEA;
    using OpenSHC::Map::LogicHelpers::L_STAIRS;
    using OpenSHC::Map::LogicHelpers::L_STOCKPILE;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    using OpenSHC::Game::GameMode2;
    using OpenSHC::Map::Buildings::BuildingType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Restarted to delay deadcode elimination for space: ram
     */
    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00509180
    void TileMapState::updateGfxLayer()
    {

        OpenSHC::Map::Buildings::BuildingTypeShort BVar1;
        ushort uVar2;
        ushort uVar3;
        short sVar4;
        short sVar5;
        byte bVar6;
        byte bVar7;
        int sVar8;
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
        int local_c0; // signed: idiv at 0x50DDC3 / 0x50E2E2
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
        int local_48; // signed: idiv at 0x50AEC6
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
            local_c = DAT_PathFindingState::instance.dirtyMinY % 10;
            for (local_18 = this->dirtySectionRowMin; local_18 <= this->dirtySectionRowMax; local_18 = local_18 + 1) {
                for (local_10 = this->dirtySectionColMin; local_10 <= this->dirtySectionColMax; local_10 = local_10 + 1) {
                    if (*(char*)(local_18 * 0x28 + 0x1f93438 + local_10) != '\0') {
                        local_24 = local_c;
                        local_c = 0;
                        for (; local_24 < 10; local_24 = local_24 + 1) {
                            this->curTileY = local_18 * 10 + local_24;
                            this->curTileX = local_10 * 10;
                            for (local_30 = 0; local_30 < 10; local_30 = local_30 + 1) {
                                bVar9 = MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                                    DAT_ViewportRenderState::ptr)(this->curTileX, (uint)((int)(this->curTileY)));
                                if ((bVar9 != 0)
                                    && (this->curTileIndex = MACRO_CALL_MEMBER(
                                            OpenSHC::Rendering::ViewportRenderState_Func::translateXYToTile,
                                            DAT_ViewportRenderState::ptr)(this->curTileX, this->curTileY),
                                        this->ChangedLayer[this->curTileIndex] != 0)) {
                                    if (this->BuildingLayer[this->curTileIndex] == 0) {
                                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::computeTileLuminescence,
                                            this)(this->curTileIndex, this->curTileY);
                                        iVar17 = this->curTileX;
                                        this->FloatingLayer[this->curTileIndex] = 0;
                                        this->MiscDisplayLayer[this->curTileIndex]
                                            = this->MiscDisplayLayer[this->curTileIndex] & 0xfc3f;
                                        this->MiscDisplayLayer[this->curTileIndex]
                                            = this->MiscDisplayLayer[this->curTileIndex] & 0xf7ff;
                                        if ((this->LogicLayer[this->curTileIndex] & L_RIVER) == 0) {
                                            if ((this->LogicLayer[this->curTileIndex] & L_FORD) == 0) {
                                                if ((this->LogicLayer[this->curTileIndex] & L_FARM_FIELD_WHEAT) == 0) {
                                                    if ((this->LogicLayer[this->curTileIndex] & L_FARM_FIELD_HOP)
                                                        == 0) {
                                                        if ((this->LogicLayer[this->curTileIndex] & (L_FARM_FIELD_APPLE
                                                                | L_FARM_FIELD_DAIRY))
                                                            == 0) {
                                                            if ((((this->LogicLayer[this->curTileIndex]
                                                                          & (L_WALL_OR_GATEHOUSE
                                                                      | L_BUILDING | L_KEEP_NON_MANOR_HOUSE))
                                                                     == 0)
                                                                    && (this->BuildingWasLayer[this->curTileIndex]
                                                                        != '\0'))
                                                                && ((this->MiscDisplayLayer[this->curTileIndex] & 0x10)
                                                                    != 0)) {
                                                                local_44 = 0;
                                                                switch (this->BuildingWasLayer[this->curTileIndex]) {
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
                                                                if ((this->MiscDisplayLayer[this->curTileIndex]
                                                                        & 0x2000)
                                                                    == 0) {
                                                                    this->GfxLayer[this->curTileIndex]
                                                                        = (short)
                                                                              GMFirstPictureIndex::instance[0x95]
                                                                        + local_44 + 4
                                                                        + (this->RandomLayer[this->curTileIndex] & 7);
                                                                } else {
                                                                    this->GfxLayer[this->curTileIndex]
                                                                        = (short)
                                                                              GMFirstPictureIndex::instance[0x95]
                                                                        + local_44
                                                                        + (this->RandomLayer[this->curTileIndex] & 7);
                                                                }
                                                            } else if ((this->LogicLayer[this->curTileIndex]
                                                                           & L_WALL_OR_GATEHOUSE)
                                                                == 0) {
                                                                if ((this->LogicLayer[this->curTileIndex] & (L_SEA
                                                                        | L_ROCKY | L_WALL_OR_GATEHOUSE | L_BUILDING
                                                                        | L_BOULDERS | L_PEBBLES | L_IRON | L_RIVER
                                                                        | L_FARM_FIELD_WHEAT | L_FARM_FIELD_HOP
                                                                        | L_FARM_FIELD_APPLE | L_FARM_FIELD_DAIRY
                                                                        | L_KEEP_NON_MANOR_HOUSE | L_MARSH | L_OIL))
                                                                    == 0) {
                                                                    local_48 = 0;
                                                                    this->WallOwnerLayer[this->curTileIndex]
                                                                        = this->WallOwnerLayer[this->curTileIndex]
                                                                        & 0xf7;
                                                                    MACRO_NEIGHBOUR_FLAGS_LOGIC_8(
                                                                        wall, NEIGHBOUR_FLAGS_MASK_WALL_OR_GATEHOUSE)
                                                                    bVar19 = this->neighbourMask;
                                                                    MACRO_NEIGHBOUR_FLAGS_LOGIC_8(m1, 2)
                                                                    bVar19 = ~this->neighbourMask & bVar19;
                                                                    if (bVar19 != 0) {
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
                                                                        if (local_48 != 0) {
                                                                            MACRO_NEIGHBOUR_FLAGS_LOGIC_8(r1, 0x800)
                                                                            if (this->neighbourMask != 0) {
                                                                                local_48 = 0;
                                                                            }
                                                                        }
                                                                        if (local_48 != 0) {
                                                                            /* the corner picks its two cardinal
                                                                               neighbours and the diagonal between them
                                                                               (the decompiler lost these four arms:
                                                                               they are the jump table at 0x00510d94) */
                                                                            switch (local_48) {
                                                                            case 1:
                                                                                local_68 = this->curTileIndex
                                                                                    + this->directionTranslationMatrix
                                                                                          [this->curTileY][2];
                                                                                local_60 = this->curTileIndex
                                                                                    + this->directionTranslationMatrix
                                                                                          [this->curTileY][4];
                                                                                local_54 = this->curTileIndex
                                                                                    + this->directionTranslationMatrix
                                                                                          [this->curTileY][3];
                                                                                break;
                                                                            case 2:
                                                                                local_68 = this->curTileIndex
                                                                                    + this->directionTranslationMatrix
                                                                                          [this->curTileY][6];
                                                                                local_60 = this->curTileIndex
                                                                                    + this->directionTranslationMatrix
                                                                                          [this->curTileY][4];
                                                                                local_54 = this->curTileIndex
                                                                                    + this->directionTranslationMatrix
                                                                                          [this->curTileY][5];
                                                                                break;
                                                                            case 3:
                                                                                local_68 = this->curTileIndex
                                                                                    + this->directionTranslationMatrix
                                                                                          [this->curTileY][6];
                                                                                local_60 = this->curTileIndex
                                                                                    + this->directionTranslationMatrix
                                                                                          [this->curTileY][0];
                                                                                local_54 = this->curTileIndex
                                                                                    + this->directionTranslationMatrix
                                                                                          [this->curTileY][7];
                                                                                break;
                                                                            case 4:
                                                                                local_68 = this->curTileIndex
                                                                                    + this->directionTranslationMatrix
                                                                                          [this->curTileY][2];
                                                                                local_60 = this->curTileIndex
                                                                                    + this->directionTranslationMatrix
                                                                                          [this->curTileY][0];
                                                                                local_54 = this->curTileIndex
                                                                                    + this->directionTranslationMatrix
                                                                                          [this->curTileY][1];
                                                                                break;
                                                                            }
                                                                            bVar19 = this->HeightLayer[local_68];
                                                                            bVar16 = this->HeightLayer[local_60];
                                                                            bVar7 = this->HeightLayer[local_54];
                                                                            if ((this->LogicLayer[local_54] & 0x100U)
                                                                                == 0) {
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
                                                                            if (this->HeightLayer[this->curTileIndex]
                                                                                < bVar7) {
                                                                                this->WallGfxOrAnimCounterLayer[this->curTileIndex]
                                                                                    = (ushort)bVar7;
                                                                                if (((this->DamageOrCropStageLayer[local_68] != 0)
                                                                                        || (this->DamageOrCropStageLayer[local_60]
                                                                                            != 0))
                                                                                    || ((
                                                                                        this->DamageOrCropStageLayer[local_54] != 0
                                                                                        && ((this->LogicLayer[local_54]
                                                                                                & 0x100U)
                                                                                            != 0)))) {
                                                                                    this->WallOwnerLayer[this
                                                                                            ->curTileIndex]
                                                                                        = this->WallOwnerLayer[this
                                                                                                  ->curTileIndex]
                                                                                        | 8;
                                                                                }
                                                                            } else {
                                                                                local_48 = 0;
                                                                            }
                                                                            if (local_48 != 0) {
                                                                                uVar12 = ((local_48 + 3)
                                                                                             - this->mapOrientation / 2)
                                                                                    % 4;
                                                                                switch (uVar12) {
                                                                                case 0:
                                                                                    this->MiscDisplayLayer[this
                                                                                            ->curTileIndex]
                                                                                        = this->MiscDisplayLayer[this
                                                                                                  ->curTileIndex]
                                                                                        | 0x40;
                                                                                    this->overlayImageOrStockpileIdLayer[this
                                                                                            ->curTileIndex] = 0x2f;
                                                                                    break;
                                                                                case 1:
                                                                                    this->MiscDisplayLayer[this
                                                                                            ->curTileIndex]
                                                                                        = this->MiscDisplayLayer[this
                                                                                                  ->curTileIndex]
                                                                                        | 0x200;
                                                                                    this->overlayImageOrStockpileIdLayer[this
                                                                                            ->curTileIndex] = 0x2e;
                                                                                    break;
                                                                                case 2:
                                                                                    this->MiscDisplayLayer[this
                                                                                            ->curTileIndex]
                                                                                        = this->MiscDisplayLayer[this
                                                                                                  ->curTileIndex]
                                                                                        | 0x80;
                                                                                    this->overlayImageOrStockpileIdLayer[this
                                                                                            ->curTileIndex] = 0x31;
                                                                                    break;
                                                                                case 3:
                                                                                    this->MiscDisplayLayer[this
                                                                                            ->curTileIndex]
                                                                                        = this->MiscDisplayLayer[this
                                                                                                  ->curTileIndex]
                                                                                        | 0x100;
                                                                                    this->overlayImageOrStockpileIdLayer[this
                                                                                            ->curTileIndex] = 0x30;
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            } else {
                                                                this->tmpGfxVariant = MACRO_CALL_MEMBER(
                                                                    OpenSHC::Map::TileMapState_Func::
                                                                        computeWallCornerRenderRotation,
                                                                    this)(iVar17);
                                                                this->WallGfxOrAnimCounterLayer[this->curTileIndex]
                                                                    = (short)GMFirstPictureIndex::instance[10] + -1
                                                                    + (short)this->tmpGfxVariant;
                                                                sVar4 = (short)GMFirstPictureIndex::instance[0xc];
                                                                if (this->DamageOrCropStageLayer[this->curTileIndex] == 0) {
                                                                    if ((this->LogicLayer[this->curTileIndex] & 0x200U)
                                                                        == 0) {
                                                                        if ((this->LogicLayer[this->curTileIndex]
                                                                                & 0x800U)
                                                                            == 0) {
                                                                            if (this->LuminesenceLayer[this
                                                                                        ->curTileIndex]
                                                                                < 4) {
                                                                                this->GfxLayer[this->curTileIndex]
                                                                                    = sVar4 + 0x60
                                                                                    + (this->RandomLayer[this
                                                                                               ->curTileIndex]
                                                                                        & 7);
                                                                            } else {
                                                                                this->GfxLayer[this->curTileIndex]
                                                                                    = sVar4 + 0x68
                                                                                    + (this->RandomLayer[this
                                                                                               ->curTileIndex]
                                                                                        & 7);
                                                                            }
                                                                        } else {
                                                                            BVar11 = MACRO_CALL_MEMBER(
                                                                                OpenSHC::Map::TileMapState_Func::
                                                                                    hasHigherNeighborWithStairs,
                                                                                this)(
                                                                                this->curTileIndex, this->curTileY, 0);
                                                                            if (BVar11 == FALSE) {
                                                                                BVar11 = MACRO_CALL_MEMBER(
                                                                                    OpenSHC::Map::TileMapState_Func::
                                                                                        hasHigherNeighborWithStairs,
                                                                                    this)(this->curTileIndex,
                                                                                    this->curTileY, 2);
                                                                                if (BVar11 == FALSE) {
                                                                                    BVar11 = MACRO_CALL_MEMBER(
                                                                                        OpenSHC::Map::TileMapState_Func::
                                                                                            hasHigherNeighborWithStairs,
                                                                                        this)(this->curTileIndex,
                                                                                        this->curTileY, 4);
                                                                                    if (BVar11 == FALSE) {
                                                                                        BVar11 = MACRO_CALL_MEMBER(
                                                                                            OpenSHC::Map::TileMapState_Func::
                                                                                                hasHigherNeighborWithStairs,
                                                                                            this)(this->curTileIndex,
                                                                                            this->curTileY, 6);
                                                                                        if (BVar11 == FALSE) {
                                                                                            BVar11 = MACRO_CALL_MEMBER(
                                                                                                OpenSHC::Map::
                                                                                                    TileMapState_Func::
                                                                                                        hasHigherPlainNeighborWithWallOrGatehouse,
                                                                                                this)(
                                                                                                this->curTileIndex,
                                                                                                this->curTileY, 0);
                                                                                            if (BVar11 == FALSE) {
                                                                                                BVar11 = MACRO_CALL_MEMBER(
                                                                                                    OpenSHC::Map::
                                                                                                        TileMapState_Func::
                                                                                                            hasHigherPlainNeighborWithWallOrGatehouse,
                                                                                                    this)(
                                                                                                    this->curTileIndex,
                                                                                                    this->curTileY, 2);
                                                                                                if (BVar11 == FALSE) {
                                                                                                    BVar11 = MACRO_CALL_MEMBER(
                                                                                                        OpenSHC::Map::
                                                                                                            TileMapState_Func::
                                                                                                                hasHigherPlainNeighborWithWallOrGatehouse,
                                                                                                        this)(
                                                                                                        this->curTileIndex,
                                                                                                        this->curTileY,
                                                                                                        4);
                                                                                                    if (BVar11
                                                                                                        == FALSE) {
                                                                                                        BVar11 = MACRO_CALL_MEMBER(
                                                                                                            OpenSHC::Map::
                                                                                                                TileMapState_Func::
                                                                                                                    hasHigherPlainNeighborWithWallOrGatehouse,
                                                                                                            this)(
                                                                                                            this->curTileIndex,
                                                                                                            this->curTileY,
                                                                                                            6);
                                                                                                        if (BVar11
                                                                                                            == FALSE) {
                                                                                                            this->GfxLayer
                                                                                                                [this->curTileIndex]
                                                                                                                = (short)GMFirstPictureIndex::
                                                                                                                      instance
                                                                                                                          [0xc]
                                                                                                                + 0x68;
                                                                                                        } else {
                                                                                                            this->GfxLayer
                                                                                                                [this->curTileIndex]
                                                                                                                = (short)GMFirstPictureIndex::
                                                                                                                      instance
                                                                                                                          [0xc]
                                                                                                                + 0x85;
                                                                                                        }
                                                                                                    } else {
                                                                                                        this->GfxLayer
                                                                                                            [this->curTileIndex]
                                                                                                            = (short)GMFirstPictureIndex::
                                                                                                                  instance
                                                                                                                      [0xc]
                                                                                                            + 0x88;
                                                                                                    }
                                                                                                } else {
                                                                                                    this->GfxLayer[this
                                                                                                            ->curTileIndex]
                                                                                                        = (short)GMFirstPictureIndex::
                                                                                                              instance
                                                                                                                  [0xc]
                                                                                                        + 0x87;
                                                                                                }
                                                                                            } else {
                                                                                                this->GfxLayer[this
                                                                                                        ->curTileIndex]
                                                                                                    = (short)
                                                                                                          GMFirstPictureIndex::
                                                                                                              instance
                                                                                                                  [0xc]
                                                                                                    + 0x86;
                                                                                            }
                                                                                        } else {
                                                                                            this->GfxLayer[this
                                                                                                    ->curTileIndex]
                                                                                                = (short)
                                                                                                      GMFirstPictureIndex::
                                                                                                          instance[0xc]
                                                                                                + 0x85;
                                                                                        }
                                                                                    } else {
                                                                                        this->GfxLayer[this
                                                                                                ->curTileIndex]
                                                                                            = (short)
                                                                                                  GMFirstPictureIndex::
                                                                                                      instance[0xc]
                                                                                            + 0x88;
                                                                                    }
                                                                                } else {
                                                                                    this->GfxLayer[this->curTileIndex]
                                                                                        = (short)
                                                                                              GMFirstPictureIndex::
                                                                                                  instance[0xc]
                                                                                        + 0x87;
                                                                                }
                                                                            } else {
                                                                                this->GfxLayer[this->curTileIndex]
                                                                                    = (short)GMFirstPictureIndex::
                                                                                          instance[0xc]
                                                                                    + 0x86;
                                                                            }
                                                                        }
                                                                    } else {
                                                                        BVar11 = MACRO_CALL_MEMBER(
                                                                            OpenSHC::Map::TileMapState_Func::
                                                                                isWallCornerForCardinalDirection,
                                                                            this)(
                                                                            this->curTileIndex, this->curTileY, 0);
                                                                        if (BVar11 == FALSE) {
                                                                            BVar11 = MACRO_CALL_MEMBER(
                                                                                OpenSHC::Map::TileMapState_Func::
                                                                                    isWallCornerForCardinalDirection,
                                                                                this)(
                                                                                this->curTileIndex, this->curTileY, 2);
                                                                            if (BVar11 == FALSE) {
                                                                                uVar12 = MACRO_CALL_MEMBER(
                                                                                    OpenSHC::Map::TileMapState_Func::
                                                                                        isWallCornerForDiagonalDirection,
                                                                                    this)(this->curTileIndex,
                                                                                    this->curTileY, 1);
                                                                                if (uVar12 == 0) {
                                                                                    uVar12 = MACRO_CALL_MEMBER(
                                                                                        OpenSHC::Map::TileMapState_Func::
                                                                                            isWallCornerForDiagonalDirection,
                                                                                        this)(this->curTileIndex,
                                                                                        this->curTileY, 3);
                                                                                    if (uVar12 == 0) {
                                                                                        uVar12 = MACRO_CALL_MEMBER(
                                                                                            OpenSHC::Map::TileMapState_Func::
                                                                                                isWallCornerForDiagonalDirection,
                                                                                            this)(this->curTileIndex,
                                                                                            this->curTileY, 5);
                                                                                        if (uVar12 == 0) {
                                                                                            uVar12 = MACRO_CALL_MEMBER(
                                                                                                OpenSHC::Map::
                                                                                                    TileMapState_Func::
                                                                                                        isWallCornerForDiagonalDirection,
                                                                                                this)(
                                                                                                this->curTileIndex,
                                                                                                this->curTileY, 7);
                                                                                            sVar4 = (short)
                                                                                                GMFirstPictureIndex::
                                                                                                    instance[0xc];
                                                                                            if (uVar12 == 0) {
                                                                                                this->GfxLayer[this
                                                                                                        ->curTileIndex]
                                                                                                    = sVar4 + 0x84;
                                                                                                this->LogicLayer[this
                                                                                                        ->curTileIndex]
                                                                                                    = this->LogicLayer
                                                                                                          [this->curTileIndex]
                                                                                                    | 0x400000;
                                                                                            } else {
                                                                                                if (this->mapOrientation
                                                                                                    == 0) {
                                                                                                    this->GfxLayer[this
                                                                                                            ->curTileIndex]
                                                                                                        = sVar4 + 0x81;
                                                                                                } else if (
                                                                                                    this->mapOrientation
                                                                                                    == 2) {
                                                                                                    this->GfxLayer[this
                                                                                                            ->curTileIndex]
                                                                                                        = sVar4 + 0x80;
                                                                                                } else if (
                                                                                                    this->mapOrientation
                                                                                                    == 4) {
                                                                                                    this->GfxLayer[this
                                                                                                            ->curTileIndex]
                                                                                                        = sVar4 + 0x83;
                                                                                                } else if (
                                                                                                    this->mapOrientation
                                                                                                    == 6) {
                                                                                                    this->GfxLayer[this
                                                                                                            ->curTileIndex]
                                                                                                        = sVar4 + 0x82;
                                                                                                }
                                                                                                this->LogicLayer[this
                                                                                                        ->curTileIndex]
                                                                                                    = this->LogicLayer
                                                                                                          [this->curTileIndex]
                                                                                                    | 0x400000;
                                                                                            }
                                                                                        } else {
                                                                                            sVar4 = (short)
                                                                                                GMFirstPictureIndex::
                                                                                                    instance[0xc];
                                                                                            if (this->mapOrientation
                                                                                                == 0) {
                                                                                                this->GfxLayer[this
                                                                                                        ->curTileIndex]
                                                                                                    = sVar4 + 0x80;
                                                                                            } else if (
                                                                                                this->mapOrientation
                                                                                                == 2) {
                                                                                                this->GfxLayer[this
                                                                                                        ->curTileIndex]
                                                                                                    = sVar4 + 0x83;
                                                                                            } else if (
                                                                                                this->mapOrientation
                                                                                                == 4) {
                                                                                                this->GfxLayer[this
                                                                                                        ->curTileIndex]
                                                                                                    = sVar4 + 0x82;
                                                                                            } else if (
                                                                                                this->mapOrientation
                                                                                                == 6) {
                                                                                                this->GfxLayer[this
                                                                                                        ->curTileIndex]
                                                                                                    = sVar4 + 0x81;
                                                                                            }
                                                                                            this->LogicLayer[this
                                                                                                    ->curTileIndex]
                                                                                                = this->LogicLayer[this
                                                                                                          ->curTileIndex]
                                                                                                | 0x400000;
                                                                                        }
                                                                                    } else {
                                                                                        sVar4 = (short)
                                                                                            GMFirstPictureIndex::
                                                                                                instance[0xc];
                                                                                        if (this->mapOrientation == 0) {
                                                                                            this->GfxLayer[this
                                                                                                    ->curTileIndex]
                                                                                                = sVar4 + 0x83;
                                                                                        } else if (this->mapOrientation
                                                                                            == 2) {
                                                                                            this->GfxLayer[this
                                                                                                    ->curTileIndex]
                                                                                                = sVar4 + 0x82;
                                                                                        } else if (this->mapOrientation
                                                                                            == 4) {
                                                                                            this->GfxLayer[this
                                                                                                    ->curTileIndex]
                                                                                                = sVar4 + 0x81;
                                                                                        } else if (this->mapOrientation
                                                                                            == 6) {
                                                                                            this->GfxLayer[this
                                                                                                    ->curTileIndex]
                                                                                                = sVar4 + 0x80;
                                                                                        }
                                                                                        this->LogicLayer[this
                                                                                                ->curTileIndex]
                                                                                            = this->LogicLayer[this
                                                                                                      ->curTileIndex]
                                                                                            | 0x400000;
                                                                                    }
                                                                                } else {
                                                                                    sVar4 = (short)
                                                                                        GMFirstPictureIndex::
                                                                                            instance[0xc];
                                                                                    if (this->mapOrientation == 0) {
                                                                                        this->GfxLayer[this
                                                                                                ->curTileIndex]
                                                                                            = sVar4 + 0x82;
                                                                                    } else if (this->mapOrientation
                                                                                        == 2) {
                                                                                        this->GfxLayer[this
                                                                                                ->curTileIndex]
                                                                                            = sVar4 + 0x81;
                                                                                    } else if (this->mapOrientation
                                                                                        == 4) {
                                                                                        this->GfxLayer[this
                                                                                                ->curTileIndex]
                                                                                            = sVar4 + 0x80;
                                                                                    } else if (this->mapOrientation
                                                                                        == 6) {
                                                                                        this->GfxLayer[this
                                                                                                ->curTileIndex]
                                                                                            = sVar4 + 0x83;
                                                                                    }
                                                                                    this->LogicLayer[this->curTileIndex]
                                                                                        = this->LogicLayer[this
                                                                                                  ->curTileIndex]
                                                                                        | 0x400000;
                                                                                }
                                                                            } else {
                                                                                sVar4
                                                                                    = (short)GMFirstPictureIndex::
                                                                                        instance[0xc];
                                                                                if ((this->mapOrientation == 0)
                                                                                    || (this->mapOrientation == 4)) {
                                                                                    if ((this->LogicLayer[this
                                                                                                 ->curTileIndex]
                                                                                            & 0x400000U)
                                                                                        == 0) {
                                                                                        this->GfxLayer[this
                                                                                                ->curTileIndex] = sVar4
                                                                                            + 0x70
                                                                                            + (this->RandomLayer[this
                                                                                                       ->curTileIndex]
                                                                                                & 3);
                                                                                    } else {
                                                                                        this->GfxLayer[this
                                                                                                ->curTileIndex] = sVar4
                                                                                            + 0x78
                                                                                            + (this->RandomLayer[this
                                                                                                       ->curTileIndex]
                                                                                                & 3);
                                                                                    }
                                                                                } else if ((this->LogicLayer[this
                                                                                                    ->curTileIndex]
                                                                                               & 0x400000U)
                                                                                    == 0) {
                                                                                    this->GfxLayer[this->curTileIndex]
                                                                                        = sVar4 + 0x74
                                                                                        + (this->RandomLayer[this
                                                                                                   ->curTileIndex]
                                                                                            & 3);
                                                                                } else {
                                                                                    this->GfxLayer[this->curTileIndex]
                                                                                        = sVar4 + 0x7c
                                                                                        + (this->RandomLayer[this
                                                                                                   ->curTileIndex]
                                                                                            & 3);
                                                                                }
                                                                            }
                                                                        } else {
                                                                            sVar4 = (short)
                                                                                GMFirstPictureIndex::instance[0xc];
                                                                            if ((this->mapOrientation == 0)
                                                                                || (this->mapOrientation == 4)) {
                                                                                if ((this->LogicLayer[this
                                                                                             ->curTileIndex]
                                                                                        & 0x400000U)
                                                                                    == 0) {
                                                                                    this->GfxLayer[this->curTileIndex]
                                                                                        = sVar4 + 0x74
                                                                                        + (this->RandomLayer[this
                                                                                                   ->curTileIndex]
                                                                                            & 3);
                                                                                } else {
                                                                                    this->GfxLayer[this->curTileIndex]
                                                                                        = sVar4 + 0x7c
                                                                                        + (this->RandomLayer[this
                                                                                                   ->curTileIndex]
                                                                                            & 3);
                                                                                }
                                                                            } else if ((this->LogicLayer[this
                                                                                                ->curTileIndex]
                                                                                           & 0x400000U)
                                                                                == 0) {
                                                                                this->GfxLayer[this->curTileIndex]
                                                                                    = sVar4 + 0x70
                                                                                    + (this->RandomLayer[this
                                                                                               ->curTileIndex]
                                                                                        & 3);
                                                                            } else {
                                                                                this->GfxLayer[this->curTileIndex]
                                                                                    = sVar4 + 0x78
                                                                                    + (this->RandomLayer[this
                                                                                               ->curTileIndex]
                                                                                        & 3);
                                                                            }
                                                                        }
                                                                    }
                                                                } else {
                                                                    this->GfxLayer[this->curTileIndex] = sVar4 + 0x8a
                                                                        + (this->RandomLayer[this->curTileIndex] & 7);
                                                                }
                                                            }
                                                        }
                                                    } else {
                                                        MACRO_CALL_MEMBER(
                                                            OpenSHC::Map::TileMapState_Func::computeClimbRampRotation,
                                                            this)(this->curTileIndex, (uint)((int)(iVar17)),
                                                            (uint)((int)(this->curTileY)));
                                                        this->PillarGFXLayer[this->curTileIndex]
                                                            = (short)GMFirstPictureIndex::instance[9] + -1
                                                            + (short)this->tmpGfxVariant;
                                                        this->MiscDisplayLayer[this->curTileIndex]
                                                            = this->MiscDisplayLayer[this->curTileIndex] | 0x800;
                                                        this->GfxLayer[this->curTileIndex]
                                                            = (short)GMFirstPictureIndex::instance[0xe] + 0x25
                                                            + (this->RandomLayer[this->curTileIndex] & 1) * 9;
                                                        DAT_BuildingsState::instance.farmFieldGfxFullRefresh = 1;
                                                    }
                                                } else {
                                                    MACRO_CALL_MEMBER(
                                                        OpenSHC::Map::TileMapState_Func::computeClimbRampRotation,
                                                        this)(this->curTileIndex, (uint)((int)(iVar17)),
                                                        (uint)((int)(this->curTileY)));
                                                    this->PillarGFXLayer[this->curTileIndex]
                                                        = (short)GMFirstPictureIndex::instance[9] + -1
                                                        + (short)this->tmpGfxVariant;
                                                    this->MiscDisplayLayer[this->curTileIndex]
                                                        = this->MiscDisplayLayer[this->curTileIndex] | 0x800;
                                                    this->GfxLayer[this->curTileIndex]
                                                        = (this->RandomLayer[this->curTileIndex] & 3)
                                                        + (short)GMFirstPictureIndex::instance[0xe];
                                                    DAT_BuildingsState::instance.farmFieldGfxFullRefresh = 1;
                                                }
                                            } else {
                                                BVar11 = MACRO_CALL_MEMBER(
                                                    OpenSHC::Map::TileMapState_Func::isTileHigherThanAnyNeighbour,
                                                    this)(this->curTileIndex, (uint)((int)(iVar17)),
                                                    (uint)((int)(this->curTileY)));
                                                if (BVar11 == FALSE) {
                                                    this->PillarGFXLayer[this->curTileIndex] = 0x20;
                                                } else {
                                                    this->PillarGFXLayer[this->curTileIndex]
                                                        = (this->RandomLayer[this->curTileIndex] & 0xf) + 0x23;
                                                }
                                                this->GfxLayer[this->curTileIndex]
                                                    = (short)GMFirstPictureIndex::instance[5] + 0x29c;
                                            }
                                        } else {
                                            BVar11 = MACRO_CALL_MEMBER(
                                                OpenSHC::Map::TileMapState_Func::isTileHigherThanAnyNeighbour, this)(
                                                this->curTileIndex, (uint)((int)(iVar17)),
                                                (uint)((int)(this->curTileY)));
                                            if (BVar11 == FALSE) {
                                                this->PillarGFXLayer[this->curTileIndex] = 0x20;
                                            } else {
                                                this->PillarGFXLayer[this->curTileIndex]
                                                    = (this->RandomLayer[this->curTileIndex] & 0xf) + 0x23;
                                            }
                                            this->GfxLayer[this->curTileIndex]
                                                = (short)GMFirstPictureIndex::instance[5] + 0x214;
                                        }
                                    } else if (DAT_BuildingsState::instance
                                                   .buildings[this->BuildingLayer[this->curTileIndex]]
                                                   .buildingType
                                        == OpenSHC::Map::Buildings::BT_DRAWBRIDGE) {
                                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::computeTileLuminescence,
                                            this)(this->curTileIndex, this->curTileY);
                                    }
                                }
                                this->curTileX = this->curTileX + 1;
                            }
                        }
                    }
                }
            }
            local_c = DAT_PathFindingState::instance.dirtyMinY % 10;
            for (local_18 = this->dirtySectionRowMin; local_18 <= this->dirtySectionRowMax; local_18 = local_18 + 1) {
                for (local_10 = this->dirtySectionColMin; local_10 <= this->dirtySectionColMax; local_10 = local_10 + 1) {
                    if (*(char*)(local_18 * 0x28 + 0x1f93438 + local_10) != '\0') {
                        local_24 = local_c;
                        local_c = 0;
                        for (; local_24 < 10; local_24 = local_24 + 1) {
                            this->curTileY = local_18 * 10 + local_24;
                            this->curTileX = local_10 * 10;
                            for (local_30 = 0; local_30 < 10; local_30 = local_30 + 1) {
                                BVar11 = MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                                    DAT_ViewportRenderState::ptr)(this->curTileX, (uint)((int)(this->curTileY)));
                                if ((((BVar11 != FALSE)
                                         && (this->curTileIndex = MACRO_CALL_MEMBER(
                                                 OpenSHC::Rendering::ViewportRenderState_Func::translateXYToTile,
                                                 DAT_ViewportRenderState::ptr)(this->curTileX, this->curTileY),
                                             (this->LogicLayer[this->curTileIndex] & 0x100201U) != 0))
                                        && (this->ChangedLayer[this->curTileIndex] != 0))
                                    && ((this->BuildingLayer[this->curTileIndex] == 0
                                        && ((this->LogicLayer[this->curTileIndex] & 0x10000030U) == 0)))) {
                                    if ((this->LogicLayer[this->curTileIndex] & 1U) == 0) {
                                        if ((this->LogicLayer[this->curTileIndex] & 0x100000U) != 0) {
                                            MACRO_CALL_MEMBER(
                                                OpenSHC::Map::TileMapState_Func::computeTileCliffEdgeFlags, this)(
                                                this->curTileIndex, this->curTileX, this->curTileY);
                                        }
                                    } else {
                                        this->MiscDisplayLayer[this->curTileIndex]
                                            = this->MiscDisplayLayer[this->curTileIndex] & 0xfffc;
                                        iVar17 = this->curTileIndex
                                            + this->directionTranslationMatrix[this->curTileY][this->mapOrientation];
                                        this->tmpNeighbourHeight = (ushort)this->HeightLayer[iVar17];
                                        if ((this->LogicLayer[iVar17] & 1U) != 0) {
                                            this->tmpNeighbourHeight = 0;
                                        }
                                        if ((this->LogicLayer[iVar17] & 0x80U) != 0) {
                                            this->tmpNeighbourHeight = 0x14;
                                        }
                                        if (0x13 < this->tmpNeighbourHeight) {
                                            sVar4 = (short)GMFirstPictureIndex::instance[0xa6];
                                            if (this->tmpNeighbourHeight < 0x5b) {
                                                if (this->tmpNeighbourHeight < 0x29) {
                                                    this->GfxLayer[this->curTileIndex] = sVar4 + 0x5dc;
                                                } else {
                                                    this->GfxLayer[this->curTileIndex] = sVar4 + 0x5e2;
                                                }
                                            } else {
                                                this->GfxLayer[this->curTileIndex] = sVar4 + 0x5ee;
                                            }
                                            this->PillarGFXLayer[this->curTileIndex]
                                                = (ushort)GMFirstPictureIndex::instance[9];
                                            this->MiscDisplayLayer[this->curTileIndex]
                                                = this->MiscDisplayLayer[this->curTileIndex] | 0x40;
                                        }
                                        local_74 = 0;
                                        this->neighbourMask = 0;
                                        for (local_70 = 0; local_70 < 8; local_70 = local_70 + 1) {
                                            iVar17 = this->curTileIndex
                                                + this->directionTranslationMatrix[this->curTileY][local_70];
                                            if (this->HeightLayer[iVar17] < 0x14) {
                                                if ((this->LogicLayer[iVar17] & 0x100031U) == 0) {
                                                    this->neighbourMask
                                                        = this->neighbourMask | (byte)(0x80 >> ((byte)local_70 & 0x1f));
                                                }
                                                if (((this->LogicLayer[iVar17] & 0x100001U) == 0)
                                                    && ((this->Logic2Layer[iVar17] & 0x20) != 0)) {
                                                    local_74 = 0x80 >> ((byte)local_70 & 0x1f) | local_74;
                                                }
                                            }
                                        }
                                        if (this->neighbourMask != 0) {
                                            this->MiscDisplayLayer[this->curTileIndex]
                                                = this->MiscDisplayLayer[this->curTileIndex] | 0x100;
                                            this->SearchDistanceLayer[this->curTileIndex]
                                                = (ushort)this->neighbourMask | (ushort)(local_74 << 8);
                                        }
                                    }
                                    if ((this->LogicLayer[this->curTileIndex] & 0x200U) != 0) {
                                        uVar12 = (this->viewDirFront + 7) % 8;
                                        iVar17 = this->curTileIndex
                                            + this->directionTranslationMatrix[this->curTileY][uVar12];
                                        uVar12 = (this->viewDirFront + 1) % 8;
                                        iVar13 = this->curTileIndex
                                            + this->directionTranslationMatrix[this->curTileY][uVar12];
                                        if (((((this->LogicLayer[iVar17] | this->LogicLayer[iVar13]) & 1U) == 0)
                                                && ((this->MiscDisplayLayer[iVar17] & 0x3c0) != 0))
                                            && ((this->MiscDisplayLayer[iVar13] & 0x3c0) != 0)) {
                                            if (this->LuminesenceLayer[this->curTileIndex] < 4) {
                                                this->GfxLayer[this->curTileIndex]
                                                    = (short)GMFirstPictureIndex::instance[0xc] + 0x60
                                                    + (this->RandomLayer[this->curTileIndex] & 7);
                                            } else {
                                                this->GfxLayer[this->curTileIndex]
                                                    = (short)GMFirstPictureIndex::instance[0xc] + 0x68
                                                    + (this->RandomLayer[this->curTileIndex] & 7);
                                            }
                                        }
                                        uVar12 = (this->viewDirFront + 1) % 8;
                                        iVar17 = this->curTileIndex
                                            + this->directionTranslationMatrix[this->curTileY][uVar12];
                                        uVar12 = (this->viewDirFront + 3) % 8;
                                        iVar13 = this->curTileIndex
                                            + this->directionTranslationMatrix[this->curTileY][uVar12];
                                        if (((((this->LogicLayer[iVar17] | this->LogicLayer[iVar13]) & 1U) == 0)
                                                && ((this->MiscDisplayLayer[iVar17] & 0x3c0) != 0))
                                            && ((this->MiscDisplayLayer[iVar13] & 0x3c0) != 0)) {
                                            if ((this->curTileY & 1U) == 0) {
                                                this->GfxLayer[this->curTileIndex]
                                                    = (short)GMFirstPictureIndex::instance[0xc] + 0x138;
                                            } else {
                                                this->GfxLayer[this->curTileIndex]
                                                    = (short)GMFirstPictureIndex::instance[0xc] + 0x137;
                                            }
                                            this->MiscDisplayLayer[this->curTileIndex]
                                                = this->MiscDisplayLayer[this->curTileIndex] | 0x3c0;
                                        }
                                        uVar12 = (this->viewDirFront + 5) % 8;
                                        iVar17 = this->curTileIndex
                                            + this->directionTranslationMatrix[this->curTileY][uVar12];
                                        uVar12 = (this->viewDirFront + 7) % 8;
                                        iVar13 = this->curTileIndex
                                            + this->directionTranslationMatrix[this->curTileY][uVar12];
                                        if (((((this->LogicLayer[iVar17] | this->LogicLayer[iVar13]) & 1U) == 0)
                                                && ((this->MiscDisplayLayer[iVar17] & 0x3c0) != 0))
                                            && ((this->MiscDisplayLayer[iVar13] & 0x3c0) != 0)) {
                                            if ((this->curTileY & 1U) == 0) {
                                                this->GfxLayer[this->curTileIndex]
                                                    = (short)GMFirstPictureIndex::instance[0xc] + 0x13a;
                                            } else {
                                                this->GfxLayer[this->curTileIndex]
                                                    = (short)GMFirstPictureIndex::instance[0xc] + 0x139;
                                            }
                                            this->MiscDisplayLayer[this->curTileIndex]
                                                = this->MiscDisplayLayer[this->curTileIndex] | 0x3c0;
                                        }
                                        uVar12 = (this->viewDirFront + 3) % 8;
                                        iVar17 = this->curTileIndex
                                            + this->directionTranslationMatrix[this->curTileY][uVar12];
                                        uVar12 = (this->viewDirFront + 5) % 8;
                                        iVar13 = this->curTileIndex
                                            + this->directionTranslationMatrix[this->curTileY][uVar12];
                                        if (((((this->LogicLayer[iVar17] | this->LogicLayer[iVar13]) & 1U) == 0)
                                                && ((this->MiscDisplayLayer[iVar17] & 0x3c0) != 0))
                                            && ((this->MiscDisplayLayer[iVar13] & 0x3c0) != 0)) {
                                            uVar12 = (int)this->curTileY % 8;
                                            this->GfxLayer[this->curTileIndex]
                                                = (short)GMFirstPictureIndex::instance[0xc] + 0x12f
                                                + (short)uVar12;
                                            this->MiscDisplayLayer[this->curTileIndex]
                                                = this->MiscDisplayLayer[this->curTileIndex] | 0x3c0;
                                        }
                                    }
                                }
                                this->curTileX = this->curTileX + 1;
                            }
                        }
                    }
                }
            }
            local_c = DAT_PathFindingState::instance.dirtyMinY % 10;
            for (local_18 = this->dirtySectionRowMin; local_18 <= this->dirtySectionRowMax; local_18 = local_18 + 1) {
                for (local_10 = this->dirtySectionColMin; local_10 <= this->dirtySectionColMax; local_10 = local_10 + 1) {
                    if (*(char*)(local_18 * 0x28 + 0x1f93438 + local_10) != '\0') {
                        local_24 = local_c;
                        local_c = 0;
                        for (; local_24 < 10; local_24 = local_24 + 1) {
                            this->curTileY = local_18 * 10 + local_24;
                            this->curTileX = local_10 * 10;
                            for (local_30 = 0; local_30 < 10; local_30 = local_30 + 1) {
                                BVar11 = MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                                    DAT_ViewportRenderState::ptr)(this->curTileX, (uint)((int)(this->curTileY)));
                                if (((BVar11 != FALSE)
                                        && (this->curTileIndex = MACRO_CALL_MEMBER(
                                                OpenSHC::Rendering::ViewportRenderState_Func::translateXYToTile,
                                                DAT_ViewportRenderState::ptr)(this->curTileX, this->curTileY),
                                            (this->LogicLayer[this->curTileIndex] & 1U) != 0))
                                    && (((this->ChangedLayer[this->curTileIndex] != 0
                                             && (((this->LogicLayer[this->curTileIndex] & 0x10000030U) == 0
                                                 && (this->BuildingLayer[this->curTileIndex] == 0))))
                                        && ((this->MiscDisplayLayer[this->curTileIndex] & 0x40) == 0)))) {
                                    MACRO_NEIGHBOUR_FLAGS_MISC_8(m2, 0x80)
                                    bVar19 = this->neighbourMask;
                                    MACRO_NEIGHBOUR_FLAGS_MISC_8(m3, 0x40)
                                    bVar16 = this->neighbourMask;
                                    this->neighbourMask = bVar16 & ~bVar19;
                                    this->neighbourMask = this->neighbourMask & 0xe3; // 0x50C00B
                                    if (this->neighbourMask != 0) {
                                        this->GfxLayer[this->curTileIndex]
                                            = (short)GMFirstPictureIndex::instance[0xa6] + 0x5d0;
                                        this->PillarGFXLayer[this->curTileIndex]
                                            = (ushort)GMFirstPictureIndex::instance[9];
                                        this->MiscDisplayLayer[this->curTileIndex]
                                            = this->MiscDisplayLayer[this->curTileIndex] | 0x80;
                                    }
                                }
                                this->curTileX = this->curTileX + 1;
                            }
                        }
                    }
                }
            }
            local_c = DAT_PathFindingState::instance.dirtyMinY % 10;
            for (local_18 = this->dirtySectionRowMin; local_18 <= this->dirtySectionRowMax; local_18 = local_18 + 1) {
                for (local_10 = this->dirtySectionColMin; local_10 <= this->dirtySectionColMax; local_10 = local_10 + 1) {
                    if (*(char*)(local_18 * 0x28 + 0x1f93438 + local_10) != '\0') {
                        local_24 = local_c;
                        local_c = 0;
                        for (; local_24 < 10; local_24 = local_24 + 1) {
                            this->curTileY = local_18 * 10 + local_24;
                            this->curTileX = local_10 * 10;
                            for (local_30 = 0; local_30 < 10; local_30 = local_30 + 1) {
                                BVar11 = MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                                    DAT_ViewportRenderState::ptr)(this->curTileX, (uint)((int)(this->curTileY)));
                                if (((BVar11 != FALSE)
                                        && (this->curTileIndex = MACRO_CALL_MEMBER(
                                                OpenSHC::Rendering::ViewportRenderState_Func::translateXYToTile,
                                                DAT_ViewportRenderState::ptr)(this->curTileX, this->curTileY),
                                            (this->LogicLayer[this->curTileIndex] & (L_BORDER | L_BORDER_EDGE)) == 0))
                                    && (this->ChangedLayer[this->curTileIndex] != 0)) {
                                    this->ChangedLayer[this->curTileIndex] = this->ChangedLayer[this->curTileIndex] - 1;
                                    iVar17 = this->curTileX;
                                    if ((this->LogicLayer[this->curTileIndex] & L_SEA) == 0) {
                                        if ((this->LogicLayer[this->curTileIndex] & L_RIVER) == 0) {
                                            if ((this->LogicLayer[this->curTileIndex] & L_FORD) == 0) {
                                                if ((this->LogicLayer[this->curTileIndex] & L_PLAIN2_AND_PITCH) == 0) {
                                                    if (this->BuildingLayer[this->curTileIndex] != 0) {
                                                        iVar13 = (int)this->BuildingLayer[this->curTileIndex];
                                                        if (DAT_BuildingsState::instance.buildings[iVar13].buildingType
                                                            == OpenSHC::Map::Buildings::BT_STOCKPILE) {
                                                            this->tmpGfxVariant
                                                                = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::
                                                                                        computeWallCornerRenderRotation,
                                                                    this)(this->curTileX);
                                                            this->WallGfxOrAnimCounterLayer[this->curTileIndex]
                                                                = (short)GMFirstPictureIndex::instance[10] + -1
                                                                + (short)this->tmpGfxVariant;
                                                        }
                                                        iVar14 = MACRO_CALL_MEMBER(
                                                            OpenSHC::Map::TileMapState_Func::computeClimbRampRotation,
                                                            this)(this->curTileIndex, (uint)((int)(iVar17)),
                                                            (uint)((int)(this->curTileY)));
                                                        BVar1 = DAT_BuildingsState::instance.buildings[iVar13]
                                                                    .buildingType;
                                                        if (((BVar1 == OpenSHC::Map::Buildings::BT_FIREBALLISTA)
                                                                || ((0x4f < (short)BVar1 && ((short)BVar1 < 0x55))))
                                                            && (iVar14 == 0)) {
                                                            this->PillarGFXLayer[this->curTileIndex]
                                                                = (short)(((((int)(uint)this
                                                                                    ->HeightLayer[this->curTileIndex]
                                                                                >> 3)
                                                                               + -1)
                                                                              * 0x40)
                                                                      / 2)
                                                                + (short)GMFirstPictureIndex::instance[3]
                                                                + (ushort)this->LuminesenceLayer[this->curTileIndex] * 4
                                                                + (this->RandomLayer[this->curTileIndex] & 3);
                                                        } else {
                                                            this->PillarGFXLayer[this->curTileIndex]
                                                                = (short)GMFirstPictureIndex::instance[9] + -1
                                                                + (short)this->tmpGfxVariant;
                                                            this->MiscDisplayLayer[this->curTileIndex]
                                                                = this->MiscDisplayLayer[this->curTileIndex] | 0x800;
                                                        }
                                                        if (((DAT_BuildingsState::instance.buildings[iVar13]
                                                                     .buildingType
                                                                 == OpenSHC::Map::Buildings::BT_KILLINGPIT)
                                                                && (DAT_BuildingsState::instance.buildings[iVar13].state
                                                                    < 1))
                                                            && ((
                                                                BVar11 = MACRO_CALL_MEMBER(
                                                                    OpenSHC::Game::GameStateStructures_Func::isSameTeam,
                                                                    DAT_GameState::ptr)(
                                                                    (int)DAT_BuildingsState::instance.buildings[iVar13]
                                                                        .owner,
                                                                    (int)((int)(DAT_GameSynchronyState::instance
                                                                            .currentPlayerSlotID))),
                                                                BVar11 == FALSE
                                                                    && (DAT_GameCore::instance.gameMode_2
                                                                        != OpenSHC::Game::GM_EDITOR)))) {
                                                            if ((this->LogicLayer[this->curTileIndex]
                                                                    & L_DEFAULT_EARTH_OR_TEXTURE)
                                                                == 0)
                                                                goto LAB_00510585;
                                                            this->GfxLayer[this->curTileIndex] = 0;
                                                        } else {
                                                            if (DAT_BuildingsState::instance.buildings[iVar13]
                                                                    .buildingType
                                                                == OpenSHC::Map::Buildings::BT_SIEGETOWER_PLACED)
                                                                goto LAB_00510585;
                                                            if (DAT_BuildingsState::instance.buildings[iVar13]
                                                                    .currentTilePositionAdjusted
                                                                == this->curTileIndex) {
                                                                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::
                                                                                      updateBuildingGraphicsLayer,
                                                                    this)(iVar13);
                                                                goto LAB_005109e8;
                                                            }
                                                        }
                                                        goto LAB_0050c199;
                                                    }
                                                    if ((this->LogicLayer[this->curTileIndex] & L_KEEP_NON_MANOR_HOUSE)
                                                        == 0) {
                                                        if (((this->LogicLayer[this->curTileIndex] & L_ROCKY) == 0)
                                                            || ((this->LogicLayer[this->curTileIndex]
                                                                    & L_WALL_OR_GATEHOUSE)
                                                                != 0)) {
                                                            if ((this->LogicLayer[this->curTileIndex] & L_BOULDERS)
                                                                == 0) {
                                                                if ((this->LogicLayer[this->curTileIndex] & L_PEBBLES)
                                                                    == 0) {
                                                                    if ((this->LogicLayer[this->curTileIndex] & L_IRON)
                                                                        == 0) {
                                                                        if ((this->LogicLayer[this->curTileIndex]
                                                                                & L_OIL)
                                                                            == 0) {
                                                                            if ((this->LogicLayer[this->curTileIndex]
                                                                                    & L_MOAT)
                                                                                == 0) {
                                                                                if (((this->LogicLayer[this
                                                                                              ->curTileIndex]
                                                                                             & (L_WALL_OR_GATEHOUSE
                                                                                         | L_FARM_FIELD_WHEAT
                                                                                         | L_FARM_FIELD_HOP
                                                                                         | L_FARM_FIELD_APPLE
                                                                                         | L_FARM_FIELD_DAIRY))
                                                                                        == 0)
                                                                                    || ((this->LogicLayer[this
                                                                                                 ->curTileIndex]
                                                                                            & L_FARM_FIELD_APPLE)
                                                                                        != 0)) {
                                                                                    sVar8 = 0;
                                                                                    if ((this->WallOwnerLayer[this
                                                                                                 ->curTileIndex]
                                                                                            & 8)
                                                                                        != 0) {
                                                                                        sVar8 = 0x2d;
                                                                                    }
                                                                                    if ((this->MiscDisplayLayer[this
                                                                                                 ->curTileIndex]
                                                                                            & 0x80)
                                                                                        != 0)
                                                                                        goto LAB_0050ffbc;
                                                                                    if ((((this->LogicLayer[this
                                                                                                   ->curTileIndex]
                                                                                                  & (L_WALL_OR_GATEHOUSE
                                                                                              | L_BUILDING
                                                                                              | L_KEEP_NON_MANOR_HOUSE))
                                                                                             != 0)
                                                                                            || (this->BuildingWasLayer
                                                                                                    [this->curTileIndex]
                                                                                                == '\0'))
                                                                                        || ((this->MiscDisplayLayer[this
                                                                                                     ->curTileIndex]
                                                                                                & 0x10)
                                                                                            == 0))
                                                                                        goto LAB_00510585;
                                                                                }
                                                                            } else {
                                                                                this->neighbourMask = 0;
                                                                                for (local_d4 = 0; local_d4 < 8;
                                                                                    local_d4 = local_d4 + 2) {
                                                                                    iVar13 = this->curTileIndex
                                                                                        + this->directionTranslationMatrix
                                                                                              [this->curTileY]
                                                                                              [local_d4];
                                                                                    if ((this->LogicLayer[iVar13]
                                                                                            & L_MOAT)
                                                                                        == 0) {
                                                                                        if (((this->BuildingLayer
                                                                                                     [iVar13]
                                                                                                 != 0)
                                                                                                && (DAT_BuildingsState::instance
                                                                                                        .buildings[this->BuildingLayer
                                                                                                                [iVar13]]
                                                                                                        .buildingType
                                                                                                    == OpenSHC::Map::
                                                                                                        Buildings::
                                                                                                            BT_DRAWBRIDGE))
                                                                                            && (iVar13
                                                                                                = MACRO_CALL_MEMBER(
                                                                                                    OpenSHC::Map::
                                                                                                        TileMapState_Func::
                                                                                                            returnOwnedMoatAtTile,
                                                                                                    this)(iVar13),
                                                                                                iVar13 != 0)) {
                                                                                            this->neighbourMask
                                                                                                = this->neighbourMask
                                                                                                | (byte)(0x80
                                                                                                    >> ((byte)local_d4
                                                                                                        & 0x1f));
                                                                                        }
                                                                                    } else {
                                                                                        this->neighbourMask = this->neighbourMask
                                                                                            | (byte)(0x80
                                                                                                >> ((byte)local_d4
                                                                                                    & 0x1f));
                                                                                    }
                                                                                }
                                                                                this->neighbourMask = ~this->neighbourMask & 0xaa;
                                                                                if (this->neighbourMask == 0) {
                                                                                    this->neighbourMask = 0;
                                                                                    for (local_d4 = 1; local_d4 < 8;
                                                                                        local_d4 = local_d4 + 2) {
                                                                                        iVar13 = this->curTileIndex
                                                                                            + this->directionTranslationMatrix
                                                                                                  [this->curTileY]
                                                                                                  [local_d4];
                                                                                        if ((this->LogicLayer[iVar13]
                                                                                                & L_MOAT)
                                                                                            == 0) {
                                                                                            if (((this->BuildingLayer
                                                                                                         [iVar13]
                                                                                                     != 0)
                                                                                                    && (DAT_BuildingsState::instance
                                                                                                            .buildings
                                                                                                                [this->BuildingLayer
                                                                                                                        [iVar13]]
                                                                                                            .buildingType
                                                                                                        == OpenSHC::Map::
                                                                                                            Buildings::
                                                                                                                BT_DRAWBRIDGE))
                                                                                                && (iVar13
                                                                                                    = MACRO_CALL_MEMBER(
                                                                                                        OpenSHC::Map::
                                                                                                            TileMapState_Func::
                                                                                                                returnOwnedMoatAtTile,
                                                                                                        this)(iVar13),
                                                                                                    iVar13 != 0)) {
                                                                                                this->neighbourMask
                                                                                                    = this->neighbourMask
                                                                                                    | (byte)(0x80
                                                                                                        >> ((byte)
                                                                                                                local_d4
                                                                                                            & 0x1f));
                                                                                            }
                                                                                        } else {
                                                                                            this->neighbourMask
                                                                                                = this->neighbourMask
                                                                                                | (byte)(0x80
                                                                                                    >> ((byte)local_d4
                                                                                                        & 0x1f));
                                                                                        }
                                                                                    }
                                                                                    this->neighbourMask
                                                                                        = ~this->neighbourMask & 0x55;
                                                                                }
                                                                                if (this->mapOrientation == 0) {
                                                                                    this->neighbourMask = MACRO_CALL_MEMBER(
                                                                                        OpenSHC::Map::Navigation::
                                                                                            DirectionAlgorithmState_Func::
                                                                                                rotateByteLeft,
                                                                                        DAT_DirectionAlgorithmState::
                                                                                            ptr)(this->neighbourMask, 0);
                                                                                } else if (this->mapOrientation == 2) {
                                                                                    this->neighbourMask = MACRO_CALL_MEMBER(
                                                                                        OpenSHC::Map::Navigation::
                                                                                            DirectionAlgorithmState_Func::
                                                                                                rotateByteLeft,
                                                                                        DAT_DirectionAlgorithmState::
                                                                                            ptr)(this->neighbourMask, 2);
                                                                                } else if (this->mapOrientation == 4) {
                                                                                    this->neighbourMask = MACRO_CALL_MEMBER(
                                                                                        OpenSHC::Map::Navigation::
                                                                                            DirectionAlgorithmState_Func::
                                                                                                rotateByteLeft,
                                                                                        DAT_DirectionAlgorithmState::
                                                                                            ptr)(this->neighbourMask, 4);
                                                                                } else if (this->mapOrientation == 6) {
                                                                                    this->neighbourMask = MACRO_CALL_MEMBER(
                                                                                        OpenSHC::Map::Navigation::
                                                                                            DirectionAlgorithmState_Func::
                                                                                                rotateByteLeft,
                                                                                        DAT_DirectionAlgorithmState::
                                                                                            ptr)(this->neighbourMask, 6);
                                                                                }
                                                                                this->GfxLayer[this->curTileIndex]
                                                                                    = (short)GMFirstPictureIndex::
                                                                                          instance[5]
                                                                                    + 0xcc
                                                                                    + (ushort)this->LuminesenceLayer
                                                                                            [this->curTileIndex]
                                                                                        * 4
                                                                                    + (this->RandomLayer[this
                                                                                               ->curTileIndex]
                                                                                        & 3);
                                                                                for (local_14 = 0; local_14 < 7;
                                                                                    local_14 = local_14 + 1) {
                                                                                    if (DAT_TerrainDefinedData::instance
                                                                                            .edgeMaskGfxOffsetsB[local_14]
                                                                                            .unk1
                                                                                        == this->neighbourMask) {
                                                                                        sVar4 = (short)
                                                                                            GMFirstPictureIndex::
                                                                                                instance[5];
                                                                                        if (local_14 < 4) {
                                                                                            this->GfxLayer[this
                                                                                                    ->curTileIndex]
                                                                                                = sVar4 + 0xec
                                                                                                + (ushort)this->LuminesenceLayer
                                                                                                        [this->curTileIndex]
                                                                                                    * 4
                                                                                                + (ushort)DAT_TerrainDefinedData::
                                                                                                      instance
                                                                                                          .edgeMaskGfxOffsetsB
                                                                                                              [local_14]
                                                                                                          .unk2;
                                                                                        } else if (local_14 == 4) {
                                                                                            this->GfxLayer[this
                                                                                                    ->curTileIndex]
                                                                                                = sVar4 + 0x10c
                                                                                                + (ushort)this->LuminesenceLayer
                                                                                                        [this->curTileIndex]
                                                                                                    * 4
                                                                                                + (this->RandomLayer[this
                                                                                                           ->curTileIndex]
                                                                                                    & 3);
                                                                                        } else if (local_14 == 5) {
                                                                                            this->GfxLayer[this
                                                                                                    ->curTileIndex]
                                                                                                = sVar4 + 300
                                                                                                + (ushort)this->LuminesenceLayer
                                                                                                        [this->curTileIndex]
                                                                                                    * 4
                                                                                                + (this->RandomLayer[this
                                                                                                           ->curTileIndex]
                                                                                                    & 3);
                                                                                        } else if (local_14 == 6) {
                                                                                            this->GfxLayer[this
                                                                                                    ->curTileIndex]
                                                                                                = sVar4 + 0x14c
                                                                                                + (ushort)this->LuminesenceLayer
                                                                                                      [this->curTileIndex];
                                                                                        }
                                                                                        break;
                                                                                    }
                                                                                }
                                                                                if ((this->MiscDisplayLayer[this
                                                                                             ->curTileIndex]
                                                                                        & 0x80)
                                                                                    != 0) {
                                                                                LAB_0050ffbc:
                                                                                    uVar12
                                                                                        = (0xd - this->mapOrientation)
                                                                                        % 8;
                                                                                    uVar15 = (9 - this->mapOrientation)
                                                                                        % 8;
                                                                                    iVar13 = this->curTileIndex
                                                                                        + this->directionTranslationMatrix
                                                                                              [this->curTileY][uVar15];
                                                                                    uVar2 = (ushort)iVar17;
                                                                                    uVar3 = (ushort)this->curTileY;
                                                                                    if ((this->MiscDisplayLayer[this->curTileIndex
                                                                                             + this
                                                                                                 ->directionTranslationMatrix
                                                                                                     [this->curTileY]
                                                                                                     [uVar12]]
                                                                                            & 0x80)
                                                                                        == 0) {
                                                                                        if ((this->MiscDisplayLayer
                                                                                                    [iVar13]
                                                                                                & 0x80)
                                                                                            == 0) {
                                                                                            this->overlayImageOrStockpileIdLayer[this
                                                                                                    ->curTileIndex]
                                                                                                = this->overlayImageOrStockpileIdLayer[this
                                                                                                          ->curTileIndex]
                                                                                                + ((uVar2 ^ uVar3) & 1);
                                                                                        } else if ((this->mapOrientation
                                                                                                       == 0)
                                                                                            || (this->mapOrientation
                                                                                                == 4)) {
                                                                                            this->overlayImageOrStockpileIdLayer[this
                                                                                                    ->curTileIndex]
                                                                                                = ((uVar2 ^ uVar3) & 1)
                                                                                                + 0x33 + sVar8;
                                                                                        } else {
                                                                                            this->overlayImageOrStockpileIdLayer[this
                                                                                                    ->curTileIndex]
                                                                                                = ((uVar2 ^ uVar3) & 1)
                                                                                                + 0x35 + sVar8;
                                                                                        }
                                                                                    } else if ((this->MiscDisplayLayer
                                                                                                       [iVar13]
                                                                                                   & 0x80)
                                                                                        == 0) {
                                                                                        if ((this->mapOrientation == 0)
                                                                                            || (this->mapOrientation
                                                                                                == 4)) {
                                                                                            this->overlayImageOrStockpileIdLayer[this
                                                                                                    ->curTileIndex]
                                                                                                = ((uVar2 ^ uVar3) & 1)
                                                                                                + 0x35 + sVar8;
                                                                                        } else {
                                                                                            this->overlayImageOrStockpileIdLayer[this
                                                                                                    ->curTileIndex]
                                                                                                = ((uVar2 ^ uVar3) & 1)
                                                                                                + 0x33 + sVar8;
                                                                                        }
                                                                                    } else if ((this->mapOrientation
                                                                                                   == 0)
                                                                                        || (this->mapOrientation
                                                                                            == 6)) {
                                                                                        uVar12
                                                                                            = (int)this->curTileY % 8;
                                                                                        this->overlayImageOrStockpileIdLayer[this
                                                                                                ->curTileIndex]
                                                                                            = (0x3e - (short)uVar12)
                                                                                            + sVar8;
                                                                                    } else {
                                                                                        uVar12
                                                                                            = (int)this->curTileY % 8;
                                                                                        this->overlayImageOrStockpileIdLayer[this
                                                                                                ->curTileIndex]
                                                                                            = (short)uVar12 + 0x37
                                                                                            + sVar8;
                                                                                    }
                                                                                    MACRO_NEIGHBOUR_FLAGS_LOGIC_8(
                                                                                        r2, 0x200)
                                                                                    if (this->neighbourMask != 0) {
                                                                                        switch (this->mapOrientation) {
                                                                                        case 0:
                                                                                            if ((this->neighbourMask & 0x82)
                                                                                                == 0x82) {
                                                                                                this->overlayImageOrStockpileIdLayer[this
                                                                                                        ->curTileIndex]
                                                                                                    = this->overlayImageOrStockpileIdLayer
                                                                                                          [this->curTileIndex]
                                                                                                    + 0xe;
                                                                                            }
                                                                                            break;
                                                                                        case 2:
                                                                                            if ((this->neighbourMask & 0xa0)
                                                                                                == 0xa0) {
                                                                                                this->overlayImageOrStockpileIdLayer[this
                                                                                                        ->curTileIndex]
                                                                                                    = this->overlayImageOrStockpileIdLayer
                                                                                                          [this->curTileIndex]
                                                                                                    + 0xe;
                                                                                            }
                                                                                            break;
                                                                                        case 4:
                                                                                            if ((this->neighbourMask & 0x28)
                                                                                                == 0x28) {
                                                                                                this->overlayImageOrStockpileIdLayer[this
                                                                                                        ->curTileIndex]
                                                                                                    = this->overlayImageOrStockpileIdLayer
                                                                                                          [this->curTileIndex]
                                                                                                    + 0xe;
                                                                                            }
                                                                                            break;
                                                                                        case 6:
                                                                                            if ((this->neighbourMask & 10)
                                                                                                == 10) {
                                                                                                this->overlayImageOrStockpileIdLayer[this
                                                                                                        ->curTileIndex]
                                                                                                    = this->overlayImageOrStockpileIdLayer
                                                                                                          [this->curTileIndex]
                                                                                                    + 0xe;
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                    if ((this->LogicLayer[this
                                                                                                 ->curTileIndex]
                                                                                                & (L_PLAIN2_AND_PITCH
                                                                                            | L_MOAT))
                                                                                        == 0)
                                                                                        goto LAB_00510585;
                                                                                }
                                                                            }
                                                                        } else {
                                                                            this->PillarGFXLayer[this
                                                                                    ->curTileIndex] = (ushort)
                                                                                GMFirstPictureIndex::instance[9];
                                                                            this->tmpGfxVariant
                                                                                = (int)(short)this
                                                                                      ->RandomLayer[this->curTileIndex]
                                                                                & 7;
                                                                            this->GfxLayer[this->curTileIndex]
                                                                                = (short)GMFirstPictureIndex::
                                                                                      instance[0x37]
                                                                                + 0x428
                                                                                + (short)(this->tmpGfxVariant << 4);
                                                                            sVar4 = (short)this->curTileY;
                                                                            sVar5 = (short)this->curTileX;
                                                                            if (this->tmpGfxVariant == 0) {
                                                                                this->WallGfxOrAnimCounterLayer[this->curTileIndex]
                                                                                    = this->RandomLayer[this
                                                                                              ->curTileIndex]
                                                                                        + sVar5 + sVar4
                                                                                    & 0x1ff;
                                                                            } else if (this->tmpGfxVariant == 1) {
                                                                                this->WallGfxOrAnimCounterLayer[this->curTileIndex]
                                                                                    = this->RandomLayer[this
                                                                                              ->curTileIndex]
                                                                                        + sVar5 + sVar4
                                                                                    & 0x1ff;
                                                                            } else if (this->tmpGfxVariant == 2) {
                                                                                this->WallGfxOrAnimCounterLayer[this->curTileIndex]
                                                                                    = this->RandomLayer[this
                                                                                              ->curTileIndex]
                                                                                        + sVar5 + sVar4
                                                                                    & 0x7f;
                                                                            } else if (this->tmpGfxVariant == 3) {
                                                                                this->WallGfxOrAnimCounterLayer[this->curTileIndex]
                                                                                    = this->RandomLayer[this
                                                                                              ->curTileIndex]
                                                                                        + sVar5 + sVar4
                                                                                    & 0x7f;
                                                                            } else if (this->tmpGfxVariant == 4) {
                                                                                this->WallGfxOrAnimCounterLayer[this->curTileIndex]
                                                                                    = this->RandomLayer[this
                                                                                              ->curTileIndex]
                                                                                        + sVar5 + sVar4
                                                                                    & 0xff;
                                                                            } else if (this->tmpGfxVariant == 5) {
                                                                                this->WallGfxOrAnimCounterLayer[this->curTileIndex]
                                                                                    = this->RandomLayer[this
                                                                                              ->curTileIndex]
                                                                                        + sVar5 + sVar4
                                                                                    & 0xff;
                                                                            } else if (this->tmpGfxVariant == 6) {
                                                                                this->WallGfxOrAnimCounterLayer[this->curTileIndex]
                                                                                    = this->RandomLayer[this
                                                                                              ->curTileIndex]
                                                                                        + sVar5 + sVar4
                                                                                    & 0x7f;
                                                                            } else if (this->tmpGfxVariant == 7) {
                                                                                this->WallGfxOrAnimCounterLayer[this->curTileIndex]
                                                                                    = this->RandomLayer[this
                                                                                              ->curTileIndex]
                                                                                        + sVar5 + sVar4
                                                                                    & 0x7f;
                                                                            }
                                                                        }
                                                                    } else {
                                                                        MACRO_CALL_MEMBER(
                                                                            OpenSHC::Map::TileMapState_Func::
                                                                                computeClimbRampRotation,
                                                                            this)(this->curTileIndex,
                                                                            (uint)((int)(this->curTileX)),
                                                                            (uint)((int)(this->curTileY)));
                                                                        this->PillarGFXLayer[this->curTileIndex]
                                                                            = (short)
                                                                                  GMFirstPictureIndex::instance[9]
                                                                            + -1 + (short)this->tmpGfxVariant;
                                                                        this->MiscDisplayLayer[this->curTileIndex]
                                                                            = this->MiscDisplayLayer[this->curTileIndex]
                                                                            | 0x800;
                                                                        this->tmpGfxVariant
                                                                            = (int)(short)this
                                                                                  ->RandomLayer[this->curTileIndex]
                                                                            & 0xf;
                                                                        this->GfxLayer[this->curTileIndex]
                                                                            = (short)GMFirstPictureIndex::instance
                                                                                  [0xc]
                                                                            + 0xee + (short)this->tmpGfxVariant;
                                                                    }
                                                                } else {
                                                                    MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::
                                                                                          computeClimbRampRotation,
                                                                        this)(this->curTileIndex,
                                                                        (uint)((int)(this->curTileX)),
                                                                        (uint)((int)(this->curTileY)));
                                                                    this->PillarGFXLayer[this->curTileIndex]
                                                                        = (short)GMFirstPictureIndex::instance[9]
                                                                        + -1 + (short)this->tmpGfxVariant;
                                                                    this->MiscDisplayLayer[this->curTileIndex]
                                                                        = this->MiscDisplayLayer[this->curTileIndex]
                                                                        | 0x800;
                                                                    this->tmpGfxVariant
                                                                        = (int)(short)this
                                                                              ->RandomLayer[this->curTileIndex]
                                                                        & 0xf;
                                                                    if (this->LuminesenceLayer[this->curTileIndex]
                                                                        < 6) {
                                                                        this->GfxLayer[this->curTileIndex]
                                                                            = (short)GMFirstPictureIndex::instance
                                                                                  [0xc]
                                                                            + 0x20 + (short)this->tmpGfxVariant;
                                                                    } else {
                                                                        this->GfxLayer[this->curTileIndex]
                                                                            = (short)GMFirstPictureIndex::instance
                                                                                  [0xc]
                                                                            + 0x30 + (short)this->tmpGfxVariant;
                                                                    }
                                                                }
                                                            } else {
                                                                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::
                                                                                      computeClimbRampRotation,
                                                                    this)(this->curTileIndex,
                                                                    (uint)((int)(this->curTileX)),
                                                                    (uint)((int)(this->curTileY)));
                                                                this->PillarGFXLayer[this->curTileIndex]
                                                                    = (short)GMFirstPictureIndex::instance[9] + -1
                                                                    + (short)this->tmpGfxVariant;
                                                                this->MiscDisplayLayer[this->curTileIndex]
                                                                    = this->MiscDisplayLayer[this->curTileIndex]
                                                                    | 0x800;
                                                                this->tmpGfxVariant
                                                                    = (int)(short)this->RandomLayer[this->curTileIndex]
                                                                    & 0xf;
                                                                if (this->LuminesenceLayer[this->curTileIndex] < 6) {
                                                                    this->GfxLayer[this->curTileIndex]
                                                                        = (short)GMFirstPictureIndex::instance[0xc]
                                                                        + 0x40 + (short)this->tmpGfxVariant;
                                                                } else {
                                                                    this->GfxLayer[this->curTileIndex]
                                                                        = (short)GMFirstPictureIndex::instance[0xc]
                                                                        + 0x50 + (short)this->tmpGfxVariant;
                                                                }
                                                            }
                                                        } else {
                                                            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::
                                                                                  computeClimbRampRotation,
                                                                this)(this->curTileIndex,
                                                                (uint)((int)(this->curTileX)),
                                                                (uint)((int)(this->curTileY)));
                                                            this->PillarGFXLayer[this->curTileIndex]
                                                                = (short)GMFirstPictureIndex::instance[9] + -1
                                                                + (short)this->tmpGfxVariant;
                                                            this->MiscDisplayLayer[this->curTileIndex]
                                                                = this->MiscDisplayLayer[this->curTileIndex] | 0x800;
                                                            iVar13 = (int)this->OrganismLayer[this->curTileIndex];
                                                            if (1999 < iVar13) {
                                                                if (*(int*)(&DAT_LandscapeState::instance.trees[0x635]
                                                                                .hasCrows
                                                                        + iVar13 * 0x10)
                                                                    == this->curTileIndex) {
                                                                    MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::
                                                                                          applyRockGraphicsToFootprint,
                                                                        this)(iVar13 + -2000);
                                                                }
                                                                goto LAB_0050c199;
                                                            }
                                                            this->tmpGfxVariant
                                                                = (int)(short)this->RandomLayer[this->curTileIndex] & 7;
                                                            this->GfxLayer[this->curTileIndex]
                                                                = (short)GMFirstPictureIndex::instance[0x38]
                                                                + (ushort)this->LuminesenceLayer[this->curTileIndex] * 8
                                                                + (short)this->tmpGfxVariant;
                                                        }
                                                    } else {
                                                        if (DAT_BuildingsState::instance
                                                                .buildings[this->BuildingLayer[this->curTileIndex]]
                                                                .currentTilePositionAdjusted
                                                            != this->curTileIndex)
                                                            goto LAB_0050c199;
                                                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::
                                                                              updateBuildingGraphicsLayer,
                                                            this)((int)this->BuildingLayer[this->curTileIndex]);
                                                    }
                                                } else {
                                                    this->MiscDisplayLayer[this->curTileIndex]
                                                        = this->MiscDisplayLayer[this->curTileIndex] & 0xdfff;
                                                    iVar13 = MACRO_CALL_MEMBER(
                                                        OpenSHC::Map::TileMapState_Func::getPitchDitchIDForTile, this)(
                                                        this->curTileIndex);
                                                    if (iVar13 != 0) {
                                                        if (((this->pitchDitches[iVar13].state < 2)
                                                                && (BVar11 = MACRO_CALL_MEMBER(
                                                                        OpenSHC::Game::GameStateStructures_Func::
                                                                            isSameTeam,
                                                                        DAT_GameState::ptr)(
                                                                        (int)this->pitchDitches[iVar13].owner,
                                                                        (int)((int)(DAT_GameSynchronyState::instance
                                                                                .currentPlayerSlotID))),
                                                                    BVar11 == FALSE))
                                                            && (DAT_GameCore::instance.gameMode_2
                                                                != OpenSHC::Game::GM_EDITOR)) {
                                                            if ((this->LogicLayer[this->curTileIndex]
                                                                    & L_DEFAULT_EARTH_OR_TEXTURE)
                                                                == 0)
                                                                goto LAB_00510585;
                                                            this->GfxLayer[this->curTileIndex] = 0;
                                                        } else {
                                                            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::
                                                                                  computeClimbRampRotation,
                                                                this)(this->curTileIndex, (uint)((int)(iVar17)),
                                                                (uint)((int)(this->curTileY)));
                                                            this->PillarGFXLayer[this->curTileIndex]
                                                                = (short)GMFirstPictureIndex::instance[9] + -1
                                                                + (short)this->tmpGfxVariant;
                                                            this->MiscDisplayLayer[this->curTileIndex]
                                                                = this->MiscDisplayLayer[this->curTileIndex] | 0x800;
                                                            this->GfxLayer[this->curTileIndex]
                                                                = (this->pitchDitches[iVar13].rng & 7U)
                                                                + (short)GMFirstPictureIndex::instance[0x8c];
                                                            this->MiscDisplayLayer[this->curTileIndex]
                                                                = this->MiscDisplayLayer[this->curTileIndex] | 0x2000;
                                                            if ((this->MiscDisplayLayer[this->curTileIndex] & 0x80)
                                                                != 0)
                                                                goto LAB_0050ffbc;
                                                        }
                                                        goto LAB_0050c199;
                                                    }
                                                LAB_00510585:
                                                    uVar12
                                                        = (((int)(uint)this->HeightLayer[this->curTileIndex] >> 3) - 1)
                                                        % 16;
                                                    local_8 = uVar12 * 0x40 + 1;
                                                    iVar13 = MACRO_CALL_MEMBER(
                                                        OpenSHC::Map::TileMapState_Func::computeClimbRampRotation,
                                                        this)(this->curTileIndex, (uint)((int)(iVar17)),
                                                        (uint)((int)(this->curTileY)));
                                                    if ((this->HeightLayer[this->curTileIndex] < 0x88)
                                                        && (iVar13 == 0)) {
                                                        if (local_8 < 1) {
                                                            local_8 = 1;
                                                        }
                                                        this->PillarGFXLayer[this->curTileIndex]
                                                            = (short)((local_8 + -1) / 2)
                                                            + (short)GMFirstPictureIndex::instance[3]
                                                            + (ushort)this->LuminesenceLayer[this->curTileIndex] * 4
                                                            + (this->RandomLayer[this->curTileIndex] & 3);
                                                        BVar11 = MACRO_CALL_MEMBER(
                                                            OpenSHC::Map::TileMapState_Func::isCliffDropInDirection,
                                                            this)(this->curTileIndex, (undefined4)((int)(iVar17)),
                                                            this->curTileY);
                                                        if (BVar11 == FALSE) {
                                                            bVar10 = false;
                                                        } else {
                                                            bVar10 = true;
                                                        }
                                                    } else {
                                                        this->PillarGFXLayer[this->curTileIndex]
                                                            = (short)GMFirstPictureIndex::instance[9] + -1
                                                            + (short)this->tmpGfxVariant;
                                                        this->MiscDisplayLayer[this->curTileIndex]
                                                            = this->MiscDisplayLayer[this->curTileIndex] | 0x800;
                                                        bVar10 = true;
                                                    }
                                                    if ((this->Logic2Layer[this->curTileIndex] & 0x20) == 0) {
                                                        if (this->HeightLayer[this->curTileIndex] < 8) {
                                                            if ((this->Logic2Layer[this->curTileIndex] & 2) == 0) {
                                                                this->GfxLayer[this->curTileIndex]
                                                                    = (short)GMFirstPictureIndex::instance[2]
                                                                    + (ushort)this->LuminesenceLayer[this->curTileIndex]
                                                                        * 4
                                                                    + (this->RandomLayer[this->curTileIndex] & 3);
                                                            } else {
                                                                this->GfxLayer[this->curTileIndex]
                                                                    = (short)GMFirstPictureIndex::instance[0x37]
                                                                    + 0xb4
                                                                    + (this->RandomLayer[this->curTileIndex] & 7);
                                                            }
                                                        } else if ((this->LogicLayer[this->curTileIndex]
                                                                       & L_DEFAULT_EARTH_OR_TEXTURE)
                                                            == 0) {
                                                            if ((bVar10)
                                                                && (DAT_GameCore::instance.gameMode_2
                                                                    == OpenSHC::Game::GM_EDITOR)) {
                                                                this->LogicLayer[this->curTileIndex]
                                                                    = this->LogicLayer[this->curTileIndex] | 128;
                                                                this->GfxLayer[this->curTileIndex]
                                                                    = (short)GMFirstPictureIndex::instance[0x38]
                                                                    + (ushort)this->LuminesenceLayer[this->curTileIndex]
                                                                        * 8
                                                                    + (this->RandomLayer[this->curTileIndex] & 7);
                                                            } else {
                                                                this->GfxLayer[this->curTileIndex]
                                                                    = (short)GMFirstPictureIndex::instance[2]
                                                                    + ((short)((int)(uint)this
                                                                                   ->HeightLayer[this->curTileIndex]
                                                                           >> 3)
                                                                          + -1)
                                                                        * 0x20
                                                                    + (ushort)this->LuminesenceLayer[this->curTileIndex]
                                                                        * 4
                                                                    + (this->RandomLayer[this->curTileIndex] & 3);
                                                            }
                                                        } else {
                                                            /*
                                                              sets section 1001 after placing oasis grass for example
                                                             */
                                                            this->GfxLayer[this->curTileIndex] = 0;
                                                        }
                                                    } else {
                                                        this->GfxLayer[this->curTileIndex] = 0;
                                                    }
                                                }
                                            } else {
                                                MACRO_NEIGHBOUR_FLAGS_LOGIC_4(c1, NEIGHBOUR_FLAGS_MASK_RIVER_OR_FORD)
                                                bVar19 = this->neighbourMask;
                                                this->neighbourMask = ~bVar19 & 0xaa;
                                                if (this->neighbourMask == 0) {
                                                    MACRO_NEIGHBOUR_FLAGS_LOGIC_8(
                                                        d1, NEIGHBOUR_FLAGS_MASK_RIVER_OR_FORD)
                                                    this->neighbourMask = ~this->neighbourMask;
                                                    this->neighbourMask = this->neighbourMask & 0x55;
                                                }
                                                if (this->mapOrientation == 0) {
                                                    this->neighbourMask = MACRO_CALL_MEMBER(
                                                        OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::
                                                            rotateByteLeft,
                                                        DAT_DirectionAlgorithmState::ptr)(this->neighbourMask, 0);
                                                } else if (this->mapOrientation == 2) {
                                                    this->neighbourMask = MACRO_CALL_MEMBER(
                                                        OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::
                                                            rotateByteLeft,
                                                        DAT_DirectionAlgorithmState::ptr)(this->neighbourMask, 2);
                                                } else if (this->mapOrientation == 4) {
                                                    this->neighbourMask = MACRO_CALL_MEMBER(
                                                        OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::
                                                            rotateByteLeft,
                                                        DAT_DirectionAlgorithmState::ptr)(this->neighbourMask, 4);
                                                } else if (this->mapOrientation == 6) {
                                                    this->neighbourMask = MACRO_CALL_MEMBER(
                                                        OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::
                                                            rotateByteLeft,
                                                        DAT_DirectionAlgorithmState::ptr)(this->neighbourMask, 6);
                                                }
                                                this->GfxLayer[this->curTileIndex]
                                                    = (short)GMFirstPictureIndex::instance[5] + 0x29c
                                                    + (ushort)this->LuminesenceLayer[this->curTileIndex] * 8
                                                    + (this->RandomLayer[this->curTileIndex] & 7);
                                                for (local_14 = 0; local_14 < 7; local_14 = local_14 + 1) {
                                                    if (DAT_TerrainDefinedData::instance.edgeMaskGfxOffsetsB[local_14].unk1
                                                        == this->neighbourMask) {
                                                        sVar4 = (short)GMFirstPictureIndex::instance[5];
                                                        if (local_14 < 4) {
                                                            this->GfxLayer[this->curTileIndex] = sVar4 + 0x234
                                                                + (ushort)this->LuminesenceLayer[this->curTileIndex] * 4
                                                                + (ushort)DAT_TerrainDefinedData::instance
                                                                      .edgeMaskGfxOffsetsB[local_14]
                                                                      .unk2;
                                                        } else if (local_14 == 4) {
                                                            this->GfxLayer[this->curTileIndex] = sVar4 + 0x254
                                                                + (ushort)this->LuminesenceLayer[this->curTileIndex] * 4
                                                                + (this->RandomLayer[this->curTileIndex] & 3);
                                                        } else if (local_14 == 5) {
                                                            this->GfxLayer[this->curTileIndex] = sVar4 + 0x274
                                                                + (ushort)this->LuminesenceLayer[this->curTileIndex] * 4
                                                                + (this->RandomLayer[this->curTileIndex] & 3);
                                                        } else if (local_14 == 6) {
                                                            this->GfxLayer[this->curTileIndex] = sVar4 + 0x294
                                                                + (ushort)this->LuminesenceLayer[this->curTileIndex];
                                                        }
                                                        break;
                                                    }
                                                }
                                            }
                                        } else {
                                            this->Logic2Layer[this->curTileIndex]
                                                = this->Logic2Layer[this->curTileIndex] & 0xf7;
                                            MACRO_NEIGHBOUR_FLAGS_LOGIC_4(c2, 1)
                                            bVar19 = this->neighbourMask;
                                            if ((bVar19 != 0)
                                                && (this->Logic2Layer[this->curTileIndex]
                                                    = this->Logic2Layer[this->curTileIndex] | 8,
                                                    (this->Logic2Layer[this->curTileIndex] & 0x20) != 0)) {
                                                this->Logic2Layer[this->curTileIndex]
                                                    = this->Logic2Layer[this->curTileIndex] & 0xdf;
                                                this->WallGfxOrAnimCounterLayer[this->curTileIndex]
                                                    = this->RandomLayer[this->curTileIndex] & 7;
                                            }
                                            MACRO_NEIGHBOUR_FLAGS_LOGIC_4(c3, 0x100031)
                                            bVar19 = this->neighbourMask;
                                            this->neighbourMask = ~bVar19 & 0xaa;
                                            if (this->neighbourMask == 0) {
                                                MACRO_NEIGHBOUR_FLAGS_LOGIC_8(d2, 0x100031)
                                                this->neighbourMask = ~this->neighbourMask;
                                                this->neighbourMask = this->neighbourMask & 0x55;
                                            }
                                            if (this->mapOrientation == 0) {
                                                this->neighbourMask = MACRO_CALL_MEMBER(
                                                    OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::
                                                        rotateByteLeft,
                                                    DAT_DirectionAlgorithmState::ptr)(this->neighbourMask, 0);
                                            } else if (this->mapOrientation == 2) {
                                                this->neighbourMask = MACRO_CALL_MEMBER(
                                                    OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::
                                                        rotateByteLeft,
                                                    DAT_DirectionAlgorithmState::ptr)(this->neighbourMask, 2);
                                            } else if (this->mapOrientation == 4) {
                                                this->neighbourMask = MACRO_CALL_MEMBER(
                                                    OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::
                                                        rotateByteLeft,
                                                    DAT_DirectionAlgorithmState::ptr)(this->neighbourMask, 4);
                                            } else if (this->mapOrientation == 6) {
                                                this->neighbourMask = MACRO_CALL_MEMBER(
                                                    OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::
                                                        rotateByteLeft,
                                                    DAT_DirectionAlgorithmState::ptr)(this->neighbourMask, 6);
                                            }
                                            MACRO_CALL_MEMBER(
                                                OpenSHC::Map::TileMapState_Func::propagateCliffEdgeFlagFromNeighbor,
                                                this)(this->curTileIndex, iVar17, this->curTileY);
                                            if (this->Logic2Layer[this->curTileIndex] == 0) {
                                                this->GfxLayer[this->curTileIndex]
                                                    = (short)GMFirstPictureIndex::instance[5] + 0x214
                                                    + (ushort)this->LuminesenceLayer[this->curTileIndex] * 4
                                                    + (this->RandomLayer[this->curTileIndex] & 3);
                                                for (local_14 = 0; local_14 < 7; local_14 = local_14 + 1) {
                                                    if (DAT_TerrainDefinedData::instance.edgeMaskGfxOffsetsB[local_14].unk1
                                                        == this->neighbourMask) {
                                                        MACRO_NEIGHBOUR_FLAGS_LOGIC_4(c4, 0x200000)
                                                        sVar4 = (short)GMFirstPictureIndex::instance[5];
                                                        if (local_14 < 4) {
                                                            if (this->neighbourMask == 0) {
                                                                this->GfxLayer[this->curTileIndex] = sVar4 + 0x234
                                                                    + (ushort)this->LuminesenceLayer[this->curTileIndex]
                                                                        * 4
                                                                    + (ushort)DAT_TerrainDefinedData::instance
                                                                          .edgeMaskGfxOffsetsB[local_14]
                                                                          .unk2;
                                                            } else {
                                                                this->GfxLayer[this->curTileIndex] = sVar4 + 0x2dc
                                                                    + (ushort)this->LuminesenceLayer[this->curTileIndex]
                                                                        * 4
                                                                    + (ushort)DAT_TerrainDefinedData::instance
                                                                          .edgeMaskGfxOffsetsB[local_14]
                                                                          .unk2;
                                                            }
                                                        } else if (this->neighbourMask == 0) {
                                                            if (local_14 == 4) {
                                                                this->GfxLayer[this->curTileIndex] = sVar4 + 0x254
                                                                    + (ushort)this->LuminesenceLayer[this->curTileIndex]
                                                                        * 4
                                                                    + (this->RandomLayer[this->curTileIndex] & 3);
                                                            } else if (local_14 == 5) {
                                                                this->GfxLayer[this->curTileIndex] = sVar4 + 0x274
                                                                    + (ushort)this->LuminesenceLayer[this->curTileIndex]
                                                                        * 4
                                                                    + (this->RandomLayer[this->curTileIndex] & 3);
                                                            } else if (local_14 == 6) {
                                                                this->GfxLayer[this->curTileIndex] = sVar4 + 0x294
                                                                    + (ushort)this
                                                                          ->LuminesenceLayer[this->curTileIndex];
                                                            }
                                                        }
                                                        break;
                                                    }
                                                }
                                            }
                                            if ((this->Logic2Layer[this->curTileIndex] & 0x20) != 0) {
                                                sVar4 = (this->WallGfxOrAnimCounterLayer[this->curTileIndex] & 8) * 8 + 0x38d;
                                                sVar5 = (short)GMFirstPictureIndex::instance[5];
                                                if (this->mapOrientation == 0) {
                                                    this->GfxLayer[this->curTileIndex] = sVar5 + sVar4 + -1
                                                        + (short)((int)(this->WallGfxOrAnimCounterLayer[this->curTileIndex] & 0x3e0)
                                                              >> 5)
                                                            * 8;
                                                } else if (this->mapOrientation == 2) {
                                                    this->GfxLayer[this->curTileIndex] = sVar5 + sVar4 + -1
                                                        + ((short)((int)(this->WallGfxOrAnimCounterLayer[this->curTileIndex] & 0x3e0)
                                                               >> 5)
                                                                  - 2U
                                                              & 7)
                                                            * 8;
                                                } else if (this->mapOrientation == 4) {
                                                    this->GfxLayer[this->curTileIndex] = sVar5 + sVar4 + -1
                                                        + ((short)((int)(this->WallGfxOrAnimCounterLayer[this->curTileIndex] & 0x3e0)
                                                               >> 5)
                                                                  - 4U
                                                              & 7)
                                                            * 8;
                                                } else {
                                                    this->GfxLayer[this->curTileIndex] = sVar5 + sVar4 + -1
                                                        + ((short)((int)(this->WallGfxOrAnimCounterLayer[this->curTileIndex] & 0x3e0)
                                                               >> 5)
                                                                  - 6U
                                                              & 7)
                                                            * 8;
                                                }
                                            }
                                            sVar4 = (short)GMFirstPictureIndex::instance[5];
                                            if ((this->Logic2Layer[this->curTileIndex] & 0x50) == 0) {
                                                if (((int)(char)this->Logic2Layer[this->curTileIndex] & 0x88U) == 0) {
                                                    if ((this->Logic2Layer[this->curTileIndex] & 1) == 0) {
                                                        if ((this->Logic2Layer[this->curTileIndex] & 2) == 0) {
                                                            if ((this->Logic2Layer[this->curTileIndex] & 4) != 0) {
                                                                this->GfxLayer[this->curTileIndex] = sVar4 + 0x41c;
                                                            }
                                                        } else {
                                                            this->GfxLayer[this->curTileIndex] = sVar4 + 0x414;
                                                        }
                                                    } else {
                                                        this->GfxLayer[this->curTileIndex] = sVar4 + 0x40c;
                                                    }
                                                } else {
                                                    MACRO_NEIGHBOUR_FLAGS_LOGIC_8(m4, 1)
                                                    bVar19 = this->neighbourMask;
                                                    MACRO_NEIGHBOUR_FLAGS_TERRAIN_8(r3, 0x50)
                                                    bVar16 = this->neighbourMask;
                                                    this->neighbourMask = bVar16 | bVar19;
                                                    local_c0 = 0xffffffff;
                                                    if (this->neighbourMask == 0) {
                                                        MACRO_NEIGHBOUR_FLAGS_LOGIC_8(m5, 0x100000)
                                                        if (this->neighbourMask != 0) {
                                                            for (local_14 = 0; local_14 < 8; local_14 = local_14 + 1) {
                                                                if ((((uint)this->neighbourMask
                                                                         & 1 << ((byte)local_14 & 0x1f))
                                                                        != 0)
                                                                    && (this->HeightLayer[this->curTileIndex
                                                                            + this->directionTranslationMatrix
                                                                                [this->curTileY]
                                                                                [DAT_TerrainDefinedData::instance
                                                                                        .neighbourBitDirections[local_14]]]
                                                                        <= this->HeightLayer[this->curTileIndex])) {
                                                                    this->neighbourMask = this->neighbourMask
                                                                        & ~(byte)(1 << ((byte)local_14 & 0x1f));
                                                                }
                                                            }
                                                            if (this->neighbourMask != 0) {
                                                                if ((this->neighbourMask & 0x80) == 0) {
                                                                    if ((this->neighbourMask & 0x20) == 0) {
                                                                        if ((this->neighbourMask & 8) == 0) {
                                                                            if ((this->neighbourMask & 2) == 0) {
                                                                                if (this->neighbourMask == 0x41) {
                                                                                    local_c0 = 4;
                                                                                } else if (this->neighbourMask == 0x50) {
                                                                                    local_c0 = 6;
                                                                                } else if (this->neighbourMask == 0x14) {
                                                                                    local_c0 = 0;
                                                                                } else if (this->neighbourMask == 5) {
                                                                                    local_c0 = 2;
                                                                                } else if ((this->neighbourMask & 0x40)
                                                                                    == 0) {
                                                                                    if ((this->neighbourMask & 1) == 0) {
                                                                                        if ((this->neighbourMask & 4) == 0) {
                                                                                            if ((this->neighbourMask & 0x10)
                                                                                                != 0) {
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
                                                                            } else if ((this->neighbourMask & 0x80) == 0) {
                                                                                if ((this->neighbourMask & 8) == 0) {
                                                                                    if ((this->neighbourMask & 5) == 5) {
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
                                                                        } else if ((this->neighbourMask & 2) == 0) {
                                                                            if ((this->neighbourMask & 0x20) == 0) {
                                                                                if ((this->neighbourMask & 0x14) == 0x14) {
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
                                                                    } else if ((this->neighbourMask & 8) == 0) {
                                                                        if ((this->neighbourMask & 0x80) == 0) {
                                                                            if ((this->neighbourMask & 0x50) == 0x50) {
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
                                                                } else if ((this->neighbourMask & 0x20) == 0) {
                                                                    if ((this->neighbourMask & 2) == 0) {
                                                                        if ((this->neighbourMask & 0x41) == 0x41) {
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
                                                                local_c0 = ((local_c0 - this->mapOrientation) + 8) % 8;
                                                                this->GfxLayer[this->curTileIndex]
                                                                    = sVar4 + 0x30c + (short)(local_c0 << 4);
                                                            }
                                                        }
                                                        if (local_c0 == 0xffffffff) {
                                                            this->GfxLayer[this->curTileIndex]
                                                                = (short)GMFirstPictureIndex::instance[5] + 0x214
                                                                + (ushort)this->LuminesenceLayer[this->curTileIndex] * 4
                                                                + (this->RandomLayer[this->curTileIndex] & 3);
                                                            this->Logic2Layer[this->curTileIndex]
                                                                = this->Logic2Layer[this->curTileIndex] & 0x7f;
                                                        }
                                                    } else {
                                                        if ((this->neighbourMask & 0x80) == 0) {
                                                            if ((this->neighbourMask & 0x20) == 0) {
                                                                if ((this->neighbourMask & 8) == 0) {
                                                                    if ((this->neighbourMask & 2) == 0) {
                                                                        if (this->neighbourMask == 0x40) {
                                                                            local_c0 = 5;
                                                                        } else if (this->neighbourMask == 1) {
                                                                            local_c0 = 3;
                                                                        } else if (this->neighbourMask == 4) {
                                                                            local_c0 = 1;
                                                                        } else if (this->neighbourMask == 0x10) {
                                                                            local_c0 = 7;
                                                                        } else if (this->neighbourMask == 0x41) {
                                                                            local_c0 = 4;
                                                                        } else if (this->neighbourMask == 0x50) {
                                                                            local_c0 = 6;
                                                                        } else if (this->neighbourMask == 0x14) {
                                                                            local_c0 = 0;
                                                                        } else if (this->neighbourMask == 5) {
                                                                            local_c0 = 2;
                                                                        }
                                                                    } else if ((this->neighbourMask & 0x80) == 0) {
                                                                        if ((this->neighbourMask & 8) == 0) {
                                                                            if ((this->neighbourMask & 5) == 5) {
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
                                                                } else if ((this->neighbourMask & 2) == 0) {
                                                                    if ((this->neighbourMask & 0x20) == 0) {
                                                                        if ((this->neighbourMask & 0x14) == 0x14) {
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
                                                            } else if ((this->neighbourMask & 8) == 0) {
                                                                if ((this->neighbourMask & 0x80) == 0) {
                                                                    if ((this->neighbourMask & 0x50) == 0x50) {
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
                                                        } else if ((this->neighbourMask & 0x20) == 0) {
                                                            if ((this->neighbourMask & 2) == 0) {
                                                                if ((this->neighbourMask & 0x41) == 0x41) {
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
                                                            this->GfxLayer[this->curTileIndex] = sVar4 + 0x214
                                                                + (ushort)this->LuminesenceLayer[this->curTileIndex] * 4
                                                                + (this->RandomLayer[this->curTileIndex] & 3);
                                                            this->Logic2Layer[this->curTileIndex]
                                                                = this->Logic2Layer[this->curTileIndex] & 0x7f;
                                                        } else {
                                                            uVar12 = ((local_c0 - this->mapOrientation) + 8) % 8;
                                                            this->GfxLayer[this->curTileIndex]
                                                                = sVar4 + 0x30c + (short)(uVar12 << 4);
                                                        }
                                                    }
                                                }
                                            } else {
                                                this->GfxLayer[this->curTileIndex] = sVar4 + 0x2fc;
                                            }
                                        }
                                    LAB_005109e8:
                                        if ((this->LogicLayer[this->curTileIndex] & 0x10000100U) != 0) {
                                            bVar19 = this->DefaultHeightLayer[this->curTileIndex];
                                            iVar17 = MACRO_CALL_MEMBER(
                                                OpenSHC::Map::TileMapState_Func::computeClimbRampRotation, this)(
                                                this->curTileIndex, (uint)((int)(iVar17)),
                                                (uint)((int)(this->curTileY)));
                                            sVar5 = (short)GMFirstPictureIndex::instance[9];
                                            sVar4 = (short)this->tmpGfxVariant;
                                            if (this->DefaultHeightLayer[this->curTileIndex] < 0x88) {
                                                if (iVar17 == 0) {
                                                    if ((this->Logic2Layer[this->curTileIndex] & 2) == 0) {
                                                        this->PillarGFXLayer[this->curTileIndex]
                                                            = (short)(((((int)(uint)bVar19 >> 3) + -1) * 0x40) / 2)
                                                            + (short)GMFirstPictureIndex::instance[3]
                                                            + (ushort)this->LuminesenceLayer[this->curTileIndex] * 4
                                                            + (this->RandomLayer[this->curTileIndex] & 3);
                                                    } else {
                                                        this->PillarGFXLayer[this->curTileIndex] = sVar5 + -1 + sVar4;
                                                        this->MiscDisplayLayer[this->curTileIndex]
                                                            = this->MiscDisplayLayer[this->curTileIndex] | 0x800;
                                                    }
                                                } else {
                                                    this->PillarGFXLayer[this->curTileIndex] = sVar5 + -1 + sVar4;
                                                    this->MiscDisplayLayer[this->curTileIndex]
                                                        = this->MiscDisplayLayer[this->curTileIndex] | 0x800;
                                                }
                                            } else {
                                                this->PillarGFXLayer[this->curTileIndex] = sVar5 + -1 + sVar4;
                                                this->MiscDisplayLayer[this->curTileIndex]
                                                    = this->MiscDisplayLayer[this->curTileIndex] | 0x800;
                                            }
                                        }
                                    } else {
                                        this->Logic2Layer[this->curTileIndex]
                                            = this->Logic2Layer[this->curTileIndex] & 0xf7;
                                        MACRO_NEIGHBOUR_FLAGS_LOGIC_4(c5, 0x100000)
                                        if (this->neighbourMask == 0) {
                                            if ((this->MiscDisplayLayer[this->curTileIndex] & 0xc0) == 0) {
                                                MACRO_NEIGHBOUR_FLAGS_MISC_8(m6, 0x40)
                                                bVar19 = this->neighbourMask;
                                                MACRO_NEIGHBOUR_FLAGS_MISC_8(m7, 0x80)
                                                bVar16 = this->neighbourMask;
                                                this->neighbourMask = bVar16 & ~bVar19;
                                                this->neighbourMask = this->neighbourMask & 0xe3; // 0x50C5E1
                                                if (this->neighbourMask != 0) {
                                                    this->GfxLayer[this->curTileIndex]
                                                        = (short)GMFirstPictureIndex::instance[0xa6] + 0x5c4;
                                                    this->PillarGFXLayer[this->curTileIndex]
                                                        = (ushort)GMFirstPictureIndex::instance[9];
                                                    this->MiscDisplayLayer[this->curTileIndex]
                                                        = this->MiscDisplayLayer[this->curTileIndex] | 0xc0;
                                                }
                                            }
                                            if (2 < this->LuminesenceLayer[this->curTileIndex]) {
                                                this->MiscDisplayLayer[this->curTileIndex]
                                                    = this->MiscDisplayLayer[this->curTileIndex] & 0xffbf;
                                                this->MiscDisplayLayer[this->curTileIndex]
                                                    = this->MiscDisplayLayer[this->curTileIndex] & 0xff7f;
                                            }
                                            local_38 = this->LuminesenceLayer[this->curTileIndex] - 2;
                                            if (local_38 < 0) {
                                                local_38 = 0;
                                            }
                                            sVar4 = (short)local_38;
                                            if ((this->MiscDisplayLayer[this->curTileIndex] & 0xc0) == 0) {
                                                if ((this->MiscDisplayLayer[this->curTileIndex] & 0x100) == 0) {
                                                    MACRO_NEIGHBOUR_FLAGS_MISC_8(m8, 0x100)
                                                    if (this->neighbourMask != 0) {
                                                        local_ac = 2;
                                                        uVar12 = (uint)this->neighbourMask
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
                                                                if ((1 << ((byte)local_b8 & 0x1f) & uVar12) != 0) {
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
                                                        this->GfxLayer[this->curTileIndex]
                                                            = (short)GMFirstPictureIndex::instance[0xa6]
                                                            + (short)((int)(short)this->RandomLayer[this->curTileIndex]
                                                                % local_ac)
                                                            + local_b0 + 8 + sVar4 * 0xf6;
                                                        this->MiscDisplayLayer[this->curTileIndex]
                                                            = this->MiscDisplayLayer[this->curTileIndex] | 0x200;
                                                    }
                                                } else {
                                                    local_94 = 2;
                                                    uVar15 = (int)this->SearchDistanceLayer[this->curTileIndex] & 0xff;
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
                                                            if ((1 << ((byte)local_a4 & 0x1f) & uVar12) != 0) {
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
                                                    local_9c = (short)((int)(short)this->RandomLayer[this->curTileIndex]
                                                                   % local_94)
                                                        + local_9c;
                                                    if (uVar15
                                                        != ((int)this->SearchDistanceLayer[this->curTileIndex] >> 8
                                                            & 0xffU)) {
                                                        local_9c = local_9c + 0x66;
                                                    }
                                                    this->GfxLayer[this->curTileIndex]
                                                        = (short)GMFirstPictureIndex::instance[0xa6] + local_9c
                                                        + 0x2a + sVar4 * 0xf6;
                                                }
                                            }
                                            if ((this->MiscDisplayLayer[this->curTileIndex] & 0x3c0) == 0) {
                                                this->GfxLayer[this->curTileIndex]
                                                    = (this->RandomLayer[this->curTileIndex] & 7)
                                                    + (short)GMFirstPictureIndex::instance[0xa6] + sVar4 * 0xf6;
                                                this->PillarGFXLayer[this->curTileIndex]
                                                    = (ushort)GMFirstPictureIndex::instance[9];
                                            }
                                        } else {
                                            this->GfxLayer[this->curTileIndex]
                                                = (short)GMFirstPictureIndex::instance[5] + 0x2fc;
                                            this->Logic2Layer[this->curTileIndex]
                                                = this->Logic2Layer[this->curTileIndex] | 8;
                                        }
                                    }
                                }
                            LAB_0050c199:
                                this->curTileX = this->curTileX + 1;
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

#pragma optimize("", on)
