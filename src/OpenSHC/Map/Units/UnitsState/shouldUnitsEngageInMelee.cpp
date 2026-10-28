#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Game::GameMode;
        using OpenSHC::Map::Units::UnitType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00531000
        BOOLEnum UnitsState::isMeleeBetweenUnitsForbidden(int unitID_1, int unitID_2)
        {
            UnitTypeShort type1 = this->units[unitID_1].unitType;
            if (type1 == OpenSHC::Map::Units::UT_TRADER || type1 == OpenSHC::Map::Units::UT_TRADERHORSE) {
                return TRUE;
            }
            UnitTypeShort type2 = this->units[unitID_2].unitType;
            if (type2 == OpenSHC::Map::Units::UT_TRADER || type2 == OpenSHC::Map::Units::UT_TRADERHORSE
                || type1 == OpenSHC::Map::Units::UT_GHOST || type2 == OpenSHC::Map::Units::UT_GHOST) {
                return TRUE;
            }
            if (type1 == OpenSHC::Map::Units::UT_CAMELSHBEAR) {
                if (type2 == OpenSHC::Map::Units::UT_WOODCUTTER || type2 == OpenSHC::Map::Units::UT_LIONSHWOLF) {
                    return FALSE;
                }
                return TRUE;
            }
            if (type2 == OpenSHC::Map::Units::UT_CAMELSHBEAR) {
                if (type1 == OpenSHC::Map::Units::UT_WOODCUTTER || type1 == OpenSHC::Map::Units::UT_LIONSHWOLF) {
                    return FALSE;
                }
                return TRUE;
            }
            if (this->units[unitID_1].isAnimalOrAmbient != 0) {
                if (type1 == OpenSHC::Map::Units::UT_LIONSHWOLF) {
                    if (type2 == OpenSHC::Map::Units::UT_ANTELOPESHDEER || type2 == OpenSHC::Map::Units::UT_COW
                        || type2 == OpenSHC::Map::Units::UT_RABBIT || type2 == OpenSHC::Map::Units::UT_HUNTERDOG) {
                        return FALSE;
                    }
                    if (this->units[unitID_2].isAnimalOrAmbient == 0) {
                        return FALSE;
                    }
                    return TRUE;
                }
                if (type1 == OpenSHC::Map::Units::UT_CAGEDOG) {
                    if (type2 == OpenSHC::Map::Units::UT_ANTELOPESHDEER || type2 == OpenSHC::Map::Units::UT_COW
                        || type2 == OpenSHC::Map::Units::UT_RABBIT || type2 == OpenSHC::Map::Units::UT_HUNTERDOG) {
                        return FALSE;
                    }
                    if (this->units[unitID_2].isAnimalOrAmbient != 0) {
                        return TRUE;
                    }
                    return (BOOLEnum)(DAT_GameState::instance.mapAndTime
                                          .playerTeams[this->units[unitID_1].displayColorPlayerID]
                        == DAT_GameState::instance.mapAndTime.playerTeams[this->units[unitID_2].owner]);
                }
                if (type1 == OpenSHC::Map::Units::UT_HUNTERDOG) {
                    if (type2 == OpenSHC::Map::Units::UT_RABBIT || type2 == OpenSHC::Map::Units::UT_LIONSHWOLF
                        || type2 == OpenSHC::Map::Units::UT_CAGEDOG) {
                        return FALSE;
                    }
                    if (this->units[unitID_2].isAnimalOrAmbient == 0) {
                        return FALSE;
                    }
                    return TRUE;
                }
                return TRUE;
            }
            if (this->units[unitID_2].isAnimalOrAmbient != 0) {
                if (type2 == OpenSHC::Map::Units::UT_LIONSHWOLF) {
                    return FALSE;
                }
                if (type2 == OpenSHC::Map::Units::UT_CAGEDOG) {
                    return (BOOLEnum)(DAT_GameState::instance.mapAndTime
                                          .playerTeams[this->units[unitID_2].displayColorPlayerID]
                        == DAT_GameState::instance.mapAndTime.playerTeams[this->units[unitID_1].owner]);
                }
                if (type2 == OpenSHC::Map::Units::UT_RABBIT || type2 == OpenSHC::Map::Units::UT_QUARRYOX
                    || type2 == OpenSHC::Map::Units::UT_COW) {
                    return FALSE;
                }
                return (BOOLEnum)(type2 != OpenSHC::Map::Units::UT_HUNTERDOG);
            } else if (DAT_GameState::instance.mapAndTime.skirmishNoRushTicksLeft == 0
                || DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER
                || DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY) {
                return FALSE;
            }
            return TRUE;
        }

    }
}
}
