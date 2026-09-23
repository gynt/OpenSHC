#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"





namespace OpenSHC {
namespace Map {
namespace Buildings {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00424310
void BuildingsState::applyVersionUpgradeAccessibilityRecompute(PackagedFileMagicNum receivedMapVersion,PackagedFileMagicNum packagerMapVersion)

{
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::recomputeAccessibilityForAllBuildings, this)();
return;
}


}
}
}