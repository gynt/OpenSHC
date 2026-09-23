#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"



#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040B660
undefined4 BuildingsState::prepareCampgroundCoords(int playerID)

{
short sVar1;
int iVar2;
int _campground;

_campground = DAT_GameState::instance.playerDataArray[playerID].campground.id;
if (_campground < 1) {
return(undefined4)( 0);
}
sVar1 = this->buildings[_campground].orientation;
if (sVar1 == 4) {
this->DAT_TempXOffset = (short)this->buildings[_campground].x + 3;
this->DAT_TempYOffset = (short)this->buildings[_campground].y + 5;
return(undefined4)( 1);
}
if (sVar1 == 2) {
this->DAT_TempXOffset = (short)this->buildings[_campground].x + 1;
}
else {
iVar2 = (int)(short)this->buildings[_campground].x;
if (sVar1 != 6) {
this->DAT_TempXOffset = iVar2 + 3;
this->DAT_TempYOffset = (short)this->buildings[_campground].y + 1;
return(undefined4)( 1);
}
this->DAT_TempXOffset = iVar2 + 5;
}
this->DAT_TempYOffset = (short)this->buildings[_campground].y + 3;
return(undefined4)( 1);
}


}
}
}