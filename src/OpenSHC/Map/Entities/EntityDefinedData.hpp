/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Entities/EntityDefinedData.hpp'
*/

#pragma once

#include "OpenSHC/IO/Graphics/GmIDInt.hpp"
#include "OpenSHC/Map/Location/Point4ShortXY.hpp"
#include "OpenSHC/Map/Location/Point8IntXY.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        using OpenSHC::IO::Graphics::GmIDInt;
        using OpenSHC::Map::Location::Point4ShortXY;
        using OpenSHC::Map::Location::Point8IntXY;

#pragma pack(push, 1)
        // SIZE: 0x00001964
        typedef struct EntityDefinedData {

            int field0_0x0[9]; // 0x00000000 length: 36
            pointer EntityCallbacks[44]; // 0x00000024 length: 176
            GmIDInt EntityPropertyArray_1[45]; // 0x000000D4 length: 180
            // Fire frame sequence (signed bytes 33..48, <=0 ends the cycle) used in every phase when fire level
            // fireParameter_0xb6 == 2
            byte fireLevel2Frames[36]; // 0x00000188 length: 36
            int EntityPropertyArray_2[45]; // 0x000001AC length: 180
            // Fire frame sequence (signed bytes 49..64) used in every phase when fire level < 2
            byte fireLevel1Frames[16]; // 0x00000260 length: 16
            undefined1 padding_0x270[20]; // 0x00000270 length: 20
            // Real base of the per-entity-type table: setProjectileEntityValues2 does add ecx,-0xA then movzx word
            // [ecx*4+0x5B62B0] = +0x284 + type*4; 45 entries end at fireLargeStartFramesA (+0x338). +0x270..+0x283
            // are unreferenced zeros.
            int projectileParamPerType[45]; // 0x00000284 length: 180
            // Fire level >= 3, phase 0 (start) frames, variant with rng_1 bit 0x80 set (gmID 0x76)
            byte fireLargeStartFramesA[28]; // 0x00000338 length: 28
            uint EntityTypeArrayForProjectileRange[38]; // 0x00000354 length: 152
            undefined1 padding_0x3ec[28]; // 0x000003EC length: 28
            // Large fire end-stage (stage 2) frames, variant A
            byte fireLargeEndFramesA[28]; // 0x00000408 length: 28
            int EntityArrayCurveTypeForProjectileType[45]; // 0x00000424 length: 180
            // Large fire start-stage frames, variant B (gmID 0x90)
            byte fireLargeStartFramesB[28]; // 0x000004D8 length: 28
            int EntityArrayProjectileVelocityForProjectileType[45]; // 0x000004F4 length: 180
            // Large fire end-stage frames, variant B (gmID 0x90)
            byte fireLargeEndFramesB[28]; // 0x000005A8 length: 28
            // Per entity type initial value of Entity._elapsedTimeOrGravityAccumulator
            float initialGravityAccumPerType[46]; // 0x000005C4 length: 184
            // Per-entity-type table of 46 entries: setProjectileEntityValues2 reads movzx word [type*4+0x5B6680]
            // (+0x67C); the next per-type table starts 46*4 bytes later at +0x734 (see next op). Data: 38 non-
            // zero/filled entries + 8 zero tail entries, same shape as initialGravityAccumPerType float[46] at
            // +0x5C4.
            int EntityPropertyArray_3[46]; // 0x0000067C length: 184
            // Second per-entity-type table: setProjectileEntityValues2 does add ecx,-0xA then movzx word
            // [ecx*4+0x5B6760] = +0x734 + type*4 and stores it to Entity+0xBA (losClearanceStepsLeft). Ghidra
            // showed it as field45_0x75c (base of type 10). Values 0/3 are non-zero exactly for the
            // projectile/effect types that also have frame counts at +0x7EC (types 1-4,7,8,23-25,33,34,36,37) plus
            // type 20.
            int losClearanceStepsPerType[46]; // 0x00000734 length: 184
            // Per-gmLookup frame-count table, 46 entries like gmIDPerGmLookup[46] (+0x95C): setEntityParameters
            // reads it with the same index register as gmIDPerGmLookup (+0x95C), the +0xA14 table and
            // frameTicksPerGmLookup (+0x8A4); the four tables are exactly 0xB8 = 46*4 apart. drawEntityEffect reads
            // entry 3 directly (0x5B67FC).
            int frameCountPerGmLookup[46]; // 0x000007EC length: 184
            // Per-gmLookup frame-duration table, 46 entries: setEntityParameters reads [g*4+0x5B68A8] with the
            // gmLookup index (same as +0x7EC/+0x95C); drawEntityEffect reads entry 3 directly (0x5B68B4).
            int frameTicksPerGmLookup[46]; // 0x000008A4 length: 184
            // GM sprite sheet ID per gmLookupValue (-> Entity.gmID)
            GmIDInt gmIDPerGmLookup[46]; // 0x0000095C length: 184
            // Per gmLookupValue frame offset (-> Entity.graphicType2RelatedOffset)
            int graphicOffsetPerGmLookup[92]; // 0x00000A14 length: 368
            // 8x8 table of (x,y) int pairs (read as low shorts) of screen draw offsets x1/y1 per sub-tile position
            // (microX&7, microY&7); mapOrientation only changes the index order/mirroring
            Point4ShortXY microPosDrawOffsets[128]; // 0x00000B84 length: 512
            // The 16 (x,y) tile offsets at distance 2 (5x5 ring); a cow poison cloud damages units there
            // (tileDistance 2) after its own tile and the 8 neighbours; loop ends at absolute 0x5B6E08
            Point8IntXY poisonCloudRing2Offsets[16]; // 0x00000D84 length: 128
            // Fire level >= 3, phase 1 (burning) frames, variant with rng_1 bit 0x80 set (gmID 0x76)
            byte fireLargeLoopFramesA[48]; // 0x00000E04 length: 48
            // Large fire burning (stage 1) frames, variant B (gmID 0x90)
            byte fireLargeLoopFramesB[56]; // 0x00000E34 length: 56
            int XYOffsetsInAllDirections[64][2]; // 0x00000E6C length: 512
            int field59_0x106c[4]; // 0x0000106C length: 16
            // Popup entities 0x28-0x2b: per animation tick value-1 is stored into the fade level unkMinusOne; an
            // entry < 1 ends the popup (logicalState 3)
            int popupFadeLevels[58]; // 0x0000107C length: 232
            // Flag entities (types 1,2,4): frame offsets for wave state 0 (someTracker 0; from wind / AI mood
            // defensive), <1 ends the cycle
            int flagWaveFramesState0[76]; // 0x00001164 length: 304
            // Flag entities (types 1,2,4): frame offsets for wave state 1 (wind value 1 / AI raiding)
            int flagWaveFramesState1[66]; // 0x00001294 length: 264
            // Flag entities (types 1,2,4): frame offsets for wave states 2 and 3 (strong wind / AI destroy-nervous;
            // state 3 also sets 1 tick per frame)
            int flagWaveFramesState23[144]; // 0x0000139C length: 576
            // Flag type 3: frame offsets for wave state 0 (someTracker 0)
            int flag3WaveFramesState0[114]; // 0x000015DC length: 456
            // Flag type 3: frame offsets for wave states 1-2 (latched wind value)
            int flag3WaveFramesState12[112]; // 0x000017A4 length: 448

        } EntityDefinedData;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(EntityDefinedData) == 6500, EntityDefinedData);
    } // namespace Entities
} // namespace Map
} // namespace OpenSHC
