#include "../../Map.func.hpp"
#include "../Trees.func.hpp"

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_CurrentTreeID.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_OrganismDefinedData.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004F2640
    void Trees::UpdateTree5()
    {
        byte _frame;
        short _rng2;
        int _tree;
        _tree = DAT_CurrentTreeID::instance;
        _rng2 = DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex;
        if (DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].flag == FALSE) {
            _frame = DAT_OrganismDefinedData::instance.Tree_1_A[_rng2];
        } else {
            _frame = DAT_OrganismDefinedData::instance.Tree_1_B[_rng2];
        }
        if ((char)_frame < '\x01') {
            DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex = 0;
            DAT_LandscapeState::instance.trees[_tree].flag = (uint)(DAT_LandscapeState::instance.trees[_tree].one == 2);
        }
        _rng2 = DAT_LandscapeState::instance.trees[_tree].animationFrameIndex;
        if (DAT_LandscapeState::instance.trees[_tree].flag == FALSE) {
            _frame = DAT_OrganismDefinedData::instance.Tree_1_A[_rng2];
        } else {
            _frame = DAT_OrganismDefinedData::instance.Tree_1_B[_rng2];
        }
        DAT_LandscapeState::instance.trees[_tree].animationFrameUnk = (int)(char)_frame;
        if (DAT_LandscapeState::instance.field0_0x0 != 0) {
            DAT_LandscapeState::instance.trees[_tree].animationFrameUnk = 0;
        }
    }

}
}
