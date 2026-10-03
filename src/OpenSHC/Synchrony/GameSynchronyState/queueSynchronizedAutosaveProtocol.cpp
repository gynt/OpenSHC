#include "../../Synchrony.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {
namespace Synchrony {

    using OpenSHC::Commands::GameCommandType;
    using OpenSHC::Game::GameMode;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0048C660
    void GameSynchronyState::queueSynchronizedAutosaveProtocol()
    {
        BOOLEnum BVar1;
        DWORD DVar2;
        if ((((this->currentGameMode != OpenSHC::Game::GM_SOLITARY)
                 && (this->currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER))
                && (this->isHost != FALSE))
            && ((this->skirmishAutoSaveEveryMinutes != 0 && (this->timeSkirmishGameStart != 0)))) {
            BVar1 = MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)();
            if ((BVar1 != FALSE) && ((this->syncStatus == 0 && (this->saveRelated == 0)))) {
                DVar2 = timeGetTime();
                if (this->skirmishAutoSaveEveryMinutes * 60000 < (int)(DVar2 - this->timeSkirmishGameStart)) {
                    /*
                      autosave
                     */
                    strcpy(this->shortMapName, "autosave");
                    this->DAT_GameCommandParam0 = DAT_GameCore::instance.mapTimeInTicks;
                    this->field75_0xbe4 = DVar2;
                    this->timeSkirmishGameStart = DVar2;
                    this->DAT_GameCommandParam1 = MACRO_CALL_MEMBER(
                        OpenSHC::Synchrony::GameSynchronyState_Func::computeSomeHashOnUnitArray, this)();
                    this->DAT_GameCommandParam2 = 1;
                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, this)(
                        OpenSHC::Commands::GCT_SAVE);
                }
            }
        }
    }

}
}
