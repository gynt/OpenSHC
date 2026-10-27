#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

// the original falls off the end of the non-campground path without a return value (eax = 0 from the call)
#pragma warning(disable : 4715)

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Game::GameMode2;
        using OpenSHC::Map::Units::UnitLogicState;
        using OpenSHC::Map::Units::UnitType;
        using OpenSHC::Map::Units::States::UnitState;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0052EDC0
        int UnitsState::disbandUnit(int unitID)
        {
            if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_E_KNIGHT
                && this->units[unitID].stablesOrPitchSourceBuildingID != 0) {
                if (*(int*)&this->units[unitID].pitchSourceBuildingUid
                    == DAT_BuildingsState::instance.buildings[this->units[unitID].stablesOrPitchSourceBuildingID]
                        .uid) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::removeTetheredUnitFromBuilding,
                        DAT_BuildingsState::ptr)(this->units[unitID].stablesOrPitchSourceBuildingID, unitID);
                }
            }
            if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                this->units[unitID].logicalState = OpenSHC::Map::Units::ULS_REMOVE;
                /* uninitialised as in the original: the compiler places it in the (dead) unitID parameter slot
                   (0x0052EE20 lea edx,[esp+0xc]), so for unit types getPriceForDisbandedUnitType has no price for
                   the refund is the unit ID */
                int _refund;
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getPriceForDisbandedUnitType,
                    DAT_BuildingsState::ptr)((UnitType)this->units[unitID].unitType, &_refund);
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .pendingResources[0xf] += _refund;
                return (
                    int)&DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .pendingResources[0xf];
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::playerHasACampground, DAT_GameState::ptr)(
                    this->units[unitID].owner)
                != FALSE) {
                this->units[unitID].fadeLevel = 0;
                this->units[unitID].state_2 = 0;
                this->units[unitID].stateAfterFade = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                this->units[unitID].unitTypeToChangeInto = OpenSHC::Map::Units::UT_PEASANT;
                this->units[unitID].state.generic = OpenSHC::Map::Units::States::US_FADE_TRANSITION;
                this->units[unitID].fadeAlphaStep = 1;
                this->units[unitID].isFadeActive = 1;
                return 1;
            }
            this->units[unitID].fadeLevel = 0;
            this->units[unitID].updateTickTracker = 0;
            this->units[unitID].state.generic = OpenSHC::Map::Units::States::US_DISAPPEAR;
            this->units[unitID].isDisbanded = 1;
            /* the original has no return value here: eax still holds the (zero) campground result */
        }

    }
}
}
