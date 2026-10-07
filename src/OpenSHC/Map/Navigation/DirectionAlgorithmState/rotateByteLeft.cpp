#include "../../../Map.func.hpp"
#include "../DirectionAlgorithmState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        // FUNCTION: STRONGHOLDCRUSADER 0x0046CE30
        byte DirectionAlgorithmState::rotateByteLeft(byte value, int bits)
        {
            switch (bits) {
            case 1:
                return (byte)(value << 1 | (char)value < '\0');
            case 2:
                return (byte)(value << 2 | value >> 6);
            case 3:
                return (byte)(value << 3 | value >> 5);
            case 4:
                return (byte)(value << 4 | value >> 4);
            case 5:
                return (byte)(value << 5 | value >> 3);
            case 6:
                return (byte)(value << 6 | value >> 2);
            case 7:
                value = value << 7 | value >> 1;
            }
            return (byte)(value);
        }

    }
}
}
