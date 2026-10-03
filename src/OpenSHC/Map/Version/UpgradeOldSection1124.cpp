#include "../../Map.func.hpp"
#include "../Version.func.hpp"

#include "OpenSHC/Globals/DAT_SkirmishLobbySetupStructureLongMapName.hpp"
#include "OpenSHC/Globals/SEC_SkirmishLobbySetupStructure.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00486AD0
    void Version::UpgradeOldSection1124()
    {
        char cVar1;
        byte bVar2;
        int iVar3;
        int iVar4;
        int iVar5;
        SEC_SkirmishLobbySetupStructure::instance.mapu4int2
            = DAT_SkirmishLobbySetupStructureLongMapName::instance.mapu4int2;
        SEC_SkirmishLobbySetupStructure::instance.mbr_0x4
            = DAT_SkirmishLobbySetupStructureLongMapName::instance.mbr_0x4;
        iVar5 = 0;
        do {
            cVar1 = DAT_SkirmishLobbySetupStructureLongMapName::instance.mapName[iVar5];
            SEC_SkirmishLobbySetupStructure::instance.mapName[iVar5] = cVar1;
            iVar5 = iVar5 + 1;
        } while (cVar1 != '\0');
        iVar5 = 0;
        do {
            bVar2 = DAT_SkirmishLobbySetupStructureLongMapName::instance.playerGroupArray[iVar5];
            SEC_SkirmishLobbySetupStructure::instance.roundTableOrderArray[iVar5]
                = DAT_SkirmishLobbySetupStructureLongMapName::instance.roundTableOrderArray[iVar5];
            iVar3 = DAT_SkirmishLobbySetupStructureLongMapName::instance.currentAIArray[iVar5];
            SEC_SkirmishLobbySetupStructure::instance.playerGroupArray[iVar5] = bVar2;
            iVar4 = DAT_SkirmishLobbySetupStructureLongMapName::instance.aiVariationArray[iVar5];
            SEC_SkirmishLobbySetupStructure::instance.currentAIArray[iVar5] = iVar3;
            SEC_SkirmishLobbySetupStructure::instance.aiVariationArray[iVar5] = iVar4;
            iVar5 = iVar5 + 1;
        } while (iVar5 < 9);
        /*
          optimization of slotPosition setting
         */
        SEC_SkirmishLobbySetupStructure::instance.slot1Position
            = DAT_SkirmishLobbySetupStructureLongMapName::instance.slot1Position;
        SEC_SkirmishLobbySetupStructure::instance.slot2Position
            = DAT_SkirmishLobbySetupStructureLongMapName::instance.slot2Position;
        SEC_SkirmishLobbySetupStructure::instance.slot3Position
            = DAT_SkirmishLobbySetupStructureLongMapName::instance.slot3Position;
        SEC_SkirmishLobbySetupStructure::instance.slot4Position
            = DAT_SkirmishLobbySetupStructureLongMapName::instance.slot4Position;
        /*
          optimization of slotPosition setting
         */
        SEC_SkirmishLobbySetupStructure::instance.slot5Position
            = DAT_SkirmishLobbySetupStructureLongMapName::instance.slot5Position;
        SEC_SkirmishLobbySetupStructure::instance.slot6Position
            = DAT_SkirmishLobbySetupStructureLongMapName::instance.slot6Position;
        SEC_SkirmishLobbySetupStructure::instance.slot7Position
            = DAT_SkirmishLobbySetupStructureLongMapName::instance.slot7Position;
        SEC_SkirmishLobbySetupStructure::instance.slot8Position
            = DAT_SkirmishLobbySetupStructureLongMapName::instance.slot8Position;
        SEC_SkirmishLobbySetupStructure::instance.currentPlayerSlotID
            = DAT_SkirmishLobbySetupStructureLongMapName::instance.currentPlayerSlotID;
        SEC_SkirmishLobbySetupStructure::instance.currentAdvantageBalance
            = DAT_SkirmishLobbySetupStructureLongMapName::instance.currentAdvantageBalance;
        SEC_SkirmishLobbySetupStructure::instance.currentAdvantageGroup
            = DAT_SkirmishLobbySetupStructureLongMapName::instance.currentAdvantageGroup;
        SEC_SkirmishLobbySetupStructure::instance.mbr_0x80
            = DAT_SkirmishLobbySetupStructureLongMapName::instance.mbr_0x80;
        SEC_SkirmishLobbySetupStructure::instance.playerLordTypeArray[0]
            = DAT_SkirmishLobbySetupStructureLongMapName::instance.playerLordTypeArray[0];
        SEC_SkirmishLobbySetupStructure::instance.playerLordTypeArray[1]
            = DAT_SkirmishLobbySetupStructureLongMapName::instance.playerLordTypeArray[1];
        SEC_SkirmishLobbySetupStructure::instance.playerLordTypeArray[2]
            = DAT_SkirmishLobbySetupStructureLongMapName::instance.playerLordTypeArray[2];
        SEC_SkirmishLobbySetupStructure::instance.playerLordTypeArray[3]
            = DAT_SkirmishLobbySetupStructureLongMapName::instance.playerLordTypeArray[3];
        SEC_SkirmishLobbySetupStructure::instance.playerLordTypeArray[4]
            = DAT_SkirmishLobbySetupStructureLongMapName::instance.playerLordTypeArray[4];
        SEC_SkirmishLobbySetupStructure::instance.playerLordTypeArray[5]
            = DAT_SkirmishLobbySetupStructureLongMapName::instance.playerLordTypeArray[5];
        SEC_SkirmishLobbySetupStructure::instance.playerLordTypeArray[6]
            = DAT_SkirmishLobbySetupStructureLongMapName::instance.playerLordTypeArray[6];
        SEC_SkirmishLobbySetupStructure::instance.playerLordTypeArray[7]
            = DAT_SkirmishLobbySetupStructureLongMapName::instance.playerLordTypeArray[7];
        SEC_SkirmishLobbySetupStructure::instance.playerLordTypeArray[8]
            = DAT_SkirmishLobbySetupStructureLongMapName::instance.playerLordTypeArray[8];
        SEC_SkirmishLobbySetupStructure::instance.mbr_0xf0
            = DAT_SkirmishLobbySetupStructureLongMapName::instance.mbr_0xf0;
        SEC_SkirmishLobbySetupStructure::instance.selectedLordType
            = DAT_SkirmishLobbySetupStructureLongMapName::instance.selectedLordType;
        SEC_SkirmishLobbySetupStructure::instance.popularity
            = DAT_SkirmishLobbySetupStructureLongMapName::instance.popularity;
        SEC_SkirmishLobbySetupStructure::instance.mapSelectionRelativeSelected
            = DAT_SkirmishLobbySetupStructureLongMapName::instance.mapSelectionRelativeSelected;
        SEC_SkirmishLobbySetupStructure::instance.mapSelectionScrollOffset
            = DAT_SkirmishLobbySetupStructureLongMapName::instance.mapSelectionScrollOffset;
        SEC_SkirmishLobbySetupStructure::instance.mbr_0xfc
            = DAT_SkirmishLobbySetupStructureLongMapName::instance.mbr_0xfc;
    }

}
}
