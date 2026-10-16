#include "../../Synchrony.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameLoopStopwatch.hpp"
#include "OpenSHC/Globals/DAT_MillisecCarry.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Synchrony {

    using Game::GameMode;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00487A30
    int GameSynchronyState::determineGameTicksToPerform(int currentPlayerSlotID)
    {
        int iVar1;
        int _durationOfOneTick;
        int _relativeTickTime;
        dword _gameSpeedLevel = this->skirmishGameSpeedLevel;
        if (!DAT_GameCore::instance.gameSpeedLevel) {
            DAT_GameCore::instance.gameSpeedLevel = 40;
        }
        if ((DAT_GameCore::instance.currentlyInGameUnk_0xa4 != TRUE) || (this->DAT_GameHalted)) {
            return 0;
        }
        if ((this->currentGameMode == Game::GM_SOLITARY)
            || (this->currentGameMode == Game::GM_SKIRMISH_SINGLE_PLAYER)) {
            this->mapTimeInTicksSinglePlayer = DAT_GameCore::instance.mapTimeInTicks;
            _gameSpeedLevel = DAT_GameCore::instance.gameSpeedLevel;
            _relativeTickTime = this->relativeTickTime;
        } else {
            /*
              Calculate multiplayer game speed.
             */
            DAT_GameCore::instance.gameSpeedMultiplicator = 1;
            DAT_GameSynchronyState::instance.relativeTickTime = 0;
            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::computeLatencyAdjustmentFromMatchTimes, this)(
                currentPlayerSlotID);
            _relativeTickTime = this->ticksBehindFastestPlayer;
            if (-1 < (int)this->ticksBehindFastestPlayer
                && (iVar1 = this->ticksAheadOfSlowestPlayer, _relativeTickTime = DAT_GameSynchronyState::instance.relativeTickTime, 0 < iVar1)) {
                int iVar2 = this->ticksAheadOfSlowestPlayer;
                if (iVar2 > (int)this->commandDelay + 0x4b) {
                    DAT_GameSynchronyState::instance.relativeTickTime = iVar1;
                    if ((int)this->unknownIncrementBy40_01 < 1) {
                        this->unknownIncrementBy40_01 = 1;
                    }
                    _gameSpeedLevel = this->unknownIncrementBy40_01;
                    _relativeTickTime = DAT_GameSynchronyState::instance.relativeTickTime;
                    if ((int)this->unknownIncrementBy40_01 > this->skirmishGameSpeedLevel) {
                        _gameSpeedLevel = this->skirmishGameSpeedLevel;
                    }
                } else {
                    _relativeTickTime = iVar1;
                    if (5 < iVar2
                        && (_gameSpeedLevel = ((5 - iVar2) * 2) / 3 + this->skirmishGameSpeedLevel,
                            (int)_gameSpeedLevel < 15)) {
                        _gameSpeedLevel = 15;
                    }
                }
            }
        }
        DAT_GameSynchronyState::instance.relativeTickTime = _relativeTickTime;
        if (DAT_GameCore::instance.gameSpeedMultiplicator < 0) {
            _durationOfOneTick
                = -1000 / (int)_gameSpeedLevel * DAT_GameCore::instance.gameSpeedMultiplicator;
        } else {
            _durationOfOneTick = 1000 / (int)_gameSpeedLevel;
            if (1 < DAT_GameCore::instance.gameSpeedMultiplicator) {
                _durationOfOneTick = _durationOfOneTick / DAT_GameCore::instance.gameSpeedMultiplicator;
            }
        }
        _relativeTickTime
            = DAT_MillisecCarry::instance + (DAT_GameLoopStopwatch::instance.duration_0x0 - _durationOfOneTick);
        DAT_MillisecCarry::instance = _relativeTickTime;
        if (_relativeTickTime < 0) {
            /*
              Wait
             */
            if (_relativeTickTime < -_durationOfOneTick) {
                DAT_MillisecCarry::instance = _relativeTickTime + _durationOfOneTick;
                return 0;
            }
        } else {
            /*
              Execute game ticks
             */
            if (_durationOfOneTick < DAT_GameCore::instance.averageTimePerGameTick
                && _durationOfOneTick * 2 <= _relativeTickTime
                && _durationOfOneTick == 1000 / (int)_gameSpeedLevel) {
                /*
                  Slow down
                 */
                DAT_MillisecCarry::instance = 0;
                return 2;
            }
            if ((_durationOfOneTick * 7) / 10 < DAT_GameCore::instance.averageTimePerGameTick
                && _durationOfOneTick * 2 <= _relativeTickTime
                && _durationOfOneTick == 1000 / (int)_gameSpeedLevel) {
                /*
                  Slow down
                 */
                DAT_MillisecCarry::instance = 0;
                return 3;
            }
            if (_durationOfOneTick * 10 < _relativeTickTime) {
                /*
                  Cap game ticks per rendering
                 */
                DAT_MillisecCarry::instance = 0;
                return (int)(11);
            }
            if (_durationOfOneTick < _relativeTickTime) {
                DAT_MillisecCarry::instance
                    = _relativeTickTime - (_relativeTickTime / _durationOfOneTick) * _durationOfOneTick;
                return _relativeTickTime / _durationOfOneTick + 1;
            }
        }
        return 1;
    }

}
}
