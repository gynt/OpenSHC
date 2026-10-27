#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00455050
        TextureRenderCore* TextureRenderCore::Constructor_TextureRenderCore(
            int processedImageDataBufferSize, int gmAndGfxImageDataBufferSize, int unknownMemSize)
        {
            /*
              generates rendering class?
             */
            this->gmProcessedImageDataBufferSize_0x74 = processedImageDataBufferSize;
            this->gmAndGfxImageDataBufferSize_0x8c = gmAndGfxImageDataBufferSize;
            if (unknownMemSize == 0) {
                this->unknownMemSize_1_0x7c = 0;
                this->unknownMemSize_2_0x84 = 0;
            } else {
                this->unknownMemSize_2_0x84 = unknownMemSize / 2;
                this->unknownMemSize_1_0x7c = unknownMemSize;
            }
            this->allocErrorCode = 0;
            this->drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            this->flaggedSurfaceTarget = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            this->ctorZeroed128 = 0;
            this->ctorZeroed12c = 0;
            this->ctorFlag2c = 1;
            this->isZoom2 = 0;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::clearSomeMemory, this)();
            this->gmAllowRelativeAliasing = FALSE;
            this->gmProcessedImageData
                = MACRO_CALL(OpenSHC::OS_Func::_malloc)(this->gmProcessedImageDataBufferSize_0x74);
            if (this->gmProcessedImageData != (void*)0x0) {
                if (unknownMemSize == 0) {
                    this->unknownMemPtr_1_0x80 = (void*)0x0;
                    this->address2 = (void*)0x0;
                } else {
                    this->unknownMemPtr_1_0x80 = MACRO_CALL(OpenSHC::OS_Func::_malloc)(this->unknownMemSize_1_0x7c);
                    if (this->unknownMemPtr_1_0x80 == (void*)0x0) {
                        this->allocErrorCode = 2;
                        return this;
                    }
                    this->address2 = MACRO_CALL(OpenSHC::OS_Func::_malloc)(this->unknownMemSize_2_0x84);
                    if (this->address2 == (void*)0x0) {
                        this->allocErrorCode = 3;
                        return this;
                    }
                }
                this->gmAndGfxImageDataBuffer
                    = MACRO_CALL(OpenSHC::OS_Func::_malloc)(this->gmAndGfxImageDataBufferSize_0x8c);
                if (this->gmAndGfxImageDataBuffer != (void*)0x0) {
                    this->totalLoadedGfx = 0;
                    this->paletteOverridePtr = 0;
                    this->bitmapsFaces_0x94 = MACRO_CALL(OpenSHC::OS_Func::_malloc)(304128);
                    this->faceBitmapByteSize[0] = 0;
                    this->faceBitmapByteSize[1] = 0;
                    this->faceBitmapByteSize[2] = 0;
                    this->faceBitmapByteSize[3] = 0;
                    this->faceBitmapByteSize[4] = 0;
                    this->faceBitmapByteSize[5] = 0;
                    this->faceBitmapByteSize[6] = 0;
                    this->faceBitmapByteSize[7] = 0;
                    this->faceBitmapByteSize[8] = 0;
                    this->faceBitmapByteSize[9] = 0;
                    this->faceBitmapByteSize[10] = 0;
                    this->faceBitmapByteSize[0xb] = 0;
                    this->faceBitmapByteSize[0xc] = 0;
                    this->faceBitmapByteSize[0xd] = 0;
                    this->faceBitmapByteSize[0xe] = 0;
                    this->faceBitmapByteSize[0xf] = 0;
                    this->faceBitmapByteSize[0x10] = 0;
                    this->faceBitmapByteSize[0x11] = 0;
                    this->faceBitmapByteSize[0x12] = 0;
                    this->faceBitmapByteSize[0x13] = 0;
                    this->faceBitmapByteSize[20] = 0;
                    this->faceBitmapByteSize[21] = 0;
                    this->faceBitmapByteSize[22] = 0;
                    this->faceBitmapByteSize[23] = 0;
                    this->faceBitmapByteSize[24] = 0;
                    this->faceBitmapByteSize[25] = 0;
                    this->faceBitmapByteSize[26] = 0;
                    this->faceBitmapByteSize[27] = 0;
                    this->ctorZeroed108 = 0;
                    this->ctorZeroed10c = 0;
                    this->ctorZeroed110 = 0;
                    this->ctorZeroed114 = 0;
                    this->ctorZeroed118 = 0;
                    this->ctorZeroed11c = 0;
                    this->ctorZeroed120 = 0;
                    this->ctorZeroed124 = 0;
                    return this;
                }
            }
            this->allocErrorCode = 1;
            return this;
        }

    }
}
}
