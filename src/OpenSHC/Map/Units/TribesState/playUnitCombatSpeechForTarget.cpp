#include "../TribesState.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_EntityDefinedData.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitType;

        // EntityTypeArrayForProjectileRange is declared uint, but the range test is signed (jle at 0x521B87).
        // The tribe size is read through DAT_TribesState::instance (0x521ABC), the majority type through this.
        // FUNCTION: STRONGHOLDCRUSADER 0x00521A90
        void TribesState::playUnitCombatSpeechForTarget(int selectionID, int unitID)
        {
            int count;
            int const selectedUnitID = MACRO_CALL_MEMBER(
                OpenSHC::Map::Units::UnitsState_Func::getRepresentativeSelectedUnitID, DAT_UnitsState::ptr)(1);
            UnitType const unitType = MACRO_CALL_MEMBER(
                OpenSHC::Map::Units::TribesState_Func::getMajoritySelectedUnitType, this)(selectionID, &count);
            int const tribeSize = DAT_TribesState::instance.tribes[selectionID].size;
            switch (unitType) {
            case UT_E_ARCHER:
            case UT_E_XBOW:
            case UT_A_ARCHER:
            case UT_A_SLINGER:
            case UT_A_HARCHER:
            case UT_A_FIRETHROWER: {
                int rangeSquared;
                if (unitType == UT_E_ARCHER) {
                    rangeSquared = DAT_EntityDefinedData::instance.EntityTypeArrayForProjectileRange[1]
                        * DAT_EntityDefinedData::instance.EntityTypeArrayForProjectileRange[1];
                } else if (unitType == UT_E_XBOW) {
                    rangeSquared = DAT_EntityDefinedData::instance.EntityTypeArrayForProjectileRange[7]
                        * DAT_EntityDefinedData::instance.EntityTypeArrayForProjectileRange[7];
                } else if (unitType == UT_A_ARCHER) {
                    rangeSquared = DAT_EntityDefinedData::instance.EntityTypeArrayForProjectileRange[1]
                        * DAT_EntityDefinedData::instance.EntityTypeArrayForProjectileRange[1];
                } else if (unitType == UT_A_SLINGER) {
                    rangeSquared = DAT_EntityDefinedData::instance.EntityTypeArrayForProjectileRange[0x21]
                        * DAT_EntityDefinedData::instance.EntityTypeArrayForProjectileRange[0x21];
                } else if (unitType == UT_A_HARCHER) {
                    rangeSquared = DAT_EntityDefinedData::instance.EntityTypeArrayForProjectileRange[1]
                        * DAT_EntityDefinedData::instance.EntityTypeArrayForProjectileRange[1];
                } else if (unitType == UT_A_FIRETHROWER) {
                    rangeSquared = DAT_EntityDefinedData::instance.EntityTypeArrayForProjectileRange[0x22]
                        * DAT_EntityDefinedData::instance.EntityTypeArrayForProjectileRange[0x22];
                } else {
                    // unreachable (the case labels admit only the six types above); the original loads unitID
                    rangeSquared = unitID;
                }
                int const selectedX = DAT_UnitsState::instance.units[selectedUnitID].x;
                int const targetX = DAT_UnitsState::instance.units[unitID].x;
                int const selectedY = DAT_UnitsState::instance.units[selectedUnitID].y;
                int const targetY = DAT_UnitsState::instance.units[unitID].y;
                int const deltaX = selectedX - targetX;
                int const deltaY = selectedY - targetY;
                if (deltaX * deltaX + deltaY * deltaY > rangeSquared) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playUnitSpeech, DAT_SFXState::ptr)(
                        unitType, 0x1e);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playUnitSpeech, DAT_SFXState::ptr)(
                        unitType, 0x19);
                }
                if (unitType != UT_A_HARCHER) {
                    return;
                }
                if (count == 1) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                        DAT_UnitsState::instance.units[selectedUnitID].x,
                        DAT_UnitsState::instance.units[selectedUnitID].y, 0xea);
                } else if (count <= 4) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                        DAT_UnitsState::instance.units[selectedUnitID].x,
                        DAT_UnitsState::instance.units[selectedUnitID].y, 0xeb);
                } else {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                        DAT_UnitsState::instance.units[selectedUnitID].x,
                        DAT_UnitsState::instance.units[selectedUnitID].y, 0xec);
                }
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                    DAT_UnitsState::instance.units[selectedUnitID].x, DAT_UnitsState::instance.units[selectedUnitID].y,
                    0x59);
                return;
            }
            case UT_E_KNIGHT:
                if (count == 1) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                        DAT_UnitsState::instance.units[selectedUnitID].x,
                        DAT_UnitsState::instance.units[selectedUnitID].y, 0x56);
                } else {
                    if (count == 2 || count == 3) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                            DAT_UnitsState::instance.units[selectedUnitID].x,
                            DAT_UnitsState::instance.units[selectedUnitID].y, 0x57);
                    }
                    if (count >= 4) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                            DAT_UnitsState::instance.units[selectedUnitID].x,
                            DAT_UnitsState::instance.units[selectedUnitID].y, 0x58);
                    }
                }
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                    DAT_UnitsState::instance.units[selectedUnitID].x, DAT_UnitsState::instance.units[selectedUnitID].y,
                    0x59);
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playUnitSpeech, DAT_SFXState::ptr)(
                    unitType, 0x15);
                if (tribeSize >= 15) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                        DAT_UnitsState::instance.units[selectedUnitID].x,
                        DAT_UnitsState::instance.units[selectedUnitID].y, 0xfa);
                }
                return;
            case UT_E_SWORD:
                if (count == 1) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                        DAT_UnitsState::instance.units[selectedUnitID].x,
                        DAT_UnitsState::instance.units[selectedUnitID].y, 0xad);
                } else if (count == 2) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                        DAT_UnitsState::instance.units[selectedUnitID].x,
                        DAT_UnitsState::instance.units[selectedUnitID].y, 0xae);
                } else if (count >= 3) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                        DAT_UnitsState::instance.units[selectedUnitID].x,
                        DAT_UnitsState::instance.units[selectedUnitID].y, 0xaf);
                }
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playUnitSpeech, DAT_SFXState::ptr)(
                    unitType, 0x15);
                if (tribeSize >= 15) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                        DAT_UnitsState::instance.units[selectedUnitID].x,
                        DAT_UnitsState::instance.units[selectedUnitID].y, 0x14);
                }
                return;
            case UT_E_SPEAR:
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playUnitSpeech, DAT_SFXState::ptr)(
                    unitType, 0x15);
                if (tribeSize >= 15) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                        DAT_UnitsState::instance.units[selectedUnitID].x,
                        DAT_UnitsState::instance.units[selectedUnitID].y, 0x14);
                }
                return;
            case UT_E_PIKE:
            case UT_E_MACE:
            case UT_E_MONK:
                if (DAT_UnitsState::instance.units[unitID].unitType == UT_E_KNIGHT
                    || DAT_UnitsState::instance.units[unitID].unitType == UT_E_SWORD
                    || DAT_UnitsState::instance.units[unitID].unitType == UT_LORD) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playUnitSpeech, DAT_SFXState::ptr)(
                        unitType, 0x11);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playUnitSpeech, DAT_SFXState::ptr)(
                        unitType, 0x15);
                }
                if (tribeSize >= 15) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                        DAT_UnitsState::instance.units[selectedUnitID].x,
                        DAT_UnitsState::instance.units[selectedUnitID].y, 0x14);
                }
                return;
            case UT_E_ENGINEER:
                return;
            case UT_A_SWORDSMAN:
                if (tribeSize >= 15) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                        DAT_UnitsState::instance.units[selectedUnitID].x,
                        DAT_UnitsState::instance.units[selectedUnitID].y, 0x14);
                }
                return;
            default:
                if (DAT_UnitsState::instance.units[unitID].unitType == UT_E_KNIGHT
                    || DAT_UnitsState::instance.units[unitID].unitType == UT_E_SWORD
                    || DAT_UnitsState::instance.units[unitID].unitType == UT_E_MACE
                    || DAT_UnitsState::instance.units[unitID].unitType == UT_E_PIKE
                    || DAT_UnitsState::instance.units[unitID].unitType == UT_LORD) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playUnitSpeech, DAT_SFXState::ptr)(
                        unitType, 0x11);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playUnitSpeech, DAT_SFXState::ptr)(
                        unitType, 0x15);
                }
                return;
            }
        }

    }
}
}
