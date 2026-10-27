#include "../EntityState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

#include "math.h"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // Works on `this` (edi = ecx at 0x406656). Remainders are signed: currentNumber2 % 360 and % 16 (movsx word,
        // idiv / and 0x8000000f), the high byte of currentNumber2 as a signed char (movsx byte [0x1A279C3]) % 360
        // and % 40. The angle wrap is inverted in the original (>= 360 adds 360, < 0 subtracts 360; 0x4067E1 /
        // 0x4067F9), compared as signed shorts (cmp ax, 0x168; jl / test ax, ax; jge).
        // FUNCTION: STRONGHOLDCRUSADER 0x00406650
        int EntityState::createSeagull(int x, int y)
        {
            int seagullID;
            int offsetX;
            int offsetY;
            short entityID;
            for (seagullID = 1; seagullID < 100; seagullID++) {
                if (this->seagullArray[seagullID].slotState == 0) {
                    break;
                }
                if (this->seagullArray[seagullID].entityUID
                    != this->entityArray[this->seagullArray[seagullID].entityID].uid) {
                    MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                        sizeof(ExtraEntityInfo), 0, &this->seagullArray[seagullID]);
                }
                if (seagullID >= 99) {
                    return 0;
                }
            }
            this->seagullArray[seagullID].slotState = 2;
            this->seagullArray[seagullID].unkResetOnCreateA = 0;
            this->seagullArray[seagullID].diveCountdown = 0;
            this->seagullArray[seagullID].x = x;
            this->seagullArray[seagullID].x_2 = x;
            this->seagullArray[seagullID].y = y;
            this->seagullArray[seagullID].y_2 = y;
            this->seagullArray[seagullID].angle = SEC_RNG::instance.currentNumber2 % 360;
            this->seagullArray[seagullID].angle_2 = ((char*)&SEC_RNG::instance.currentNumber2)[1] % 360;
            MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
            this->seagullArray[seagullID].circleRadius = SEC_RNG::instance.currentNumber2 % 16 + 0x18;
            this->seagullArray[seagullID].orbitCenterRadius
                = ((char*)&SEC_RNG::instance.currentNumber2)[1] % 40 + 0x3c;
            MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
            if ((SEC_RNG::instance.currentNumber2 & 1) != 0) {
                this->seagullArray[seagullID].circleDirection = 1;
            }
            else {
                this->seagullArray[seagullID].circleDirection = -1;
            }
            this->seagullArray[seagullID].angle2Step = (SEC_RNG::instance.currentNumber2 & 2) != 0 ? 1 : -1;
            double angleRad = (this->seagullArray[seagullID].angle - 180) * 3.1415926535 / 180.0;
            this->seagullArray[seagullID].angle
                = this->seagullArray[seagullID].circleDirection * 20 + this->seagullArray[seagullID].angle;
            if (this->seagullArray[seagullID].angle >= 360) {
                this->seagullArray[seagullID].angle += 360;
            }
            if (this->seagullArray[seagullID].angle < 0) {
                this->seagullArray[seagullID].angle -= 360;
            }
            this->seagullArray[seagullID].circlePhase = -20;
            offsetX = (int)(sin(angleRad) * this->seagullArray[seagullID].circleRadius);
            offsetY = (int)(cos(angleRad) * this->seagullArray[seagullID].circleRadius);
            this->seagullArray[seagullID].retargetWaitCountdown = 400;
            this->seagullArray[seagullID].x_3 = x;
            this->seagullArray[seagullID].y_3 = y;
            MACRO_CALL_MEMBER(EntityState_Func::initializeSeagullMovementVector, this)(seagullID,
                this->seagullArray[seagullID].x, this->seagullArray[seagullID].y, this->seagullArray[seagullID].x_3,
                this->seagullArray[seagullID].y_3);
            this->seagullArray[seagullID].lineStepDelay = 5;
            entityID = MACRO_CALL_MEMBER(EntityState_Func::spawnEntity, this)(
                seagullID, 0, 0, x, y, 0xfa, offsetX + x, offsetY + y, 0xfa, ET_SEAGULL, 0);
            this->seagullArray[seagullID].entityID = entityID;
            this->seagullArray[seagullID].entityUID = this->entityArray[entityID].uid;
            this->seagullArray[seagullID].randomNumber = SEC_RNG::instance.currentNumber2;
            MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
            return seagullID;
        }

    }
}
}
