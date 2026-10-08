#include "../Actions.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/AI/AIVState.func.hpp"
#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Game/Skirmish/SkirmishLobbySetupStructure.func.hpp"
#include "OpenSHC/IO/FilePackager.func.hpp"
#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/WildlifeState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Rendering/Bink/AIMessageQueue.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/Synchrony.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/MenuTextInputState.func.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Game/TrailType.hpp"
#include "OpenSHC/IO/FileResourceType.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Game/Market/BuySellPair.hpp"
#include "OpenSHC/Game/Player/PlayerData.hpp"
#include "OpenSHC/Game/Skirmish/SkirmishStatistics.hpp"
#include "OpenSHC/Game/Skirmish/StartingResourceStructureInt.hpp"
#include "OpenSHC/Globals/DAT_00b960dc.hpp"
#include "OpenSHC/Globals/DAT_00b960f8.hpp"
#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_AIVPlacementFit.hpp"
#include "OpenSHC/Globals/DAT_AIVState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapDefinedData.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_MissionDefinedData.hpp"
#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UIDragDropDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_VideoBikQueue.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_WildlifeState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/DWORD_00b95b1c.hpp"
#include "OpenSHC/Globals/FilePackagerObj.hpp"
#include "OpenSHC/Globals/INT_00b960f0.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"
#include "OpenSHC/Globals/PTR_005c2a68.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"
#include "OpenSHC/Globals/SEC_SkirmishLobbySetupStructure.hpp"
#include "OpenSHC/Globals/TIME_ReceivedMessage_2.hpp"

namespace OpenSHC {
namespace UI {

    using AI::AIType;
    using Commands::MappersEnum;
    using Game::GameMode;
    using Game::GameMode2;
    using Game::TrailType;
    using IO::FileResourceType;
    using Map::Entities::EntityType;
    using UI::Enums::BuildingsAndStatusMenuTabType;
    using UI::Enums::MenuViewType;
    using WindowsHelper::Enums::BOOLEnum;
    using Game::Market::BuySellPair;
    using Game::Player::PlayerData;
    using Game::Skirmish::SkirmishStatistics;
    using Game::Skirmish::StartingResourceStructureInt;

    /*
      This function stores a bunch of variables a .map file shouldn't overwrite, to then reapply those   stored info to
      the game again. For example, a .map file could contain the results of a skirmish,   but of course you don't want
      that if you start a game new and fresh   decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00441270
    void Actions::LaunchSkirmishGame(int whichCastle)
    {
        char cVar1;
        byte bVar2;
        ushort uVar3;
        short sVar4;
        int iVar5;
        int iVar6;
        int iVar7;
        int iVar8;
        int iVar9;
        int iVar10;
        int iVar11;
        int iVar12;
        BOOLEnum BVar13;
        char* pcVar14;
        uint uVar15;
        int _charIndex;
        char* pcVar16;
        int _playerIDby4;
        int iVar17;
        int iVar18;
        int _playerPosition;
        int _fitPercentage;
        uint uVar19;
        int _lordType;
        int _aiNumber;
        int _index;
        BuySellPair* pBVar20;
        int _finalResultsIndex;
        int _arrayIndex1;
        int _indexFinalResults;
        int _counter;
        PlayerData* _pKeepPlayer2;
        int _resourceIndex;
        char (*pacVar21)[250];
        int* _ptrAIVID;
        int _advantage;
        SkirmishLobbySetupStructure* _ptrSection1124;
        GameSynchronyState* _pFinalResults;
        undefined4* puVar22;
        dword* pdVar23;
        PlayerData* piVar14;
        int _playerID;
        StartingResourceStructureInt* pSVar24;
        int* piVar26;
        int (*_startingTroopsPlayerData)[20];
        int iVar25;
        SkirmishStatistics* pSVar26;
        PlayerData* pAVar27;
        int* piVar27;
        int _ptrFinalResults;
        int (*_killMatrix)[9];
        undefined1 auStack_d8c[4];
        dword _playerIndex;
        char (*_aiType2)[250];
        int* local_d80;
        int _whichCastle;
        int _s1023;
        int _section1093;
        int _autoSaveMinutes;
        int _storedCurrentAIArray[9];
        int _storedLordTypes[9];
        int _storedArray1[9];
        int _playerTeams[9];
        int local_ca0;
        int local_c9c;
        dword _mapMagicU4Int2[66];
        undefined4 local_b78[477];
        char uStack1025;
        char _mapName[1000];
        int _keepBuildingID;
        uint _keepID;
        int _delay;
        int _anotherPlayerIDUnk;
        GameModeInt _gameMode;
        int _seed;
        uVar15 = MSVC_SecurityCookie::instance ^ (uint)auStack_d8c;
        _whichCastle = whichCastle;
        MACRO_CALL_MEMBER(Game::Skirmish::SkirmishLobbySetupStructure_Func::commitSkirmishSettings,
            SEC_SkirmishLobbySetupStructure::ptr)();
        _gameMode = DAT_GameSynchronyState::instance.currentGameMode;
        _ptrSection1124 = SEC_SkirmishLobbySetupStructure::ptr;
        pdVar23 = _mapMagicU4Int2;
        for (_arrayIndex1 = 66; _arrayIndex1 != 0; _arrayIndex1 = _arrayIndex1 + -1) {
            *pdVar23 = _ptrSection1124->mapu4int2;
            _ptrSection1124 = (SkirmishLobbySetupStructure*)&_ptrSection1124->mbr_0x4;
            pdVar23 = pdVar23 + 1;
        }
        _s1023 = DAT_GameState::instance.mapAndTime.skirmishFogOfWar;
        _autoSaveMinutes = DAT_GameSynchronyState::instance.skirmishAutoSaveEveryMinutes;
        DAT_AIVPlacementFit::instance[0] = -10;
        DAT_AIVPlacementFit::instance[1] = -10;
        DAT_AIVPlacementFit::instance[2] = -10;
        DAT_AIVPlacementFit::instance[3] = -10;
        DAT_AIVPlacementFit::instance[4] = -10;
        DAT_AIVPlacementFit::instance[5] = -10;
        DAT_AIVPlacementFit::instance[6] = -10;
        DAT_AIVPlacementFit::instance[7] = -10;
        DAT_AIVPlacementFit::instance[8] = -10;
        _section1093 = DAT_GameSynchronyState::instance.skirmishPoints;
        DAT_GameCore::instance.missionNumber1to20 = 1;
        _charIndex = 0;
        do {
            cVar1 = DAT_GameSynchronyState::instance.mapName[_charIndex];
            _mapName[_charIndex] = cVar1;
            _charIndex = _charIndex + 1;
        } while (cVar1 != '\0');
        /*
          this appends .map to the map name
         */
        pcVar14 = &uStack1025;
        do {
            pcVar16 = pcVar14;
            pcVar14 = pcVar16 + 1;
        } while (pcVar16[1] != '\0');
        /*
          .map
         */
        strcpy(pcVar16 + 1, ".map");
        MACRO_CALL_MEMBER(IO::ResourceManager_Func::resolveResourceFileName, DAT_ResourceManager::ptr)(
            IO::FRT_MAPS, (char const*)((int)(_mapName)));
        MACRO_CALL_MEMBER(Map::TileMapState_Func::setupAllMapSections, DAT_TileMapState::ptr)();
        _playerID = 0;
        for (_playerIDby4 = 1; _playerIDby4 < 9; _playerIDby4 += 4) {
            bVar2 = DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[_playerIDby4];
            iVar25 = (int)(char)bVar2;
            DAT_GameState::instance.mapAndTime.playerGroupArray[_playerIDby4] = iVar25;
            if (('\0' < (char)bVar2)
                && (DAT_GameState::instance.mapAndTime.playerTeams[_playerIDby4] = iVar25, _playerID < iVar25)) {
                _playerID = iVar25;
            }
            bVar2 = DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[_playerIDby4 + 1];
            iVar25 = (int)(char)bVar2;
            DAT_GameState::instance.mapAndTime.playerGroupArray[_playerIDby4 + 1] = iVar25;
            if (('\0' < (char)bVar2)
                && (DAT_GameState::instance.mapAndTime.playerTeams[_playerIDby4 + 1] = iVar25, _playerID < iVar25)) {
                _playerID = iVar25;
            }
            bVar2 = DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[_playerIDby4 + 2];
            iVar25 = (int)(char)bVar2;
            DAT_GameState::instance.mapAndTime.playerGroupArray[_playerIDby4 + 2] = iVar25;
            if (('\0' < (char)bVar2)
                && (DAT_GameState::instance.mapAndTime.playerTeams[_playerIDby4 + 2] = iVar25, _playerID < iVar25)) {
                _playerID = iVar25;
            }
            bVar2 = DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[_playerIDby4 + 3];
            iVar25 = (int)(char)bVar2;
            DAT_GameState::instance.mapAndTime.playerGroupArray[_playerIDby4 + 3] = iVar25;
            if (('\0' < (char)bVar2)
                && (DAT_GameState::instance.mapAndTime.playerTeams[_playerIDby4 + 3] = iVar25, _playerID < iVar25)) {
                _playerID = iVar25;
            }
            BVar13 = DAT_GameCore::instance.isSkirmishTrail;
            _seed = SEC_RNG::instance.seed;
            iVar12 = DAT_GameSynchronyState::instance.currentPlayerSlotID;
            iVar11 = DAT_GameSynchronyState::instance.skirmishGameIntensityType;
            iVar10 = DAT_GameSynchronyState::instance.aiVariationArray[8];
            iVar9 = DAT_GameSynchronyState::instance.aiVariationArray[7];
            iVar8 = DAT_GameSynchronyState::instance.aiVariationArray[6];
            iVar7 = DAT_GameSynchronyState::instance.aiVariationArray[5];
            iVar6 = DAT_GameSynchronyState::instance.aiVariationArray[4];
            iVar5 = DAT_GameSynchronyState::instance.aiVariationArray[3];
            iVar18 = DAT_GameSynchronyState::instance.aiVariationArray[2];
            iVar17 = DAT_GameSynchronyState::instance.aiVariationArray[1];
            iVar25 = DAT_GameSynchronyState::instance.aiVariationArray[0];
        }
        if (DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[1] == 0) {
            _playerID = _playerID + 1;
            DAT_GameState::instance.mapAndTime.playerTeams[1] = _playerID;
        }
        if (DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[2] == 0) {
            _playerID = _playerID + 1;
            DAT_GameState::instance.mapAndTime.playerTeams[2] = _playerID;
        }
        if (DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[3] == 0) {
            _playerID = _playerID + 1;
            DAT_GameState::instance.mapAndTime.playerTeams[3] = _playerID;
        }
        if (DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[4] == 0) {
            _playerID = _playerID + 1;
            DAT_GameState::instance.mapAndTime.playerTeams[4] = _playerID;
        }
        if (DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[5] == 0) {
            _playerID = _playerID + 1;
            DAT_GameState::instance.mapAndTime.playerTeams[5] = _playerID;
        }
        if (DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[6] == 0) {
            _playerID = _playerID + 1;
            DAT_GameState::instance.mapAndTime.playerTeams[6] = _playerID;
        }
        if (DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[7] == 0) {
            _playerID = _playerID + 1;
            DAT_GameState::instance.mapAndTime.playerTeams[7] = _playerID;
        }
        if (DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[8] == 0) {
            DAT_GameState::instance.mapAndTime.playerTeams[8] = _playerID + 1;
        }
        local_d80 = (int*)DAT_GameSynchronyState::instance.skirmishCurrentAdvantageBalance;
        _playerIndex = DAT_GameCore::instance.skirmishTrailProgress;
        _aiType2 = (char (*)[250])DAT_GameCore::instance.currentTrailType;
        if (DAT_GameCore::instance.currentTrailType == Game::TT_WARCHEST) {
            _playerIndex = DAT_GameCore::instance.warchestTrailProgress;
        } else if (DAT_GameCore::instance.currentTrailType == Game::TT_EXTREME) {
            _playerIndex = DAT_GameCore::instance.extremeTrailProgress;
        }
        _playerTeams[0] = DAT_GameState::instance.mapAndTime.playerTeams[0];
        _storedArray1[0] = DAT_GameState::instance.mapAndTime.playerGroupArray[0];
        _storedCurrentAIArray[0] = DAT_GameSynchronyState::instance.currentAIArray[0];
        _storedLordTypes[0] = DAT_GameCore::instance.selectedLordTypes[0];
        _playerTeams[1] = DAT_GameState::instance.mapAndTime.playerTeams[1];
        _storedArray1[1] = DAT_GameState::instance.mapAndTime.playerGroupArray[1];
        _storedCurrentAIArray[1] = DAT_GameSynchronyState::instance.currentAIArray[1];
        _storedLordTypes[1] = DAT_GameCore::instance.selectedLordTypes[1];
        _playerTeams[2] = DAT_GameState::instance.mapAndTime.playerTeams[2];
        _storedArray1[2] = DAT_GameState::instance.mapAndTime.playerGroupArray[2];
        _storedCurrentAIArray[2] = DAT_GameSynchronyState::instance.currentAIArray[2];
        _storedLordTypes[2] = DAT_GameCore::instance.selectedLordTypes[2];
        _playerTeams[3] = DAT_GameState::instance.mapAndTime.playerTeams[3];
        _storedArray1[3] = DAT_GameState::instance.mapAndTime.playerGroupArray[3];
        _storedCurrentAIArray[3] = DAT_GameSynchronyState::instance.currentAIArray[3];
        _storedLordTypes[3] = DAT_GameCore::instance.selectedLordTypes[3];
        _playerTeams[4] = DAT_GameState::instance.mapAndTime.playerTeams[4];
        _storedArray1[4] = DAT_GameState::instance.mapAndTime.playerGroupArray[4];
        _storedCurrentAIArray[4] = DAT_GameSynchronyState::instance.currentAIArray[4];
        _storedLordTypes[4] = DAT_GameCore::instance.selectedLordTypes[4];
        _playerTeams[5] = DAT_GameState::instance.mapAndTime.playerTeams[5];
        _storedArray1[5] = DAT_GameState::instance.mapAndTime.playerGroupArray[5];
        _storedCurrentAIArray[5] = DAT_GameSynchronyState::instance.currentAIArray[5];
        _storedLordTypes[5] = DAT_GameCore::instance.selectedLordTypes[5];
        _playerTeams[6] = DAT_GameState::instance.mapAndTime.playerTeams[6];
        _storedArray1[6] = DAT_GameState::instance.mapAndTime.playerGroupArray[6];
        _storedCurrentAIArray[6] = DAT_GameSynchronyState::instance.currentAIArray[6];
        _storedLordTypes[6] = DAT_GameCore::instance.selectedLordTypes[6];
        _playerTeams[7] = DAT_GameState::instance.mapAndTime.playerTeams[7];
        _storedArray1[7] = DAT_GameState::instance.mapAndTime.playerGroupArray[7];
        _storedCurrentAIArray[7] = DAT_GameSynchronyState::instance.currentAIArray[7];
        _storedLordTypes[7] = DAT_GameCore::instance.selectedLordTypes[7];
        _storedArray1[8] = DAT_GameState::instance.mapAndTime.playerGroupArray[8];
        _storedLordTypes[8] = DAT_GameCore::instance.selectedLordTypes[8];
        _playerTeams[8] = DAT_GameState::instance.mapAndTime.playerTeams[8];
        _pFinalResults = &DAT_GameSynchronyState::instance.finalResults;
        puVar22 = local_b78;
        for (_indexFinalResults = 478; _indexFinalResults != 0; _indexFinalResults = _indexFinalResults + -1) {
            *puVar22 = *(undefined4*)_pFinalResults->names[0];
            _pFinalResults = (GameSynchronyState*)(_pFinalResults->names[0] + 4);
            puVar22 = puVar22 + 1;
        }
        _storedCurrentAIArray[8] = DAT_GameSynchronyState::instance.currentAIArray[8];
        MACRO_CALL_MEMBER(IO::FilePackager_Func::readMapOrSavFile, FilePackagerObj::ptr)(
            DAT_MapDefinedData::instance.MapSectionAddressArray);
        MACRO_CALL_MEMBER(
            Audio::MSS::SoundSystem_Func::mapLoadingAndLaunchGameRelated1, DAT_SoundSystemState::ptr)();
        puVar22 = local_b78;
        pSVar26 = &DAT_GameSynchronyState::instance.finalResults;
        for (_playerID = 0x1de; _playerID != 0; _playerID = _playerID + -1) {
            *(undefined4*)pSVar26->names[0] = *puVar22;
            puVar22 = puVar22 + 1;
            pSVar26 = (SkirmishStatistics*)(pSVar26->names[0] + 4);
        }
        pdVar23 = _mapMagicU4Int2;
        _ptrSection1124 = SEC_SkirmishLobbySetupStructure::ptr;
        for (_playerID = 0x42; _playerID != 0; _playerID = _playerID + -1) {
            _ptrSection1124->mapu4int2 = *pdVar23;
            pdVar23 = pdVar23 + 1;
            _ptrSection1124 = (SkirmishLobbySetupStructure*)&_ptrSection1124->mbr_0x4;
        }
        DAT_GameSynchronyState::instance.skirmishCurrentAdvantageBalance = (int)local_d80;
        DAT_GameCore::instance.mapTimeInTicks = 1;
        DAT_GameCore::instance.section1127 = 1;
        DAT_GameCore::instance.currentTrailType = (TrailTypeInt)_aiType2;
        DAT_GameCore::instance.isVictoryOrDefeatUnk = 0;
        if (_aiType2 == (char (*)[250])0x2) {
            DAT_GameCore::instance.extremeTrailProgress = _playerIndex;
        } else if (_aiType2 == (char (*)[250])0x1) {
            DAT_GameCore::instance.warchestTrailProgress = _playerIndex;
        } else {
            DAT_GameCore::instance.skirmishTrailProgress = _playerIndex;
        }
        if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[0] == -1) && (_storedCurrentAIArray[0] != 0)) {
            DAT_GameSynchronyState::instance.aiVariationArray[0] = iVar25;
        }
        if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[1] == -1) && (_storedCurrentAIArray[1] != 0)) {
            DAT_GameSynchronyState::instance.aiVariationArray[1] = iVar17;
        }
        if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[2] == -1) && (_storedCurrentAIArray[2] != 0)) {
            DAT_GameSynchronyState::instance.aiVariationArray[2] = iVar18;
        }
        if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[3] == -1) && (_storedCurrentAIArray[3] != 0)) {
            DAT_GameSynchronyState::instance.aiVariationArray[3] = iVar5;
        }
        if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[4] == -1) && (_storedCurrentAIArray[4] != 0)) {
            DAT_GameSynchronyState::instance.aiVariationArray[4] = iVar6;
        }
        if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[5] == -1) && (_storedCurrentAIArray[5] != 0)) {
            DAT_GameSynchronyState::instance.aiVariationArray[5] = iVar7;
        }
        if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[6] == -1) && (_storedCurrentAIArray[6] != 0)) {
            DAT_GameSynchronyState::instance.aiVariationArray[6] = iVar8;
        }
        if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[7] == -1) && (_storedCurrentAIArray[7] != 0)) {
            DAT_GameSynchronyState::instance.aiVariationArray[7] = iVar9;
        }
        if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[8] == -1) && (_storedCurrentAIArray[8] != 0)) {
            DAT_GameSynchronyState::instance.aiVariationArray[8] = iVar10;
        }
        DAT_GameSynchronyState::instance.skirmishGameIntensityType = iVar11;
        DAT_GameCore::instance.isSkirmishTrail = BVar13;
        MACRO_CALL_MEMBER(AI::AIVState_Func::wipeAIVsAndHeatMaps, DAT_AIVState::ptr)();
        DAT_GameCore::instance.isTimeHalted = FALSE;
        DAT_GameCore::instance.section1095 = 0;
        DAT_GameSynchronyState::instance.skirmishAutoSaveEveryMinutes = _autoSaveMinutes;
        DAT_GameSynchronyState::instance.currentPlayerSlotID = iVar12;
        SEC_RNG::instance.seed = _seed;
        MACRO_CALL_MEMBER(Random::RNG_Func::populateRNG1040, SEC_RNG::ptr)();
        DAT_GameSynchronyState::instance.skirmishPoints = _section1093;
        DAT_GameState::instance.mapAndTime.skirmishFogOfWar = _s1023;
        DAT_GameState::instance.mapAndTime.playerTeams[0] = _playerTeams[0];
        DAT_GameState::instance.mapAndTime.playerGroupArray[0] = _storedArray1[0];
        DAT_GameSynchronyState::instance.currentAIArray[0] = _storedCurrentAIArray[0];
        DAT_GameCore::instance.selectedLordTypes[0] = _storedLordTypes[0];
        DAT_GameState::instance.mapAndTime.playerTeams[1] = _playerTeams[1];
        DAT_GameState::instance.mapAndTime.playerGroupArray[1] = _storedArray1[1];
        DAT_GameSynchronyState::instance.currentAIArray[1] = _storedCurrentAIArray[1];
        DAT_GameCore::instance.selectedLordTypes[1] = _storedLordTypes[1];
        DAT_GameState::instance.mapAndTime.playerTeams[2] = _playerTeams[2];
        DAT_GameState::instance.mapAndTime.playerGroupArray[2] = _storedArray1[2];
        DAT_GameSynchronyState::instance.currentAIArray[2] = _storedCurrentAIArray[2];
        DAT_GameCore::instance.selectedLordTypes[2] = _storedLordTypes[2];
        DAT_GameState::instance.mapAndTime.playerTeams[3] = _playerTeams[3];
        DAT_GameState::instance.mapAndTime.playerGroupArray[3] = _storedArray1[3];
        DAT_GameSynchronyState::instance.currentAIArray[3] = _storedCurrentAIArray[3];
        DAT_GameCore::instance.selectedLordTypes[3] = _storedLordTypes[3];
        DAT_GameState::instance.mapAndTime.playerTeams[4] = _playerTeams[4];
        DAT_GameState::instance.mapAndTime.playerGroupArray[4] = _storedArray1[4];
        DAT_GameSynchronyState::instance.currentAIArray[4] = _storedCurrentAIArray[4];
        DAT_GameCore::instance.selectedLordTypes[4] = _storedLordTypes[4];
        DAT_GameState::instance.mapAndTime.playerTeams[5] = _playerTeams[5];
        DAT_GameState::instance.mapAndTime.playerGroupArray[5] = _storedArray1[5];
        DAT_GameSynchronyState::instance.currentAIArray[5] = _storedCurrentAIArray[5];
        DAT_GameCore::instance.selectedLordTypes[5] = _storedLordTypes[5];
        DAT_GameCore::instance.gameMode_2 = Game::GM_SKIRMISH_AND_MULTIPLAYER;
        DAT_GameCore::instance.xbowProducible_logic = 1;
        DAT_GameCore::instance.bowProducible_logic = 1;
        DAT_GameCore::instance.spearProducible_logic = 1;
        DAT_GameCore::instance.maceProducible_logic = 1;
        DAT_GameState::instance.mapAndTime.unitJesterRelated = 1;
        DAT_GameState::instance.mapAndTime.unitLadyRelated = 0;
        DAT_GameState::instance.mapAndTime.difficulty = 1;
        DAT_GameSynchronyState::instance.skirmishTroopsCostGold = 1;
        DAT_GameState::instance.mapAndTime.playerTeams[6] = _playerTeams[6];
        DAT_GameState::instance.mapAndTime.playerGroupArray[6] = _storedArray1[6];
        DAT_GameSynchronyState::instance.currentAIArray[6] = _storedCurrentAIArray[6];
        DAT_GameCore::instance.selectedLordTypes[6] = _storedLordTypes[6];
        DAT_GameState::instance.mapAndTime.playerTeams[7] = _playerTeams[7];
        DAT_GameSynchronyState::instance.currentAIArray[7] = _storedCurrentAIArray[7];
        DAT_GameState::instance.mapAndTime.playerGroupArray[7] = _storedArray1[7];
        DAT_GameCore::instance.selectedLordTypes[7] = _storedLordTypes[7];
        DAT_GameState::instance.mapAndTime.playerGroupArray[8] = _storedArray1[8];
        DAT_GameState::instance.mapAndTime.playerTeams[8] = _playerTeams[8];
        DAT_GameSynchronyState::instance.currentAIArray[8] = _storedCurrentAIArray[8];
        DAT_GameCore::instance.missionNumber1to20 = DAT_GameSynchronyState::instance.skirmishTechLevel + 0x16;
        DAT_GameCore::instance.selectedLordTypes[8] = _storedLordTypes[8];
        DAT_GameCore::instance.swordProducible_logic = (int)(DAT_GameSynchronyState::instance.skirmishTechLevel != 2);
        DAT_GameCore::instance.pikeProducible_logic = (int)(DAT_GameSynchronyState::instance.skirmishTechLevel != 2);
        _aiType2 = (char (*)[250])0x0;
        _playerIndex = 0;
        local_d80 = DAT_GameSynchronyState::instance.currentAIArray + 1;
        piVar14 = &DAT_GameState::instance.playerDataArray[1];
        piVar27 = _playerTeams + 3;
        do {
            _keepID = (piVar14->keep).id;
            piVar27[-1] = -1;
            *piVar27 = -1;
            if (_keepID) {
                _aiType2 = (char (*)[250])((int)_aiType2 + 1);
                uVar3 = DAT_BuildingsState::instance.buildings[_keepID].y;
                piVar27[-1] = (int)(short)DAT_BuildingsState::instance.buildings[_keepID].x;
                *piVar27 = (int)(short)uVar3;
                DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding = 1;
                MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::destroyBuildingAndLinkedDuplicates,
                    DAT_BuildingsState::ptr)(_keepID);
                DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding = 1;
                MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::destroyBuildingAndLinkedDuplicates,
                    DAT_BuildingsState::ptr)((piVar14->stockpile).id);
                uVar19 = piVar14->lordID;
                if (uVar19) {
                    if (piVar14->lordUID == DAT_UnitsState::instance.units[uVar19].uid) {
                        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::deleteUnit, DAT_UnitsState::ptr)(
                            uVar19);
                    }
                    piVar14->lordID = 0;
                    piVar14->lordUID = 0;
                }
                piVar14->lordKilledByPlayerID = 0;
            }
            if ((local_d80[-0x1b] != -1) || (*local_d80 != 0)) {
                _playerIndex = _playerIndex + 1;
            }
            piVar14 = piVar14 + 0xe7d;
            local_d80 = local_d80 + 1;
            piVar27 = piVar27 + 2;
        } while ((int)piVar14 < 0x117e984);
        if ((int)_playerIndex < (int)_aiType2) {
            _playerID = 1;
            piVar27 = _playerTeams;
            do {
                piVar27 = piVar27 + 2;
                if ((DAT_GameSynchronyState::instance.playerPositionsArray[_playerID - 1] < 0) && (*piVar27 != -1)) {
                    MACRO_CALL_MEMBER(Game::GameStateStructures_Func::destroyPlayerCompletely,
                        DAT_GameState::ptr)(_playerID);
                }
                _playerID = _playerID + 1;
            } while (_playerID < 9);
        }
        _playerID = 1;
        pAVar27 = &DAT_GameState::instance.playerDataArray[1];
        do {
            iVar25 = DAT_GameSynchronyState::instance.currentPlayerFullIDArray[_playerID];
            _storedLordTypes[_playerID] = 0;
            pAVar27->aiType = AI::AIT_NULL;
            if ((iVar25 != -1) || (DAT_GameSynchronyState::instance.currentAIArray[_playerID] != 0)) {
                iVar25 = MACRO_CALL(Synchrony_Func::GetPlayerPosition)(_playerID);
                _storedLordTypes[_playerID] = iVar25;
                if (_playerID == iVar25) {
                    MACRO_CALL_MEMBER(Game::GameStateStructures_Func::swapOwnership, DAT_GameState::ptr)(
                        _playerID, _playerID);
                    _storedLordTypes[_playerID] = 0;
                }
            }
            pAVar27 = pAVar27 + 0xe7d;
            _playerID = _playerID + 1;
        } while ((int)pAVar27 < 0x117ea8c);
        local_d80 = (int*)0x8;
        do {
            _playerID = 1;
            do {
                if (((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[_playerID] != -1)
                        || (DAT_GameSynchronyState::instance.currentAIArray[_playerID] != 0))
                    && (iVar25 = _storedLordTypes[_playerID], iVar25)) {
                    MACRO_CALL_MEMBER(Game::GameStateStructures_Func::swapOwnership, DAT_GameState::ptr)(
                        iVar25, _playerID);
                    iVar17 = 1;
                    do {
                        if (_storedLordTypes[iVar17] == _playerID) {
                            _storedLordTypes[iVar17] = iVar25;
                            break;
                        }
                        iVar17 = iVar17 + 1;
                    } while (iVar17 < 9);
                    _storedLordTypes[_playerID] = 0;
                }
                _playerID = _playerID + 1;
            } while (_playerID < 9);
            local_d80 = (int*)((int)local_d80 + -1);
        } while (local_d80 != (int*)0x0);
        MACRO_CALL_MEMBER(AI::AIVState_Func::setAIVFilePresenceByFileHashArray, DAT_AIVState::ptr)();
        _section1093 = _whichCastle + -0x191de14;
        _playerID = 1;
        _ptrAIVID = &DAT_GameState::instance.playerDataArray[1].aivID;
        do {
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[_playerID] == -1) {
                if (DAT_GameSynchronyState::instance.currentAIArray[_playerID] != 0) {
                    _playerPosition = MACRO_CALL(Synchrony_Func::GetPlayerPosition)(_playerID);
                    _ptrAIVID[-0x18] = DAT_GameSynchronyState::instance.skirmishPoints;
                    DAT_TileMapState::instance.clearKeepFootprintOnPlace = 1;
                    DAT_TileMapState::instance.skipPlacementCheck = 1;
                    DAT_TileMapState::instance.buildingPlacementFail = FALSE;
                    /*
                      set aiType to 1 + ai
                     */
                    _ptrAIVID[1] = DAT_GameSynchronyState::instance.currentAIArray[_playerID] + 1;
                    iVar25
                        = MACRO_CALL_MEMBER(AI::AIVState_Func::setupAIVMetadata, DAT_AIVState::ptr)(_playerID);
                    _s1023 = _playerTeams[_playerPosition * 2 + 1];
                    _autoSaveMinutes = _playerTeams[_playerPosition * 2];
                    *_ptrAIVID = iVar25;
                    MACRO_CALL_MEMBER(AI::AIVState_Func::setKeepOffsetAndOrientation, DAT_AIVState::ptr)(
                        iVar25, _autoSaveMinutes, _s1023);
                    if (!_whichCastle) {
                        MACRO_CALL_MEMBER(AI::AIVState_Func::selectBestAIVwithRandomStart, DAT_AIVState::ptr)(
                            *_ptrAIVID);
                    } else {
                        /*
                          local_d74 = param_1 - 4 or something
                         */
                        _fitPercentage
                            = MACRO_CALL_MEMBER(AI::AIVState_Func::tryPlaceAIVAndReturnFitPercentage,
                                DAT_AIVState::ptr)(*_ptrAIVID, *(int*)(_section1093 + 0x191de10 + _playerID * 4));
                        DAT_AIVPlacementFit::instance[_playerID] = _fitPercentage;
                    }
                    _anotherPlayerIDUnk = *_ptrAIVID;
                    if (DAT_AIVState::instance.aivs[_anotherPlayerIDUnk].aivSubType == 0) {
                        /*
                          aiv placement failed, choose default castle
                         */
                        MACRO_CALL_MEMBER(Map::TileMapState_Func::placeBuilding, DAT_TileMapState::ptr)(
                            _playerID, _autoSaveMinutes, _s1023, Commands::M_MAPPER_KEEP2, 7, 0xf);
                    } else {
                        /*
                          successfull aiv placement trying
                         */
                        MACRO_CALL_MEMBER(AI::AIVState_Func::applyAIV, DAT_AIVState::ptr)(
                            _anotherPlayerIDUnk, _playerID);
                        MACRO_CALL_MEMBER(Map::TileMapState_Func::placeBuilding, DAT_TileMapState::ptr)(
                            _playerID, DAT_AIVState::instance.keepX, DAT_AIVState::instance.keepY,
                            Commands::M_MAPPER_KEEP2, 7,
                            DAT_AIVState::instance.aivs[_anotherPlayerIDUnk].keepOrientation);
                        _keepBuildingID = _ptrAIVID[-0x89a];
                        if (_keepBuildingID) {
                            iVar17 = (int)(short)DAT_BuildingsState::instance.buildings[_keepBuildingID].y;
                            iVar25 = (int)(short)DAT_BuildingsState::instance.buildings[_keepBuildingID].x;
                            iVar18 = DAT_TileMapState::instance.DefaultHeightLayer
                                         [DAT_ViewportRenderState::instance.translationMatrix[iVar17].addXgetTile
                                             + iVar25 + 6]
                                + 0x5a;
                            iVar17 = iVar17 * 8;
                            iVar25 = iVar25 * 8 + 0x37;
                            MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::spawnProjectileEntity,
                                DAT_EntityState::ptr)(0, (undefined4)((int)(_playerID)), (uint)((int)(_playerID)),
                                iVar25, iVar17, iVar18, iVar25, iVar17, iVar18, Map::Entities::ET_FLAG_4, 0);
                        }
                    }
                }
            } else {
                iVar18 = MACRO_CALL(Synchrony_Func::GetPlayerPosition)(_playerID);
                iVar25 = DAT_GameSynchronyState::instance.skirmishPoints;
                iVar17 = _playerTeams[iVar18 * 2 + 1];
                _s1023 = _playerTeams[iVar18 * 2];
                _ptrAIVID[0x5b6] = 0;
                DAT_TileMapState::instance.buildingPlacementFail = FALSE;
                DAT_TileMapState::instance.clearKeepFootprintOnPlace = 1;
                DAT_TileMapState::instance.skipPlacementCheck = 1;
                _ptrAIVID[-0x18] = iVar25;
                MACRO_CALL_MEMBER(Map::TileMapState_Func::placeBuilding, DAT_TileMapState::ptr)(
                    _playerID, _s1023, iVar17, Commands::M_MAPPER_KEEP2, 7, 0xf);
                iVar18 = DAT_TileMapState::instance
                             .DefaultHeightLayer[DAT_ViewportRenderState::instance.translationMatrix[iVar17].addXgetTile
                                 + _s1023]
                    + 0x5a;
                iVar25 = _s1023 * 8 + 0x37;
                MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::spawnProjectileEntity,
                    DAT_EntityState::ptr)(0, (undefined4)((int)(_playerID)), (uint)((int)(_playerID)), iVar25,
                    iVar17 * 8, iVar18, iVar25, iVar17 * 8, iVar18, Map::Entities::ET_FLAG_4, 0);
                if (_playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                    MACRO_CALL_MEMBER(
                        Rendering::ViewportRenderState_Func::focusOnCoordinate, DAT_ViewportRenderState::ptr)(
                        (short)DAT_BuildingsState::instance.buildings[_ptrAIVID[-0x89a]].x + 2,
                        (int)((int)((short)DAT_BuildingsState::instance.buildings[_ptrAIVID[-0x89a]].y + 2)));
                }
            }
            _playerID = _playerID + 1;
            _ptrAIVID = _ptrAIVID + 0xe7d;
        } while (_playerID < 9);
        if (DAT_GameCore::instance.mapU4Int0) {
            _playerID = 1;
            do {
                /*
                  produce the startup keep destroyal visual effects?
                 */
                if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[_playerID] == -1)
                    && (DAT_GameSynchronyState::instance.currentAIArray[_playerID] == 0)) {
                    DAT_TileMapState::instance.buildingPlacementFail = FALSE;
                    DAT_GameState::instance.mapAndTime.somePlayerID = _playerID;
                    MACRO_CALL_MEMBER(Map::TileMapState_Func::placeBuilding, DAT_TileMapState::ptr)(
                        _playerID, local_ca0, local_c9c, Commands::M_MAPPER_KEEP2, 7, 0xf);
                    iVar25 = DAT_ViewportRenderState::instance.translationMatrix[local_c9c].addXgetTile + local_ca0;
                    sVar4 = DAT_TileMapState::instance.BuildingLayer[iVar25];
                    iVar17 = DAT_TileMapState::instance.DefaultHeightLayer[iVar25] + 0x7c;
                    iVar25 = local_ca0 * 8 + 0x37;
                    DAT_GameState::instance.playerDataArray[_playerID].keep.id = 0;
                    uVar19 = MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::spawnProjectileEntity,
                        DAT_EntityState::ptr)(0, (undefined4)((int)(_playerID)), 5, iVar25, local_c9c * 8, iVar17,
                        iVar25, local_c9c * 8, iVar17, Map::Entities::ET_FLAG_4, 0);
                    *(short*)&DAT_BuildingsState::instance.buildings[sVar4].field_0x2c2 = (short)uVar19;
                    break;
                }
                _playerID = _playerID + 1;
            } while (_playerID < 9);
        }
        /*
          copy start gold, note that this value is written after the goods, event   thoguh in the decompiler it shows up
          as if written before (and then   overwritten by the goods...)
         */
        DAT_GameState::instance.mapAndTime.startGoods[0xf]
            = (int)(PTR_005c2a68::ptr)[DAT_GameSynchronyState::instance.skirmishGameIntensityType];
        /*
          copy start goods
         */
        pSVar24 = DAT_RenderingDefinedData::instance.StartGoods
            + DAT_GameSynchronyState::instance.skirmishGameIntensityType + -1;
        piVar26 = &pSVar24->invalid1;
        piVar27 = DAT_GameState::instance.mapAndTime.startGoods;
        for (_counter = 0x19; _counter != 0; _counter = _counter + -1) {
            *piVar27 = *piVar26;
            piVar26 = piVar26 + 1;
            piVar27 = piVar27 + 1;
        }
        DAT_GameState::instance.mapAndTime.euroRecruitable[0] = 1;
        DAT_GameState::instance.mapAndTime.mercRecruitable[0] = 1;
        DAT_GameState::instance.mapAndTime.euroRecruitable[1] = 1;
        DAT_GameState::instance.mapAndTime.mercRecruitable[1] = 1;
        DAT_GameState::instance.mapAndTime.euroRecruitable[2] = 1;
        DAT_GameState::instance.mapAndTime.mercRecruitable[2] = 1;
        DAT_GameState::instance.mapAndTime.euroRecruitable[3] = 1;
        DAT_GameState::instance.mapAndTime.mercRecruitable[3] = 1;
        DAT_GameState::instance.mapAndTime.euroRecruitable[4] = 1;
        DAT_GameState::instance.mapAndTime.mercRecruitable[4] = 1;
        DAT_GameState::instance.mapAndTime.euroRecruitable[5] = 1;
        DAT_GameState::instance.mapAndTime.mercRecruitable[5] = 1;
        DAT_GameState::instance.mapAndTime.euroRecruitable[6] = 1;
        DAT_GameState::instance.mapAndTime.mercRecruitable[6] = 1;
        _playerIndex = 1;
        _startingTroopsPlayerData = DAT_GameState::instance.mapAndTime.startingTroops;
        _aiType2 = (char (*)[250]) & DAT_GameState::instance.playerDataArray[1].aiType;
        _playerID = _whichCastle;
        do {
            _whichCastle = _playerID;
            _advantage = 100;
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[_playerIndex] == -1) {
                if (DAT_GameSynchronyState::instance.currentAIArray[_playerIndex] == 0) {
                    _aiNumber = 0;
                } else {
                    _advantage = *(int*)((int)(DAT_RenderingDefinedData::instance.StartingTroops + -1)
                        + (DAT_GameSynchronyState::instance.skirmishCurrentAdvantageBalance + 0x35) * 4);
                    _aiNumber = *(AITypeInt*)_aiType2 + ~AI::AIT_NULL;
                }
            } else {
                _lordType = MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::getLordTypeForPlayer,
                    DAT_GameSynchronyState::ptr)(_playerIndex);
                _advantage = *(int*)((int)(DAT_RenderingDefinedData::instance.StartingTroops + -1)
                    + (DAT_GameSynchronyState::instance.skirmishCurrentAdvantageBalance + 0x2f) * 4);
                _aiNumber = 19 - (uint)(_lordType != 1);
            }
            /*
              This points to the starting troops array.
             */
            piVar27 = (int*)((int)DAT_RenderingDefinedData::instance.StartGoods
                + (DAT_GameSynchronyState::instance.skirmishGameIntensityType + _aiNumber * 3) * 0x50 + 0x110);
            _whichCastle = 20;
            do {
                (*_startingTroopsPlayerData)[0] = (*piVar27 * _advantage) / 100;
                piVar27 = piVar27 + 1;
                _startingTroopsPlayerData = (int (*)[20])(*_startingTroopsPlayerData + 1);
                _whichCastle = _whichCastle + -1;
            } while (_whichCastle);
            _aiType2 = (char (*)[250])((int)_aiType2 + 0x39f4);
            _playerIndex = _playerIndex + 1;
            _playerID = 0;
        } while ((int)_playerIndex < 9);
        DAT_GameState::instance.mapAndTime.startingPopularity
            = DAT_GameSynchronyState::instance.skirmishDefaultPopularity * 10;
        MACRO_CALL_MEMBER(Map::TileMapState_Func::prepareMap, DAT_TileMapState::ptr)();
        MACRO_CALL_MEMBER(Map::WildlifeState_Func::clearWildlifeState, DAT_WildlifeState::ptr)();
        DAT_GameSynchronyState::instance.currentGameMode = _gameMode;
        DAT_GameState::instance.mapAndTime.rawDeerCount
            = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getRawDeerCount, DAT_UnitsState::ptr)();
        /*
          This applies the start goods!
         */
        MACRO_CALL_MEMBER(Game::GameStateStructures_Func::clearEnemyRelatedStructures, DAT_GameState::ptr)();
        DAT_GameState::instance.mapAndTime.militaryCampaignStage = 0;
        DAT_GameState::instance.mapAndTime.field3183_0x27dc = 0;
        DAT_GameState::instance.mapAndTime.militaryCampaignFlags = 0;
        DAT_GameState::instance.mapAndTime.yearCopy = 0;
        DAT_GameState::instance.mapAndTime.monthCopy = 0;
        DAT_GameState::instance.mapAndTime.field3184_0x27de = 0;
        MACRO_CALL_MEMBER(Game::GameStateStructures_Func::setMonthAndYear, DAT_GameState::ptr)(
            6, (int)((int)(1181)));
        DAT_GameState::instance.mapAndTime.traderRelated1 = 4;
        DAT_GameState::instance.mapAndTime.traderRelatedCounter2 = 4;
        DAT_GameState::instance.mapAndTime.field1363_0x71c = 1;
        DAT_GameState::instance.mapAndTime.field1364_0x720 = 0;
        DAT_GameState::instance.mapAndTime.traderRelated2 = 0;
        DAT_GameState::instance.mapAndTime.traderRelatedCounter1 = 0;
        _pKeepPlayer2 = &DAT_GameState::instance.playerDataArray[2];
        _index = 0;
        do {
            if (((*(int*)((int)DAT_GameSynchronyState::instance.currentPlayerFullIDArray + _index + 4) != -1)
                    || (*(int*)((int)DAT_GameSynchronyState::instance.currentAIArray + _index + 4) != 0))
                && (*(int*)((int)(_pKeepPlayer2 + -0x173) + 4) != 0)) {
                *(uint*)((int)DAT_GameState::instance.mapAndTime.playerKeepTile + _index + 4)
                    = DAT_BuildingsState::instance.buildings[*(int*)((int)(_pKeepPlayer2 + -0x173) + 4)]
                          .currentTilePositionAdjusted;
            }
            if (((*(int*)((int)DAT_GameSynchronyState::instance.currentPlayerFullIDArray + _index + 8) != -1)
                    || (*(int*)((int)DAT_GameSynchronyState::instance.currentAIArray + _index + 8) != 0))
                && (_pKeepPlayer2->id)) {
                *(uint*)((int)DAT_GameState::instance.mapAndTime.playerKeepTile + _index + 8)
                    = DAT_BuildingsState::instance.buildings[_pKeepPlayer2->id].currentTilePositionAdjusted;
            }
            if (((*(int*)((int)DAT_GameSynchronyState::instance.currentPlayerFullIDArray + _index + 0xc) != -1)
                    || (*(int*)((int)DAT_GameSynchronyState::instance.currentAIArray + _index + 0xc) != 0))
                && (*(int*)((int)(_pKeepPlayer2 + 0x172) + 0x24) != 0)) {
                *(uint*)((int)DAT_GameState::instance.mapAndTime.playerKeepTile + _index + 0xc)
                    = DAT_BuildingsState::instance.buildings[*(int*)((int)(_pKeepPlayer2 + 0x172) + 0x24)]
                          .currentTilePositionAdjusted;
            }
            if (((*(int*)((int)DAT_GameSynchronyState::instance.currentPlayerFullIDArray + _index + 0x10) != -1)
                    || (*(int*)((int)DAT_GameSynchronyState::instance.currentAIArray + _index + 0x10) != 0))
                && (*(int*)((int)(_pKeepPlayer2 + 0x2e5) + 0x20) != 0)) {
                *(uint*)((int)DAT_GameState::instance.mapAndTime.playerKeepTile + _index + 0x10)
                    = DAT_BuildingsState::instance.buildings[*(int*)((int)(_pKeepPlayer2 + 0x2e5) + 0x20)]
                          .currentTilePositionAdjusted;
            }
            _pKeepPlayer2 = (PlayerData*)((int)(_pKeepPlayer2 + 0x5cb) + 0x18);
            _index = _index + 16;
        } while ((int)_pKeepPlayer2 < 0x1180214);
        pBVar20 = DAT_GameState::instance.mapAndTime.copyOfBuyAndSalesPrice;
        _resourceIndex = 0;
        do {
            /*
              this code resets the buy and sell prices to the default
             */
            _playerID = *(int*)((int)DAT_RenderingDefinedData::instance.BuyPricePerResource + _resourceIndex);
            pBVar20[0x19].buyPrice = _playerID;
            pBVar20->buyPrice = _playerID;
            _playerID = *(int*)((int)DAT_RenderingDefinedData::instance.SalesPricePerResource + _resourceIndex);
            pBVar20[0x19].salesPrice = _playerID;
            pBVar20->salesPrice = _playerID;
            /*
              this code sets every trade good as tradeable
             */
            *(undefined4*)((int)DAT_GameState::instance.mapAndTime.isResourceTradeable + _resourceIndex) = 1;
            *(undefined4*)((int)DAT_GameState::instance.mapAndTime.unknownResouceFlagArray1 + _resourceIndex) = 0;
            *(undefined4*)((int)DAT_GameState::instance.mapAndTime.unknownResourceFlagArray2 + _resourceIndex) = 0;
            pBVar20 = pBVar20 + 1;
            _resourceIndex = _resourceIndex + 4;
        } while ((int)pBVar20 < 0x117cfd4);
        if (DAT_GameSynchronyState::instance.skirmishTechLevel < 3) {
            DAT_GameState::instance.mapAndTime.isResourceTradeable[0x10] = 0;
        }
        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_0 = 1;
        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_2 = 1;
        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_4 = 1;
        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_1_b = 1;
        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_3_b = 1;
        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_6_a = 1;
        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_1_a = 1;
        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_3_a_and_6_b = 1;
        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_6_c = 1;
        MACRO_CALL(Synchrony_Func::SetAIPlayerNickNames)();
        if ((DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SKIRMISH_SINGLE_PLAYER)
            && (!DAT_GameSynchronyState::instance.currentPlayerSlotID)) {
            DAT_GameState::instance.playerDataArray[0].playerDeathRelated = 1;
        }
        _finalResultsIndex = 1;
        _aiType2 = DAT_GameSynchronyState::instance.DAT_PlayerNames + 1;
        _ptrFinalResults = 0x1a26d86;
        do {
            if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[_finalResultsIndex] == -1)
                && (DAT_GameSynchronyState::instance.currentAIArray[_finalResultsIndex] == 0)) {
                DAT_GameSynchronyState::instance.finalResults.active[_finalResultsIndex] = 0;
            } else {
                DAT_GameSynchronyState::instance.finalResults.active[_finalResultsIndex] = 1;
                pacVar21 = _aiType2;
                do {
                    cVar1 = (*pacVar21)[0];
                    *(char*)((int)pacVar21 + (_ptrFinalResults - (int)_aiType2)) = cVar1;
                    pacVar21 = (char (*)[250])(*pacVar21 + 1);
                } while (cVar1 != '\0');
                DAT_GameSynchronyState::instance.finalResults.finalGold[_finalResultsIndex] = 0;
                DAT_GameSynchronyState::instance.finalResults.finalMaxPopulation[_finalResultsIndex] = 0;
                DAT_GameSynchronyState::instance.finalResults.finalMaxGoodThings[_finalResultsIndex] = 0;
                DAT_GameSynchronyState::instance.finalResults.finalMaxBadThings[_finalResultsIndex] = 0;
                DAT_GameSynchronyState::instance.finalResults.finalBuildingsBurned[_finalResultsIndex] = 0;
                DAT_GameSynchronyState::instance.finalResults.finalBuidingsDestroyed[_finalResultsIndex] = 0;
                DAT_GameSynchronyState::instance.finalResults.finalFoodProduced[_finalResultsIndex] = 0;
                DAT_GameSynchronyState::instance.finalResults.finalWeaponsProduced[_finalResultsIndex] = 0;
                DAT_GameSynchronyState::instance.finalResults.finalIronProduced[_finalResultsIndex] = 0;
                DAT_GameSynchronyState::instance.finalResults.finalStoneProduced[_finalResultsIndex] = 0;
                DAT_GameSynchronyState::instance.finalResults.finalWoodProduced[_finalResultsIndex] = 0;
                DAT_GameSynchronyState::instance.finalResults.finalPitchProduced[_finalResultsIndex] = 0;
                DAT_GameSynchronyState::instance.finalResults.finalKilledLords[_finalResultsIndex] = 0;
                DAT_GameSynchronyState::instance.finalResults.finalTroopsKilledWeighted[_finalResultsIndex] = 0;
                DAT_GameSynchronyState::instance.finalResults.finalBuildingsDestroyedWeighted[_finalResultsIndex] = 0;
                /*
                  monthStart
                 */
                DAT_GameSynchronyState::instance.finalResults.finalDateOfDeathInMonths[_finalResultsIndex + 9] = 0;
            }
            _aiType2 = _aiType2 + 1;
            _ptrFinalResults = _ptrFinalResults + 90;
            _finalResultsIndex = _finalResultsIndex + 1;
        } while (_ptrFinalResults < 0x1a27056);
        _killMatrix = DAT_GameSynchronyState::instance.finalResults.finalKillMatrix;
        for (_playerID = 81; _playerID != 0; _playerID = _playerID + -1) {
            (*_killMatrix)[0] = 0;
            _killMatrix = (int (*)[9])(*_killMatrix + 1);
        }
        DAT_GameSynchronyState::instance.finalResults.monthStart = DAT_GameState::instance.mapAndTime.month;
        DAT_GameSynchronyState::instance.finalResults.yearStart = DAT_GameState::instance.mapAndTime.year;
        MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::clearAttackInfo, DAT_TroopValueState::ptr)();
        MACRO_CALL_MEMBER(AI::AIVState_Func::recomputeHeatmaps, DAT_AIVState::ptr)(1);
        MACRO_CALL_MEMBER(AI::AICState_Func::recomputeAttackAIZone, DAT_AICState::ptr)();
        for (_playerID = 1; _playerID < 9; _playerID++) {
            if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[_playerID] == -1)
                && (DAT_GameSynchronyState::instance.currentAIArray[_playerID] != 0)) {
                MACRO_CALL_MEMBER(AI::AIVState_Func::recomputeAIAvailableGridTiles, DAT_AIVState::ptr)(
                    _playerID);
            }
        }
        MACRO_CALL_MEMBER(
            Rendering::Bink::AIMessageQueue_Func::playNextStoredBinkVideo, DAT_VideoBikQueue::ptr)();
        DAT_GameState::instance.mapAndTime.skirmishStrongWalls = DAT_GameSynchronyState::instance.skirmishStrongWalls;
        DAT_GameState::instance.mapAndTime.skirmishAlliances = DAT_GameSynchronyState::instance.skirmishAlliances;
        DAT_GameState::instance.mapAndTime.skirmishNoDogs = DAT_GameSynchronyState::instance.skirmishNoDogs;
        DAT_GameState::instance.mapAndTime.skirmishNoCowThrowing
            = DAT_GameSynchronyState::instance.skirmishNoCowThrowing;
        DAT_GameState::instance.mapAndTime.skirmishExtremeMode = DAT_GameSynchronyState::instance.skirmishExtremeMode;
        DAT_GameState::instance.mapAndTime.skirmishNoRushTicks
            = DAT_RenderingDefinedData::instance.NoRushTicks[DAT_GameSynchronyState::instance.skirmishNoRushSetting];
        DAT_GameState::instance.mapAndTime.skirmishExtremeMode2 = DAT_GameSynchronyState::instance.skirmishExtremeMode2;
        DAT_GameState::instance.mapAndTime.countUpTo201 = 0;
        DAT_GameState::instance.mapAndTime.skirmishNoRushTicksLeft
            = DAT_GameState::instance.mapAndTime.skirmishNoRushTicks;
        MACRO_CALL_MEMBER(UI::MenuTextInputState_Func::clearModalDialog2to6, DAT_MenuTextInputState::ptr)();
        DAT_GameSynchronyState::instance.timeSkirmishGameStart = timeGetTime();
        DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType = UI::Enums::BASMTT_HUNTERSHUT;
        DAT_MissionDefinedData::instance.field26_0xaf8 = false;
        if ((DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_SELECT_CRUSADE)
            || (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_CRUSADE_MISSION_INTRO)) {
            _delay = 0;
        } else {
            _delay = 10000;
        }
        MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
            UI::Enums::MVT_BUILD_MENU, _delay);
        DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial = TRUE;
        DAT_WindowAndDirectDraw::instance.unk_resetViewportRelated = 1;
        DWORD_00b95b1c::instance = timeGetTime();
        DAT_00b960dc::instance = 1;
        MACRO_CALL_MEMBER(
            Synchrony::GameSynchronyState_Func::recomputeHashesAndSendResync, DAT_GameSynchronyState::ptr)(0);
        DAT_GameSynchronyState::instance.DAT_TwoIfNotHost = 0;
        DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue[0] = 0;
        DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue[1] = 0;
        DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue[2] = 0;
        DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue[3] = 0;
        DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue[4] = 0;
        DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue[5] = 0;
        DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue[6] = 0;
        DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue[7] = 0;
        DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue[8] = 0;
        DAT_GameCore::instance.timeSum_2 = timeGetTime();
        DAT_GameCore::instance.gameDuration = 0;
        TIME_ReceivedMessage_2::instance = 0;
        DAT_00b960f8::instance = 0;
        INT_00b960f0::instance = 0;
        ;
        return;
    }

}
}
