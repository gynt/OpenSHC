#include "../../../Map.func.hpp"
#include "../DirectionAlgorithmState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        // FUNCTION: STRONGHOLDCRUSADER 0x0046CAA0
        void DirectionAlgorithmState::somethingWithProjectileDistance(int x, int y, int targetX, int targetY)
        {
            int iVar1;
            if (targetX < x) {
                this->distanceX = x - targetX;
            } else {
                this->distanceX = targetX - x;
            }
            if (targetY < y) {
                this->distanceY = y - targetY;
            } else {
                this->distanceY = targetY - y;
            }
            if (this->distanceX < this->distanceY) {
                if (this->distanceY == 0) {
                    iVar1 = 100;
                } else {
                    iVar1 = (this->distanceX * 100) / this->distanceY;
                }
            } else if (this->distanceX == 0) {
                iVar1 = 100;
            } else {
                iVar1 = (this->distanceY * 100) / this->distanceX;
            }
            if (this->distanceX < this->distanceY) {
                if (targetY < y) {
                    if (targetX < x) {
                        if (iVar1 < 0x1a) {
                            this->orientation = 60;
                            goto LAB_0046cc5d;
                        }
                        if (iVar1 < 0x4b) {
                            this->orientation = 75;
                            goto LAB_0046cc5d;
                        }
                        goto LAB_0046cb3f;
                    }
                    if (iVar1 < 0x1a) {
                        this->orientation = 60;
                        goto LAB_0046cc5d;
                    }
                    if (iVar1 < 0x4b) {
                        this->orientation = 61;
                        goto LAB_0046cc5d;
                    }
                    goto LAB_0046cc06;
                }
                if (x <= targetX) {
                    if (iVar1 < 0x1a) {
                        this->orientation = 0x44;
                        goto LAB_0046cc5d;
                    }
                    if (iVar1 < 0x4b) {
                        this->orientation = 0x43;
                        goto LAB_0046cc5d;
                    }
                    goto LAB_0046cc56;
                }
                if (iVar1 < 0x1a) {
                    this->orientation = 0x44;
                    goto LAB_0046cc5d;
                }
                if (iVar1 < 0x4b) {
                    this->orientation = 0x45;
                    goto LAB_0046cc5d;
                }
            } else {
                if (x <= targetX) {
                    if (y <= targetY) {
                        if (iVar1 < 0x1a) {
                            this->orientation = 0x40;
                            goto LAB_0046cc5d;
                        }
                        if (iVar1 < 0x4b) {
                            this->orientation = 0x41;
                            goto LAB_0046cc5d;
                        }
                    LAB_0046cc56:
                        this->orientation = 0x42;
                        goto LAB_0046cc5d;
                    }
                    if (iVar1 < 0x1a) {
                        this->orientation = 0x40;
                        goto LAB_0046cc5d;
                    }
                    if (iVar1 < 0x4b) {
                        this->orientation = 0x3f;
                        goto LAB_0046cc5d;
                    }
                LAB_0046cc06:
                    this->orientation = 0x3e;
                    goto LAB_0046cc5d;
                }
                if (targetY < y) {
                    if (iVar1 < 0x1a) {
                        this->orientation = 0x48;
                        goto LAB_0046cc5d;
                    }
                    if (iVar1 < 0x4b) {
                        this->orientation = 0x49;
                        goto LAB_0046cc5d;
                    }
                LAB_0046cb3f:
                    this->orientation = 74;
                    goto LAB_0046cc5d;
                }
                if (iVar1 < 0x1a) {
                    this->orientation = 0x48;
                    goto LAB_0046cc5d;
                }
                if (iVar1 < 0x4b) {
                    this->orientation = 0x47;
                    goto LAB_0046cc5d;
                }
            }
            this->orientation = 0x46;
        LAB_0046cc5d:
            if (this->distanceY + this->distanceX < 1) {
                this->orientation = 0x4c;
            }
        }

    }
}
}
