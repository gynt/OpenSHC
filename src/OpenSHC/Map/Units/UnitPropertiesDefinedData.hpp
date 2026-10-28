/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Units/UnitPropertiesDefinedData.hpp'
*/

#pragma once

#include "OpenSHC/Map/AnimationFrameData.hpp"
#include "OpenSHC/Map/Navigation/Algorithms/XYPair.hpp"
#include "OpenSHC/Util/FunctionTypes/NoArgCallback.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::AnimationFrameData;
        using OpenSHC::Map::Navigation::Algorithms::XYPair;
        using OpenSHC::Util::FunctionTypes::NoArgCallback;

#pragma pack(push, 1)
        // SIZE: 0x0001226C
        typedef struct UnitPropertiesDefinedData {

            byte Frames_Shared_UnitClimbingDown[20]; // 0x00000000 length: 20
            NoArgCallback* UpdateUnitFunctions[80]; // 0x00000014 length: 320
            // determines which spriteset to load
            int SPRITE_ID[80]; // 0x00000154 length: 320
            int GRAPHIC_SIZE[80]; // 0x00000294 length: 320
            int COMPUTER_CONTROLLED[80]; // 0x000003D4 length: 320
            int COMPUTER_MANAGED[80]; // 0x00000514 length: 320
            int UNIT_MOVEMENT_SPEED_ARRAY[80]; // 0x00000654 length: 320
            int ABLE_TO_CLIMB_TOWERS[80]; // 0x00000794 length: 320
            int UNIT_MOVABLE[80]; // 0x000008D4 length: 320
            // troop base hp
            int BASE_HP[80]; // 0x00000A14 length: 320
            // damage dealt by archers (euro, arab, horse)
            int ARROW_DAMAGE[80]; // 0x00000B54 length: 320
            // damage dealt by slingers
            int STONE_DAMAGE[80]; // 0x00000C94 length: 320
            // damage dealt by crossbowmen
            int BOLT_DAMAGE[80]; // 0x00000DD4 length: 320
            // melee damage table [attacker][attacked] (not 100% sure if order is correct)
            int MELEE_DAMAGE[80][80]; // 0x00000F14 length: 25600
            int EuroUnitResourceCosts[7][4]; // 0x00007314 length: 112
            undefined1 padding_0x7384[48]; // 0x00007384 length: 48
            int UNIT_CLIMB[80]; // 0x000073B4 length: 320
            int SomeUnitStatMatrix4[80]; // 0x000074F4 length: 320
            // Per unit type default for Unit.occupiesNeighbourTiles (occupies neighbour tiles), copied by setUnitValues; 1
            // for quarry ox, catapult, trebuchet, mangonel, siege tent, cow, siege tower, battering ram, shield,
            // ballista (bytes verified at 0xB55580)
            // Per unit type default for Unit.field64_0x90 (occupies neighbour tiles), copied by setUnitValues; 1
            // for quarry ox, catapult, trebuchet, mangonel, siege tent, cow, siege tower, battering ram, shield,
            // ballista (bytes verified at 0xB55580)
            int occupiesNeighbourTilesPerType[80]; // 0x00007634 length: 320
            // Per unit type default for Unit.isAnimalOrAmbient, copied by setUnitValues; 1 for quarry ox,
            // deer/lion/rabbit/camel/crow/seagull (44-49), cow, hunter dog and chicken/mother/child/juggler/fire
            // eater/cage dog (62-67) (bytes verified at 0xB556C0)
            // Per unit type default for Unit.isStalked, copied by setUnitValues; 1 for quarry ox,
            // deer/lion/rabbit/camel/crow/seagull (44-49), cow, hunter dog and chicken/mother/child/juggler/fire
            // eater/cage dog (62-67) (bytes verified at 0xB556C0)
            int isStalkedPerType[80]; // 0x00007774 length: 320
            int SomeUnitStatMatrix5[80]; // 0x000078B4 length: 320
            int NotBlessableUnits[80]; // 0x000079F4 length: 320
            int UNIT_CAN_MELEE[80]; // 0x00007B34 length: 320
            int UNIT_ENEMY_NOTICE_RANGE[80]; // 0x00007C74 length: 320
            // [161 0x00531920] row 0 indexed by unit type decides if a cow poison cloud damages the unit
            int diseaseVulnerable[7][80]; // 0x00007DB4 length: 2240
            int UNIT_SPRITE_DIMENSIONS[80][2]; // 0x00008674 length: 640
            int FadeAlpha_Values_1_2[46]; // 0x000088F4 length: 184
            int FadeAlpha_Values_3[54]; // 0x000089AC length: 216
            int FadeAlpha_Values_4[61]; // 0x00008A84 length: 244
            // Holds all units' AnimationFrameData tables, not just climbing frames.
            AnimationFrameData animationFrames; // 0x00008B78 length: 33748
            // Pixel (x,y) offsets of a unit's sub-tile micro position, index subX + subY*8 (pairs); used by
            // updateMicroPosition and for the cursor sub-tile offset (viewportState.mouseMicroOffsetX/Y)
            int microPosScreenOffsets[328][2]; // 0x00010F4C length: 2624
            int UnitOrientationRelatedOffset[8][2]; // 0x0001198C length: 64
            // Per facing direction (only [0..7] used: 4,4,3,3,3,4,4,4): movementRelated step at which
            // processUnitMove sets pendingPositionValid (commit of the next tile); entries 8..21 of the declared
            // int[22] are not reached by this index
            int moveStepCommitThreshold[22]; // 0x000119CC length: 88
            int field80_0x11a24[18]; // 0x00011A24 length: 72
            // Ghost unit: per-tick alpha offsets (100-tick cycle, +0x16, capped at 0x20) for the flicker effect.
            int ghostAlphaFlicker[110]; // 0x00011A6C length: 440
            // Resource types looted when a lord is killed: 25% of the victim's stock of each listed resource goes
            // to the killer.
            int lordKillLootResources[20]; // 0x00011C24 length: 80
            // Tile (x,y) offsets around the mother where a child unit walks to play.
            XYPair childPlayOffsets[8]; // 0x00011C74 length: 64
            // 8 direction indices {0,4,2,6,1,3,7,5} (opposite pairs, straight first) into
            // directionTranslationMatrix used to scan neighbouring tiles (findNearestEnemyAndHeadTowardsIt, map
            // upgrade v120)
            int neighbourDirOrder[8]; // 0x00011CB4 length: 32
            undefined1 padding_0x11cd4[32]; // 0x00011CD4 length: 32
            // Per facing (9) x 24: order of neighbour-tile indices scanned for melee enemies in
            // processMeleeInitiation.
            int meleeScanOrderByFacing[9][24]; // 0x00011CF4 length: 864
            // Per neighbour index (24): pair of intermediate tile indices (-1 = none) whose height must be within
            // 0x20 for a 2-tile melee reach.
            XYPair meleeReachViaTiles[24]; // 0x00012054 length: 192
            int UnitVisionBonus[10]; // 0x00012114 length: 40
            // findFreeTileNearby: 3x3 block of (x,y) offsets on the y-1..y-3 side ((-1..1, -1..-3)) searched for a
            // free tile when the tile at y-2 is reachable across the wall line
            XYPair freeTileOffsetsYMinus[9]; // 0x0001213C length: 72
            // findFreeTileNearby: 3x3 block of (x,y) offsets on the x+1..x+3 side searched when the tile at x+2 is
            // reachable
            XYPair freeTileOffsetsXPlus[9]; // 0x00012184 length: 72
            // findFreeTileNearby: 3x3 block of (x,y) offsets on the y+1..y+3 side searched when the tile at y+2 is
            // reachable
            XYPair freeTileOffsetsYPlus[9]; // 0x000121CC length: 72
            // findFreeTileNearby: 3x3 block of (x,y) offsets on the x-1..x-3 side searched when the tile at x-2 is
            // reachable
            XYPair freeTileOffsetsXMinus[9]; // 0x00012214 length: 72
            // Worker speech selection: last chosen complaint topic index; repeated twice clears that topic's
            // counter.
            int lastSpeechTopic; // 0x0001225C length: 4
            // Worker speech weight bonus for the rations topic; rotates 0/10/25 with the taxes and fear biases when
            // a different unit is inspected.
            int rationsSpeechBias; // 0x00012260 length: 4
            // Worker speech weight bonus for the taxes topic (rotates 0/10/25).
            int taxesSpeechBias; // 0x00012264 length: 4
            // Worker speech weight bonus for the fear-factor/productivity topic (rotates 0/10/25).
            int fearSpeechBias; // 0x00012268 length: 4

        } UnitPropertiesDefinedData;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(UnitPropertiesDefinedData) == 74348, UnitPropertiesDefinedData);
    } // namespace Units
} // namespace Map
} // namespace OpenSHC
