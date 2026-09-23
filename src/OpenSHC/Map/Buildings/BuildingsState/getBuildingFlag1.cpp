#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"





namespace OpenSHC {
namespace Map {
namespace Buildings {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040F440
int BuildingsState::getBuildingFlag1(int param_1)

{
return (int)this->buildings[param_1].flag1;
}


}
}
}