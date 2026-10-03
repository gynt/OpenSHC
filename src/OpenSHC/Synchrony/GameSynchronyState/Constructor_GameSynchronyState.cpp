#include "../../Synchrony.func.hpp"

#include "OpenSHC/Global.func.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Synchrony {

    using OpenSHC::Game::GameMode;

    // FUNCTION: STRONGHOLDCRUSADER 0x0048C150
    GameSynchronyState* GameSynchronyState::Constructor_GameSynchronyState()
    {
        this->currentGameMode = OpenSHC::Game::GM_SOLITARY;
        this->field304_0x109e8c = 1;
        this->DPLAYX_ReceivedPlayerID = 0;
        this->DPLAY_ToID = 0;
        this->DPLAYX_PlayerHandle = 0xffffffff;
        this->currentPlayerSlotID = 0;
        this->field326_0x109ecc = GetTickCount();
        this->now2 = GetTickCount();
        this->field329_0x109ed8 = timeGetTime();
        this->field319_0x109ebc = 0;
        this->field320_0x109ec0 = 0;
        this->field316_0x109eb0 = 1;
        this->field317_0x109eb4 = 1;
        this->DAT_HostAnnounced = 0;
        this->field57_0x79c[0] = 0;
        this->field57_0x79c[1] = 0;
        this->field57_0x79c[2] = 0;
        this->field57_0x79c[3] = 0;
        this->field196_0x101ad4 = 0;
        MACRO_CALL(OpenSHC::Global_Func::PrintToDestination)(this->DPLAYX_SessionName, L"Crusader");
        MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::copyData, DAT_LowLevelMemory::ptr)(
            0xc, "Contestant", (void*)((int)(this->DPLAY_PlayerShortName)));
        this->scrollBarItemCount = 0;
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::setupSkirmishLobby, this)();
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::readGameSpyConfig, this)();
        this->skirmishAutoSaveEveryMinutes = 10;
        return this;
    }

}
}
