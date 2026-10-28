/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/BottomLeftTextDisplayState.hpp'
*/

#pragma once

#include "OpenSHC/UI/TextMessageBLLookupStructUnion.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::UI::TextMessageBLLookupStructUnion;

#pragma pack(push, 1)

    // SIZE: 0x00000024
    class BottomLeftTextDisplayState {
    public:
        // Both reviewers: holds a message type (0 none, 1..13 switched on), not a boolean. Unsigned Double-Word
        // (ddw, 4-bytes)
        dword displayedMessageType; // 0x00000000 length: 4
        // Unsigned Double-Word (ddw, 4-bytes) [UNK PASS] was currentlyDisplayedUnkTextGroupIndex_0x4
        dword currentlyDisplayedTextGroupIndex_0x4; // 0x00000004 length: 4
        // Unsigned Double-Word (ddw, 4-bytes) [UNK PASS] was currentlyDisplayedUnkTextNumInGroup_0x8
        dword currentlyDisplayedTextNumInGroup_0x8; // 0x00000008 length: 4
        // [203 0x004F4F60] holds a command building type (kind 2), troop type (6/12), selection slot (10) or mapper
        // tool (11) depending on the message kind
        TextMessageBLLookupStructUnion messageExtraParam; // 0x0000000C length: 4
        // [UNK PASS] was currentlyDisplayedTextImportanceUnk
        int currentlyDisplayedTextImportance; // 0x00000010 length: 4
        // [202 0x004F4EF0] compared with timeGetTime() - textMessageTime; 0/-1 are the short-lived 'refresh every
        // frame' states
        int textMessageDurationMs; // 0x00000014 length: 4
        int textMessageTime; // 0x00000018 length: 4
        int unknownCountdown01; // 0x0000001C length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        dword countdown; // 0x00000020 length: 4

    private:
        BottomLeftTextDisplayState(BottomLeftTextDisplayState const&);
        void operator=(BottomLeftTextDisplayState const&);

    public:
        BottomLeftTextDisplayState() {};
        ~BottomLeftTextDisplayState() {};

        /**
         * Shows a message in the bottom-left text area. messageType 0 clears it. A new message is ignored if a more
         * important one is showing; the countdown is reset unless the same message (group, index, extra object) is
         * already shown. textGroupIndex -1 means: look up group/index in TextMessageLookupTable by the extra
         * object's building type (message type 2 = building text); if nothing matches, the previous group/index
         * stay. Text 0x4D/1 ('not enough workers') plays placement_warning1.wav. Stores the extra object,
         * importance and duration; duration -1 is stored as 0 without a start time, which the tick function turns
         * into an expiry after about two ticks (so the caller must keep re-sending it).
         */
        void setBottomLeftTextDisplayText(int messageTypeUnk, int textGroupIndex, int textNumInGroup,
            int param_4, int importanceUnk, int displayDurationUnk);

        /**
         * Per-tick expiry of the bottom-left message: if none is shown, decrements unknownCountdown01. Otherwise a
         * duration of 0 is changed to -1 (one more tick), a duration of -1 hides the message immediately, and a
         * positive duration hides it once that many ms have passed since textMessageTime; hiding also sets
         * unknownCountdown01=1. Finally subtracts the real time elapsed since the previous call from 'countdown'.
         * NAME? Returns nothing; it is a tick/update, not a predicate.
         */
        void tickTextExpiry();

        /**
         * Draws the current bottom-left/hover info message at DAT_ButtonX/Y, switching on the message kind; except
         * for kinds 6/7/12/13 the position is moved into map space (camera offset) and drawn to RT_MAP_GAME. 1 =
         * plain text (group 0x4D: multiline, drawn upward from the anchor using its measured height); 2 = building
         * cost (wood/stone/iron/pitch/gold, each with the player's stock in parentheses; wood cost hidden while the
         * player qualifies for the free woodcutter hut, all free in the editor, only stone+gold from
         * getBuildingCost against start resources in Siege That); 3 = scrolling crowding ticker with its popularity
         * effect, or a popularity trend line; 4/9 = stone/wood stock; 5 = plain text; 6/12 = troop recruit cost; 7
         * = bubble help (cleared while a modal is open); 8 = repair cost (wood/stone); 10 = selected-unit text; 11
         * = mapper tool gold cost; 13 = multiline text (widened in the non-English lobby). Unless forceShow is set
         * it draws nothing in the building/status menu's barracks and mercenary tabs.
         */
        void renderCurrentlyDisplayedText(int forceShowOrStoneCost);
    };

    static_assert_cpp98_obj(sizeof(BottomLeftTextDisplayState) == 36, BottomLeftTextDisplayState);

#pragma pack(pop)

} // namespace UI
} // namespace OpenSHC
