#include "../BitMapState.func.hpp"

namespace OpenSHC {
namespace IO {

    // FUNCTION: STRONGHOLDCRUSADER 0x0046C580
    BitMapState* BitMapState::Constructor_BitMapState()
    {
        this->address = 0;
        this->surface = 0;
        this->forceRgb555 = 0;
        return this;
    }

}
}
