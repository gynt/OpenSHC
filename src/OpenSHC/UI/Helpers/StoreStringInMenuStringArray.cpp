#include "../Helpers.func.hpp"

#include "OpenSHC/Globals/DAT_ArrayOfStoredMenuStrings.hpp"
#include "OpenSHC/Globals/DAT_NumberOfStoredMenuStrings.hpp"

namespace OpenSHC {
namespace UI {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004DA750
    void Helpers::StoreStringInMenuStringArray(char* textToStore)
    {
        char cVar1;
        char* pcVar2;
        if (DAT_NumberOfStoredMenuStrings::instance < 33) {
            pcVar2 = textToStore;
            do {
                cVar1 = *pcVar2;
                pcVar2 = pcVar2 + 1;
            } while (cVar1 != '\0');
            if ((uint)((int)pcVar2 - (int)(textToStore + 1)) < 1023) {
                pcVar2 = DAT_ArrayOfStoredMenuStrings::instance[DAT_NumberOfStoredMenuStrings::instance];
                DAT_NumberOfStoredMenuStrings::instance = DAT_NumberOfStoredMenuStrings::instance + 1;
                do {
                    cVar1 = *textToStore;
                    *pcVar2 = cVar1;
                    textToStore = textToStore + 1;
                    pcVar2 = pcVar2 + 1;
                } while (cVar1 != '\0');
            }
        }
    }

}
}
