/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Random/RNG.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Random {

#pragma pack(push, 1)

    // SIZE: 0x00009C50
    class RNG {
    public:
        // Unsigned Word (dw, 2-bytes)
        short currentNumber1; // 0x00000000 length: 2
        // Unsigned Word (dw, 2-bytes)
        short currentNumber2; // 0x00000002 length: 2
        int seed; // 0x00000004 length: 4
        short randomNumbers[20000]; // 0x00000008 length: 40000
        // Unsigned Double-Word (ddw, 4-bytes)
        int index2; // 0x00009C48 length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        int index1; // 0x00009C4C length: 4

    private:
        RNG(RNG const&);
        void operator=(RNG const&);

    public:
        RNG() {};
        ~RNG() {};

        // Constructor
        /**
         * Constructor of the global RNG: sets a time-based seed and fills the random number table via
         * populateRNG1040. Returns &SEC_RNG.
         */
        RNG* Constructor_RNG();

        /**
         * __thiscall: this->seed (+4) = (int)_time64(NULL). The decompiler shows SEC_RNG.seed because the RNG
         * object is SEC_RNG (Constructor_RNG forwards its own ECX); the machine code writes through ECX, not to the
         * global.
         */
        void setTimeBasedSeed();

        /**
         * Seeds the CRT rand() with SEC_RNG.seed, fills the 20000-entry SEC_RNG.randomNumbers table with rand()
         * values, resets both read indices and pre-loads currentNumber2 and currentNumber1 from the first table
         * entry (both indices end at 1).
         */
        void populateRNG1040();

        /**
         * Advances RNG stream 2: loads SEC_RNG.randomNumbers[index2] into currentNumber2, increments index2 and
         * wraps it to 0 once it exceeds 19999.
         */
        void nextRandomNumber2();

        /**
         * Advances RNG stream 1: loads SEC_RNG.randomNumbers[index1] into currentNumber1, increments index1 and
         * wraps it to 0 once it exceeds 19999.
         */
        void nextRandomNumber1();
    };

    static_assert_cpp98_obj(sizeof(RNG) == 40016, RNG);

#pragma pack(pop)

} // namespace Random
} // namespace OpenSHC
