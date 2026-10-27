/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Util/Timing/Stopwatch.hpp'
*/

#pragma once

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Util {
    namespace Timing {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

        // SIZE: 0x00000010
        class Stopwatch {
        public:
            // Set after stop.
            dword duration_0x0; // 0x00000000 length: 4
            BOOLEnum running_0x4; // 0x00000004 length: 4
            dword startTime_0x8; // 0x00000008 length: 4
            dword stopTime_0xc; // 0x0000000C length: 4

        private:
            Stopwatch(Stopwatch const&);
            void operator=(Stopwatch const&);

        public:
            Stopwatch() {};
            ~Stopwatch() {};

            // Constructor
            /**
             * Stopwatch constructor: not running, duration 0.
             */
            Stopwatch* Constructor_Stopwatch();

            /**
             * Starts the stopwatch: stores timeGetTime() as start time and sets running.
             */
            void start();

            /**
             * Stops a running stopwatch: stores stop time, clears running and sets duration = stop - start (ms).
             */
            void stop();
        };

        static_assert_cpp98_obj(sizeof(Stopwatch) == 16, Stopwatch);

#pragma pack(pop)

    } // namespace Timing
} // namespace Util
} // namespace OpenSHC
