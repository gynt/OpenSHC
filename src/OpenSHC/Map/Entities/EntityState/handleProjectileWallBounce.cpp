#include "../EntityState.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

#include "math.h"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x00403FF0
        void EntityState::handleProjectileWallBounce(int entityID)
        {
            int microY = this->entityArray[entityID].microY;
            int microX = this->entityArray[entityID].microX;
            int subTileX = microX & 7;
            int newTargetX = 0;
            int newTargetY = 0;
            int subTileY = microY & 7;
            int wallFlags = MACRO_CALL_MEMBER(
                OpenSHC::Map::TileMapState_Func::setBitFlagBasedOnWallTowerGatehouseOrKeep, DAT_TileMapState::ptr)(
                microX / 8, microY / 8);
            switch (this->entityArray[entityID].orientation) {
            case 0x3c:
            case 0x40:
            case 0x44:
            case 0x48:
            bounceBack:
                newTargetY = this->entityArray[entityID].y_2;
                newTargetX = this->entityArray[entityID].x_2;
                break;
            case 0x3d:
                subTileY = 7 - subTileY;
                if (subTileX == subTileY) {
                    switch (wallFlags & 0xa) {
                    case 0:
                    case 8:
                        subTileY = 100;
                        break;
                    case 2:
                        subTileX = 100;
                        break;
                    case 0xa:
                        goto bounceBack;
                    }
                }
                goto mirror;
            case 0x3e:
                subTileY = 7 - subTileY;
                if (subTileX == subTileY) {
                    switch (wallFlags & 0xa) {
                    case 0:
                    case 8:
                        subTileY = 100;
                        break;
                    case 2:
                        subTileX = 100;
                        break;
                    case 0xa:
                        goto bounceBack;
                    }
                }
                goto mirror;
            case 0x3f:
                subTileY = 7 - subTileY;
                if (subTileX == subTileY) {
                    switch (wallFlags & 0xa) {
                    case 0:
                    case 2:
                        subTileX = 100;
                        break;
                    case 8:
                        subTileY = 100;
                        break;
                    case 0xa:
                        goto bounceBack;
                    }
                }
                goto mirror;
            case 0x41:
                if (subTileX == subTileY) {
                    switch (wallFlags & 0x82) {
                    case 0:
                    case 2:
                        subTileY = 100;
                        break;
                    case 0x80:
                        subTileX = 100;
                        break;
                    case 0x82:
                        goto bounceBack;
                    }
                }
                goto mirror;
            case 0x42:
                if (subTileX == subTileY) {
                    switch (wallFlags & 0x82) {
                    case 0:
                    case 2:
                        subTileY = 100;
                        break;
                    case 0x80:
                        subTileX = 100;
                        break;
                    case 0x82:
                        goto bounceBack;
                    }
                }
                goto mirror;
            case 0x43:
                if (subTileX == subTileY) {
                    switch (wallFlags & 0x82) {
                    case 0:
                    case 0x80:
                        subTileX = 100;
                        break;
                    case 2:
                        subTileY = 100;
                        break;
                    case 0x82:
                        goto bounceBack;
                    }
                }
                goto mirror;
            case 0x45:
                subTileX = 7 - subTileX;
                if (subTileX == subTileY) {
                    switch (wallFlags & 0xa0) {
                    case 0:
                    case 0x80:
                        subTileY = 100;
                        break;
                    case 0x20:
                        subTileX = 100;
                        break;
                    case 0xa0:
                        goto bounceBack;
                    }
                }
                goto mirror;
            case 0x46:
                subTileX = 7 - subTileX;
                if (subTileX == subTileY) {
                    switch (wallFlags & 0xa0) {
                    case 0:
                    case 0x80:
                        subTileY = 100;
                        break;
                    case 0x20:
                        subTileX = 100;
                        break;
                    case 0xa0:
                        goto bounceBack;
                    }
                }
                goto mirror;
            case 0x47:
                subTileX = 7 - subTileX;
                if (subTileX == subTileY) {
                    switch (wallFlags & 0xa0) {
                    case 0:
                    case 0x20:
                        subTileX = 100;
                        break;
                    case 0x80:
                        subTileY = 100;
                        break;
                    case 0xa0:
                        goto bounceBack;
                    }
                }
                goto mirror;
            case 0x49:
                subTileX = 7 - subTileX;
                subTileY = 7 - subTileY;
                if (subTileX == subTileY) {
                    switch (wallFlags & 0x28) {
                    case 0:
                    case 0x20:
                        subTileX = 100;
                        break;
                    case 8:
                        subTileY = 100;
                        break;
                    case 0x28:
                        goto bounceBack;
                    }
                }
                goto mirror;
            case 0x4a:
                subTileX = 7 - subTileX;
                subTileY = 7 - subTileY;
                if (subTileX == subTileY) {
                    switch (wallFlags & 0x28) {
                    case 0:
                    case 8:
                        subTileY = 100;
                        break;
                    case 0x20:
                        subTileX = 100;
                        break;
                    case 0x28:
                        goto bounceBack;
                    }
                }
                goto mirror;
            case 0x4b:
                subTileX = 7 - subTileX;
                subTileY = 7 - subTileY;
                if (subTileX == subTileY) {
                    switch (wallFlags & 0x28) {
                    case 0:
                    case 8:
                        subTileY = 100;
                        break;
                    case 0x20:
                        subTileX = 100;
                        break;
                    case 0x28:
                        goto bounceBack;
                    }
                }
            mirror:
                if (subTileX > subTileY) {
                    newTargetX = this->entityArray[entityID].microX * 2 - this->entityArray[entityID].x_2;
                    newTargetY = this->entityArray[entityID].y_2;
                }
                else {
                    newTargetY = this->entityArray[entityID].microY * 2 - this->entityArray[entityID].y_2;
                    newTargetX = this->entityArray[entityID].x_2;
                }
                break;
            }

            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::somethingWithProjectileDistance,
                DAT_DirectionAlgorithmState::ptr)(microX, microY, newTargetX, newTargetY);
            this->entityArray[entityID].orientation = DAT_DirectionAlgorithmState::instance.orientation;
            if (microY > newTargetY) {
                this->entityArray[entityID].lineDeltaY = microY - newTargetY;
            }
            else {
                this->entityArray[entityID].lineDeltaY = newTargetY - microY;
            }
            if (microX > newTargetX) {
                this->entityArray[entityID].lineDeltaX = microX - newTargetX;
            }
            else {
                this->entityArray[entityID].lineDeltaX = newTargetX - microX;
            }
            this->entityArray[entityID].lineTargetMicroX = newTargetX;
            this->entityArray[entityID].stepX = microX <= newTargetX ? 1 : -1;
            this->entityArray[entityID].lineTargetMicroY = newTargetY;
            this->entityArray[entityID].stepY = microY <= newTargetY ? 1 : -1;

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
                this->entityArray[entityID].lineStepError = incMinor - this->entityArray[entityID].lineDeltaY;
                this->entityArray[entityID].lineStepIncMajor = incMinor - this->entityArray[entityID].lineDeltaY * 2;
            }
            else if (this->entityArray[entityID].lineStepMode == 4) {
                short incMinor = this->entityArray[entityID].lineDeltaY * 2;
                this->entityArray[entityID].lineStepIncMinor = incMinor;
                this->entityArray[entityID].lineStepError = incMinor - this->entityArray[entityID].lineDeltaX;
                this->entityArray[entityID].lineStepIncMajor = incMinor - this->entityArray[entityID].lineDeltaX * 2;
            }

            short bouncePitch = (short)this->entityArray[entityID].wanderCountdownOrPitchDegrees;
            this->entityArray[entityID].moveDirOrDriftXOrLaunchPitch = bouncePitch;
            if (bouncePitch < -80) {
                this->entityArray[entityID].moveDirOrDriftXOrLaunchPitch = -80;
            }
            int pitchDegrees = this->entityArray[entityID].moveDirOrDriftXOrLaunchPitch;
            *(float*)&this->entityArray[entityID].flightTime = 0.0f;
            double angleRad = pitchDegrees * 3.1415926535 / 180.0;
            short speed = this->entityArray[entityID].launchSpeedOrDriftPeriodY / 8;
            this->entityArray[entityID].launchSpeedOrDriftPeriodY = speed;
            this->entityArray[entityID].startingHeight = this->entityArray[entityID].height;
            this->entityArray[entityID].travelledDistance = 0;
            this->entityArray[entityID].vCos = (float)(cos(angleRad) * speed);
            this->entityArray[entityID].vSin = (float)(sin(angleRad) * speed);
            this->entityArray[entityID].pitchFrameIndex = (short)MACRO_CALL_MEMBER(
                OpenSHC::Map::Entities::EntityState_Func::angleToRotationFrameIndex, this)(pitchDegrees);
            this->entityArray[entityID].gmLookupValue = 0;
            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                this->entityArray[entityID].xPosition, this->entityArray[entityID].yPosition,
                OpenSHC::DE::SHCDE::FX_ARROW_BOUNCE);
        }

    }
}
}
