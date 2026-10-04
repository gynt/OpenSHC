#include "../../Map.func.hpp"
#include "../MapPropertiesState.func.hpp"

#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {

    using Commands::MappersEnum;
    using Game::GameMode;
    using Game::GameMode2;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004BB010
    BOOLEnum MapPropertiesState::isMapperAvailable(MappersEnum param_1)
    {
        if ((param_1 == Commands::M_MAPPER_OUTPOST_EURO)
            || (param_1 == Commands::M_MAPPER_OUTPOST_ARAB)) {
            if (DAT_GameCore::instance.gameMode_2 != Game::GM_EDITOR) {
                return FALSE;
            }
        } else if (DAT_GameCore::instance.gameMode_2 != Game::GM_EDITOR)
            goto LAB_004bb062;
        if (0 < (int)DAT_GameCore::instance.U2_mapType_singleOrMulti) {
            if (param_1 == Commands::M_MAPPER_KEEP1) {
                return FALSE;
            }
            if ((0x3d < (int)param_1) && ((int)param_1 < 0x41)) {
                return FALSE;
            }
            return TRUE;
        }
        if (DAT_GameCore::instance.gameMode_2 == Game::GM_EDITOR) {
            return TRUE;
        }
    LAB_004bb062:
        if (param_1 == Commands::M_MAPPER_DOG_CAGE) {
            if (((DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY)
                    && (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SKIRMISH_SINGLE_PLAYER))
                && (DAT_GameState::instance.mapAndTime.skirmishNoDogs != 0)) {
                return FALSE;
            }
        } else if (((param_1 == Commands::M_MAPPER_HUNTER)
                       && (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY))
            && (DAT_GameState::instance.mapAndTime.rawDeerCount == 0)) {
            return FALSE;
        }
        return (int)this->buildingAvailabilityRelatedFlags[param_1];
    }

}
}
