#include "../MapEditorProperties.func.hpp"

#include "OpenSHC/Globals/g_mapDescriptionTextHeight.hpp"
#include "OpenSHC/Globals/mapDescScrollOffset.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0042EE80
        void MapEditorProperties::MenuItemActionHandler_MapEditorProperties_MapDescriptionScrollbar(
            int param_1, int param_2, int* minValue, int* maxValue, int* currentValue)
        {
            int iVar1;
            if (DAT_GameCore::instance.U2_mapType_singleOrMulti != 0) {
                switch (param_2) {
                case 1:
                    *minValue = 0;
                    *maxValue = g_mapDescriptionTextHeight::instance + -0xe7;
                    *currentValue = 0;
                    return;
                case 2:
                case 3:
                    mapDescScrollOffset::instance = *currentValue;
                    return;
                case 4:
                    *minValue = 0;
                    *maxValue = g_mapDescriptionTextHeight::instance + -0xe7;
                    *currentValue = mapDescScrollOffset::instance;
                    return;
                case 5:
                    if (0 < mapDescScrollOffset::instance) {
                        mapDescScrollOffset::instance = mapDescScrollOffset::instance + -0xe;
                    }
                    if (mapDescScrollOffset::instance < 0) {
                        mapDescScrollOffset::instance = 0;
                    }
                    *currentValue = mapDescScrollOffset::instance;
                    return;
                case 6:
                    iVar1 = g_mapDescriptionTextHeight::instance + -0xe7;
                    if ((mapDescScrollOffset::instance < iVar1)
                        && (mapDescScrollOffset::instance = mapDescScrollOffset::instance + 0xe, iVar1 < mapDescScrollOffset::instance)) {
                        mapDescScrollOffset::instance = iVar1;
                    }
                    *currentValue = mapDescScrollOffset::instance;
                    break;
                case 7:
                    *currentValue = 0xfc;
                }
            }
        }

    }
}
}
