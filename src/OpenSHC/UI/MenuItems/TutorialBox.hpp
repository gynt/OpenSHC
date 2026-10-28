/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/TutorialBox.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace TutorialBox {

            /**
             * Action handler of the tutorial box: button 2 quits to the main menu (closing modals and speech);
             * button 1 advances the tutorial sub-step once its condition is met and no transition runs (step 2
             * skips sub-step 1 if a keep exists), and at the end of a step starts the step transition, lifts
             * tutorial restrictions on the last step, plays the next tutorial speech clip if the step has one, and
             * at step 14 sets taxes 3 / rations 2 / popularity 10000 and tops food up to 75 meat.
             */
            void __cdecl MenuItemActionHandler_TutorialBox_Main(int param_1, ...);

            /**
             * Render callback of the tutorial box buttons (hidden during step transition): button 2 shows
             * TEXT_TUTORIAL_BUTTONS[2], others only when the step condition is met, showing text 1 or 5 (when more
             * sub-steps remain and sound is active).
             */
            void __cdecl MenuItemRenderFunction_TutorialBox_Main(int param_1, ...);

        } // namespace TutorialBox
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
