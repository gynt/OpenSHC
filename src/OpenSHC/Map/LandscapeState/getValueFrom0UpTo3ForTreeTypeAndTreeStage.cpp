#include "OpenSHC/Map/LandscapeState.func.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F1BE0
    undefined4 LandscapeState::getValueFrom0UpTo3ForTreeTypeAndTreeStage(undefined4 treeType, int treeStage)
    {
        if (treeStage <= 1) {
            return 1;
        }
        switch (treeType) {
        case OpenSHC::Map::Trees::TT_CHESTNUT:
        case OpenSHC::Map::Trees::TT_OAK:
            return 3;
        case OpenSHC::Map::Trees::TT_PINE:
        case OpenSHC::Map::Trees::TT_BIRCH:
        case OpenSHC::Map::Trees::TT_APPLE:
            return 2;
        case OpenSHC::Map::Trees::TT_SHRUB1A:
        case OpenSHC::Map::Trees::TT_SHRUB1B:
        case OpenSHC::Map::Trees::TT_SHRUB1C:
        case OpenSHC::Map::Trees::TT_SHRUB1D:
        case OpenSHC::Map::Trees::TT_SHRUB1E:
            return 1;
        }
        return 0;
    }

}
}
