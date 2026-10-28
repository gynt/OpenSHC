#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Units.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/Pathfinding/DestinationNeededEnum.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Units::UnitLogicState;
    using OpenSHC::Map::Units::Pathfinding::DestinationNeededEnum;
    using OpenSHC::Map::Units::States::UnitState;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x005416B0
    void Units::UpdateMerchant()
    {
        int unitID = DAT_CurrentUnitSlotID::instance;
        DAT_UnitsState::instance.units[unitID].ownerColorIndex = 1;
        UnitStateShort state = DAT_UnitsState::instance.units[unitID].state.generic;
        if (state == OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk) {
            DAT_UnitsState::instance.units[unitID].gfxNumber = 1;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            int marketplace
                = DAT_GameState::instance.playerDataArray[DAT_GameState::instance.mapAndTime.traderVisitsPlayer]
                      .marketplace.id;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::buildingIsAccessible,
                    DAT_BuildingsState::ptr)(marketplace, 1)
                != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance, DAT_BuildingsState::instance.buildings[marketplace].buildingEntryX,
                    DAT_BuildingsState::instance.buildings[marketplace].buildingEntryY, 0);
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_IDLEUnk;
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].logicalState
                = OpenSHC::Map::Units::ULS_REMOVE;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_IDLEUnk) {
            DAT_UnitsState::instance.units[unitID].stateBasedSpeed
                = DAT_TroopValueState::instance.attackInfo.aiTroops > 1;
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            MACRO_CALL_MEMBER(
                OpenSHC::Map::Units::UnitsState_Func::clearHiddenFlagAndUpdatePosition, DAT_UnitsState::ptr)(unitID);
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance)
                != FALSE) {
                MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::activateTraderState, DAT_GameState::ptr)();
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_FADE_TRANSITION;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].fadeLevel = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].fadeAlphaStep
                    = 2;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateAfterFade = 2;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker = 0;
            }
            return;
        }
        if (state == (UnitState)2) {
            DAT_UnitsState::instance.units[unitID].gfxNumber = 1;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            if (DAT_GameState::instance.mapAndTime.traderState == 1) {
                DAT_UnitsState::instance.units[unitID].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
                DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_FADE_TRANSITION;
                DAT_UnitsState::instance.units[unitID].fadeLevel = 32;
                DAT_UnitsState::instance.units[unitID].fadeAlphaStep = 0xfe;
                DAT_UnitsState::instance.units[unitID].stateAfterFade = 3;
                DAT_UnitsState::instance.units[unitID].updateTickTracker = 0;
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::resetUnitMovementState, DAT_UnitsState::ptr)(
                    unitID);
            }
            return;
        }
        if (state == (UnitState)3) {
            if (DAT_UnitsState::instance.units[unitID].destinationNeeded
                != OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                    unitID, DAT_GameState::instance.mapAndTime.signpostsMapEdge[0][0].x,
                    DAT_GameState::instance.mapAndTime.signpostsMapEdge[0][0].y, 0);
                unitID = DAT_CurrentUnitSlotID::instance;
                DAT_UnitsState::instance.units[unitID].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET;
            }
            DAT_UnitsState::instance.units[unitID].stateBasedSpeed
                = DAT_TroopValueState::instance.attackInfo.aiTroops > 1;
            DAT_UnitsState::instance.units[unitID].gfxNumber = 1;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            MACRO_CALL_MEMBER(
                OpenSHC::Map::Units::UnitsState_Func::clearHiddenFlagAndUpdatePosition, DAT_UnitsState::ptr)(unitID);
            int traveller = DAT_CurrentUnitSlotID::instance;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    traveller)
                != FALSE) {
                DAT_UnitsState::instance.units[traveller].logicalState = OpenSHC::Map::Units::ULS_REMOVE;
            }
            return;
        }
        if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::isUnitInDeathState,
                DAT_UnitsState::ptr)(unitID)
            != FALSE) {
            DAT_UnitsState::instance.units[unitID].gfxNumber = 1;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::clearHiddenFlagAndUpdatePosition,
                DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance);
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_DISAPPEAR;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker = 0;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_DISAPPEAR) {
            DAT_UnitsState::instance.units[unitID].fadeLevel += 1;
            if ((char)DAT_UnitsState::instance.units[unitID].fadeLevel > 32) {
                DAT_UnitsState::instance.units[unitID].fadeLevel = 32;
            }
            DAT_UnitsState::instance.units[unitID].updateTickTracker += 1;
            if (DAT_UnitsState::instance.units[unitID].updateTickTracker > 32) {
                DAT_UnitsState::instance.units[unitID].logicalState = OpenSHC::Map::Units::ULS_REMOVE;
            }
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_FADE_TRANSITION) {
            DAT_UnitsState::instance.units[unitID].fadeLevel
                += DAT_UnitsState::instance.units[unitID].fadeAlphaStep;
            if ((char)DAT_UnitsState::instance.units[unitID].fadeLevel < 0) {
                DAT_UnitsState::instance.units[unitID].fadeLevel = 0;
            } else if ((char)DAT_UnitsState::instance.units[unitID].fadeLevel >= 32) {
                DAT_UnitsState::instance.units[unitID].fadeLevel = 31;
            }
            DAT_UnitsState::instance.units[unitID].updateTickTracker += 1;
            if (DAT_UnitsState::instance.units[unitID].updateTickTracker > 16) {
                DAT_UnitsState::instance.units[unitID].updateTickTracker = 0;
                DAT_UnitsState::instance.units[unitID].fadeLevel = 0;
                DAT_UnitsState::instance.units[unitID].state.generic
                    = DAT_UnitsState::instance.units[unitID].stateAfterFade;
                if ((char)DAT_UnitsState::instance.units[unitID].fadeAlphaStep > 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::commitUnitLocation, DAT_UnitsState::ptr)(
                        DAT_CurrentUnitSlotID::instance);
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updateWorkshopProgressSign,
                    DAT_BuildingsState::ptr)(DAT_UnitsState::instance.units[unitID].workplaceOrHomeBuildingID, 2);
            }
            return;
        }
        DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
        MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::makeUnitStopWalkingByClearingPathProgressState,
            DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance);
    }

}
}
