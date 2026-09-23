#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"



#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::UI::Enums::BuildingsAndStatusMenuTabType;
using OpenSHC::IO::Graphics::GmID;


/* 
  WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
 */

/* 
  WARNING: Enum "DPERRInt": Some values do not have unique names
 */

/* 
  WARNING: Enum "MappersEnum": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040DC70
void BuildingsState::createEntityForAssemblyPointsForActiveTabType()

{
short sVar1;
int iVar2;
int _tileEngineers;
int _cathedralRallyTileUnk;
int iVar3;
int *piVar4;

if (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM) {
iVar3 = 0;
do {
sVar1 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].
barracksAssemblyPoints[iVar3].x;
if (sVar1 != 0) {
iVar2 = (int)sVar1 +
DAT_ViewportRenderState::instance.translationMatrix
[DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].
barracksAssemblyPoints[iVar3].y].addXgetTile;
MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::createFloatingLayerElement, DAT_ViewportRenderState::ptr)(OpenSHC::IO::Graphics::GID_FLOATS_NEW, (int)((int)(
DAT_TileMapState::instance.field165_0x5549d0 % 10 + 0x61)), 0x12, -1, iVar2, 0xa0022);
MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::createFloatingLayerElement, DAT_ViewportRenderState::ptr)(DAT_BuildingDefinedData::instance.field382_0x9e1c[iVar3][0], (int)((int)(
DAT_BuildingDefinedData::instance.field382_0x9e1c[iVar3][1])), (int)((int)(
DAT_BuildingDefinedData::instance.field382_0x9e1c[iVar3][2] + 0x29)), (int)((int)(
DAT_BuildingDefinedData::instance.field382_0x9e1c[iVar3][3] + -0x28)), iVar2, 0xc0006);
if (iVar3 == 6) {
MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::createFloatingLayerElement, DAT_ViewportRenderState::ptr)(DAT_BuildingDefinedData::instance.field383_0x9e8c[0], (int)((int)(
DAT_BuildingDefinedData::instance.field383_0x9e8c[1])), (int)((int)(
DAT_BuildingDefinedData::instance.field383_0x9e8c[2] + 0x29)), (int)((int)(
DAT_BuildingDefinedData::instance.field383_0x9e8c[3] + -0x28)), iVar2, 0xc0006);
}
}
iVar3 = iVar3 + 1;
} while (iVar3 < 7);
return;
}
if (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST) {
iVar3 = 0;
do {
sVar1 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].
mercenaryAssemblyPoints[iVar3][0];
if (sVar1 != 0) {
iVar2 = (int)sVar1 +
DAT_ViewportRenderState::instance.translationMatrix
[DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].
mercenaryAssemblyPoints[iVar3][1]].addXgetTile;
MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::createFloatingLayerElement, DAT_ViewportRenderState::ptr)(OpenSHC::IO::Graphics::GID_FLOATS_NEW, (int)((int)(
DAT_TileMapState::instance.field165_0x5549d0 % 10 + 0x61)), 0x12, -1, iVar2, 0xa0022);
MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::createFloatingLayerElement, DAT_ViewportRenderState::ptr)(DAT_BuildingDefinedData::instance.field384_0x9e9c[iVar3][0], (int)((int)(
DAT_BuildingDefinedData::instance.field384_0x9e9c[iVar3][1])), (int)((int)(
DAT_BuildingDefinedData::instance.field384_0x9e9c[iVar3][2] + 0x29)), (int)((int)(
DAT_BuildingDefinedData::instance.field384_0x9e9c[iVar3][3] + -0x28)), iVar2, 0xc0006);
if (iVar3 == 1) {
MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::createFloatingLayerElement, DAT_ViewportRenderState::ptr)(DAT_BuildingDefinedData::instance.field383_0x9e8c[0], (int)((int)(
DAT_BuildingDefinedData::instance.field383_0x9e8c[1])), (int)((int)(
DAT_BuildingDefinedData::instance.field383_0x9e8c[2] + 0x29)), (int)((int)(
DAT_BuildingDefinedData::instance.field383_0x9e8c[3] + -0x28)), iVar2, 0xc0006);
}
}
iVar3 = iVar3 + 1;
} while (iVar3 < 7);
return;
}
if (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_ENGINEERSGUILD) {
iVar3 = 0;
piVar4 = DAT_BuildingDefinedData::instance.field401_0x9f1c[0] + 2;
do {
sVar1 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].
engineersAssemblyPoints[iVar3].x;
if (sVar1 != 0) {
_tileEngineers =
(int)sVar1 +
DAT_ViewportRenderState::instance.translationMatrix
[DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].
engineersAssemblyPoints[iVar3].y].addXgetTile;
MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::createFloatingLayerElement, DAT_ViewportRenderState::ptr)(OpenSHC::IO::Graphics::GID_FLOATS_NEW, (int)((int)(
DAT_TileMapState::instance.field165_0x5549d0 % 10 + 0x61)), 0x12, -1, _tileEngineers, 0xa0022);
MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::createFloatingLayerElement, DAT_ViewportRenderState::ptr)((*(int (*) [4])(piVar4 + -2))[0], (int)((int)(piVar4[-1])), (int)((int)(
*piVar4 + 0x29)), (int)((int)(piVar4[1] + -0x28)), _tileEngineers, 0xc0006);
}
piVar4 = piVar4 + 4;
iVar3 = iVar3 + 1;
} while ((int)piVar4 < 0x5c18b8);
return;
}
if (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_TUNNELERSGUILD) {
sVar1 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].
tunnelersGuildAssemblyPointX;
if (sVar1 != 0) {
iVar3 = (int)sVar1 +
DAT_ViewportRenderState::instance.translationMatrix
[DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].
tunnelersGuildAssemblyPointY].addXgetTile;
MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::createFloatingLayerElement, DAT_ViewportRenderState::ptr)(OpenSHC::IO::Graphics::GID_FLOATS_NEW, (int)((int)(
DAT_TileMapState::instance.field165_0x5549d0 % 10 + 0x61)), 0x12, -1, iVar3, 0xa0022);
MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::createFloatingLayerElement, DAT_ViewportRenderState::ptr)(OpenSHC::IO::Graphics::GID_BODY_TUNNELOR, 3, 0xe, -0x28, iVar3, 0xc0006);
return;
}
}
else if (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_CATHEDRAL) {
sVar1 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].
cathedralAssemblyPointX;
if (sVar1 != 0) {
_cathedralRallyTileUnk =
(int)sVar1 +
DAT_ViewportRenderState::instance.translationMatrix
[DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].
cathedralAssemblyPointY].addXgetTile;
MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::createFloatingLayerElement, DAT_ViewportRenderState::ptr)(OpenSHC::IO::Graphics::GID_FLOATS_NEW, (int)((int)(
DAT_TileMapState::instance.field165_0x5549d0 % 10 + 0x61)), 0x12, -1, _cathedralRallyTileUnk, 
0xa0022);
MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::createFloatingLayerElement, DAT_ViewportRenderState::ptr)(OpenSHC::IO::Graphics::GID_BODY_FIGHTING_MONK, 3, 0xe, -0x28, _cathedralRallyTileUnk, 
0xc0006);
}
}
return;
}


}
}
}