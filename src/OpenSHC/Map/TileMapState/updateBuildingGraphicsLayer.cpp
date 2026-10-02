#include "../../Map.func.hpp"

#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/GMTotalPicturesProcessed.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeShort.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Game::GameMode2;
    using OpenSHC::Map::Buildings::BuildingType;
    using OpenSHC::Map::Buildings::BuildingTypeShort;

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
    // FUNCTION: STRONGHOLDCRUSADER 0x00506370
    void TileMapState::updateBuildingGraphicsLayer(int buildingID)
    {
        ushort uVar1;
        ushort uVar2;
        BuildingTypeShort BVar3;
        short sVar4;
        short sVar5;
        short sVar6;
        int iVar7;
        int iVar8;
        uint uVar9;
        ushort uVar10;
        int targetedTile;
        int local_c;
        uVar1 = DAT_BuildingsState::instance.buildings[buildingID].x;
        uVar2 = DAT_BuildingsState::instance.buildings[buildingID].y;
        DAT_BuildingsState::instance.buildings[buildingID].field62_0xb0 = 0;
        local_c = 0;
        if ((this->refreshRelatedOne == 0) && (DAT_BuildingsState::instance.buildings[buildingID].gfxOffset != 0)) {
            DAT_BuildingsState::instance.buildings[buildingID].field62_0xb0 = 1;
        }
        iVar7 = DAT_BuildingsState::instance.buildings[buildingID].currentNumberOfResource
            - (int)DAT_BuildingsState::instance.buildings[buildingID].someResourceNumber;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                local_c, (int)((int)(DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight)));
            targetedTile
                = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + (short)uVar2].addXgetTile
                + (int)(short)uVar1 + this->buildingX;
            if (this->field93_0x5548c8 == 0) {
                BVar3 = DAT_BuildingsState::instance.buildings[buildingID].buildingType;
                if ((BVar3 == OpenSHC::Map::Buildings::BT_STOCKPILE)
                    || (BVar3 == OpenSHC::Map::Buildings::BT_QUARRYSTOCKPILE)) {
                    if (iVar7 < 1) {
                        uVar10 = (short)this->buildingRotationRelatedValue
                            + (short)GMTotalPicturesProcessed::instance[0xf] + 4;
                        goto LAB_00506aa2;
                    }
                    sVar5 = DAT_BuildingsState::instance.buildings[buildingID].currentStoredResourceType;
                    if (DAT_TerrainDefinedData::instance.field1001_0x8b4[sVar5] == 2) {
                        iVar8 = DAT_BuildingsState::instance.buildings[buildingID].currentLimitOfResource - iVar7;
                        sVar6 = (short)this->buildingRotationRelatedValue
                            + ((short)((int)(iVar8 + (iVar8 >> 0x1f & 3U)) >> 2) + ((ushort)iVar8 & 3) * 0xc) * 4;
                    } else if (DAT_TerrainDefinedData::instance.field1001_0x8b4[sVar5] == 0) {
                        sVar6 = (short)this->buildingRotationRelatedValue + -4 + (short)iVar7 * 4;
                    } else {
                        sVar6 = (short)this->buildingRotationRelatedValue
                            + ((short)DAT_BuildingsState::instance.buildings[buildingID].currentLimitOfResource
                                  - (short)iVar7)
                                * 4;
                    }
                    this->GfxLayer[targetedTile] = (short)GMTotalPicturesProcessed::instance[0xf]
                        + (short)DAT_TerrainDefinedData::instance.field996_0x84c[sVar5] + -1 + sVar6;
                } else if (((BVar3 == OpenSHC::Map::Buildings::BT_MERCENARYPOST)
                               || (BVar3 == OpenSHC::Map::Buildings::BT_BARRACKS))
                    || (BVar3 == OpenSHC::Map::Buildings::BT_OUTPOST_EUROPEAN)) {
                LAB_005065bd:
                    this->GfxLayer[targetedTile]
                        = ((short)GMTotalPicturesProcessed::instance
                                  [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                              + (short)DAT_BuildingsState::instance.buildings[buildingID].spriteID
                              + (short)this->buildingRotationRelatedValue)
                        - 1;
                } else if ((BVar3 == OpenSHC::Map::Buildings::BT_KEEPDOOR_LEFT)
                    || (BVar3 == OpenSHC::Map::Buildings::BT_KEEPDOOR_RIGHT)) {
                    sVar5 = DAT_BuildingsState::instance.buildings[buildingID].orientation;
                    if (((sVar5 == 6) || (uVar9 = this->mapOrientation, sVar5 == 2))
                        && (uVar9 = this->mapOrientation + 2U & 0x80000007, (int)uVar9 < 0)) {
                        uVar9 = (uVar9 - 1 | 0xfffffff8) + 1;
                    }
                    if (DAT_BuildingsState::instance.buildings[buildingID].field62_0xb0 == 0) {
                        if ((uVar9 == 2) || (uVar9 == 6)) {
                            uVar10 = (short)GMTotalPicturesProcessed::instance
                                         [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                                + (short)DAT_BuildingsState::instance.buildings[buildingID]
                                      .unknownManorHouseOrStoneKeepRelated
                                + (short)DAT_BuildingsState::instance.buildings[buildingID].spriteID;
                            goto LAB_00506aa2;
                        }
                        this->GfxLayer[targetedTile]
                            = ((short)GMTotalPicturesProcessed::instance
                                      [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                                  + (short)DAT_BuildingsState::instance.buildings[buildingID]
                                      .unknownManorHouseOrStoneKeepRelated
                                  + (short)DAT_BuildingsState::instance.buildings[buildingID].spriteID)
                            - 1;
                    } else if ((uVar9 == 2) || (uVar9 == 6)) {
                        this->GfxLayer[targetedTile]
                            = (short)GMTotalPicturesProcessed::instance
                                  [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                            + (short)DAT_BuildingsState::instance.buildings[buildingID].gfxOffset;
                    } else {
                        uVar10 = ((short)GMTotalPicturesProcessed::instance
                                         [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                                     + (short)DAT_BuildingsState::instance.buildings[buildingID].gfxOffset)
                            - 1;
                    LAB_00506aa2:
                        this->GfxLayer[targetedTile] = uVar10;
                    }
                } else if (BVar3 == OpenSHC::Map::Buildings::BT_KEEPDOOR) {
                    if (DAT_BuildingsState::instance.buildings[buildingID].field62_0xb0 == 0) {
                        if ((this->mapOrientation != 2) && (this->mapOrientation != 6)) {
                            uVar10 = ((short)GMTotalPicturesProcessed::instance
                                             [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                                         + (short)DAT_BuildingsState::instance.buildings[buildingID]
                                             .unknownManorHouseOrStoneKeepRelated
                                         + (short)DAT_BuildingsState::instance.buildings[buildingID].spriteID)
                                - 1;
                            goto LAB_00506aa2;
                        }
                        this->GfxLayer[targetedTile]
                            = (short)GMTotalPicturesProcessed::instance
                                  [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                            + (short)DAT_BuildingsState::instance.buildings[buildingID]
                                  .unknownManorHouseOrStoneKeepRelated
                            + (short)DAT_BuildingsState::instance.buildings[buildingID].spriteID;
                    } else {
                        this->GfxLayer[targetedTile]
                            = ((short)GMTotalPicturesProcessed::instance
                                      [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                                  + (short)DAT_BuildingsState::instance.buildings[buildingID]
                                      .unknownManorHouseOrStoneKeepRelated
                                  + (short)DAT_BuildingsState::instance.buildings[buildingID].gfxOffset)
                            - 1;
                    }
                } else if (((BVar3 == OpenSHC::Map::Buildings::BT_GATEHOUSELARGE)
                               || (BVar3 == OpenSHC::Map::Buildings::BT_GATEHOUSESMALL))
                    || (BVar3 == OpenSHC::Map::Buildings::BT_WOODGATE1)) {
                    if ((this->mapOrientation == 2) || (this->mapOrientation == 6)) {
                        iVar8 = (DAT_BuildingsState::instance.buildings[buildingID].buildingVariation == 0x50) + 0x50;
                    } else {
                        iVar8 = (int)DAT_BuildingsState::instance.buildings[buildingID].buildingVariation;
                    }
                    if (DAT_BuildingsState::instance.buildings[buildingID].field62_0xb0 == 0) {
                        if (iVar8 == 0x50)
                            goto LAB_005065bd;
                        sVar5 = (short)GMTotalPicturesProcessed::instance
                                    [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                            + (short)DAT_BuildingsState::instance.buildings[buildingID].gfxOffset2;
                    } else {
                        if (iVar8 != 0x50) {
                            uVar10 = ((short)GMTotalPicturesProcessed::instance
                                             [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                                         + (short)DAT_BuildingsState::instance.buildings[buildingID].gfxOffset3
                                         + (short)this->buildingRotationRelatedValue)
                                - 1;
                            goto LAB_00506aa2;
                        }
                    LAB_0050657d:
                        sVar5 = (short)GMTotalPicturesProcessed::instance
                                    [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                            + (short)DAT_BuildingsState::instance.buildings[buildingID].gfxOffset;
                    }
                    this->GfxLayer[targetedTile] = (sVar5 + (short)this->buildingRotationRelatedValue) - 1;
                } else if (BVar3 == OpenSHC::Map::Buildings::BT_MANORHOUSE) {
                    if ((this->mapOrientation == 2) || (iVar8 = 0x50, this->mapOrientation == 6)) {
                        iVar8 = 0x51;
                    }
                    if (DAT_BuildingsState::instance.buildings[buildingID].field62_0xb0 != 0) {
                        if (iVar8 == 0x50)
                            goto LAB_0050657d;
                        uVar10 = (short)GMTotalPicturesProcessed::instance
                                     [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                            + (short)this->buildingRotationRelatedValue + 0x298;
                        goto LAB_00506aa2;
                    }
                    if (iVar8 == 0x50)
                        goto LAB_005065bd;
                    this->GfxLayer[targetedTile]
                        = (short)GMTotalPicturesProcessed::instance
                              [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                        + (short)this->buildingRotationRelatedValue + 0x236;
                } else if (BVar3 == OpenSHC::Map::Buildings::BT_DRAWBRIDGE) {
                    iVar8
                        = DAT_TerrainDefinedData::instance.field2467_0x1fec
                              [(int)DAT_BuildingsState::instance.buildings[buildingID].buildingVariation / 2][local_c];
                    if (iVar8 == 0) {
                        iVar8 = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::returnOwnedMoatAtTile, this)(
                            targetedTile);
                        if (iVar8 == 0) {
                            this->GfxLayer[targetedTile] = ((byte)this->RandomLayer[targetedTile] & 3)
                                + (ushort)this->LuminesenceLayer[targetedTile] * 4
                                + (short)GMTotalPicturesProcessed::instance[2];
                        } else {
                            this->GfxLayer[targetedTile] = ((byte)this->RandomLayer[targetedTile] & 3)
                                + (this->LuminesenceLayer[targetedTile] + 0x33) * 4
                                + (short)GMTotalPicturesProcessed::instance[5];
                        }
                    } else {
                        this->GfxLayer[targetedTile]
                            = (short)GMTotalPicturesProcessed::instance
                                  [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                            + (short)iVar8 + 0x61e;
                    }
                } else if ((((BVar3 != OpenSHC::Map::Buildings::BT_KILLINGPIT)
                                || (0 < DAT_BuildingsState::instance.buildings[buildingID].state))
                               || ((DAT_GameState::instance.mapAndTime
                                           .playerTeams[DAT_BuildingsState::instance.buildings[buildingID].owner]
                                       == DAT_GameState::instance.mapAndTime
                                           .playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                   || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR))))
                    && (BVar3 != OpenSHC::Map::Buildings::BT_SIEGETOWER_PLACED)) {
                    sVar5 = DAT_BuildingsState::instance.buildings[buildingID].buildingVariation;
                    if (sVar5 == 0xf) {
                        if (DAT_BuildingsState::instance.buildings[buildingID].field62_0xb0 == 0) {
                            if (DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive == 0) {
                                this->GfxLayer[targetedTile]
                                    = ((short)GMTotalPicturesProcessed::instance
                                              [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                                          + (short)DAT_BuildingsState::instance.buildings[buildingID]
                                              .unknownManorHouseOrStoneKeepRelated
                                          + (short)DAT_BuildingsState::instance.buildings[buildingID].spriteID
                                          + (short)this->buildingRotationRelatedValue)
                                    - 1;
                            } else {
                                this->GfxLayer[targetedTile]
                                    = ((short)GMTotalPicturesProcessed::instance
                                              [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                                          + (short)DAT_BuildingsState::instance.buildings[buildingID]
                                              .visuallyActiveSpriteID
                                          + (short)this->buildingRotationRelatedValue)
                                    - 1;
                            }
                        } else {
                            this->GfxLayer[targetedTile]
                                = ((short)GMTotalPicturesProcessed::instance
                                          [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                                      + (short)DAT_BuildingsState::instance.buildings[buildingID].gfxOffset
                                      + (short)this->buildingRotationRelatedValue)
                                - 1;
                        }
                        this->AlphaGFXLayer[targetedTile]
                            = ((short)GMTotalPicturesProcessed::instance
                                      [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                                  + (short)DAT_BuildingsState::instance.buildings[buildingID]
                                      .unknownManorHouseOrStoneKeepRelated
                                  + (short)DAT_BuildingsState::instance.buildings[buildingID].spriteID
                                  + (short)this->buildingRotationRelatedValue)
                            - 1;
                    } else {
                        iVar8 = sVar5 - this->mapOrientation;
                        if (iVar8 < 0) {
                            iVar8 = iVar8 + 8;
                        }
                        sVar6 = (short)iVar8;
                        if (sVar5 == 8) {
                            sVar6 = (short)DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight;
                            sVar5 = sVar6 * 8;
                        } else {
                            sVar5 = (short)DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight;
                            sVar5 = sVar5 * sVar5;
                        }
                        if (DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive == 0) {
                            sVar4 = (short)DAT_BuildingsState::instance.buildings[buildingID].spriteID;
                        } else {
                            sVar4 = (short)DAT_BuildingsState::instance.buildings[buildingID].visuallyActiveSpriteID;
                        }
                        this->GfxLayer[targetedTile]
                            = ((short)GMTotalPicturesProcessed::instance
                                      [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                                  + sVar4 + (short)this->buildingRotationRelatedValue + sVar5 * sVar6)
                            - 1;
                        this->AlphaGFXLayer[targetedTile]
                            = ((short)GMTotalPicturesProcessed::instance
                                      [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                                  + (short)DAT_BuildingsState::instance.buildings[buildingID].spriteID
                                  + (short)this->buildingRotationRelatedValue + sVar5 * sVar6)
                            - 1;
                    }
                }
            } else {
                sVar5 = (short)DAT_TerrainDefinedData::instance
                            .BrushSizeArray[DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight + 7]
                    + (short)this->buildingRotationRelatedValue + (short)GMTotalPicturesProcessed::instance[0x9d];
                this->AlphaGFXLayer[targetedTile] = 0;
                this->GfxLayer[targetedTile] = sVar5 - 1;
            }
            local_c = local_c + 1;
            if (this->constructionTileCount <= local_c) {}
        } while (true);
    }

}
}
