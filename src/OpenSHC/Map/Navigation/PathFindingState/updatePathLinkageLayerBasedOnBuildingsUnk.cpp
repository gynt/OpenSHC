#include "../PathFindingState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeShort.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_ClimbLogicDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        using OpenSHC::Map::Buildings::BuildingTypeShort;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004999C0
        BOOLEnum PathFindingState::updatePathLinkageForTile(int yUnk, int tile)
        {
            uint _height;
            int _building;
            int _mode;
            int _isWall;
            int _isPlain;
            int _isBuilding;
            int _isGate;
            byte _climbable;
            byte _linkageResult;
            BOOLEnum _result;
            int _low;
            int _high;
            uint _logics[8];
            uint _logic;
            _logic = DAT_TileMapState::instance.LogicLayer[tile];
            _height = (uint)DAT_TileMapState::instance.HeightLayer[tile];
            _low = _height - 0x10;
            _high = _height + 0x10;
            _building = (int)DAT_TileMapState::instance.BuildingLayer[tile];
            _result = FALSE;
            if ((_logic & 0x10000000) != 0) {
                _height = _height
                    + MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                        DAT_BuildingsState::ptr)(_building);
                _low = _height - 0x10;
                _high = _height + 0x10;
            }
            if (_building != 0) {
                if (DAT_BuildingDefinedData::instance
                        .BuildingIsGateHouseArray[(short)DAT_BuildingsState::instance.buildings[_building].buildingType]
                    != 0) {
                    _result = TRUE;
                }
                if (DAT_BuildingDefinedData::instance
                        .BuildingIsKeepArray[(short)DAT_BuildingsState::instance.buildings[_building].buildingType]
                    != 0) {
                    _result = TRUE;
                }
            }
            _isBuilding = 0;
            _isGate = 0;
            _isWall = 0;
            _isPlain = 0;
            _linkageResult = 0;
            _mode = 0;
            _climbable = 0;
            DAT_TileMapState::instance.PathLinkageLayer[tile] = _linkageResult;
            if ((_logic & 0x800000) == 0) {
                if ((_logic & 0x10000000) != 0) {
                    _isBuilding = 1;
                    _mode = 1;
                } else if ((_logic & 2) != 0) {
                    _isPlain = 1;
                } else if ((_logic & 0x200000) != 0) {
                    _isPlain = 1;
                } else if ((_logic & 0x800) != 0) {
                    _isGate = 1;
                } else if ((_logic & 0x400000) != 0) {
                    return _result;
                } else if ((_logic & 0x100) != 0) {
                    _isWall = 1;
                    if (DAT_TileMapState::instance.BuildingLayer[tile] != 0) {
                        _mode = 2;
                    }
                } else if ((_logic & 0x4a5014b1) != 0) {
                    return _result;
                } else {
                    _isPlain = 1;
                }
            }
            for (int _directionIndex = 0; _directionIndex < 8; _directionIndex = _directionIndex + 1) {
                int _tile = DAT_TileMapState::instance.directionTranslationMatrix[yUnk][_directionIndex] + tile;
                _logic = DAT_TileMapState::instance.LogicLayer[_tile];
                _logics[_directionIndex] = _logic;
                if ((_logic & 0x200000) == 0) {
                    if ((_logic & 0x800) != 0) {
                        if (_mode == 1) {
                            continue;
                        }
                        if ((char)DAT_TileMapState::instance.DamageOrCropStageLayer[_tile] > 0x14) {
                            continue;
                        }
                    } else if ((_logic & 2) != 0) {
                        if (_isBuilding != 0) {
                            continue;
                        }
                        if ((_logic & 0x400) != 0 && DAT_TileMapState::instance.BuildingLayer[_tile] != 0) {
                            continue;
                        }
                    } else if ((_logic & 0x400) != 0) {
                        if (DAT_BuildingDefinedData::instance.linksPathAcrossPerType[(short)DAT_BuildingsState::instance
                                    .buildings[DAT_TileMapState::instance.BuildingLayer[_tile]]
                                    .buildingType]
                            != FALSE) {
                            _climbable
                                = _climbable + DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[_directionIndex];
                        }
                        continue;
                    } else if ((_logic & 0x10000000) != 0) {
                        _climbable
                            = _climbable + DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[_directionIndex];
                    } else if ((_logic & 0x400000) != 0) {
                        _climbable
                            = _climbable + DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[_directionIndex];
                        continue;
                    } else if ((_logic & 0x100) != 0) {
                        _climbable
                            = _climbable + DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[_directionIndex];
                    } else if ((_logic & 0x30) != 0) {
                        _climbable
                            = _climbable + DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[_directionIndex];
                        continue;
                    } else if ((_logic & 0x4a5014b1) != 0) {
                        continue;
                    }
                }
                if ((_logic & 0x10000000) != 0) {
                    if (_isBuilding == 0) {
                        if (_isWall == 0) {
                            continue;
                        }
                        if ((char)DAT_TileMapState::instance.DamageOrCropStageLayer[tile] > 0x14) {
                            continue;
                        }
                    }
                } else if ((_logic & 0x100) != 0 && _mode != 0) {
                    if ((char)DAT_TileMapState::instance.DamageOrCropStageLayer[_tile] > 0x14) {
                        continue;
                    }
                } else if ((_isWall != 0 || _isGate != 0) && (_logic & 0x100) != 0
                    && DAT_TileMapState::instance.BuildingLayer[_tile] != 0) {
                    if ((char)DAT_TileMapState::instance.DamageOrCropStageLayer[tile] > 0x14) {
                        continue;
                    }
                } else {
                    int _tileHeight = DAT_TileMapState::instance.HeightLayer[_tile];
                    if (_tileHeight < _low) {
                        continue;
                    }
                    if (_tileHeight > _high) {
                        continue;
                    }
                }
                _linkageResult
                    = _linkageResult | DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[_directionIndex];
            }
            if (_isPlain != 0) {
                if ((_linkageResult & 1) == 0 && (_climbable & 1) != 0) {
                    if ((_linkageResult & 4) == 0 && (_climbable & 4) != 0) {
                        _linkageResult = _linkageResult & 0xfd;
                    }
                    if ((_linkageResult & 0x40) == 0 && (_climbable & 0x40) != 0) {
                        _linkageResult = _linkageResult & 0x7f;
                    }
                }
                if ((_linkageResult & 0x10) == 0 && (_climbable & 0x10) != 0) {
                    if ((_linkageResult & 4) == 0 && (_climbable & 4) != 0) {
                        _linkageResult = _linkageResult & 0xf7;
                    }
                    if ((_linkageResult & 0x40) == 0 && (_climbable & 0x40) != 0) {
                        _linkageResult = _linkageResult & 0xdf;
                    }
                }
            } else {
                if ((_logics[0] & 0x10000100) != 0 && (_logics[2] & 0x10000100) != 0
                    && (_logics[1] & 0x10000100) == 0 && (_logics[1] & 2) == 0 && (_logics[0] & 0x800) == 0
                    && (_logics[2] & 0x800) == 0) {
                    _linkageResult = _linkageResult & 0xfd;
                }
                if ((_logics[0] & 0x10000100) != 0 && (_logics[6] & 0x10000100) != 0
                    && (_logics[7] & 0x10000100) == 0 && (_logics[7] & 2) == 0 && (_logics[0] & 0x800) == 0
                    && (_logics[6] & 0x800) == 0) {
                    _linkageResult = _linkageResult & 0x7f;
                }
                if ((_logics[4] & 0x10000100) != 0 && (_logics[2] & 0x10000100) != 0
                    && (_logics[3] & 0x10000100) == 0 && (_logics[3] & 2) == 0 && (_logics[4] & 0x800) == 0
                    && (_logics[2] & 0x800) == 0) {
                    _linkageResult = _linkageResult & 0xf7;
                }
                if ((_logics[4] & 0x10000100) != 0 && (_logics[6] & 0x10000100) != 0
                    && (_logics[5] & 0x10000100) == 0 && (_logics[5] & 2) == 0 && (_logics[4] & 0x800) == 0
                    && (_logics[6] & 0x800) == 0) {
                    _linkageResult = _linkageResult & 0xdf;
                }
            }
            DAT_TileMapState::instance.PathLinkageLayer[tile] = _linkageResult;
            return _result;
        }

    }
}
}
