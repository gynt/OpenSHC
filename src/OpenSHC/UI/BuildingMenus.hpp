/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/BuildingMenus.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace BuildingMenus {

        /**
         * Shared info panel of the weapon workshops (fletcher, poleturner, blacksmith). If the worker is in its 'no
         * raw material' state (unit state 8 for fletcher, 1 for poleturner, 9 for blacksmith) and production is not
         * paused, it shows 'Not producing - No Wood/Iron'; otherwise 'Producing:' with the weapon from
         * producedItemTypeNext. It always shows 'Next:' with the weapon from producedItemType. For a non-weapon
         * item type the text index is an uninitialized local (the push ecx stack slot).
         */
        void __cdecl RenderBuildingMenu_WorkshopWeaponProduction();

        /**
         * Building-menu callback for recruiting buildings: only calls
         * BuildingsState::createEntityForAssemblyPointsForActiveTabType (assembly-point entities for the active tab
         * type). It draws no text itself.
         */
        void __cdecl RenderBuildingMenu_RecruitingBuilding();

        /**
         * Keep building menu. While a tax change is pending (timeTaxesOrRationsChange) it triggers the scribe
         * reaction for the tax category (2 = bribes, slider 0-2; 1 = slider 3-4; 3 = higher taxes; every frame
         * after 2 s) and after 2.5 s plays the matching SEID_TAXES_RATE speech and clears the timer. It shows the
         * keep's name (for keep doors BT 71-73 the linked keep, checked against uidWhenPlaced), the tax/bribe
         * label, then population (peasant icon) = bribe cost (shown negated) or tax income, with a gold icon. It
         * then draws the tax level's popularity effect (+7/+5/+3/+1/-2/-4/-6/-8/-12/-16/-20/-24 in units of 25 for
         * slider 0-11, shifted right when the label is wider than 190 px; +1 also when bribes are set but the
         * player has no gold, 0 with no population; an out-of-range slider would show the gold amount) and calls
         * QueueChangeTaxes.
         */
        void __cdecl RenderBuildingMenu_Keep();

        /**
         * Inn building menu: shows the inn's ale stock / 160 next to the ale icon and its flagons of ale, the
         * player's working inns (total inns), ale coverage % with its popularity bonus (0/+2/+4/+6/+8 in units of
         * 25), and either the next coverage threshold (25/50/75/100%) or 'Maximum bonus achieved' at 100% or more.
         */
        void __cdecl RenderBuildingMenu_Inn();

        /**
         * Draws the Granary panel for the local player: title, rations icon (GM_INTERFACE_ICONS2 frame 0x11C-0x120
         * by rationsLevel, with per-level x/y nudges), food-clock slider bar (foodClock*162/15000), total food,
         * months of supply (foodStorageLevel), food types eaten and the popularity effects of rations and food
         * variety (TransformAndRenderPercentage). If rations were changed recently (timeTaxesOrRationsChange):
         * after 2 s it calls Helpers::TriggerScribeReaction (2 for double rations, 3 for none, 1 otherwise), after
         * 2.5 s it clears the timestamp and plays the SEID_FOOD_* speech for the setting. Takes no register
         * parameters: the prologue 'push ecx' only reserves a local whose stale value (the decompiler's unaff_ECX)
         * is used only on the unreachable switch defaults (rationsLevel > 4). The SpeechEffectID-typed SVar1 also
         * carries the popularity values (e.g. 200/-200) passed to TransformAndRenderPercentage.
         */
        void __cdecl RenderBuildingMenu_Granary();

        /**
         * Draws the Fletcher's Workshop panel title, then the shared weapon-workshop production view
         * (RenderBuildingMenu_WorkshopWeaponProduction).
         */
        void __cdecl RenderBuildingMenu_Fletcher();

        /**
         * Draws the Blacksmith's Workshop panel title, then the shared weapon-workshop production view.
         */
        void __cdecl RenderBuildingMenu_Blacksmith();

        /**
         * Draws the Poleturner's Workshop panel title, then the shared weapon-workshop production view.
         */
        void __cdecl RenderBuildingMenu_Poleturner();

        /**
         * Draws the Armourer's Workshop panel title; if the building's first worker exists, has state.generic == 9
         * and CheckUnitProductionPaused is false (field166_0x2fe != 1), also prints 'Not producing - No Iron'
         * (TEXT_IN_BLACKSMITHS_WORKSHOP index 0xC).
         */
        void __cdecl RenderBuildingMenu_Armourer();

        /**
         * Draws the Tanner's Workshop panel title; if its first worker exists, has state.generic == US_IDLEUnk (1)
         * and CheckUnitProductionPaused is false, prints 'Not producing - No Cows' (TEXT_IN_BLACKSMITHS_WORKSHOP
         * index 0xD).
         */
        void __cdecl RenderBuildingMenu_Tanner();

        /**
         * Draws the Bakery panel title text only.
         */
        void __cdecl RenderBuildingMenu_Bakery();

        /**
         * Draws the Brewery panel title text only.
         */
        void __cdecl RenderBuildingMenu_Brewery();

        /**
         * Draws the Outpost panel: title (TEXT_IN_OUTPOST index 0, or 9 for BT_OUTPOST_ARABIAN) and the static
         * labels Size/Small/Large and Start Delay/None/10 Mins.
         */
        void __cdecl RenderBuildingMenu_Outpost();

        /**
         * Draws the Hovel panel: title (font 0x10) and the word-wrapped description 'Provides space for 8
         * peasants.' (max width 0x136, font 0x12).
         */
        void __cdecl RenderBuildingMenu_House();

        /**
         * Draws the Woodcutter's hut panel title text only.
         */
        void __cdecl RenderBuildingMenu_WoodcutterShut();

        /**
         * NAME? typo 'OxThether' (Ox Tether). Draws the Ox Tether panel: title and the word-wrapped description
         * that an ox transports stone from here to the stockpile (TEXT_IN_OXEN_BASE 0 and 3).
         */
        void __cdecl RenderBuildingMenu_OxThether();

        /**
         * Draws the Quarry panel title text only.
         */
        void __cdecl RenderBuildingMenu_Quarry();

        /**
         * Draws the Iron Mine panel title text only.
         */
        void __cdecl RenderBuildingMenu_Ironmine();

        /**
         * Draws the Pitch Rig panel title text only.
         */
        void __cdecl RenderBuildingMenu_PitchRig();

        /**
         * Draws the Hunter's Post panel title text only.
         */
        void __cdecl RenderBuildingMenu_HuntersHut();

        /**
         * Draws the Apothecary panel: title, 'Immunity From Disease' label and the immunity percentage =
         * min(healerCount,3)*20 followed by '%'.
         */
        void __cdecl RenderBuildingMenu_Apothecary();

        /**
         * Draws the Wheat Farm panel title text only.
         */
        void __cdecl RenderBuildingMenu_Wheatfarm();

        /**
         * Draws the Hops Farm panel title text only.
         */
        void __cdecl RenderBuildingMenu_Hopfarm();

        /**
         * Draws the Apple Orchard panel title text only.
         */
        void __cdecl RenderBuildingMenu_Applefarm();

        /**
         * NAME? typo 'Diaryfarm' (Dairy farm). Draws the Dairy Farm panel title text only.
         */
        void __cdecl RenderBuildingMenu_Diaryfarm();

        /**
         * Draws the Mill panel title text only.
         */
        void __cdecl RenderBuildingMenu_Mill();

        /**
         * Draws the Chapel/Church/Cathedral panel (title index 0/3/4). Without a priest (currentEmployeeCount==0)
         * shows 'No Wedding this month'. Once per game month it picks a couple via chooseHusbandAndWife and
         * advances one of three rotating (0..9) marriage-text indices chosen by the wife's unit type (brewer,
         * tanner, other); while both partners keep their unit types it draws the background gfx, the wedding text,
         * both portraits and first names/surnames, otherwise 'No Wedding this month'.
         */
        void __cdecl RenderBuildingMenu_ChapelAndChurch();

        /**
         * Draws the Stockpile panel: title and, for the 8 stockpile goods (wood, hops, stone, iron, pitch, wheat,
         * ale, flour), the icon and the local player's amount. Left-clicking an icon of a tradeable good while the
         * player owns a marketplace selects the marketplace, requests building-menu tab 0x39 (trade) and preselects
         * that resource.
         */
        void __cdecl RenderBuildingMenu_Stockpile();

        /**
         * Draws the Armoury panel: title and, for the 8 weapon/armour goods (bow, spear, mace, crossbow, pike,
         * sword, leather armour, metal armour), the icon (drawn blended when the amount is <1) and the local
         * player's amount. Left-clicking a tradeable item with a marketplace present jumps to the marketplace trade
         * tab (0x39) with that resource preselected.
         */
        void __cdecl RenderBuildingMenu_Armory();

        /**
         * Draws the Quarry Stone Pile panel: title and the word-wrapped note that an ox transports stone placed
         * here.
         */
        void __cdecl RenderBuildingMenu_Quarry_Stonepile();

        /**
         * Draws the Engineer's Guild panel title; calls CheckIfEnoughGoldForLadderman and, if
         * DAT_EnoughGoldForRequestedUnit is FALSE, prints 'You do not have enough gold for apprentices' (wrapped,
         * width 400, font 0x11). Finally calls BuildingsState::createEntityForAssemblyPointsForActiveTabType.
         */
        void __cdecl RenderBuildingMenu_Engineersguild();

        /**
         * Draws the Tunneller's Guild panel title; if CheckIfEnoughGoldForTunneler leaves
         * DAT_EnoughGoldForRequestedUnit FALSE, prints 'You do not have enough gold to train a tunneller'. Then
         * calls createEntityForAssemblyPointsForActiveTabType.
         */
        void __cdecl RenderBuildingMenu_Tunnelersguild();

        /**
         * Draws the Cathedral (monk-recruiting) panel title; if CheckIfEnoughGoldForMonk leaves
         * DAT_EnoughGoldForRequestedUnit FALSE, prints 'You do not have enough gold for monks'. Then calls
         * createEntityForAssemblyPointsForActiveTabType.
         */
        void __cdecl RenderBuildingMenu_Cathedral();

        /**
         * Draws the Marketplace main tab: title 'The Marketplace' and centered hint 'Choose a goods type to trade'.
         */
        void __cdecl RenderBuildingMenu_Marketplace();

        /**
         * Draws the Marketplace price-list tab: header text, then for each of the 20 MarketStonksOrder slots (slot
         * 13 is empty, so 19 goods) whose good is tradeable, the good icon (RT_PARTIALPITCH frame for pitch; drawn
         * blended only if the stock is <= -100, i.e. effectively never) in two rows (slots 0-9 row 1, slots 10-19
         * row 2 with columns 0-2 and 3-8, 0x2F px apart) and below it 'buy/sell' = getBuyPriceForOneUnit /
         * getSalePriceOfGood, with per-slot x nudges.
         */
        void __cdecl RenderBuildingMenu_Marketplace_Stonks();

        /**
         * Draws the Marketplace 'Trade Food' tab: title and, for each tradeable good of
         * RenderingDefinedData.FoodTypes (meat, cheese, apples, hops, ale, wheat, flour, bread), the local player's
         * stock centred under its icon column (columns 0x34 px apart).
         */
        void __cdecl RenderBuildingMenu_Marketplace_Food();

        /**
         * Draws the Marketplace 'Trade Raw Materials' tab: title and, for each tradeable good of
         * RenderingDefinedData.RawResourceTypes (wood, stone, iron, pitch), the local player's stock centred under
         * its icon column (columns 0x68 px apart).
         */
        void __cdecl RenderBuildingMenu_Marketplace_Resource();

        /**
         * Draws the Marketplace 'Trade Weapons' tab: title and, for each tradeable good of
         * RenderingDefinedData.marketWeaponsResourceTypes (spear, bow, mace, leather armour, crossbow, pike, sword, metal
         * armour), the local player's stock centred under its icon column (columns 0x34 px apart).
         */
        void __cdecl RenderBuildingMenu_Marketplace_Weapons();

        /**
         * Draws the Marketplace single-good trade view for marketSelectedResourceType: the good's icon (frame
         * type+0x62, pitch shown as RT_PARTIALPITCH; offset by the per-resource position table field1048_0x55604),
         * the player's stock of it, the gold icon and gold amount (currentResources[15]), and, if any goods are
         * tradeable, the icons of the previous/next tradeable goods of the market cycle.
         */
        void __cdecl RenderBuildingMenu_Marketplace_Trade();

        /**
         * Draws the Well building panel title text only.
         */
        void __cdecl RenderBuildingMenu_Well();

        /**
         * Draws the Water Pot building panel title text only.
         */
        void __cdecl RenderBuildingMenu_WaterPot();

        /**
         * Draws the Oil Smelter panel: title and word-wrapped description 'Boils oil for siege defence.'.
         */
        void __cdecl RenderBuildingMenu_Oilsmelter();

        /**
         * Draws the Stables panel: title, horses available = numberOfAnimals - horsesInUseOrOutpostArcherCap with
         * 'Horse/Horses Available' (text 3 if exactly 1, else 1), and horses in use = horsesInUseOrOutpostArcherCap
         * with 'Horse/Horses In Use' (text 4 if exactly 1, else 2).
         */
        void __cdecl RenderBuildingMenu_Stables();

        /**
         * Draws the Drawbridge building panel title text only.
         */
        void __cdecl RenderBuildingMenu_Drawbridge();

        /**
         * Draws the Postern Gate (unused building) panel title text only.
         */
        void __cdecl RenderBuildingMenu_Unused_PosternGate();

        /**
         * Draws the Tunnel Entrance building panel title text only.
         */
        void __cdecl RenderBuildingMenu_TunnelEntrance();

        /**
         * Draws the Signpost building panel title text only (drawn lower than usual, y+0x1F5).
         */
        void __cdecl RenderBuildingMenu_Signpost();

        /**
         * Draws the Killing Pit building panel title text only.
         */
        void __cdecl RenderBuildingMenu_KillingPit();

        /**
         * Draws the Camp Ground (campfire) panel: title and word-wrapped description 'Peasants gather here.'.
         */
        void __cdecl RenderBuildingMenu_Campfire();

        /**
         * Draws the Gallows building panel title text only.
         */
        void __cdecl RenderBuildingMenu_Gallows();

        /**
         * Draws the Stocks building panel title text only.
         */
        void __cdecl RenderBuildingMenu_Stocks();

        /**
         * Draws the Witch Hoist (unused building) panel title text only.
         */
        void __cdecl RenderBuildingMenu_Unused_Witchhoist();

        /**
         * Draws the Maypole building panel title text only.
         */
        void __cdecl RenderBuildingMenu_Maypole();

        /**
         * Draws the Gardens building panel title text only (string taken from TEXT_BUBBLE_HELP_TEXT index 0x7C).
         */
        void __cdecl RenderBuildingMenu_Gardens();

        /**
         * Draws the Training Ground building panel title text only.
         */
        void __cdecl RenderBuildingMenu_TrainingGrounds();

        /**
         * Draws the Cesspit building panel title text only.
         */
        void __cdecl RenderBuildingMenu_CessPit();

        /**
         * Draws the Burning Stake building panel title text only.
         */
        void __cdecl RenderBuildingMenu_BurningStake();

        /**
         * Draws the Gibbet building panel title text only.
         */
        void __cdecl RenderBuildingMenu_Gibbet();

        /**
         * Draws the Dungeon building panel title text only.
         */
        void __cdecl RenderBuildingMenu_Dungeon();

        /**
         * Draws the Stretching Rack building panel title text only.
         */
        void __cdecl RenderBuildingMenu_StretchingRack();

        /**
         * Draws the Flogging Rack (unused building) panel title text only.
         */
        void __cdecl RenderBuildingMenu_Unused_FloggingRack();

        /**
         * Draws the Chopping Block building panel title text only.
         */
        void __cdecl RenderBuildingMenu_ChoppingBlock();

        /**
         * Draws the Dunking Stool building panel title text only.
         */
        void __cdecl RenderBuildingMenu_DunkingStool();

        /**
         * Draws the Dog Cage panel: title 'Caged war dogs' and, when the local player's releaseDogsFlag == 1, the
         * line 'The dogs are loose!'.
         */
        void __cdecl RenderBuildingMenu_DogCage();

        /**
         * Draws the Statue panel title; if the statue's owner is 0 (memorial of a defeated lord) also prints 'Here
         * lies the poor bones of' followed by the name of statueCommemoratingPlayerID from finalResults.names.
         */
        void __cdecl RenderBuildingMenu_Statue();

        /**
         * Draws the Shrine building panel title text only.
         */
        void __cdecl RenderBuildingMenu_Shrine();

        /**
         * Draws only the title text 'Beehive' of the (unused) Beehive building panel.
         */
        void __cdecl RenderBuildingMenu_Unused_BeeHive();

        /**
         * Draws only the title text 'Dancing bear' of the Dancing Bear building panel.
         */
        void __cdecl RenderBuildingMenu_DancingBear();

        /**
         * Draws only the title text 'Pond' of the (unused) Pond building panel.
         */
        void __cdecl RenderBuildingMenu_Unused_Pond();

        /**
         * Draws only the title text 'Bear cave' of the (unused) Bear Cave building panel.
         */
        void __cdecl RenderBuildingMenu_Unused_BearCave();

        /**
         * Siege-tent panel while a Catapult is being built: draws the label 'Catapult' (TEXT_IN_SIEGE_TENT 1), then
         * the build progress of the selected building as buildingProgress*100/320 followed by the text '%
         * Complete'.
         */
        void __cdecl RenderBuildingMenu_Siegetent_Catapult();

        /**
         * Siege-tent panel while a Fire Ballista is being built: draws the label (TEXT_IN_SIEGE_TENT 7), then build
         * progress buildingProgress*100/320 followed by '% Complete'.
         */
        void __cdecl RenderBuildingMenu_Siegetent_Fireballista();

        /**
         * Siege-tent panel while a Trebuchet is being built: draws the label (TEXT_IN_SIEGE_TENT 2), then build
         * progress buildingProgress*100/640 followed by '% Complete'.
         */
        void __cdecl RenderBuildingMenu_Siegetent_Trebuchet();

        /**
         * Siege-tent panel while a Siege Tower is being built: draws the label (TEXT_IN_SIEGE_TENT 3), then build
         * progress buildingProgress*100/1280 followed by '% Complete'.
         */
        void __cdecl RenderBuildingMenu_Siegetent_Siegetower();

        /**
         * Siege-tent panel while a Battering Ram is being built: draws the label (TEXT_IN_SIEGE_TENT 4), then build
         * progress buildingProgress*100/640 followed by '% Complete'.
         */
        void __cdecl RenderBuildingMenu_Siegetent_BatteringRam();

        /**
         * Siege-tent panel while a Portable Shield is being built: draws the label (TEXT_IN_SIEGE_TENT 5), then
         * build progress buildingProgress*100/120 followed directly by '% Complete' (TEXT_IN_SIEGE_TENT 6,
         * keepOffsetX). The iVar temporaries are reused argument slots for the two renderTextToScreen calls.
         */
        void __cdecl RenderBuildingMenu_Siegetent_Shield();

        /**
         * Draws the health bar of the selected tower/gatehouse in the building panel: health percent =
         * currentHealth*100/maxHealth (0 if either is < 1); black border box, red background, and if percent > 1 a
         * lime fill of width percent/2 px (50 px = 100%); then a centered 'current/max' text printed with sprintf
         * from Building.currentHealth/maxHealth (accessed as resources-0x14/-0x12, i.e. offsets 0x10C/0x10E).
         */
        void __cdecl RenderBuildingMenu_RenderTowerAndGateHealth();

        /**
         * Draws the Gatehouse panel title, then the shared tower/gate health bar
         * (RenderBuildingMenu_RenderTowerAndGateHealth).
         */
        void __cdecl RenderBuildingMenu_Gatehouse();

        /**
         * Draws the Tower panel: title 'Tower' (TEXT_IN_TOWER 0, font 0x10), a multi-line description chosen by
         * TEXT_IN_TOWER index (buildingType - 0x49) for the specific tower type (wrap width 0x136, font 0x12), and
         * the shared tower/gate health bar.
         */
        void __cdecl RenderBuildingMenu_Tower();

    } // namespace BuildingMenus
} // namespace UI
} // namespace OpenSHC
