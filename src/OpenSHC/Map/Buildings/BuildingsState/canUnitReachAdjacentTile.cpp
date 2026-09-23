#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"



#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::WindowsHelper::Enums::BOOLEnum;


/* 
  WARNING: Enum "MappersEnum": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004105F0
undefined4 BuildingsState::canUnitReachAdjacentTile(int param_1,int param_2)

{
byte bVar1;
short sVar2;
ushort uVar3;
ushort uVar4;
int iVar5;
BOOLEnum BVar6;
uint uVar7;
int iVar8;
uint uVar9;
int (*paiVar10) [8];

iVar5 = param_1;
bVar1 = DAT_TileMapState::instance.HeightLayer[param_1];
sVar2 = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[param_1];
uVar3 = DAT_TileMapState::instance.PathConnectionLayer[DAT_UnitsState::instance.units[param_2].tile];
BVar6 = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::selectionContainsOnlyArabAssassins, DAT_UnitsState::ptr)();
if (BVar6 != FALSE) {
return(undefined4)( 0);
}
paiVar10 = DAT_TileMapState::instance.directionTranslationMatrix + sVar2;
param_1 = 0;
do {
uVar4 = DAT_TileMapState::instance.PathConnectionLayer[(*paiVar10)[0] + iVar5];
uVar7 = (uint)bVar1 - (uint)DAT_TileMapState::instance.HeightLayer[iVar5];
uVar9 = (int)uVar7 >> 0x1f;
if (((int)((uVar7 ^ uVar9) - uVar9) < 0x10) && ((int)(short)uVar4 != 0)) {
iVar8 = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::canAUnitClimb, DAT_UnitsState::ptr)();
iVar8 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea, DAT_PathFindingState::ptr)((int)DAT_UnitsState::instance.units[param_2].owner, (dword)((int)(
(int)(short)uVar3)), (dword)((int)((int)(short)uVar4)), iVar8);
if (iVar8 != 0) {
return(undefined4)( 1);
}
}
param_1 = param_1 + 1;
paiVar10 = (int (*) [8])(*paiVar10 + 1);
} while (param_1 < 8);
return(undefined4)( 0);
}


}
}
}