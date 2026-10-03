#include "../../Game.func.hpp"
#include "../Skirmish.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_SkMasterDataEntry.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x004C6CD0
    int Skirmish::StoreLocalTime()
    {
        _SYSTEMTIME local_10;
        GetLocalTime(&local_10);
        DAT_SkMasterDataEntry::instance.localTimeDay = (uint)local_10.wDay;
        DAT_SkMasterDataEntry::instance.localTimeYear = (uint)local_10.wYear;
        DAT_SkMasterDataEntry::instance.localTimeMonth = (uint)local_10.wMonth;
        DAT_SkMasterDataEntry::instance.gameDurationInMinutes = (int)DAT_GameCore::instance.gameDuration / 60000;
        DAT_SkMasterDataEntry::instance.mapTimeInTicks = DAT_GameCore::instance.mapTimeInTicks;
        return DAT_GameCore::instance.gameDuration * 0x45e7b273;
    }

}
}
