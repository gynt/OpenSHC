/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/AI/AttackInfo/AttackInfoDefinedData.hpp'
*/

#pragma once

#include "OpenSHC/AI/Tribes/AITribeTypeInt.hpp"
#include "OpenSHC/AI/Tribes/AITribeTypeShort.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"

namespace OpenSHC {
namespace AI {
    namespace AttackInfo {

        using OpenSHC::AI::Tribes::AITribeTypeInt;
        using OpenSHC::AI::Tribes::AITribeTypeShort;
        using OpenSHC::Commands::MappersEnum;

#pragma pack(push, 1)
        // SIZE: 0x00000A34
        typedef struct AttackInfoDefinedData {

            // per attacker type (attackInfo.attacker 0..9; exe init 0,0,100,4,0,0,5,5,5,5):
            // advanceAttackWaveStaging switches STBT_5 tribes to STBT_1 (advance) once attackInfo.casDis
            // (getDistanceToNearestUnknownNonZero01FromSignpost) >= this value
            int castleDistanceThresholdPerAttacker[10]; // 0x00000000 length: 40
            // per attacker type (exe init 0,0,800,300,0,0,200,200,200,200): attackWaveTicker threshold in
            // initializeOrAdvanceAttackWave before the staged wave advances (attacker 8 plays the attack alarm
            // instead); sibling of AttackWaveDurationPerAttacker
            int attackWaveInitTicksPerAttacker[10]; // 0x00000028 length: 40
            int AttackWaveDurationPerAttacker[10]; // 0x00000050 length: 40
            // per attacker type (exe init 0,0,300,400,0,0,400,400,400,400): attackWaveTicker threshold in
            // executeAttackWaveTargetAssignment; when reached the ticker is reset and a new target-assignment round
            // runs (attackInfo.targetRecomputeCount++)
            // per attacker type (exe init 0,0,300,400,0,0,400,400,400,400): attackWaveTicker threshold in
            // executeAttackWaveTargetAssignment; when reached the ticker is reset and a new target-assignment round
            // runs (attackInfo.value10++)
            int targetAssignmentIntervalPerAttacker[10]; // 0x00000078 length: 40
            // per attacker type (exe init 0,0,0,2,0,0,400,400,400,400): copied into attackInfo.catapultLeadRounds
            // when the wave has catapults (+10 if zoneSize < 3000); infantry/town/moat/archer orders only start
            // once value10 (target-assignment rounds) exceeds it by >2, i.e. number of rounds the catapults bombard
            // before the rest attacks
            // per attacker type (exe init 0,0,0,2,0,0,400,400,400,400): copied into attackInfo.field89399_0x21c48
            // when the wave has catapults (+10 if zoneSize < 3000); infantry/town/moat/archer orders only start
            // once value10 (target-assignment rounds) exceeds it by >2, i.e. number of rounds the catapults bombard
            // before the rest attacks
            int catapultHoldbackRoundsPerAttacker[10]; // 0x000000A0 length: 40
            // Per siege-engine slot table with 9 slots: placeSiegeTentsAndAssignEngineers reads slots 0..4 via
            // [k*4+0xB4C7CC] (k<=0x10/4) and slot 8 directly at 0xB4C7EC; slots 5..7 are zero in the exe
            // (190,191,193,192,194,0,0,0,358). Per-player siege counts at 0x1793C7A+p*10 use the same slot numbers.
            MappersEnum siegeEngineMapperTypes[9]; // 0x000000C8 length: 36
            // 16 (dx,dy) short tile offsets cycled (idx+1)&15 to spread units around a point: engineers leaving
            // siege buildings, tribe instructions, siege tower unloading
            short unitScatterOffsetsXY[16][2]; // 0x000000EC length: 64
            undefined1 padding_0x12c[240]; // 0x0000012C length: 240
            // [RUNTIME] AITribeType confirmed: values 0/19 (battering rams)/20 (siege towers)
            AITribeTypeInt field251_0x21c[20]; // 0x0000021C length: 80
            // [RUNTIME] AITribeType confirmed: values 0/19 (battering rams)/20 (siege towers)
            AITribeTypeInt field252_0x26c[20]; // 0x0000026C length: 80
            // [RUNTIME] AITribeType confirmed: values 0/19 (battering rams)/20 (siege towers)
            AITribeTypeInt field253_0x2bc[20]; // 0x000002BC length: 80
            // [RUNTIME] AITribeType confirmed: values 0/19 (battering rams)/20 (siege towers)
            AITribeTypeInt field254_0x30c[20]; // 0x0000030C length: 80
            // [RUNTIME] AITribeType confirmed: values 0/19 (battering rams)/20 (siege towers)
            AITribeTypeInt field255_0x35c[20]; // 0x0000035C length: 80
            // [RUNTIME] AITribeType confirmed: values 0/19 (battering rams)/20 (siege towers)
            AITribeTypeInt field256_0x3ac[20]; // 0x000003AC length: 80
            // [RUNTIME] AITribeType confirmed: values 0/19 (battering rams)/20 (siege towers)
            AITribeTypeInt field257_0x3fc[20]; // 0x000003FC length: 80
            undefined1 padding_0x44c[800]; // 0x0000044C length: 800
            // [RUNTIME] AITribeType confirmed: values 0/19 (battering rams)/20 (siege towers)
            AITribeTypeInt field1058_0x76c[20]; // 0x0000076C length: 80
            // [RUNTIME] AITribeType confirmed: values 0/19 (battering rams)/20 (siege towers)
            AITribeTypeInt field1059_0x7bc[20]; // 0x000007BC length: 80
            // [RUNTIME] AITribeType confirmed: values 0/19 (battering rams)/20 (siege towers)
            AITribeTypeShort field1060_0x80c[40]; // 0x0000080C length: 80
            undefined1 padding_0x85c[400]; // 0x0000085C length: 400
            // Same 9-slot layout: slots 0..4 via [k*4+0xB4D0F0], slot 8 directly at 0xB4D110 (exe values
            // 2,3,4,4,1,0,0,0,2).
            int engineersPerSiegeEngine[9]; // 0x000009EC length: 36
            undefined1 padding_0xa10[36]; // 0x00000A10 length: 36

        } AttackInfoDefinedData;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(AttackInfoDefinedData) == 2612, AttackInfoDefinedData);
    } // namespace AttackInfo
} // namespace AI
} // namespace OpenSHC
