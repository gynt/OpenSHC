#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00534520
        void UnitsState::writeSixToTileMap1104InAllDirections(int unitID, undefined4 six)
        {
            /*
                The original is a hand-written asm block. Equivalent C++:

                uchar* row = DAT_TileMapState::instance.SEC_TileMap1104 + this->units[unitID].tile;
                int* directionRow = (int*)((uchar*)DAT_TileMapState::instance.ptr_MovementDirectionTranslationMatrix
                                           + this->units[unitID].y * 0x20);
                row[1] = row[-1] = row[0] = (uchar)six;
                row[directionRow[0] - 1] = row[directionRow[0] + 1] = row[directionRow[0]] = (uchar)six;
                row[directionRow[4] - 1] = row[directionRow[4] + 1] = row[directionRow[4]] = (uchar)six;
            */
            uchar* tileMap1104 = DAT_TileMapState::instance.SEC_TileMap1104;
            int tile = this->units[unitID].tile;
            int y = this->units[unitID].y;
            __asm {
                mov ebx, six
                mov esi, tileMap1104
                mov eax, tile
                add esi, eax
                push esi
                mov edx, DAT_TileMapState::instance.ptr_MovementDirectionTranslationMatrix
                mov eax, y
                shl eax, 5
                add edx, eax
                mov byte ptr [esi + 1], bl
                mov byte ptr [esi - 1], bl
                mov byte ptr [esi], bl
                mov ecx, dword ptr [edx]
                add esi, ecx
                mov byte ptr [esi - 1], bl
                mov byte ptr [esi + 1], bl
                mov byte ptr [esi], bl
                mov ecx, dword ptr [edx + 0x10]
                pop esi
                add esi, ecx
                mov byte ptr [esi - 1], bl
                mov byte ptr [esi + 1], bl
                mov byte ptr [esi], bl
            }
        }

    }
}
}
