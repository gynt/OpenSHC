#include "../../Map.func.hpp"

#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

namespace OpenSHC {
namespace Map {

    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004BE590
    void MapPropertiesState::setStartingYearAndStartingResources()
    {
        int iVar1;
        short* psVar2;
        char local_10[12];
        uint local_4;
        local_4 = MSVC_SecurityCookie::instance ^ (uint)local_10;
        DAT_MapPropertiesState::instance.SEC_StartingYear = 1181;
        DAT_GameState::instance.mapAndTime.year = 1181;
        DAT_MapPropertiesState::instance.SEC_StartingResources[0] = 0;
        DAT_MapPropertiesState::instance.SEC_StartingResources[1] = 0;
        DAT_MapPropertiesState::instance.SEC_StartingResources[2] = 0;
        DAT_MapPropertiesState::instance.SEC_StartingResources[3] = 0;
        DAT_MapPropertiesState::instance.SEC_StartingResources[4] = 0;
        DAT_MapPropertiesState::instance.SEC_StartingResources[5] = 0;
        DAT_MapPropertiesState::instance.SEC_StartingResources[6] = 0;
        DAT_MapPropertiesState::instance.SEC_StartingResources[7] = 0;
        DAT_MapPropertiesState::instance.SEC_StartingResources[8] = 0;
        DAT_MapPropertiesState::instance.SEC_StartingResources[9] = 0;
        DAT_MapPropertiesState::instance.SEC_StartingResources[10] = 0;
        DAT_MapPropertiesState::instance.SEC_StartingResources[0xb] = 0;
        DAT_MapPropertiesState::instance.SEC_StartingResources[0xc] = 0;
        DAT_MapPropertiesState::instance.SEC_StartingResources[0xd] = 0;
        DAT_MapPropertiesState::instance.SEC_StartingResources[0xe] = 0;
        DAT_MapPropertiesState::instance.SEC_StartingResources[0xf] = 0;
        DAT_MapPropertiesState::instance.SEC_StartingResources[0x10] = 0;
        DAT_MapPropertiesState::instance.SEC_StartingResources[0x11] = 0;
        DAT_MapPropertiesState::instance.SEC_StartingResources[0x12] = 0;
        DAT_MapPropertiesState::instance.SEC_StartingResources[0x13] = 0;
        DAT_MapPropertiesState::instance.SEC_StartingResources[0x14] = 0;
        DAT_MapPropertiesState::instance.SEC_StartingResources[0x15] = 0;
        DAT_MapPropertiesState::instance.SEC_StartingResources[0x16] = 0;
        DAT_MapPropertiesState::instance.SEC_StartingResources[0x17] = 0;
        DAT_MapPropertiesState::instance.SEC_StartingResources[0x18] = 0;
        DAT_MapPropertiesState::instance.SEC_Section1065.tradeabilityArray[0] = TRUE;
        DAT_MapPropertiesState::instance.SEC_Section1065.tradeabilityArray[1] = TRUE;
        DAT_MapPropertiesState::instance.SEC_Section1065.tradeabilityArray[2] = TRUE;
        DAT_MapPropertiesState::instance.SEC_Section1065.tradeabilityArray[3] = TRUE;
        DAT_MapPropertiesState::instance.SEC_Section1065.tradeabilityArray[4] = TRUE;
        DAT_MapPropertiesState::instance.SEC_Section1065.tradeabilityArray[5] = TRUE;
        DAT_MapPropertiesState::instance.SEC_Section1065.tradeabilityArray[6] = TRUE;
        DAT_MapPropertiesState::instance.SEC_Section1065.tradeabilityArray[7] = TRUE;
        DAT_MapPropertiesState::instance.SEC_Section1065.tradeabilityArray[8] = TRUE;
        DAT_MapPropertiesState::instance.SEC_Section1065.tradeabilityArray[9] = TRUE;
        DAT_MapPropertiesState::instance.SEC_Section1065.tradeabilityArray[10] = TRUE;
        DAT_MapPropertiesState::instance.SEC_Section1065.tradeabilityArray[0xb] = TRUE;
        DAT_MapPropertiesState::instance.SEC_Section1065.tradeabilityArray[0xc] = TRUE;
        DAT_MapPropertiesState::instance.SEC_Section1065.tradeabilityArray[0xd] = TRUE;
        DAT_MapPropertiesState::instance.SEC_Section1065.tradeabilityArray[0xe] = TRUE;
        DAT_MapPropertiesState::instance.SEC_Section1065.tradeabilityArray[0xf] = TRUE;
        DAT_MapPropertiesState::instance.SEC_Section1065.tradeabilityArray[0x10] = TRUE;
        DAT_MapPropertiesState::instance.SEC_Section1065.tradeabilityArray[0x11] = TRUE;
        DAT_MapPropertiesState::instance.SEC_Section1065.tradeabilityArray[0x12] = TRUE;
        DAT_MapPropertiesState::instance.SEC_Section1065.tradeabilityArray[0x13] = TRUE;
        DAT_MapPropertiesState::instance.SEC_Section1065.tradeabilityArray[0x14] = TRUE;
        DAT_MapPropertiesState::instance.SEC_Section1065.tradeabilityArray[0x15] = TRUE;
        DAT_MapPropertiesState::instance.SEC_Section1065.tradeabilityArray[0x16] = TRUE;
        DAT_MapPropertiesState::instance.SEC_Section1065.tradeabilityArray[0x17] = TRUE;
        DAT_MapPropertiesState::instance.SEC_Section1065.tradeabilityArray[0x18] = TRUE;
        DAT_MapPropertiesState::instance.SEC_StartingMonth = 0;
        DAT_GameState::instance.mapAndTime.month = 0;
        DAT_MapPropertiesState::instance.eventsCount = 0;
        DAT_MapPropertiesState::instance.SEC_SiegeInformation.archers = 0;
        DAT_MapPropertiesState::instance.SEC_SiegeInformation.crossbowmen = 0;
        DAT_MapPropertiesState::instance.SEC_SiegeInformation.spearmen = 0;
        DAT_MapPropertiesState::instance.SEC_SiegeInformation.pikemen = 0;
        DAT_MapPropertiesState::instance.SEC_SiegeInformation.macemen = 0;
        DAT_MapPropertiesState::instance.SEC_SiegeInformation.swordsmen = 0;
        DAT_MapPropertiesState::instance.SEC_SiegeInformation.knights = 0;
        DAT_MapPropertiesState::instance.SEC_SiegeInformation.laddermen = 0;
        DAT_MapPropertiesState::instance.SEC_SiegeInformation.engineers = 0;
        DAT_MapPropertiesState::instance.SEC_SiegeInformation.monks = 0;
        DAT_MapPropertiesState::instance.SEC_SiegeInformation.arabianArchers = 0;
        DAT_MapPropertiesState::instance.SEC_SiegeInformation.slaves = 0;
        DAT_MapPropertiesState::instance.SEC_SiegeInformation.slingers = 0;
        DAT_MapPropertiesState::instance.SEC_SiegeInformation.assassins = 0;
        DAT_MapPropertiesState::instance.SEC_SiegeInformation.horseArchers = 0;
        DAT_MapPropertiesState::instance.SEC_SiegeInformation.arabianSwordsmen = 0;
        DAT_MapPropertiesState::instance.SEC_SiegeInformation.fireThrowers = 0;
        DAT_MapPropertiesState::instance.SEC_SiegeInformation.fireBallistas = 0;
        DAT_MapPropertiesState::instance.SEC_SiegeInformation.field18_0x48 = 0;
        DAT_MapPropertiesState::instance.SEC_SiegeInformation.field19_0x4c = 0;
        DAT_MapPropertiesState::instance.SEC_Section1067.field0_0x0 = 0;
        DAT_MapPropertiesState::instance.SEC_Section1067.field1_0x4 = 0;
        DAT_MapPropertiesState::instance.SEC_Section1067.field2_0x8 = 0;
        DAT_MapPropertiesState::instance.SEC_Section1067.field3_0xc = 0;
        DAT_MapPropertiesState::instance.SEC_Section1067.field4_0x10 = 0;
        DAT_MapPropertiesState::instance.SEC_Section1067.field5_0x14 = 0;
        DAT_MapPropertiesState::instance.SEC_StartingPopularity = 100;
        MACRO_CALL_MEMBER(Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(10);
        MACRO_CALL(OS_Func::_sprintf)(local_10, "%d", DAT_MapPropertiesState::instance.SEC_StartingYear);
        MACRO_CALL_MEMBER(Text::UserTextHandler_Func::copyIntoTextArray, DAT_UserTextHandlerState::ptr)(
            local_10);
        DAT_MapPropertiesState::instance.field48_0x13560 = -1;
        DAT_MapPropertiesState::instance.field47_0x1355c = 0;
        psVar2 = DAT_MapPropertiesState::instance.buildingAvailability;
        /*
          bitmask for setting the availability of two shorts
         */
        for (iVar1 = 50; iVar1 != 0; iVar1 = iVar1 + -1) {
            psVar2[0] = 1;
            psVar2[1] = 1;
            psVar2 = psVar2 + 2;
        }
        MACRO_CALL_MEMBER(Map::MapPropertiesState_Func::commitBuildingAvailability, this)();
        MACRO_CALL_MEMBER(Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(9);
        ;
    }

}
}
