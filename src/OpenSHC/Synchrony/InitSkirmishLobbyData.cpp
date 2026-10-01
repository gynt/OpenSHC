#include "../Synchrony.func.hpp"

#include "OpenSHC/AI/AIVState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_00b95960.hpp"
#include "OpenSHC/Globals/DAT_00b960dc.hpp"
#include "OpenSHC/Globals/DAT_00b960f8.hpp"
#include "OpenSHC/Globals/DAT_AIVState.hpp"
#include "OpenSHC/Globals/DAT_ButtonBackgroundBlendStrength.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DWORD_00b95b1c.hpp"
#include "OpenSHC/Globals/INT_00b95950.hpp"
#include "OpenSHC/Globals/INT_00b95958.hpp"
#include "OpenSHC/Globals/INT_00b95ab8.hpp"
#include "OpenSHC/Globals/INT_00b960b0.hpp"

namespace OpenSHC {

using OpenSHC::Game::GameMode2;
using OpenSHC::WindowsHelper::Enums::BOOLEnum;

/*
  WARNING: Enum "MappersEnumShort": Some values do not have unique names
 */
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
// FUNCTION: STRONGHOLDCRUSADER 0x004274F0
void Synchrony::InitSkirmishLobbyData()
{
    int iVar1;
    MACRO_CALL_MEMBER(OpenSHC::AI::AIVState_Func::hostChecksLobbyAIVAvailability, DAT_AIVState::ptr)();
    DAT_GameSynchronyState::instance.skirmishRelated1 = -1;
    DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected = -1;
    DAT_GameSynchronyState::instance.reparseMaps = TRUE;
    DAT_GameSynchronyState::instance.field239_0x1072f8 = 0;
    DAT_GameCore::instance.mapU4Int0 = 0;
    MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setupAllMapSections, DAT_TileMapState::ptr)();
    MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::resetTeams, DAT_GameState::ptr)();
    DAT_GameSynchronyState::instance.mapName[0] = '\0';
    DAT_GameCore::instance.mapDescription[0] = '\0';
    DAT_GameCore::instance.mapDescUseStringTableIndex = 0;
    MACRO_CALL(OpenSHC::OS_Func::_memset)(DAT_MinimapViewState::instance.loadedMiniMap, 0, 80000);
    DAT_ButtonBackgroundBlendStrength::instance = 0x20;
    DAT_00b960dc::instance = 0xfffffffd;
    DWORD_00b95b1c::instance = timeGetTime();
    DAT_GameSynchronyState::instance.playerPositionsArray[0] = -10;
    DAT_GameSynchronyState::instance.playerPositionsArray[1] = -10;
    DAT_GameSynchronyState::instance.playerPositionsArray[2] = -10;
    DAT_GameSynchronyState::instance.playerPositionsArray[3] = -10;
    DAT_GameSynchronyState::instance.playerPositionsArray[4] = -10;
    DAT_GameSynchronyState::instance.playerPositionsArray[5] = -10;
    DAT_GameSynchronyState::instance.playerPositionsArray[6] = -10;
    DAT_GameSynchronyState::instance.playerPositionsArray[7] = -10;
    DAT_00b95960::instance = 0xffffffff;
    INT_00b95950::instance = -1;
    INT_00b960b0::instance = -1;
    DAT_GameCore::instance.gameMode_2 = OpenSHC::Game::GM_SKIRMISH_AND_MULTIPLAYER;
    DAT_GameSynchronyState::instance.field248_0x109250 = 6;
    INT_00b95ab8::instance = 0;
    iVar1 = 0;
    do {
        DAT_GameSynchronyState::instance.skirmishIntensityRelatedArray[iVar1]
            = DAT_RenderingDefinedData::instance
                  .SkirmishIntensityRelatedArray[0][DAT_GameSynchronyState::instance.skirmishTechLevel][iVar1];
        iVar1 = iVar1 + 1;
    } while (iVar1 < 20);
    DAT_GameSynchronyState::instance.skirmishBalanceRelatedArrayUnk1[0]
        = DAT_RenderingDefinedData::instance
              .SkirmishIntensityRelatedArray2[DAT_GameSynchronyState::instance.skirmishTechLevel][0];
    DAT_GameSynchronyState::instance.skirmishBalanceRelatedArrayUnk1[1]
        = DAT_RenderingDefinedData::instance
              .SkirmishIntensityRelatedArray2[DAT_GameSynchronyState::instance.skirmishTechLevel][1];
    DAT_GameSynchronyState::instance.skirmishBalanceRelatedArrayUnk1[2]
        = DAT_RenderingDefinedData::instance
              .SkirmishIntensityRelatedArray2[DAT_GameSynchronyState::instance.skirmishTechLevel][2];
    DAT_GameSynchronyState::instance.skirmishBalanceRelatedArrayUnk1[3]
        = DAT_RenderingDefinedData::instance
              .SkirmishIntensityRelatedArray2[DAT_GameSynchronyState::instance.skirmishTechLevel][3];
    DAT_GameSynchronyState::instance.skirmishBalanceRelatedArrayUnk1[4]
        = DAT_RenderingDefinedData::instance
              .SkirmishIntensityRelatedArray2[DAT_GameSynchronyState::instance.skirmishTechLevel][4];
    DAT_GameSynchronyState::instance.skirmishBalanceRelatedArrayUnk1[5]
        = DAT_RenderingDefinedData::instance
              .SkirmishIntensityRelatedArray2[DAT_GameSynchronyState::instance.skirmishTechLevel][5];
    DAT_GameSynchronyState::instance.skirmishBalanceRelatedArrayUnk1[6]
        = DAT_RenderingDefinedData::instance
              .SkirmishIntensityRelatedArray2[DAT_GameSynchronyState::instance.skirmishTechLevel][6];
    DAT_GameSynchronyState::instance.skirmishBalanceRelatedArrayUnk1[7]
        = DAT_RenderingDefinedData::instance
              .SkirmishIntensityRelatedArray2[DAT_GameSynchronyState::instance.skirmishTechLevel][7];
    DAT_GameSynchronyState::instance.skirmishBalanceRelatedArrayUnk1[8]
        = DAT_RenderingDefinedData::instance
              .SkirmishIntensityRelatedArray2[DAT_GameSynchronyState::instance.skirmishTechLevel][8];
    DAT_GameSynchronyState::instance.skirmishBalanceRelatedArrayUnk1[9]
        = DAT_RenderingDefinedData::instance
              .SkirmishIntensityRelatedArray2[DAT_GameSynchronyState::instance.skirmishTechLevel][9];
    DAT_GameSynchronyState::instance.skirmishStartGold
        = DAT_RenderingDefinedData::instance.StartGold[DAT_GameSynchronyState::instance.skirmishTechLevel / 2];
    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[0] = 1;
    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[1] = 1;
    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[2] = 1;
    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[3] = 1;
    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[4] = 1;
    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[5] = 1;
    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[6] = 1;
    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[7] = 1;
    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[8] = 1;
    if (DAT_GameSynchronyState::instance.isHost != FALSE) {
        DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[0] = 0xff;
        DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[1] = 0xff;
        DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[2] = 0xff;
        DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[3] = 0xff;
        DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[4] = 0xff;
        DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[5] = 0xff;
        DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[6] = 0xff;
        DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[7] = 0xff;
        DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[8] = 0xff;
        MACRO_CALL_MEMBER(
            OpenSHC::Synchrony::GameSynchronyState_Func::reorderTeamsAndPositions, DAT_GameSynchronyState::ptr)();
    }
    DAT_00b960f8::instance = 0;
    INT_00b95958::instance = 0;
}

}
