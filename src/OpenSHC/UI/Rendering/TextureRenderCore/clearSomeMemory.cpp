#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"

#include "OpenSHC/Globals/DAT_BlendFilterArrays.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/gmRepeatRunFillJumpTable.hpp"
#include "OpenSHC/Globals/tgxRepeatPixelRunJumpTable.hpp"
#include "OpenSHC/Globals/tgxPixelStreamRunJumpTable.hpp"
#include "OpenSHC/Globals/PTR_ARRAY_GmRunCopyJumpTable.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x0044CC30
        void TextureRenderCore::clearSomeMemory()
        {
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                0x80, '\0', (void*)((int)(tgxRepeatPixelRunJumpTable::instance)));
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                0x80, '\0', (void*)((int)(tgxPixelStreamRunJumpTable::instance)));
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                0x80, '\0', (void*)((int)(gmRepeatRunFillJumpTable::instance)));
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                0x80, '\0', (void*)((int)(PTR_ARRAY_GmRunCopyJumpTable::instance)));
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                16896, '\0', (void*)((int)(DAT_BlendFilterArrays::instance)));
        }

    }
}
}
