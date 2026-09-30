#include "../../Map.func.hpp"
#include "../Version.func.hpp"

#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Trees/TreeType.hpp"
#include "OpenSHC/Map/Trees/TreeTypeShort.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Trees::TreeType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;
    using OpenSHC::Map::Trees::TreeTypeShort;

    /*
      fixme:todo:bug:Is this the origin of the not visualized foliage bug?   decompilerscript: committed: 2025-01-30
      21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004F37B0
    void Version::UpdateFixTrees2()
    {
        TreeTypeShort TVar1;
        int iVar2;
        BOOLEnum BVar3;
        Tree* _pTree;
        int _treeID;
        _treeID = 1;
        _pTree = &DAT_LandscapeState::instance.trees[1];
        do {
            TVar1 = _pTree->treeType;
            if ((((TVar1 == ((TreeType)1)) || (TVar1 == ((TreeType)2))) || (TVar1 == ((TreeType)3)))
                || (TVar1 == ((TreeType)4))) {
                iVar2 = DAT_TextureRenderCoreObject::instance.gmFileHeaderColorpaletteArray[_pTree->treeTypeBasedValue1]
                            .originY;
                _pTree->gmOriginX = (short)DAT_TextureRenderCoreObject::instance
                                        .gmFileHeaderColorpaletteArray[_pTree->treeTypeBasedValue1]
                                        .originX;
                _pTree->gmOriginY = (short)iVar2;
                BVar3 = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Navigation::PathFindingState_Func::findNoTreeInRange, DAT_PathFindingState::ptr)(
                    2, (uint)((int)((int)(short)_pTree->xPosition)), (uint)((int)((int)(short)_pTree->yPosition)));
                if (BVar3 == FALSE) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::removeTree, DAT_LandscapeState::ptr)(_treeID);
                }
            }
            _pTree = _pTree + 0x4e;
            _treeID = _treeID + 1;
        } while ((int)_pTree < 0xf78f5a);
    }

}
}
