#include "../EntityState.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

#include "math.h"
#include <stdlib.h>

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // Works on `this` (ebx = ecx at 0x40690B). All seagull fields are signed shorts (movsx / test ax, ax; jl/jg).
        // Dive chance is a signed remainder (cdq; idiv 0x1F4 at 0x4069CE) of randomNumber ^ rng_1 ^ currentNumber2.
        // In the X-major drift step with a non-positive error the original adds the ENTITY's stepX (mov cx, [edi+0x74]
        // at 0x406F3C, edi = &entityArray[entityID]) instead of lineStepDirX; kept as in the original.
        // FUNCTION: STRONGHOLDCRUSADER 0x00406900
        void EntityState::processSeaGulls(int seagullID)
        {
            int entityID = this->seagullArray[seagullID].entityID;
            if (this->seagullArray[seagullID].diveCountdown != 0) {
                this->seagullArray[seagullID].diveCountdown--;
                if (this->seagullArray[seagullID].diveCountdown != 0) {
                    return;
                }
                this->entityArray[entityID].targetX = this->entityArray[entityID].microX;
                this->entityArray[entityID].targetY = this->entityArray[entityID].microY;
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    this->entityArray[entityID].xPosition, this->entityArray[entityID].yPosition,
                    OpenSHC::DE::SHCDE::FX_GULL_SURFACE);
            }
            if ((abs(this->entityArray[entityID].microX - this->entityArray[entityID].targetX) < 3)
                && (abs(this->entityArray[entityID].microY - this->entityArray[entityID].targetY) < 3)) {
                if (((this->seagullArray[seagullID].randomNumber ^ this->entityArray[entityID].rng_1
                         ^ SEC_RNG::instance.currentNumber2)
                        % 500)
                    == 0x7b) {
                    int diveY = this->entityArray[entityID].stepY + this->entityArray[entityID].microY;
                    int diveX = this->entityArray[entityID].stepX + this->entityArray[entityID].microX;
                    int diveTileY = diveY / 8;
                    int diveTileX = diveX / 8;
                    if (MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                            DAT_ViewportRenderState::ptr)(diveTileX, diveTileY)) {
                        int tileY = this->entityArray[entityID].microY / 8;
                        int tileX = this->entityArray[entityID].microX / 8;
                        if (MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                                DAT_ViewportRenderState::ptr)(tileX, tileY)
                            && ((DAT_TileMapState::instance.LogicLayer
                                        [DAT_ViewportRenderState::instance.translationMatrix[diveTileY].addXgetTile
                                            + diveTileX]
                                    & 1)
                                != 0)
                            && ((DAT_TileMapState::instance.LogicLayer
                                        [DAT_ViewportRenderState::instance.translationMatrix[tileY].addXgetTile + tileX]
                                    & 1)
                                != 0)) {
                            this->seagullArray[seagullID].diveCountdown = 0xa0;
                            MACRO_CALL_MEMBER(EntityState_Func::setProjectileTargetPosition, this)(entityID,
                                this->entityArray[entityID].microX, this->entityArray[entityID].microY, 0xfa, diveX,
                                diveY, 0);
                            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation,
                                DAT_SFXState::ptr)(this->entityArray[entityID].xPosition,
                                this->entityArray[entityID].yPosition, OpenSHC::DE::SHCDE::FX_GULL);
                            return;
                        }
                    }
                }
                double angleRad = (this->seagullArray[seagullID].angle - 180) * 3.1415926535 / 180.0;
                this->seagullArray[seagullID].angle
                    = this->seagullArray[seagullID].circleDirection * 20 + this->seagullArray[seagullID].angle;
                if (this->seagullArray[seagullID].angle >= 360) {
                    MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber1, SEC_RNG::ptr)();
                    if (SEC_RNG::instance.currentNumber1 % 5 == 1) {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            this->entityArray[entityID].xPosition, this->entityArray[entityID].yPosition,
                            OpenSHC::DE::SHCDE::FX_GULL);
                    }
                    this->seagullArray[seagullID].angle -= 360;
                    if (this->seagullArray[seagullID].circlePhase < 0) {
                        this->seagullArray[seagullID].circleRadius++;
                    }
                    else if (this->seagullArray[seagullID].circlePhase > 0) {
                        this->seagullArray[seagullID].circleRadius--;
                    }
                    if (this->seagullArray[seagullID].circleRadius < 0x18) {
                        this->seagullArray[seagullID].circleRadius = 0x18;
                    }
                    if (this->seagullArray[seagullID].circleRadius > 0x50) {
                        this->seagullArray[seagullID].circleRadius = 0x50;
                    }
                    this->seagullArray[seagullID].circlePhase++;
                    if (this->seagullArray[seagullID].circlePhase >= 20) {
                        this->seagullArray[seagullID].circlePhase = -20;
                    }
                }
                if (this->seagullArray[seagullID].angle < 0) {
                    this->seagullArray[seagullID].angle += 360;
                    if (this->seagullArray[seagullID].circlePhase < 0) {
                        this->seagullArray[seagullID].circleRadius++;
                    }
                    else if (this->seagullArray[seagullID].circlePhase > 0) {
                        this->seagullArray[seagullID].circleRadius--;
                    }
                    if (this->seagullArray[seagullID].circleRadius < 0x18) {
                        this->seagullArray[seagullID].circleRadius = 0x18;
                    }
                    if (this->seagullArray[seagullID].circleRadius > 0x50) {
                        this->seagullArray[seagullID].circleRadius = 0x50;
                    }
                    this->seagullArray[seagullID].circlePhase++;
                    if (this->seagullArray[seagullID].circlePhase >= 20) {
                        this->seagullArray[seagullID].circlePhase = -20;
                    }
                }
                double radius = this->seagullArray[seagullID].circleRadius;
                int offsetX = (int)(sin(angleRad) * radius);
                int offsetY = (int)(cos(angleRad) * radius);
                double angle2Rad = (this->seagullArray[seagullID].angle_2 - 180) * 3.1415926535 / 180.0;
                this->seagullArray[seagullID].angle_2
                    = this->seagullArray[seagullID].angle2Step + this->seagullArray[seagullID].angle_2;
                if (this->seagullArray[seagullID].angle_2 >= 360) {
                    this->seagullArray[seagullID].angle_2 -= 360;
                }
                if (this->seagullArray[seagullID].angle_2 < 0) {
                    this->seagullArray[seagullID].angle_2 += 360;
                }
                double orbitRadius = this->seagullArray[seagullID].orbitCenterRadius;
                this->seagullArray[seagullID].x_2
                    = (int)(sin(angle2Rad) * orbitRadius) + this->seagullArray[seagullID].x;
                this->seagullArray[seagullID].y_2
                    = (int)(cos(angle2Rad) * orbitRadius) + this->seagullArray[seagullID].y;
                MACRO_CALL_MEMBER(EntityState_Func::setProjectileTargetPosition, this)(entityID,
                    this->entityArray[entityID].microX, this->entityArray[entityID].microY,
                    this->entityArray[entityID].height, this->seagullArray[seagullID].x_2 + offsetX,
                    this->seagullArray[seagullID].y_2 + offsetY, 0xfa);
            }
            if (((abs(this->seagullArray[seagullID].x - this->seagullArray[seagullID].x_3) < 2)
                    && (abs(this->seagullArray[seagullID].y - this->seagullArray[seagullID].y_3) < 2))
                || (this->seagullArray[seagullID].lineStepsLeft <= 0)) {
                if (this->seagullArray[seagullID].retargetWaitCountdown > 0) {
                    this->seagullArray[seagullID].retargetWaitCountdown--;
                    return;
                }
                this->seagullArray[seagullID].retargetWaitCountdown = SEC_RNG::instance.currentNumber2 % 400 + 400;
                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::findFurthestSeaTile,
                    DAT_PathFindingState::ptr)((SEC_RNG::instance.currentNumber2 >> 4) % 200 + 400,
                    this->seagullArray[seagullID].x / 8, this->seagullArray[seagullID].y / 8);
                this->seagullArray[seagullID].x_3 = DAT_PathFindingState::instance.ALG_ResultX * 8;
                this->seagullArray[seagullID].y_3 = DAT_PathFindingState::instance.ALG_ResultY * 8;
                MACRO_CALL_MEMBER(EntityState_Func::initializeSeagullMovementVector, this)(seagullID,
                    this->seagullArray[seagullID].x, this->seagullArray[seagullID].y, this->seagullArray[seagullID].x_3,
                    this->seagullArray[seagullID].y_3);
                this->seagullArray[seagullID].lineStepDelay = 10;
                return;
            }
            this->seagullArray[seagullID].lineStepDelay--;
            if (this->seagullArray[seagullID].lineStepDelay > 0) {
                return;
            }
            short lineStepMode = this->seagullArray[seagullID].lineStepMode;
            this->seagullArray[seagullID].lineStepDelay = 10;
            this->seagullArray[seagullID].lineStepsLeft--;
            if (lineStepMode == 0) {
                return;
            }
            if (lineStepMode == 2) {
                this->seagullArray[seagullID].x += this->seagullArray[seagullID].lineStepDirX;
            }
            else if (lineStepMode == 1) {
                this->seagullArray[seagullID].y += this->seagullArray[seagullID].lineStepDirY;
            }
            else if (lineStepMode == 4) {
                short lineStepError = this->seagullArray[seagullID].lineStepError;
                if (lineStepError > 0) {
                    this->seagullArray[seagullID].x += this->seagullArray[seagullID].lineStepDirX;
                    this->seagullArray[seagullID].y += this->seagullArray[seagullID].lineStepDirY;
                    this->seagullArray[seagullID].lineStepError
                        = this->seagullArray[seagullID].lineStepIncMajor + lineStepError;
                }
                else {
                    this->seagullArray[seagullID].x += this->entityArray[entityID].stepX;
                    this->seagullArray[seagullID].lineStepError
                        = this->seagullArray[seagullID].lineStepIncMinor + lineStepError;
                }
            }
            else if (lineStepMode == 3) {
                short lineStepError = this->seagullArray[seagullID].lineStepError;
                this->seagullArray[seagullID].y += this->seagullArray[seagullID].lineStepDirY;
                if (lineStepError > 0) {
                    this->seagullArray[seagullID].x += this->seagullArray[seagullID].lineStepDirX;
                    this->seagullArray[seagullID].lineStepError
                        = this->seagullArray[seagullID].lineStepIncMajor + lineStepError;
                }
                else {
                    this->seagullArray[seagullID].lineStepError
                        = this->seagullArray[seagullID].lineStepIncMinor + lineStepError;
                }
            }
        }

    }
}
}
