#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00519310
        void TroopValueState::computeAttackWaveTroopComposition()
        {
            if (DAT_TroopValueState::instance.attackInfo.fightingTribeCount < 6) {
                DAT_TroopValueState::instance.attackInfo.field_0x20f44
                    = DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen;
                DAT_TroopValueState::instance.attackInfo.field_0x20f48 = 1;
                DAT_TroopValueState::instance.attackInfo.field_0x20f4c = 1;
                DAT_TroopValueState::instance.attackInfo.field_0x20f54 = 1;
                DAT_TroopValueState::instance.attackInfo.field_0x20f58 = 1;
                DAT_TroopValueState::instance.attackInfo.field_0x20f5c = 0;
                DAT_TroopValueState::instance.attackInfo.field_0x20f40 = 0;
                DAT_TroopValueState::instance.attackInfo.field_0x20f50
                    = DAT_TroopValueState::instance.attackInfo.engineers;
            } else if (DAT_TroopValueState::instance.attackInfo.fightingTribeCount < 10) {
                if (DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen <= 0) {
                    DAT_TroopValueState::instance.attackInfo.field_0x20f44 = 0;
                } else if (DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen <= 1) {
                    DAT_TroopValueState::instance.attackInfo.field_0x20f44 = 1;
                } else if (DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen >= 3) {
                    DAT_TroopValueState::instance.attackInfo.field_0x20f44 = 2;
                } else {
                    DAT_TroopValueState::instance.attackInfo.field_0x20f44
                        = DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen - 1;
                }
                if (DAT_TroopValueState::instance.attackInfo.pikemenSwordsmenAndMore != 0) {
                    DAT_TroopValueState::instance.attackInfo.field_0x20f48 = 2;
                } else {
                    DAT_TroopValueState::instance.attackInfo.field_0x20f48 = 1;
                }
                if (DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen > 4) {
                    DAT_TroopValueState::instance.attackInfo.field_0x20f4c = 3;
                } else {
                    DAT_TroopValueState::instance.attackInfo.field_0x20f4c = 2;
                }
                if (DAT_TroopValueState::instance.attackInfo.pikemenSwordsmenAndMore != 0) {
                    DAT_TroopValueState::instance.attackInfo.field_0x20f54 = 1;
                } else {
                    DAT_TroopValueState::instance.attackInfo.field_0x20f54 = 0;
                }
                if (DAT_TroopValueState::instance.attackInfo.pikemenSwordsmenAndMore > 0) {
                    DAT_TroopValueState::instance.attackInfo.field_0x20f58 = 1;
                } else {
                    DAT_TroopValueState::instance.attackInfo.field_0x20f58 = 0;
                }
                DAT_TroopValueState::instance.attackInfo.field_0x20f5c = 2;
                if (DAT_TroopValueState::instance.attackInfo.laddermen <= 2) {
                    DAT_TroopValueState::instance.attackInfo.field_0x20f5c
                        = DAT_TroopValueState::instance.attackInfo.laddermen;
                }
                if (DAT_TroopValueState::instance.attackInfo.pikemenSwordsmenAndMore != 0) {
                    DAT_TroopValueState::instance.attackInfo.field_0x20f40 = 1;
                } else {
                    DAT_TroopValueState::instance.attackInfo.field_0x20f40 = 0;
                }
                DAT_TroopValueState::instance.attackInfo.field_0x20f50
                    = DAT_TroopValueState::instance.attackInfo.engineers;
            } else if (DAT_TroopValueState::instance.attackInfo.fightingTribeCount < 20) {
                if (DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen <= 0) {
                    DAT_TroopValueState::instance.attackInfo.field_0x20f44 = 0;
                } else if (DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen <= 1) {
                    DAT_TroopValueState::instance.attackInfo.field_0x20f44 = 1;
                } else if (DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen >= 4) {
                    DAT_TroopValueState::instance.attackInfo.field_0x20f44 = 3;
                } else {
                    DAT_TroopValueState::instance.attackInfo.field_0x20f44
                        = DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen - 1;
                }
                DAT_TroopValueState::instance.attackInfo.field_0x20f5c = 4;
                if (DAT_TroopValueState::instance.attackInfo.pikemenSwordsmenAndMore > 1) {
                    DAT_TroopValueState::instance.attackInfo.field_0x20f48 = 3;
                } else {
                    DAT_TroopValueState::instance.attackInfo.field_0x20f48 = 2;
                }
                if (DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen > 6) {
                    DAT_TroopValueState::instance.attackInfo.field_0x20f4c = 4;
                } else {
                    DAT_TroopValueState::instance.attackInfo.field_0x20f4c = 3;
                }
                if (DAT_TroopValueState::instance.attackInfo.pikemenSwordsmenAndMore > 4) {
                    DAT_TroopValueState::instance.attackInfo.field_0x20f54 = 3;
                } else {
                    DAT_TroopValueState::instance.attackInfo.field_0x20f54 = 2;
                }
                if (DAT_TroopValueState::instance.attackInfo.pikemenSwordsmenAndMore > 0) {
                    DAT_TroopValueState::instance.attackInfo.field_0x20f58 = 2;
                } else {
                    DAT_TroopValueState::instance.attackInfo.field_0x20f58 = 1;
                }
                if (DAT_TroopValueState::instance.attackInfo.laddermen <= 4) {
                    DAT_TroopValueState::instance.attackInfo.field_0x20f5c
                        = DAT_TroopValueState::instance.attackInfo.laddermen;
                }
                DAT_TroopValueState::instance.attackInfo.field_0x20f40 = 1;
                DAT_TroopValueState::instance.attackInfo.field_0x20f50
                    = DAT_TroopValueState::instance.attackInfo.engineers;
            } else if (DAT_TroopValueState::instance.attackInfo.fightingTribeCount < 30) {
                if (DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen <= 0) {
                    DAT_TroopValueState::instance.attackInfo.field_0x20f44 = 0;
                } else if (DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen <= 1) {
                    DAT_TroopValueState::instance.attackInfo.field_0x20f44 = 1;
                } else if (DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen >= 4) {
                    DAT_TroopValueState::instance.attackInfo.field_0x20f44 = 3;
                } else {
                    DAT_TroopValueState::instance.attackInfo.field_0x20f44
                        = DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen - 1;
                }
                if (DAT_TroopValueState::instance.attackInfo.pikemenSwordsmenAndMore > 4) {
                    DAT_TroopValueState::instance.attackInfo.field_0x20f48 = 4;
                } else {
                    DAT_TroopValueState::instance.attackInfo.field_0x20f48 = 2;
                }
                if (DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen <= 10) {
                    if (DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen > 5) {
                        DAT_TroopValueState::instance.attackInfo.field_0x20f4c = 4;
                    } else {
                        DAT_TroopValueState::instance.attackInfo.field_0x20f4c = 2;
                    }
                } else {
                    DAT_TroopValueState::instance.attackInfo.field_0x20f4c = 6;
                }
                if (DAT_TroopValueState::instance.attackInfo.pikemenSwordsmenAndMore > 8) {
                    DAT_TroopValueState::instance.attackInfo.field_0x20f54 = 5;
                } else if (DAT_TroopValueState::instance.attackInfo.pikemenSwordsmenAndMore > 4) {
                    DAT_TroopValueState::instance.attackInfo.field_0x20f54 = 4;
                } else {
                    DAT_TroopValueState::instance.attackInfo.field_0x20f54 = 2;
                }
                DAT_TroopValueState::instance.attackInfo.field_0x20f58 = 2;
                DAT_TroopValueState::instance.attackInfo.field_0x20f5c = 5;
                if (DAT_TroopValueState::instance.attackInfo.laddermen <= 5) {
                    DAT_TroopValueState::instance.attackInfo.field_0x20f5c
                        = DAT_TroopValueState::instance.attackInfo.laddermen;
                }
                if (DAT_TroopValueState::instance.attackInfo.pikemenSwordsmenAndMore > 4) {
                    DAT_TroopValueState::instance.attackInfo.field_0x20f40 = 2;
                } else {
                    DAT_TroopValueState::instance.attackInfo.field_0x20f40 = 1;
                }
                DAT_TroopValueState::instance.attackInfo.field_0x20f50
                    = DAT_TroopValueState::instance.attackInfo.engineers;
            } else {
                if (DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen <= 0) {
                    DAT_TroopValueState::instance.attackInfo.field_0x20f44 = 0;
                } else if (DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen <= 1) {
                    DAT_TroopValueState::instance.attackInfo.field_0x20f44 = 1;
                } else if (DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen >= 5) {
                    DAT_TroopValueState::instance.attackInfo.field_0x20f44 = 4;
                } else {
                    DAT_TroopValueState::instance.attackInfo.field_0x20f44
                        = DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen - 1;
                }
                if (DAT_TroopValueState::instance.attackInfo.pikemenSwordsmenAndMore > 5) {
                    DAT_TroopValueState::instance.attackInfo.field_0x20f48 = 5;
                } else {
                    DAT_TroopValueState::instance.attackInfo.field_0x20f48 = 2;
                }
                if (DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen > 12) {
                    DAT_TroopValueState::instance.attackInfo.field_0x20f4c = 8;
                } else if (DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen > 6) {
                    DAT_TroopValueState::instance.attackInfo.field_0x20f4c = 5;
                } else {
                    DAT_TroopValueState::instance.attackInfo.field_0x20f4c = 3;
                }
                if (DAT_TroopValueState::instance.attackInfo.pikemenSwordsmenAndMore > 10) {
                    DAT_TroopValueState::instance.attackInfo.field_0x20f54 = 6;
                } else if (DAT_TroopValueState::instance.attackInfo.pikemenSwordsmenAndMore > 8) {
                    DAT_TroopValueState::instance.attackInfo.field_0x20f54 = 5;
                } else {
                    DAT_TroopValueState::instance.attackInfo.field_0x20f54 = 3;
                }
                DAT_TroopValueState::instance.attackInfo.field_0x20f5c = 6;
                if (DAT_TroopValueState::instance.attackInfo.pikemenSwordsmenAndMore > 0) {
                    DAT_TroopValueState::instance.attackInfo.field_0x20f58 = 3;
                } else {
                    DAT_TroopValueState::instance.attackInfo.field_0x20f58 = 2;
                }
                if (DAT_TroopValueState::instance.attackInfo.laddermen <= 6) {
                    DAT_TroopValueState::instance.attackInfo.field_0x20f5c
                        = DAT_TroopValueState::instance.attackInfo.laddermen;
                }
                DAT_TroopValueState::instance.attackInfo.field_0x20f40 = 2;
                DAT_TroopValueState::instance.attackInfo.field_0x20f50
                    = DAT_TroopValueState::instance.attackInfo.engineers;
            }
            if (DAT_TroopValueState::instance.attackInfo.slaveTribeCount
                > DAT_TroopValueState::instance.attackInfo.field_0x20f48) {
                DAT_TroopValueState::instance.attackInfo.field_0x20f48
                    = DAT_TroopValueState::instance.attackInfo.slaveTribeCount;
            }
            DAT_TroopValueState::instance.attackInfo.field_0x20f3c = 3;
        }

    }
}
}
