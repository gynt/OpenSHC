#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_BORDER;
    using OpenSHC::Map::LogicHelpers::L_BUILDING;
    using OpenSHC::Map::LogicHelpers::L_FORD;
    using OpenSHC::Map::LogicHelpers::L_MARSH;
    using OpenSHC::Map::LogicHelpers::L_MOAT;
    using OpenSHC::Map::LogicHelpers::L_PLAIN1_AND_FARM;
    using OpenSHC::Map::LogicHelpers::L_RIVER;
    using OpenSHC::Map::LogicHelpers::L_ROCKY;
    using OpenSHC::Map::LogicHelpers::L_SEA;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    using OpenSHC::Map::Units::UnitLogicState;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004F94A0
    void TileMapState::validateWallPlacementAtTile(int playerID, uint x, uint y, OpenSHC::Commands::MappersEnumShort param_4)
    {
        this->illegalBuild = TRUE;
        int tile = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
        uint logic = this->LogicLayer[tile];
        int buildingID = this->BuildingLayer[tile];
        if (((logic & L_WALL_OR_GATEHOUSE) == 0 || (char)this->DamageOrCropStageLayer[tile] >= 12)
            && (logic & L_BUILDING) == 0 && buildingID == 0 && (logic & (L_PLAIN1_AND_FARM | L_BORDER)) == 0
            && (logic & (L_SEA | L_ROCKY | L_RIVER | L_FORD | L_MARSH | L_MOAT)) == 0
            && MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::isEnemyUnitWithinDistance,
                   DAT_PathFindingState::ptr)(playerID, x, y, 5)
                == FALSE
            && MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::isEnemyBuildingOrWallWithinDistance,
                   DAT_PathFindingState::ptr)(playerID, x, y, 2)
                == 0) {
            short unitID = this->UnitLayer[tile];
            if (unitID != 0 && (this->LogicLayer[tile] & L_WALL_OR_GATEHOUSE) == 0
                && ((short)param_4 == OpenSHC::Commands::M_MAPPER_CRENAL
                    || (short)param_4 == OpenSHC::Commands::M_MAPPER_CRENAL2)) {
                DAT_UnitsState::instance.units[unitID].logicalState = OpenSHC::Map::Units::ULS_REMOVE;
            }
            this->illegalBuild = FALSE;
        }
    }

}
}
