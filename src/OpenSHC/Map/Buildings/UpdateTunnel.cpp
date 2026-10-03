#include "../../Map.func.hpp"
#include "../Buildings.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/States/UnitStateShort.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::DE::SHCDE::eSFX;
    using OpenSHC::Map::Units::States::UnitState;
    using OpenSHC::Map::Units::States::UnitStateShort;

    // FUNCTION: STRONGHOLDCRUSADER 0x00417FD0
    void Buildings::UpdateTunnel()
    {
        UnitStateShort UVar1;
        int iVar2;
        int iVar3;
        short _unitID;
        iVar2 = DAT_CurrentBuildingID::instance;
        _unitID = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].unitRefID;
        UVar1 = DAT_UnitsState::instance.units[_unitID].state.generic;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIncrement = 1;
        if (((UVar1 == ((UnitState)3)) || (UVar1 == OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk))
            || (DAT_UnitsState::instance.units[_unitID].dying != 0)) {
            DAT_BuildingsState::instance.buildings[iVar2].animationIndex = 0;
            DAT_BuildingsState::instance.buildings[iVar2].renderAnimation = 0;
        } else {
            if (UVar1 != (OpenSHC::Map::Units::States::US_STAND_UPUnk | OpenSHC::Map::Units::States::US_IDLEUnk)) {
                DAT_BuildingsState::instance.buildings[iVar2].animationIndex = 0;
                DAT_BuildingsState::instance.buildings[iVar2].renderAnimation = 1;
                DAT_BuildingsState::instance.buildings[iVar2].animationFrame
                    = (int)(char)DAT_BuildingDefinedData::instance
                          .field95_0x5a18[DAT_BuildingsState::instance.buildings[iVar2].animationIndex];
            }
            DAT_BuildingsState::instance.buildings[iVar2].renderAnimation = 1;
            if (DAT_BuildingDefinedData::instance
                    .field95_0x5a18[DAT_BuildingsState::instance.buildings[iVar2].animationIndex]
                == 0xff) {
                DAT_BuildingsState::instance.buildings[iVar2].renderAnimation = 0;
                DAT_BuildingsState::instance.buildings[iVar2].animationIndex = 0;
                DAT_UnitsState::instance.units[_unitID].state.generic = ((UnitState)3);
                DAT_UnitsState::instance.units[_unitID].tunnelerFinishedDigging = 2;
            }
            iVar3 = (int)(char)DAT_BuildingDefinedData::instance
                        .field95_0x5a18[DAT_BuildingsState::instance.buildings[iVar2].animationIndex];
            DAT_BuildingsState::instance.buildings[iVar2].animationFrame = iVar3;
            if (((iVar3 == 10) || (iVar3 == 0x19))
                && (DAT_BuildingsState::instance.buildings[iVar2].animationActive != 0)) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    (int)(short)DAT_BuildingsState::instance.buildings[iVar2].x,
                    (int)((int)((short)DAT_BuildingsState::instance.buildings[iVar2].y)), OpenSHC::DE::SHCDE::FX_DIG2);
            }
        }
    }

}
}
