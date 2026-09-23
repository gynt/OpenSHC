#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"



#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {




/* 
  WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
 */

/* 
  WARNING: Enum "DPERRInt": Some values do not have unique names
 */

/* 
  WARNING: Enum "MappersEnum": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040B840
uint BuildingsState::isBuildingPathBlockerOrDamageable(uint param_1,int param_2)

{
int iVar1;

if (param_1 == 0) {
return 0;
}
iVar1 = (int)(short)this->buildings[param_1].buildingType;
switch(iVar1) {
case 0x2d:
case 0x2e:
case 0x4a:
case 0x4b:
case 0x4c:
case 0x4d:
case 0x4e:
iVar1 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea, DAT_PathFindingState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID, (dword)((int)(
(int)(short)DAT_TileMapState::instance.PathConnectionLayer[param_2])), (dword)((int)(
(int)(short)DAT_TileMapState::instance.PathConnectionLayer
[(int)(short)this->buildings[param_1].x +
DAT_ViewportRenderState::instance.translationMatrix
[(short)this->buildings[param_1].y + 1].addXgetTile
+ 1])), 0);
return (uint)(iVar1 == 0);
default:
return (uint)(DAT_BuildingDefinedData::instance.BuildingTypeHasHealth[iVar1] != 0);
}
}


}
}
}