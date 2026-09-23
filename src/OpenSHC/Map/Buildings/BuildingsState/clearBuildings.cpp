#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"



#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040A020
void BuildingsState::clearBuildings()

{
Building *destination;
int iVar1;

this->structCount = 0;
destination = this->buildings;
iVar1 = 2000;
do {
MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(0x32c, '\0', (void *)((int)(destination)));
destination = destination + 1;
iVar1 = iVar1 + -1;
} while (iVar1 != 0);
this->maxBuildingsCount = 2000;
return;
}


}
}
}