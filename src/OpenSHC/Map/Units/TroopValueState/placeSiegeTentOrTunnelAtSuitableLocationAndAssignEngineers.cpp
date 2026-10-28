#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Commands::MappersEnum;
        using OpenSHC::Map::Units::UnitInstructionType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051B420
        BOOLEnum TroopValueState::placeSiegeTentOrTunnelAtSuitableLocationAndAssignEngineers(
            int tribeID, MappersEnum commandBuildingType, uint strategicDistance, UnitInstructionType instruction)
        {
            int const leaderUnitID = DAT_TribesState::instance.tribes[tribeID].leaderUnitID;
            dword siteTile = MACRO_CALL_MEMBER(
                OpenSHC::Map::Navigation::PathFindingState_Func::findAppropriateLocationForSiegeTent,
                DAT_PathFindingState::ptr)(100, DAT_UnitsState::instance.units[leaderUnitID].x,
                DAT_UnitsState::instance.units[leaderUnitID].y, tribeID, strategicDistance,
                DAT_TribesState::instance.tribes[tribeID].owner);
            if (siteTile == 0) {
                siteTile = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Navigation::PathFindingState_Func::findAppropriateLocationForSiegeTent,
                    DAT_PathFindingState::ptr)(200, DAT_UnitsState::instance.units[leaderUnitID].x,
                    DAT_UnitsState::instance.units[leaderUnitID].y, tribeID, strategicDistance,
                    DAT_TribesState::instance.tribes[tribeID].owner);
                if (siteTile == 0) {
                    return FALSE;
                }
            }
            int const siteY = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[siteTile];
            uint x = siteTile - DAT_ViewportRenderState::instance.translationMatrix[siteY].addXgetTile - 1;
            uint y = siteY - 1;
            if (x > 399 || y > 399 || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] == 0) {
                DAT_TileMapState::instance.buildingPlacementResult = TRUE;
                return FALSE;
            }
            if ((DAT_TileMapState::instance
                        .LogicLayer[DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x]
                    & 0x4a5014b1)
                != 0) {
                DAT_TileMapState::instance.buildingPlacementResult = TRUE;
                return FALSE;
            }
            MACRO_CALL_MEMBER(TileMapState_Func::placeBuilding, DAT_TileMapState::ptr)(
                DAT_TribesState::instance.tribes[tribeID].owner, x, y, commandBuildingType, 3, 15);
            if (DAT_TileMapState::instance.buildingPlacementResult != FALSE) {
                return FALSE;
            }
            int const buildingID = DAT_TileMapState::instance.placedBuildingID;
            DAT_BuildingsState::instance.buildings[buildingID].attackWave
                = DAT_TribesState::instance.tribes[tribeID].attackWave;
            DAT_BuildingsState::instance.buildings[buildingID].unknownSiegeTentRelated01 = 2;
            MACRO_CALL_MEMBER(TribesState_Func::giveTribeAnInstruction, DAT_TribesState::ptr)(
                tribeID, instruction, buildingID, DAT_BuildingsState::instance.buildings[buildingID].uid, 0);
            return TRUE;
        }

    }
}
}
