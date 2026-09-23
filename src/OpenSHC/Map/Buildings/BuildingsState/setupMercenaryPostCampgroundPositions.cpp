#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"



#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Map::Buildings::BuildingLogicalState;
using OpenSHC::Map::Buildings::BuildingType;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040D400
void BuildingsState::setupMercenaryPostCampgroundPositions(int playerID)

{
BuildingTypeShort BVar1;
ushort uVar2;
ushort uVar3;
short *psVar4;
short *psVar5;
Building * _ptrBuilding;
short *_ptrStructureStartPlus2;
short *psVar6;
int iVar7;
int _buildingID;
int _bID;
int _chosenParadeGround3;
int _chosenParadeGround4;
int _chosenBuilding;
int *local_10;
short *local_c;
int *_pIndex;
int _pType;
int _pType2;
int _pType3;
int _mercenaryOutpostID;
int _paradeGround3Unk;
int _paradeGround4Unk;
ushort _x;
ushort _y;

_chosenParadeGround3 = 0;
_chosenParadeGround4 = 0;
_chosenBuilding = 0;
MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(1728, '\0', (void *)((int)(&DAT_GameState::instance.playerDataArray[playerID].structure)));
_mercenaryOutpostID = DAT_GameState::instance.playerDataArray[playerID].mercenaryPost.id;
DAT_GameState::instance.playerDataArray[playerID].structureRelated1 = 0;
if ((0 < _mercenaryOutpostID) && (_buildingID = 1, 1 < this->maxBuildingsCount)) {
_ptrBuilding = &this->buildings[1];
do {
_paradeGround3Unk = _chosenParadeGround3;
_paradeGround4Unk = _chosenParadeGround4;
if ((((((_ptrBuilding->logicalState != ((BuildingLogicalState)0)) &&
(_ptrBuilding->logicalState != OpenSHC::Map::Buildings::BLS_REMOVE)) &&
(_ptrBuilding->owner == playerID)) &&
(((BVar1 = _ptrBuilding->buildingType, BVar1 == OpenSHC::Map::Buildings::BT_PARADEGROUND2 ||
(BVar1 == OpenSHC::Map::Buildings::BT_PARADEGROUND3)) || (BVar1 == OpenSHC::Map::Buildings::BT_PARADEGROUND4)))) &&
((this->buildings[(short)_ptrBuilding->quarryStockpileID].buildingType
== OpenSHC::Map::Buildings::BT_MERCENARYPOST && (_paradeGround3Unk = _buildingID, BVar1 != OpenSHC::Map::Buildings::BT_PARADEGROUND2))))
&& ((_paradeGround3Unk = _chosenParadeGround3, _paradeGround4Unk = _buildingID,
BVar1 != OpenSHC::Map::Buildings::BT_PARADEGROUND3 &&
(_paradeGround4Unk = _chosenParadeGround4, BVar1 == OpenSHC::Map::Buildings::BT_PARADEGROUND4)))) {
_chosenBuilding = _buildingID;
}
_chosenParadeGround4 = _paradeGround4Unk;
_chosenParadeGround3 = _paradeGround3Unk;
_buildingID = _buildingID + 1;
_ptrBuilding = _ptrBuilding + 0x196;
} while (_buildingID < this->maxBuildingsCount);
if (((_chosenParadeGround3 != 0) && (_chosenParadeGround4 != 0)) && (_chosenBuilding != 0)) {
local_c = &DAT_GameState::instance.playerDataArray[playerID].structure.xyPairs2[0].y;
DAT_GameState::instance.playerDataArray[playerID].structureRelated1 = 72;
local_10 = DAT_BuildingDefinedData::instance.PlayerDataUnknownStructureRelatedArray_2[0] + 1;
_pIndex = DAT_BuildingDefinedData::instance.PlayerDataUnknownStructureRelatedArray_1;
playerID = _buildingID;
/* 
  
   playerID is now buildingID
 */

do {
_pType = (*(int (*) [3])(local_10 + -1))[0];
_bID = _chosenParadeGround3;
if (((_pType == 0) || (_bID = _chosenParadeGround4, _pType == 1)) ||
(_bID = _chosenBuilding, _pType == 2)) {
playerID = _bID;
}
_x = this->buildings[playerID].x;
_y = this->buildings[playerID].y;
_ptrStructureStartPlus2 = local_c + -0x30;
psVar5 = &DAT_BuildingDefinedData::instance.PlayerDataUnknownStructureRelatedArray_3[*_pIndex][0].y;
iVar7 = 24;
psVar4 = psVar5;
do {
_ptrStructureStartPlus2[-1] = ((XYPairShort *)(psVar4 + -1))->x + _x;
*_ptrStructureStartPlus2 = *psVar4 + _y;
psVar4 = psVar4 + 2;
_ptrStructureStartPlus2 = _ptrStructureStartPlus2 + 2;
iVar7 = iVar7 + -1;
} while (iVar7 != 0);
_pType2 = *local_10;
if (_pType2 == 0) {
playerID = _chosenParadeGround3;
}
else if (_pType2 == 1) {
playerID = _chosenParadeGround4;
}
else if (_pType2 == 2) {
playerID = _chosenBuilding;
}
uVar2 = this->buildings[playerID].x;
uVar3 = this->buildings[playerID].y;
iVar7 = 24;
psVar4 = psVar5;
psVar6 = local_c;
do {
((XYPairShort *)(psVar6 + -1))->x = ((XYPairShort *)(psVar4 + -1))->x + uVar2;
*psVar6 = *psVar4 + uVar3;
psVar4 = psVar4 + 2;
psVar6 = psVar6 + 2;
iVar7 = iVar7 + -1;
} while (iVar7 != 0);
_pType3 = local_10[1];
if (_pType3 == 0) {
playerID = _chosenParadeGround3;
}
else if (_pType3 == 1) {
playerID = _chosenParadeGround4;
}
else if (_pType3 == 2) {
playerID = _chosenBuilding;
}
uVar2 = this->buildings[playerID].x;
uVar3 = this->buildings[playerID].y;
psVar4 = local_c + 0x30;
iVar7 = 24;
do {
psVar4[-1] = ((XYPairShort *)(psVar5 + -1))->x + uVar2;
*psVar4 = *psVar5 + uVar3;
psVar5 = psVar5 + 2;
psVar4 = psVar4 + 2;
iVar7 = iVar7 + -1;
} while (iVar7 != 0);
local_10 = local_10 + 3;
local_c = local_c + 0x90;
_pIndex = _pIndex + 1;
} while ((int)_pIndex < 0x5c1680);
}
}
return;
}


}
}
}