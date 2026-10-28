#include "../EntityState.func.hpp"

#include "math.h"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x00402DA0
        int EntityState::computeVelocity(int unusedEntityType, double angleDegrees, int horizontalDistance, int heightDifference)
        {
            double angleRad = angleDegrees * 3.1415926535 / 180.0;
            double doubledDistance = horizontalDistance * 2;
            double cosAngle = cos(angleRad);
            double numerator = 9.812 * doubledDistance * doubledDistance / (cosAngle * cosAngle);
            return (int)sqrt(numerator / (tan(angleRad) * doubledDistance - heightDifference / 4));
        }

    }
}
}
