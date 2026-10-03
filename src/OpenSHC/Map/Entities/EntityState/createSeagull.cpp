#include "../../../Map.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

#include "math.h"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        using OpenSHC::Map::Entities::EntityType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00406650
        int EntityState::createSeagull(int x, int y)
        {
            ExtraEntityInfo* pEVar1;
            short sVar2;
            int iVar3;
            uint _entityID;
            int iVar4;
            uint uVar5;
            int _id;
            short _y;
            ExtraEntityInfo* destination;
            short _x;
            double fVar6;
            double fVar7;
            short _y2;
            short _x2;
            _id = 1;
            pEVar1 = this->seagullArray;
            do {
                destination = pEVar1 + 1;
                if (pEVar1[1].field3_0x8 == 0)
                    break;
                if (pEVar1[1].entityUID != this->entityArray[destination->entityID].uid) {
                    MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                        100, '\0', (void*)((int)(destination)));
                }
                if (_id >= 99) {
                    return 0;
                }
                _id = _id + 1;
                pEVar1 = destination;
            } while (_id < 100);
            this->seagullArray[_id].field3_0x8 = 2;
            this->seagullArray[_id].field4_0xa = 0;
            this->seagullArray[_id].someCountDown = 0;
            _x = (short)x;
            this->seagullArray[_id].x = _x;
            this->seagullArray[_id].x_2 = _x;
            _y = (short)y;
            this->seagullArray[_id].y = _y;
            this->seagullArray[_id].y_2 = _y;
            this->seagullArray[_id].angle = SEC_RNG::instance.currentNumber2 % 0x168;
            this->seagullArray[_id].angle_2 = (short)(*(char*)((char*)&SEC_RNG::instance.currentNumber2 + 1)) % 0x168;
            MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
            uVar5 = (int)SEC_RNG::instance.currentNumber2 & 0x8000000f;
            if ((int)uVar5 < 0) {
                uVar5 = (uVar5 - 1 | 0xfffffff0) + 1;
            }
            this->seagullArray[_id].unknownCounter_0x16 = (short)uVar5 + 0x18;
            this->seagullArray[_id].numberBetween60And100
                = (short)(*(char*)((char*)&SEC_RNG::instance.currentNumber2 + 1)) % 0x28 + 0x3c;
            MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
            if ((SEC_RNG::instance.currentNumber2 & 1U) == 0) {
                this->seagullArray[_id].someAngle = -1;
            } else {
                this->seagullArray[_id].someAngle = 1;
            }
            sVar2 = this->seagullArray[_id].angle;
            fVar6 = ((double)(sVar2 + -0xb4) * (double)3.1415926535) / (double)180.0;
            sVar2 = this->seagullArray[_id].someAngle * 0x14 + sVar2;
            this->seagullArray[_id].field15_0x20 = (-(ushort)((SEC_RNG::instance.currentNumber2 & 2U) != 0) & 2) - 1;
            this->seagullArray[_id].angle = sVar2;
            if (0x167 < sVar2) {
                this->seagullArray[_id].angle = sVar2 + 0x168;
            }
            sVar2 = this->seagullArray[_id].angle;
            if (sVar2 < 0) {
                this->seagullArray[_id].angle = sVar2 + -0x168;
            }
            iVar4 = (int)this->seagullArray[_id].unknownCounter_0x16;
            this->seagullArray[_id].field12_0x1a = -0x14;
            fVar7 = sin(fVar6);
            iVar3 = (long)(fVar7 * (double)iVar4);
            fVar6 = cos((double)fVar6);
            iVar4 = (long)(fVar6 * (double)iVar4);
            _y2 = this->seagullArray[_id].y;
            _x2 = this->seagullArray[_id].x;
            this->seagullArray[_id].rngMax799_countdown = 400;
            this->seagullArray[_id].x_3 = _x;
            this->seagullArray[_id].y_3 = _y;
            MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::initializeSeagullMovementVector, this)(
                _id, (int)((int)(_x2)), (int)((int)(_y2)), (int)((int)(_x)), (int)((int)(_y)));
            this->seagullArray[_id].field25_0x34 = 5;
            _entityID = MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::spawnProjectileEntity, this)(
                _id, 0, 0, x, y, 0xfa, iVar3 + x, iVar4 + y, 0xfa, OpenSHC::Map::Entities::ET_SEAGULLUnk, 0);
            this->seagullArray[_id].entityID = (short)_entityID;
            this->seagullArray[_id].entityUID = this->entityArray[(short)_entityID].uid;
            this->seagullArray[_id].randomNumber = SEC_RNG::instance.currentNumber2;
            MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
            return _id;
        }

    }
}
}
