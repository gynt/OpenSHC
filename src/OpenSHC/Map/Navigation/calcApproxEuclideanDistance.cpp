#include "../../Map.func.hpp"
#include "../Navigation.func.hpp"

namespace OpenSHC {
namespace Map {

    /*
      Computes an approximate Euclidean distance between two 2D integer points (param_1, param_3) and   (param_2,
      param_4) using the Octagonal Distance Approximation formula: max(dx,dy) + 0.4 *   min(dx,dy)^2 / max(dx,dy). This
      is a fast integer-math alternative to true Euclidean distance,   with a maximum error of ~8%. Commonly used in
      pathfinding and navigation to avoid expensive sqrt   operations. Returns 0 if both dx and dy are zero. renamed by:
      Claude Sonnet 4.6
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0049B8C0
    int Navigation::calcApproxEuclideanDistance(int param_1, int param_2, int param_3, int param_4)
    {
        int iVar1;
        int iVar2;
        if (param_2 < param_1) {
            iVar1 = param_1 - param_2;
        } else {
            iVar1 = param_2 - param_1;
        }
        if (param_4 < param_3) {
            iVar2 = param_3 - param_4;
        } else {
            iVar2 = param_4 - param_3;
        }
        if (iVar1 < iVar2) {
            if (iVar2) {
                return (((iVar1 * 2) / 5) * iVar1) / iVar2 + iVar2;
            }
        } else if (iVar1) {
            return (((iVar2 * 2) / 5) * iVar2) / iVar1 + iVar1;
        }
        return 0;
    }

}
}
