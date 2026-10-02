#include "../../../Map.func.hpp"
#include "../EntityState.func.hpp"

#include "math.h"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        /*
          decompilerscript: committed: 2025-01-30 21:56:35.138000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00402DA0
        int EntityState::computeVelocity(int param_2, double param_3, int param_4, int param_5)
        {
            int iVar1;
            double fVar2;
            double fVar3;
            double fVar4;
            fVar2 = ((double)param_3 * (double)3.1415926535) / (double)180.0;
            fVar3 = cos(fVar2);
            fVar4 = (double)(param_4 * 2);
            fVar2 = tan((double)fVar2);
            fVar2 = sqrt((double)(((double)9.812 * fVar4 * fVar4) / (fVar3 * fVar3))
                / (fVar2 * (double)(param_4 * 2) - (double)((int)(param_5 + (param_5 >> 0x1f & 3U)) >> 2)));
            iVar1 = (long)(fVar2);
            return iVar1;
        }

    }
}
}
