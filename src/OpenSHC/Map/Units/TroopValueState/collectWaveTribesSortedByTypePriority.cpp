#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/AI/Tribes/AITribeTypeInt.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"

#include "OpenSHC/Globals/DAT_AttackInfoDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

// The priority tables are 28 consecutive AITribeTypeInt[20] blocks at AttackInfoDefinedData+0x12C (only the first 12
// entries are used). The header only names some of them (field251_0x21c ... field1060_0x80c, the latter even as
// short), the others lie in padding, so they are addressed through the padding arrays here.
#define PRIORITY_TABLE_IN_PADDING(padding, offset)                                                                     \
    ((AITribeTypeInt*)&DAT_AttackInfoDefinedData::instance.padding[offset])

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::AI::Tribes::AITribeTypeInt;
        using OpenSHC::Map::Units::SomeTribeBehaviorType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00518380
        void TroopValueState::collectWaveTribesSortedByTypePriority(
            int attackWave, int shrinkSize, int tribeSizeSumLimit, SomeTribeBehaviorType someTribeTypeIdentifier)
        {
            AITribeTypeInt* priorityTable;
            if (someTribeTypeIdentifier == STBT_0x3f2) {
                priorityTable = DAT_AttackInfoDefinedData::instance.field251_0x21c;
            } else if (someTribeTypeIdentifier == STBT_0x3f3) {
                priorityTable = PRIORITY_TABLE_IN_PADDING(padding_0x44c, 0x0);
            } else if (someTribeTypeIdentifier == STBT_0x3f4) {
                priorityTable = DAT_AttackInfoDefinedData::instance.field255_0x35c;
            } else if (someTribeTypeIdentifier == STBT_0x3fa) {
                priorityTable = PRIORITY_TABLE_IN_PADDING(padding_0x44c, 0xa0);
            } else if (someTribeTypeIdentifier == STBT_0x410_SIEGE_EQUIPMENT_CONSTRUCTION) {
                priorityTable = DAT_AttackInfoDefinedData::instance.field256_0x3ac;
            } else if (someTribeTypeIdentifier == STBT_0x415) {
                priorityTable = DAT_AttackInfoDefinedData::instance.field257_0x3fc;
            } else if (someTribeTypeIdentifier == STBT_7) {
                priorityTable = PRIORITY_TABLE_IN_PADDING(padding_0x12c, 0x0);
            } else if (someTribeTypeIdentifier == STBT_5) {
                priorityTable = PRIORITY_TABLE_IN_PADDING(padding_0x12c, 0x50);
            } else if (someTribeTypeIdentifier == STBT_0x3f6) {
                priorityTable = DAT_AttackInfoDefinedData::instance.field252_0x26c;
            } else if (someTribeTypeIdentifier == STBT_0x417) {
                priorityTable = PRIORITY_TABLE_IN_PADDING(padding_0x85c, 0x140);
            } else if (someTribeTypeIdentifier == STBT_0x413) {
                priorityTable = DAT_AttackInfoDefinedData::instance.field253_0x2bc;
            } else if (someTribeTypeIdentifier == STBT_0x414) {
                priorityTable = DAT_AttackInfoDefinedData::instance.field254_0x30c;
            } else if (someTribeTypeIdentifier == STBT_0x3f5) {
                priorityTable = PRIORITY_TABLE_IN_PADDING(padding_0x44c, 0xf0);
            } else if (someTribeTypeIdentifier == STBT_0x3fb) {
                priorityTable = PRIORITY_TABLE_IN_PADDING(padding_0x44c, 0x140);
            } else if (someTribeTypeIdentifier == STBT_0x401) {
                priorityTable = PRIORITY_TABLE_IN_PADDING(padding_0x44c, 0x190);
            } else if (someTribeTypeIdentifier == STBT_0x3fd) {
                priorityTable = PRIORITY_TABLE_IN_PADDING(padding_0x44c, 0x1e0);
            } else if (someTribeTypeIdentifier == STBT_0x416) {
                priorityTable = PRIORITY_TABLE_IN_PADDING(padding_0x44c, 0x230);
            } else if (someTribeTypeIdentifier == STBT_0x3fc) {
                priorityTable = DAT_AttackInfoDefinedData::instance.field1059_0x7bc;
            } else if (someTribeTypeIdentifier == STBT_0x419) {
                // declared as AITribeTypeShort[40] in the header, but it is an AITribeTypeInt table like the others
                priorityTable = (AITribeTypeInt*)DAT_AttackInfoDefinedData::instance.field1060_0x80c;
            } else if (someTribeTypeIdentifier == STBT_0x41a) {
                priorityTable = PRIORITY_TABLE_IN_PADDING(padding_0x44c, 0x2d0);
            } else if (someTribeTypeIdentifier == STBT_0x41b) {
                priorityTable = PRIORITY_TABLE_IN_PADDING(padding_0x44c, 0x2d0);
            } else if (someTribeTypeIdentifier == STBT_0x418) {
                priorityTable = PRIORITY_TABLE_IN_PADDING(padding_0x85c, 0x0);
            } else if (someTribeTypeIdentifier == STBT_0x41e) {
                priorityTable = PRIORITY_TABLE_IN_PADDING(padding_0x85c, 0xa0);
            } else if (someTribeTypeIdentifier == STBT_0x412) {
                priorityTable = PRIORITY_TABLE_IN_PADDING(padding_0x85c, 0x50);
            } else if (someTribeTypeIdentifier == STBT_0x3f8) {
                priorityTable = PRIORITY_TABLE_IN_PADDING(padding_0x44c, 0x280);
            } else if (someTribeTypeIdentifier == STBT_0x3f9) {
                priorityTable = DAT_AttackInfoDefinedData::instance.field1058_0x76c;
            } else if (someTribeTypeIdentifier == STBT_0x3f7) {
                priorityTable = PRIORITY_TABLE_IN_PADDING(padding_0x44c, 0x50);
            } else if (someTribeTypeIdentifier == STBT_0x411) {
                priorityTable = PRIORITY_TABLE_IN_PADDING(padding_0x85c, 0xf0);
            } else if (someTribeTypeIdentifier == STBT_0x3ff) {
                priorityTable = PRIORITY_TABLE_IN_PADDING(padding_0x12c, 0xa0);
            } else {
                priorityTable = PRIORITY_TABLE_IN_PADDING(padding_0x12c, 0x50);
            }

            for (int i = 0; i < 50; ++i) {
                DAT_TroopValueState::instance.attackInfo.tribeIDArray[i] = 0;
                DAT_TroopValueState::instance.attackInfo.tribeTypePriorityRank[i] = 12;
            }

            int tribeID = 1;
            DAT_TroopValueState::instance.attackInfo.tribeIDArraySize = 0;
            for (; tribeID < 1250; ++tribeID) {
                if (DAT_TribesState::instance.tribes[tribeID].tribeState != 0
                    && DAT_TribesState::instance.tribes[tribeID].tribeState != 3
                    && DAT_GameSynchronyState::instance
                            .currentPlayerFullIDArray[DAT_TribesState::instance.tribes[tribeID].owner]
                        == -1
                    && DAT_TribesState::instance.tribes[tribeID].attackWave == attackWave
                    && DAT_TribesState::instance.tribes[tribeID].attackInfo_someCounter1
                        != DAT_TroopValueState::instance.attackInfo.someCounter1
                    && DAT_TribesState::instance.tribes[tribeID].tribeBehaviorType
                        != STBT_0x410_SIEGE_EQUIPMENT_CONSTRUCTION
                    && DAT_TribesState::instance.tribes[tribeID].tribeBehaviorType != STBT_0x415) {
                    DAT_TroopValueState::instance.attackInfo
                        .tribeIDArray[DAT_TroopValueState::instance.attackInfo.tribeIDArraySize]
                        = tribeID;
                    DAT_TroopValueState::instance.attackInfo.tribeIDArraySize++;
                }
            }

            if (shrinkSize <= 0 || tribeSizeSumLimit <= 0) {
                return;
            }

            // bubble sort by the rank of the tribe type in the priority table
            int swapped;
            do {
                swapped = 0;
                for (int i = 0; i < DAT_TroopValueState::instance.attackInfo.tribeIDArraySize - 1; ++i) {
                    int const tribeA = DAT_TroopValueState::instance.attackInfo.tribeIDArray[i];
                    int const tribeB = DAT_TroopValueState::instance.attackInfo.tribeIDArray[i + 1];
                    int const tribeTypeA = DAT_TribesState::instance.tribes[tribeA].tribeType;
                    int const tribeTypeB = DAT_TribesState::instance.tribes[tribeB].tribeType;
                    int rankA;
                    for (rankA = 0; rankA < 12; ++rankA) {
                        if (priorityTable[rankA] == tribeTypeA) {
                            break;
                        }
                    }
                    int rankB;
                    for (rankB = 0; rankB < 12; ++rankB) {
                        if (priorityTable[rankB] == tribeTypeB) {
                            break;
                        }
                    }
                    if (rankB < rankA) {
                        swapped = 1;
                        DAT_TroopValueState::instance.attackInfo.tribeIDArray[i] = tribeB;
                        DAT_TroopValueState::instance.attackInfo.tribeIDArray[i + 1] = tribeA;
                    }
                }
            } while (swapped != 0);

            for (int i = 0; i < DAT_TroopValueState::instance.attackInfo.tribeIDArraySize; ++i) {
                int const tribeType
                    = DAT_TribesState::instance.tribes[DAT_TroopValueState::instance.attackInfo.tribeIDArray[i]].tribeType;
                int rank;
                for (rank = 0; rank < 12; ++rank) {
                    if (priorityTable[rank] == tribeType) {
                        break;
                    }
                }
                DAT_TroopValueState::instance.attackInfo.tribeTypePriorityRank[i] = rank;
            }

            int sizeSum = 0;
            for (int i = 0; i < DAT_TroopValueState::instance.attackInfo.tribeIDArraySize; ++i) {
                int const tribeID = DAT_TroopValueState::instance.attackInfo.tribeIDArray[i];
                if (sizeSum > tribeSizeSumLimit) {
                    DAT_TroopValueState::instance.attackInfo.tribeTypePriorityRank[i] = 12;
                }
                sizeSum += DAT_TribesState::instance.tribes[tribeID].size;
            }

            if (DAT_TroopValueState::instance.attackInfo.tribeIDArraySize > shrinkSize) {
                DAT_TroopValueState::instance.attackInfo.tribeIDArraySize = shrinkSize;
            }
        }

    }
}
}

#undef PRIORITY_TABLE_IN_PADDING
