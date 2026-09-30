#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::Instructions::UnitMatchSpeedEnum;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0051B190
        int TroopValueState::assignTribeToSupportPoint(uint x, uint y, int tribeID)
        {
            uint y1;
            int _index;
            short _oldIndex;
            _index = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::findSupportPointIndex,
                DAT_PathFindingState::ptr)(200, x, y, tribeID);
            if (_index != 0) {
                _oldIndex = DAT_TribesState::instance.tribes[tribeID].supportPointIndex;
                DAT_TribesState::instance.tribes[tribeID].oldSupportPointIndex = _oldIndex;
                this->attackInfo.supportPointsArray[_oldIndex].tribeID = 0;
                this->attackInfo.supportPointsArray[_oldIndex].tribeUID = 0;
                DAT_TribesState::instance.tribes[tribeID].supportPointIndex = (short)_index;
                y1 = this->attackInfo.supportPointsArray[_index].y;
                this->attackInfo.supportPointsArray[_index].tribeUID = DAT_TribesState::instance.tribes[tribeID].uid;
                this->attackInfo.supportPointsArray[_index].tribeID = tribeID;
                this->attackInfo.supportPointsArray[_index].three = 3;
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::giveTribeMoveInstruction,
                    DAT_TribesState::ptr)(tribeID, (uint)((int)(this->attackInfo.supportPointsArray[_index].x)), y1, 0,
                    0, OpenSHC::Map::Units::Instructions::UMSE_0);
                return _index;
            }
            return 0;
        }

    }
}
}
