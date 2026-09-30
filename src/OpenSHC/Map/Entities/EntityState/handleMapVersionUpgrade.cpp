#include "../../../Map.func.hpp"
#include "../EntityState.func.hpp"

#include "OpenSHC/Map/Version.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/IO/PackagedFileMagicNum.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        using OpenSHC::Game::GameMode;
        using OpenSHC::IO::PackagedFileMagicNum;

        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00408770
        void EntityState::handleMapVersionUpgrade(
            PackagedFileMagicNum receivedMapVersion, PackagedFileMagicNum packagerMapVersion)
        {
            if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
                MACRO_CALL(OpenSHC::Map::Version_Func::DeleteSeagull)();
            }
            if (receivedMapVersion == packagerMapVersion) {}
            if (receivedMapVersion == ((PackagedFileMagicNum)100)) {
                MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeSetCurrentEntityID3000)();
            } else if (0x90 < (int)receivedMapVersion)
                goto LAB_004087a2;
            MACRO_CALL(OpenSHC::Map::Version_Func::SetFlagEntityColor)();
        LAB_004087a2:
            if ((int)receivedMapVersion < 0xa0) {
                MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeFirst25Entities)();
            }
        }

    }
}
}
