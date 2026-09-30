#include "../AICState.func.hpp"

#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/AI/AIVUnitType.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/Map/Units/UnitTypeInt.hpp"
#include "OpenSHC/Map/Units/UnitTypeShort.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AIType;
    using OpenSHC::AI::AIVUnitType;
    using OpenSHC::Map::Units::UnitType;
    using OpenSHC::Map::Units::UnitTypeInt;
    using OpenSHC::Map::Units::UnitTypeShort;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004CC390
    AIVUnitType AICState::getUnitTypeIndexForUnitID(int unitID, int param_2)
    {
        AIVUnitType _someUnitTypeIndex;
        UnitTypeInt _unitType2;
        short _playerID;
        UnitTypeShort _unitType;
        _unitType = DAT_UnitsState::instance.units[unitID].unitType;
        _playerID = DAT_UnitsState::instance.units[unitID].owner;
        if (_unitType == OpenSHC::Map::Units::UT_PEASANT) {
            _unitType = DAT_UnitsState::instance.units[unitID].unitTypeToChangeInto;
        }
        _unitType2 = (UnitTypeInt)(short)_unitType;
        if ((((DAT_GameState::instance.playerDataArray[_playerID].aiType != OpenSHC::AI::AIT_CALIPH) && (param_2 != 0))
                && (0 < DAT_GameState::instance.playerDataArray[_playerID].aivUnitLocationSlotLocationCount[0xd]))
            && (((_unitType2 == OpenSHC::Map::Units::UT_E_ARCHER || (_unitType2 == OpenSHC::Map::Units::UT_E_XBOW))
                || ((_unitType2 == OpenSHC::Map::Units::UT_A_ARCHER
                    || ((_unitType2 == OpenSHC::Map::Units::UT_A_SLINGER
                        || (_unitType2 == OpenSHC::Map::Units::UT_A_FIRETHROWER)))))))) {
            /*
              slave
             */
            return OpenSHC::AI::AIVUT_SLAVE;
        }
        _someUnitTypeIndex = OpenSHC::AI::AIVUT_NONE;
        do {
            if (DAT_SkirmishDefinedData::instance.SomeAIUnitTypeArray[_someUnitTypeIndex] == _unitType2) {
                return _someUnitTypeIndex;
            }
            _someUnitTypeIndex = (OpenSHC::AI::AIVUnitType)(_someUnitTypeIndex + OpenSHC::AI::AIVUT_ENGINEER);
        } while ((int)_someUnitTypeIndex < 0x14);
        return OpenSHC::AI::AIVUT_NONE;
    }

}
}
