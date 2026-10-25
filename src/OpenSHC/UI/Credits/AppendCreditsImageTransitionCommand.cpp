#include "../Credits.func.hpp"

#include "OpenSHC/Globals/DAT_ARRAY_00eb9b68.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_UnknownBinkCount.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004DA8D0
    void Credits::AppendCreditsImageTransitionCommand(int param_1, int param_2, int param_3, int param_4, int param_5)
    {
        int iVar1;
        int iVar2;
        CreditsRelatedStructure2* pCVar3;
        if (((DAT_UnknownBinkCount::instance < 0x120) && (-1 < param_2))
            && ((param_1 == 5 || ((param_1 == 6 || (param_1 == 7)))))) {
            DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].commandType = param_1;
            DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].soundStream = param_2;
            DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].field17_0x38 = -1;
            DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].x = param_3;
            DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].y = param_4;
            DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].field13_0x28 = param_5;
            iVar1 = DAT_TextureRenderCoreObject::instance.loadedGfxArray[param_2].width;
            iVar2 = DAT_TextureRenderCoreObject::instance.loadedGfxArray[param_2].height;
            DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].field_0x1c = 0;
            DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].width = iVar1;
            DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].height = iVar2;
            if (param_1 == 6) {
                pCVar3 = DAT_ARRAY_00eb9b68::instance + DAT_UnknownBinkCount::instance;
                DAT_UnknownBinkCount::instance = DAT_UnknownBinkCount::instance + 1;
                pCVar3->field_0x1c = 1;
                return;
            }
            if (param_1 == 7) {
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].field_0x1c
                    = 2;
            }
            DAT_UnknownBinkCount::instance = DAT_UnknownBinkCount::instance + 1;
        }
        return;
    }

}
}
