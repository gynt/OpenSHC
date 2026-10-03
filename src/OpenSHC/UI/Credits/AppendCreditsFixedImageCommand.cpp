#include "../Credits.func.hpp"

#include "OpenSHC/Globals/DAT_ARRAY_00eb9b68.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_UnknownBinkCount.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004DAB00
    void Credits::AppendCreditsFixedImageCommand(int param_1, int param_2, int param_3)
    {
        int iVar1;
        int iVar2;
        if (DAT_UnknownBinkCount::instance < 0x120) {
            DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].field0_0x0 = 0x15;
            DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].soundStream = param_1;
            DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].x = param_2;
            DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].y = param_3;
            iVar1 = DAT_TextureRenderCoreObject::instance.loadedGfxArray[param_1].width;
            iVar2 = DAT_TextureRenderCoreObject::instance.loadedGfxArray[param_1].height;
            DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].field13_0x28 = 7;
            DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].field_0x1c = 0;
            DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].field4_0x10 = iVar1;
            DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].field5_0x14 = iVar2;
            DAT_UnknownBinkCount::instance = DAT_UnknownBinkCount::instance + 1;
        }
        return;
    }

}
}
