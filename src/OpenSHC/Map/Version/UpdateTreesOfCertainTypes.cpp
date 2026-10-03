#include "../../Map.func.hpp"
#include "../Version.func.hpp"

#include "OpenSHC/Map/Trees/TreeType.hpp"
#include "OpenSHC/Map/Trees/TreeTypeShort.hpp"

#include "OpenSHC/Globals/DAT_CurrentTreeID.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_OrganismDefinedData.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Trees::TreeType;
    using OpenSHC::Map::Trees::TreeTypeShort;

    // FUNCTION: STRONGHOLDCRUSADER 0x004F38A0
    void Version::UpdateTreesOfCertainTypes()
    {
        TreeTypeShort TVar1;
        NoArgCallback* pNVar2;
        Tree* pTVar3;
        int iVar3;
        iVar3 = 1;
        pTVar3 = &DAT_LandscapeState::instance.trees[1];
        do {
            if ((pTVar3->state == 2)
                && ((((TVar1 = pTVar3->treeType, TVar1 == ((TreeType)0x10) || (TVar1 == ((TreeType)0x11)))
                         || (TVar1 == ((TreeType)0x12)))
                    || (TVar1 == ((TreeType)0x13))))) {
                pNVar2 = DAT_OrganismDefinedData::instance.UpdateTree[(short)TVar1];
                pTVar3->state = 4;
                DAT_CurrentTreeID::instance = iVar3;
                (*pNVar2)();
            }
            pTVar3 = pTVar3 + 0x4e;
            iVar3 = iVar3 + 1;
        } while ((int)pTVar3 < 0xf78f5a);
    }

}
}
