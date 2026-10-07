#include "../../Map.func.hpp"
#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004FF080
    void TileMapState::updateMacroLayerRelated2()
    {
        XYPair* pXVar1;
        uint uVar2;
        XYPair* pXVar3;
        ushort uVar4;
        int iVar5;
        int iVar6;
        int _upTo16;
        int iVar7;
        int _upTo960;
        int iVar8;
        int _someX;
        int local_20;
        int local_1c;
        int local_18;
        int local_14;
        int local_10;
        int local_c;
        int local_8;
        int _upTo32;
        int _upTo32_2;
        iVar7 = DAT_PathFindingState::instance.mappingYRelated % 10;
        if (this->someIndex <= this->someLimit) {
            local_c = this->someIndex * 10;
            local_10 = this->someIndex * 0x28 + 0x1f93438;
            iVar6 = this->someIndex;
            do {
                if (this->someYLike <= this->someYLikeLimit) {
                    local_14 = this->someYLike * 10;
                    iVar5 = this->someYLike;
                    iVar8 = iVar7;
                    do {
                        iVar7 = iVar8;
                        if ((*(char*)(local_10 + iVar5) != '\0') && (iVar7 = 0, iVar8 < 10)) {
                            do {
                                this->DAT_SomeY = local_c + iVar8;
                                this->DAT_SomeX = local_14;
                                local_8 = 2;
                                do {
                                    if (((((uint)this->DAT_SomeX < 400) && ((uint)this->DAT_SomeY < 400))
                                            && (*(char*)(this->DAT_SomeX + 0x21aec98 + this->DAT_SomeY * 400) != '\0'))
                                        && ((this->DAT_SomeTile
                                            = DAT_ViewportRenderState::instance.translationMatrix[this->DAT_SomeY]
                                                    .addXgetTile
                                                + this->DAT_SomeX,
                                            this->ChangedLayer[this->DAT_SomeTile] != 0
                                                && ((this->LogicLayer[this->DAT_SomeTile]
                                                    & Map::LogicHelpers::L_SEA))))) {
                                        this->MacroLayer[this->DAT_SomeTile] = 0x800;
                                    }
                                    uVar2 = this->DAT_SomeX + 1;
                                    if (((uVar2 < 400) && ((uint)this->DAT_SomeY < 400))
                                        && (*(char*)(this->DAT_SomeX + 0x21aec99 + this->DAT_SomeY * 400) != '\0')) {
                                        iVar7 = DAT_ViewportRenderState::instance.translationMatrix[this->DAT_SomeY]
                                                    .addXgetTile;
                                        this->DAT_SomeTile = iVar7 + uVar2;
                                        if ((this->ChangedLayer[this->DAT_SomeTile] != 0)
                                            && ((this->LogicLayer[this->DAT_SomeX + iVar7 + 1]
                                                & Map::LogicHelpers::L_SEA))) {
                                            iVar7 = this->DAT_SomeX + iVar7 + 1;
                                            this->DAT_SomeX = uVar2;
                                            this->MacroLayer[iVar7] = 0x800;
                                            uVar2 = this->DAT_SomeX;
                                        }
                                    }
                                    this->DAT_SomeX = uVar2;
                                    uVar2 = this->DAT_SomeX + 1;
                                    if (((uVar2 < 400) && ((uint)this->DAT_SomeY < 400))
                                        && (*(char*)(this->DAT_SomeX + 0x21aec99 + this->DAT_SomeY * 400) != '\0')) {
                                        iVar7 = DAT_ViewportRenderState::instance.translationMatrix[this->DAT_SomeY]
                                                    .addXgetTile;
                                        this->DAT_SomeTile = iVar7 + uVar2;
                                        if ((this->ChangedLayer[this->DAT_SomeTile] != 0)
                                            && ((this->LogicLayer[this->DAT_SomeX + iVar7 + 1]
                                                & Map::LogicHelpers::L_SEA))) {
                                            iVar7 = this->DAT_SomeX + iVar7 + 1;
                                            this->DAT_SomeX = uVar2;
                                            this->MacroLayer[iVar7] = 0x800;
                                            uVar2 = this->DAT_SomeX;
                                        }
                                    }
                                    this->DAT_SomeX = uVar2;
                                    uVar2 = this->DAT_SomeX + 1;
                                    if (((uVar2 < 400) && ((uint)this->DAT_SomeY < 400))
                                        && (*(char*)(this->DAT_SomeX + 0x21aec99 + this->DAT_SomeY * 400) != '\0')) {
                                        iVar7 = DAT_ViewportRenderState::instance.translationMatrix[this->DAT_SomeY]
                                                    .addXgetTile;
                                        this->DAT_SomeTile = iVar7 + uVar2;
                                        if ((this->ChangedLayer[this->DAT_SomeTile] != 0)
                                            && ((this->LogicLayer[this->DAT_SomeX + iVar7 + 1]
                                                & Map::LogicHelpers::L_SEA))) {
                                            iVar7 = this->DAT_SomeX + iVar7 + 1;
                                            this->DAT_SomeX = uVar2;
                                            this->MacroLayer[iVar7] = 0x800;
                                            uVar2 = this->DAT_SomeX;
                                        }
                                    }
                                    this->DAT_SomeX = uVar2;
                                    uVar2 = this->DAT_SomeX + 1;
                                    if (((uVar2 < 400) && ((uint)this->DAT_SomeY < 400))
                                        && (*(char*)(this->DAT_SomeX + 0x21aec99 + this->DAT_SomeY * 400) != '\0')) {
                                        iVar7 = DAT_ViewportRenderState::instance.translationMatrix[this->DAT_SomeY]
                                                    .addXgetTile;
                                        this->DAT_SomeTile = iVar7 + uVar2;
                                        if ((this->ChangedLayer[this->DAT_SomeTile] != 0)
                                            && ((this->LogicLayer[this->DAT_SomeX + iVar7 + 1]
                                                & Map::LogicHelpers::L_SEA))) {
                                            iVar7 = this->DAT_SomeX + iVar7 + 1;
                                            this->DAT_SomeX = uVar2;
                                            this->MacroLayer[iVar7] = 0x800;
                                            uVar2 = this->DAT_SomeX;
                                        }
                                    }
                                    this->DAT_SomeX = uVar2;
                                    this->DAT_SomeX = this->DAT_SomeX + 1;
                                    local_8 = local_8 + -1;
                                } while (local_8);
                                iVar8 = iVar8 + 1;
                            } while (iVar8 < 10);
                            iVar7 = 0;
                        }
                        local_14 = local_14 + 10;
                        iVar5 = iVar5 + 1;
                        iVar8 = iVar7;
                    } while (iVar5 <= this->someYLikeLimit);
                }
                local_10 = local_10 + 0x28;
                local_c = local_c + 10;
                iVar6 = iVar6 + 1;
            } while (iVar6 <= this->someLimit);
        }
        local_18 = DAT_PathFindingState::instance.mappingYRelated % 10;
        local_1c = this->someIndex;
        if (this->someIndex <= this->someLimit) {
            local_14 = this->someIndex * 10;
            local_10 = this->someIndex * 0x28 + 0x1f93438;
            do {
                local_20 = this->someYLike;
                if (this->someYLike <= this->someYLikeLimit) {
                    local_c = this->someYLike * 10;
                    do {
                        iVar7 = local_18;
                        if (*(char*)(local_10 + local_20) != '\0') {
                            local_18 = 0;
                            for (; iVar7 < 10; iVar7 = iVar7 + 1) {
                                this->DAT_SomeY = local_14 + iVar7;
                                this->DAT_SomeX = local_c;
                                local_8 = 10;
                                do {
                                    if ((((uint)this->DAT_SomeX < 400) && ((uint)this->DAT_SomeY < 400))
                                        && ((*(char*)(this->DAT_SomeY * 400 + 0x21aec98 + this->DAT_SomeX) != '\0'
                                            && ((this->DAT_SomeTile = this->DAT_SomeX
                                                    + DAT_ViewportRenderState::instance
                                                        .translationMatrix[this->DAT_SomeY]
                                                        .addXgetTile,
                                                this->MacroLayer[this->DAT_SomeTile] == 0x800
                                                    && ((this->LogicLayer[this->DAT_SomeTile]
                                                        & Map::LogicHelpers::L_SEA))))))) {
                                        uVar4 = this->RandomLayer[this->DAT_SomeTile];
                                        _someX = this->DAT_SomeTile
                                            - DAT_ViewportRenderState::instance.translationMatrix[this->DAT_SomeY]
                                                  .addXgetTile;
                                        iVar6 = 0;
                                        do {
                                            if (*(short*)((int)this
                                                    + (DAT_ViewportRenderState::instance
                                                              .translationMatrix[DAT_TerrainDefinedData::instance
                                                                                     .MacroLayerScanOffsets[iVar6]
                                                                                     .y
                                                                  + this->DAT_SomeY]
                                                              .addXgetTile
                                                          + DAT_TerrainDefinedData::instance
                                                              .MacroLayerScanOffsets[iVar6]
                                                              .x
                                                          + _someX)
                                                        * 2
                                                    + 0x33cab0)
                                                != 0x800) {
                                                if (iVar6 < 0x10)
                                                    goto LAB_004ff539;
                                                break;
                                            }
                                            iVar6 = iVar6 + 1;
                                        } while (iVar6 < 0x10);
                                        _upTo16 = 0;
                                        do {
                                            pXVar3 = DAT_TerrainDefinedData::instance.MacroLayerScanOffsets + _upTo16;
                                            pXVar1 = DAT_TerrainDefinedData::instance.MacroLayerScanOffsets + _upTo16;
                                            _upTo960 = _upTo16 << 6;
                                            _upTo16 = _upTo16 + 1;
                                            /*
                                              set MacroLayer
                                             */
                                            *(ushort*)((int)this
                                                + (DAT_ViewportRenderState::instance
                                                          .translationMatrix[pXVar3->y + this->DAT_SomeY]
                                                          .addXgetTile
                                                      + pXVar1->x + _someX)
                                                    * 2
                                                + 0x33cab0) = (ushort)(byte)uVar4 * 0x1000 + 0x10 + (short)_upTo960;
                                        } while (_upTo16 < 0x10);
                                    }
                                LAB_004ff539:
                                    this->DAT_SomeX = this->DAT_SomeX + 1;
                                    local_8 = local_8 + -1;
                                } while (local_8);
                            }
                        }
                        local_c = local_c + 10;
                        local_20 = local_20 + 1;
                    } while (local_20 <= this->someYLikeLimit);
                }
                local_10 = local_10 + 0x28;
                local_14 = local_14 + 10;
                local_1c = local_1c + 1;
            } while (local_1c <= this->someLimit);
        }
        iVar7 = DAT_PathFindingState::instance.mappingYRelated % 10;
        if (this->someIndex <= this->someLimit) {
            local_14 = this->someIndex * 10;
            local_10 = this->someIndex * 0x28 + 0x1f93438;
            iVar6 = this->someIndex;
            do {
                if (this->someYLike <= this->someYLikeLimit) {
                    local_c = this->someYLike * 10;
                    iVar5 = this->someYLike;
                    iVar8 = iVar7;
                    do {
                        iVar7 = iVar8;
                        if ((*(char*)(local_10 + iVar5) != '\0') && (iVar7 = 0, iVar8 < 10)) {
                            do {
                                this->DAT_SomeY = local_14 + iVar8;
                                this->DAT_SomeX = local_c;
                                local_8 = 2;
                                do {
                                    if (((((uint)this->DAT_SomeX < 400) && ((uint)this->DAT_SomeY < 400))
                                            && (*(char*)(this->DAT_SomeY * 400 + 0x21aec98 + this->DAT_SomeX) != '\0'))
                                        && (this->DAT_SomeTile
                                            = DAT_ViewportRenderState::instance.translationMatrix[this->DAT_SomeY]
                                                    .addXgetTile
                                                + this->DAT_SomeX,
                                            this->MacroLayer[this->DAT_SomeTile] == 0x800)) {
                                        this->MacroLayer[this->DAT_SomeTile] = 2;
                                    }
                                    uVar2 = this->DAT_SomeX + 1;
                                    if (((uVar2 < 400) && ((uint)this->DAT_SomeY < 400))
                                        && (*(char*)(this->DAT_SomeY * 400 + 0x21aec98 + uVar2) != '\0')) {
                                        iVar7 = DAT_ViewportRenderState::instance.translationMatrix[this->DAT_SomeY]
                                                    .addXgetTile;
                                        this->DAT_SomeTile = iVar7 + uVar2;
                                        if (this->MacroLayer[this->DAT_SomeX + iVar7 + 1] == 0x800) {
                                            iVar7 = this->DAT_SomeX + iVar7 + 1;
                                            this->DAT_SomeX = uVar2;
                                            this->MacroLayer[iVar7] = 2;
                                            uVar2 = this->DAT_SomeX;
                                        }
                                    }
                                    this->DAT_SomeX = uVar2;
                                    uVar2 = this->DAT_SomeX + 1;
                                    if (((uVar2 < 400) && ((uint)this->DAT_SomeY < 400))
                                        && (*(char*)(this->DAT_SomeY * 400 + 0x21aec98 + uVar2) != '\0')) {
                                        iVar7 = DAT_ViewportRenderState::instance.translationMatrix[this->DAT_SomeY]
                                                    .addXgetTile;
                                        this->DAT_SomeTile = iVar7 + uVar2;
                                        if (this->MacroLayer[this->DAT_SomeX + iVar7 + 1] == 0x800) {
                                            iVar7 = this->DAT_SomeX + iVar7 + 1;
                                            this->DAT_SomeX = uVar2;
                                            this->MacroLayer[iVar7] = 2;
                                            uVar2 = this->DAT_SomeX;
                                        }
                                    }
                                    this->DAT_SomeX = uVar2;
                                    uVar2 = this->DAT_SomeX + 1;
                                    if (((uVar2 < 400) && ((uint)this->DAT_SomeY < 400))
                                        && (*(char*)(this->DAT_SomeY * 400 + 0x21aec98 + uVar2) != '\0')) {
                                        iVar7 = DAT_ViewportRenderState::instance.translationMatrix[this->DAT_SomeY]
                                                    .addXgetTile;
                                        this->DAT_SomeTile = iVar7 + uVar2;
                                        if (this->MacroLayer[this->DAT_SomeX + iVar7 + 1] == 0x800) {
                                            iVar7 = this->DAT_SomeX + iVar7 + 1;
                                            this->DAT_SomeX = uVar2;
                                            this->MacroLayer[iVar7] = 2;
                                            uVar2 = this->DAT_SomeX;
                                        }
                                    }
                                    this->DAT_SomeX = uVar2;
                                    uVar2 = this->DAT_SomeX + 1;
                                    if (((uVar2 < 400) && ((uint)this->DAT_SomeY < 400))
                                        && (*(char*)(this->DAT_SomeY * 400 + 0x21aec98 + uVar2) != '\0')) {
                                        iVar7 = DAT_ViewportRenderState::instance.translationMatrix[this->DAT_SomeY]
                                                    .addXgetTile;
                                        this->DAT_SomeTile = iVar7 + uVar2;
                                        if (this->MacroLayer[this->DAT_SomeX + iVar7 + 1] == 0x800) {
                                            iVar7 = this->DAT_SomeX + iVar7 + 1;
                                            this->DAT_SomeX = uVar2;
                                            this->MacroLayer[iVar7] = 2;
                                            uVar2 = this->DAT_SomeX;
                                        }
                                    }
                                    this->DAT_SomeX = uVar2;
                                    this->DAT_SomeX = this->DAT_SomeX + 1;
                                    local_8 = local_8 + -1;
                                } while (local_8);
                                iVar8 = iVar8 + 1;
                            } while (iVar8 < 10);
                            iVar7 = 0;
                        }
                        local_c = local_c + 10;
                        iVar5 = iVar5 + 1;
                        iVar8 = iVar7;
                    } while (iVar5 <= this->someYLikeLimit);
                }
                local_10 = local_10 + 0x28;
                local_14 = local_14 + 10;
                iVar6 = iVar6 + 1;
            } while (iVar6 <= this->someLimit);
        }
    }

}
}
