/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/UserHelpDefinedData.hpp'
*/

#pragma once

#include "OpenSHC/Text/HelpTextRelatedColorStruct.hpp"
#include "OpenSHC/Text/UnkHelpTextRelatedFontStruct.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::Text::HelpTextRelatedColorStruct;
    using OpenSHC::Text::UnkHelpTextRelatedFontStruct;

#pragma pack(push, 1)
    // SIZE: 0x0007A23C
    typedef struct UserHelpDefinedData {

        undefined1 padding_0x0[4]; // 0x00000000 length: 4
        char HelpSections[500][1000]; // 0x00000004 length: 500000
        // Verified in clean.exe: 0xB33290 holds {"Stronghold 14 aa",19}...{NULL,-1} font entries; colour table
        // follows at +0x48 (=helpColorTable). Not sections. Help section descriptors iterated by
        // get{Next,Prev}HelpSectionID / getHelpSectionText
        UnkHelpTextRelatedFontStruct helpFontTable[9]; // 0x0007A124 length: 72
        // Named color entries {name, r, g, b} used by help rich-text color tokens and the text editor (null name
        // terminates)
        HelpTextRelatedColorStruct helpColorTable[13]; // 0x0007A16C length: 208

    } UserHelpDefinedData;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(UserHelpDefinedData) == 500284, UserHelpDefinedData);
} // namespace UI
} // namespace OpenSHC
