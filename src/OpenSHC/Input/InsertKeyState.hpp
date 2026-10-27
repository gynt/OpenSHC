/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Input/InsertKeyState.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Input {

#pragma pack(push, 1)

    // SIZE: 0x00000008
    class InsertKeyState {
    public:
        int insert; // 0x00000000 length: 4
        // zeroed in the InsertKeyState constructor; no other use seen
        int ctorZeroed04; // 0x00000004 length: 4

    private:
        InsertKeyState(InsertKeyState const&);
        void operator=(InsertKeyState const&);

    public:
        InsertKeyState() {};
        ~InsertKeyState() {};

        // Constructor
        /**
         * InsertKeyState constructor: clears field1_0x4 and sets insert = 1.
         */
        InsertKeyState* Constructor_InsertKeyState();
    };

    static_assert_cpp98_obj(sizeof(InsertKeyState) == 8, InsertKeyState);

#pragma pack(pop)

} // namespace Input
} // namespace OpenSHC
