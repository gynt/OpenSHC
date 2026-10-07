#include "../ScrollingHandler.func.hpp"

#include "OpenSHC/UI/ScrollDirection.hpp"
#include "OpenSHC/UI/ScrollSpeed.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace UI {

    using UI::ScrollDirection;
    using UI::ScrollSpeed;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00468A90
    ScrollingHandler* ScrollingHandler::Constructor_ScrollingHandler()
    {
        this->isScrolling_0x0 = FALSE;
        this->scrollRight = FALSE;
        this->rightKeyDown_0x18 = FALSE;
        this->scrollLeft = FALSE;
        this->leftKeyDown_0x1c = FALSE;
        this->scrollDown = FALSE;
        this->downKeyDown_0x20 = FALSE;
        this->scrollUp = FALSE;
        this->upKeyDown_0x24 = FALSE;
        this->scrollDirection_0x4 = UI::SD_NONE;
        this->scrollAccelerationInterval = 0x14;
        this->scrollDistanceLimit = 0x28;
        this->scrollDistanceMin = 1;
        this->scrollSpeedSetting_0x38 = UI::SS_NORMAL;
        return this;
    }

}
}
