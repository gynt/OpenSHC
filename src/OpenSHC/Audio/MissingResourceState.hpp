/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Audio/MissingResourceState.hpp'
*/

#pragma once

#include "OpenSHC/Audio/SFX/ResourceLackSFX.hpp"

namespace OpenSHC {
namespace Audio {

    using OpenSHC::Audio::SFX::ResourceLackSFX;

#pragma pack(push, 1)

    // SIZE: 0x00000001
    class MissingResourceState {
    public:
        undefined1 padding_0x0[1]; // 0x00000000 length: 1

    private:
        MissingResourceState(MissingResourceState const&);
        void operator=(MissingResourceState const&);

    public:
        MissingResourceState() {};
        ~MissingResourceState() {};

        /**
         * Shows the 'not enough X' feedback element for 5 s and, if no advisor speech is playing, plays a random
         * 'need iron/pitch/gold/wood/stone' speech variant (0..3, variant 0 weighted 70%; partial stone has a
         * single line).
         */
        void playResourceLackSFX(int resourceTextElement, ResourceLackSFX resourceType);

        /**
         * Draws the resource-missing feedback text (TEXT_FEEDBACK group textGroup) at posX/posY. Normally measures
         * the word-wrapped height (font slot 0x11, max width 0x208) and renders it bottom-aligned (y = posY -
         * height + 0x20), shifted up 20/10 px in building/status menus (barracks/mercenary post vs others); for
         * siege-tent tabs renders a single shadowed left-aligned line at posY+0x94. unusedUnk is ignored. The
         * candidate locals are call-argument temporaries.
         */
        void renderResourceMissingText(int posX, int posY, dword textGroup, dword unusedUnk);
    };

    static_assert_cpp98_obj(sizeof(MissingResourceState) == 1, MissingResourceState);

#pragma pack(pop)

} // namespace Audio
} // namespace OpenSHC
