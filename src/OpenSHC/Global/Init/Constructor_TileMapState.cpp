#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Global {

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2026-05-02 18:15:17.059000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0059CAC0
    void Init::Constructor_TileMapState()
    {
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::Constructor_TileMapState, DAT_TileMapState::ptr)();
        MACRO_CALL(OpenSHC::OS_Func::_atexit)(MACRO_CALL(OpenSHC::Meta_Func::Destructor_0059d6b0));
        return;
    }

}
}
