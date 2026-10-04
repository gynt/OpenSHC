#include "../MenuModalComposition.func.hpp"

#include "OpenSHC/UI/Enums/MenuModalType.hpp"

namespace OpenSHC {
namespace UI {

    using UI::Enums::MenuModalType;

    // FUNCTION: STRONGHOLDCRUSADER 0x004A9E60
    MenuModalComposition* MenuModalComposition::Constructor_MenuModalComposition(int slot)
    {
        this->slot = slot;
        this->activeModalDialogID = UI::Enums::MMT_NONE;
        return this;
    }

}
}
