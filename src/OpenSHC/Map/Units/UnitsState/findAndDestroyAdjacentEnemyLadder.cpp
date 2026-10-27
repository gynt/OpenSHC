#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitType;
        using OpenSHC::Map::Units::States::UnitState;

        // FUNCTION: STRONGHOLDCRUSADER 0x00533810
        int UnitsState::findAndDestroyAdjacentEnemyLadder(int unitID, int checkOnly)
        {
            for (int direction = 0; direction < 8; ++direction) {
                int _otherUnitID = (short)DAT_TileMapState::instance
                                       .UnitLayer[DAT_TileMapState::instance
                                                      .directionTranslationMatrix[this->units[unitID].y][direction]
                                           + this->units[unitID].tile];
                if (_otherUnitID == 0) {
                    continue;
                }
                int _owner = this->units[unitID].owner;
                do {
                    if (DAT_GameState::instance.mapAndTime.playerTeams[_owner]
                            != DAT_GameState::instance.mapAndTime.playerTeams[this->units[_otherUnitID].owner]
                        && _owner != 0 && this->units[_otherUnitID].unitType == OpenSHC::Map::Units::UT_E_LADDER
                        && this->units[_otherUnitID].state.generic == (UnitState)3) {
                        if (checkOnly != 0) {
                            return direction;
                        }
                        this->units[_otherUnitID].dying = 1;
                        this->units[_otherUnitID].animationCycleNumber = 0;
                        this->units[_otherUnitID].state.generic = OpenSHC::Map::Units::States::US_DEATH_02;
                        this->units[_otherUnitID].movementState = 1;
                        return 1;
                    }
                    _otherUnitID = (short)this->units[_otherUnitID].nextUnitOnTheSameTile;
                } while (_otherUnitID > 0);
            }
            return -1;
        }

    }
}
}
