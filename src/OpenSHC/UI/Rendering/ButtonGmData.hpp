/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/Rendering/ButtonGmData.hpp'
*/

#pragma once

#include "OpenSHC/IO/Graphics/GmIDInt.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::IO::Graphics::GmIDInt;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

        // SIZE: 0x0000001C
        class ButtonGmData {
        public:
            GmIDInt gmId_0x0; // 0x00000000 length: 4
            int pictureInGm_0x4; // 0x00000004 length: 4
            int numOfAdditionalIconStates_0x8; // 0x00000008 length: 4
            // [249 0x004630D0] GM id rendered for hit testing when the picture number is negative; alpha channel
            // threshold applied Currently it seems even unused. At least not a sinlge one I tested pointed to an
            // non Null-Gm. Maybe it is used a a marker for transparency, or to have a separate hitbox.
            GmIDInt alphaGmId; // 0x0000000C length: 4
            int field4_0x10; // 0x00000010 length: 4
            int field5_0x14; // 0x00000014 length: 4
            // [UNK PASS] was stateTransitionTimeBaseUnk_0x18
            int animationStartTime_0x18; // 0x00000018 length: 4

        private:
            ButtonGmData(ButtonGmData const&);
            void operator=(ButtonGmData const&);

        public:
            ButtonGmData() {};
            ~ButtonGmData() {};

            /**
             * __thiscall on a ButtonGmData (ECX): returns pictureInGm (+4), or pictureInGm +
             * numOfAdditionalIconStates (+8) when the BOOL argument is non-zero, i.e. the picture of the button's
             * alternate state.
             */
            int getPictureNumberInGm(BOOLEnum useAlternatePicture);
        };

        static_assert_cpp98_obj(sizeof(ButtonGmData) == 28, ButtonGmData);

#pragma pack(pop)

    } // namespace Rendering
} // namespace UI
} // namespace OpenSHC
