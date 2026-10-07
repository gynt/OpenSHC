#include "../../../Map.func.hpp"
#include "../EntityState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x00403900
        void EntityState::removeEntityFromTileLinkedList(int param_1)
        {
            int iVar1;
            int iVar2;
            int iVar3;
            int iVar4;
            int iVar5;
            iVar4 = this->entityArray[param_1].tile;
            iVar3 = (int)DAT_TileMapState::instance.EntityLayer[iVar4];
            iVar5 = 0;
            if (iVar3 == param_1) {
                DAT_TileMapState::instance.EntityLayer[iVar4] = this->entityArray[param_1].nextEntityOnThisTileByID;
                this->entityArray[param_1].nextEntityOnThisTileByID = 0;
            }
            iVar4 = iVar3;
            if (iVar3) {
                while ((iVar1 = iVar3, iVar5 = iVar5 + 1, iVar3 = iVar4,
                    iVar5 < 100
                        && (iVar2 = (int)this->entityArray[iVar1].nextEntityOnThisTileByID, iVar3 = iVar1,
                            iVar2 != param_1))) {
                    iVar3 = iVar2;
                    iVar4 = iVar1;
                    if (!iVar2) {}
                }
            }
            this->entityArray[iVar3].nextEntityOnThisTileByID = this->entityArray[param_1].nextEntityOnThisTileByID;
            this->entityArray[param_1].nextEntityOnThisTileByID = 0;
        }

    }
}
}
