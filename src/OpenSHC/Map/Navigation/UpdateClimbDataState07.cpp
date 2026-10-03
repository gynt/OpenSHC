#include "../../Map.func.hpp"
#include "../Navigation.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentClimbDataID.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004A5230
    void Navigation::UpdateClimbDataState07()
    {
        int iVar1;
        int iVar2;
        iVar2 = DAT_CurrentClimbDataID::instance;
        if (DAT_PathFindingState::instance.climbData[DAT_CurrentClimbDataID::instance].sourceUID
            != DAT_BuildingsState::instance
                .buildings[DAT_PathFindingState::instance.climbData[DAT_CurrentClimbDataID::instance].buildingID]
                .uid) {
            DAT_PathFindingState::instance.climbData[DAT_CurrentClimbDataID::instance].canBeUsed = 0;
        }
        DAT_PathFindingState::instance.climbData[iVar2].isRecognizedByPathfinding = 1;
        DAT_PathFindingState::instance.climbData[iVar2].topXPosition
            = DAT_PathFindingState::instance.climbData[iVar2].bottomXPosition;
        iVar1 = DAT_PathFindingState::instance.climbData[iVar2].bottomYPosition;
        DAT_PathFindingState::instance.climbData[iVar2].topYPosition = iVar1 + -2;
        DAT_PathFindingState::instance.climbData[iVar2].topTilePositionUnk
            = DAT_ViewportRenderState::instance.translationMatrix[iVar1 + -2].addXgetTile
            + DAT_PathFindingState::instance.climbData[iVar2].topXPosition;
        DAT_PathFindingState::instance.climbData[iVar2].area
            = (int)(short)DAT_TileMapState::instance
                  .PathConnectionLayer[DAT_PathFindingState::instance.climbData[iVar2].bottomTilePosition];
        DAT_PathFindingState::instance.climbData[iVar2].wallGroupAreaID
            = (int)(short)DAT_TileMapState::instance
                  .PathConnectionLayer[DAT_PathFindingState::instance.climbData[iVar2].topTilePositionUnk];
        DAT_PathFindingState::instance.climbData[iVar2].buildingArea = -1;
    }

}
}
