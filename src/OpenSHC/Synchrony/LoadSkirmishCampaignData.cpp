#include "../Synchrony.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Synchrony.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/TrailType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/CHAR_ARRAY_00eb0ab0.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"
#include "OpenSHC/Game/CampaignTrailMission.hpp"

namespace OpenSHC {

using OpenSHC::Commands::GameCommandType;
using OpenSHC::Game::GameMode;
using OpenSHC::Game::TrailType;
using OpenSHC::WindowsHelper::Enums::BOOLEnum;
using OpenSHC::Game::CampaignTrailMission;

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
// FUNCTION: STRONGHOLDCRUSADER 0x004C6B20
void Synchrony::LoadSkirmishCampaignData(int missionID)
{
    char cVar1;
    byte bVar2;
    char* pcVar3;
    int* piVar4;
    int iVar5;
    int iVar6;
    int iVar7;
    char (*pacVar8)[250];
    CampaignTrailMission* pCVar9;
    pCVar9 = DAT_SkirmishDefinedData::instance.SkirmishTrailMissions + missionID;
    if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_EXTREME) {
        pCVar9 = DAT_SkirmishDefinedData::instance.ExtremeTrailMissions + missionID;
    } else if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_WARCHEST) {
        pCVar9 = DAT_SkirmishDefinedData::instance.WarchestTrailMissions + missionID;
    }
    pcVar3 = (char *)(pCVar9->mapNameAddress);
    iVar7 = (int)CHAR_ARRAY_00eb0ab0::instance - (int)pcVar3;
    do {
        cVar1 = *pcVar3;
        pcVar3[iVar7] = cVar1;
        pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
    MACRO_CALL(OpenSHC::OS_Func::_memset)(DAT_GameSynchronyState::instance.DAT_PlayerNames, 0, 0x8ca);
    piVar4 = DAT_GameSynchronyState::instance.currentAIArray;
    do {
        piVar4[-0x1b] = -1;
        *piVar4 = 0;
        piVar4[9] = -1;
        piVar4 = piVar4 + 1;
    } while ((int)piVar4 < 0x191dea0);
    pcVar3
        = MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::getTextArrayPointer, DAT_UserTextHandlerState::ptr)(0);
    pacVar8 = DAT_GameSynchronyState::instance.DAT_PlayerNames + 1;
    do {
        cVar1 = *pcVar3;
        (*pacVar8)[0] = cVar1;
        pcVar3 = pcVar3 + 1;
        pacVar8 = (char (*)[250])(*pacVar8 + 1);
    } while (cVar1 != '\0');
    DAT_GameSynchronyState::instance.isHost = TRUE;
    DAT_GameSynchronyState::instance.currentGameMode = OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER;
    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
        OpenSHC::Commands::GCT_ASK_FOR_SLOT_ASSIGNMENT);
    if (1 < pCVar9->numberOfPlayers) {
        piVar4 = &pCVar9->player2AI;
        iVar7 = 1;
        do {
            iVar5 = iVar7 + 1;
            DAT_GameSynchronyState::instance.currentAIArray[iVar7 + 1] = *piVar4;
            MACRO_CALL(OpenSHC::Synchrony_Func::ResetAiVariationArrayValue)(iVar5);
            piVar4 = piVar4 + 1;
            iVar7 = iVar5;
        } while (iVar5 < pCVar9->numberOfPlayers);
    }
    MACRO_CALL(OpenSHC::Synchrony_Func::SetAIPlayerNickNames)();
    iVar7 = pCVar9->numberOfPlayers;
    iVar5 = 0;
    piVar4 = &pCVar9->team1;
    do {
        DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[iVar5 + 1] = (byte)*piVar4;
        if (iVar7 <= iVar5) {
            DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[iVar5 + 1] = 0xff;
        }
        iVar5 = iVar5 + 1;
        piVar4 = piVar4 + 1;
    } while (iVar5 < 8);
    iVar7 = 0;
    iVar5 = 1;
    do {
        bVar2 = DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[iVar5];
        iVar6 = (int)(char)bVar2;
        DAT_GameState::instance.mapAndTime.playerGroupArray[iVar5] = iVar6;
        if (('\0' < (char)bVar2) && (DAT_GameState::instance.mapAndTime.playerTeams[iVar5] = iVar6, iVar7 < iVar6)) {
            iVar7 = iVar6;
        }
        iVar5 = iVar5 + 1;
    } while (iVar5 < 9);
    iVar5 = 1;
    do {
        if (DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[iVar5] == 0) {
            iVar7 = iVar7 + 1;
            DAT_GameState::instance.mapAndTime.playerTeams[iVar5] = iVar7;
        }
        iVar5 = iVar5 + 1;
    } while (iVar5 < 9);
    DAT_GameSynchronyState::instance.skirmishCurrentAdvantageBalance = pCVar9->fairness;
    DAT_GameSynchronyState::instance.skirmishGameIntensityType = pCVar9->startLevels;
    DAT_GameSynchronyState::instance.playerPositionsArray[0] = -10;
    DAT_GameSynchronyState::instance.playerPositionsArray[1] = -10;
    DAT_GameSynchronyState::instance.playerPositionsArray[2] = -10;
    DAT_GameSynchronyState::instance.playerPositionsArray[3] = -10;
    DAT_GameSynchronyState::instance.playerPositionsArray[4] = -10;
    DAT_GameSynchronyState::instance.playerPositionsArray[5] = -10;
    DAT_GameSynchronyState::instance.playerPositionsArray[6] = -10;
    DAT_GameSynchronyState::instance.playerPositionsArray[7] = -10;
    piVar4 = &pCVar9->position1;
    iVar7 = 0;
    do {
        if (*piVar4 != 0) {
            DAT_GameSynchronyState::instance.field294_0x109e5f[*piVar4 + 8] = (byte)iVar7;
        }
        iVar7 = iVar7 + 1;
        piVar4 = piVar4 + 1;
    } while (iVar7 < 8);
}

}
