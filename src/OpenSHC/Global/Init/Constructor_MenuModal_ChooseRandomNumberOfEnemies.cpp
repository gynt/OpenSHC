#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/ChooseRandomNumberOfEnemies.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/MenuModalRenderFunction.hpp"

#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/MenuModal_ChooseRandomNumberOfEnemies.hpp"
#include "OpenSHC/Globals/Menu_ChooseRandomNumberOfEnemies.hpp"

namespace OpenSHC {
namespace Global {

    using OpenSHC::UI::Enums::MenuModalType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C2C0
    void Init::Constructor_MenuModal_ChooseRandomNumberOfEnemies()
    {
        MACRO_CALL_MEMBER(OpenSHC::UI::MenuModal_Func::Constructor_MenuModal,
            MenuModal_ChooseRandomNumberOfEnemies::ptr)(OpenSHC::UI::Enums::MMT_CHOOSE_RANDOM_NUMBER_OF_ENEMIES, -1, -1,
            600, 400, 0x200, (int)((int)(COL_WHITE::instance.shortValue)),
            (OpenSHC::UI::MenuModalRenderFunction*)MACRO_CALL(OpenSHC::UI::MenuModals::
                    ChooseRandomNumberOfEnemies_Func::MenuModalRenderFunction_ChooseRandomNumberOfEnemies),
            Menu_ChooseRandomNumberOfEnemies::ptr);
        MACRO_CALL(OpenSHC::OS_Func::_atexit)(
            MACRO_CALL(OpenSHC::Meta_Func::Destructor_MenuModal_ChooseRandomNumberOfEnemies));
        return;
    }

}
}
