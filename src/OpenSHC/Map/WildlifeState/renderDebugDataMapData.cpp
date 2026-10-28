#include "OpenSHC/Map/WildlifeState.func.hpp"

#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/COL_BLUE.hpp"
#include "OpenSHC/Globals/COL_BRIGHT_YELLOW.hpp"
#include "OpenSHC/Globals/COL_DARK_CYAN_GREY.hpp"
#include "OpenSHC/Globals/COL_DARK_GREEN.hpp"
#include "OpenSHC/Globals/COL_LIME.hpp"
#include "OpenSHC/Globals/COL_MODERATE_GREEN.hpp"
#include "OpenSHC/Globals/COL_RED.hpp"
#include "OpenSHC/Globals/COL_VERY_DARK_GREY.hpp"
#include "OpenSHC/Globals/COL_VIVID_BLUE.hpp"
#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Text::TextAlignment;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // Debug overlay of the 40x40 wildlife grid. Label per display type 0..9 (strings 0x5ABBCC..0x5ABB74) at
    // (x + 0x1A6, y + 4); other types draw no label. 41 white horizontal and 41 vertical lines, step 10, from
    // (x + 2, y). Each cell with validTileCount > 0 (jle 0x52C54E) gets an 8x8 box whose colour is the first
    // matching test of the display type's chain (display type re-read per cell); types above 9 draw no boxes.
    // FUNCTION: STRONGHOLDCRUSADER 0x0052BF40
    void WildlifeState::renderDebugDataMapData(int x, int y, int width, int height)
    {
        x += 2;
        int const displayType = this->DAT_DebugDataMapDataDisplayType;
        if (displayType == 0) {
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)
            ("Connect ", x + 0x1a4, y + 4, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x11, FALSE, 0);
        } else if (displayType == 1) {
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)
            ("Chimps  ", x + 0x1a4, y + 4, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x11, FALSE, 0);
        } else if (displayType == 2) {
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)
            ("Farmland   ", x + 0x1a4, y + 4, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x11, FALSE, 0);
        } else if (displayType == 3) {
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)
            ("Humans  ", x + 0x1a4, y + 4, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x11, FALSE, 0);
        } else if (displayType == 4) {
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)
            ("Mankind  ", x + 0x1a4, y + 4, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x11, FALSE, 0);
        } else if (displayType == 5) {
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)
            ("Deer  ", x + 0x1a4, y + 4, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x11, FALSE, 0);
        } else if (displayType == 6) {
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)
            ("Route  ", x + 0x1a4, y + 4, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x11, FALSE, 0);
        } else if (displayType == 7) {
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)
            ("Panic  ", x + 0x1a4, y + 4, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x11, FALSE, 0);
        } else if (displayType == 8) {
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)
            ("Siege  ", x + 0x1a4, y + 4, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x11, FALSE, 0);
        } else if (displayType == 9) {
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)
            ("Slink  ", x + 0x1a4, y + 4, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x11, FALSE, 0);
        }
        for (int i = 0; i <= 400; i += 10) {
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)
            (x, y + i, x + 400, y + i, COL_WHITE::instance.shortValue);
        }
        for (int i = 0; i <= 400; i += 10) {
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)
            (x + i, y, x + i, y + 400, COL_WHITE::instance.shortValue);
        }
        for (int gy = 0; gy < 40; gy++) {
            for (int gx = 0; gx < 40; gx++) {
                WildlifeGridElement* const cell = &this->grid[gx][gy];
                if (cell->validTileCount <= 0) {
                    continue;
                }
                ushort color;
                int const type = this->DAT_DebugDataMapDataDisplayType;
                if (type == 0) {
                    int const area = cell->dominantPathAreaId;
                    int const areaColor = area & 7;
                    if (area == 0) {
                        color = COL_BLUE::instance.shortValue;
                    } else if (areaColor == 1) {
                        color = COL_RED::instance.shortValue;
                    } else if (areaColor == 2) {
                        color = COL_BRIGHT_YELLOW::instance.shortValue;
                    } else if (areaColor == 3) {
                        color = COL_MODERATE_GREEN::instance.shortValue;
                    } else if (areaColor == 4) {
                        color = COL_WHITE::instance.shortValue;
                    } else if (areaColor == 5) {
                        color = COL_DARK_CYAN_GREY::instance.shortValue;
                    } else if (areaColor == 6) {
                        color = COL_LIME::instance.shortValue;
                    } else if (areaColor == 7) {
                        color = COL_VIVID_BLUE::instance.shortValue;
                    } else {
                        color = COL_VERY_DARK_GREY::instance.shortValue;
                    }
                } else if (type == 1) {
                    if (cell->dominantPathAreaId == 0) {
                        color = COL_BLUE::instance.shortValue;
                    } else if (cell->humanPlayerAreaTileCount != 0) {
                        color = COL_RED::instance.shortValue;
                    } else {
                        color = COL_LIME::instance.shortValue;
                    }
                } else if (type == 2) {
                    if (cell->dominantPathAreaId == 0) {
                        color = COL_BLUE::instance.shortValue;
                    } else if (cell->farmlandTileCount != 0) {
                        color = COL_DARK_GREEN::instance.shortValue;
                    } else if (cell->rabbitCount != 0) {
                        color = COL_RED::instance.shortValue;
                    } else if (cell->routeVisited != 0) {
                        color = COL_WHITE::instance.shortValue;
                    } else if (cell->farmlandInfluence != 0) {
                        color = COL_DARK_CYAN_GREY::instance.shortValue;
                    } else {
                        color = COL_LIME::instance.shortValue;
                    }
                } else if (type == 3) {
                    if (cell->dominantPathAreaId == 0) {
                        color = COL_BLUE::instance.shortValue;
                    } else if (cell->humanCount != 0) {
                        color = COL_RED::instance.shortValue;
                    } else {
                        color = COL_LIME::instance.shortValue;
                    }
                } else if (type == 4) {
                    if (cell->dominantPathAreaId == 0) {
                        color = COL_BLUE::instance.shortValue;
                    } else if (cell->humanCount != 0) {
                        color = COL_RED::instance.shortValue;
                    } else if (cell->buildingTileCount != 0) {
                        color = COL_RED::instance.shortValue;
                    } else if (cell->dangerInfluence != 0) {
                        color = COL_BRIGHT_YELLOW::instance.shortValue;
                    } else {
                        color = COL_LIME::instance.shortValue;
                    }
                } else if (type == 5) {
                    if (cell->dominantPathAreaId == 0) {
                        color = COL_BLUE::instance.shortValue;
                    } else if (cell->humanCount != 0) {
                        color = COL_RED::instance.shortValue;
                    } else if (cell->buildingTileCount != 0) {
                        color = COL_RED::instance.shortValue;
                    } else if (cell->lionCount != 0) {
                        color = COL_BLACK::instance.shortValue;
                    } else if (cell->camelCount != 0) {
                        color = COL_BLACK::instance.shortValue;
                    } else if (cell->deerCount != 0) {
                        color = COL_MODERATE_GREEN::instance.shortValue;
                    } else if (cell->dangerInfluence != 0) {
                        color = COL_BRIGHT_YELLOW::instance.shortValue;
                    } else {
                        color = COL_LIME::instance.shortValue;
                    }
                } else if (type == 6) {
                    if (cell->dominantPathAreaId == 0) {
                        color = COL_BLUE::instance.shortValue;
                    } else if (cell->deerCount != 0) {
                        color = COL_RED::instance.shortValue;
                    } else if (cell->lionCount != 0) {
                        color = COL_VIVID_BLUE::instance.shortValue;
                    } else if (cell->routeVisited != 0) {
                        color = COL_WHITE::instance.shortValue;
                    } else if (cell->routeBfsValue != 0) {
                        color = COL_BRIGHT_YELLOW::instance.shortValue;
                    } else if (cell->dangerInfluence != 0) {
                        color = COL_BLACK::instance.shortValue;
                    } else {
                        color = COL_LIME::instance.shortValue;
                    }
                } else if (type == 7) {
                    if (cell->dominantPathAreaId == 0) {
                        color = COL_BLUE::instance.shortValue;
                    } else if (cell->panicSourceCount != 0) {
                        color = COL_WHITE::instance.shortValue;
                    } else if (cell->deerCount != 0) {
                        color = COL_RED::instance.shortValue;
                    } else if (cell->dangerInfluence != 0) {
                        color = COL_BLACK::instance.shortValue;
                    } else {
                        color = COL_LIME::instance.shortValue;
                    }
                } else if (type == 8) {
                    if (cell->castleCoreScore != 0) {
                        color = COL_WHITE::instance.shortValue;
                    } else if (cell->castleZoneSpread != 0) {
                        color = COL_BLACK::instance.shortValue;
                    } else if (cell->castlebuildings != 0) {
                        color = COL_BRIGHT_YELLOW::instance.shortValue;
                    } else if (cell->dominantPathAreaId == 0) {
                        color = COL_BLUE::instance.shortValue;
                    } else if (cell->zoneProximity != 0) {
                        color = COL_VIVID_BLUE::instance.shortValue;
                    } else if (cell->siegeCampSuitable != 0) {
                        color = COL_RED::instance.shortValue;
                    } else {
                        color = COL_LIME::instance.shortValue;
                    }
                } else if (type == 9) {
                    if (cell->reachedFromSignpost != 0) {
                        color = COL_RED::instance.shortValue;
                    } else if (cell->zoneProximity != 0) {
                        color = COL_VIVID_BLUE::instance.shortValue;
                    } else if (cell->dominantPathAreaId == 0) {
                        color = COL_BLUE::instance.shortValue;
                    } else {
                        color = COL_LIME::instance.shortValue;
                    }
                } else {
                    continue;
                }
                int const boxX = x + gx * 10;
                int const boxY = y + gy * 10;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)
                (boxX + 1, boxY + 1, boxX + 9, boxY + 9, color);
            }
        }
    }

}
}
