/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Game/MissionDefinedData.hpp'
*/

#pragma once

#include "OpenSHC/Game/CampaignInfoStruct1.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::Game::CampaignInfoStruct1;

#pragma pack(push, 1)
    // SIZE: 0x000016C4
    typedef struct MissionDefinedData {

        char** field0_0x0; // 0x00000000 length: 4
        char** field1_0x4; // 0x00000004 length: 4
        char** field2_0x8; // 0x00000008 length: 4
        char** field3_0xc; // 0x0000000C length: 4
        char** field4_0x10; // 0x00000010 length: 4
        char** field5_0x14; // 0x00000014 length: 4
        char** field6_0x18; // 0x00000018 length: 4
        char** field7_0x1c; // 0x0000001C length: 4
        char** field8_0x20; // 0x00000020 length: 4
        undefined1 padding_0x24[4]; // 0x00000024 length: 4
        // MenuView_CampaignUnk_Prepare indexes per-mission blocks as (mission-2)*0x58 + 0xB42B7C and compares with
        // the next block (+0x58). Exe data: 21 full 0x58-byte blocks (trailer = mission no. 1..18) + one final
        // 0x54-byte region-state block, ending exactly at the char** at +0x7B4.
        CampaignInfoStruct1 missionCampaignMapStates[21]; // 0x00000028 length: 1848
        // Tail of the per-mission table: 22nd block has only the 0x54-byte region-state part (21 ints = 1) before
        // the pointer at +0x7B4 (0x5AAE14).
        CampaignInfoSubStructure1 missionCampaignMapStatesLast; // 0x00000760 length: 84
        char** field15_0x7b4; // 0x000007B4 length: 4
        char** field16_0x7b8; // 0x000007B8 length: 4
        char** field17_0x7bc; // 0x000007BC length: 4
        char** field18_0x7c0; // 0x000007C0 length: 4
        char** field19_0x7c4; // 0x000007C4 length: 4
        char** field20_0x7c8; // 0x000007C8 length: 4
        char** field21_0x7cc; // 0x000007CC length: 4
        char** field22_0x7d0; // 0x000007D0 length: 4
        // per greatest-lord sort column: [textGroup, textOffset] of the column title
        int greatestLordColumnTitleText[18][2]; // 0x000007D4 length: 144
        // speech file name per mission (1..20) played on stream 3 after 1.5 s in the scenario description screen
        char missionBriefingSpeechFiles[20][32]; // 0x00000864 length: 640
        // eco missions 33-37 read [mn*4+0xB435B4] = +0xAE4..+0xAF4 (review 381 verified); int[5] eco hint counts,
        // not a base read at [missionNumber+5], so the per-mission data starts at +0xAFC (exe init
        // 2,3,3,3,2,2,3,3,1,...): number of hints listed on the scenario description hints page (0 = none, 1 =
        // 'Hint', >1 = 'Hints' heading, one icon per hint)
        int ecoMissionHintCounts[5]; // 0x00000AE4 length: 20
        // true while the crusade mission intro screen is shown (set in Prepare, cleared on skirmish launch);
        // DoEveryFrame renders only when set
        bool crusadeMissionIntroActive; // 0x00000AF8 length: 1
        byte field27_0xaf9[3]; // 0x00000AF9 length: 3
        // Hint counts of military missions 1..21, indexed missionNumber-1 (0x4DD4DC reads [eax*4+0xB4364C] with the
        // -4 folded into the displacement; 0xB4364C itself is the byte flag crusadeMissionIntroActive). Review 607.
        int militaryMissionHintCounts[21]; // 0x00000AFC length: 84
        int sortColumn; // 0x00000B50 length: 4
        // gfx frame sequence (26 frames, 250 ms each) animated on the scenario description screen
        int scenarioDescriptionAnimFrames[26]; // 0x00000B54 length: 104
        // screen x,y of each mission icon on the crusader (skirmish) trail map, 50 missions
        int crusadeTrailIconPosXY[50][2]; // 0x00000BBC length: 400
        // screen x,y of each mission icon on the warchest trail map, 30 missions
        int warchestTrailIconPosXY[30][2]; // 0x00000D4C length: 240
        // screen x,y of each mission icon on the extreme trail map
        int extremeTrailIconPosXY[30][2]; // 0x00000E3C length: 240
        // per trail mission: GID_SKIRMISH_TRAIL_ICONS frame offset for the mission icon
        int trailIconFrameOffset[50]; // 0x00000F2C length: 200
        // per trail mission: {spriteId, frame, dx, dy} drawn when the mission was chickened/skipped (months ==
        // -1200)
        int trailChickenSprite[50][4]; // 0x00000FF4 length: 800
        // int[22] ping-pong frame table indexed by time to animate the lord marker on the trail map. 22-frame
        // animation sequence cycled on the crusade map screen
        int trailLordMarkerAnimFrames[22]; // 0x00001314 length: 88
        undefined4 descending; // 0x0000136C length: 4
        // countdown while the tactical powers help text is displayed; cleared when a power is used
        int tacticalPowersHelpTextTimer; // 0x00001370 length: 4
        undefined1 padding_0x1374[8]; // 0x00001374 length: 8
        // gfx index per history-book page (RenderHistoryBookEdgeUnk)
        int historyBookPageGfx[50]; // 0x0000137C length: 200
        // speech file per historic mission (1..20) played on stream 3 on the mission intro screen
        char historicMissionIntroSpeechFiles[20][32]; // 0x00001444 length: 640

    } MissionDefinedData;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(MissionDefinedData) == 5828, MissionDefinedData);
} // namespace Game
} // namespace OpenSHC
