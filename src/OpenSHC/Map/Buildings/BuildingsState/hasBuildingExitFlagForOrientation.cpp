#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"



#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {




/* 
  WARNING: Enum "MappersEnum": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040B7B0
undefined4 BuildingsState::hasBuildingExitFlagForOrientation(int buildingID)

{
if (DAT_TileMapState::instance.mapOrientation == 0) {
if (this->buildings[buildingID].field_0x282 != '\0') {
return(undefined4)( 1);
}
}
else if (DAT_TileMapState::instance.mapOrientation == 2) {
if (this->buildings[buildingID].field_0x283 != '\0') {
return(undefined4)( 1);
}
}
else if (DAT_TileMapState::instance.mapOrientation == 4) {
if (this->buildings[buildingID].field_0x280 != '\0') {
return(undefined4)( 1);
}
}
else if ((DAT_TileMapState::instance.mapOrientation == 6) &&
(this->buildings[buildingID].field_0x281 != '\0')) {
return(undefined4)( 1);
}
return(undefined4)( 0);
}


}
}
}