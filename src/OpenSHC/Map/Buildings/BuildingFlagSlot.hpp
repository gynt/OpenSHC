/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Buildings/BuildingFlagSlot.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Buildings {

#pragma pack(push, 1)
        // SIZE: 0x00000004
        // Building offset 0x80, which two kinds of building use differently.
        // Most types run it as the owner flag's animation clock: the Update*
        // functions increment it and index
        // BuildingDefinedData.field177_0x7e1c by `ownerFlagFrame / 2`, putting
        // the resolved image in overlayImageID at 0x84.
        // UpdateGranary instead treats 0x80 as slot 14 of the overlay family
        // and writes a GM image index there, which renderGmOverlayBuilding
        // pushes as an imageID like any other slot.
        typedef union BuildingFlagSlot {

            int ownerFlagFrame; // 0x00000000 length: 4
            int overlayImage; // 0x00000000 length: 4

        } BuildingFlagSlot;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(BuildingFlagSlot) == 4, BuildingFlagSlot);
    } // namespace Buildings
} // namespace Map
} // namespace OpenSHC
