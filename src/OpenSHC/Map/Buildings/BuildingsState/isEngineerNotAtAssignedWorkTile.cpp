#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"



#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040E900
undefined4 BuildingsState::isEngineerNotAtAssignedWorkTile(int param_1,int param_2,int param_3)

{
int iVar1;

if (DAT_UnitsState::instance.units[param_2].field252_0x3c4 == 0) {
if (DAT_UnitsState::instance.units[param_2].resourceToDeposit != 0) {
param_3 = 0xf - param_3;
}
}
else {
param_3 = 0;
}
iVar1 = *(int *)(this->buildings[param_1].workers + param_3 * 2 + 8);
this->DAT_TempYOffset =
(int)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[iVar1];
this->DAT_TempXOffset =
iVar1 - DAT_ViewportRenderState::instance.translationMatrix[this->DAT_TempYOffset].
addXgetTile;
if ((this->DAT_TempXOffset == DAT_UnitsState::instance.units[param_2].x) &&
(this->DAT_TempYOffset == DAT_UnitsState::instance.units[param_2].y)) {
return(undefined4)( 0);
}
return(undefined4)( 1);
}


}
}
}