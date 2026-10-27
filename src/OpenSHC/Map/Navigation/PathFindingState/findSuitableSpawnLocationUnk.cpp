#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState/LinkageNeighbourAsm.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00497B80
        undefined4 PathFindingState::findPathWithBudget(
            int x, int y, int x2, int y2, int param_5, int param_6)
        {
            if (399 < (uint)x || 399 < (uint)y
                || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] == '\0') {
                return (undefined4)(0);
            }
            if (x2 != -1
                && (399 < (uint)x2 || 399 < (uint)y2
                    || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y2 * 400 + x2] == '\0')
                && 500 < param_5) {
                param_5 = 500;
            }
            if (param_6 == 0) {
                this->searchGeneration = this->searchGeneration + 1;
                if (32000 < this->searchGeneration) {
                    this->searchGeneration = 1;
                    MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                        0x27420, '\0', (void*)((int)(DAT_TileMapState::instance.SearchGenerationLayer)));
                }
                this->searchQueue.writeIndex = 1;
                this->searchQueue.readIndex = 0;
                this->searchQueue.dequeuedCount = 0;
            }
            /*
              The whole dequeue loop is handwritten assembly in the original, the same stream as in
              findLinkageBasedPathOrWalkRadius (0x004978A7) minus the distance cap; this is the variant
              that only enters a neighbour whose OccupancyLayer byte is zero. It reaches the layers and
              the queue through these locals; see LinkageNeighbourAsm.hpp.
             */
            int _writeIndex = this->searchQueue.writeIndex;
            int _readIndex = this->searchQueue.readIndex;
            int _dequeued = this->searchQueue.dequeuedCount;
            int _target;
            int* _tilesQueue = this->searchQueue.tilesQueue;
            short* _yQueue = this->searchQueue.yQueue;
            this->searchQueue.yQueue[0] = (short)y;
            _tilesQueue[0] = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
            DAT_TileMapState::instance.SearchDistanceLayer[_tilesQueue[0]] = 1;
            DAT_TileMapState::instance.SearchGenerationLayer[_tilesQueue[0]] = (short)this->searchGeneration;
            int _curGen = (ushort)this->searchGeneration;
            short* _certainPath = DAT_TileMapState::instance.SearchDistanceLayer;
            uchar* _occupancy = DAT_TileMapState::instance.OccupancyLayer;
            short* _walkLayer = DAT_TileMapState::instance.SearchGenerationLayer;
            uchar* _linkage = DAT_TileMapState::instance.PathLinkageLayer;
            int* _dirMatrix = &DAT_TileMapState::instance.directionTranslationMatrix[0][0];
            int _cCardinalDistance = 0;
            int _result = 0;
            int _tile;
            int _cY;

            if (x2 == -1) {
                _target = 0;
            } else {
                _target = DAT_ViewportRenderState::instance.translationMatrix[y2].addXgetTile + x2;
            }

            // clang-format off
            __asm {
            budget_loop:
                mov ecx, _readIndex
                cmp ecx, _writeIndex
                je budget_done
                mov eax, _dequeued
                cmp eax, param_5
                jge budget_done
                add _dequeued, 1
                mov esi, _tilesQueue
                mov edx, dword ptr [esi + ecx*4]
                mov _tile, edx
                cmp edx, _target
                je budget_found
                mov esi, _certainPath
                mov bx, word ptr [esi + edx*2]
                add bx, 1
                mov word ptr _cCardinalDistance, bx
                mov esi, _yQueue
                mov eax, 0
                mov ax, word ptr [esi + ecx*2]
                mov _cY, eax
                mov edi, _walkLayer
                mov edx, _tile
                mov esi, _linkage
                mov bl, byte ptr [esi + edx]
            }
            MACRO_LINKAGE_PUSH_FREE(1, w, _writeIndex, -2, -1, 0x40, MACRO_ASM_SAME, MACRO_ASM_DEC, MACRO_ASM_SAME)
            MACRO_LINKAGE_PUSH_FREE(1, e, _writeIndex, +2, +1, 0x04, MACRO_ASM_SAME, MACRO_ASM_INC, MACRO_ASM_SAME)
            __asm mov eax, _cY
            __asm shl eax, 3
            __asm mov esi, _dirMatrix
            __asm add edx, dword ptr [esi + eax*4]
            MACRO_LINKAGE_PUSH_FREE(1, n, _writeIndex, 0, 0, 0x01, MACRO_ASM_SAME, MACRO_ASM_SAME, MACRO_ASM_DEC)
            MACRO_LINKAGE_PUSH_FREE(1, nw, _writeIndex, -2, -1, 0x80, MACRO_ASM_DIAGONAL, MACRO_ASM_DEC, MACRO_ASM_DEC)
            MACRO_LINKAGE_PUSH_FREE(1, ne, _writeIndex, +2, +1, 0x02, MACRO_ASM_DIAGONAL, MACRO_ASM_INC, MACRO_ASM_DEC)
            __asm mov edx, _tile
            __asm mov eax, _cY
            __asm shl eax, 3
            __asm add eax, 4
            __asm mov esi, _dirMatrix
            __asm add edx, dword ptr [esi + eax*4]
            MACRO_LINKAGE_PUSH_FREE(1, s, _writeIndex, 0, 0, 0x10, MACRO_ASM_SAME, MACRO_ASM_SAME, MACRO_ASM_INC)
            MACRO_LINKAGE_PUSH_FREE(1, sw, _writeIndex, -2, -1, 0x20, MACRO_ASM_DIAGONAL, MACRO_ASM_DEC, MACRO_ASM_INC)
            MACRO_LINKAGE_PUSH_FREE(1, se, _writeIndex, +2, +1, 0x08, MACRO_ASM_DIAGONAL, MACRO_ASM_INC, MACRO_ASM_INC)
            __asm {
                add _readIndex, 1
                jmp budget_loop
            budget_found:
                mov _result, 1
            budget_done:
            }
            // clang-format on

            this->searchQueue.writeIndex = _writeIndex;
            this->searchQueue.readIndex = _readIndex;
            this->searchQueue.dequeuedCount = _dequeued;
            return (undefined4)(_result);
        }

    }
}
}
