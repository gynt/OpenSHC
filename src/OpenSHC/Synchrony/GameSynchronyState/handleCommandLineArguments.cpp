#include "../../Synchrony.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Synchrony.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"
#include "OpenSHC/Globals/Menu_LobbyMenu.hpp"

#include "stdlib.h"
#include "string.h"

namespace OpenSHC {
namespace Synchrony {

    using Commands::GameCommandType;
    using DE::SHCDE::eTextSections;
    using UI::Enums::BuildingsAndStatusMenuTabType;
    using UI::Enums::MenuViewType;
    using WindowsHelper::Enums::BOOLEnum;

    /*
      valid arguments seem to be: +connect, +host, +name   decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00491040
    void GameSynchronyState::handleCommandLineArguments(char* arguments)
    {
        char* _pArguments;
        int _charIndex3;
        int _copyIndex;
        int _isConnect;
        int _connectArgLength;
        char* pcVar2;
        int _charIndex;
        int _candidateIndex;
        undefined1 auStack_40c[2];
        bool _quotation;
        char local_409;
        char _candidates[4][256];
        char* _pConnectTarget;
        int _argCharIndex;
        char _argChar;
        char _char;
        char* _pCandidatePlus1;
        uint uVar1 = MSVC_SecurityCookie::instance ^ (uint)auStack_40c;
        _charIndex3 = 0;
        _quotation = false;
        local_409 = '\0';
        this->useTCPIP = FALSE;
        _pArguments = arguments;
        do {
            _char = *_pArguments;
            _pArguments = _pArguments + 1;
        } while (_char != '\0');
        if ((int)_pArguments - (int)(arguments + 1) != 0) {
            _candidates[0][0] = '\0';
            _candidates[1][0] = '\0';
            _candidateIndex = 0;
            _charIndex = 0;
            do {
                _argChar = arguments[_charIndex3];
                if (_argChar == '\"') {
                    _charIndex3 = _charIndex3 + 1;
                    _quotation = _quotation == false;
                    if (!_quotation) {
                        _candidates[_candidateIndex][_charIndex] = '\0';
                        _charIndex = 0;
                        if (arguments[_charIndex3 + 1] != '+') {
                            if (arguments[_charIndex3 + 1] == '\"') {
                                if (arguments[_charIndex3 + 2] == '+')
                                    goto LAB_004910fb;
                            }
                        LAB_004910ea:
                            if (_candidateIndex != 1) {
                                _candidateIndex = _candidateIndex + 1;
                                continue;
                            }
                        }
                    LAB_004910fb:
                        _candidateIndex = 0;
                    LAB_00491101:
                        _copyIndex = 0;
                        do {
                            _char = _candidates[0][_copyIndex];
                            _candidates[2][_copyIndex] = _char;
                            _copyIndex = _copyIndex + 1;
                        } while (_char != 0);
                        _copyIndex = 0;
                        do {
                            _char = _candidates[1][_copyIndex];
                            _candidates[3][_copyIndex] = _char;
                            _copyIndex = _copyIndex + 1;
                        } while (_char != 0);
                        _isConnect = MACRO_CALL(OS_Func::__stricmp)("+connect", (char const*)((int)(_candidates[0])));
                        if (!_isConnect) {
                            _pConnectTarget = _candidates[1];
                            this->useTCPIP = TRUE;
                            _pCandidatePlus1 = _pConnectTarget + 1;
                            do {
                                _char = *_pConnectTarget;
                                _pConnectTarget = _pConnectTarget + 1;
                            } while (_char != '\0');
                            if ((uint)((int)_pConnectTarget - (int)_pCandidatePlus1) < 29) {
                                _pConnectTarget = _candidates[1];
                                _pCandidatePlus1 = _pConnectTarget + 1;
                                do {
                                    _char = *_pConnectTarget;
                                    _pConnectTarget = _pConnectTarget + 1;
                                } while (_char != '\0');
                                _connectArgLength = (int)_pConnectTarget - (int)_pCandidatePlus1;
                            } else {
                                _connectArgLength = 0x1d;
                            }
                            memset(this->connectTarget, 0, 30);
                            _charIndex3 = 0;
                            if (0 < _connectArgLength) {
                                do {
                                    _char = _candidates[1][_charIndex3];
                                    this->connectTarget[_charIndex3] = _char;
                                    if (_char == ':') {
                                        this->connectPort = atol(_candidates[1] + _charIndex3 + 1);
                                        break;
                                    }
                                    _charIndex3 = _charIndex3 + 1;
                                } while (_charIndex3 < _connectArgLength);
                            }
                            MACRO_CALL_MEMBER(
                                Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(5);
                            MACRO_CALL_MEMBER(Text::UserTextHandler_Func::copyIntoTextArray,
                                DAT_UserTextHandlerState::ptr)(_candidates[3]);
                            if (this->connectPort) {
                                MACRO_CALL_MEMBER(
                                    Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(6);
                                MACRO_CALL_MEMBER(Text::UserTextHandler_Func::copyIntoTextArray,
                                    DAT_UserTextHandlerState::ptr)(_candidates[3] + _charIndex3 + 1);
                            }
                        } else {
                            _charIndex3 = MACRO_CALL(OS_Func::__stricmp)("+host", (char const*)((int)(_candidates[0])));
                            if (!_charIndex3) {
                                this->useTCPIP = TRUE;
                                this->willHost = 1;
                                this->connectPort = atol(_candidates[1]);
                                if (this->connectPort) {
                                    MACRO_CALL_MEMBER(
                                        Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(6);
                                    MACRO_CALL_MEMBER(Text::UserTextHandler_Func::copyIntoTextArray,
                                        DAT_UserTextHandlerState::ptr)(_candidates[3]);
                                }
                            } else {
                                _charIndex3
                                    = MACRO_CALL(OS_Func::__stricmp)("+name", (char const*)((int)(_candidates[0])));
                                if (!_charIndex3) {
                                    strcpy((char*)DAT_GameSynchronyState::instance.connectName, _candidates[1]);
                                }
                            }
                        }
                        _candidates[0][0] = '\0';
                        _candidates[1][0] = '\0';
                    }
                } else {
                    if (_argChar == '\0') {
                        _candidates[_candidateIndex][_charIndex] = '\0';
                        _charIndex = 0;
                        local_409 = '\x01';
                        goto LAB_00491101;
                    }
                    if (_argChar == ' ') {
                        if (_quotation == false) {
                            _char = arguments[_charIndex3 + 1];
                            _candidates[_candidateIndex][_charIndex] = '\0';
                            _charIndex3 = _charIndex3 + 1;
                            _charIndex = 0;
                            if (_char != '+') {
                                if (_char == '\"') {
                                    if (arguments[_charIndex3 + 1] == '+')
                                        goto LAB_004910fb;
                                }
                                goto LAB_004910ea;
                            }
                            goto LAB_004910fb;
                        }
                        _candidates[_candidateIndex][_charIndex] = ' ';
                        _charIndex = _charIndex + 1;
                        _charIndex3 = _charIndex3 + 1;
                    } else {
                        _candidates[_candidateIndex][_charIndex] = _argChar;
                        _charIndex = _charIndex + 1;
                        _charIndex3 = _charIndex3 + 1;
                    }
                }
            } while (local_409 == '\0');
            if (this->useTCPIP) {
                pcVar2 = MACRO_CALL_MEMBER(
                    Text::UserTextHandler_Func::getTextArrayPointer, DAT_UserTextHandlerState::ptr)(0);
                _pCandidatePlus1 = pcVar2 + 1;
                do {
                    _char = *pcVar2;
                    pcVar2 = pcVar2 + 1;
                } while (_char != '\0');
                if (pcVar2 == _pCandidatePlus1) {
                    MACRO_CALL_MEMBER(Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(0);
                    /*
                      added by script: "Lord Crusader"
                     */
                    _pCandidatePlus1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_GAME_OPTIONS, 0x30);
                    MACRO_CALL_MEMBER(Text::UserTextHandler_Func::copyIntoTextArray, DAT_UserTextHandlerState::ptr)(
                        _pCandidatePlus1);
                    MACRO_CALL_MEMBER(Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(9);
                }
                DAT_GameSynchronyState::instance.isHost = this->willHost;
                if (!this->willHost) {
                    this->nextModalDialog = 21;
                    /*
                      switching to this menu triggers a bunch of multiplayer logic via the render   functions
                     */
                    MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        UI::Enums::MVT_MP_CONNECTION, 0);
                    /*
                      triggers the loading of directplay and connection to lobby
                     */
                    this->multiplayerJoinStep = 0;
                } else {
                    MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::initializeMultiplayerLobby, this)();
                    _candidateIndex = MACRO_CALL_MEMBER(
                        Synchrony::GameSynchronyState_Func::initializeDirectPlayAndCreateOrJoinSession, this)(FALSE);
                    if (_candidateIndex < 0) {
                        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::disconnectDPlay, this)();
                    } else {
                        this->field224_0x106ee4 = 1;
                        DAT_GameCore::instance.menuTabToSwitchTo.tabType = ((BuildingsAndStatusMenuTabType)0);
                        MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            UI::Enums::MVT_LOBBY_MENU, 0);
                        MACRO_CALL(Synchrony_Func::InitSkirmishLobbyData)();
                        Menu_LobbyMenu::instance.thousand = 0;
                        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::waitForMultiplayerHost, this)();
                        MACRO_CALL_MEMBER(Game::GameStateStructures_Func::resetTeams, DAT_GameState::ptr)();
                        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
                            Commands::GCT_ASK_FOR_SLOT_ASSIGNMENT);
                    }
                }
            }
        };
        return;
    }

}
}
