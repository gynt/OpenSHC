#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"



#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {




/* 
  WARNING: Enum "MappersEnum": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040CB90
undefined4 BuildingsState::isFarmTileReadyForWheatStageChange(int param_1)

{
short sVar1;
int iVar2;
int *piVar3;
int iVar4;
bool bVar5;
bool bVar6;

iVar4 = 0;
piVar3 = &this->buildings[param_1].tileRef1;
do {
this->farmerDestinationTile = *piVar3;
iVar2 = (int)(char)DAT_TileMapState::instance.DamageLayer[this->farmerDestinationTile];
sVar1 = *(short *)&this->buildings[param_1].wheatGrowStateRelated;
if (sVar1 == 6) {
if (10 < iVar2) {
bVar6 = (iVar2 < 0x65);
bVar5 = iVar2 + -0x65 < 0;
goto LAB_0040cc12;
}
}
else if (sVar1 == 8) {
if (iVar2 == 0x79) {
return(undefined4)( 1);
}
}
else if (sVar1 == 3) {
if (iVar2 == 0) {
return(undefined4)( 1);
}
if (iVar2 == 0x78) {
return(undefined4)( 1);
}
if (100 < iVar2) {
bVar6 = (iVar2 < 0x78);
bVar5 = iVar2 + -0x78 < 0;
LAB_0040cc12:
if (bVar6 != bVar5) {
return(undefined4)( 1);
}
}
}
else {
if (sVar1 != 5) {
return(undefined4)( 0);
}
if (0 < iVar2) {
bVar6 = (iVar2 < 2);
bVar5 = iVar2 + -2 < 0;
goto LAB_0040cc12;
}
}
iVar4 = iVar4 + 1;
piVar3 = piVar3 + 1;
if (0x23 < iVar4) {
return(undefined4)( 0);
}
} while( true );
}


}
}
}