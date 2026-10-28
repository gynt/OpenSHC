#include "../EntityState.func.hpp"

#include "OpenSHC/Map/Entities/EntityType.hpp"

#include "OpenSHC/Globals/DAT_EntityDefinedData.hpp"

#include "math.h"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x00403A20
        void EntityState::initializeProjectileVelocities(
            int entityID, int x, int y, int height, int targetX, int targetY, int targetZ)
        {
            if (y > targetY) {
                this->entityArray[entityID].lineDeltaY = y - targetY;
            }
            else {
                this->entityArray[entityID].lineDeltaY = targetY - y;
            }
            if (x > targetX) {
                this->entityArray[entityID].lineDeltaX = x - targetX;
            }
            else {
                this->entityArray[entityID].lineDeltaX = targetX - x;
            }
            if (this->entityArray[entityID].height < this->entityArray[entityID].targetZ) {
                this->entityArray[entityID].lineDeltaZ
                    = this->entityArray[entityID].targetZ - this->entityArray[entityID].height;
            }
            else {
                this->entityArray[entityID].lineDeltaZ
                    = this->entityArray[entityID].height - this->entityArray[entityID].targetZ;
            }
            this->entityArray[entityID].lineTargetMicroX = targetX;
            this->entityArray[entityID].lineTargetMicroY = targetY;
            this->entityArray[entityID].stepX = x <= targetX ? 1 : -1;
            this->entityArray[entityID].stepY = y <= targetY ? 1 : -1;

            if (this->entityArray[entityID].lineDeltaX == 0 && this->entityArray[entityID].lineDeltaY == 0) {
                this->entityArray[entityID].lineStepMode = 0;
            }
            else if (this->entityArray[entityID].lineDeltaX == 0) {
                this->entityArray[entityID].lineStepMode = 1;
            }
            else if (this->entityArray[entityID].lineDeltaY == 0) {
                this->entityArray[entityID].lineStepMode = 2;
            }
            else if (this->entityArray[entityID].lineDeltaY > this->entityArray[entityID].lineDeltaX) {
                this->entityArray[entityID].lineStepMode = 3;
            }
            else {
                this->entityArray[entityID].lineStepMode = 4;
            }

            if (this->entityArray[entityID].lineStepMode == 3) {
                int incMinor = this->entityArray[entityID].lineDeltaX * 2;
                this->entityArray[entityID].lineStepIncMinor = incMinor;
                this->entityArray[entityID].lineStepIncMajor = incMinor - this->entityArray[entityID].lineDeltaY * 2;
                this->entityArray[entityID].lineStepError = incMinor - this->entityArray[entityID].lineDeltaY;
            }
            else if (this->entityArray[entityID].lineStepMode == 4) {
                short incMinor = this->entityArray[entityID].lineDeltaY * 2;
                this->entityArray[entityID].lineStepIncMinor = incMinor;
                this->entityArray[entityID].lineStepIncMajor = incMinor - this->entityArray[entityID].lineDeltaX * 2;
                this->entityArray[entityID].lineStepError = incMinor - this->entityArray[entityID].lineDeltaX;
            }

            int curveType = DAT_EntityDefinedData::instance
                                .EntityArrayCurveTypeForProjectileType[(short)this->entityArray[entityID].entityType];
            if (curveType == 0) {
                uint losDistance = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Entities::EntityState_Func::computeLineOfSightDistance, this)(
                    x, y, height, targetX, targetY, targetZ, 1);
                this->entityArray[entityID].lineOfSightDistanceInit = losDistance;
                this->entityArray[entityID].lineOfSightDistance = losDistance;
                this->entityArray[entityID].losClearanceStepsLeft = (short)this->lineOfSightClearanceSteps;
                this->entityArray[entityID].moveDirOrDriftXOrLaunchPitch
                    = MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::computeLaunchAngle, this)(
                        (short)this->entityArray[entityID].entityType,
                        (double)this->entityArray[entityID].launchSpeedOrDriftPeriodY, (short)losDistance,
                        this->entityArray[entityID].heightDifference);
            }
            else if (curveType == 1) {
                uint losDistance = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Entities::EntityState_Func::computeLineOfSightDistance, this)(
                    x, y, height, targetX, targetY, targetZ, 1);
                this->entityArray[entityID].lineOfSightDistanceInit = losDistance;
                this->entityArray[entityID].lineOfSightDistance = losDistance;
                this->entityArray[entityID].losClearanceStepsLeft = (short)this->lineOfSightClearanceSteps;
                this->entityArray[entityID].launchSpeedOrDriftPeriodY
                    = MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::computeVelocity, this)(
                        (short)this->entityArray[entityID].entityType,
                        (double)this->entityArray[entityID].moveDirOrDriftXOrLaunchPitch, (short)losDistance,
                        this->entityArray[entityID].heightDifference);
            }
            else if (curveType == 2) {
                uint losDistance = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Entities::EntityState_Func::computeLineOfSightDistance, this)(
                    x, y, height, targetX, targetY, targetZ, 1);
                this->entityArray[entityID].lineOfSightDistanceInit = losDistance;
                this->entityArray[entityID].lineOfSightDistance = losDistance;
                this->entityArray[entityID].losClearanceStepsLeft = (short)this->lineOfSightClearanceSteps;
                if (this->entityArray[entityID].height > this->entityArray[entityID].targetZ) {
                    this->entityArray[entityID].moveDirOrDriftXOrLaunchPitch = 3;
                }
                int heightDifference = this->entityArray[entityID].heightDifference;
                short speed = MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::computeVelocity, this)(
                    (short)this->entityArray[entityID].entityType,
                    (double)this->entityArray[entityID].moveDirOrDriftXOrLaunchPitch, (short)losDistance, heightDifference);
                this->entityArray[entityID].launchSpeedOrDriftPeriodY = speed;
                if (speed <= 0) {
                    this->entityArray[entityID].moveDirOrDriftXOrLaunchPitch = 15;
                    this->entityArray[entityID].launchSpeedOrDriftPeriodY
                        = MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::computeVelocity, this)(
                            (short)this->entityArray[entityID].entityType, 15.0, (short)losDistance, heightDifference);
                }
            }
            else if (curveType == 3) {
                ushort rngBits = (ushort)this->entityArray[entityID].rng_1;
                this->entityArray[entityID].moveDirOrDriftXOrLaunchPitch = (rngBits & 0xf) + 8;
                this->entityArray[entityID].launchSpeedOrDriftPeriodY = (rngBits & 7) + 0x15;
            }
            else if (curveType == 4) {
                int rng = this->entityArray[entityID].rng_1;
                int driftX = rng % 20 + 16;
                this->entityArray[entityID].moveDirOrDriftXOrLaunchPitch = driftX;
                if ((char)rng < 0) {
                    this->entityArray[entityID].moveDirOrDriftXOrLaunchPitch = -driftX;
                }
                int driftY = (rng >> 8) % 20 + 16;
                this->entityArray[entityID].launchSpeedOrDriftPeriodY = driftY;
                if ((rng & 0x8000) != 0) {
                    this->entityArray[entityID].launchSpeedOrDriftPeriodY = -driftY;
                }
                return;
            }
            else if (curveType == 5) {
                this->entityArray[entityID].launchSpeedOrDriftPeriodY = 0;
                this->entityArray[entityID].moveDirOrDriftXOrLaunchPitch = this->entityArray[entityID].rng_1 & 7;
                this->entityArray[entityID].wanderCountdownOrPitchDegrees
                    = (this->entityArray[entityID].rng_1 >> 8) & 0x3f;
                return;
            }
            else if (curveType == 6) {
                uint losDistance = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Entities::EntityState_Func::computeLineOfSightDistance, this)(
                    x, y, height, targetX, targetY, targetZ, 1);
                this->entityArray[entityID].lineOfSightDistanceInit = losDistance;
                this->entityArray[entityID].lineOfSightDistance = losDistance;
                this->entityArray[entityID].losClearanceStepsLeft = (short)this->lineOfSightClearanceSteps;
                if ((short)losDistance > 150) {
                    this->entityArray[entityID].launchSpeedOrDriftPeriodY = 125;
                }
                this->entityArray[entityID].moveDirOrDriftXOrLaunchPitch
                    = MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::computeLaunchAngle, this)(
                        (short)this->entityArray[entityID].entityType,
                        (double)this->entityArray[entityID].launchSpeedOrDriftPeriodY, (short)losDistance,
                        this->entityArray[entityID].heightDifference);
            }
            else if (curveType == 7 || curveType == 10) {
                return;
            }
            else if (curveType == 8) {
                short shooterID = this->entityArray[entityID].unitID_OR_seaGullID;
                if (shooterID == 0) {
                    this->entityArray[entityID].moveDirOrDriftXOrLaunchPitch
                        = this->entityArray[entityID].rng_1 % 60 + 8;
                    this->entityArray[entityID].launchSpeedOrDriftPeriodY
                        = (this->entityArray[entityID].rng_1 & 7) + 35;
                }
                else if (shooterID == 4) {
                    this->entityArray[entityID].moveDirOrDriftXOrLaunchPitch
                        = this->entityArray[entityID].rng_1 % 30 + 15;
                    this->entityArray[entityID].launchSpeedOrDriftPeriodY
                        = (this->entityArray[entityID].rng_1 & 7) + 15;
                    this->entityArray[entityID]._elapsedTimeOrGravityAccumulator
                        = this->entityArray[entityID]._elapsedTimeOrGravityAccumulator * 0.75;
                }
                else if (shooterID == 5) {
                    this->entityArray[entityID].moveDirOrDriftXOrLaunchPitch
                        = this->entityArray[entityID].rng_1 % 30 + 45;
                    this->entityArray[entityID].launchSpeedOrDriftPeriodY
                        = (this->entityArray[entityID].rng_1 & 7) + 35;
                }
                else {
                    this->entityArray[entityID].moveDirOrDriftXOrLaunchPitch
                        = this->entityArray[entityID].rng_1 % 35 + 20;
                    this->entityArray[entityID].launchSpeedOrDriftPeriodY
                        = (this->entityArray[entityID].rng_1 & 7) + 25;
                    this->entityArray[entityID]._elapsedTimeOrGravityAccumulator
                        = this->entityArray[entityID]._elapsedTimeOrGravityAccumulator * 0.75;
                }
            }
            else if (curveType == 9) {
                this->entityArray[entityID].moveDirOrDriftXOrLaunchPitch = 0;
            }

            if ((this->entityArray[entityID].entityType == OpenSHC::Map::Entities::ET_ARROW_AND_DEFAULT
                    || this->entityArray[entityID].entityType == OpenSHC::Map::Entities::ET_CROSSBOWARROW)
                && height + 54 < targetZ && this->entityArray[entityID].rng_1 % 10 == 5) {
                this->entityArray[entityID].impactEffectDone = 1;
            }
            int pitchDegrees = this->entityArray[entityID].moveDirOrDriftXOrLaunchPitch;
            *(float*)&this->entityArray[entityID].flightTime = 0.0f;
            int speed = this->entityArray[entityID].launchSpeedOrDriftPeriodY;
            this->entityArray[entityID].travelledDistance = 0;
            double angleRad = pitchDegrees * 3.1415926535 / 180.0;
            double speedD = speed;
            this->entityArray[entityID].vCos = (float)(cos(angleRad) * speedD);
            this->entityArray[entityID].vSin = (float)(sin(angleRad) * speedD);
            this->entityArray[entityID].pitchFrameIndex = (short)MACRO_CALL_MEMBER(
                OpenSHC::Map::Entities::EntityState_Func::angleToRotationFrameIndex, this)(pitchDegrees);
        }

    }
}
}
