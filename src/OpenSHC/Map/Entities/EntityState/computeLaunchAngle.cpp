#include "../EntityState.func.hpp"

#include "float.h"
#include "math.h"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x00402C50
        int EntityState::computeLaunchAngle(int entityType, double launchSpeed, int horizontalDistance, int heightDifference)
        {
            double speedSq = launchSpeed * launchSpeed;
            double speedSqSq = speedSq * speedSq;
            double distance = horizontalDistance * 4;
            double distanceSq = distance * distance;
            int halfHeight = heightDifference / 2;
            double tanBase = speedSq / (distance * 9.812);
            double root = sqrt(speedSqSq / (96.275344 * distanceSq)
                - 2.0 * speedSq * halfHeight / (distanceSq * 9.812) - 1.0);

            int angleMinusRoot;
            double tanValue = tanBase - root;
            if (tanValue == HUGE_VAL || _isnan(tanValue)) {
                angleMinusRoot = 1000;
            }
            else {
                angleMinusRoot = (int)(atan(tanValue) * 180.0 / 3.1415926535 + 0.4999f);
            }

            int anglePlusRoot;
            tanValue = root + tanBase;
            if (tanValue == HUGE_VAL || _isnan(tanValue)) {
                anglePlusRoot = 1000;
            }
            else {
                anglePlusRoot = (int)(atan(tanValue) * 180.0 / 3.1415926535 + 0.4999f);
            }

            int angle = angleMinusRoot < anglePlusRoot ? angleMinusRoot : anglePlusRoot;
            if (angle < -90) {
                angle = angleMinusRoot > anglePlusRoot ? angleMinusRoot : anglePlusRoot;
                if (angle < -90) {
                    return 45;
                }
            }
            if (angle > 90) {
                return 45;
            }
            return angle;
        }

    }
}
}
