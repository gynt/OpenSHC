#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/AI/AIVState.func.hpp"



#include "OpenSHC/Globals/DAT_AIVState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Map::Buildings::BuildingLogicalState;
using OpenSHC::WindowsHelper::Enums::BOOLEnum;


/* 
  WARNING: Enum "MappersEnumShort": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00424270
void BuildingsState::updateHeatmapBasedOnBuildingAccessibility(int playerID)

{
int _accessibility;
Building * psVar2;
int buildingID;

if (1 < this->maxBuildingsCount) {
psVar2 = &this->buildings[1];
buildingID = 1;
do {
/* 
  logicalState != 0 && != 3 and owner == playeriD and array[bildingType] == 0
   
 */

if ((((psVar2->logicalState != ((BuildingLogicalState)0)) && (psVar2->logicalState != OpenSHC::Map::Buildings::BLS_REMOVE)) &&
(psVar2->owner == playerID)) &&
(DAT_BuildingDefinedData::instance.ABuildingTypeValueArray[(short)psVar2->buildingType] == FALSE
)) {
_accessibility = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::buildingIsAccessible, this)(buildingID, 0);
if (_accessibility == 0) {
psVar2->logicalState = OpenSHC::Map::Buildings::BLS_REMOVE;
}
else if (_accessibility == 2) {
psVar2->logicalState = OpenSHC::Map::Buildings::BLS_REMOVE;
}
else if (psVar2->logicalState != OpenSHC::Map::Buildings::BLS_REMOVE) goto LAB_004242f2;
MACRO_CALL_MEMBER(OpenSHC::AI::AIVState_Func::resetCountdownInHeatMap, DAT_AIVState::ptr)((int)(short)psVar2->x, (int)((int)((short)psVar2->y)));
}
LAB_004242f2:
buildingID = buildingID + 1;
psVar2 = psVar2 + 0x196;
} while (buildingID < this->maxBuildingsCount);
}
return;
}


}
}
}