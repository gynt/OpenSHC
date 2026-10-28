/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/HistoricMissionSelect.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace HistoricMissionSelect {

            void __cdecl MenuItemRenderFunction_HistoricMissionSelect_MissionRows(int param_1, ...);

            /**
             * Action handler of the historic mission select screen: 0xD starts the selected mission, 0x12 goes back
             * to campaign select, 0x14 cycles difficulty 0..3, any other id selects the mission row and starts it
             * on a double click (same mission within 500 ms).
             */
            void __cdecl MenuItemActionHandler_HistoricMissionSelect_General(int param_1, ...);

        } // namespace HistoricMissionSelect
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
