#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Random/RNG.func.hpp"



#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Map::Buildings::BuildingLogicalState;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040AEF0
int BuildingsState::pickARandomBuildingOfType(int playerID,BuildingType buildingType)

{
BuildingLogicalStateShort *pBVar1;
BuildingLogicalStateShort *pBVar2;
int iVar3;
int iVar4;

iVar4 = 0;
if (1 < this->maxBuildingsCount) {
pBVar2 = &this->buildings[1].logicalState;
iVar3 = this->maxBuildingsCount + -1;
pBVar1 = pBVar2;
do {
if ((((*pBVar1 != ((BuildingLogicalState)0)) && (*pBVar1 != OpenSHC::Map::Buildings::BLS_REMOVE)) && ((int)(short)pBVar1[1] == buildingType))
&& ((short)pBVar1[3] == playerID)) {
iVar4 = iVar4 + 1;
}
pBVar1 = pBVar1 + 0x196;
iVar3 = iVar3 + -1;
} while (iVar3 != 0);
if (0 < iVar4) {
iVar4 = (int)SEC_RNG::instance.currentNumber2 % iVar4;
MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
iVar3 = 1;
if (1 < this->maxBuildingsCount) {
do {
if (((*pBVar2 != ((BuildingLogicalState)0)) && (*pBVar2 != OpenSHC::Map::Buildings::BLS_REMOVE)) &&
(((int)(short)pBVar2[1] == buildingType &&
(((short)pBVar2[3] == playerID && (iVar4 = iVar4 + -1, iVar4 < 0)))))) {
return iVar3;
}
iVar3 = iVar3 + 1;
pBVar2 = pBVar2 + 0x196;
} while (iVar3 < this->maxBuildingsCount);
}
}
}
return 0;
}


}
}
}