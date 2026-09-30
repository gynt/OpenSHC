#include "../../Map.func.hpp"
#include "../Navigation.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentClimbDataID.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004A4E40
    void Navigation::UpdateClimbDataState03()
    {
        int iVar1;
        int iVar2;
        int iVar3;
        int iVar4;
        iVar2 = DAT_CurrentClimbDataID::instance;
        iVar1 = DAT_PathFindingState::instance.climbData[DAT_CurrentClimbDataID::instance].buildingID;
        DAT_BuildingsState::instance.buildings[iVar1].laddermanDataID = (short)DAT_CurrentClimbDataID::instance;
        if (DAT_PathFindingState::instance.climbData[iVar2].sourceUID
            != DAT_BuildingsState::instance.buildings[iVar1].uid) {
            DAT_PathFindingState::instance.climbData[iVar2].canBeUsed = 0;
        }
        DAT_PathFindingState::instance.climbData[iVar2].owner
            = (int)DAT_BuildingsState::instance.buildings[iVar1].owner;
        DAT_PathFindingState::instance.climbData[iVar2].isRecognizedByPathfinding
            = (uint)(DAT_BuildingsState::instance.buildings[iVar1].pathLinkageRelated2 != 2);
        iVar3 = DAT_PathFindingState::instance.climbData[iVar2].ladderDirection;
        if (iVar3 == 2) {
            iVar3 = (int)(short)DAT_BuildingsState::instance.buildings[iVar1].x;
            DAT_PathFindingState::instance.climbData[iVar2].bottomXPosition = iVar3 + 7;
            iVar4 = (short)DAT_BuildingsState::instance.buildings[iVar1].y + 3;
            DAT_PathFindingState::instance.climbData[iVar2].bottomYPosition = iVar4;
            iVar3 = iVar3 + -1;
        } else {
            if (iVar3 != 0)
                goto LAB_004a4efe;
            iVar4 = (int)(short)DAT_BuildingsState::instance.buildings[iVar1].y;
            iVar3 = (short)DAT_BuildingsState::instance.buildings[iVar1].x + 3;
            DAT_PathFindingState::instance.climbData[iVar2].bottomXPosition = iVar3;
            DAT_PathFindingState::instance.climbData[iVar2].bottomYPosition = iVar4 + 7;
            iVar4 = iVar4 + -1;
        }
        DAT_PathFindingState::instance.climbData[iVar2].topXPosition = iVar3;
        DAT_PathFindingState::instance.climbData[iVar2].topYPosition = iVar4;
    LAB_004a4efe:
        DAT_PathFindingState::instance.climbData[iVar2].bottomTilePosition
            = DAT_ViewportRenderState::instance
                  .translationMatrix[DAT_PathFindingState::instance.climbData[iVar2].bottomYPosition]
                  .addXgetTile
            + DAT_PathFindingState::instance.climbData[iVar2].bottomXPosition;
        DAT_PathFindingState::instance.climbData[iVar2].topTilePositionUnk
            = DAT_ViewportRenderState::instance
                  .translationMatrix[DAT_PathFindingState::instance.climbData[iVar2].topYPosition]
                  .addXgetTile
            + DAT_PathFindingState::instance.climbData[iVar2].topXPosition;
        DAT_PathFindingState::instance.climbData[iVar2].area
            = (int)(short)DAT_TileMapState::instance
                  .PathConnectionLayer[DAT_PathFindingState::instance.climbData[iVar2].bottomTilePosition];
        DAT_PathFindingState::instance.climbData[iVar2].wallGroupAreaID
            = (int)(short)DAT_TileMapState::instance
                  .PathConnectionLayer[DAT_PathFindingState::instance.climbData[iVar2].topTilePositionUnk];
        DAT_PathFindingState::instance.climbData[iVar2].buildingArea
            = (int)(short)DAT_TileMapState::instance.PathConnectionLayer
                  [DAT_ViewportRenderState::instance
                          .translationMatrix[(short)DAT_BuildingsState::instance.buildings[iVar1].y + 1]
                          .addXgetTile
                      + (int)(short)DAT_BuildingsState::instance.buildings[iVar1].x + 1];
    }

}
}
