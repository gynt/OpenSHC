#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"



#include "OpenSHC/Globals/PTR_caseD_144_004097c4.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Commands::MappersEnum;
using OpenSHC::Map::Buildings::BuildingType;


/* 
  WARNING: Enum "MappersEnum": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00409370
BuildingType BuildingsState::convertCommandBuildingTypeToBuildingType(MappersEnum commandBuildingType)

{
if (commandBuildingType - OpenSHC::Commands::M_MAPPER_TOWER < 0x14b) {
/* 
  WARNING (jumptable): Sanity check requires truncation of jumptable
 */

/* 
  WARNING: Could not find normalized switch variable to match jumptable
 */

switch(*(undefined1 *)((int)PTR_caseD_144_004097c4::ptr + commandBuildingType)) {
case 0:
return OpenSHC::Map::Buildings::BT_TOWER;
case 1:
return OpenSHC::Map::Buildings::BT_FLETCHER;
case 2:
return OpenSHC::Map::Buildings::BT_WOODCUTTERSHUT;
case 3:
return OpenSHC::Map::Buildings::BT_STOCKPILE;
case 4:
return OpenSHC::Map::Buildings::BT_HOUSE;
case 5:
return OpenSHC::Map::Buildings::BT_HOVEL;
case 6:
return OpenSHC::Map::Buildings::BT_OXTETHER;
case 7:
return OpenSHC::Map::Buildings::BT_QUARRY;
case 8:
return OpenSHC::Map::Buildings::BT_TUNNEL;
case 9:
return OpenSHC::Map::Buildings::BT_SIGNPOST;
case 10:
return OpenSHC::Map::Buildings::BT_MANORHOUSE;
case 0xb:
return OpenSHC::Map::Buildings::BT_STONEKEEP;
case 0xc:
return OpenSHC::Map::Buildings::BT_STRONGHOLD;
case 0xd:
return OpenSHC::Map::Buildings::BT_STABLES;
case 0xe:
return OpenSHC::Map::Buildings::BT_UNKNOWN4;
case 0xf:
return OpenSHC::Map::Buildings::BT_WHEATFARM;
case 0x10:
return OpenSHC::Map::Buildings::BT_HOPFARM;
case 0x11:
return OpenSHC::Map::Buildings::BT_APPLEFARM;
case 0x12:
return OpenSHC::Map::Buildings::BT_DAIRYFARM;
case 0x13:
return OpenSHC::Map::Buildings::BT_MILL;
case 0x14:
return OpenSHC::Map::Buildings::BT_BAKERY;
case 0x15:
return OpenSHC::Map::Buildings::BT_BREWERY;
case 0x16:
return OpenSHC::Map::Buildings::BT_MARKETPLACE;
case 0x17:
return OpenSHC::Map::Buildings::BT_HUNTERSHUT;
case 0x18:
return OpenSHC::Map::Buildings::BT_GRANARY;
case 0x19:
return OpenSHC::Map::Buildings::BT_ARMORY;
case 0x1a:
return OpenSHC::Map::Buildings::BT_POLETURNER;
case 0x1b:
return OpenSHC::Map::Buildings::BT_BLACKSMITH;
case 0x1c:
return OpenSHC::Map::Buildings::BT_ARMOURER;
case 0x1d:
return OpenSHC::Map::Buildings::BT_TANNER;
case 0x1e:
return OpenSHC::Map::Buildings::BT_MERCENARYPOST;
case 0x1f:
return OpenSHC::Map::Buildings::BT_BARRACKS;
case 0x20:
return OpenSHC::Map::Buildings::BT_ENGINEERSGUILD;
case 0x21:
return OpenSHC::Map::Buildings::BT_TUNNELERSGUILD;
case 0x22:
return OpenSHC::Map::Buildings::BT_IRONMINE;
case 0x23:
return OpenSHC::Map::Buildings::BT_PITCHRIG;
case 0x24:
return OpenSHC::Map::Buildings::BT_INN;
case 0x25:
return OpenSHC::Map::Buildings::BT_APOTHECARY;
case 0x26:
return OpenSHC::Map::Buildings::BT_SIEGETOWER_PLACED;
case 0x27:
return OpenSHC::Map::Buildings::BT_CHAPEL;
case 0x28:
return OpenSHC::Map::Buildings::BT_CHURCH;
case 0x29:
return OpenSHC::Map::Buildings::BT_CATHEDRAL;
case 0x2a:
return OpenSHC::Map::Buildings::BT_KILLINGPIT;
case 0x2b:
return OpenSHC::Map::Buildings::BT_PITCHDITCH;
case 0x2c:
return OpenSHC::Map::Buildings::BT_GATEHOUSELARGE;
case 0x2d:
return OpenSHC::Map::Buildings::BT_GATEHOUSESMALL;
case 0x2e:
return OpenSHC::Map::Buildings::BT_WOODGATE2;
case 0x2f:
return OpenSHC::Map::Buildings::BT_DRAWBRIDGE;
case 0x30:
return OpenSHC::Map::Buildings::BT_QUARRYSTOCKPILE;
case 0x31:
return OpenSHC::Map::Buildings::BT_TOWER1;
case 0x32:
return OpenSHC::Map::Buildings::BT_TOWER2;
case 0x33:
return OpenSHC::Map::Buildings::BT_TOWER3;
case 0x34:
return OpenSHC::Map::Buildings::BT_TOWER4;
case 0x35:
return OpenSHC::Map::Buildings::BT_TOWER5;
case 0x36:
return OpenSHC::Map::Buildings::BT_MANGONEL;
case 0x37:
return OpenSHC::Map::Buildings::BT_BALLISTA;
case 0x38:
return OpenSHC::Map::Buildings::BT_UNKNOWN5;
case 0x39:
return OpenSHC::Map::Buildings::BT_UNKNOWN6;
case 0x3a:
return OpenSHC::Map::Buildings::BT_UNKNOWN3;
case 0x3b:
return OpenSHC::Map::Buildings::BT_WOODGATE1;
case 0x3c:
return OpenSHC::Map::Buildings::BT_GARDEN;
case 0x3d:
return OpenSHC::Map::Buildings::BT_MAYPOLE;
case 0x3e:
return OpenSHC::Map::Buildings::BT_GALLOWS;
case 0x3f:
return OpenSHC::Map::Buildings::BT_STOCKS;
case 0x40:
return OpenSHC::Map::Buildings::BT_OUTPOST_EUROPEAN;
case 0x41:
return OpenSHC::Map::Buildings::BT_OUTPOST_ARABIAN;
case 0x42:
return OpenSHC::Map::Buildings::BT_OILSMELTER;
case 0x43:
return OpenSHC::Map::Buildings::BT_CATAPULT;
case 0x44:
return OpenSHC::Map::Buildings::BT_TREBUCHET;
case 0x45:
return OpenSHC::Map::Buildings::BT_BATTERINGRAM;
case 0x46:
return OpenSHC::Map::Buildings::BT_SIEGETOWER;
case 0x47:
return OpenSHC::Map::Buildings::BT_SHIELD;
case 0x48:
return OpenSHC::Map::Buildings::BT_UNKNOWN1;
case 0x49:
return OpenSHC::Map::Buildings::BT_CESSPIT;
case 0x4a:
return OpenSHC::Map::Buildings::BT_BURNINGSTAKE;
case 0x4b:
return OpenSHC::Map::Buildings::BT_GIBBET;
case 0x4c:
return OpenSHC::Map::Buildings::BT_DUNGEON;
case 0x4d:
return OpenSHC::Map::Buildings::BT_STRETCHINGRACK;
case 0x4e:
return OpenSHC::Map::Buildings::BT_RACKFLOGGING;
case 0x4f:
return OpenSHC::Map::Buildings::BT_CHOPPINGBLOCK;
case 0x50:
return OpenSHC::Map::Buildings::BT_DUNKINGSTOOL;
case 0x51:
return OpenSHC::Map::Buildings::BT_DOGCAGE;
case 0x52:
return OpenSHC::Map::Buildings::BT_STATUE;
case 0x53:
return OpenSHC::Map::Buildings::BT_SHRINE;
case 0x54:
return OpenSHC::Map::Buildings::BT_BEEHIVE;
case 0x55:
return OpenSHC::Map::Buildings::BT_DANCINGBEAR;
case 0x56:
return OpenSHC::Map::Buildings::BT_POND;
case 0x57:
return OpenSHC::Map::Buildings::BT_BEARCAVE;
case 0x58:
return OpenSHC::Map::Buildings::BT_WELL;
case 0x59:
return OpenSHC::Map::Buildings::BT_WATERPOT;
case 0x5a:
return OpenSHC::Map::Buildings::BT_FIREBALLISTA;
}
}
return ((BuildingType)0);
}


}
}
}