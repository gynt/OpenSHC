/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/TerrainDefinedData.hpp'
*/

#pragma once

#include "OpenSHC/Map/Buildings/WheatFarm/WheatFarmFieldSpec.hpp"
#include "OpenSHC/Map/GFX/UnkBytePair.hpp"
#include "OpenSHC/Map/Location/Point8.hpp"
#include "OpenSHC/Map/Location/Point8IntXY.hpp"
#include "OpenSHC/Map/Navigation/Algorithms/XYPair.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Buildings::WheatFarm::WheatFarmFieldSpec;
    using OpenSHC::Map::GFX::UnkBytePair;
    using OpenSHC::Map::Location::Point8;
    using OpenSHC::Map::Location::Point8IntXY;
    using OpenSHC::Map::Navigation::Algorithms::XYPair;

#pragma pack(push, 1)
    // SIZE: 0x000037AC
    typedef struct TerrainDefinedData {

        undefined1 padding_0x0[12]; // 0x00000000 length: 12
        // Per round-brush tile index 0..36 a step code walked by getTileForBrush: 0..7 one step, 20..27 two steps,
        // 40..47 three steps in direction (code mod 20); 15 and codes > 47 = no move
        int brushSpiralStepCodes[37]; // 0x0000000C length: 148
        int BrushSizeArray[8]; // 0x000000A0 length: 32
        XYPair field14_0xc0; // 0x000000C0 length: 8
        undefined1 padding_0xc8[8]; // 0x000000C8 length: 8
        undefined4 field23_0xd0; // 0x000000D0 length: 4
        undefined1 padding_0xd4[32]; // 0x000000D4 length: 32
        // [033 0x004EEE10] 8 entries (index 7 used, stride-8 walk visits 8 directions); other searches step by 2
        // entries to visit only 4, so it is not only cardinal directions
        Point8 clockwiseNeighbourOffsets[8]; // 0x000000F4 length: 64
        undefined1 padding_0x134[4]; // 0x00000134 length: 4
        int field61_0x138; // 0x00000138 length: 4
        XYPair BuildingPartsOffsets[4][3]; // 0x0000013C length: 96
        // Offset (x,y) of the oil smelter's 4x4 secondary part per rotation index (orientation/2):
        // (0,4),(4,0),(0,-4),(-4,0); used by placeOilsmelter, placement check and AIV placement
        XYPair oilSmelterPartOffsetByRot[4]; // 0x0000019C length: 32
        XYPair Stockpile_BuildingPartsOffsets[4]; // 0x000001BC length: 32
        XYPair StockpilePathableOffsets[9]; // 0x000001DC length: 72
        undefined1 padding_0x224[64]; // 0x00000224 length: 64
        // Per keep size class (3) x 4 orientations x 3 doors (left 0x47, centre 0x49, right 0x48) the door tile
        // offset from the keep origin (24 bytes per keep/orientation); used by placeKeep and the keep construction
        // preview
        XYPair keepDoorOffsets[3][12]; // 0x00000264 length: 288
        // Keep offset table per keep size class (3) x orientation (4), like keepDoorOffsets XYPair[3][12] (+0x264):
        // checkBuildingCanBePlacedHere, demolishBuildingsInKeepsConstructionFootprint and
        // setConstructionGFXLayerBasedOnPlacementChecks index it with class<<5 (row = 4 entries); placeKeep with
        // eax*8. Data: (0,8),(8,0),(0,-8),(-8,0) x2, (2,12),(12,2),(2,-12),(-12,2). The second table starts at
        // +0x3E4, not +0x3C4.
        Point8IntXY unkXYOffsets_0x384[3][4]; // 0x00000384 length: 96
        // Stockpile offset per keep size class x orientation: same class<<5 / eax*8 indexing at 0xB49338 (+0x3E4)
        // right after the +0x384 reads; data (7,2),(2,-5),(-5,0),(0,7) x2, (11,6),(6,-5),(-5,0),(0,11); the table
        // ends exactly at campgroundSpotOffsets (+0x444).
        Point8IntXY keepStockpileOffsets[3][4]; // 0x000003E4 length: 96
        // 24 (x,y) offsets inside the 7x7 campground (relative to the campground origin) whose tiles placeKeep
        // stores in the campground's tile-ref slots; probably the peasants' standing/seating spots
        XYPair campgroundSpotOffsets[24]; // 0x00000444 length: 192
        undefined1 padding_0x504[8]; // 0x00000504 length: 8
        XYPair field206_0x50c; // 0x0000050C length: 8
        // accessed by 0x5060a7
        undefined1 field_0x514[4]; // 0x00000514 length: 4
        XYPair field211_0x518; // 0x00000518 length: 8
        // accessed by 0x5061d5
        int field_0x520; // 0x00000520 length: 4
        undefined1 padding_0x524[72]; // 0x00000524 length: 72
        XYPair field288_0x56c; // 0x0000056C length: 8
        undefined1 padding_0x574[4]; // 0x00000574 length: 4
        XYPair field293_0x578; // 0x00000578 length: 8
        undefined1 padding_0x580[76]; // 0x00000580 length: 76
        XYPair field370_0x5cc; // 0x000005CC length: 8
        undefined1 padding_0x5d4[184]; // 0x000005D4 length: 184
        // Base of 8 groups x 5 (x,y) offsets (group*40 bytes; group 0..7 comes from the {x,y,group} part table) =
        // 40 XYPairs ending exactly at +0x7CC. The +0x7C8 placeholder is the y of group 7 entry 4, not a separate
        // field (the real int table starts at +0x7CC).
        XYPair woodGatePartTileOffsets[40]; // 0x0000068C length: 320
        // Real base of the per-group direction table: code reads [(k + group*4)*4 + 0xB4971C] only for k=1..4 (k=0
        // takes another branch), i.e. int[8][4] at +0x7CC (values 0/2/4/6), ending at stockpileResourceGfxBase
        // (+0x84C). Ghidra folded k-1 into the base (+0x7C8).
        int woodGatePartTileDirs[32]; // 0x000007CC length: 128
        // Per resource type base graphic offset for stockpile piles
        int stockpileResourceGfxBase[25]; // 0x0000084C length: 100
        undefined1 padding_0x8b0[4]; // 0x000008B0 length: 4
        // Per resource type stockpile pile drawing style used by updateBuildingGraphicsLayer: 0 = frame by amount,
        // 2 = 4-tile interleaved layout, other = frame by remaining space
        int stockpilePileStyle[25]; // 0x000008B4 length: 100
        undefined1 padding_0x918[4]; // 0x00000918 length: 4
        XYPair WheatFarmTiles[4][36]; // 0x0000091C length: 1152
        // [107 0x005151C0] per-variation table of 24 XYPair field-tile offsets relative to the farm origin
        XYPair hopFarmFieldTiles[2][24]; // 0x00000D9C length: 384
        XYPair AppleFarmOffsets[8]; // 0x00000F1C length: 64
        // Per dairy farm variation (4) x 27 tile specs (offset + property) for cattle farm field
        WheatFarmFieldSpec dairyFarmTileSpecs[4][27]; // 0x00000F5C length: 1296
        undefined1 padding_0x146c[1280]; // 0x0000146C length: 1280
        // Tile offsets of a 2x2 macro tile block (MacroLayer value 4)
        XYPair macroBlock2x2Offsets[4]; // 0x0000196C length: 32
        // Tile offsets of a 3x3 macro tile block (MacroLayer value 8)
        XYPair macroBlock3x3Offsets[9]; // 0x0000198C length: 72
        // Tile offsets of a 4x4 macro tile block (MacroLayer value 0x10)
        XYPair macroBlock4x4Offsets[16]; // 0x000019D4 length: 128
        int field2293_0x1a54[4][16]; // 0x00001A54 length: 256
        int field2294_0x1b54[4][16]; // 0x00001B54 length: 256
        int field2295_0x1c54[4][16]; // 0x00001C54 length: 256
        // updateGFXLayers walks one 8-entry {mask,gfxOffset} byte-pair table: loop i=0..3 then i=4..7 over
        // [i*2+0xB4ACA8]/[i*2+0xB4ACA9]; field2297_0x1d5c is entries 4..7. UnkBytePair (2 bytes) already used for
        // the sibling table at +0x1D64.
        UnkBytePair edgeMaskGfxOffsetsA[8]; // 0x00001D54 length: 16
        // Pairs {neighbour bitmask, gfx offset} (7 used) for terrain border graphics in updateGfxLayer
        UnkBytePair edgeMaskGfxOffsetsB[8]; // 0x00001D64 length: 16
        int MapSizes[5]; // 0x00001D74 length: 20
        undefined1 padding_0x1d88[164]; // 0x00001D88 length: 164
        int SomeOrientationOrderArray[8]; // 0x00001E2C length: 32
        // 4 sides x 4 (x,y) tile offsets probed for wall tiles to auto-rotate a placed building
        int rotationProbeOffsets[32]; // 0x00001E4C length: 128
        XYPair drawBridgeOffsets[4][9]; // 0x00001ECC length: 288
        // Per drawbridge variation/2 (4) x 25 footprint tiles: 0 = draw the moat/ground texture, otherwise sprite
        // frame offset (1 or 2, + 0x61E on the building's sheet)
        int drawbridgeTileFramesByRot[4][25]; // 0x00001FEC length: 400
        int TowerTileOffsetsBySize[7][4]; // 0x0000217C length: 112
        // Per drawbridge variation/2 (4) x 25 tiles of the 5x5 footprint: 1 = side tile skipped, 0 = tile checked
        // for units by isUnitBlockingSizeFiveFootprint (table at 0xB4B140, bytes verified)
        int drawbridgeUnitCheckMaskByRot[4][25]; // 0x000021EC length: 400
        int DrawbridgeOrientationMapping[4][25]; // 0x0000237C length: 400
        int DrawbridgeTileMoatProperty[26]; // 0x0000250C length: 104
        int orientationRelativeBuildingTileOffset2[60]; // 0x00002574 length: 240
        int orientationRelativeBuildingTileOffset1[64]; // 0x00002664 length: 256
        // -1-terminated (x,y) offset lists (60 pairs per size class = type/2) of tiles around a footprint where
        // floating markers are spawned
        XYPair markerRingOffsetsBySize[501]; // 0x00002764 length: 4008
        // Direction index (into directionTranslationMatrix) for each of the 8 neighbour bits tested in
        // updateGfxLayer
        int neighbourBitDirections[8]; // 0x0000370C length: 32
        // 8 neighbour (x,y) offsets examined by computeTileCliffEdgeFlags / propagateCliffEdgeFlagFromNeighbor
        XYPair cliffNeighbourOffsets[8]; // 0x0000372C length: 64
        // 4 neighbour (x,y) offsets to which burning pitch ditches spread fire
        XYPair pitchSpreadOffsets[4]; // 0x0000376C length: 32
        // 4 (x,y) offsets two tiles away from a target: (0,2),(0,-2),(2,0),(-2,0) (bytes at 0xB4C6E0);
        // findNearestValidDigTileNearTarget picks the reachable one at similar height closest to the attacker
        XYPair approachOffsetsDist2[4]; // 0x0000378C length: 32

    } TerrainDefinedData;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(TerrainDefinedData) == 14252, TerrainDefinedData);
} // namespace Map
} // namespace OpenSHC
