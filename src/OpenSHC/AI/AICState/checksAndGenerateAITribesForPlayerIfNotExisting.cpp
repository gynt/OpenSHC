#include "../AICState.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004CCFB0
    int AICState::checksAndGenerateAITribesForPlayerIfNotExisting(int playerID, int maxAmount, BOOLEnum checkOnly)
    {
        int _tribe;
        int _newTribe;
        int _offset;
        int _baseOffset;
        _baseOffset = DAT_SkirmishDefinedData::instance.AITribeIDOffsetForAIVUnitType[1];
        for (_offset = 0; _offset < maxAmount; _offset++) {
            if (9 < _offset) {
                return 0;
            }
            _tribe = (int)DAT_GameState::instance.playerDataArray[playerID]
                         .aiTribeIDs[DAT_SkirmishDefinedData::instance.AITribeIDOffsetForAIVUnitType[1] + _offset];
            if ((_tribe == 0)
                || (DAT_TribesState::instance.tribes[_tribe].uid
                    != DAT_GameState::instance.playerDataArray[playerID]
                        .aiTribeUIDs[DAT_SkirmishDefinedData::instance.AITribeIDOffsetForAIVUnitType[1] + _offset])) {
                if (checkOnly != FALSE) {
                    return 1;
                }
                _newTribe = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::TribesState_Func::createTribeForPlayer, DAT_TribesState::ptr)(playerID);
                DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[_baseOffset + _offset] = (short)_newTribe;
                DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[_baseOffset + _offset]
                    = DAT_TribesState::instance.tribes[_newTribe].uid;
                return _newTribe;
            }
        }
        return 0;
    }

}
}
