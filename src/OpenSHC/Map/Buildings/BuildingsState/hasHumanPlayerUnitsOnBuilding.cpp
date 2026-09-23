#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"



#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::WindowsHelper::Enums::BOOLEnum;


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


// FUNCTION: STRONGHOLDCRUSADER 0x0040B980
BOOLEnum BuildingsState::hasHumanPlayerUnitsOnBuilding(int buildingID)

{
int _counterTillBuildingWidth2;
ushort *_pUnitID;
int _counterTillBuildingWidth;
int *piVar1;
uint _buildingWidth;

_buildingWidth = this->buildings[buildingID].widthOrHeight;
_counterTillBuildingWidth = 0;
if (0 < (int)_buildingWidth) {
piVar1 = &DAT_ViewportRenderState::instance.translationMatrix
[(short)this->buildings[buildingID].y].addXgetTile;
do {
_counterTillBuildingWidth2 = 0;
_pUnitID = DAT_TileMapState::instance.UnitLayer +
*piVar1 + (int)(short)this->buildings[buildingID].x;
do {
if (((short)*_pUnitID != 0) &&
(DAT_GameSynchronyState::instance.currentPlayerFullIDArray
[DAT_UnitsState::instance.units[(short)*_pUnitID].owner] != -1)) {
return TRUE;
}
_counterTillBuildingWidth2 = _counterTillBuildingWidth2 + 1;
_pUnitID = _pUnitID + 1;
} while (_counterTillBuildingWidth2 < (int)_buildingWidth);
_counterTillBuildingWidth = _counterTillBuildingWidth + 1;
piVar1 = piVar1 + 3;
} while (_counterTillBuildingWidth < (int)_buildingWidth);
}
return FALSE;
}


}
}
}