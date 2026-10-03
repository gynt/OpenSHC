#include "../../../Map.func.hpp"
#include "../EntityState.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        using OpenSHC::Map::Entities::EntityType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00401A50
        undefined4 EntityState::isBrazierNearby(int unitX, int unitY, int unitZ)
        {
            uint uVar1;
            EntityTypeShort* _entityTypeAddress;
            int _entityCounter;
            _entityCounter = 1;
            if (1 < this->maxEntityCount) {
                _entityTypeAddress = &this->entityArray[1].entityType;
                do {
                    if ((_entityTypeAddress[-1] == 2) && (*_entityTypeAddress == OpenSHC::Map::Entities::ET_BRAZIER)) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                            DAT_DirectionAlgorithmState::ptr)(unitX, unitY,
                            (int)((int)((short)_entityTypeAddress[0xd])), (int)((int)((short)_entityTypeAddress[0xe])));
                        if ((DAT_DirectionAlgorithmState::instance.distanceHigh < 4)
                            && (uVar1 = unitZ - (short)_entityTypeAddress[9] >> 0x1f,
                                (int)((unitZ - (short)_entityTypeAddress[9] ^ uVar1) - uVar1) < 0x2d)) {
                            return (undefined4)(1);
                        }
                    }
                    _entityCounter = _entityCounter + 1;
                    _entityTypeAddress = _entityTypeAddress + 0x74;
                } while (_entityCounter < this->maxEntityCount);
            }
            return (undefined4)(0);
        }

    }
}
}
