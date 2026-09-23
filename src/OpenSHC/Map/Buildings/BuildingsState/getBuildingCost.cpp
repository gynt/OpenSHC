#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"





namespace OpenSHC {
namespace Map {
namespace Buildings {




/* 
  WARNING: Enum "MappersEnum": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040C5F0
void BuildingsState::getBuildingCost(MappersEnum commandBuildingType,int *pStone,int *pGold)

{
BuildingType _buildingType;

/* 
  This function seems to neither dirty ECX nor EDX, which might cause issues,
   because the compiler knew it, but ghidra does not get it.
   -TheRedDaemon
 */

_buildingType = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::convertCommandBuildingTypeToBuildingType, this)(commandBuildingType);
/* 
  Types of the extraouts are guessed based on the code at the moment.
   -TheRedDaemon
 */

*pStone = this->buildingCosts[_buildingType].requiredStone_0x4;
*pGold = this->buildingCosts[_buildingType].requiredGold;
if ((int)commandBuildingType < 357) {
if (commandBuildingType == 357) {
*pGold = this->buildingCosts[0x36].requiredGold;
}
else {
switch(commandBuildingType) {
case OpenSHC::Commands::M_MAPPER_KILLING_PIT:
case OpenSHC::Commands::M_MAPPER_BRAZIER:
*pGold = 5;
return;
case OpenSHC::Commands::M_MAPPER_PITCH_DITCH:
*pGold = 2;
return;
case OpenSHC::Commands::M_MAPPER_MOAT:
case OpenSHC::Commands::M_MAPPER_PEOPLE_LADDERMEN:
*pGold = 1;
return;
case OpenSHC::Commands::M_MAPPER_MANGONEL:
*pGold = this->buildingCosts[0x56].requiredGold;
return;
case OpenSHC::Commands::M_MAPPER_BALLISTA:
*pGold = this->buildingCosts[0x57].requiredGold;
return;
case OpenSHC::Commands::M_MAPPER_PEOPLE_ARCHERS:
*pGold = 0xc;
return;
case OpenSHC::Commands::M_MAPPER_PEOPLE_SPEARMEN:
*pGold = 8;
return;
case OpenSHC::Commands::M_MAPPER_PEOPLE_PIKEMEN:
case OpenSHC::Commands::M_MAPPER_PEOPLE_MACEMEN:
case OpenSHC::Commands::M_MAPPER_PEOPLE_XBOWMEN:
case OpenSHC::Commands::M_MAPPER_PEOPLE_TUNNELERS:
*pGold = 0x14;
return;
case OpenSHC::Commands::M_MAPPER_PEOPLE_SWORDSMEN:
case OpenSHC::Commands::M_MAPPER_PEOPLE_KNIGHTS:
*pGold = 0x28;
return;
case OpenSHC::Commands::M_MAPPER_PEOPLE_ENGINEERS:
*pGold = 0x1e;
return;
case OpenSHC::Commands::M_MAPPER_PEOPLE_MONKS:
*pGold = 10;
return;
case OpenSHC::Commands::M_MAPPER_PEOPLE_CATAPULTS:
*pGold = this->buildingCosts[0x50].requiredGold;
return;
case OpenSHC::Commands::M_MAPPER_PEOPLE_TREBUCHETS:
*pGold = this->buildingCosts[0x51].requiredGold;
return;
case OpenSHC::Commands::M_MAPPER_PEOPLE_BATTERING_RAMS:
*pGold = this->buildingCosts[0x53].requiredGold;
return;
case OpenSHC::Commands::M_MAPPER_PEOPLE_SIEGE_TOWERS:
*pGold = this->buildingCosts[0x52].requiredGold;
return;
case OpenSHC::Commands::M_MAPPER_PEOPLE_PORTABLE_SHIELDS:
*pGold = this->buildingCosts[0x54].requiredGold;
return;
}
}
}
return;
}


}
}
}