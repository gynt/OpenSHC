#include "../../Map.func.hpp"

#include "OpenSHC/Game.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/WallAndPitchState.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MinimapViewState.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeInt.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeShort.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_WallAndPitchState.hpp"

namespace OpenSHC {
namespace Map {

    using Commands::MappersEnum;
    using Game::GameMode;
    using Game::GameMode2;
    using Map::Buildings::BuildingType;
    using Map::Buildings::BuildingTypeInt;
    using Map::Buildings::BuildingTypeShort;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x005162D0
    void TileMapState::placeBuilding(
        PlayerID playerID, int x, int y, MappersEnum cbt, int buildingSize, int buildingOrientation)
    {
        int* piVar1;
        int yPosition_param;
        BuildingTypeShort _buildingType2;
        BuildingType _realBuildingType;
        BuildingType _buildingType_dup2;
        BOOLEnum BVar2;
        int iVar3;
        uint _height;
        BuildingTypeInt _buildingType_2;
        uint uVar4;
        MappersEnum _commandBuildingType;
        int _tile;
        int _averageHeight;
        int local_4;
        int _x;
        yPosition_param = y;
        _x = x;
        _commandBuildingType = (MappersEnum)(short)cbt;
        local_4 = 0;
        if (this->skipPlacementCheck == 0) {
            if (buildingOrientation == 0xf) {
                this->DAT_TempBuildingRotation = 0;
            } else {
                this->DAT_TempBuildingRotation = buildingOrientation / 2;
            }
            MACRO_CALL_MEMBER(Map::TileMapState_Func::checkBuildingCanBePlacedHere, this)(
                playerID, (uint)((int)(x)), (uint)((int)(y)), cbt, buildingSize);
            if (this->buildingPlacementFail != FALSE) {}
        }
        this->skipPlacementCheck = (Map::Buildings::BuildingType)(0);
        _realBuildingType
            = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::convertCommandBuildingTypeToBuildingType,
                DAT_BuildingsState::ptr)(_commandBuildingType);
        _buildingType_dup2 = (Map::Buildings::BuildingType)(_realBuildingType & 0xffff);
        _buildingType2 = (BuildingTypeShort)_realBuildingType;
        if (DAT_GameCore::instance.gameMode_2 == Game::GM_CRUSADER_TUTORIAL) {
            BVar2 = MACRO_CALL(Game_Func::Tutorial_IsActionAllowed)(2, (int)((int)((short)_buildingType2)));
            if (BVar2 == FALSE) {
                MACRO_CALL(UI::Helpers_Func::SetTutorialHintActiveWithTimestamp)();
            }
            MACRO_CALL(UI::Helpers_Func::SetTutorialBuildingActionState)(
                7, (BuildingType)((int)((int)(short)_buildingType2)));
        }
        y = 0;
        do {
            MACRO_CALL_MEMBER(Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(y, buildingSize);
            _tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + yPosition_param].addXgetTile
                + this->buildingX + x;
            if ((DAT_GameCore::instance.gameMode_2 == Game::GM_SIEGE_THAT)
                && ((this->LogicLayer[_tile] & 0x100U) != 0)) {
                piVar1 = DAT_GameState::instance.playerDataArray[playerID].startResources + 4;
                *piVar1 = *piVar1 + 1;
            }
            if (((this->LogicLayer[_tile] & 0x80) != 0) && (1999 < this->OrganismLayer[_tile])) {
                MACRO_CALL_MEMBER(Map::LandscapeState_Func::removeRock, DAT_LandscapeState::ptr)(
                    this->OrganismLayer[_tile] + -2000);
                MACRO_CALL_MEMBER(Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                    y, buildingSize);
                MACRO_CALL_MEMBER(
                    Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer, DAT_PathFindingState::ptr)(
                    8, (uint)((int)(this->buildingX + x)), (uint)((int)(this->buildingY + yPosition_param)));
            }
            this->LogicLayer[_tile] = this->LogicLayer[_tile] & 0xffbef4f7;
            this->HeightLayer[_tile] = this->DefaultHeightLayer[_tile];
            this->DamageLayer[_tile] = 0;
            if (((this->LogicLayer[_tile] & 0x1000U) != 0) && (iVar3 = (int)this->OrganismLayer[_tile], iVar3 < 2000)) {
                switch (DAT_LandscapeState::instance.trees[iVar3].treeType) {
                case ((TreeType)5):
                case ((TreeType)6):
                case ((TreeType)7):
                case ((TreeType)8):
                case ((TreeType)9):
                case ((TreeType)10):
                case ((TreeType)0xb):
                case ((TreeType)0xc):
                case ((TreeType)0xd):
                case ((TreeType)0xe):
                case ((TreeType)0x10):
                case ((TreeType)0x11):
                case ((TreeType)0x12):
                case ((TreeType)0x13):
                    MACRO_CALL_MEMBER(Map::LandscapeState_Func::removeTree, DAT_LandscapeState::ptr)(iVar3);
                    MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer,
                        DAT_PathFindingState::ptr)(3, (uint)((int)(x)), (uint)((int)(yPosition_param)));
                    break;
                default:
                    MACRO_CALL_MEMBER(Map::LandscapeState_Func::removeTree, DAT_LandscapeState::ptr)(iVar3);
                    MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer,
                        DAT_PathFindingState::ptr)(3, (uint)((int)(x)), (uint)((int)(yPosition_param)));
                }
                MACRO_CALL_MEMBER(Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                    y, buildingSize);
            }
            if ((int)(short)this->UnitLayer[_tile] != 0) {
                switch (_buildingType2) {
                case Map::Buildings::BT_GATEHOUSELARGE:
                case Map::Buildings::BT_GATEHOUSESMALL:
                case Map::Buildings::BT_DRAWBRIDGE:
                case Map::Buildings::BT_CAMPFIRE:
                case Map::Buildings::BT_PARADEGROUND:
                case Map::Buildings::BT_CAMPGROUND:
                case Map::Buildings::BT_PARADEGROUND2:
                case Map::Buildings::BT_PARADEGROUND3:
                case Map::Buildings::BT_PARADEGROUND4:
                case Map::Buildings::BT_PARADEGROUND5:
                case Map::Buildings::BT_KILLINGPIT:
                case Map::Buildings::BT_PITCHDITCH:
                case Map::Buildings::BT_SIEGETOWER_PLACED:
                case Map::Buildings::BT_TOWER1:
                case Map::Buildings::BT_TOWER2:
                case Map::Buildings::BT_TOWER3:
                case Map::Buildings::BT_TOWER4:
                case Map::Buildings::BT_TOWER5:
                    break;
                default:
                    MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::deleteUnit, DAT_UnitsState::ptr)(
                        (int)(short)this->UnitLayer[_tile]);
                }
            }
            if ((this->LogicLayer[_tile] & 0x40004000U) != 0) {
                MACRO_CALL_MEMBER(Map::TileMapState_Func::clearMoatDataAtTile, this)(
                    this->buildingX + x, this->buildingY + yPosition_param);
                this->LogicLayer[_tile] = this->LogicLayer[_tile] & 0xbfffbfff;
            }
            this->MiscDisplayLayer[_tile] = this->MiscDisplayLayer[_tile] & 0xfc3f;
            y = y + 1;
            DAT_PathFindingState::instance.toggleUpdateSeparateAreaTileMap = 1;
            this->field204_0x554a30 = 1;
        } while (y < this->constructionTileCount);
        iVar3 = 0;
        /*

                These parameters now become min and max height on the terrain covered by the   building
        */

        y = 1000;
        x = 0;
        do {
            MACRO_CALL_MEMBER(Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                iVar3, buildingSize);
            _height = (uint)this->HeightLayer[DAT_ViewportRenderState::instance
                                                  .translationMatrix[this->buildingY + yPosition_param]
                                                  .addXgetTile
                + this->buildingX + _x];
            if ((uint)x < _height) {
                x = _height;
            }
            if (_height < (uint)y) {
                y = _height;
            }
            iVar3 = iVar3 + 1;
        } while (iVar3 < this->constructionTileCount);
        _averageHeight = (x - y) / 2 + y;
        if ((_buildingType2 == Map::Buildings::BT_TUNNEL)
            && (playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID)) {
            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::playTunnelerCommandSpeech, DAT_TribesState::ptr)();
        }
        _buildingType_2 = (BuildingTypeInt)(short)_buildingType2;
        switch (_buildingType_2) {
        case Map::Buildings::BT_MERCENARYPOST:
        case Map::Buildings::BT_BARRACKS:
            MACRO_CALL_MEMBER(Map::TileMapState_Func::placeBarracks, this)(playerID, (uint)((int)(_x)),
                (int*)((int)(yPosition_param)), (undefined4)((int)(_buildingType_dup2)), (uint)((int)(buildingSize)),
                buildingOrientation, (undefined4)((int)(_averageHeight)));
            break;
        case Map::Buildings::BT_STOCKPILE:
            MACRO_CALL_MEMBER(Map::TileMapState_Func::placeStockpile, this)(playerID, _x, yPosition_param,
                (undefined4)((int)(_buildingType_dup2)), (undefined4)((int)(buildingSize)), buildingOrientation,
                _averageHeight);
            break;
        default:
            MACRO_CALL_MEMBER(Map::TileMapState_Func::placeWorkshopOrHovel, this)(playerID, (uint)((int)(_x)),
                (uint)((int)(yPosition_param)), _buildingType_dup2, (uint)((int)(buildingSize)), buildingOrientation,
                (undefined4)((int)(_averageHeight)));
            break;
        case Map::Buildings::BT_QUARRY:
            MACRO_CALL_MEMBER(Map::TileMapState_Func::placeQuarry, this)(playerID, (uint)((int)(_x)),
                (uint)((int)(yPosition_param)), (undefined4)((int)(_buildingType_dup2)), (uint)((int)(buildingSize)),
                buildingOrientation, (uint)((int)(_averageHeight)));
            break;
        case Map::Buildings::BT_ENGINEERSGUILD:
            MACRO_CALL_MEMBER(Map::TileMapState_Func::placeEngineersguild, this)(playerID, (int*)((int)(_x)),
                (uint)((int)(yPosition_param)), (undefined4)((int)(_buildingType_dup2)), (uint)((int)(buildingSize)),
                buildingOrientation, (undefined4)((int)(_averageHeight)));
            break;
        case Map::Buildings::BT_TUNNELERSGUILD:
            MACRO_CALL_MEMBER(Map::TileMapState_Func::placeTunnelersguild, this)(playerID, (int*)((int)(_x)),
                (uint)((int)(yPosition_param)), (undefined4)((int)(_buildingType_dup2)), (uint)((int)(buildingSize)),
                buildingOrientation, (undefined4)((int)(_averageHeight)));
            break;
        case Map::Buildings::BT_OILSMELTER:
            MACRO_CALL_MEMBER(Map::TileMapState_Func::placeOilsmelter, this)(playerID, (uint)((int)(_x)),
                (uint)((int)(yPosition_param)), (undefined4)((int)(_buildingType_dup2)), (uint)((int)(buildingSize)),
                buildingOrientation, (undefined4)((int)(_averageHeight)));
            break;
        case Map::Buildings::BT_WHEATFARM:
            MACRO_CALL_MEMBER(Map::TileMapState_Func::placeWheatfarm, this)(playerID, (uint)((int)(_x)),
                (uint)((int)(yPosition_param)), (undefined4)((int)(_buildingType_dup2)),
                (undefined4)((int)(buildingSize)), buildingOrientation, (undefined4)((int)(_averageHeight)));
            break;
        case Map::Buildings::BT_HOPFARM:
            MACRO_CALL_MEMBER(Map::TileMapState_Func::placeHopfarm, this)(playerID, (uint)((int)(_x)),
                (uint)((int)(yPosition_param)), (undefined4)((int)(_buildingType_dup2)),
                (undefined4)((int)(buildingSize)), buildingOrientation, _averageHeight);
            break;
        case Map::Buildings::BT_APPLEFARM:
            MACRO_CALL_MEMBER(Map::TileMapState_Func::placeApplefarm, this)(playerID, (uint)((int)(_x)),
                (uint)((int)(yPosition_param)), _buildingType_dup2, (undefined4)((int)(buildingSize)),
                buildingOrientation, (int*)((int)(_averageHeight)));
            break;
        case Map::Buildings::BT_DAIRYFARM:
            MACRO_CALL_MEMBER(Map::TileMapState_Func::placeDairyfarm, this)(playerID, (uint)((int)(_x)),
                (uint)((int)(yPosition_param)), (undefined4)((int)(_buildingType_dup2)),
                (undefined4)((int)(buildingSize)), (int*)((int)(buildingOrientation)),
                (undefined4)((int)(_averageHeight)));
            break;
        case Map::Buildings::BT_UNKNOWN1:
            MACRO_CALL_MEMBER(Map::TileMapState_Func::stampBuildingOntoTileMap, this)(playerID,
                (uint)((int)(_x)), (uint)((int)(yPosition_param)), (undefined4)((int)(_buildingType_dup2)),
                (undefined4)((int)(_commandBuildingType + ~Commands::M_MAPPER_MP_KEEP8)),
                (uint)((int)(buildingSize)), (undefined4)((int)(buildingOrientation)),
                (undefined4)((int)(_averageHeight)));
            break;
        case Map::Buildings::BT_MANORHOUSE:
        case Map::Buildings::BT_STONEKEEP:
        case Map::Buildings::BT_STRONGHOLD:
        case Map::Buildings::BT_KEEPFOUR:
        case Map::Buildings::BT_KEEPFIVE:
            MACRO_CALL_MEMBER(Map::TileMapState_Func::placeKeep, this)(playerID, (uint)((int)(_x)),
                (uint)((int)(yPosition_param)), _buildingType_dup2, (uint)((int)(buildingSize)), buildingOrientation,
                _averageHeight);
            break;
        case Map::Buildings::BT_GATEHOUSELARGE:
            MACRO_CALL_MEMBER(Map::TileMapState_Func::placeGatehouseLarge, this)(playerID, (uint)((int)(_x)),
                (uint)((int)(yPosition_param)), (undefined4)((int)(_buildingType_dup2)), (uint)((int)(buildingSize)),
                buildingOrientation, (undefined4)((int)(_averageHeight)));
            break;
        case Map::Buildings::BT_GATEHOUSESMALL:
            MACRO_CALL_MEMBER(Map::TileMapState_Func::placeGatehouseSmall, this)(playerID, (uint)((int)(_x)),
                (uint)((int)(yPosition_param)), (undefined4)((int)(_buildingType_dup2)), (uint)((int)(buildingSize)),
                buildingOrientation, (undefined4)((int)(_averageHeight)));
            break;
        case Map::Buildings::BT_WOODGATE1:
            break;
        case Map::Buildings::BT_DRAWBRIDGE:
            MACRO_CALL_MEMBER(Map::TileMapState_Func::placeDrawbridge, this)(playerID, (uint)((int)(_x)),
                (uint)((int)(yPosition_param)), (undefined4)((int)(_buildingType_dup2)), (uint)((int)(buildingSize)),
                (int*)((int)(buildingOrientation)), (undefined4)((int)(_averageHeight)));
            break;
        case Map::Buildings::BT_FIREBALLISTA:
        case Map::Buildings::BT_CATAPULT:
        case Map::Buildings::BT_TREBUCHET:
        case Map::Buildings::BT_BATTERINGRAM:
        case Map::Buildings::BT_SIEGETOWER:
        case Map::Buildings::BT_SHIELD:
            MACRO_CALL_MEMBER(Map::TileMapState_Func::placeSiegeTent, this)(playerID, (uint)((int)(_x)),
                (uint)((int)(yPosition_param)), (undefined4)((int)(_buildingType_dup2)), (uint)((int)(buildingSize)),
                buildingOrientation, (undefined4)((int)(_averageHeight)));
            break;
        case Map::Buildings::BT_GARDEN:
            MACRO_CALL_MEMBER(Map::TileMapState_Func::placePositiveFearfactor, this)(playerID,
                (uint)((int)(_x)), (uint)((int)(yPosition_param)), (undefined4)((int)(_buildingType_dup2)),
                (undefined4)((int)(_commandBuildingType - Commands::M_MAPPER_GARDEN1)),
                (uint)((int)(buildingSize)), (undefined4)((int)(buildingOrientation)),
                (undefined4)((int)(_averageHeight)));
            break;
        case Map::Buildings::BT_KILLINGPIT:
            MACRO_CALL_MEMBER(Map::TileMapState_Func::placeKillingPit, this)(playerID, (uint)((int)(_x)),
                (uint)((int)(yPosition_param)), (undefined4)((int)(_buildingType_dup2)), (uint)((int)(buildingSize)),
                buildingOrientation, _averageHeight);
            break;
        case Map::Buildings::BT_PITCHDITCH:
            local_4 = MACRO_CALL_MEMBER(Map::TileMapState_Func::placePitchDitch, this)(
                playerID, (uint)((int)(_x)), (uint)((int)(yPosition_param)));
            break;
        case Map::Buildings::BT_SIEGETOWER_PLACED:
            MACRO_CALL_MEMBER(Map::TileMapState_Func::placeSiegetowerPlaced, this)(playerID, (uint)((int)(_x)),
                (uint)((int)(yPosition_param)), (undefined4)((int)(_buildingType_dup2)), (uint)((int)(buildingSize)),
                buildingOrientation, (undefined4)((int)(_averageHeight)));
            break;
        case Map::Buildings::BT_TOWER1:
        case Map::Buildings::BT_TOWER2:
        case Map::Buildings::BT_TOWER3:
        case Map::Buildings::BT_TOWER4:
        case Map::Buildings::BT_TOWER5:
            MACRO_CALL_MEMBER(Map::TileMapState_Func::placeTower, this)(playerID, (uint)((int)(_x)),
                (uint)((int)(yPosition_param)), (undefined4)((int)(_buildingType_dup2)), (uint)((int)(buildingSize)),
                buildingOrientation, (undefined4)((int)(_averageHeight)));
            break;
        case Map::Buildings::BT_CESSPIT:
            MACRO_CALL_MEMBER(Map::TileMapState_Func::placePositiveFearfactor, this)(playerID,
                (uint)((int)(_x)), (uint)((int)(yPosition_param)), (undefined4)((int)(_buildingType_dup2)),
                (undefined4)((int)(_commandBuildingType - Commands::M_MAPPER_CESS_PIT1)),
                (uint)((int)(buildingSize)), (undefined4)((int)(buildingOrientation)),
                (undefined4)((int)(_averageHeight)));
            break;
        case Map::Buildings::BT_STATUE:
            MACRO_CALL_MEMBER(Map::TileMapState_Func::placePositiveFearfactor, this)(playerID,
                (uint)((int)(_x)), (uint)((int)(yPosition_param)), (undefined4)((int)(_buildingType_dup2)),
                (undefined4)((int)(_commandBuildingType - Commands::M_MAPPER_STATUE1)),
                (uint)((int)(buildingSize)), (undefined4)((int)(buildingOrientation)),
                (undefined4)((int)(_averageHeight)));
            break;
        case Map::Buildings::BT_SHRINE:
            MACRO_CALL_MEMBER(Map::TileMapState_Func::placePositiveFearfactor, this)(playerID,
                (uint)((int)(_x)), (uint)((int)(yPosition_param)), (undefined4)((int)(_buildingType_dup2)),
                (undefined4)((int)(_commandBuildingType - Commands::M_MAPPER_SHRINE1)),
                (uint)((int)(buildingSize)), (undefined4)((int)(buildingOrientation)),
                (undefined4)((int)(_averageHeight)));
            break;
        case Map::Buildings::BT_POND:
            MACRO_CALL_MEMBER(Map::TileMapState_Func::placePositiveFearfactor, this)(playerID,
                (uint)((int)(_x)), (uint)((int)(yPosition_param)), (undefined4)((int)(_buildingType_dup2)),
                (undefined4)((int)(_commandBuildingType - Commands::M_MAPPER_POND1)),
                (uint)((int)(buildingSize)), (undefined4)((int)(buildingOrientation)),
                (undefined4)((int)(_averageHeight)));
        }
        /*
         ** Now PlacedBuildingID has been set ***/
        if (playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
            if (_buildingType2 == Map::Buildings::BT_PITCHDITCH) {
                if (local_4 != 0) {
                    MACRO_CALL_MEMBER(
                        Map::WallAndPitchState_Func::placePitchDitch, DAT_WallAndPitchState::ptr)(local_4);
                }
            } else {
                MACRO_CALL_MEMBER(Map::WallAndPitchState_Func::startBuildingDestructionConfirmation,
                    DAT_WallAndPitchState::ptr)(this->placedBuildingID);
            }
        }
        MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::processPlacementResourceLossForBuildingType,
            DAT_BuildingsState::ptr)(playerID, (BuildingType)((int)(_buildingType_2)), 0);
        uVar4 = MACRO_CALL_MEMBER(
            Map::Buildings::BuildingsState_Func::hasLessWoodThanTheCostOfAWoodcuttersHutAndNoWoodcutters,
            DAT_BuildingsState::ptr)(playerID, (int)((int)(_buildingType_2)));
        if (uVar4 != 0) {
            DAT_BuildingsState::instance.buildings[this->placedBuildingID].field203_0x288 = 1;
        }
        MACRO_CALL_MEMBER(UI::MinimapViewState_Func::triggerMinimapRedraw, DAT_MinimapViewState::ptr)(1);
        if (buildingSize < 6) {
            iVar3 = 9;
        } else {
            iVar3 = buildingSize + 5;
        }
        MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer,
            DAT_PathFindingState::ptr)(iVar3, (uint)((int)(_x)), (uint)((int)(yPosition_param)));
        DAT_PathFindingState::instance.toggleUpdateSeparateAreaTileMap = 1;
        this->field204_0x554a30 = 1;
        if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY) {
            this->forceUpdateMacroLayerFlag = 1;
            this->field68_0x55487c = 200;
        }
    }

}
}
