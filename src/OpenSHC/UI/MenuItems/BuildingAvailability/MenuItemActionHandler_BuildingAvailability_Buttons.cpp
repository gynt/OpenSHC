#include "../BuildingAvailability.func.hpp"

#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MissionAestheticsDefinedData.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using UI::Enums::MenuModalType;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004BB2C0
        void BuildingAvailability::MenuItemActionHandler_BuildingAvailability_Buttons(int param_1, ...)
        {
            if (param_1 < 1000) {
                if (param_1 < 2000)
                    goto LAB_004bb359;
            } else if (param_1 < 2000) {
                DAT_MapPropertiesState::instance
                    .buildingAvailability[DAT_MissionAestheticsDefinedData::instance.BuildingAvailabilityRowOrder
                            [DAT_MapPropertiesState::instance.DAT_BuildingAvailabilityScrollbarOffset + param_1]]
                    = DAT_MapPropertiesState::instance
                          .buildingAvailability[DAT_MissionAestheticsDefinedData::instance.BuildingAvailabilityRowOrder
                                  [DAT_MapPropertiesState::instance.DAT_BuildingAvailabilityScrollbarOffset + param_1]]
                    ^ 1;
            }
            if (param_1 < 3000) {
                switch (DAT_MissionAestheticsDefinedData::instance
                        .BuildingNameRelatedStructArray[DAT_MissionAestheticsDefinedData::instance.field1224_0x218c
                                [DAT_MapPropertiesState::instance.DAT_BuildingAvailabilityScrollbarOffset + param_1]]
                        .field1_0x4[0]
                        .identifier1) {
                case 0x32:
                case 0x52:
                case 0x53:
                    MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                        DAT_MenuModalComposition1::ptr)(UI::Enums::MMT_DISABLE_WEAPON, FALSE);
                    return;
                default:
                    return;
                case 0x56:
                    MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                        DAT_MenuModalComposition1::ptr)(UI::Enums::MMT_DISABLE_ARAB_TROOPS, FALSE);
                    return;
                case 0x57:
                    MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                        DAT_MenuModalComposition1::ptr)(UI::Enums::MMT_DISABLE_EURO_TROOPS, FALSE);
                }
            }
        LAB_004bb359:
            if (param_1 == -2) {
                if (DAT_MapPropertiesState::instance.DAT_BuildingAvailabilityScrollbarOffset
                    < DAT_MapPropertiesState::instance.buildingAvailabilityRowCount + -0x13) {
                    DAT_MapPropertiesState::instance.DAT_BuildingAvailabilityScrollbarOffset
                        = DAT_MapPropertiesState::instance.DAT_BuildingAvailabilityScrollbarOffset + 1;
                }
            } else if (param_1 == -1) {
                if (0 < DAT_MapPropertiesState::instance.DAT_BuildingAvailabilityScrollbarOffset) {
                    DAT_MapPropertiesState::instance.DAT_BuildingAvailabilityScrollbarOffset
                        = DAT_MapPropertiesState::instance.DAT_BuildingAvailabilityScrollbarOffset + -1;
                }
            } else if (param_1 == 0x25) {
                MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition1::ptr)(UI::Enums::MMT_NONE, FALSE);
            }
        }

    }
}
}
