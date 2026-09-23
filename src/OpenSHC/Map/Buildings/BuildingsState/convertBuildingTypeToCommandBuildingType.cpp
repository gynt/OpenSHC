#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"





namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Commands::MappersEnum;


/* 
  WARNING: Enum "MappersEnum": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00409930
MappersEnum BuildingsState::convertBuildingTypeToCommandBuildingType(BuildingType buildingType)

{
switch(buildingType) {
case OpenSHC::Map::Buildings::BT_HOVEL:
return OpenSHC::Commands::M_MAPPER_HOVEL;
case OpenSHC::Map::Buildings::BT_HOUSE:
return OpenSHC::Commands::M_MAPPER_OUTPOST_BEDOUIN;
case OpenSHC::Map::Buildings::BT_WOODCUTTERSHUT:
return OpenSHC::Commands::M_MAPPER_WOODSMAN;
case OpenSHC::Map::Buildings::BT_OXTETHER:
return OpenSHC::Commands::M_MAPPER_OXENBASE;
case OpenSHC::Map::Buildings::BT_IRONMINE:
return OpenSHC::Commands::M_MAPPER_IRON_MINE;
case OpenSHC::Map::Buildings::BT_PITCHRIG:
return OpenSHC::Commands::M_MAPPER_PITCH_WORKINGS;
case OpenSHC::Map::Buildings::BT_HUNTERSHUT:
return OpenSHC::Commands::M_MAPPER_HUNTER;
case OpenSHC::Map::Buildings::BT_MERCENARYPOST:
return OpenSHC::Commands::M_MAPPER_BARRACKS_EURO;
case OpenSHC::Map::Buildings::BT_BARRACKS:
return OpenSHC::Commands::M_MAPPER_BARRACKS_ARAB;
case OpenSHC::Map::Buildings::BT_STOCKPILE:
return OpenSHC::Commands::M_MAPPER_STORES;
case OpenSHC::Map::Buildings::BT_ARMORY:
return OpenSHC::Commands::M_MAPPER_ARMOURY;
case OpenSHC::Map::Buildings::BT_FLETCHER:
return OpenSHC::Commands::M_MAPPER_FLETCHER;
case OpenSHC::Map::Buildings::BT_BLACKSMITH:
return OpenSHC::Commands::M_MAPPER_BLACKSMITH;
case OpenSHC::Map::Buildings::BT_POLETURNER:
return OpenSHC::Commands::M_MAPPER_POLETURNER;
case OpenSHC::Map::Buildings::BT_ARMOURER:
return OpenSHC::Commands::M_MAPPER_ARMOURER;
case OpenSHC::Map::Buildings::BT_TANNER:
return OpenSHC::Commands::M_MAPPER_TANNER;
case OpenSHC::Map::Buildings::BT_BAKERY:
return OpenSHC::Commands::M_MAPPER_BAKER;
case OpenSHC::Map::Buildings::BT_BREWERY:
return OpenSHC::Commands::M_MAPPER_BREWER;
case OpenSHC::Map::Buildings::BT_GRANARY:
return OpenSHC::Commands::M_MAPPER_GRANARY;
case OpenSHC::Map::Buildings::BT_QUARRY:
return OpenSHC::Commands::M_MAPPER_QUARRY;
OpenSHC::Map::Buildings::default:
return OpenSHC::Commands::M_MAPPER_NULL;
case OpenSHC::Map::Buildings::BT_INN:
return OpenSHC::Commands::M_MAPPER_INN;
case OpenSHC::Map::Buildings::BT_APOTHECARY:
return OpenSHC::Commands::M_MAPPER_HEALER;
case OpenSHC::Map::Buildings::BT_ENGINEERSGUILD:
return OpenSHC::Commands::M_MAPPER_ENGINEERS_GUILD;
case OpenSHC::Map::Buildings::BT_TUNNELERSGUILD:
return OpenSHC::Commands::M_MAPPER_TUNNELERS_GUILD;
case OpenSHC::Map::Buildings::BT_MARKETPLACE:
return OpenSHC::Commands::M_MAPPER_TRADEPOST;
case OpenSHC::Map::Buildings::BT_WELL:
return OpenSHC::Commands::M_MAPPER_WELL;
case OpenSHC::Map::Buildings::BT_OILSMELTER:
return OpenSHC::Commands::M_MAPPER_OIL_SMELTER;
case OpenSHC::Map::Buildings::BT_WHEATFARM:
return OpenSHC::Commands::M_MAPPER_WHEATFARM;
case OpenSHC::Map::Buildings::BT_HOPFARM:
return OpenSHC::Commands::M_MAPPER_HOPSFARM;
case OpenSHC::Map::Buildings::BT_APPLEFARM:
return OpenSHC::Commands::M_MAPPER_APPLEFARM;
case OpenSHC::Map::Buildings::BT_DAIRYFARM:
return OpenSHC::Commands::M_MAPPER_CATTLEFARM;
case OpenSHC::Map::Buildings::BT_MILL:
return OpenSHC::Commands::M_MAPPER_MILL;
case OpenSHC::Map::Buildings::BT_STABLES:
return OpenSHC::Commands::M_MAPPER_STABLES;
case OpenSHC::Map::Buildings::BT_CHAPEL:
return OpenSHC::Commands::M_MAPPER_CHURCH1;
case OpenSHC::Map::Buildings::BT_CHURCH:
return OpenSHC::Commands::M_MAPPER_CHURCH2;
case OpenSHC::Map::Buildings::BT_CATHEDRAL:
return OpenSHC::Commands::M_MAPPER_CHURCH3;
case OpenSHC::Map::Buildings::BT_UNKNOWN1:
return OpenSHC::Commands::M_MAPPER_MP_KEEP1|OpenSHC::Commands::M_MAPPER_BEACH;
case OpenSHC::Map::Buildings::BT_MANORHOUSE:
return OpenSHC::Commands::M_MAPPER_KEEP1;
case OpenSHC::Map::Buildings::BT_STONEKEEP:
return OpenSHC::Commands::M_MAPPER_KEEP2;
case OpenSHC::Map::Buildings::BT_STRONGHOLD:
return OpenSHC::Commands::M_MAPPER_KEEP3;
case OpenSHC::Map::Buildings::BT_GATEHOUSELARGE:
return OpenSHC::Commands::M_MAPPER_GATE_MAIN;
case OpenSHC::Map::Buildings::BT_GATEHOUSESMALL:
return OpenSHC::Commands::M_MAPPER_GATE_INNER;
case OpenSHC::Map::Buildings::BT_DRAWBRIDGE:
return OpenSHC::Commands::M_MAPPER_DRAWBRIDGE;
case OpenSHC::Map::Buildings::BT_TUNNEL:
return OpenSHC::Commands::M_MAPPER_TUNNEL;
case OpenSHC::Map::Buildings::BT_SIGNPOST:
return OpenSHC::Commands::M_MAPPER_SIGNPOST;
case OpenSHC::Map::Buildings::BT_FIREBALLISTA:
return OpenSHC::Commands::M_MAPPER_ARAB_BALLISTA;
case OpenSHC::Map::Buildings::BT_TOWER:
return OpenSHC::Commands::M_MAPPER_TOWER;
case OpenSHC::Map::Buildings::BT_GALLOWS:
return OpenSHC::Commands::M_MAPPER_GALLOWS;
case OpenSHC::Map::Buildings::BT_STOCKS:
return OpenSHC::Commands::M_MAPPER_STOCKS;
case OpenSHC::Map::Buildings::BT_MAYPOLE:
return OpenSHC::Commands::M_MAPPER_MAYPOLE;
case OpenSHC::Map::Buildings::BT_GARDEN:
return OpenSHC::Commands::M_MAPPER_GARDEN1;
case OpenSHC::Map::Buildings::BT_KILLINGPIT:
return OpenSHC::Commands::M_MAPPER_KILLING_PIT;
case OpenSHC::Map::Buildings::BT_PITCHDITCH:
return OpenSHC::Commands::M_MAPPER_PITCH_DITCH;
case OpenSHC::Map::Buildings::BT_SIEGETOWER_PLACED:
return OpenSHC::Commands::M_MAPPER_SIEGE_TOWER_BASE;
case OpenSHC::Map::Buildings::BT_WATERPOT:
return OpenSHC::Commands::M_MAPPER_WATERPOT;
case OpenSHC::Map::Buildings::BT_TOWER1:
return OpenSHC::Commands::M_MAPPER_TOWER1;
case OpenSHC::Map::Buildings::BT_TOWER2:
return OpenSHC::Commands::M_MAPPER_TOWER2;
case OpenSHC::Map::Buildings::BT_TOWER3:
return OpenSHC::Commands::M_MAPPER_TOWER3;
case OpenSHC::Map::Buildings::BT_TOWER4:
return OpenSHC::Commands::M_MAPPER_TOWER4;
case OpenSHC::Map::Buildings::BT_TOWER5:
return OpenSHC::Commands::M_MAPPER_TOWER5;
case OpenSHC::Map::Buildings::BT_UNKNOWN3:
return OpenSHC::Commands::M_MAPPER_TOWER5_DESTROYED;
case OpenSHC::Map::Buildings::BT_CATAPULT:
return OpenSHC::Commands::M_MAPPER_CATAPULT;
case OpenSHC::Map::Buildings::BT_TREBUCHET:
return OpenSHC::Commands::M_MAPPER_TREBUCHET;
case OpenSHC::Map::Buildings::BT_BATTERINGRAM:
return OpenSHC::Commands::M_MAPPER_SIEGE_TOWER;
case OpenSHC::Map::Buildings::BT_SIEGETOWER:
return OpenSHC::Commands::M_MAPPER_BATTERING_RAM;
case OpenSHC::Map::Buildings::BT_SHIELD:
return OpenSHC::Commands::M_MAPPER_PORTABLE_SHIELD;
case OpenSHC::Map::Buildings::BT_UNKNOWN4:
return OpenSHC::Commands::M_MAPPER_TUNNEL_CONSTRUCTION;
case OpenSHC::Map::Buildings::BT_MANGONEL:
return OpenSHC::Commands::M_MAPPER_TOWER1_DESTROYED;
case OpenSHC::Map::Buildings::BT_BALLISTA:
return OpenSHC::Commands::M_MAPPER_TOWER2_DESTROYED;
case OpenSHC::Map::Buildings::BT_UNKNOWN5:
return OpenSHC::Commands::M_MAPPER_TOWER3_DESTROYED;
case OpenSHC::Map::Buildings::BT_UNKNOWN6:
return OpenSHC::Commands::M_MAPPER_TOWER4_DESTROYED;
case OpenSHC::Map::Buildings::BT_CESSPIT:
return OpenSHC::Commands::M_MAPPER_CESS_PIT4;
case OpenSHC::Map::Buildings::BT_BURNINGSTAKE:
return OpenSHC::Commands::M_MAPPER_BURNING_STAKE;
case OpenSHC::Map::Buildings::BT_GIBBET:
return OpenSHC::Commands::M_MAPPER_GIBBET;
case OpenSHC::Map::Buildings::BT_DUNGEON:
return OpenSHC::Commands::M_MAPPER_DUNGEON;
case OpenSHC::Map::Buildings::BT_STRETCHINGRACK:
return OpenSHC::Commands::M_MAPPER_RACK_STRETCHING;
case OpenSHC::Map::Buildings::BT_RACKFLOGGING:
return OpenSHC::Commands::M_MAPPER_RACK_FLOGGING;
case OpenSHC::Map::Buildings::BT_CHOPPINGBLOCK:
return OpenSHC::Commands::M_MAPPER_CHOPPING_BLOCK;
case OpenSHC::Map::Buildings::BT_DUNKINGSTOOL:
return OpenSHC::Commands::M_MAPPER_DUNKING_STOOL;
case OpenSHC::Map::Buildings::BT_DOGCAGE:
return OpenSHC::Commands::M_MAPPER_DOG_CAGE;
case OpenSHC::Map::Buildings::BT_STATUE:
return OpenSHC::Commands::M_MAPPER_STATUE5;
case OpenSHC::Map::Buildings::BT_SHRINE:
return OpenSHC::Commands::M_MAPPER_SHRINE5;
case OpenSHC::Map::Buildings::BT_DANCINGBEAR:
return OpenSHC::Commands::M_MAPPER_DANCING_BEAR;
case OpenSHC::Map::Buildings::BT_POND:
return OpenSHC::Commands::M_MAPPER_POND4_LARGE2;
case OpenSHC::Map::Buildings::BT_BEARCAVE:
return OpenSHC::Commands::M_MAPPER_BEAR_CAVE;
case OpenSHC::Map::Buildings::BT_OUTPOST_EUROPEAN:
return OpenSHC::Commands::M_MAPPER_OUTPOST_EURO;
case OpenSHC::Map::Buildings::BT_OUTPOST_ARABIAN:
return OpenSHC::Commands::M_MAPPER_OUTPOST_ARAB;
}
}


}
}
}