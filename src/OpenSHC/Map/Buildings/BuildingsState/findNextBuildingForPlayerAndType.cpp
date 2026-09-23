#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"





namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Map::Buildings::BuildingLogicalState;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040AB30
int BuildingsState::findNextBuildingForPlayerAndType(PlayerID playerID,BuildingType buildingType,int buildingID)

{
int iVar1;
BuildingLogicalStateShort *pBVar2;

iVar1 = buildingID + 1;
if (iVar1 < this->maxBuildingsCount) {
pBVar2 = &this->buildings[buildingID + 1].logicalState;
do {
if ((((*pBVar2 != ((BuildingLogicalState)0)) && (*pBVar2 != OpenSHC::Map::Buildings::BLS_REMOVE)) && ((short)pBVar2[3] == playerID)) &&
((int)(short)pBVar2[1] == buildingType)) {
return iVar1;
}
iVar1 = iVar1 + 1;
pBVar2 = pBVar2 + 0x196;
} while (iVar1 < this->maxBuildingsCount);
}
return 0;
}


}
}
}