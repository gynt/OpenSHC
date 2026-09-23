#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"



#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {




/* 
  WARNING: Enum "MappersEnum": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0041B7C0
void BuildingsState::computeBuildingEntranceFlagsForOrientations(int param_1)

{
uint buildingSize;
int iVar1;
uint uVar2;
int iVar3;
int try;

buildingSize = this->buildings[param_1].widthOrHeight;
iVar1 = DAT_BuildingDefinedData::instance.BuildingAccessibleTilesCount[buildingSize];
if (buildingSize == 4) {
try = iVar1 + -1;
}
else {
if ((buildingSize != 5) && (buildingSize != 6)) {
return;
}
try = iVar1 + -2;
}
iVar3 = 0;
*(undefined4 *)&this->buildings[param_1].field_0x280 = 0;
if (0 < iVar1) {
do {
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingEntrancesOffset, this)(buildingSize, 1, try, 0);
try = try + 1;
if (iVar1 <= try) {
try = 0;
}
uVar2 = DAT_TileMapState::instance.LogicLayer
[DAT_ViewportRenderState::instance.translationMatrix
[(short)this->buildings[param_1].y + this->DAT_TempYOffset]
.addXgetTile + (int)(short)this->buildings[param_1].x +
this->DAT_TempXOffset];
if ((((uVar2 &0x100) != 0) && ((uVar2 &2) == 0)) && ((uVar2 &0x200) == 0)) {
*(undefined1 *)
((int)this->buildings[param_1].quarryLinkedOxTethers +
iVar3 / (int)buildingSize + -0x4a) = 1;
}
iVar3 = iVar3 + 1;
} while (iVar3 < iVar1);
}
return;
}


}
}
}