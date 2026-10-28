#include "../TextEditorState.func.hpp"

#include "OpenSHC/Globals/DAT_UserHelpDefinedData.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x0045D9E0
    char* TextEditorState::getHelpFontName(int param_1)
    {
        for (int index = 0; DAT_UserHelpDefinedData::instance.helpFontTable[index].fontID != -1; ++index) {
            if (DAT_UserHelpDefinedData::instance.helpFontTable[index].fontID == param_1) {
                return DAT_UserHelpDefinedData::instance.helpFontTable[index].fontName;
            }
        }
        return NULL;
    }

}
}
