#include "../TextEditorState.func.hpp"

#include "OpenSHC/Globals/DAT_UserHelpDefinedData.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x0045D950
    int TextEditorState::getNextHelpFontId(int param_1)
    {
        for (int index = 0; DAT_UserHelpDefinedData::instance.helpFontTable[index].fontID != -1; ++index) {
            if (DAT_UserHelpDefinedData::instance.helpFontTable[index].fontID != param_1) {
                continue;
            }

            ++index;
            if (DAT_UserHelpDefinedData::instance.helpFontTable[index].fontID == -1) {
                index = 0;
            }
            return DAT_UserHelpDefinedData::instance.helpFontTable[index].fontID;
        }
        return -1;
    }

}
}
