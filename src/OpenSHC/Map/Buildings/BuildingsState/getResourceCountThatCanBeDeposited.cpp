#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"





namespace OpenSHC {
namespace Map {
namespace Buildings {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040BFA0
int BuildingsState::getResourceCountThatCanBeDeposited(int buildingID,undefined4 resourceType,int storageLimit)

{
int iVar1;

iVar1 = this->buildings[buildingID].currentNumberOfResource;
if (storageLimit <= iVar1) {
return 0;
}
return storageLimit - iVar1;
}


}
}
}