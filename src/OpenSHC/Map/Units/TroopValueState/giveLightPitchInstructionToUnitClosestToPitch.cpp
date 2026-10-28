#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051BF70
        undefined4 TroopValueState::giveLightPitchInstructionToUnitClosestToPitch(int tile)
        {
            int const ditchID
                = MACRO_CALL_MEMBER(TileMapState_Func::getPitchDitchIDForTile, DAT_TileMapState::ptr)(tile);
            int minUnitID = 0;
            int minDistance = 100000000;
            for (int unitID = 1; unitID < (int)DAT_UnitsState::instance.maxUnitCount; ++unitID) {
                if (DAT_UnitsState::instance.units[unitID].logicalState != ULS_INVISIBLE
                    && MACRO_CALL_MEMBER(TroopValueState_Func::getPlayerNot1AndHasKeep, this)(
                           DAT_UnitsState::instance.units[unitID].owner)
                        != FALSE
                    && (DAT_UnitsState::instance.units[unitID].unitType == UT_E_ARCHER
                        || DAT_UnitsState::instance.units[unitID].unitType == UT_A_ARCHER)
                    && DAT_UnitsState::instance.units[unitID].dying == 0
                    && DAT_UnitsState::instance.units[unitID].isNearBrazier
                    && DAT_UnitsState::instance.units[unitID].targetingType_OR_performanceStep != UIT_LIGHT_PITCH) {
                    int const pitchY = DAT_TileMapState::instance.pitchDitches[ditchID].y;
                    int const pitchX = DAT_TileMapState::instance.pitchDitches[ditchID].x;
                    int const dy = pitchY - DAT_UnitsState::instance.units[unitID].y;
                    int const dx = pitchX - DAT_UnitsState::instance.units[unitID].x;
                    int const distanceSq = dx * dx + dy * dy;
                    if (distanceSq <= 2500
                        && MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::arrowShootingRelated,
                               DAT_EntityState::ptr)(DAT_UnitsState::instance.units[unitID].microXPosition,
                               DAT_UnitsState::instance.units[unitID].microYPosition,
                               DAT_UnitsState::instance.units[unitID].terrainOrClimbHeight
                                   + DAT_UnitsState::instance.units[unitID].buildingHeight + 30,
                               pitchX * 8 + 4, pitchY * 8 + 4,
                               DAT_TileMapState::instance
                                   .HeightLayer[DAT_TileMapState::instance.pitchDitches[ditchID].tile])
                            > 0
                        && distanceSq < minDistance) {
                        minUnitID = unitID;
                        minDistance = distanceSq;
                    }
                }
            }
            if (minUnitID == 0) {
                return 0;
            }
            DAT_UnitsState::instance.units[minUnitID].shootTargetMicroX
                = DAT_TileMapState::instance.pitchDitches[ditchID].x * 8 + 4;
            DAT_UnitsState::instance.units[minUnitID].shootTargetMicroY
                = DAT_TileMapState::instance.pitchDitches[ditchID].y * 8 + 4;
            DAT_UnitsState::instance.units[minUnitID].shootTargetZ
                = DAT_TileMapState::instance.HeightLayer[DAT_TileMapState::instance.pitchDitches[ditchID].tile];
            DAT_UnitsState::instance.units[minUnitID].shootTargetedUnit = -1;
            DAT_UnitsState::instance.units[minUnitID].targetID_OR_targetBuildingID = ditchID;
            DAT_UnitsState::instance.units[minUnitID]
                .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID
                = DAT_TileMapState::instance.pitchDitches[ditchID].uid;
            DAT_UnitsState::instance.units[minUnitID].pendingTargetingType = UIT_LIGHT_PITCH;
            DAT_UnitsState::instance.units[minUnitID].targetingType_OR_performanceStep = UIT_LIGHT_PITCH;
            DAT_UnitsState::instance.units[minUnitID].idleInterruptedForAttack = 0;
            MACRO_CALL_MEMBER(UnitsState_Func::makeUnitStopWalkingByClearingPathProgressState, DAT_UnitsState::ptr)(
                minUnitID);
            DAT_UnitsState::instance.units[minUnitID].state.generic = States::US_FIRE_WEAPONUnk;
            DAT_UnitsState::instance.units[minUnitID].fireImmediately = true;
            return 1;
        }

    }
}
}
