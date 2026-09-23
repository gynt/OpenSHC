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


// FUNCTION: STRONGHOLDCRUSADER 0x0040AFB0
int BuildingsState::pickARandomBuildingIDOfTheseThreeTypes(int playerID,BuildingType buildingType1,BuildingType buildingType2,BuildingType buildingType3)

{
BuildingTypeShort _buildingType;
BuildingTypeShort *pBVar1;
BuildingTypeShort *pBVar2;
int iVar3;
int iVar4;

if (1 < this->maxBuildingsCount) {
pBVar2 = &this->buildings[1].buildingType;
iVar3 = this->maxBuildingsCount + -1;
iVar4 = 0;
pBVar1 = pBVar2;
do {
if ((((pBVar1[-1] != ((BuildingLogicalState)0)) && (pBVar1[-1] != OpenSHC::Map::Buildings::BLS_REMOVE)) &&
((__buildingType = (BuildingType)(short)*pBVar1, __buildingType == buildingType1 ||
((__buildingType == buildingType2 || (__buildingType == buildingType3)))))) &&
((short)pBVar1[2] == playerID)) {
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
if ((((pBVar2[-1] != ((BuildingLogicalState)0)) && (pBVar2[-1] != OpenSHC::Map::Buildings::BLS_REMOVE)) &&
(((__buildingType = (BuildingType)(short)*pBVar2, __buildingType == buildingType1 ||
((__buildingType == buildingType2 || (__buildingType == buildingType3)))) &&
((short)pBVar2[2] == playerID)))) && (iVar4 = iVar4 + -1, iVar4 < 0)) {
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