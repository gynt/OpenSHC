#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00534490
        void UnitsState::stampOccupancyFlagOnSurroundingTiles(int unitID)
        {
            /*
                The original is a hand-written asm block. Equivalent C++:

                uchar* row = DAT_TileMapState::instance.OccupancyLayer + this->units[unitID].tile;
                int* directionRow = (int*)((uchar*)DAT_TileMapState::instance.ptr_MovementDirectionTranslationMatrix
                                           + this->units[unitID].y * 0x20);
                uchar value = this->units[unitID].ownerBitMask;
                row[1] |= value; row[-1] |= value; row[0] |= value;
                row[directionRow[0] - 1] |= value; row[directionRow[0] + 1] |= value; row[directionRow[0]] |= value;
                row[directionRow[4] - 1] |= value; row[directionRow[4] + 1] |= value; row[directionRow[4]] |= value;

                The ORs are word-sized with the high byte 0 (the value is zero-extended), so the byte after each
                tile is read and written back unchanged.
            */
            uchar* occupancyLayer = DAT_TileMapState::instance.OccupancyLayer;
            int tile = this->units[unitID].tile;
            int y = this->units[unitID].y;
            int value = this->units[unitID].ownerBitMask;
            __asm {
                mov ebx, value
                mov esi, occupancyLayer
                mov eax, tile
                add esi, eax
                push esi
                mov edx, DAT_TileMapState::instance.ptr_MovementDirectionTranslationMatrix
                mov eax, y
                shl eax, 5
                add edx, eax
                or word ptr [esi + 1], bx
                or word ptr [esi - 1], bx
                or word ptr [esi], bx
                mov ecx, dword ptr [edx]
                add esi, ecx
                or word ptr [esi - 1], bx
                or word ptr [esi + 1], bx
                or word ptr [esi], bx
                mov ecx, dword ptr [edx + 0x10]
                pop esi
                add esi, ecx
                or word ptr [esi - 1], bx
                or word ptr [esi + 1], bx
                or word ptr [esi], bx
            }
        }

    }
}
}
