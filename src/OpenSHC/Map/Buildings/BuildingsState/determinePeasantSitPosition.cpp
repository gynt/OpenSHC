#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"



#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040F460
undefined4 BuildingsState::determinePeasantSitPosition(int campfireID,int availablePeasants)

{
int iVar1;

if (24 < availablePeasants) {
availablePeasants = 23;
}
iVar1 = *(int *)(this->buildings[campfireID].workers + availablePeasants * 2 + 8);
this->campfireSpotY =
(int)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[iVar1];
this->campfireSpotX =
iVar1 - DAT_ViewportRenderState::instance.translationMatrix[this->campfireSpotY].
addXgetTile;
MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::calculatePreferredRelativeOrientation, DAT_DirectionAlgorithmState::ptr)(this->campfireSpotX, 
this->campfireSpotY, (int)((int)((short)this->buildings[campfireID].x + 3)), (int)((int)(
(short)this->buildings[campfireID].y + 3)));
this->campfireSpotOrientation = DAT_DirectionAlgorithmState::instance.orientation;
return(undefined4)( 1);
}


}
}
}