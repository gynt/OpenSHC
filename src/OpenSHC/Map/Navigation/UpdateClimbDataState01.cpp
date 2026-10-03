#include "../../Map.func.hpp"
#include "../Navigation.func.hpp"

#include "OpenSHC/Map/Units/States/UnitState.hpp"

#include "OpenSHC/Globals/DAT_CurrentClimbDataID.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Units::States::UnitState;

    // FUNCTION: STRONGHOLDCRUSADER 0x004A4D60
    void Navigation::UpdateClimbDataState01()
    {
        int _direction;
        int _unit;
        int _id;
        _id = DAT_CurrentClimbDataID::instance;
        _unit = DAT_PathFindingState::instance.climbData[DAT_CurrentClimbDataID::instance].unitID;
        if (((DAT_PathFindingState::instance.climbData[DAT_CurrentClimbDataID::instance].sourceUID
                 == DAT_UnitsState::instance.units[_unit].uid)
                && (DAT_UnitsState::instance.units[_unit].state.generic == ((UnitState)3)))
            && (DAT_UnitsState::instance.units[_unit].dying == 0)) {
            _direction = (int)DAT_UnitsState::instance.units[_unit].facingDirection;
            DAT_PathFindingState::instance.climbData[DAT_CurrentClimbDataID::instance].isRecognizedByPathfinding = 1;
            DAT_PathFindingState::instance.climbData[_id].ladderDirection = _direction;
            DAT_PathFindingState::instance.climbData[_id].topXPosition
                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction].int_.xOffset
                + DAT_PathFindingState::instance.climbData[_id].bottomXPosition;
            DAT_PathFindingState::instance.climbData[_id].topYPosition
                = *(int*)((int)DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix
                      + DAT_PathFindingState::instance.climbData[_id].ladderDirection * 8 + 4)
                + DAT_PathFindingState::instance.climbData[_id].bottomYPosition;
            DAT_PathFindingState::instance.climbData[_id].topTilePositionUnk
                = DAT_TileMapState::instance.directionTranslationMatrix[DAT_PathFindingState::instance.climbData[_id]
                          .bottomYPosition][DAT_PathFindingState::instance.climbData[_id].ladderDirection]
                + DAT_PathFindingState::instance.climbData[_id].bottomTilePosition;
            DAT_PathFindingState::instance.climbData[_id].area
                = (int)(short)DAT_TileMapState::instance
                      .PathConnectionLayer[DAT_PathFindingState::instance.climbData[_id].bottomTilePosition];
            DAT_PathFindingState::instance.climbData[_id].wallGroupAreaID
                = (int)(short)DAT_TileMapState::instance
                      .PathConnectionLayer[DAT_PathFindingState::instance.climbData[_id].topTilePositionUnk];
            DAT_PathFindingState::instance.climbData[_id].buildingArea = -1;
        }
        DAT_PathFindingState::instance.climbData[DAT_CurrentClimbDataID::instance].canBeUsed = 0;
    }

}
}
