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


// FUNCTION: STRONGHOLDCRUSADER 0x0040CB10
int BuildingsState::getFarmThatHasTile(int tile)

{
BuildingTypeShort BVar1;
int _buildingID;
int iVar2;
int *pTileRef1;
BuildingTypeShort *pBVar3;

_buildingID = 1;
if (1 < this->maxBuildingsCount) {
pBVar3 = &this->buildings[1].buildingType;
do {
if ((pBVar3[-1] == OpenSHC::Map::Buildings::BLS_NORMAL) &&
((((BVar1 = *pBVar3, BVar1 == OpenSHC::Map::Buildings::BT_WHEATFARM || (BVar1 == OpenSHC::Map::Buildings::BT_HOPFARM)) ||
(BVar1 == OpenSHC::Map::Buildings::BT_APPLEFARM)) || (BVar1 == OpenSHC::Map::Buildings::BT_DAIRYFARM)))) {
iVar2 = 0;
pTileRef1 = (int *)(pBVar3 + 0x7b);
do {
if (*pTileRef1 == tile) {
return _buildingID;
}
iVar2 = iVar2 + 1;
pTileRef1 = pTileRef1 + 1;
} while (iVar2 < 36);
}
_buildingID = _buildingID + 1;
pBVar3 = pBVar3 + 0x196;
} while (_buildingID < this->maxBuildingsCount);
}
return 0;
}


}
}
}