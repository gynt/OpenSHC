/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Game/CampaignInfoSubStructure1.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Game {

#pragma pack(push, 1)
    // SIZE: 0x00000054
    typedef struct CampaignInfoSubStructure1 {

        // campaign map region 0 value copied from MissionDefinedData per mission; regions whose value differs from
        // the next mission are animated (CampaignUnk menu)
        undefined4 regionState00; // 0x00000000 length: 4
        // campaign map region 1 value (see regionState00)
        undefined4 regionState01; // 0x00000004 length: 4
        // campaign map region 2 value
        undefined4 regionState02; // 0x00000008 length: 4
        // campaign map region 3 value
        undefined4 regionState03; // 0x0000000C length: 4
        // campaign map region 4 value
        undefined4 regionState04; // 0x00000010 length: 4
        // campaign map region 5 value
        undefined4 regionState05; // 0x00000014 length: 4
        // campaign map region 6 value
        undefined4 regionState06; // 0x00000018 length: 4
        // campaign map region 7 value
        undefined4 regionState07; // 0x0000001C length: 4
        // campaign map region 8 value
        undefined4 regionState08; // 0x00000020 length: 4
        // campaign map region 9 value
        undefined4 regionState09; // 0x00000024 length: 4
        // campaign map region 10 value
        undefined4 regionState10; // 0x00000028 length: 4
        // campaign map region 11 value
        undefined4 regionState11; // 0x0000002C length: 4
        // campaign map region 12 value
        undefined4 regionState12; // 0x00000030 length: 4
        // campaign map region 13 value
        undefined4 regionState13; // 0x00000034 length: 4
        // campaign map region 14 value
        undefined4 regionState14; // 0x00000038 length: 4
        // campaign map region 15 value
        undefined4 regionState15; // 0x0000003C length: 4
        // campaign map region 16 value
        undefined4 regionState16; // 0x00000040 length: 4
        // campaign map region 17 value
        undefined4 regionState17; // 0x00000044 length: 4
        // campaign map region 18 value
        undefined4 regionState18; // 0x00000048 length: 4
        // campaign map region 19 value
        undefined4 regionState19; // 0x0000004C length: 4
        undefined4 field20_0x50; // 0x00000050 length: 4

    } CampaignInfoSubStructure1;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(CampaignInfoSubStructure1) == 84, CampaignInfoSubStructure1);
} // namespace Game
} // namespace OpenSHC
