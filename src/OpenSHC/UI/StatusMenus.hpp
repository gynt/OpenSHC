/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/StatusMenus.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace StatusMenus {

        /**
         * Draws the Popularity report panel for the local player on the menu surface. Page 0 shows Food (rations
         * -200..+200, +25/+50/+75 for 2/3/4 food types eaten, 0 with no population, -200 with no food), Tax
         * (bribe/tax table +175..-600; +25 when a bribe is set but gold < 1), Crowding (0..-250), Fear Factor
         * (level*25), Religion (blessed % tier + 25 church + 50 cathedral) and Ale coverage tier; the active
         * scenario events (Fair +400, Marriage, Jester, Plague, Lion Attack, Bandits, Fire) get consecutive slots
         * in a per-slot page/x/y table, 2 pages when more than 2 events are active; finally the 'In the coming
         * month' total of all effects. Values are in 1/25 popularity units. An out-of-range rationsSetting (not
         * 0..4) would read an uninitialised stack slot (the fire slot).
         */
        void __cdecl RenderStatusMenu_Popularity();

        /**
         * Draws the Fear Factor report panel: title, good/bad building counts with icons, popularity effect
         * (fearFactorLevel*25), 'Good/Bad things for next level' with objectsLeftUntilNextLevel when good != bad
         * (or a 'maximum' text, id 0x19 at level >= 5 / 0x18 at <= -5), a description of the effect on population
         * by sign of the level, and the efficiency percentage. Non-English languages shift the right column 20px
         * left. The decompiler reuses temporaries for call arguments; rightColumnX first holds the title Y.
         */
        void __cdecl RenderStatusMenu_FearFactor();

        /**
         * Draws the Population report panel for the local player: header, graph frame, 'Years' label, y-axis
         * maximum (50 * scale, scale 1/2/4/8/16/32 chosen from the max sampled population), six x-axis year labels
         * 5 years apart (59px spacing) starting at max(0,(populationIndex-300)/12), and one bar sprite per monthly
         * population sample (up to 300 samples, 75px = 50*scale people, clipped at the graph baseline).
         */
        void __cdecl RenderStatusMenu_Population();

        /**
         * Draws the Food report panel: header, in single-player (currentGameMode == GM_SOLITARY) the hint 'Clicking
         * on a food toggles consumption', and the local player's stock of each of the 4 food resource types listed
         * in DAT_TroopValueDefinedData.foodStatusResourceTypes, in 80px columns.
         */
        void __cdecl RenderStatusMenu_Food();

        /**
         * Draws the Stores (stockpile) report panel: header and, for each of the 8 stockpile resources in the
         * table, its GM_INTERFACE_ICONS2 icon (with per-icon position nudge) and the player's current amount, in
         * 52px columns.
         */
        void __cdecl RenderStatusMenu_Resources();

        /**
         * Draws the Religion report panel: total priests, blessed %, popularity effect tier (0/50/100/150/200 at
         * blessed % >= 25/50/75/95), 'Next level at' 25/50/75/100 % or 'Max bonus achieved' at >= 95 % (BUG: shows
         * 100 for 75..94 % although the top tier starts at 95 %), church/cathedral bonus text and bonus (+25
         * church, +50 cathedral). Also advances g_religionStatusAnimCounter (0..40, wraps).
         */
        void __cdecl RenderStatusMenu_Religion();

        /**
         * Draws the Weapons (armoury) report panel: header and, for each of the 8 weapon types in the table, its
         * GM_INTERFACE_ICONS2 icon (with position nudge) and the player's current amount, in 52px columns.
         */
        void __cdecl RenderStatusMenu_Weapons();

        /**
         * Draws the selected-peasant ('chimp') info panel: name (unit-type name for ghosts, else first name +
         * optional surname + job title for most types), current action, and for ordinary workers a chimp comment
         * line cached in g_statusMenuChimpCommentId (picked when it is -1); when the selected unit changed, plays
         * the comment's male/female speech SFX and remembers its id. Switches to the build menu if the selected
         * unit's type is 0.
         */
        void __cdecl RenderStatusMenu_Chimp();

        /**
         * Draws the Overview status panel (sets INT_00b96120 = 0x47): a picture, the player's name (user text 0)
         * centered, and the line '<description> and <popularity description>' from TEXT_PLAYER_DESC, whose total
         * width (+12) is measured first to center it at menuX+0x8d. The first description index comes from
         * SomeGoldRelatedComputation when fearFactorLevel is 0, else from getFearFactorDescriptionTextIndex.
         */
        void __cdecl RenderStatusMenu_Overview();

        /**
         * Draws the Army status panel: about every 41 frames recounts the player's units by type; draws the 9 (8 on
         * page 2) unit icons of the current army page (g_statusMenuArmyPage) with their counts. Page 0 additionally
         * shows the fear-factor troop combat bonus (fearFactorLevel*5 %, icon 0xb1/0xb2 and colour by sign) or 'No
         * fear factor bonus' at level 0; other pages show 'Total Troops' with armySize.
         */
        void __cdecl RenderStatusMenu_Army();

    } // namespace StatusMenus
} // namespace UI
} // namespace OpenSHC
