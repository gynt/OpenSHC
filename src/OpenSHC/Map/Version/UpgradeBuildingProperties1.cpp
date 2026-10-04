#include "../../Map.func.hpp"
#include "../Version.func.hpp"

#include "OpenSHC/Map/Buildings/Building.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace Map {

    using Map::Buildings::Building;
    using Map::Buildings::BuildingLogicalState;

    // FUNCTION: STRONGHOLDCRUSADER 0x0041A140
    void Version::UpgradeBuildingProperties1(int version)
    {
        short sVar1;
        Building* _pBuilding;
        int _buildingType;
        _pBuilding = &DAT_BuildingsState::instance.buildings[1];
        do {
            if (_pBuilding->logicalState != ((BuildingLogicalState)0)) {
                _buildingType = (int)(short)_pBuilding->buildingType;
                *(short*)&_pBuilding->spriteSheetID
                    = DAT_BuildingDefinedData::instance.Building_SpriteSheet_ID_Array_1[_buildingType].shortValue;
                switch (_buildingType) {
                case 1:
                    if (version < 0x8c) {
                        _pBuilding->spriteID
                            = DAT_BuildingDefinedData::instance.Building_Sprite_ID_Array_1[_buildingType];
                    }
                    break;
                case 0x27:
                case 0x42:
                case 0x5b:
                case 100:
                case 0x65:
                case 0x68:
                    break;
                default:
                    _pBuilding->spriteID = DAT_BuildingDefinedData::instance.Building_Sprite_ID_Array_1[_buildingType];
                    break;
                }
                _pBuilding->visuallyActiveSpriteID
                    = DAT_BuildingDefinedData::instance.VisuallyActiveSpriteIDOffsets[_buildingType];
                _pBuilding->gfxOffset = DAT_BuildingDefinedData::instance.GFXOffsets[_buildingType];
                _pBuilding->gfxOffset2 = DAT_BuildingDefinedData::instance.Building_Sprite_ID_Array_2[_buildingType];
                _pBuilding->gfxOffset3 = DAT_BuildingDefinedData::instance.GFXOffsets3[_buildingType];
                _pBuilding->unknownFlag4 = DAT_BuildingDefinedData::instance.field18_0x192c[_buildingType].byteValue;
                _pBuilding->spriteOffetX = DAT_BuildingDefinedData::instance.SpriteOffsets1[_buildingType][0][0];
                _pBuilding->spriteOffetY = DAT_BuildingDefinedData::instance.SpriteOffsets1[_buildingType][1][0];
                _pBuilding->animAdvanceThrottle = DAT_BuildingDefinedData::instance.AnimAdvanceThrottles[_buildingType];
                _pBuilding->spriteID2 = DAT_BuildingDefinedData::instance.SpriteIDs2[_buildingType].shortValue;
                if (_pBuilding->currentHealth == _pBuilding->maxHealth) {
                    sVar1 = DAT_BuildingDefinedData::instance.BuildingHP[_buildingType].shortValue;
                    _pBuilding->maxHealth = sVar1;
                    _pBuilding->currentHealth = sVar1;
                }
                _pBuilding->oldVisualActiveState = -1;
            }
            _pBuilding = _pBuilding + 0x196;
            if (0x1124dc5 < (int)_pBuilding) {}
        } while (true);
    }

}
}
