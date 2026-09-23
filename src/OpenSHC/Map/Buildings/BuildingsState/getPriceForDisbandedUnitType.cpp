#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"





namespace OpenSHC {
namespace Map {
namespace Buildings {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040C800
void BuildingsState::getPriceForDisbandedUnitType(UnitType unitType,int *outPrice)

{
switch(unitType) {
case OpenSHC::Map::Units::UT_TUNNELER:
case OpenSHC::Map::Units::UT_E_XBOW:
*outPrice = 20;
return;
case OpenSHC::Map::Units::UT_E_ARCHER:
*outPrice = 12;
return;
case OpenSHC::Map::Units::UT_E_SPEAR:
*outPrice = 8;
return;
case OpenSHC::Map::Units::UT_E_PIKE:
*outPrice = 0x14;
return;
case OpenSHC::Map::Units::UT_E_MACE:
*outPrice = 0x14;
return;
case OpenSHC::Map::Units::UT_E_SWORD:
*outPrice = 0x28;
return;
case OpenSHC::Map::Units::UT_E_KNIGHT:
*outPrice = 40;
return;
case OpenSHC::Map::Units::UT_E_LADDER:
*outPrice = 1;
return;
case OpenSHC::Map::Units::UT_E_ENGINEER:
*outPrice = 0x1e;
return;
case OpenSHC::Map::Units::UT_E_MONK:
*outPrice = 10;
return;
case OpenSHC::Map::Units::UT_S_CATAPULT:
*outPrice = this->buildingCosts[0x50].requiredGold;
return;
case OpenSHC::Map::Units::UT_S_TREBUCHET:
*outPrice = this->buildingCosts[0x51].requiredGold;
return;
case OpenSHC::Map::Units::UT_S_MANGONEL:
*outPrice = this->buildingCosts[0x56].requiredGold;
return;
case OpenSHC::Map::Units::UT_S_TOWER:
*outPrice = this->buildingCosts[0x52].requiredGold;
return;
case OpenSHC::Map::Units::UT_S_BATTERINGRAM:
*outPrice = this->buildingCosts[0x53].requiredGold;
break;
case OpenSHC::Map::Units::UT_S_SHIELD:
*outPrice = this->buildingCosts[0x54].requiredGold;
return;
case OpenSHC::Map::Units::UT_S_BALLISTA:
*outPrice = this->buildingCosts[0x57].requiredGold;
return;
case OpenSHC::Map::Units::UT_S_FBALLISTA:
*outPrice = this->buildingCosts[0x36].requiredGold;
return;
}
return;
}


}
}
}