#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/WildlifeState.func.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_WildlifeState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::SomeTribeBehaviorType;
        using OpenSHC::Map::Units::Instructions::UnitMatchSpeedEnum;
        using OpenSHC::UI::Enums::MenuViewType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0052B630
        void TribesState::updateCamelTribeBehavior(int param_1)
        {
            short* psVar1;
            SomeTribeBehaviorTypeShort SVar2;
            BOOLEnum BVar3;
            int iVar4;
            short sVar5;
            BVar3 = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::isTribeFreeOfTunnelingUnits, this)(
                param_1, this->tribes[param_1].uid);
            psVar1 = &this->tribes[param_1].unknownCounter01;
            *psVar1 = *psVar1 + 1;
            sVar5 = this->tribes[param_1].unknownCounter01;
            this->tribes[param_1].unkIsAnimalTribe = 1;
            if (7999 < sVar5) {
                this->tribes[param_1].unknownCounter01 = 4000;
            }
            if ((BVar3 != FALSE)
                && (iVar4 = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::trySpawnAdditionalWildlifeForTribe,
                        this)(param_1, 1000, 10, 0x2f),
                    iVar4 != 0)) {
                this->tribes[param_1].field64_0x204 = 1;
                this->tribes[param_1].unknownAttackRelatedUpdateCounter = 0;
            }
            sVar5 = this->tribes[param_1].field64_0x204;
            if (sVar5 == 0) {
                sVar5 = this->tribes[param_1].selectionTargetUnitID;
                this->tribes[param_1].unknownAttackRelatedUpdateCounter = 0;
                this->tribes[param_1].field64_0x204 = 2;
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::giveTribeMoveInstruction, this)(param_1,
                    (uint)((int)((int)DAT_UnitsState::instance.units[sVar5].x)),
                    (uint)((int)((int)DAT_UnitsState::instance.units[sVar5].y)), 0, 0,
                    OpenSHC::Map::Units::Instructions::UMSE_0);
                this->tribes[param_1].tribeBehaviorType = OpenSHC::Map::Units::STBT_1;
            }
            if (DAT_GameCore::instance.currentMenuViewType != OpenSHC::UI::Enums::MVT_MAP_EDITOR_LANDSCAPING) {
                if (sVar5 == 1) {
                    this->tribes[param_1].unknownAttackRelatedUpdateCounter = 0;
                    this->tribes[param_1].field64_0x204 = 2;
                    MACRO_CALL_MEMBER(OpenSHC::Map::WildlifeState_Func::findAndSetNewRallyPointForDeerAndLions,
                        DAT_WildlifeState::ptr)(param_1, 2, 0);
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::standUpAllTribeUnits, this)(param_1);
                    sVar5 = this->tribes[param_1].currentRallyPointIndex;
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::giveTribeMoveInstruction, this)(param_1,
                        (uint)((int)((int)this->tribes[param_1].rallyPointArray[sVar5][0])),
                        (uint)((int)((int)this->tribes[param_1].rallyPointArray[sVar5][1])), 0, 0,
                        OpenSHC::Map::Units::Instructions::UMSE_0);
                    psVar1 = &this->tribes[param_1].currentRallyPointIndex;
                    *psVar1 = *psVar1 + 1;
                    if (this->tribes[param_1].rallyPointCount <= this->tribes[param_1].currentRallyPointIndex) {
                        this->tribes[param_1].rallyPointCount = 0;
                        this->tribes[param_1].tribeBehaviorType = OpenSHC::Map::Units::STBT_1;
                    }
                    this->tribes[param_1].tribeBehaviorType = OpenSHC::Map::Units::STBT_1;
                }
                SVar2 = this->tribes[param_1].tribeBehaviorType;
                if (SVar2 == ((SomeTribeBehaviorType)0)) {
                    sVar5 = this->tribes[param_1].unknownAttackRelatedUpdateCounter;
                    this->tribes[param_1].unknownAttackRelatedUpdateCounter = sVar5 + 1;
                    if (sVar5 == 0) {
                        MACRO_CALL_MEMBER(OpenSHC::Map::WildlifeState_Func::findAndSetNewRallyPointForDeerAndLions,
                            DAT_WildlifeState::ptr)(param_1, 2, 1);
                        if (0 < this->tribes[param_1].rallyPointCount) {
                            MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::standUpAllTribeUnits, this)(
                                param_1);
                            iVar4 = (int)this->tribes[param_1].rallyPointCount;
                            MACRO_CALL_MEMBER(
                                OpenSHC::Map::Units::TribesState_Func::giveUnitSelectionMoveInstructionNoMatchedSpeed,
                                this)(param_1, (uint)((int)((int)this->tribes[param_1].rallyPointArray[iVar4 + -1][0])),
                                (uint)((int)((int)this->tribes[param_1].rallyPointArray[iVar4 + -1][1])), 0, 0);
                        }
                    } else if (BVar3 != FALSE) {
                        this->tribes[param_1].tribeBehaviorType = OpenSHC::Map::Units::STBT_1;
                        this->tribes[param_1].unknownAttackRelatedUpdateCounter = 0;
                    }
                } else if (SVar2 == OpenSHC::Map::Units::STBT_1) {
                    sVar5 = 800;
                    if (this->tribes[param_1].unknownCounter01 < 0x65) {
                        sVar5 = 10;
                    }
                    psVar1 = &this->tribes[param_1].unknownAttackRelatedUpdateCounter;
                    *psVar1 = *psVar1 + 1;
                    if (sVar5 <= this->tribes[param_1].unknownAttackRelatedUpdateCounter) {
                        this->tribes[param_1].tribeBehaviorType = ((SomeTribeBehaviorType)0);
                        this->tribes[param_1].unknownAttackRelatedUpdateCounter = 0;
                    }
                }
            }
            this->tribes[param_1].unknownCounter01 = 0;
        }

    }
}
}
