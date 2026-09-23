#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"





namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Map::Buildings::BuildingLogicalState;
using OpenSHC::Map::Buildings::BuildingType;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040AA10
int BuildingsState::countFarms(PlayerID playerID,int param_2)

{
BuildingTypeShort BVar1;
int _count;
Building * pBVar3;
int iVar2;

_count = 0;
if (1 < this->maxBuildingsCount) {
pBVar3 = &this->buildings[1];
iVar2 = this->maxBuildingsCount + -1;
do {
if ((((pBVar3->logicalState == OpenSHC::Map::Buildings::BLS_NORMAL) && (pBVar3->owner == playerID)) &&
((BVar1 = pBVar3->buildingType, BVar1 == OpenSHC::Map::Buildings::BT_WHEATFARM ||
((BVar1 == OpenSHC::Map::Buildings::BT_APPLEFARM || (BVar1 == OpenSHC::Map::Buildings::BT_DAIRYFARM)))))) &&
((param_2 == 0 || (pBVar3->field245_0x2c8 == 0)))) {
_count = _count + 1;
}
pBVar3 = pBVar3 + 0x196;
iVar2 = iVar2 + -1;
} while (iVar2 != 0);
}
return _count;
}


}
}
}