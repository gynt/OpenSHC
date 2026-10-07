#include "../../Synchrony.func.hpp"
#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x00480050
    void GameSynchronyState::resetGameCommands()
    {
        this->DAT_CurrentGameCommandID = 0;
        this->MBR_GameCommandID = 0;
        this->DAT_GameCommandArrayIndex = 0;
        MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            0x3e1c0, '\0', (void*)((int)(this->DAT_GameCommandArray)));
        this->DAT_LagIndicatorPerPlayer[0] = 1000;
        this->DAT_LagIndicatorPerPlayer[1] = 1000;
        this->DAT_LagIndicatorPerPlayer[2] = 1000;
        this->DAT_LagIndicatorPerPlayer[3] = 1000;
        this->DAT_LagIndicatorPerPlayer[4] = 1000;
        this->DAT_LagIndicatorPerPlayer[5] = 1000;
        this->DAT_LagIndicatorPerPlayer[6] = 1000;
        this->DAT_LagIndicatorPerPlayer[7] = 1000;
        this->DAT_LagIndicatorPerPlayer[8] = 1000;
    }

}
}
