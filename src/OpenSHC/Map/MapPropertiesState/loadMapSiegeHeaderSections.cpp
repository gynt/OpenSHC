#include "../../Map.func.hpp"

#include "OpenSHC/IO/FilePackager.func.hpp"
#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/IO/FileResourceType.hpp"

#include "OpenSHC/Globals/DAT_MapDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/FilePackagerObj.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::IO::FileResourceType;

    /*
      Resolves the map filename via ResourceManager (FRT_MAPS), then reads map header siege info   sections 1063, 1062,
      1064, 1056, and 1057 from the file packager. If the file version is below   154, calls meth_0x4c1320 as a legacy
      upgrade path.      renamed by: Claude Sonnet 4.6
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004C3110
    void MapPropertiesState::loadMapSiegeHeaderSections(char* param_1)
    {
        MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName, DAT_ResourceManager::ptr)(
            OpenSHC::IO::FRT_MAPS, (char const*)((int)(param_1)));
        MACRO_CALL_MEMBER(OpenSHC::IO::FilePackager_Func::readMapHeaderSectionByID, FilePackagerObj::ptr)(
            DAT_MapDefinedData::instance.MapSectionAddressArray, (int)((int)(1063)));
        MACRO_CALL_MEMBER(OpenSHC::IO::FilePackager_Func::readMapHeaderSectionByID, FilePackagerObj::ptr)(
            DAT_MapDefinedData::instance.MapSectionAddressArray, (int)((int)(1062)));
        MACRO_CALL_MEMBER(OpenSHC::IO::FilePackager_Func::readMapHeaderSectionByID, FilePackagerObj::ptr)(
            DAT_MapDefinedData::instance.MapSectionAddressArray, (int)((int)(1064)));
        MACRO_CALL_MEMBER(OpenSHC::IO::FilePackager_Func::readMapHeaderSectionByID, FilePackagerObj::ptr)(
            DAT_MapDefinedData::instance.MapSectionAddressArray, (int)((int)(1056)));
        MACRO_CALL_MEMBER(OpenSHC::IO::FilePackager_Func::readMapHeaderSectionByID, FilePackagerObj::ptr)(
            DAT_MapDefinedData::instance.MapSectionAddressArray, (int)((int)(1057)));
        if ((int)FilePackagerObj::instance.versionNumOfCurrentFileTypeUnk < 154) {
            MACRO_CALL_MEMBER(OpenSHC::Map::MapPropertiesState_Func::removeProcessedInvasionEvents, this)();
        }
    }

}
}
