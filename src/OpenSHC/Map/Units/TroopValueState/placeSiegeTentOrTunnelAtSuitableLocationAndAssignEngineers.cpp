#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
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

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0051B420
        BOOLEnum TroopValueState::placeSiegeTentOrTunnelAtSuitableLocationAndAssignEngineers(
            int tribeID, MappersEnum commandBuildingType, uint strategicDistance, UnitInstructionType instruction)
        {
            dword _targetTile;
            uint x;
            uint y;
            int _targetUnitID;
            int _buildingID;
            _targetUnitID = (int)DAT_TribesState::instance.tribes[tribeID].selectionTargetUnitID;
            _targetTile = MACRO_CALL_MEMBER(
                OpenSHC::Map::Navigation::PathFindingState_Func::findAppropriateLocationForSiegeTent,
                DAT_PathFindingState::ptr)(100, (uint)((int)((int)DAT_UnitsState::instance.units[_targetUnitID].x)),
                (uint)((int)((int)DAT_UnitsState::instance.units[_targetUnitID].y)), (undefined4)((int)(tribeID)),
                strategicDistance, DAT_TribesState::instance.tribes[tribeID].owner);
            if ((_targetTile == 0)
                && (_targetTile = MACRO_CALL_MEMBER(
                        OpenSHC::Map::Navigation::PathFindingState_Func::findAppropriateLocationForSiegeTent,
                        DAT_PathFindingState::ptr)(200,
                        (uint)((int)((int)DAT_UnitsState::instance.units[_targetUnitID].x)),
                        (uint)((int)((int)DAT_UnitsState::instance.units[_targetUnitID].y)),
                        (undefined4)((int)(tribeID)), strategicDistance,
                        DAT_TribesState::instance.tribes[tribeID].owner),
                    _targetTile == 0)) {
                return FALSE;
            }
            _buildingID = (int)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[_targetTile];
            x = (_targetTile - DAT_ViewportRenderState::instance.translationMatrix[_buildingID].addXgetTile) - 1;
            y = _buildingID - 1;
            if ((((x < 400) && (y < 400)) && (*(char*)(y * 400 + 0x21aec98 + x) != '\0'))
                && ((*(uint*)((int)DAT_TileMapState::ptr
                         + (DAT_ViewportRenderState::instance.translationMatrix[_buildingID + -1].addXgetTile + x) * 4
                         + 0x165160)
                        & 0x4a5014b1)
                    == 0)) {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::placeBuilding, DAT_TileMapState::ptr)(
                    DAT_TribesState::instance.tribes[tribeID].owner, (int)((int)(x)), (int)((int)(y)),
                    commandBuildingType, 3, 0xf);
                _buildingID = DAT_TileMapState::instance.placedBuildingID;
                if (DAT_TileMapState::instance.buildingPlacementFail == FALSE) {
                    DAT_BuildingsState::instance.buildings[DAT_TileMapState::instance.placedBuildingID].attackWave
                        = (int)DAT_TribesState::instance.tribes[tribeID].attackWave;
                    DAT_BuildingsState::instance.buildings[_buildingID].unknownSiegeTentRelated01 = 2;
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Units::TribesState_Func::giveTribeAnInstruction, DAT_TribesState::ptr)(
                        tribeID, instruction, _buildingID, DAT_BuildingsState::instance.buildings[_buildingID].uid, 0);
                    return TRUE;
                }
            } else {
                DAT_TileMapState::instance.buildingPlacementFail = TRUE;
            }
            return FALSE;
        }

    }
}
}
