#include "../SiegeAttackingForceAndStartGoods.func.hpp"

#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition2.hpp"
#include "OpenSHC/Globals/DAT_MissionAestheticsDefinedData.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Map::MapType2;
        using OpenSHC::UI::Enums::MenuModalType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004BA5C0
        void SiegeAttackingForceAndStartGoods::MenuItemActionHandler_SiegeAttackingForceAndStartGoods_Main(
            int param_1, ...)
        {
            int iVar1;
            char** maximum;
            if (param_1 < 0) {
                iVar1 = -param_1 + -1;
                if (iVar1 < 0x14) {
                    if (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == OpenSHC::Map::MT_SIEGE) {
                        return;
                    }
                } else if ((iVar1 < 0x1e)
                    && (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 != OpenSHC::Map::MT_SIEGE)) {
                    return;
                }
                DAT_MapPropertiesState::instance.indexStored = iVar1;
                if (iVar1 < 0x14) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::MenuModalComposition_Func::setSliderParameters, DAT_MenuModalComposition2::ptr)(0,
                        *(int*)((int)DAT_MissionAestheticsDefinedData::ptr + iVar1 * 4 + 0x34b4),
                        (int)((int)(DAT_MapPropertiesState::instance.SEC_StartingResources[*(
                            int*)(DAT_MissionAestheticsDefinedData::ptr + iVar1 * 4 + 0x345c)])),
                        (undefined*)((int)(

                            (DAT_MapPropertiesState::instance.SEC_StartingResources
                                + *(int*)((int)DAT_MissionAestheticsDefinedData::ptr + iVar1 * 4 + 0x345c)))),
                        (void*)MACRO_CALL(OpenSHC::UI::Helpers_Func::SumUnitPoints));
                    DAT_MenuModalComposition2::instance.textIndex
                        = DAT_MissionAestheticsDefinedData::instance
                              .field1239_0x3554[DAT_MapPropertiesState::instance.indexStored];
                    DAT_MenuModalComposition2::instance.textGroup = 199;
                    MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::setExtraActiveModalDialog,
                        DAT_MenuModalComposition2::ptr)(OpenSHC::UI::Enums::MMT_OVERLAY_SLIDER,
                        (int)((int)(DAT_ButtonX::instance + -0x25)), (int)((int)(DAT_ButtonY::instance + 0x19)));
                    return;
                }
                if (iVar1 < 0x1e) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::MapPropertiesState_Func::sumUnitPoints, DAT_MapPropertiesState::ptr)();
                    iVar1 = (DAT_MapPropertiesState::instance
                                    .SEC_StartingResources[DAT_MapPropertiesState::instance.indexStored + 5]
                                - DAT_MapPropertiesState::instance.DAT_MapEditorUnitPointsSum)
                        + 500;
                    if (DAT_MissionAestheticsDefinedData::instance
                            .field1239_0x3554[DAT_MapPropertiesState::instance.indexStored]
                        < iVar1) {
                        iVar1 = DAT_MissionAestheticsDefinedData::instance
                                    .field1239_0x3554[DAT_MapPropertiesState::instance.indexStored];
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::setSliderParameters,
                        DAT_MenuModalComposition2::ptr)(0, iVar1,
                        (int)((int)(DAT_MapPropertiesState::instance
                                .SEC_StartingResources[DAT_MapPropertiesState::instance.indexStored + 5])),
                        (undefined*)((int)(

                            (DAT_MapPropertiesState::instance.SEC_StartingResources
                                + DAT_MapPropertiesState::instance.indexStored + 5))),
                        (void*)MACRO_CALL(OpenSHC::UI::Helpers_Func::SumUnitPoints));
                    DAT_MenuModalComposition2::instance.textIndex
                        = DAT_MissionAestheticsDefinedData::instance
                              .InvasionUnitLimits[DAT_MapPropertiesState::instance.indexStored + 4];
                } else {
                    if (iVar1 == 0x1e) {
                        return;
                    }
                    if (9 < -param_1 - 0x29U) {
                        return;
                    }
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::MapPropertiesState_Func::sumUnitPoints, DAT_MapPropertiesState::ptr)();
                    maximum = (char**)((DAT_MapPropertiesState::instance
                                               .SEC_StartingResources[DAT_MapPropertiesState::instance.indexStored + 5]
                                           - DAT_MapPropertiesState::instance.DAT_MapEditorUnitPointsSum)
                        + 500);
                    if ((int)(&DAT_MissionAestheticsDefinedData::instance
                                .field614_0x9a8)[DAT_MapPropertiesState::instance.indexStored]
                        < (int)maximum) {
                        maximum = (&DAT_MissionAestheticsDefinedData::instance
                                .field614_0x9a8)[DAT_MapPropertiesState::instance.indexStored];
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::setSliderParameters,
                        DAT_MenuModalComposition2::ptr)(0, (int)((int)(maximum)),
                        (int)((int)(DAT_MapPropertiesState::instance
                                .SEC_StartingResources[DAT_MapPropertiesState::instance.indexStored + 5])),
                        (undefined*)((int)(

                            (DAT_MapPropertiesState::instance.SEC_StartingResources
                                + DAT_MapPropertiesState::instance.indexStored + 5))),
                        (void*)MACRO_CALL(OpenSHC::UI::Helpers_Func::SumUnitPoints));
                    DAT_MenuModalComposition2::instance.textIndex = (int)(&DAT_MissionAestheticsDefinedData::instance
                            .field1182_0x1288)[DAT_MapPropertiesState::instance.indexStored];
                }
                DAT_MenuModalComposition2::instance.textGroup = 199;
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::setExtraActiveModalDialog,
                    DAT_MenuModalComposition2::ptr)(OpenSHC::UI::Enums::MMT_OVERLAY_SLIDER,
                    (int)((int)(DAT_ButtonX::instance + -0x25)), (int)((int)(DAT_ButtonY::instance + 0x19)));
            } else if (param_1 == 0x25) {
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
                return;
            }
            return;
        }

    }
}
}
