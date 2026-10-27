#include "OpenSHC/Map/MapPropertiesState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueDefinedData.hpp"

namespace OpenSHC {
namespace Map {

    // Per resource (25): buyAndSalesPriceArray[i] (= copyOfBuyAndSalesPrice[i + 25], the original addresses it
    // from the copy pointer, [eax+0xC8] at 0x4B7846) is written before copyOfBuyAndSalesPrice[i] (0x4B784C).
    // FUNCTION: STRONGHOLDCRUSADER 0x004B7800
    void MapPropertiesState::importTradingCosts()
    {
        DAT_GameState::instance.mapAndTime.traderFlag71c = 0;
        DAT_GameState::instance.mapAndTime.traderValue720 = 0;
        DAT_GameState::instance.mapAndTime.traderReturnDelayWeeks = 10;
        DAT_GameState::instance.mapAndTime.traderSpawnIntervalWeeks = 6;
        DAT_GameState::instance.mapAndTime.traderState = 0;
        DAT_GameState::instance.mapAndTime.traderWeekCounter = 0;
        for (int i = 0; i < 25; i++) {
            DAT_GameState::instance.mapAndTime.copyOfBuyAndSalesPrice[i].buyPrice
                = DAT_GameState::instance.mapAndTime.copyOfBuyAndSalesPrice[i + 25].buyPrice
                = DAT_TroopValueDefinedData::instance.BuyPricePerResource[i];
            DAT_GameState::instance.mapAndTime.copyOfBuyAndSalesPrice[i].salesPrice
                = DAT_GameState::instance.mapAndTime.copyOfBuyAndSalesPrice[i + 25].salesPrice
                = DAT_TroopValueDefinedData::instance.SalesPricePerResource[i];
            DAT_GameState::instance.mapAndTime.unknownResouceFlagArray1[i] = 0;
            DAT_GameState::instance.mapAndTime.unknownResourceFlagArray2[i] = 0;
            DAT_GameState::instance.mapAndTime.isResourceTradeable[i] = this->SEC_Section1065.tradeabilityArray[i];
        }
    }

}
}
