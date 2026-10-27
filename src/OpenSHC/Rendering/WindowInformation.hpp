/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Rendering/WindowInformation.hpp'
*/

#pragma once

#include "WinDef.h"
#include "winnt.h"

namespace OpenSHC {
namespace Rendering {

#pragma pack(push, 1)

    // SIZE: 0x00000040
    class WindowInformation {
    public:
        undefined1 padding_0x0[48]; // 0x00000000 length: 48
        // [183 0x00467F60] only written by setGameWindowRect with the game window rectangle
        RECT gameWindowRect; // 0x00000030 length: 16

    private:
        WindowInformation(WindowInformation const&);
        void operator=(WindowInformation const&);

    public:
        WindowInformation() {};
        ~WindowInformation() {};

        /**
         * Stores four LONGs into DAT_WindowInformation.gameWindowRect. Parameter order is (left, right,
         * top, bottom), not RECT order — param_2 goes to .right and param_3 to .top (matches the byte-exact OpenSHC
         * source).
         */
        void setGameWindowRect(LONG left, LONG right, LONG top, LONG bottom);
    };

    static_assert_cpp98_obj(sizeof(WindowInformation) == 64, WindowInformation);

#pragma pack(pop)

} // namespace Rendering
} // namespace OpenSHC
