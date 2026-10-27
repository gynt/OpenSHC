/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Commands/GameCommandParameterReadWrite.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Commands {
    typedef enum GameCommandParameterReadWrite {

        GCPRW_WRITE_VAR_TO_STREAM = 0, // 0x00000000
        GCPRW_READ_STREAM_TO_VAR = 1 // 0x00000001

    } GameCommandParameterReadWrite;

    static_assert_cpp98_obj(sizeof(GameCommandParameterReadWrite) == 4, GameCommandParameterReadWrite);
} // namespace Commands
} // namespace OpenSHC
