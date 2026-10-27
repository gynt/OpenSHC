/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuViews/CampaignUnk.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace CampaignUnk {

            /**
             * Per-frame handler of the CampaignUnk view (whose Prepare loads the England campaign map): once
             * Helpers::TicksSinceCounterStart returns non-zero, switches to the scenario description view for
             * campaign mission 1, otherwise to menu view 26 (MVT_MISSION_INTRO_SEQUENCE).
             */
            void __cdecl MenuView_CampaignMap_DoEveryFrame();

            /**
             * Prepare handler of the CampaignUnk (England campaign map) view: clears the screen, parses the hotspot
             * bitmap once, then copies the 20-dword campaign-map region state (0x58-byte stride,
             * missionCampaignMapStates) into CampaignInfoSubStructure1_00ec02f4: block 0 for mission 1, otherwise
             * block missionNumber-2 (previous mission's state); for mission >= 2 it also stores into
             * g_campaignChangedRegionNumbers the 1-based numbers (1..20) of regions whose value differs in the next block
             * (missionNumber-1), count in g_campaignChangedRegionCount. If nothing changed (or mission 1), sets INT_00eb9b4c=100
             * and a start time. Then loads campaign_map_england + the 20 region overlays, the pig/rat/snake/wolf
             * map icons, shc_back, and starts the tick counter. The
             * DAT_SkirmishDefinedData.aiTauntWeightAndMessage[missionNumber*0x16+k] references are the decompiler
             * mis-resolving missionCampaignMapStates[missionNumber-2] (machine code reads all 20 values from one
             * base pointer (m-2)*0x58+0xB42B7C).
             */
            void __cdecl MenuView_CampaignMap_Prepare();

            /**
             * Initial handler of the CampaignUnk (campaign map) view: positions the menu origin and the current
             * menu at the main-menu border offset, clears the screen to black and draws the outer menu border.
             */
            void __cdecl MenuView_CampaignMap_DoInitial();

        } // namespace CampaignUnk
    } // namespace MenuViews
} // namespace UI
} // namespace OpenSHC
