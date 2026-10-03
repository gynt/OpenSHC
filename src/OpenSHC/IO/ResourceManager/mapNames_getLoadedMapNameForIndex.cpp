#include "../../IO.func.hpp"
#include "../ResourceManager.func.hpp"

namespace OpenSHC {
namespace IO {

    // FUNCTION: STRONGHOLDCRUSADER 0x0046C2E0
    char* ResourceManager::mapNames_getLoadedMapNameForIndex(int mapIndex)
    {
        if (499 < mapIndex) {
            return (char*)0x0;
        }
        return (char*)(this->loadedMapNames[mapIndex]);
    }

}
}
