
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/GMFirstPictureIndex.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Game::GameMode2;
    using OpenSHC::Map::Buildings::BuildingType;

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
        int buildingXPos = (short)DAT_BuildingsState::instance.buildings[buildingID].x;
        int buildingYPos = (short)DAT_BuildingsState::instance.buildings[buildingID].y;
        int index = 0;
        DAT_BuildingsState::instance.buildings[buildingID].usesGfxOffsetLayer = 0;
        if (this->fullHeightViewActive == 0 && DAT_BuildingsState::instance.buildings[buildingID].gfxOffset != 0) {
            DAT_BuildingsState::instance.buildings[buildingID].usesGfxOffsetLayer = 1;
        }
        int stored = DAT_BuildingsState::instance.buildings[buildingID].currentNumberOfResource
            - (int)DAT_BuildingsState::instance.buildings[buildingID].pendingResourceLossPreview;

        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                index, DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight);
            int tile
                = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + buildingYPos].addXgetTile
                + buildingXPos + this->buildingX;
            if (this->flatViewMode != 0) {
                /* the placement overlay replaces every building graphic with its outline */
                short outline = (short)DAT_TerrainDefinedData::instance
                                    .BrushSizeArray[DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight + 7]
                    + (short)this->rotatedFootprintPieceIndex + (short)GMFirstPictureIndex::instance[0x9d] - 1;
                this->overlayImageOrStockpileIdLayer[tile] = 0;
                this->GfxLayer[tile] = outline;
            } else if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                    == OpenSHC::Map::Buildings::BT_STOCKPILE
                || DAT_BuildingsState::instance.buildings[buildingID].buildingType
                    == OpenSHC::Map::Buildings::BT_QUARRYSTOCKPILE) {
                /* a stockpile's pile grows with what is stored on it */
                if (stored > 0) {
                    int resource = DAT_BuildingsState::instance.buildings[buildingID].currentStoredResourceType;
                    int gfxBase = DAT_TerrainDefinedData::instance.stockpileResourceGfxBase[resource];
                    int pile;
                    if (DAT_TerrainDefinedData::instance.stockpilePileStyle[resource] == 2) {
                        int remaining
                            = DAT_BuildingsState::instance.buildings[buildingID].currentLimitOfResource - stored;
                        pile = this->rotatedFootprintPieceIndex + (remaining / 4 + (remaining & 3) * 0xc) * 4;
                    } else if (DAT_TerrainDefinedData::instance.stockpilePileStyle[resource] != 0) {
                        pile = this->rotatedFootprintPieceIndex
                            + (DAT_BuildingsState::instance.buildings[buildingID].currentLimitOfResource - stored) * 4;
                    } else {
                        pile = this->rotatedFootprintPieceIndex + stored * 4 - 4;
                    }
                    this->GfxLayer[tile] = GMFirstPictureIndex::instance[0xf] + gfxBase + pile - 1;
                } else {
                    this->GfxLayer[tile] = (short)this->rotatedFootprintPieceIndex
                        + (short)GMFirstPictureIndex::instance[0xf] + 4;
                }
            } else if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                    == OpenSHC::Map::Buildings::BT_MERCENARYPOST
                || DAT_BuildingsState::instance.buildings[buildingID].buildingType
                    == OpenSHC::Map::Buildings::BT_BARRACKS
                || DAT_BuildingsState::instance.buildings[buildingID].buildingType
                    == OpenSHC::Map::Buildings::BT_OUTPOST_EUROPEAN) {
                this->GfxLayer[tile] = ((short)GMFirstPictureIndex::instance
                                               [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                                           + (short)DAT_BuildingsState::instance.buildings[buildingID].spriteID
                                           + (short)this->rotatedFootprintPieceIndex)
                    - 1;
            } else if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                    == OpenSHC::Map::Buildings::BT_KEEPDOOR_LEFT
                || DAT_BuildingsState::instance.buildings[buildingID].buildingType
                    == OpenSHC::Map::Buildings::BT_KEEPDOOR_RIGHT) {
                /* a side door faces along the keep's axis, so its graphic follows the map rotation */
                uint facing = this->mapOrientation;
                if (DAT_BuildingsState::instance.buildings[buildingID].orientation == 6
                    || DAT_BuildingsState::instance.buildings[buildingID].orientation == 2) {
                    facing = (this->mapOrientation + 2) % 8;
                }
                if (DAT_BuildingsState::instance.buildings[buildingID].usesGfxOffsetLayer != 0) {
                    if (facing != 2 && facing != 6) {
                        this->GfxLayer[tile]
                            = ((short)GMFirstPictureIndex::instance
                                      [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                                  + (short)DAT_BuildingsState::instance.buildings[buildingID].gfxOffset)
                            - 1;
                    } else {
                        this->GfxLayer[tile] = (short)GMFirstPictureIndex::instance
                                                   [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                            + (short)DAT_BuildingsState::instance.buildings[buildingID].gfxOffset;
                    }
                } else if (facing != 2 && facing != 6) {
                    this->GfxLayer[tile]
                        = ((short)GMFirstPictureIndex::instance
                                  [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                              + (short)DAT_BuildingsState::instance.buildings[buildingID]
                                  .spriteFrameOffset
                              + (short)DAT_BuildingsState::instance.buildings[buildingID].spriteID)
                        - 1;
                } else {
                    this->GfxLayer[tile]
                        = (short)GMFirstPictureIndex::instance
                              [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                        + (short)DAT_BuildingsState::instance.buildings[buildingID]
                              .spriteFrameOffset
                        + (short)DAT_BuildingsState::instance.buildings[buildingID].spriteID;
                }
            } else if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                == OpenSHC::Map::Buildings::BT_KEEPDOOR) {
                if (DAT_BuildingsState::instance.buildings[buildingID].usesGfxOffsetLayer != 0) {
                    this->GfxLayer[tile]
                        = ((short)GMFirstPictureIndex::instance
                                  [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                              + (short)DAT_BuildingsState::instance.buildings[buildingID]
                                  .spriteFrameOffset
                              + (short)DAT_BuildingsState::instance.buildings[buildingID].gfxOffset)
                        - 1;
                } else {
                    if (this->mapOrientation != 2 && this->mapOrientation != 6) {
                        this->GfxLayer[tile]
                            = ((short)GMFirstPictureIndex::instance
                                      [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                                  + (short)DAT_BuildingsState::instance.buildings[buildingID]
                                      .spriteFrameOffset
                                  + (short)DAT_BuildingsState::instance.buildings[buildingID].spriteID)
                            - 1;
                    } else {
                        this->GfxLayer[tile]
                            = (short)GMFirstPictureIndex::instance
                                  [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                            + (short)DAT_BuildingsState::instance.buildings[buildingID]
                                  .spriteFrameOffset
                            + (short)DAT_BuildingsState::instance.buildings[buildingID].spriteID;
                    }
                }
            } else if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                    == OpenSHC::Map::Buildings::BT_GATEHOUSELARGE
                || DAT_BuildingsState::instance.buildings[buildingID].buildingType
                    == OpenSHC::Map::Buildings::BT_GATEHOUSESMALL
                || DAT_BuildingsState::instance.buildings[buildingID].buildingType
                    == OpenSHC::Map::Buildings::BT_WOODGATE1) {
                int variation;
                if (this->mapOrientation == 2 || this->mapOrientation == 6) {
                    variation = (DAT_BuildingsState::instance.buildings[buildingID].buildingVariation == 0x50) + 0x50;
                } else {
                    variation = DAT_BuildingsState::instance.buildings[buildingID].buildingVariation;
                }
                if (DAT_BuildingsState::instance.buildings[buildingID].usesGfxOffsetLayer != 0) {
                    if (variation != 0x50) {
                        this->GfxLayer[tile]
                            = ((short)GMFirstPictureIndex::instance
                                      [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                                  + (short)DAT_BuildingsState::instance.buildings[buildingID].gfxOffset3
                                  + (short)this->rotatedFootprintPieceIndex)
                            - 1;
                    } else {
                        this->GfxLayer[tile]
                            = (((short)GMFirstPictureIndex::instance
                                       [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                                   + (short)DAT_BuildingsState::instance.buildings[buildingID].gfxOffset)
                                  + (short)this->rotatedFootprintPieceIndex)
                            - 1;
                    }
                } else if (variation != 0x50) {
                    this->GfxLayer[tile]
                        = (((short)GMFirstPictureIndex::instance
                                   [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                               + (short)DAT_BuildingsState::instance.buildings[buildingID].gfxOffset2)
                              + (short)this->rotatedFootprintPieceIndex)
                        - 1;
                } else {
                    this->GfxLayer[tile]
                        = ((short)GMFirstPictureIndex::instance
                                  [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                              + (short)DAT_BuildingsState::instance.buildings[buildingID].spriteID
                              + (short)this->rotatedFootprintPieceIndex)
                        - 1;
                }
            } else if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                == OpenSHC::Map::Buildings::BT_MANORHOUSE) {
                int variation;
                if (this->mapOrientation == 2 || this->mapOrientation == 6) {
                    variation = 0x51;
                } else {
                    variation = 0x50;
                }
                if (DAT_BuildingsState::instance.buildings[buildingID].usesGfxOffsetLayer != 0) {
                    if (variation == 0x50) {
                        this->GfxLayer[tile]
                            = (((short)GMFirstPictureIndex::instance
                                       [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                                   + (short)DAT_BuildingsState::instance.buildings[buildingID].gfxOffset)
                                  + (short)this->rotatedFootprintPieceIndex)
                            - 1;
                    } else {
                        this->GfxLayer[tile]
                            = (short)GMFirstPictureIndex::instance
                                  [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                            + (short)this->rotatedFootprintPieceIndex + 0x298;
                    }
                } else if (variation == 0x50) {
                    this->GfxLayer[tile]
                        = ((short)GMFirstPictureIndex::instance
                                  [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                              + (short)DAT_BuildingsState::instance.buildings[buildingID].spriteID
                              + (short)this->rotatedFootprintPieceIndex)
                        - 1;
                } else {
                    this->GfxLayer[tile] = (short)GMFirstPictureIndex::instance
                                               [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                        + (short)this->rotatedFootprintPieceIndex + 0x236;
                }
            } else if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                == OpenSHC::Map::Buildings::BT_DRAWBRIDGE) {
                int plank
                    = DAT_TerrainDefinedData::instance
                          .drawbridgeTileFramesByRot[(int)DAT_BuildingsState::instance.buildings[buildingID].buildingVariation
                              / 2][index];
                if (plank != 0) {
                    this->GfxLayer[tile] = (short)GMFirstPictureIndex::instance
                                               [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                        + (short)plank + 0x61e;
                } else if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::returnOwnedMoatAtTile, this)(tile) != 0) {
                    this->GfxLayer[tile] = (this->RandomLayer[tile] & 3)
                        + (this->LuminesenceLayer[tile] + 0x33) * 4 + (short)GMFirstPictureIndex::instance[5];
                } else {
                    this->GfxLayer[tile] = (this->RandomLayer[tile] & 3)
                        + (ushort)this->LuminesenceLayer[tile] * 4 + (short)GMFirstPictureIndex::instance[2];
                }
            } else if ((DAT_BuildingsState::instance.buildings[buildingID].buildingType
                               != OpenSHC::Map::Buildings::BT_KILLINGPIT
                           || DAT_BuildingsState::instance.buildings[buildingID].state > 0
                           || DAT_GameState::instance.mapAndTime
                                   .playerTeams[DAT_BuildingsState::instance.buildings[buildingID].owner]
                               == DAT_GameState::instance.mapAndTime
                                   .playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                           || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                && DAT_BuildingsState::instance.buildings[buildingID].buildingType
                    != OpenSHC::Map::Buildings::BT_SIEGETOWER_PLACED) {
                /* a killing pit is invisible to anyone not on the owner's team */
                if (DAT_BuildingsState::instance.buildings[buildingID].buildingVariation != 0xf) {
                    int variation = DAT_BuildingsState::instance.buildings[buildingID].buildingVariation;
                    int rotation = variation - this->mapOrientation;
                    if (rotation < 0) {
                        rotation = rotation + 8;
                    }
                    int span;
                    if (DAT_BuildingsState::instance.buildings[buildingID].buildingVariation == 8) {
                        rotation = DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight;
                        span = variation * rotation;
                    } else {
                        span = DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight
                            * DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight;
                    }
                    span = span * rotation;
                    if (DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive != 0) {
                        this->GfxLayer[tile]
                            = ((short)GMFirstPictureIndex::instance
                                      [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                                  + (short)DAT_BuildingsState::instance.buildings[buildingID].visuallyActiveSpriteID
                                  + (short)this->rotatedFootprintPieceIndex + (short)span)
                            - 1;
                    } else {
                        this->GfxLayer[tile]
                            = ((short)GMFirstPictureIndex::instance
                                      [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                                  + (short)DAT_BuildingsState::instance.buildings[buildingID].spriteID
                                  + (short)this->rotatedFootprintPieceIndex + (short)span)
                            - 1;
                    }
                    this->overlayImageOrStockpileIdLayer[tile]
                        = ((short)GMFirstPictureIndex::instance
                                  [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                              + (short)DAT_BuildingsState::instance.buildings[buildingID].spriteID
                              + (short)this->rotatedFootprintPieceIndex + (short)span)
                        - 1;
                } else {
                    if (DAT_BuildingsState::instance.buildings[buildingID].usesGfxOffsetLayer != 0) {
                        this->GfxLayer[tile]
                            = ((short)GMFirstPictureIndex::instance
                                      [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                                  + (short)DAT_BuildingsState::instance.buildings[buildingID].gfxOffset
                                  + (short)this->rotatedFootprintPieceIndex)
                            - 1;
                    } else if (DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive != 0) {
                        this->GfxLayer[tile]
                            = ((short)GMFirstPictureIndex::instance
                                      [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                                  + (short)DAT_BuildingsState::instance.buildings[buildingID].visuallyActiveSpriteID
                                  + (short)this->rotatedFootprintPieceIndex)
                            - 1;
                    } else {
                        this->GfxLayer[tile]
                            = ((short)GMFirstPictureIndex::instance
                                      [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                                  + (short)DAT_BuildingsState::instance.buildings[buildingID]
                                      .spriteFrameOffset
                                  + (short)DAT_BuildingsState::instance.buildings[buildingID].spriteID
                                  + (short)this->rotatedFootprintPieceIndex)
                            - 1;
                    }
                    this->overlayImageOrStockpileIdLayer[tile]
                        = ((short)GMFirstPictureIndex::instance
                                  [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                              + (short)DAT_BuildingsState::instance.buildings[buildingID]
                                  .spriteFrameOffset
                              + (short)DAT_BuildingsState::instance.buildings[buildingID].spriteID
                              + (short)this->rotatedFootprintPieceIndex)
                        - 1;
                }
            }
            index++;
        } while (index < this->constructionTileCount);
    }

}
}
