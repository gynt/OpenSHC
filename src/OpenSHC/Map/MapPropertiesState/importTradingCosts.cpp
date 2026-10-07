#include "../../Map.func.hpp"
#include "../MapPropertiesState.func.hpp"

#include "OpenSHC/Game/Market/BuySellPair.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"

namespace OpenSHC {
namespace Map {
    using Game::Market::BuySellPair;

    // FUNCTION: STRONGHOLDCRUSADER 0x004B7800
    void MapPropertiesState::importTradingCosts()
    {
        BuySellPair* pBVar1;
        int _indexUpTo25;
        TradeableResourcesSection* _ptr;
        int _buyPrice;
        int _salesPrice;
        _ptr = &this->SEC_Section1065;
        DAT_GameState::instance.mapAndTime.field1363_0x71c = 0;
        DAT_GameState::instance.mapAndTime.field1364_0x720 = 0;
        DAT_GameState::instance.mapAndTime.traderRelated1 = 10;
        DAT_GameState::instance.mapAndTime.traderRelatedCounter2 = 6;
        DAT_GameState::instance.mapAndTime.traderRelated2 = 0;
        DAT_GameState::instance.mapAndTime.traderRelatedCounter1 = 0;
        pBVar1 = DAT_GameState::instance.mapAndTime.copyOfBuyAndSalesPrice;
        _indexUpTo25 = 0;
        do {
            _buyPrice = *(int*)((int)DAT_RenderingDefinedData::instance.BuyPricePerResource + _indexUpTo25);
            /*
              this one is used in game
             */
            pBVar1[0x19].buyPrice = _buyPrice;
            pBVar1->buyPrice = _buyPrice;
            _salesPrice = *(int*)((int)DAT_RenderingDefinedData::instance.SalesPricePerResource + _indexUpTo25);
            pBVar1[0x19].salesPrice = _salesPrice;
            pBVar1->salesPrice = _salesPrice;
            *(undefined4*)((int)DAT_GameState::instance.mapAndTime.unknownResouceFlagArray1 + _indexUpTo25) = 0;
            *(undefined4*)((int)DAT_GameState::instance.mapAndTime.unknownResourceFlagArray2 + _indexUpTo25) = 0;
            *(BOOLEnum*)((int)DAT_GameState::instance.mapAndTime.isResourceTradeable + _indexUpTo25)
                = _ptr->tradeabilityArray[0];
            pBVar1 = pBVar1 + 1;
            _indexUpTo25 = _indexUpTo25 + 4;
            _ptr = (TradeableResourcesSection*)(_ptr->tradeabilityArray + 1);
        } while ((int)pBVar1 < 0x117cfd4);
    }

}
}
