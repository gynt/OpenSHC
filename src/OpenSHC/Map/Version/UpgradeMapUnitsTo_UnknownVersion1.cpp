#include "../../Map.func.hpp"
#include "../Version.func.hpp"

#include "OpenSHC/Map/Units/Unit.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    using Map::Units::UnitLogicState;
    using Map::Units::UnitType;
    using Map::Units::Unit;

    // FUNCTION: STRONGHOLDCRUSADER 0x0053B3E0
    void Version::UpgradeMapUnitsTo_UnknownVersion1()
    {
        Unit* psVar1;
        psVar1 = &DAT_UnitsState::instance.units[1];
        DAT_CurrentUnitSlotID::instance = 2500;
        do {
            if (psVar1->logicalState == Map::Units::ULS_NORMAL) {
                if (psVar1->unitType != Map::Units::UT_CHILD) {
                    psVar1->spriteID
                        = (short)DAT_UnitPropertiesDefinedData::instance.SPRITE_ID[(short)psVar1->unitType];
                }
                psVar1->unitCanClimb
                    = (short)DAT_UnitPropertiesDefinedData::instance.UNIT_CLIMB[(short)psVar1->unitType];
                psVar1->someUnitStat4
                    = (short)DAT_UnitPropertiesDefinedData::instance.SomeUnitStatMatrix4[(short)psVar1->unitType];
                psVar1->field22_0x2a
                    = (short)DAT_TextureRenderCoreObject::instance.gmFileHeaderColorpaletteArray[psVar1->spriteID]
                          .originX;
                *(short*)&psVar1->unknownV
                    = (short)DAT_TextureRenderCoreObject::instance.gmFileHeaderColorpaletteArray[psVar1->spriteID]
                          .originY;
                psVar1->drawXOffset = psVar1->field22_0x2a - psVar1->spriteWidthUnk / 2;
                psVar1->someDrawYOffset = ((short)psVar1->unknownV - psVar1->spriteHeightUnk) + 3;
                psVar1->graphicSize
                    = (short)DAT_UnitPropertiesDefinedData::instance.GRAPHIC_SIZE[(short)psVar1->unitType];
                psVar1->enemyNoticeFrequencyUnk
                    = DAT_UnitPropertiesDefinedData::instance.UNIT_ENEMY_NOTICE_RANGE[(short)psVar1->unitType];
                psVar1->moveableUnk
                    = (short)DAT_UnitPropertiesDefinedData::instance.UNIT_MOVABLE[(short)psVar1->unitType];
            }
            psVar1 = psVar1 + 0x248;
        } while ((int)psVar1 < 0x1651398);
    }

}
}
