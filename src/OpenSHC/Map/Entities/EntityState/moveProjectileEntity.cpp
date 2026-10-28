#include "../EntityState.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"

#include "OpenSHC/Globals/DAT_EntityDefinedData.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"

#include "math.h"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        /* flightTime is a float in the original (fld dword at 0x4084BA); the header declares it int.
           The pitch falls back to the launch pitch when the flight time is exactly 0 (fucomp at 0x408544). */
        // FUNCTION: STRONGHOLDCRUSADER 0x004084A0
        BOOLEnum EntityState::moveProjectileEntity(int entityID)
        {
            double flightTime = *(float*)&this->entityArray[entityID].flightTime;
            double vCos = this->entityArray[entityID].vCos;
            double vSin = this->entityArray[entityID].vSin;
            int heightOffset = this->entityArray[entityID].height - this->entityArray[entityID].startingHeight;
            int heightStep = 0;
            if (this->entityArray[entityID].burnCyclesOrImpactCountdown != 0) {
                return FALSE;
            }
            if (this->entityArray[entityID].lineStepMode == 0) {
                this->entityArray[entityID].burnCyclesOrImpactCountdown = 0x28;
            }
            double horizontal = vCos * flightTime;
            double vertical = vSin * flightTime - flightTime * flightTime * 4.906;
            int targetDistance = (int)(horizontal * 0.25);
            int targetHeight = (int)(vertical + vertical);
            double pitch;
            if (flightTime != 0) {
                flightTime = flightTime - this->entityArray[entityID]._elapsedTimeOrGravityAccumulator;
                pitch = atan((vertical - (vSin * flightTime - flightTime * flightTime * 4.906))
                            / (horizontal - vCos * flightTime) * 3.0)
                    * 180.0 / 3.1415926535;
            } else {
                pitch = this->entityArray[entityID].moveDirOrDriftXOrLaunchPitch;
            }
            this->entityArray[entityID].wanderCountdownOrPitchDegrees = (short)(int)pitch;
            int distanceLeft = targetDistance - this->entityArray[entityID].travelledDistance;
            *(float*)&this->entityArray[entityID].flightTime = this->entityArray[entityID]._elapsedTimeOrGravityAccumulator
                + *(float*)&this->entityArray[entityID].flightTime;
            if (distanceLeft != 0) {
                heightStep = (targetHeight - heightOffset) / distanceLeft;
            }
            while (this->entityArray[entityID].travelledDistance < targetDistance) {
                this->entityArray[entityID].travelledDistance++;
                this->entityArray[entityID].losClearanceStepsLeft--;
                if (entityID != 0) {
                    MACRO_CALL_MEMBER(EntityState_Func::unlinkEntityFromTile, this)(entityID);
                }
                MACRO_CALL_MEMBER(EntityState_Func::updateEntityMicroMovement, this)(entityID);
                int curveType = DAT_EntityDefinedData::instance
                                    .EntityArrayCurveTypeForProjectileType[this->entityArray[entityID].entityType];
                if (curveType != 9 && curveType != 10) {
                    heightOffset += heightStep;
                    MACRO_CALL_MEMBER(EntityState_Func::updateProjectileHeightAndCollision, this)(
                        entityID, heightOffset, (int)pitch, 1);
                }
                if (MACRO_CALL_MEMBER(EntityState_Func::processEntityHitBuildingOrUnit, this)(entityID) == 0) {
                    MACRO_CALL_MEMBER(EntityState_Func::calculateEntityDrawOffset, this)(entityID);
                    return TRUE;
                }
                MACRO_CALL_MEMBER(EntityState_Func::calculateEntityDrawOffset, this)(entityID);
                if (this->entityArray[entityID].burnCyclesOrImpactCountdown != 0) {
                    break;
                }
            }
            this->entityArray[entityID].travelledDistance = (short)targetDistance;
            int curveType
                = DAT_EntityDefinedData::instance.EntityArrayCurveTypeForProjectileType[this->entityArray[entityID].entityType];
            if (curveType == 9) {
                short height = this->entityArray[entityID].height;
                short targetZ = this->entityArray[entityID].targetZ;
                if (height < targetZ) {
                    this->entityArray[entityID].height = height + 1;
                    return TRUE;
                }
                if (height > targetZ) {
                    height = height - 8;
                    this->entityArray[entityID].height = height;
                    if (height <= 0) {
                        int microY = this->entityArray[entityID].microY;
                        int microX = this->entityArray[entityID].microX;
                        this->entityArray[entityID].stepY = 0;
                        this->entityArray[entityID].stepX = 0;
                        this->entityArray[entityID].height = 0;
                        MACRO_CALL_MEMBER(EntityState_Func::spawnEntity, this)(
                            0, 0, 0, microX, microY, 0, microX, microY, 0, (EntityType)0x1f, 0);
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            this->entityArray[entityID].xPosition, this->entityArray[entityID].yPosition,
                            OpenSHC::DE::SHCDE::FX_GULL_DIVE);
                        return TRUE;
                    }
                }
            } else if (curveType == 10) {
                this->entityArray[entityID].height++;
                return TRUE;
            } else {
                MACRO_CALL_MEMBER(EntityState_Func::updateProjectileHeightAndCollision, this)(
                    entityID, targetHeight, (int)pitch, 0);
            }
            return TRUE;
        }

    } // namespace Entities
} // namespace Map
} // namespace OpenSHC
