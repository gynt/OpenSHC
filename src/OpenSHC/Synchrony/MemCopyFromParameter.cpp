#include "../Synchrony.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandParameterLocation.hpp"
#include "OpenSHC/Commands/GameCommandParameterReadWrite.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

namespace OpenSHC {

using OpenSHC::Commands::GameCommandParameterLocation;
using OpenSHC::Commands::GameCommandParameterReadWrite;

// FUNCTION: STRONGHOLDCRUSADER 0x00488480
void Synchrony::MemCopyFromParameter(char* dest, size_t size, undefined4 playerID)
{
    void* destination;
    int iVar1;
    int iVar2;
    void* local_3f0;
    char local_3ec[1000];
    uint local_4;
    local_4 = MSVC_SecurityCookie::instance ^ (uint)&local_3f0;
    destination = MACRO_CALL(OpenSHC::OS_Func::_malloc)(size);
    local_3f0 = destination;
    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
        DAT_GameSynchronyState::ptr)(destination, size, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
        OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
    iVar2 = 0;
    if (0 < (int)size) {
        iVar1 = (int)destination - (int)dest;
        do {
            if (dest[iVar1] != *dest) {
                MACRO_CALL(OpenSHC::OS_Func::_sprintf)(
                    local_3ec, "ID:%d OF:%d M:%d S:%d", playerID, iVar2, (int)dest[iVar1], (int)*dest);
            }
            *dest = dest[iVar1];
            iVar2 = iVar2 + 1;
            dest = dest + 1;
            destination = local_3f0;
        } while (iVar2 < (int)size);
    }
    MACRO_CALL(OpenSHC::OS_Func::_free_base)(destination);
    ;
}

}
