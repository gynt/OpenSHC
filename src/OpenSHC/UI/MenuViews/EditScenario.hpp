/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuViews/EditScenario.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace EditScenario {

            /**
             * Per-frame handler of the edit scenario view: draws the centred background and, if no modal dialog is
             * open, the 'Scenario Editor' banner plus a dimmed panel framed by soft-yellow lines.
             */
            void __cdecl MenuView_EditScenario_DoEveryFrame();

            /**
             * Prepare handler of the edit scenario view: loads frontend_builder2.tgx, updates event years /
             * building availability from map properties and snapshots the scenario gold into
             * DAT_CopyOfScenarioGold.
             */
            void __cdecl MenuView_EditScenario_Prepare();

        } // namespace EditScenario
    } // namespace MenuViews
} // namespace UI
} // namespace OpenSHC
