/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/BuildingNameRelatedStruct.hpp'
*/

#pragma once

#include "OpenSHC/UI/BuildingNameRelatedSubStruct.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::UI::BuildingNameRelatedSubStruct;

#pragma pack(push, 1)
    // SIZE: 0x00000028
    typedef struct BuildingNameRelatedStruct {

        int nameNumberInTextGroup; // 0x00000000 length: 4
        // 3 x 3 ints read as a flat list of up to 9 ids (0 terminates): id>0 = BuildingType whose
        // buildingAvailabilityRelatedFlags[id] follows this availability toggle; id<0 = special flag at
        // MapPropertiesState+(0x290-id)*2. identifier1 of entry 0 is switched on (0x32, 0x52, 0x53 ...) by the
        // availability buttons
        BuildingNameRelatedSubStruct linkedBuildingTypes[3]; // 0x00000004 length: 36

    } BuildingNameRelatedStruct;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(BuildingNameRelatedStruct) == 40, BuildingNameRelatedStruct);
} // namespace UI
} // namespace OpenSHC
