#include "../PencilRenderCore.func.hpp"

#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x00468F70
        void PencilRenderCore::drawPixelPattern4x4(int drawX, int drawY)
        {
            int _drawPtr = (int)DAT_PencilRenderCore::instance.surfacePtr + drawX * 2
                + (uint)drawY * DAT_PencilRenderCore::instance.horizontalByteSize;
            dword _rowOffset = 0;
            dword _horizontalByteSize = DAT_PencilRenderCore::instance.horizontalByteSize;
            undefined4 _rowPixels = 0xffff7bcf;
            undefined4 _rightPixels = 0x39c70000;
            *(undefined4*)(_drawPtr + _rowOffset) = _rowPixels;
            *(undefined4*)(_drawPtr + _rowOffset + 4) = _rightPixels;
            _rowOffset = _rowOffset + _horizontalByteSize;
            _rowPixels = 0x7bcf7bcf;
            *(undefined4*)(_drawPtr + _rowOffset) = _rowPixels;
            *(undefined4*)(_drawPtr + _rowOffset + 4) = _rightPixels;
            _rowOffset = _rowOffset + _horizontalByteSize;
            _rowPixels = 0x39c739c7;
            *(undefined4*)(_drawPtr + _rowOffset) = _rowPixels;
            *(undefined4*)(_drawPtr + _rowOffset + 4) = _rightPixels;
            _rowOffset = _rowOffset + _horizontalByteSize;
            _rowPixels = 0;
            *(undefined4*)(_drawPtr + _rowOffset) = _rowPixels;
            *(undefined4*)(_drawPtr + _rowOffset + 4) = _rowPixels;
        }

    }
}
}
