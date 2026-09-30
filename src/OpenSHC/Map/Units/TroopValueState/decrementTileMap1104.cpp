#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0051D5D0
        void TroopValueState::decrementTileMap1104()
        {
            char cVar1;
            int iVar2;
            iVar2 = 0;
            do {
                cVar1 = *(char*)(this->attackInfo.tilemapOffset + 0x1ecef88 + iVar2);
                if (cVar1 != '\0') {
                    *(char*)(this->attackInfo.tilemapOffset + 0x1ecef88 + iVar2) = cVar1 + -1;
                }
                cVar1 = *(char*)(this->attackInfo.tilemapOffset + 0x1ecef89 + iVar2);
                if (cVar1 != '\0') {
                    *(char*)(this->attackInfo.tilemapOffset + 0x1ecef89 + iVar2) = cVar1 + -1;
                }
                cVar1 = *(char*)(this->attackInfo.tilemapOffset + 0x1ecef8a + iVar2);
                if (cVar1 != '\0') {
                    *(char*)(this->attackInfo.tilemapOffset + 0x1ecef8a + iVar2) = cVar1 + -1;
                }
                cVar1 = *(char*)(this->attackInfo.tilemapOffset + 0x1ecef8b + iVar2);
                if (cVar1 != '\0') {
                    *(char*)(this->attackInfo.tilemapOffset + 0x1ecef8b + iVar2) = cVar1 + -1;
                }
                cVar1 = *(char*)(this->attackInfo.tilemapOffset + 0x1ecef8c + iVar2);
                if (cVar1 != '\0') {
                    *(char*)(this->attackInfo.tilemapOffset + 0x1ecef8c + iVar2) = cVar1 + -1;
                }
                iVar2 = iVar2 + 5;
            } while (iVar2 < 200);
            if (this->attackInfo.tilemapOffset < 80200) {
                this->attackInfo.tilemapOffset = this->attackInfo.tilemapOffset + 200;
            }
            this->attackInfo.tilemapOffset = 0;
        }

    }
}
}
