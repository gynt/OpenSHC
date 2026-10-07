#include "../IO.func.hpp"

#include "OpenSHC/Globals/DAT_ProtocolDefinedData.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x00487090
char IO::Base64Encode_CharacterLookup(char param_1)
{
    if ('?' < param_1) {
        return '=';
    }
    return (char)(DAT_ProtocolDefinedData::instance.field136_0x4f4[param_1]);
}

}
