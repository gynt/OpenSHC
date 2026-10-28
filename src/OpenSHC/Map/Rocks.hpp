/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Rocks.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Rocks {

        /**
         * NAME? Rock update handler (no direct callers, presumably called through a table): only sets the graphic
         * of rock DAT_CurrentRockID to 0x211. Better name: setCurrentRockGfx0x211.
         */
        void __cdecl UpdateRockFunc1();

        /**
         * NAME? Rock update handler (called through a table): only sets rocks[DAT_CurrentRockID].gfx = 0x215.
         * Better name: setCurrentRockGfx0x215.
         */
        void __cdecl UpdateRockFunc2();

        /**
         * NAME? Rock update handler (called through a table): only sets rocks[DAT_CurrentRockID].gfx = 0x219.
         * Better name: setCurrentRockGfx0x219.
         */
        void __cdecl UpdateRockFunc3();

        /**
         * NAME? Rock update handler (called through a table): only sets rocks[DAT_CurrentRockID].gfx = 0x21D.
         * Better name: setCurrentRockGfx0x21D.
         */
        void __cdecl UpdateRockFunc4();

        /**
         * NAME? Rock update handler (called through a table): only sets rocks[DAT_CurrentRockID].gfx = 0x1D1.
         * Better name: setCurrentRockGfx0x1D1.
         */
        void __cdecl UpdateRockFunc5();

        /**
         * Rock update handler (called through a table): sets rocks[DAT_CurrentRockID].gfx = 0x1E1.
         */
        void __cdecl setCurrentRockGfx0x1E1();

        /**
         * Rock update handler (called through a table): sets rocks[DAT_CurrentRockID].gfx = 0x1F1.
         */
        void __cdecl setCurrentRockGfx0x1F1();

        /**
         * NAME? Rock update handler (called through a table): only sets rocks[DAT_CurrentRockID].gfx = 0x201.
         * Better name: setCurrentRockGfx0x201.
         */
        void __cdecl UpdateRockFunc8();

        /**
         * NAME? Rock update handler (called through a table): only sets rocks[DAT_CurrentRockID].gfx = 0x141.
         * Better name: setCurrentRockGfx0x141.
         */
        void __cdecl UpdateRockFunc9();

        /**
         * NAME? Rock update handler (called through a table): only sets rocks[DAT_CurrentRockID].gfx = 0x165.
         * Better name: setCurrentRockGfx0x165.
         */
        void __cdecl UpdateRockFunc10();

        /**
         * NAME? Rock update handler (called through a table): only sets rocks[DAT_CurrentRockID].gfx = 0x189.
         * Better name: setCurrentRockGfx0x189.
         */
        void __cdecl UpdateRockFunc11();

        /**
         * NAME? Rock update handler (called through a table): only sets rocks[DAT_CurrentRockID].gfx = 0x1AD.
         * Better name: setCurrentRockGfx0x1AD.
         */
        void __cdecl UpdateRockFunc12();

        /**
         * NAME? Rock update handler (called through a table): only sets rocks[DAT_CurrentRockID].gfx = 0x41. Better
         * name: setCurrentRockGfx0x41.
         */
        void __cdecl UpdateRockFunc13();

        /**
         * NAME? Rock update handler (called through a table): only sets rocks[DAT_CurrentRockID].gfx = 0x81. Better
         * name: setCurrentRockGfx0x81.
         */
        void __cdecl UpdateRockFunc14();

        /**
         * NAME? Rock update handler (called through a table): only sets rocks[DAT_CurrentRockID].gfx = 0xC1. Better
         * name: setCurrentRockGfx0xC1.
         */
        void __cdecl UpdateRockFunc15();

        /**
         * NAME? Rock update handler (called through a table): only sets rocks[DAT_CurrentRockID].gfx = 0x101.
         * Better name: setCurrentRockGfx0x101.
         */
        void __cdecl UpdateRockFunc16();

    } // namespace Rocks
} // namespace Map
} // namespace OpenSHC
