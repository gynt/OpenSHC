#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // The tribe is created before the tile is validated (0x525BAF), so every early 'return 0' leaves an empty
        // tribe behind. Unknown animal types skip the spawn loop but still get herd sizes and return the tribe.
        // FUNCTION: STRONGHOLDCRUSADER 0x00525BA0
        dword TribesState::createAnimal(OpenSHC::Commands::MappersEnum animalType, uint x, uint y, int tile)
        {
            UnitType unitType = UT_NONE;
            int herdSize = 0;
            int const tribeID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::createTribe, this)(0, 0);
            if (tribeID <= 0) {
                return 0;
            }
            if (x > 399 || y > 399 || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] == 0) {
                return 0;
            }
            int const tileIndex = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
            if (animalType == OpenSHC::Commands::M_MAPPER_DEER) {
                if ((DAT_TileMapState::instance.LogicLayer[tileIndex] & 0x4a5014b1) != 0) {
                    return 0;
                }
                this->tribes[tribeID].tribeType = OpenSHC::AI::Tribes::AITT_DEER;
                unitType = UT_ANTELOPESHDEER;
                herdSize = (SEC_RNG::instance.currentNumber2 & 3) + 9;
            } else if (animalType == OpenSHC::Commands::M_MAPPER_LION) {
                if ((DAT_TileMapState::instance.LogicLayer[tileIndex] & 0x4a5014b1) != 0) {
                    return 0;
                }
                this->tribes[tribeID].tribeType = OpenSHC::AI::Tribes::AITT_LIONS;
                unitType = UT_LIONSHWOLF;
                herdSize = (SEC_RNG::instance.currentNumber2 & 1) + 3;
            } else if (animalType == OpenSHC::Commands::M_MAPPER_RABBIT) {
                if ((DAT_TileMapState::instance.LogicLayer[tileIndex] & 0x4a5014b1) != 0) {
                    return 0;
                }
                this->tribes[tribeID].tribeType = OpenSHC::AI::Tribes::AITT_RABBITS;
                unitType = UT_RABBIT;
                herdSize = (SEC_RNG::instance.currentNumber2 & 7) + 14;
            } else if (animalType == OpenSHC::Commands::M_MAPPER_CAMEL) {
                if ((DAT_TileMapState::instance.LogicLayer[tileIndex] & 0x4a5014b1) != 0) {
                    return 0;
                }
                this->tribes[tribeID].tribeType = OpenSHC::AI::Tribes::AITT_CAMELS;
                unitType = UT_CAMELSHBEAR;
                herdSize = (SEC_RNG::instance.currentNumber2 & 3) + 2;
            } else if (animalType == OpenSHC::Commands::M_MAPPER_CROW_SEAGULL) {
                MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::markNearbyTreesAsCrowTargets,
                    DAT_LandscapeState::ptr)(x, y);
                return 0;
            } else if (animalType == OpenSHC::Commands::M_MAPPER_SEAGULL) {
                if ((DAT_TileMapState::instance.LogicLayer[tileIndex] & 1) != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::createSeagull,
                        DAT_EntityState::ptr)(x * 8, y * 8);
                }
                return 0;
            }
            for (int i = 0; i < herdSize; ++i) {
                int const unitID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::spawnUnit,
                    DAT_UnitsState::ptr)(0, 0, x * 8, y * 8, tile, unitType);
                if (unitID != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::addUnitToTribe, this)(unitID, tribeID);
                    DAT_UnitsState::instance.units[unitID].substate = (short)(DAT_UnitsState::instance.units[unitID].fixedRng & 3);
                    if (unitType == UT_ANTELOPESHDEER) {
                        byte const variant = (byte)DAT_UnitsState::instance.units[unitID].fixedRng & 7;
                        DAT_UnitsState::instance.units[unitID].antelopeBasedRngValue = variant;
                        if (variant == 3) {
                            DAT_UnitsState::instance.units[unitID].antelopeBasedRngValue = 1;
                        } else if (variant == 4) {
                            DAT_UnitsState::instance.units[unitID].antelopeBasedRngValue = 1;
                        } else if (variant == 5) {
                            DAT_UnitsState::instance.units[unitID].antelopeBasedRngValue = 1;
                        } else if (variant == 6 || variant == 7) {
                            DAT_UnitsState::instance.units[unitID].antelopeBasedRngValue = 2;
                        }
                        if (i == 0) {
                            DAT_UnitsState::instance.units[unitID].antelopeBasedRngValue = 0;
                        } else if (i == 1 || i == 2) {
                            DAT_UnitsState::instance.units[unitID].antelopeBasedRngValue = 1;
                        }
                    }
                    DAT_UnitsState::instance.units[unitID].fadeLevel = 0x20;
                }
            }
            short const size = this->tribes[tribeID].size;
            this->tribes[tribeID].wildlifeMinSize = size / 2;
            if (animalType == OpenSHC::Commands::M_MAPPER_LION) {
                this->tribes[tribeID].wildlifeMaxSize = size;
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::storeLionXAndYInMapInfo, this)(x, y);
                return tribeID;
            }
            this->tribes[tribeID].wildlifeMaxSize = size * 2;
            if (animalType == OpenSHC::Commands::M_MAPPER_DEER) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::storeDeerXAndYinMapInfo, this)(x, y);
            } else if (animalType == OpenSHC::Commands::M_MAPPER_RABBIT) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::setRabbitSpawnXY, this)(x, y);
            } else if (animalType == OpenSHC::Commands::M_MAPPER_CAMEL) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::setCamelSpawnXY, this)(x, y);
            }
            return tribeID;
        }

    }
}
}
