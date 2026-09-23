#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"





namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Map::Buildings::BuildingLogicalState;
using OpenSHC::Map::Buildings::BuildingType;


/* 
  tents and tunnels
   decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040B540
void BuildingsState::removeSiegeBuildings(int attackWave,int playerID)

{
BuildingTypeShort BVar1;
Building * pBVar2;
int iVar2;

iVar2 = 1;
if (1 < this->maxBuildingsCount) {
pBVar2 = &this->buildings[1];
do {
/* 
  if: unknown != 0, owner == playerID, unknown != 3, (buildingType == TUNNEL ||
   buildingType == FIREBALLISTA || TREBUCHET || BATTERINGRAM || SIEGETOWER ||
   SHIELD): unknown = 3
 */

if ((((pBVar2->logicalState != ((BuildingLogicalState)0)) && (pBVar2->owner == playerID)) &&
(pBVar2->logicalState != OpenSHC::Map::Buildings::BLS_REMOVE)) &&
((BVar1 = pBVar2->buildingType, BVar1 == OpenSHC::Map::Buildings::BT_TUNNEL ||
(((0 < pBVar2->attackWave && (pBVar2->attackWave == attackWave)) &&
((((BVar1 == OpenSHC::Map::Buildings::BT_CATAPULT || ((BVar1 == OpenSHC::Map::Buildings::BT_FIREBALLISTA || (BVar1 == OpenSHC::Map::Buildings::BT_TREBUCHET)))) ||
(BVar1 == OpenSHC::Map::Buildings::BT_BATTERINGRAM)) || ((BVar1 == OpenSHC::Map::Buildings::BT_SIEGETOWER || (BVar1 == OpenSHC::Map::Buildings::BT_SHIELD)))))))))
) {
pBVar2->logicalState = OpenSHC::Map::Buildings::BLS_REMOVE;
}
iVar2 = iVar2 + 1;
pBVar2 = pBVar2 + 0x196;
} while (iVar2 < this->maxBuildingsCount);
}
return;
}


}
}
}