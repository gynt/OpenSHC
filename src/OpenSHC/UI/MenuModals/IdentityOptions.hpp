/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuModals/IdentityOptions.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuModals {
        namespace IdentityOptions {

            /**
             * Renders the 'Set-up Identity' modal: header, two 0xA5-px wrapped labels ('Crusader or Arabic Lord',
             * 'Choose Portrait'), and an animated lord body sprite (GM_BODY_LORD when localSelectedLordType is 0,
             * else GM_BODY_ARABIC_LORD, owner colour 1) cycling 16 frames every 100 ms.
             */
            void __cdecl MenuModalRenderFunction_IdentityOptions(int x, int y, int width, int height);

        } // namespace IdentityOptions
    } // namespace MenuModals
} // namespace UI
} // namespace OpenSHC
