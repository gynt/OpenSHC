#include "../TextEditorState.func.hpp"

#include "OpenSHC/Globals/DAT_UserHelpDefinedData.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x0045D990
    int TextEditorState::getPrevHelpFontId(int param_1)
    {
        for (int index = 0; DAT_UserHelpDefinedData::instance.helpFontTable[index].fontID != -1; ++index) {
            if (DAT_UserHelpDefinedData::instance.helpFontTable[index].fontID == param_1) {
                --index;
                if (index < 0) {
                    index = 0;
                    while (DAT_UserHelpDefinedData::instance.helpFontTable[index].fontID != -1) {
                        ++index;
                    }
                    --index;
                }
                return DAT_UserHelpDefinedData::instance.helpFontTable[index].fontID;
            }
        }
        return -1;
    }

}
}
