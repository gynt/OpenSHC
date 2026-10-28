/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Buildings/BuildingDefinedData.hpp'
*/

#pragma once

#include "OpenSHC/Common/TruncatedInt.hpp"
#include "OpenSHC/Coordinates/XYPairShort.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeInt.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeShort.hpp"
#include "OpenSHC/Map/Navigation/Algorithms/XYPair.hpp"
#include "OpenSHC/Map/Units/UnitTypeInt.hpp"
#include "OpenSHC/Util/FunctionTypes/NoArgCallback.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Common::TruncatedInt;
        using OpenSHC::Coordinates::XYPairShort;
        using OpenSHC::Map::Buildings::BuildingTypeInt;
        using OpenSHC::Map::Buildings::BuildingTypeShort;
        using OpenSHC::Map::Navigation::Algorithms::XYPair;
        using OpenSHC::Map::Units::UnitTypeInt;
        using OpenSHC::Util::FunctionTypes::NoArgCallback;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)
        // SIZE: 0x0000B0F4
        typedef struct BuildingDefinedData {

            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Fletcher bow, work state 1, GM_SOLITARY only. Starts at offset 0 of the struct; updateBuildings also
            // uses its address + 0x34 + type*4 to reach BuildingUpdateFunctions[].
            byte fletcherBowPhase1FramesSolitary[52]; // 0x00000000 length: 52
            NoArgCallback* BuildingUpdateFunctions[110]; // 0x00000034 length: 440
            BuildingTypeShort BuildingPrioritiesWhenNoFire[32]; // 0x000001EC length: 64
            BuildingTypeShort BuildingPrioritiesWhenFire[32]; // 0x0000022C length: 64
            UnitTypeInt WorkerTypeForBuildingType[110]; // 0x0000026C length: 440
            BOOLEnum ABuildingTypeValueArray[110]; // 0x00000424 length: 440
            int BuildingPlacement_HeightLimit[110]; // 0x000005DC length: 440
            int BuildingPlacement_MaxHeightDifference[110]; // 0x00000794 length: 440
            int BuildingPlacement_Property_3[110]; // 0x0000094C length: 440
            int BuildingPlacement_Property_4[110]; // 0x00000B04 length: 440
            int BuildingPlacement_Property_5[110]; // 0x00000CBC length: 440
            int BuildingPlacement_Property_6[110]; // 0x00000E74 length: 440
            int BuildingPlacement_Property_7[110]; // 0x0000102C length: 440
            TruncatedInt EmployeeCountPerBuildingType[110]; // 0x000011E4 length: 440
            int StorageLimitResourceTypeArray[26]; // 0x0000139C length: 104
            // Per building type (TruncatedInt, short used): default of Building.unknownFlag3 (setupBuildingData);
            // computeTileLuminescence ignores the building height of such tiles (getBuildingFlag3) when casting
            // shade rays.
            TruncatedInt ignoreHeightForLightPerType[110]; // 0x00001404 length: 440
            // Per building type (short): default for Building.flag1 (setupBuildingData, UpgradeBuildingFlag1);
            // getBuildingFlag1 is used by updateLogicalTileMapRelatedSections to decide MiscDisplayLayer unit-
            // occlusion bits next to buildings.
            TruncatedInt buildingFlag1PerType[110]; // 0x000015BC length: 440
            // Per building type BOOL: when TRUE, tiles of that building type add a path-linkage bit in
            // updatePathLinkageLayerBasedOnBuildingsUnk (treated like walls/raised tiles).
            BOOLEnum linksPathAcrossPerType[110]; // 0x00001774 length: 440
            // Per building type (TruncatedInt, byte used): default of Building.blocksAIZoneSpread (setupBuildingData,
            // UpgradeBuildingProperties1); tiles of buildings with the flag are skipped by the phase-2 AI zone
            // marking.
            // Per building type (TruncatedInt, byte used): default of Building.unknownFlag4 (setupBuildingData,
            // UpgradeBuildingProperties1); tiles of buildings with the flag are skipped by the phase-2 AI zone
            // marking.
            TruncatedInt blocksAIZoneSpreadPerType[110]; // 0x0000192C length: 440
            int BuildingTypeHasHealth[110]; // 0x00001AE4 length: 440
            int BuildingIsGateHouseArray[110]; // 0x00001C9C length: 440
            int BuildingIsKeepArray[110]; // 0x00001E54 length: 440
            BOOLEnum IsGateOrTowerArray[110]; // 0x0000200C length: 440
            BOOLEnum field23_0x21c4[110]; // 0x000021C4 length: 440
            // Per building type (short): default for Building.flag2 (setupBuildingData, UpgradeBuildingFlag1);
            // checked with stockpiles in updateLogicalTileMapRelatedSections for wall-adjacent occlusion bits.
            TruncatedInt buildingFlag2PerType[110]; // 0x0000237C length: 440
            int BuildingShowRubbleWhenDestroyed[110]; // 0x00002534 length: 440
            int BuildingTypeOwnable[110]; // 0x000026EC length: 440
            // from my previous experience, I though it would be a int[106], but it seems that there are 4 more ints
            // (at least, the last 4 don't get referenced, so this seems reasonable
            TruncatedInt BuildingHP[110]; // 0x000028A4 length: 440
            BuildingTypeInt StorageBuildingTypeArray[26]; // 0x00002A5C length: 104
            TruncatedInt BuildingNumberOfPopulationProvided[110]; // 0x00002AC4 length: 440
            int field30_0x2c7c[88]; // 0x00002C7C length: 352
            // [UNK PASS] was WheatFieldTile_Unknown
            int WheatFieldTileUpdateOrder[36]; // 0x00002DDC length: 144
            TruncatedInt Building_SpriteSheet_ID_Array_1[110]; // 0x00002E6C length: 440
            int Building_Sprite_ID_Array_1[110]; // 0x00003024 length: 440
            int Building_Sprite_ID_Array_2[110]; // 0x000031DC length: 440
            int VisuallyActiveSpriteIDOffsets[110]; // 0x00003394 length: 440
            int GFXOffsets[110]; // 0x0000354C length: 440
            int GFXOffsets3[110]; // 0x00003704 length: 440
            TruncatedInt SpriteIDs2[110]; // 0x000038BC length: 440
            short SpriteOffsets1[110][2][2]; // 0x00003A74 length: 880
            int AnimAdvanceThrottles[110]; // 0x00003DE4 length: 440
            int BuildingHeights[110]; // 0x00003F9C length: 440
            // Per building type: weight added to finalResults.finalBuildingsDestroyedWeighted of the attacker when
            // a building of that type is destroyed (end-of-game statistics).
            int destroyedScorePerType[110]; // 0x00004154 length: 440
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Fletcher bow, work state 0, GM_SOLITARY (FletcherWorkshopAnimationCycle in other modes).
            byte fletcherBowFramesSolitary[312]; // 0x0000430C length: 312
            byte FletcherWorkshopAnimationCycle[160]; // 0x00004444 length: 160
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Fletcher crossbow, state 0, GM_SOLITARY; frame +0x24.
            byte fletcherCrossbowFramesSolitary[400]; // 0x000044E4 length: 400
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Fletcher crossbow, state 0, other game modes; frame +0x24.
            byte fletcherCrossbowFrames[608]; // 0x00004674 length: 608
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Fletcher crossbow, state 1, GM_SOLITARY only; frame +0x24.
            byte fletcherCrossbowPhase1FramesSolitary[56]; // 0x000048D4 length: 56
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Armorer state 0 in GM_SOLITARY; entry 5 triggers FX_ARMOUR_HIT (checked in all modes).
            byte armorerFramesSolitary[448]; // 0x0000490C length: 448
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Armorer state 0 outside GM_SOLITARY.
            byte armorerFrames[112]; // 0x00004ACC length: 112
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Armorer state 1 (finishing phase).
            byte armorerPhase1Frames[20]; // 0x00004B3C length: 20
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Hunter's post state 0 (hunter arriving, fade).
            byte hunterPostPhase0Frames[24]; // 0x00004B50 length: 24
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Hunter's post states 1..6 (butchering, FX_HUNTER_CUT at index 4); each finished cycle adds 1 RT_MEAT.
            byte hunterPostButcherFrames[40]; // 0x00004B68 length: 40
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Hunter's post state 7 (final phase, completes a work cycle).
            byte hunterPostPhase7Frames[28]; // 0x00004B90 length: 28
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Woodcutter's hut work animation; frame value 0x10 triggers FX_SAW.
            byte woodcutterFrames[104]; // 0x00004BAC length: 104
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Bakery state 0 (baking, FX_BAKE/FX_BAKE2).
            byte bakeryPhase0Frames[396]; // 0x00004C14 length: 396
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Bakery state 1 (end of batch).
            byte bakeryPhase1Frames[20]; // 0x00004DA0 length: 20
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Brewery state 0 (FX_STIR).
            byte breweryStirPhase0Frames[420]; // 0x00004DB4 length: 420
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Brewery states 2 and 4 (FX_STIR).
            byte breweryStirPhase24Frames[44]; // 0x00004F58 length: 44
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Brewery state 7 (FX_STIR at index 5); completing it ends a batch (field13_0x28++, field14_0x2c = 1).
            // The proposal had states 6/7 swapped.
            byte breweryStirPhase7Frames[48]; // 0x00004F84 length: 48
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Brewery states 1/3/5; frame +0x10.
            byte breweryPhase135Frames[36]; // 0x00004FB4 length: 36
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Brewery state 6; frame +0x20.
            byte breweryPhase6Frames[36]; // 0x00004FD8 length: 36
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Blacksmith forge overlay (field20_0x38) when the bellows are not working.
            byte blacksmithForgeIdleFrames[20]; // 0x00004FFC length: 20
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Blacksmith forge overlay with bellows working (FX_BS_BELLOW).
            byte blacksmithBellowsFrames[44]; // 0x00005010 length: 44
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Blacksmith sword, state 0; frame +0x18.
            byte blacksmithSwordPhase0Frames[88]; // 0x0000503C length: 88
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Blacksmith sword, state 2; frame +0x18.
            byte blacksmithSwordPhase2Frames[44]; // 0x00005094 length: 44
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Blacksmith sword, state 4; frame +0x18.
            byte blacksmithSwordPhase4Frames[12]; // 0x000050C0 length: 12
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Blacksmith sword states 1/3/5/6 (FX_BS_ANVIL); frame +0x18.
            byte blacksmithSwordAnvilFrames[64]; // 0x000050CC length: 64
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Blacksmith sword state 7 (FX_BS_COOL); frame +0x18.
            byte blacksmithSwordCoolFrames[56]; // 0x0000510C length: 56
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Blacksmith mace state 0 in GM_SOLITARY; frame +0x6e.
            byte blacksmithMacePhase0FramesSolitary[72]; // 0x00005144 length: 72
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Blacksmith mace state 1 (FX_BS_POUR/FX_BS_OPEN); frame +0x6e.
            byte blacksmithMacePourFrames[80]; // 0x0000518C length: 80
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Blacksmith mace state 2 (FX_BS_FILE) in GM_SOLITARY; frame +0xaf.
            byte blacksmithMaceFileFramesSolitary[244]; // 0x000051DC length: 244
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Blacksmith mace state 0 outside GM_SOLITARY; frame +0x6e.
            byte blacksmithMacePhase0Frames[36]; // 0x000052D0 length: 36
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Blacksmith mace state 2 (FX_BS_FILE) outside GM_SOLITARY; frame +0xaf.
            byte blacksmithMaceFileFrames[112]; // 0x000052F4 length: 112
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Poleturner pike, state 0.
            byte poleturnerPikePhase0Frames[88]; // 0x00005364 length: 88
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Poleturner pike states 1-2 (FX_POLE_GRIND) in GM_SOLITARY.
            byte poleturnerPikeGrindFramesSolitary[200]; // 0x000053BC length: 200
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Poleturner pike states 1-2 (FX_POLE_GRIND) outside GM_SOLITARY.
            byte poleturnerPikeGrindFrames[36]; // 0x00005484 length: 36
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Poleturner pike state 3; frame +0x3d.
            byte poleturnerPikePhase3Frames[36]; // 0x000054A8 length: 36
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Poleturner spear state 0 (FX_POLE_TURN) in GM_SOLITARY.
            byte poleturnerSpearFramesSolitary[144]; // 0x000054CC length: 144
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Poleturner spear state 0 (FX_POLE_TURN) outside GM_SOLITARY.
            byte poleturnerSpearFrames[72]; // 0x0000555C length: 72
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Poleturner spear state 1.
            byte poleturnerSpearPhase1Frames[28]; // 0x000055A4 length: 28
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Second overlay (field21_0x3c, frame +0x10) shared by blacksmith, bakery and brewery, advanced every
            // 4th tick (field28_0x58 divider) while a worker is present; chimney smoke per the proposal (GID not
            // checked).
            byte chimneySmokeFrames[20]; // 0x000055C0 length: 20
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Brewery overlay field20_0x38 (+0x30) while active.
            byte breweryOverlayFrames[260]; // 0x000055D4 length: 260
            byte AnimTannerSolitary[44]; // 0x000056D8 length: 44
            byte AnimTanner[12]; // 0x00005704 length: 12
            byte AnimTanner3[28]; // 0x00005710 length: 28
            byte AnimTanner4[32]; // 0x0000572C length: 32
            byte AnimTannerSolitary2[56]; // 0x0000574C length: 56
            byte AnimTanner2[16]; // 0x00005784 length: 16
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Tanner state 7 (FX_TANNER_CUT) in GM_SOLITARY; frame +0x19.
            byte tannerCutFramesSolitary[92]; // 0x00005794 length: 92
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Tanner state 7 (FX_TANNER_CUT) outside GM_SOLITARY; frame +0x19.
            byte tannerCutFrames[36]; // 0x000057F0 length: 36
            byte AnimTanner5[40]; // 0x00005814 length: 40
            byte AnimTannerSolitary4[152]; // 0x0000583C length: 152
            byte AnimTanner6[152]; // 0x000058D4 length: 152
            byte AnimTanner7[172]; // 0x0000596C length: 172
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Tunnel entrance while the tunneler is digging (unit state 9); 0xff ends digging.
            byte tunnelDigFrames[52]; // 0x00005A18 length: 52
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Campground fire animation (frame +0xb); each wrap counts a cycle and plays FX_CAMPFIRE.
            byte campfireFrames[36]; // 0x00005A4C length: 36
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Quarry puller (ox/rope) layer state 1 (FX_PULLER_LOWER).
            byte quarryPullerLowerFrames[28]; // 0x00005A70 length: 28
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Quarry puller layer state 3 (FX_PULLER_STRAIN/IMPACT); frame +1.
            byte quarryPullerStrainFrames[64]; // 0x00005A8C length: 64
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Quarry puller layer state 5 (FX_PULLER_ROCK); frame +1.
            byte quarryPullerRockFrames[20]; // 0x00005ACC length: 20
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Quarry puller layer state 6 (FX_PULLER_RETURN); frame +1.
            byte quarryPullerReturnFrames[24]; // 0x00005AE0 length: 24
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Quarry stone block/rope layer (field21_0x3c) state 1; frame +0x3d.
            byte quarryBlockPhase1Frames[28]; // 0x00005AF8 length: 28
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Quarry block layer state 3; frame +0x53.
            byte quarryBlockPhase3Frames[56]; // 0x00005B14 length: 56
            // [063 0x0041D510] frame-delta table for quarry block layer state 5 (+0x66), terminated by value < 1
            byte quarryBlockAnimState5Frames[24]; // 0x00005B4C length: 24
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Quarry block layer state 6; frame +0x6c.
            byte quarryBlockPhase6Frames[32]; // 0x00005B64 length: 32
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Quarry pryer (worker 0) layer state 0; frame +0x7a.
            byte quarryPryerIdleFrames[16]; // 0x00005B84 length: 16
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Quarry pryer state 1; frame +0x7a.
            byte quarryPryerPhase1Frames[64]; // 0x00005B94 length: 64
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Quarry pryer state 2; frame +0x7a.
            byte quarryPryerPhase2Frames[112]; // 0x00005BD4 length: 112
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Quarry pryer state 3 (FX_PRYER_LEVER); frame +0x86.
            byte quarryPryerLever3Frames[20]; // 0x00005C44 length: 20
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Quarry pryer state 4 (FX_PRYER_LEVER); frame +0x86.
            byte quarryPryerLever4Frames[40]; // 0x00005C58 length: 40
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Quarry pryer state 5 (FX_PRYER_LEVER); frame +0x86.
            byte quarryPryerLever5Frames[60]; // 0x00005C80 length: 60
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Quarry pryer state 6 (FX_PRYER_LEVER); frame +0x86.
            byte quarryPryerLever6Frames[72]; // 0x00005CBC length: 72
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Quarry pryer state 8; frame +0x8d.
            byte quarryPryerPhase8Frames[24]; // 0x00005D04 length: 24
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Quarry pryer state 9; frame +0xa5.
            byte quarryPryerPhase9Frames[64]; // 0x00005D1C length: 64
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Quarry pryer state 10; frame +0xb9.
            byte quarryPryerPhase10Frames[16]; // 0x00005D5C length: 16
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Quarry mason (worker 2) layer state 1 (FX_MASON_CHIP/CRUMBLE); frame +0xc1.
            byte quarryMasonChipFrames[376]; // 0x00005D6C length: 376
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Quarry mason state 2; frame +0xc1.
            byte quarryMasonPhase2Frames[264]; // 0x00005EE4 length: 264
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Quarry mason state 3; frame +0xc1.
            byte quarryMasonPhase3Frames[304]; // 0x00005FEC length: 304
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Quarry mason state 4; frame +0xc1.
            byte quarryMasonPhase4Frames[384]; // 0x0000611C length: 384
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Iron mine main layer (field20_0x38) state 0 (entry 0 / negative ends).
            byte ironMinePhase0Frames[88]; // 0x0000629C length: 88
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Iron mine main layer state 2.
            byte ironMinePhase2Frames[80]; // 0x000062F4 length: 80
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Iron mine main layer state 1; frame +0x76.
            byte ironMinePhase1Frames[472]; // 0x00006344 length: 472
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Iron mine main layer state 3 (FX_IRON_PULL); frame +0x26.
            byte ironMinePullFrames[112]; // 0x0000651C length: 112
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Iron mine main layer state 5; frame +0x3a.
            byte ironMinePhase5Frames[104]; // 0x0000658C length: 104
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Iron mine main layer state 6 (idle while the mine store is full); frame +0x4e.
            byte ironMineIdleFrames[184]; // 0x000065F4 length: 184
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Iron mine second layer (field22_0x40, killingPitField state 1); frame +0x32.
            byte ironMineLayer2Phase1Frames[24]; // 0x000066AC length: 24
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Iron mine second layer state 3; frame +0x32.
            byte ironMineLayer2Phase3Frames[12]; // 0x000066C4 length: 12
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Iron mine smelting layer (field21_0x3c, field117_0x11a state 0); frame +0x7e.
            byte ironMineSmeltPhase0Frames[60]; // 0x000066D0 length: 60
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Iron mine smelting layer state 1 (FX_IRON_STRAIN/DUMP/LDUMP/BOIL); frame +0x86; also sets
            // ironMinerBlendLevel.
            byte ironMineSmeltPhase1Frames[452]; // 0x0000670C length: 452
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Iron mine smelting layer state 2; frame +0x86.
            byte ironMineSmeltPhase2Frames[36]; // 0x000068D0 length: 36
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Iron mine pouring layer (field23_0x44, FX_IRON_POUR); frame +0x5e; completion adds 1 iron.
            byte ironMinePourFrames[84]; // 0x000068F4 length: 84
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Pitch rig states 1-3.
            byte pitchRigPhase123Frames[52]; // 0x00006948 length: 52
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Pitch rig state 0.
            byte pitchRigPhase0Frames[56]; // 0x0000697C length: 56
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Pitch rig state 4 (completes a work cycle).
            byte pitchRigPhase4Frames[104]; // 0x000069B4 length: 104
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Mill sails overlay (field23_0x44); advance speed depends on the grind timer.
            byte millSailFrames[16]; // 0x00006A1C length: 16
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Mill grinding layer field20_0x38 (+0xf).
            byte millInactiveLayerFrames[16]; // 0x00006A2C length: 16
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Mill active grinding layer field21_0x3c (+0x1e); the value is immediately overwritten by the sail-
            // based frame.
            byte millActiveLayerFrames[16]; // 0x00006A3C length: 16
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Mill miller layer (field22_0x40) state 1; frame +0x2d.
            byte millerPhase1Frames[136]; // 0x00006A4C length: 136
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Mill miller layer (field22_0x40) state 2 (killingPitField == 2); frame +0x3d.
            byte millerPhase2Frames[16]; // 0x00006AD4 length: 16
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Drawbridge state 1 (FX_DRAWBRIDGE_RAISING/RAISED).
            byte drawbridgeRaiseFrames[32]; // 0x00006AE4 length: 32
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Drawbridge state 3 (FX_DRAWBRIDGE_LOWERING/LOWERED).
            byte drawbridgeLowerFrames[36]; // 0x00006B04 length: 36
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Large/small gatehouse door opening (phase 3, FX_PC_LIFT).
            byte gatehouseOpenFrames[28]; // 0x00006B28 length: 28
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Large/small gatehouse door closing (phase 1, FX_PC_DROP/SLAM).
            byte gatehouseCloseFrames[32]; // 0x00006B44 length: 32
            // Dairy farm state 2 (new cow appearing) overlay frames for field20_0x38 (+0x37), terminated by the
            // value 0x18 (then the cow is spawned with a fade).
            byte dairyCowSpawnFrames[264]; // 0x00006B64 length: 264
            // Dairy farm state 4 milking overlay frames for field20_0x38.
            byte dairyMilkingFrames[664]; // 0x00006C6C length: 664
            // Dairy farm state 4 second overlay (field21_0x3c, +0x10), 0-terminated; FX_COW_MILK every 12 frames,
            // FX_MILK_POUR at index 0x170.
            byte dairyMilkBucketFrames[448]; // 0x00006F04 length: 448
            // Dairy farm state 5 overlay (field22_0x40, +0x2f), 0-terminated; then state 6 stores the cheese.
            byte dairyPhase5Frames[152]; // 0x000070C4 length: 152
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Stables: idle animation of each of the 4 horse layers (field20..field23).
            byte stablesHorseIdleFrames[644]; // 0x0000715C length: 644
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle. Oil
            // smelter state 3 (boiling); frame +0x20.
            byte oilSmelterPhase3Frames[52]; // 0x000073E0 length: 52
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle. Oil
            // smelter state 4 (boiling, produces a pot); frame +0x20.
            byte oilSmelterPhase4Frames[80]; // 0x00007414 length: 80
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle. Oil
            // smelter state 5; frame +0x20.
            byte oilSmelterPhase5Frames[48]; // 0x00007464 length: 48
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle. Oil
            // smelter state 6 (pot hand-over start).
            byte oilSmelterPhase6Frames[48]; // 0x00007494 length: 48
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle. Oil
            // smelter state 7 (FX_POT_OPEN/FX_OIL_REFILL; removes a pot and serves a waiting engineer).
            byte oilSmelterPhase7Frames[48]; // 0x000074C4 length: 48
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle. Oil
            // smelter state 8.
            byte oilSmelterPhase8Frames[48]; // 0x000074F4 length: 48
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle. Oil
            // smelter overlay field20_0x38 while no pots are stored (resources[7] < 1).
            byte oilSmelterFireEmptyFrames[48]; // 0x00007524 length: 48
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle. Oil
            // smelter overlay field20_0x38 while pots are stored.
            byte oilSmelterFireFullFrames[48]; // 0x00007554 length: 48
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle. Oil
            // smelter pot overlay field21_0x3c, chosen by the stored pot count.
            byte oilSmelterPotFrames[40]; // 0x00007584 length: 40
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle. Oil
            // smelter flare-up overlay after a pot is produced (FX_POT_FLARE_UP).
            byte oilSmelterFlareUpFrames[80]; // 0x000075AC length: 80
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Gallows animation (fear level < -2).
            byte gallowsFrames[40]; // 0x000075FC length: 40
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Stocks animation (fear level < -1, FX_STOCKS).
            byte stocksFrames[72]; // 0x00007624 length: 72
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Dungeon animation (fear level < -3).
            byte dungeonFrames[80]; // 0x0000766C length: 80
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Dunking stool animation (fear level < -4, FX_WH_DUNK/BREATH/LIFT).
            byte dunkingStoolFrames[172]; // 0x000076BC length: 172
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Gibbet animation (fear level < -3).
            byte gibbetFrames[36]; // 0x00007768 length: 36
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Burning stake animation (fear level < -4, FX_WITCH_BURN/SCREAM).
            byte burningStakeFrames[88]; // 0x0000778C length: 88
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Stretching rack animation (fear level < -2).
            byte stretchingRackFrames[160]; // 0x000077E4 length: 160
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Chopping block overlay animation (field20_0x38, fear level < -3).
            byte choppingBlockFrames[200]; // 0x00007884 length: 200
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle. Dog
            // cage animation while dogs wait inside.
            byte dogCageFrames[40]; // 0x0000794C length: 40
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Maypole dance animation (high popularity; FX_MAYPOLE every 8th cycle).
            byte maypoleDanceFrames[80]; // 0x00007974 length: 80
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Maypole idle animation when popularity is below the threshold; frame +0x20.
            byte maypoleIdleFrames[80]; // 0x000079C4 length: 80
            // Signed-byte animation frame table indexed by an animation counter; entry <1 ends/wraps the cycle.
            // Dancing bear animation (fear level > 2).
            byte dancingBearFrames[344]; // 0x00007A14 length: 344
            byte AnimMarketPlace[104]; // 0x00007B6C length: 104
            // Apothecary work animation frames (negative entry wraps and counts a work cycle).
            byte apothecaryFrames[104]; // 0x00007BD4 length: 104
            // Inn overlay field22_0x40 while the innkeeper is serving (0-terminated).
            byte innkeeperServeFrames[88]; // 0x00007C3C length: 88
            // Inn overlay field21_0x3c when drunkardSpawnCountdown is 0 (0-terminated).
            byte innIdleOverlayFrames[136]; // 0x00007C94 length: 136
            // Inn overlay field21_0x3c while drunkardSpawnCountdown runs (0-terminated).
            byte innBusyOverlayFrames[140]; // 0x00007D1C length: 140
            // Inn overlay field20_0x38 frames (0-terminated); the result is overwritten with 0 right after, so
            // effectively unused.
            byte innOverlay0Frames[36]; // 0x00007DA8 length: 36
            // Inn overlay field23_0x44 while drunkardSpawnCountdown runs (0-terminated).
            byte innOverlay3Frames[80]; // 0x00007DCC length: 80
            // Owner flag animation frames indexed by ownerFlagFrame/2 (entry <1 restarts); used by ~31 building
            // updates for the multiplayer owner flag.
            byte ownerFlagFrames[52]; // 0x00007E1C length: 52
            int BuildingAccessibleTilesCountForOneLarger[15]; // 0x00007E50 length: 60
            // Tile (x,y) offsets of the full ring around a 1x1 footprint including the 4 corner tiles (4*2 = 8
            // entries, BuildingAccessibleTilesCountForOneLarger[1]), starting on the y=-1 edge and going clockwise
            // (e.g. size 1: (1,-1),(1,0),(1,1),(0,1),...); setupNextCandidateLocationComputeOffsets2 case 1 copies
            // entry `try` to DAT_TempX/YOffset.
            XYPair candidateOffsetsSize1[8]; // 0x00007E8C length: 64
            // Tile (x,y) offsets of the full ring around a 2x2 footprint including the 4 corner tiles (4*3 = 12
            // entries, BuildingAccessibleTilesCountForOneLarger[2]), starting on the y=-1 edge and going clockwise
            // (e.g. size 1: (1,-1),(1,0),(1,1),(0,1),...); setupNextCandidateLocationComputeOffsets2 case 2 copies
            // entry `try` to DAT_TempX/YOffset.
            XYPair candidateOffsetsSize2[12]; // 0x00007ECC length: 96
            // Tile (x,y) offsets of the full ring around a 3x3 footprint including the 4 corner tiles (4*4 = 16
            // entries, BuildingAccessibleTilesCountForOneLarger[3]), starting on the y=-1 edge and going clockwise
            // (e.g. size 1: (1,-1),(1,0),(1,1),(0,1),...); setupNextCandidateLocationComputeOffsets2 case 3 copies
            // entry `try` to DAT_TempX/YOffset.
            XYPair candidateOffsetsSize3[16]; // 0x00007F2C length: 128
            // Tile (x,y) offsets of the full ring around a 4x4 footprint including the 4 corner tiles (4*5 = 20
            // entries, BuildingAccessibleTilesCountForOneLarger[4]), starting on the y=-1 edge and going clockwise
            // (e.g. size 1: (1,-1),(1,0),(1,1),(0,1),...); setupNextCandidateLocationComputeOffsets2 case 4 copies
            // entry `try` to DAT_TempX/YOffset.
            XYPair candidateOffsetsSize4[20]; // 0x00007FAC length: 160
            // Tile (x,y) offsets of the full ring around a 5x5 footprint including the 4 corner tiles (4*6 = 24
            // entries, BuildingAccessibleTilesCountForOneLarger[5]), starting on the y=-1 edge and going clockwise
            // (e.g. size 1: (1,-1),(1,0),(1,1),(0,1),...); setupNextCandidateLocationComputeOffsets2 case 5 copies
            // entry `try` to DAT_TempX/YOffset.
            XYPair candidateOffsetsSize5[24]; // 0x0000804C length: 192
            // Tile (x,y) offsets of the full ring around a 6x6 footprint including the 4 corner tiles (4*7 = 28
            // entries, BuildingAccessibleTilesCountForOneLarger[6]), starting on the y=-1 edge and going clockwise
            // (e.g. size 1: (1,-1),(1,0),(1,1),(0,1),...); setupNextCandidateLocationComputeOffsets2 case 6 copies
            // entry `try` to DAT_TempX/YOffset.
            XYPair candidateOffsetsSize6[28]; // 0x0000810C length: 224
            // Tile (x,y) offsets of the full ring around a 7x7 footprint including the 4 corner tiles (4*8 = 32
            // entries, BuildingAccessibleTilesCountForOneLarger[7]), starting on the y=-1 edge and going clockwise
            // (e.g. size 1: (1,-1),(1,0),(1,1),(0,1),...); setupNextCandidateLocationComputeOffsets2 case 7 copies
            // entry `try` to DAT_TempX/YOffset.
            XYPair candidateOffsetsSize7[32]; // 0x000081EC length: 256
            // Tile (x,y) offsets of the full ring around a 8x8 footprint including the 4 corner tiles (4*9 = 36
            // entries, BuildingAccessibleTilesCountForOneLarger[8]), starting on the y=-1 edge and going clockwise
            // (e.g. size 1: (1,-1),(1,0),(1,1),(0,1),...); setupNextCandidateLocationComputeOffsets2 case 8 copies
            // entry `try` to DAT_TempX/YOffset.
            XYPair candidateOffsetsSize8[36]; // 0x000082EC length: 288
            // Tile (x,y) offsets of the full ring around a 9x9 footprint including the 4 corner tiles (4*10 = 40
            // entries, BuildingAccessibleTilesCountForOneLarger[9]), starting on the y=-1 edge and going clockwise
            // (e.g. size 1: (1,-1),(1,0),(1,1),(0,1),...); setupNextCandidateLocationComputeOffsets2 case 9 copies
            // entry `try` to DAT_TempX/YOffset.
            XYPair candidateOffsetsSize9[40]; // 0x0000840C length: 320
            // Tile (x,y) offsets of the full ring around a 10x10 footprint including the 4 corner tiles (4*11 = 44
            // entries, BuildingAccessibleTilesCountForOneLarger[10]), starting on the y=-1 edge and going clockwise
            // (e.g. size 1: (1,-1),(1,0),(1,1),(0,1),...); setupNextCandidateLocationComputeOffsets2 case 10 copies
            // entry `try` to DAT_TempX/YOffset.
            XYPair candidateOffsetsSize10[44]; // 0x0000854C length: 352
            // Tile (x,y) offsets of the full ring around a 11x11 footprint including the 4 corner tiles (4*12 = 48
            // entries, BuildingAccessibleTilesCountForOneLarger[11]), starting on the y=-1 edge and going clockwise
            // (e.g. size 1: (1,-1),(1,0),(1,1),(0,1),...); setupNextCandidateLocationComputeOffsets2 case 11 copies
            // entry `try` to DAT_TempX/YOffset.
            XYPair candidateOffsetsSize11[48]; // 0x000086AC length: 384
            // Tile (x,y) offsets of the full ring around a 12x12 footprint including the 4 corner tiles (4*13 = 52
            // entries, BuildingAccessibleTilesCountForOneLarger[12]), starting on the y=-1 edge and going clockwise
            // (e.g. size 1: (1,-1),(1,0),(1,1),(0,1),...); setupNextCandidateLocationComputeOffsets2 case 12 copies
            // entry `try` to DAT_TempX/YOffset.
            XYPair candidateOffsetsSize12[52]; // 0x0000882C length: 416
            // XYPair[116] is two rings: entries 0..55 = ring around a 13x13 footprint (-1..13), entries 56..115 =
            // ring around 14x14 (-1..14). Only the size-13 ring is referenced:
            // setupNextCandidateLocationComputeOffsets2 switch bounds size<=13 and reads [i*8+0x5C0340].
            XYPair candidateOffsetsSize13[56]; // 0x000089CC length: 448
            // Second ring (60 entries, 16x16 perimeter of a 14x14 footprint) inside the old XYPair[116]; data-
            // verified, not referenced by code.
            XYPair candidateOffsetsSize14[60]; // 0x00008B8C length: 480
            int BuildingAccessibleTilesCount[15]; // 0x00008D6C length: 60
            // Tile (x,y) offsets of the 4 tiles edge-adjacent to a 1x1 footprint, without the corner tiles
            // (BuildingAccessibleTilesCount[1]; e.g. size 1: (0,-1),(1,0),(0,1),(-1,0));
            // setupBuildingEntrancesOffset case 1 copies entry param_3 to DAT_TempX/YOffset.
            XYPair entranceOffsetsSize1[4]; // 0x00008DA8 length: 32
            undefined1 padding_0x8dc8[4]; // 0x00008DC8 length: 4
            // Tile (x,y) offsets of the 8 tiles edge-adjacent to a 2x2 footprint, without the corner tiles
            // (BuildingAccessibleTilesCount[2]; e.g. size 1: (0,-1),(1,0),(0,1),(-1,0));
            // setupBuildingEntrancesOffset case 2 copies entry param_3 to DAT_TempX/YOffset.
            XYPair entranceOffsetsSize2[8]; // 0x00008DCC length: 64
            // Tile (x,y) offsets of the 12 tiles edge-adjacent to a 3x3 footprint, without the corner tiles
            // (BuildingAccessibleTilesCount[3]; e.g. size 1: (0,-1),(1,0),(0,1),(-1,0));
            // setupBuildingEntrancesOffset case 3 copies entry param_3 to DAT_TempX/YOffset.
            XYPair entranceOffsetsSize3[12]; // 0x00008E0C length: 96
            // Tile (x,y) offsets of the 16 tiles edge-adjacent to a 4x4 footprint, without the corner tiles
            // (BuildingAccessibleTilesCount[4]; e.g. size 1: (0,-1),(1,0),(0,1),(-1,0));
            // setupBuildingEntrancesOffset case 4 copies entry param_3 to DAT_TempX/YOffset.
            XYPair entranceOffsetsSize4[16]; // 0x00008E6C length: 128
            // Tile (x,y) offsets of the 20 tiles edge-adjacent to a 5x5 footprint, without the corner tiles
            // (BuildingAccessibleTilesCount[5]; e.g. size 1: (0,-1),(1,0),(0,1),(-1,0));
            // setupBuildingEntrancesOffset case 5 copies entry param_3 to DAT_TempX/YOffset.
            XYPair entranceOffsetsSize5[20]; // 0x00008EEC length: 160
            // Tile (x,y) offsets of the 24 tiles edge-adjacent to a 6x6 footprint, without the corner tiles
            // (BuildingAccessibleTilesCount[6]; e.g. size 1: (0,-1),(1,0),(0,1),(-1,0));
            // setupBuildingEntrancesOffset case 6 copies entry param_3 to DAT_TempX/YOffset.
            XYPair entranceOffsetsSize6[24]; // 0x00008F8C length: 192
            // Tile (x,y) offsets of the 28 tiles edge-adjacent to a 7x7 footprint, without the corner tiles
            // (BuildingAccessibleTilesCount[7]; e.g. size 1: (0,-1),(1,0),(0,1),(-1,0));
            // setupBuildingEntrancesOffset case 7 copies entry param_3 to DAT_TempX/YOffset.
            XYPair entranceOffsetsSize7[28]; // 0x0000904C length: 224
            // Tile (x,y) offsets of the 32 tiles edge-adjacent to a 8x8 footprint, without the corner tiles
            // (BuildingAccessibleTilesCount[8]; e.g. size 1: (0,-1),(1,0),(0,1),(-1,0));
            // setupBuildingEntrancesOffset case 8 copies entry param_3 to DAT_TempX/YOffset.
            XYPair entranceOffsetsSize8[32]; // 0x0000912C length: 256
            // Tile (x,y) offsets of the 36 tiles edge-adjacent to a 9x9 footprint, without the corner tiles
            // (BuildingAccessibleTilesCount[9]; e.g. size 1: (0,-1),(1,0),(0,1),(-1,0));
            // setupBuildingEntrancesOffset case 9 copies entry param_3 to DAT_TempX/YOffset.
            XYPair entranceOffsetsSize9[36]; // 0x0000922C length: 288
            // Tile offsets (x,y) used by setupBuildingEntrancesOffset case 10 (building footprint size class 10,
            // 4*10 perimeter entries) -> DAT_TempX/YOffset
            XYPair entranceOffsetsSize10[40]; // 0x0000934C length: 320
            // Tile offsets (x,y) for setupBuildingEntrancesOffset case 11 (size class 11, 44 perimeter entries)
            XYPair entranceOffsetsSize11[44]; // 0x0000948C length: 352
            // Tile offsets (x,y) for setupBuildingEntrancesOffset case 12 (48 entries); getSpriteID indexes past it
            // (decompiler overflow into following sprite tables for cesspit/statue/shrine/pond variants)
            XYPair entranceOffsetsSize12[48]; // 0x000095EC length: 384
            // Tile offsets (x,y) for setupBuildingEntrancesOffset case 13 (52 entries); other uses (getSpriteID
            // garden variants, construction preview) are out-of-range accesses into the following tables
            XYPair entranceOffsetsSize13[52]; // 0x0000976C length: 416
            XYPair field210_0x990c[56]; // 0x0000990C length: 448
            undefined1 padding_0x9acc[156]; // 0x00009ACC length: 156
            int GardenVariations[12]; // 0x00009B68 length: 48
            int UnknownVariations[13]; // 0x00009B98 length: 52
            int SomeSpriteArray1[7]; // 0x00009BCC length: 28
            int CesspitVariations[4]; // 0x00009BE8 length: 16
            int StatueVariations[5]; // 0x00009BF8 length: 20
            int ShrineVariations[5]; // 0x00009C0C length: 20
            int PondVariations[5]; // 0x00009C20 length: 20
            // [067 0x0040D120] XY offsets added to a parade-ground part position to produce troop gathering spots
            XYPairShort paradeLayoutOffsets[2][24]; // 0x00009C34 length: 192
            // [067 0x0040D120] per-row index into the layout offset table
            int paradeLayoutIndexPerRow[6]; // 0x00009CF4 length: 24
            // [067 0x0040D120] rows of 3 ints 0/1/2 choosing which parade-ground part each block of 24 positions is
            // relative to
            int paradeGroundPartSelectors[6][3]; // 0x00009D0C length: 72
            XYPairShort SearchRelatedXYOffsets_1[49]; // 0x00009D54 length: 196
            undefined1 padding_0x9e18[4]; // 0x00009E18 length: 4
            // Per barracks assembly slot (7, archer..knight order of barracksAssemblyPoints) the unit icon drawn
            // beside the assembly flag: {gmID (body sheet, e.g. 18/41/39/43/40/42/44), frame 3, xOffset (+0x29),
            // yOffset (-0x28)} passed to createFloatingLayerElement
            int barracksAssemblyUnitIcons[7][4]; // 0x00009E1C length: 112
            // Second floating icon {gmID 110, frame 3, xOff -32 (+0x29), yOff -10 (-0x28)} drawn on top of barracks
            // assembly slot 6 and mercenary assembly slot 1 (probably the mount of the mounted unit)
            int assemblyExtraIcon[4]; // 0x00009E8C length: 16
            // Per mercenary-post assembly slot (7) unit icon {gmID (Arabian body sheets 190-199), frame 3, xOffset,
            // yOffset} drawn beside the assembly flag
            int mercenaryAssemblyUnitIcons[7][4]; // 0x00009E9C length: 112
            undefined1 padding_0x9f0c[16]; // 0x00009F0C length: 16
            // Engineers' guild assembly slots (2) unit icon {gmID 86 / 35, frame 3, xOffset, yOffset}; loop ends at
            // absolute 0x5C18B8
            int engineersAssemblyUnitIcons[2][4]; // 0x00009F1C length: 32
            XYPairShort TunnelersGuildParadegroundLocationOffsets[25]; // 0x00009F3C length: 100
            undefined1 padding_0x9fa0[4]; // 0x00009FA0 length: 4
            XYPairShort EngineersParagroundOffsets[25]; // 0x00009FA4 length: 100
            undefined1 padding_0xa008[4]; // 0x0000A008 length: 4
            // Short (x,y) offsets from the oil smelter origin; resolved tiles are stored in the building's tile-ref
            // slots by setTileRefsForOilSmelter
            XYPairShort oilSmelterTileOffsets[16]; // 0x0000A00C length: 64
            // 16 raid troop tables (rows 0-7 European outpost, 8-15 Arabian; row = Building.raidTroopTableIndex) x 13
            // ints: [0] troop spawn period (minus incByFourUnk), [1] minimum period, [2] raid size base, [3] raid
            // size random range, [4..11] candidate unit types (0 = unused), [12] tribeSubtype1 of the raid tribe
            // (182/184/185). The UpdateCampGround access [0xc][i+6] is a decompiler alias of a separate
            // vclock->overlay-frame table at +0xA39C, not part of this array
            // 16 raid troop tables (rows 0-7 European outpost, 8-15 Arabian; row = Building.field270_0x30c) x 13
            // ints: [0] troop spawn period (minus incByFourUnk), [1] minimum period, [2] raid size base, [3] raid
            // size random range, [4..11] candidate unit types (0 = unused), [12] tribeSubtype1 of the raid tribe
            // (182/184/185). The UpdateCampGround access [0xc][i+6] is a decompiler alias of a separate
            // vclock->overlay-frame table at +0xA39C, not part of this array
            int outpostRaidTroopTables[16][13]; // 0x0000A04C length: 832
            // Base animation frame of the drawbridge per relative rotation/2 (initial 1,9,17,25); lowered = base,
            // raised = base+7, raise/lower table frames are added to it
            int drawbridgeBaseFrameByRotation[4]; // 0x0000A38C length: 16
            int field415_0xa39c[52]; // 0x0000A39C length: 208
            int field416_0xa46c[52]; // 0x0000A46C length: 208
            // Killing pit animation frame sequence for state -2 (re-arming), terminated by -1
            int killingPitResetAnimFrames[26]; // 0x0000A53C length: 104
            // Killing pit animation frame sequence for state 1 (triggered), -1 terminates and sets state 2
            int killingPitTriggerAnimFrames[102]; // 0x0000A5A4 length: 408
            // Tower2 (size 4): 4 footprint-tile indices per map orientation/2 that get MiscDisplayLayer bit 0x10
            // (units standing there are hidden/vanish, see updateUnitFadeAndVisibilityNearStructures); all its
            // tiles are cleared first
            int tower2VanishTilesByOrientation[16]; // 0x0000A73C length: 64
            // Tower3 (size 5): 6 footprint-tile indices per map orientation/2 that get MiscDisplayLayer bit 0x10
            // (unit vanish flag)
            int tower3VanishTilesByOrientation[24]; // 0x0000A77C length: 96
            // Tower4/Tower5 (size 6): 8 footprint-tile indices per map orientation/2 that get MiscDisplayLayer bit
            // 0x10 (unit vanish flag)
            int tower45VanishTilesByOrientation[32]; // 0x0000A7DC length: 128
            int BuildingCost[110][5]; // 0x0000A85C length: 2200

        } BuildingDefinedData;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(BuildingDefinedData) == 45300, BuildingDefinedData);
    } // namespace Buildings
} // namespace Map
} // namespace OpenSHC
