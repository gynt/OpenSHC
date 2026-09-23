#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Random/RNG.func.hpp"



#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Map::Buildings::BuildingLogicalState;
using OpenSHC::Map::Buildings::BuildingType;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040B090
int BuildingsState::pickARandomPositiveFearFactorBuilding(int playerID)

{
BuildingTypeShort BVar1;
BuildingTypeShort *pBVar2;
int iVar3;
int _rng;
BuildingTypeShort *pBVar4;
int iVar5;

iVar5 = 0;
if (1 < this->maxBuildingsCount) {
pBVar4 = &this->buildings[1].buildingType;
iVar3 = this->maxBuildingsCount + -1;
pBVar2 = pBVar4;
do {
if ((((pBVar2[-1] != ((BuildingLogicalState)0)) && (pBVar2[-1] != OpenSHC::Map::Buildings::BLS_REMOVE)) && ((short)pBVar2[2] == playerID)) &&
(((((BVar1 = *pBVar2, BVar1 == OpenSHC::Map::Buildings::BT_MAYPOLE || (BVar1 == OpenSHC::Map::Buildings::BT_GARDEN)) ||
((BVar1 == OpenSHC::Map::Buildings::BT_STATUE || ((BVar1 == OpenSHC::Map::Buildings::BT_SHRINE || (BVar1 == OpenSHC::Map::Buildings::BT_DANCINGBEAR)))))) ||
(BVar1 == OpenSHC::Map::Buildings::BT_POND)) || ((BVar1 == OpenSHC::Map::Buildings::BT_WELL || (BVar1 == OpenSHC::Map::Buildings::BT_BEEHIVE)))))) {
iVar5 = iVar5 + 1;
}
pBVar2 = pBVar2 + 0x196;
iVar3 = iVar3 + -1;
} while (iVar3 != 0);
if (0 < iVar5) {
_rng = (int)SEC_RNG::instance.currentNumber2 % iVar5;
MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
iVar5 = 1;
if (1 < this->maxBuildingsCount) {
do {
if ((((pBVar4[-1] != ((BuildingLogicalState)0)) && (pBVar4[-1] != OpenSHC::Map::Buildings::BLS_REMOVE)) && ((short)pBVar4[2] == playerID))
&& (((((BVar1 = *pBVar4, BVar1 == OpenSHC::Map::Buildings::BT_MAYPOLE || (BVar1 == OpenSHC::Map::Buildings::BT_GARDEN)) ||
((BVar1 == OpenSHC::Map::Buildings::BT_STATUE || ((BVar1 == OpenSHC::Map::Buildings::BT_SHRINE || (BVar1 == OpenSHC::Map::Buildings::BT_DANCINGBEAR)))))) ||
((BVar1 == OpenSHC::Map::Buildings::BT_POND || ((BVar1 == OpenSHC::Map::Buildings::BT_WELL || (BVar1 == OpenSHC::Map::Buildings::BT_BEEHIVE)))))) &&
(_rng = _rng + -1, _rng < 0)))) {
return iVar5;
}
iVar5 = iVar5 + 1;
pBVar4 = pBVar4 + 0x196;
} while (iVar5 < this->maxBuildingsCount);
}
}
}
return 0;
}


}
}
}