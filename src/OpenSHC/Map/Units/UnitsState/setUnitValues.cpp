#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0053B8E0
        void UnitsState::setUnitValues(int unitID, UnitType unitType)
        {
            this->units[unitID].unitType = (UnitTypeShort)unitType;
            this->units[unitID].occupiesNeighbourTiles = (short)DAT_UnitPropertiesDefinedData::instance.occupiesNeighbourTilesPerType[unitType];
            this->units[unitID].isAnimalOrAmbient = (byte)DAT_UnitPropertiesDefinedData::instance.isStalkedPerType[unitType];
            short _spriteID = (short)DAT_UnitPropertiesDefinedData::instance.SPRITE_ID[unitType];
            this->units[unitID].secondaryGmID = _spriteID;
            this->units[unitID].spriteID = _spriteID;
            this->units[unitID].gfxNumber = 1;
            this->units[unitID].spriteOriginX = (short)DAT_TextureRenderCoreObject::instance
                                                   .gmFileHeaderColorpaletteArray[this->units[unitID].spriteID]
                                                   .originX;
            *(short*)&this->units[unitID].spriteOriginY = (short)DAT_TextureRenderCoreObject::instance
                                                         .gmFileHeaderColorpaletteArray[this->units[unitID].spriteID]
                                                         .originY;
            this->units[unitID].hitboxWidth
                = (short)DAT_UnitPropertiesDefinedData::instance.UNIT_SPRITE_DIMENSIONS[unitType][0];
            this->units[unitID].hitboxHeight
                = (short)DAT_UnitPropertiesDefinedData::instance.UNIT_SPRITE_DIMENSIONS[unitType][1];
            this->units[unitID].drawXOffset = this->units[unitID].spriteOriginX - this->units[unitID].hitboxWidth / 2;
            this->units[unitID].someDrawYOffset
                = ((short)this->units[unitID].spriteOriginY - this->units[unitID].hitboxHeight) + 3;
            this->units[unitID].movementSpeed
                = (short)DAT_UnitPropertiesDefinedData::instance.UNIT_MOVEMENT_SPEED_ARRAY[unitType];
            this->units[unitID].calculatedMovementSpeed = this->units[unitID].movementSpeed;
            this->units[unitID].moveTickCounter = 0;
            this->units[unitID].lastMoveStepTick = 0;
            this->units[unitID].maxHealth = DAT_UnitPropertiesDefinedData::instance.BASE_HP[unitType];
            this->units[unitID].health = this->units[unitID].maxHealth;
            int _healthPercentage;
            if (this->units[unitID].maxHealth == 0) {
                _healthPercentage = 100;
            } else {
                _healthPercentage = (this->units[unitID].health * 100) / this->units[unitID].maxHealth;
            }
            this->units[unitID].healthPercentage = (short)_healthPercentage;
            byte _firstNameIndex = this->units[unitID].firstNameIndex;
            this->units[unitID].healthbar = (short)_healthPercentage / 10;
            this->units[unitID].unitCanClimb = (short)DAT_UnitPropertiesDefinedData::instance.UNIT_CLIMB[unitType];
            this->units[unitID].someUnitStat4
                = (short)DAT_UnitPropertiesDefinedData::instance.SomeUnitStatMatrix4[unitType];
            this->units[unitID].graphicSize = (short)DAT_UnitPropertiesDefinedData::instance.GRAPHIC_SIZE[unitType];
            this->units[unitID].canMelee
                = (short)DAT_UnitPropertiesDefinedData::instance.UNIT_CAN_MELEE[unitType];
            this->units[unitID].enemyScanIntervalMask
                = DAT_UnitPropertiesDefinedData::instance.UNIT_ENEMY_NOTICE_RANGE[unitType];
            this->units[unitID].isMovable = (short)DAT_UnitPropertiesDefinedData::instance.UNIT_MOVABLE[unitType];
            if ((char)_firstNameIndex <= 0 || unitType == OpenSHC::Map::Units::UT_BREWER
                || unitType == OpenSHC::Map::Units::UT_TANNER || unitType == OpenSHC::Map::Units::UT_LADY
                || unitType == OpenSHC::Map::Units::UT_MOTHER || unitType == OpenSHC::Map::Units::UT_JUGGLER
                || unitType == OpenSHC::Map::Units::UT_FIREEATER || unitType == OpenSHC::Map::Units::UT_PRIEST) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::assignNameToUnit, this)(unitID);
            }
            short _owner = this->units[unitID].owner;
            if (_owner > 0) {
                this->units[unitID].ownerBitMask = (byte)(1 << (_owner - 1));
                this->units[unitID].occupancyClearMask = ~this->units[unitID].ownerBitMask;
            } else {
                this->units[unitID].ownerBitMask = 0xff;
                this->units[unitID].occupancyClearMask = 0xff;
            }
            this->units[unitID].isSelectable_OR_matchTime = 0;
            this->units[unitID].isRangedUnit = 0;
            if (unitType != OpenSHC::Map::Units::UT_CAGEDOG) {
                this->units[unitID].cooldownTicks = 500;
            }
            if (unitType == OpenSHC::Map::Units::UT_A_ASSASSIN) {
                this->units[unitID].assassinNearestSelectableEnemyDistance = 32000;
            }
        }

    }
}
}
