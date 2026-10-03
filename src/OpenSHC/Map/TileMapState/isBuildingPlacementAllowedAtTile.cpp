#include "../../Map.func.hpp"
#include "../TileMapState.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Commands::MappersEnum;
    using OpenSHC::Game::GameMode;
    using OpenSHC::Map::Units::UnitType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      @return int 0 if allowed, 1 if not allowed, 2 not allowed because of clashing building placement decompilerscript:
      committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004F9A60
    int TileMapState::isBuildingPlacementAllowedAtTile(
        int tile, int playerID, MappersEnum commandBuildingType, int param_4)
    {
        bool bVar1;
        uint _height;
        BOOLEnum _isAI2;
        int _orgID;
        BOOL _isAI;
        int _result;
        uint _wallOrGate;
        uint _tileLogic;
        ushort _unitID;
        _tileLogic = this->LogicLayer[tile];
        _wallOrGate = _tileLogic & OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;
        bVar1 = false;
        _height = (uint)this->HeightLayer[tile];
        if ((_wallOrGate != 0) && ((this->WallOwnerLayer[tile] & 7) + 1 == playerID)) {
            switch (commandBuildingType) {
            case OpenSHC::Commands::M_MAPPER_GATEHOUSE:
            case OpenSHC::Commands::M_MAPPER_GATE_MAIN:
            case OpenSHC::Commands::M_MAPPER_GATE_INNER:
            case OpenSHC::Commands::M_MAPPER_GATE_WOOD:
            case OpenSHC::Commands::M_MAPPER_GATE_POSTERN:
            case OpenSHC::Commands::M_MAPPER_TOWER1:
            case OpenSHC::Commands::M_MAPPER_TOWER2:
            case OpenSHC::Commands::M_MAPPER_TOWER3:
            case OpenSHC::Commands::M_MAPPER_TOWER4:
            case OpenSHC::Commands::M_MAPPER_TOWER5:
            case OpenSHC::Commands::M_MAPPER_GATE_WOOD1A:
            case OpenSHC::Commands::M_MAPPER_GATE_WOOD1B:
            case OpenSHC::Commands::M_MAPPER_GATE_WOOD1C:
            case OpenSHC::Commands::M_MAPPER_GATE_WOOD1D:
            case OpenSHC::Commands::M_MAPPER_GATE_STONE1A:
            case OpenSHC::Commands::M_MAPPER_GATE_STONE1B:
            case OpenSHC::Commands::M_MAPPER_GATE_STONE2A:
            case OpenSHC::Commands::M_MAPPER_GATE_STONE2B:
                _height = (uint)this->DefaultHeightLayer[tile];
            }
        }
        if (this->buildingHeightLimit < 0) {
            if ((int)_height < -this->buildingHeightLimit) {
                return 1;
            }
        } else if (this->buildingHeightLimit < (int)_height) {
            if (commandBuildingType == OpenSHC::Commands::M_MAPPER_CATTLEFARM) {
                this->placementWarning = 1;
                return 1;
            }
            if (commandBuildingType == OpenSHC::Commands::M_MAPPER_APPLEFARM) {
                this->placementWarning = 2;
                return 1;
            }
            if (commandBuildingType == OpenSHC::Commands::M_MAPPER_HOPSFARM) {
                this->placementWarning = 3;
                return 1;
            }
            if (commandBuildingType != OpenSHC::Commands::M_MAPPER_WHEATFARM) {
                return 1;
            }
            this->placementWarning = 4;
            return 1;
        }
        if (this->buildingMaxHeightDifference + this->buildingMinHeight < (int)_height) {
            return 1;
        }
        if (((_tileLogic & 8) != 0) && (commandBuildingType == OpenSHC::Commands::M_MAPPER_PITCH_DITCH)) {
            return 1;
        }
        if (this->BuildingLayer[tile] != 0) {
            return 2;
        }
        _unitID = this->UnitLayer[tile];
        if (_unitID != 0) {
            _isAI2 = MACRO_CALL_MEMBER(
                OpenSHC::Synchrony::GameSynchronyState_Func::isAIPlayer, DAT_GameSynchronyState::ptr)(playerID);
            if (_isAI2 == FALSE) {
                if (DAT_UnitsState::instance.units[(short)_unitID].unitType != OpenSHC::Map::Units::UT_CHICKEN) {
                    return 1;
                }
            } else {
                if (DAT_UnitsState::instance.units[(short)_unitID].unitType == OpenSHC::Map::Units::UT_LORD) {
                    return 1;
                }
                if ((DAT_UnitsState::instance.units[(short)_unitID].isSelectable_OR_matchTime != 0)
                    && (DAT_UnitsState::instance.units[(short)_unitID].owner != playerID)) {
                    return 1;
                }
            }
        }
        /*
          is sea
         */
        if ((_tileLogic & OpenSHC::Map::LogicHelpers::L_SEA) != 0) {
            return 1;
        }
        /*
          is any border
         */
        if ((_tileLogic & OpenSHC::Map::LogicHelpers::L_BORDER | OpenSHC::Map::LogicHelpers::L_BORDER_EDGE) == 0) {
            /*
              is river
             */
            if ((_tileLogic & OpenSHC::Map::LogicHelpers::L_RIVER) != 0) {
                return 1;
            }
            if (_wallOrGate != 0) {
                /*
                  other people's buildings
                 */
                if ((this->WallOwnerLayer[tile] & 7) + 1 != playerID) {
                    return 1;
                }
                switch (commandBuildingType) {
                case OpenSHC::Commands::M_MAPPER_GATEHOUSE:
                case OpenSHC::Commands::M_MAPPER_GATE_MAIN:
                case OpenSHC::Commands::M_MAPPER_GATE_INNER:
                case OpenSHC::Commands::M_MAPPER_GATE_WOOD:
                case OpenSHC::Commands::M_MAPPER_GATE_POSTERN:
                case OpenSHC::Commands::M_MAPPER_TOWER1:
                case OpenSHC::Commands::M_MAPPER_TOWER2:
                case OpenSHC::Commands::M_MAPPER_TOWER3:
                case OpenSHC::Commands::M_MAPPER_TOWER4:
                case OpenSHC::Commands::M_MAPPER_TOWER5:
                case OpenSHC::Commands::M_MAPPER_GATE_WOOD1A:
                case OpenSHC::Commands::M_MAPPER_GATE_WOOD1B:
                case OpenSHC::Commands::M_MAPPER_GATE_WOOD1C:
                case OpenSHC::Commands::M_MAPPER_GATE_WOOD1D:
                case OpenSHC::Commands::M_MAPPER_GATE_STONE1A:
                case OpenSHC::Commands::M_MAPPER_GATE_STONE1B:
                case OpenSHC::Commands::M_MAPPER_GATE_STONE2A:
                case OpenSHC::Commands::M_MAPPER_GATE_STONE2B:
                    break;
                    default:
                        return 1;
                }
            }
            if ((((_tileLogic & OpenSHC::Map::LogicHelpers::L_PLAIN1_AND_FARM) == 0) || (param_4 != 0))
                && ((_tileLogic & OpenSHC::Map::LogicHelpers::L_BUILDING | OpenSHC::Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE) == 0)) {
                /*
                  not a keep and not a building
                 */
                if ((((_tileLogic & OpenSHC::Map::LogicHelpers::L_TREE | OpenSHC::Map::LogicHelpers::L_TREE_VARIATION) != 0)
                        && (_orgID = (int)this->OrganismLayer[tile], _orgID != 0))
                    && (_orgID < 2000)) {
                    /*
                      tree or tree_variation
                     */
                    switch (DAT_LandscapeState::instance.trees[_orgID].treeType) {
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
                        break;
                        default:
                            if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY)
                        {
                            return 1;
                        }
                        _isAI = MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::isAIPlayer,
                            DAT_GameSynchronyState::ptr)(playerID);
                        if (_isAI == 0) {
                            return 1;
                        }
                    }
                }
                /*
                  not any farms or fords
                 */
                if ((((_tileLogic & OpenSHC::Map::LogicHelpers::L_FARM_FIELD_WHEAT | OpenSHC::Map::LogicHelpers::L_FARM_FIELD_HOP | OpenSHC::Map::LogicHelpers::L_FARM_FIELD_APPLE | OpenSHC::Map::LogicHelpers::L_FARM_FIELD_DAIRY)
                         == 0)
                        || (param_4 != 0))
                    && ((_tileLogic & OpenSHC::Map::LogicHelpers::L_FORD) == 0)) {
                    if (((char)_tileLogic < 0) && (_wallOrGate == 0)) {
                        bVar1 = true;
                    }
                    _result = 1;
                    if ((((!bVar1) || (this->buildingPlacementProperty_4 != 0))
                            && (((_tileLogic & OpenSHC::Map::LogicHelpers::L_MOAT) == 0 || (this->buildingPlacementProperty_7 != 0))))
                        && (((this->buildingPlacementProperty_6 == 2 || ((_tileLogic & OpenSHC::Map::LogicHelpers::L_MARSH) == 0))
                            || (this->buildingPlacementProperty_6 != 0)))) {
                        /*
                          not moat and marsh
                         */
                        _result = 0;
                    }
                    return _result;
                }
            }
            return 1;
        }
        return 1;
    }

}
}
