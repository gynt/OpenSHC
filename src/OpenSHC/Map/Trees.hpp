/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Trees.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Trees {

        /**
         * Per-tick animation update for tree type 1 (DAT_CurrentTreeID). Phase zeroUpTo2==0: when the Tree_1_A/B
         * sway entry is <=0 the sway index wraps to 0 and the table is re-picked (flag = one==2). Phase !=0: when
         * the Tree_2_A/B entry (A if stage 0) is <=0 the index is stepped back so that animation holds its last
         * frame. Then sets animationFrameUnk from growth stage and phase (phase 0: sway value + 0x4b/0x32/0x19/0
         * for stage 0/1/2/3-4; phase 1: Tree_2 value + stage offset; phase 2: base -
         * treeAdultHoodStageRelatedVisual3; stage 0 phase 2 and stages >=5: 0x92); 0x94 if
         * LandscapeState.field0_0x0 is set.
         */
        void __cdecl UpdateTree1();

        /**
         * Per-tick update for tree type 5 (DAT_CurrentTreeID): wraps the sway animation index when the Tree_1_A/B
         * entry is <=0 (re-picking the table via flag = one==2) and sets animationFrameUnk to the current sway
         * table value (0 if LandscapeState.field0_0x0 is set).
         */
        void __cdecl updateTree5SwayAnimationFrame();

        /**
         * Per-tick update for apple trees (DAT_CurrentTreeID). While stage<6 advances stageTracker and cycles the
         * seasonal stage 0..5 using TreeStageLevels[15], deriving appleTreeColorVariation from rng1&7 and the
         * stage; at stage>=6 the colour is 0 and after more than 1200 ticks state is set to 3. Then wraps the sway
         * animation and sets animationFrameUnk = sway value + stage offset (stage 0/6: 0, 1: 0x19, 3: 0x32, 2/4/5:
         * 0x4b); 0 if LandscapeState.field0_0x0 is set.
         */
        void __cdecl UpdateAppleTree();

        /**
         * Update for tree type 16: sets animationFrameUnk and animationFrame2Unk of DAT_CurrentTreeID to 10 + (rng1
         * & 7), i.e. a fixed frame 10..17.
         */
        void __cdecl UpdateTree16();

        /**
         * Update for tree type 17: picks a fixed frame 1..3 from rng1 ((rng1&3)+1, value 4 clamped to 3) into
         * animationFrameUnk and animationFrame2Unk of DAT_CurrentTreeID.
         */
        void __cdecl UpdateTree17();

        /**
         * Update for tree type 18: picks a fixed frame 4..6 from rng1 ((rng1&3)+4, 7 clamped to 6) into
         * animationFrameUnk and animationFrame2Unk of DAT_CurrentTreeID.
         */
        void __cdecl UpdateTree18();

        /**
         * Update for tree type 19: picks a fixed frame 7..9 from rng1 ((rng1&3)+7, 10 clamped to 9) into
         * animationFrameUnk and animationFrame2Unk of DAT_CurrentTreeID.
         */
        void __cdecl UpdateTree19();

    } // namespace Trees
} // namespace Map
} // namespace OpenSHC
