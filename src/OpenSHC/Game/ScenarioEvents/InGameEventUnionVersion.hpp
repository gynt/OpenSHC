/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Game/ScenarioEvents/InGameEventUnionVersion.hpp'
*/

#pragma once

#include "OpenSHC/Game/ScenarioEvents/InGameEventUnion.hpp"
#include "OpenSHC/Game/ScenarioEvents/IngameEventHeader.hpp"
#include "OpenSHC/Game/ScenarioEvents/ScenarioEventCondition.hpp"

namespace OpenSHC {
namespace Game {
    namespace ScenarioEvents {

        using OpenSHC::Game::ScenarioEvents::IngameEventHeader;
        using OpenSHC::Game::ScenarioEvents::InGameEventUnion;
        using OpenSHC::Game::ScenarioEvents::ScenarioEventCondition;

#pragma pack(push, 1)

        // SIZE: 0x000000E4
        class InGameEventUnionVersion {
        public:
            IngameEventHeader header; // 0x00000000 length: 16
            InGameEventUnion data; // 0x00000010 length: 212

        private:
            InGameEventUnionVersion(InGameEventUnionVersion const&);
            void operator=(InGameEventUnionVersion const&);

        public:
            InGameEventUnionVersion() {};
            ~InGameEventUnionVersion() {};

            /**
             * Resets an event to defaults: month 0, year 1181, type 1 (invasion) and zeroes all invasion/scenario
             * data. Returns 0.
             */
            undefined4 resetEvent();

            /**
             * Initializes the event as a scenario event: month 0, year 1181, type 3, clears action data and repeat,
             * sets a word at data+8 to 1 and disables all 40 conditions. Returns a pointer past the last condition.
             */
            ScenarioEventCondition* initializeScenarioEvent();
        };

        static_assert_cpp98_obj(sizeof(InGameEventUnionVersion) == 228, InGameEventUnionVersion);

#pragma pack(pop)

    } // namespace ScenarioEvents
} // namespace Game
} // namespace OpenSHC
