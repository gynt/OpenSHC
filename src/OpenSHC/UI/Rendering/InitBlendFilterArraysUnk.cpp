#include "../Rendering.func.hpp"

#include "OpenSHC/Rendering/ColorMode.hpp"

#include "OpenSHC/Globals/DAT_BlendFilterArrays.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::Rendering::ColorMode;

    // FUNCTION: STRONGHOLDCRUSADER 0x0044E510
    void Rendering::InitBlendFilterArraysUnk()
    {
        uint uVar1;
        uint uVar2;
        short* psVar3;
        int _someCounterUnk;
        short* _shortPtr;
        int iVar4;
        undefined2* puVar5;
        int iVar6;
        int iVar7;
        int local_10;
        int local_c;
        short* local_8;
        int local_4;
        if (DAT_WindowAndDirectDraw::instance.colorBitMode != OpenSHC::Rendering::RGB_555) {
            local_10 = 0;
            local_c = 0;
            local_8 = DAT_BlendFilterArrays::instance[0][0] + 2;
            do {
                iVar7 = 0;
                iVar4 = 0;
                puVar5 = (undefined2*)(local_8 + 3);
                local_4 = 0x20;
                psVar3 = local_8;
                iVar6 = local_10;
                do {
                    uVar1 = iVar7 / 32;
                    (*(short (*)[4])(psVar3 + -2))[0] = (short)uVar1;
                    *psVar3 = (short)((uVar1 & 0xffff) << 0xb);
                    iVar7 = iVar7 + local_10;
                    puVar5[-4] = (short)((iVar4 / 64) << 5);
                    *puVar5 = (short)((iVar6 / 64) << 5);
                    psVar3 = psVar3 + 4;
                    puVar5 = puVar5 + 8;
                    iVar4 = iVar4 + local_c;
                    iVar6 = iVar6 + local_c;
                    local_4 = local_4 + -1;
                } while (local_4);
                local_10 = local_10 + 1;
                local_c = local_c + 4;
                local_8 = local_8 + 0x100;
            } while ((int)local_8 < 0xd814dc);
        }
        _shortPtr = DAT_BlendFilterArrays::instance[0][0] + 1;
        _someCounterUnk = 0;
        do {
            iVar4 = 0;
            iVar6 = 0x20;
            psVar3 = _shortPtr;
            do {
                uVar1 = iVar4 / 32;
                uVar2 = uVar1 & 0xffff;
                psVar3[-1] = (short)uVar1;
                *psVar3 = (short)(uVar2 << 5);
                psVar3[1] = (short)(uVar2 << 10);
                psVar3 = psVar3 + 4;
                iVar4 = iVar4 + _someCounterUnk;
                iVar6 = iVar6 + -1;
            } while (iVar6);
            _shortPtr = _shortPtr + 0x100;
            _someCounterUnk = _someCounterUnk + 1;
        } while ((int)_shortPtr < 0xd814da);
    }

}
}
