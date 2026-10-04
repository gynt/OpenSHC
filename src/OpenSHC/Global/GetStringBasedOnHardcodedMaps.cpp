#include "../Global.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {

using DE::SHCDE::eTextSections;

// FUNCTION: STRONGHOLDCRUSADER 0x0046D390
char* Global::GetStringBasedOnHardcodedMaps(char* mapName, int* hardcodedMapDescriptionGroupNum)
{
    int _charTest;
    char* pcVar1;
    *hardcodedMapDescriptionGroupNum = 0;
    _charTest = MACRO_CALL(OS_Func::__toupper)((int)*mapName);
    switch (_charTest) {
    case 0x41:
        _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[2]);
        if (_charTest == 0x52) {
            _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "A resourceful divide");
            if (_charTest == 0) {
                *hardcodedMapDescriptionGroupNum = 2;
                DAT_GameCore::instance.mapDescUseStringTable = 1;
                /*
                  added by script: "A Resourceful Divide"
                 */
                pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MAP_NAMES, 1);
                return pcVar1;
            }
        } else {
            _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[4]);
            if (_charTest == 0x57) {
                _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "A New Land");
                if (_charTest == 0) {
                    *hardcodedMapDescriptionGroupNum = 0x70;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    /*
                      added by script: "A new land"
                     */
                    pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MAP_NAMES, 0x6f);
                    return pcVar1;
                }
            } else {
                _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[2]);
                if (_charTest == 0x46) {
                    _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "A Friend Indeed");
                    if (_charTest == 0) {
                        *hardcodedMapDescriptionGroupNum = 0x3e;
                        DAT_GameCore::instance.mapDescUseStringTable = 1;
                        /*
                          added by script: "A Friend Indeed"
                         */
                        pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MAP_NAMES, 0x3d);
                        return pcVar1;
                    }
                } else {
                    _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[2]);
                    if (_charTest == 0x54) {
                        _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Antioch");
                        if (_charTest == 0) {
                            *hardcodedMapDescriptionGroupNum = 0x58;
                            DAT_GameCore::instance.mapDescUseStringTable = 1;
                            /*
                              added by script: "Antioch"
                             */
                            pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                                DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MAP_NAMES, 0x57);
                            return pcVar1;
                        }
                    } else {
                        _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[3]);
                        if (_charTest == 73) {
                            _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "A Mighty Oasis");
                            if (_charTest == 0) {
                                *hardcodedMapDescriptionGroupNum = 0x5e;
                                DAT_GameCore::instance.mapDescUseStringTable = 1;
                                /*
                                  added by script: "A Mighty Oasis"
                                 */
                                pcVar1
                                    = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                                        DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MAP_NAMES, 0x5d);
                                return pcVar1;
                            }
                        } else {
                            _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[3]);
                            if (_charTest == 69) {
                                _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Armenia");
                                if (_charTest == 0) {
                                    *hardcodedMapDescriptionGroupNum = 0x54;
                                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                                    /*
                                      added by script: "Armenia"
                                     */
                                    pcVar1 = MACRO_CALL_MEMBER(
                                        Text::TextManager_Func::getTextStringInGroupAtOffset,
                                        DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MAP_NAMES, 0x53);
                                    return pcVar1;
                                }
                            } else {
                                _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[4]);
                                if ((_charTest == 0x4e)
                                    && (_charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Arnon River"),
                                        _charTest == 0)) {
                                    *hardcodedMapDescriptionGroupNum = 0x7c;
                                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                                    /*
                                      added by script: "Arnon River"
                                     */
                                    pcVar1 = MACRO_CALL_MEMBER(
                                        Text::TextManager_Func::getTextStringInGroupAtOffset,
                                        DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MAP_NAMES, 0x7b);
                                    return pcVar1;
                                }
                            }
                        }
                    }
                }
            }
        }
        break;
    case 0x42:
        _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[2]);
        if (_charTest == 0x52) {
            _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Border Patrol");
            if (_charTest == 0) {
                *hardcodedMapDescriptionGroupNum = 0x50;
                DAT_GameCore::instance.mapDescUseStringTable = 1;
                /*
                  added by script: "Border Patrol"
                 */
                pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MAP_NAMES, 0x4f);
                return pcVar1;
            }
        } else {
            _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[2]);
            if (_charTest == 0x57) {
                _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Bow Ridge");
                if (_charTest == 0) {
                    *hardcodedMapDescriptionGroupNum = 0xc;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    /*
                      added by script: "Bow Ridge"
                     */
                    pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MAP_NAMES, 0xb);
                    return pcVar1;
                }
            } else {
                _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[2]);
                if ((_charTest == 0x4f)
                    && (_charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Broken Dune"), _charTest == 0)) {
                    *hardcodedMapDescriptionGroupNum = 0x7e;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    /*
                      added by script: "Broken Dune"
                     */
                    pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MAP_NAMES, 0x7d);
                    return pcVar1;
                }
            }
        }
        break;
    case 0x43:
        _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[5]);
        if (_charTest == 0x45) {
            _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Centre of the Oasis");
            if (_charTest == 0) {
                *hardcodedMapDescriptionGroupNum = 0xe;
                DAT_GameCore::instance.mapDescUseStringTable = 1;
                /*
                  added by script: "Centre of the Oasis"
                 */
                pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MAP_NAMES, 0xd);
                return pcVar1;
            }
            break;
        }
        _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[5]);
        if (_charTest == 0x20) {
            _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[6]);
            if (_charTest == 0x45) {
                _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Close Encounters");
                if (_charTest == 0) {
                    *hardcodedMapDescriptionGroupNum = 0x20;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    /*
                      added by script: "Close Encounters"
                     */
                    pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MAP_NAMES, 0x1f);
                    return pcVar1;
                }
            } else {
                _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[6]);
                if ((_charTest == 0x50)
                    && (_charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Crete Peninsula"),
                        _charTest == 0)) {
                    *hardcodedMapDescriptionGroupNum = 0x86;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    /*
                      added by script: "Crete Peninsula"
                     */
                    pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MAP_NAMES, 0x85);
                    return pcVar1;
                }
            }
            break;
        }
        _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[5]);
        if (_charTest == 0x53) {
            _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Cactus Valley");
            if (_charTest == 0) {
                *hardcodedMapDescriptionGroupNum = 0x60;
                DAT_GameCore::instance.mapDescUseStringTable = 1;
                /*
                  added by script: "Cactus Valley"
                 */
                pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MAP_NAMES, 0x5f);
                return pcVar1;
            }
            break;
        }
        _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[5]);
        if (_charTest != 0x4e) {
            _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[5]);
            if (_charTest == 0x44) {
                _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[7]);
                if (_charTest == 0x52) {
                    _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Crusader Demo");
                    if (_charTest == 0) {
                        *hardcodedMapDescriptionGroupNum = 0x6e;
                        DAT_GameCore::instance.mapDescUseStringTable = 1;
                        /*
                          added by script: "Crusader Demo"
                         */
                        pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MAP_NAMES, 0x6d);
                        return pcVar1;
                    }
                } else {
                    _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[7]);
                    if ((_charTest == 0x53)
                        && (_charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Cyclades"), _charTest == 0)) {
                        *hardcodedMapDescriptionGroupNum = 0x88;
                        DAT_GameCore::instance.mapDescUseStringTable = 1;
                        /*
                          added by script: "Cyclades"
                         */
                        pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MAP_NAMES, 0x87);
                        return pcVar1;
                    }
                }
            } else {
                _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[5]);
                if (_charTest == 0x52) {
                    _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Caesarea Swampland");
                    if (_charTest == 0) {
                        *hardcodedMapDescriptionGroupNum = 0x80;
                        DAT_GameCore::instance.mapDescUseStringTable = 1;
                        /*
                          added by script: "Caesarea Swampland"
                         */
                        pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MAP_NAMES, 0x7f);
                        return pcVar1;
                    }
                } else {
                    _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[5]);
                    if (_charTest == 0x55) {
                        _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Coconut Twist");
                        if (_charTest == 0) {
                            *hardcodedMapDescriptionGroupNum = 0x82;
                            DAT_GameCore::instance.mapDescUseStringTable = 1;
                            /*
                              added by script: "Coconut Twist"
                             */
                            pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                                DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MAP_NAMES, 0x81);
                            return pcVar1;
                        }
                    } else {
                        _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[5]);
                        if ((_charTest == 0x59)
                            && (_charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Craggy Cliffs"),
                                _charTest == 0)) {
                            *hardcodedMapDescriptionGroupNum = 0x84;
                            DAT_GameCore::instance.mapDescUseStringTable = 1;
                            /*
                              added by script: "Craggy Cliffs"
                             */
                            pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                                DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MAP_NAMES, 0x83);
                            return pcVar1;
                        }
                    }
                }
            }
            break;
        }
        pcVar1 = "Canyons";
        goto LAB_0046d823;
    case 0x44:
        _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[1]);
        if (_charTest == 0x45) {
            _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Desert Island Blues");
            if (_charTest == 0) {
                *hardcodedMapDescriptionGroupNum = 0x12;
                DAT_GameCore::instance.mapDescUseStringTable = 1;
                /*
                  added by script: "Desert Island Blues"
                 */
                pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MAP_NAMES, 0x11);
                return pcVar1;
            }
        } else {
            _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[1]);
            if (_charTest == 0x52) {
                _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Drawn and Quartered");
                if (_charTest == 0) {
                    *hardcodedMapDescriptionGroupNum = 0x8a;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    /*
                      added by script: "Drawn and Quartered"
                     */
                    pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MAP_NAMES, 0x89);
                    return pcVar1;
                }
            } else {
                _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[1]);
                if ((_charTest == 0x55)
                    && (_charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Dunes of Nicaea"),
                        _charTest == 0)) {
                    *hardcodedMapDescriptionGroupNum = 0x8c;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    /*
                      added by script: "Dunes of Nicaea"
                     */
                    pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MAP_NAMES, 0x8b);
                    return pcVar1;
                }
            }
        }
        break;
    case 0x45:
        _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[1]);
        if (_charTest == 0x4d) {
            _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Empty Handed");
            if (_charTest == 0) {
                *hardcodedMapDescriptionGroupNum = 0x40;
                DAT_GameCore::instance.mapDescUseStringTable = 1;
                /*
                  added by script: "Empty Handed"
                 */
                pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MAP_NAMES, 0x3f);
                return pcVar1;
            }
        } else {
            _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[1]);
            if ((_charTest == 0x44)
                && (_charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Edessa"), _charTest == 0)) {
                *hardcodedMapDescriptionGroupNum = 0x56;
                DAT_GameCore::instance.mapDescUseStringTable = 1;
                /*
                  added by script: "Edessa"
                 */
                pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MAP_NAMES, 0x55);
                return pcVar1;
            }
        }
        break;
    case 0x46:
        _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[1]);
        if ((_charTest == 0x4c)
            && (_charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Flood Plains of Jordan"),
                _charTest == 0)) {
            *hardcodedMapDescriptionGroupNum = 0x8e;
            DAT_GameCore::instance.mapDescUseStringTable = 1;
            /*
              added by script: "Flood Plains of Jordan"
             */
            pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MAP_NAMES, 0x8d);
            return pcVar1;
        }
        break;
    case 0x47:
        _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[6]);
        if (_charTest == 0x42) {
            _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Green Belt");
            if (_charTest == 0) {
                *hardcodedMapDescriptionGroupNum = 0x1c;
                DAT_GameCore::instance.mapDescUseStringTable = 1;
                /*
                  added by script: "Green Belt"
                 */
                pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MAP_NAMES, 0x1b);
                return pcVar1;
            }
        } else {
            _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[6]);
            if (_charTest == 0x48) {
                _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Green Haven");
                if (_charTest == 0) {
                    *hardcodedMapDescriptionGroupNum = 0x28;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    /*
                      added by script: "Green Haven"
                     */
                    pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MAP_NAMES, 0x27);
                    return pcVar1;
                }
            } else {
                _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[6]);
                if ((_charTest == 0x45)
                    && (_charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Great Euphrates"),
                        _charTest == 0)) {
                    *hardcodedMapDescriptionGroupNum = 0x90;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    /*
                      added by script: "Great Euphrates"
                     */
                    pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MAP_NAMES, 0x8f);
                    return pcVar1;
                }
            }
        }
        break;
    case 0x48:
        _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[4]);
        if (_charTest == 0x59) {
            _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Happy Land");
            if (_charTest == 0) {
                *hardcodedMapDescriptionGroupNum = 0x1e;
                DAT_GameCore::instance.mapDescUseStringTable = 1;
                /*
                  added by script: "Happy Land"
                 */
                pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MAP_NAMES, 0x1d);
                return pcVar1;
            }
        } else {
            _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[4]);
            if (_charTest == 0x48) {
                _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Height Advantage");
                if (_charTest == 0) {
                    *hardcodedMapDescriptionGroupNum = 10;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    /*
                      added by script: "Height Advantage"
                     */
                    pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MAP_NAMES, 9);
                    return pcVar1;
                }
            } else {
                _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[4]);
                if (_charTest == 0x20) {
                    _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Hell On The Hill");
                    if (_charTest == 0) {
                        *hardcodedMapDescriptionGroupNum = 0x4a;
                        DAT_GameCore::instance.mapDescUseStringTable = 1;
                        /*
                          added by script: "Hell On The Hill"
                         */
                        pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MAP_NAMES, 0x49);
                        return pcVar1;
                    }
                } else {
                    _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[4]);
                    if (_charTest == 0x54) {
                        _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Hilltop Hideout");
                        if (_charTest == 0) {
                            *hardcodedMapDescriptionGroupNum = 0x48;
                            DAT_GameCore::instance.mapDescUseStringTable = 1;
                            /*
                              added by script: "Hilltop Hideout"
                             */
                            pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                                DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MAP_NAMES, 0x47);
                            return pcVar1;
                        }
                    } else {
                        _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[4]);
                        if (_charTest == 0x53) {
                            _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[6]);
                            if (_charTest == 0x52) {
                                _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Halys River");
                                if (_charTest == 0) {
                                    *hardcodedMapDescriptionGroupNum = 0x92;
                                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                                    /*
                                      added by script: "Halys River"
                                     */
                                    pcVar1 = MACRO_CALL_MEMBER(
                                        Text::TextManager_Func::getTextStringInGroupAtOffset,
                                        DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MAP_NAMES, 0x91);
                                    return pcVar1;
                                }
                            } else {
                                _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[6]);
                                if ((_charTest == 0x4f)
                                    && (_charTest
                                        = MACRO_CALL(OS_Func::__stricmp)(mapName, "Hills of Antioch"),
                                        _charTest == 0)) {
                                    *hardcodedMapDescriptionGroupNum = 0x96;
                                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                                    /*
                                      added by script: "Hills of Antioch"
                                     */
                                    pcVar1 = MACRO_CALL_MEMBER(
                                        Text::TextManager_Func::getTextStringInGroupAtOffset,
                                        DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MAP_NAMES, 0x95);
                                    return pcVar1;
                                }
                            }
                        } else {
                            _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[4]);
                            if ((_charTest == 0x45)
                                && (_charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Hidden Crater"),
                                    _charTest == 0)) {
                                *hardcodedMapDescriptionGroupNum = 0x94;
                                DAT_GameCore::instance.mapDescUseStringTable = 1;
                                /*
                                  added by script: "Hidden Crater"
                                 */
                                pcVar1
                                    = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                                        DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MAP_NAMES, 0x93);
                                return pcVar1;
                            }
                        }
                    }
                }
            }
        }
        break;
    case 0x49:
        _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[3]);
        if (_charTest == 0x48) {
            _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Inches Apart");
            if (_charTest == 0) {
                *hardcodedMapDescriptionGroupNum = 0x36;
                DAT_GameCore::instance.mapDescUseStringTable = 1;
                /*
                  added by script: "Inches Apart"
                 */
                pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MAP_NAMES, 0x35);
                return pcVar1;
            }
            break;
        }
        _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[3]);
        if (_charTest == 0x41) {
            _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Island Hoppin");
            if (_charTest == 0) {
                *hardcodedMapDescriptionGroupNum = 0x26;
                DAT_GameCore::instance.mapDescUseStringTable = 1;
                /*
                  added by script: "Island Hopping"
                 */
                pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MAP_NAMES, 0x25);
                return pcVar1;
            }
            break;
        }
        _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[4]);
        if (_charTest == 0x41) {
            _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Its a jungle out there");
            if (_charTest == 0) {
                *hardcodedMapDescriptionGroupNum = 0x46;
                DAT_GameCore::instance.mapDescUseStringTable = 1;
                /*
                  added by script: "Its a Jungle Out There"
                 */
                pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MAP_NAMES, 0x45);
                return pcVar1;
            }
            break;
        }
        _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[7]);
        if (_charTest != 0x43) {
            _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[3]);
            if (_charTest == 0x54) {
                _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "In The Shadow");
                if (_charTest == 0) {
                    *hardcodedMapDescriptionGroupNum = 0x72;
                    _charTest = 0x71;
                    goto LAB_0046d83c;
                }
            } else {
                _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[4]);
                if ((_charTest == 0x4a)
                    && (_charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Its just not fair"),
                        _charTest == 0)) {
                    *hardcodedMapDescriptionGroupNum = 0x7a;
                    _charTest = 0x79;
                    goto LAB_0046d83c;
                }
            }
            break;
        }
        pcVar1 = "In The canyons";
    LAB_0046d823:
        _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, (char const*)((int)(pcVar1)));
        if (_charTest == 0) {
            *hardcodedMapDescriptionGroupNum = 0x62;
            _charTest = 0x61;
        LAB_0046d83c:
            DAT_GameCore::instance.mapDescUseStringTable = 1;
            /*
              added by script: "Canyons"
             */
            pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MAP_NAMES, _charTest);
            return pcVar1;
        }
        break;
    case 0x4c:
        _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[6]);
        if (_charTest == 0x48) {
            _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Love Thy Neighbour");
            if (_charTest == 0) {
                *hardcodedMapDescriptionGroupNum = 0x3a;
                _charTest = 0x39;
                goto LAB_0046d83c;
            }
        } else {
            _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[6]);
            if (_charTest == 0x42) {
                _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Large Barren Desert");
                if (_charTest == 0) {
                    *hardcodedMapDescriptionGroupNum = 100;
                    _charTest = 99;
                    goto LAB_0046d83c;
                }
            } else {
                _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[6]);
                if (_charTest == 0x49) {
                    _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Large Island");
                    if (_charTest == 0) {
                        *hardcodedMapDescriptionGroupNum = 0x66;
                        _charTest = 0x65;
                        goto LAB_0046d83c;
                    }
                } else {
                    _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[6]);
                    if (_charTest == 0x46) {
                        _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Land of the Cactus");
                        if (_charTest == 0) {
                            *hardcodedMapDescriptionGroupNum = 0x78;
                            _charTest = 0x77;
                            goto LAB_0046d83c;
                        }
                    } else {
                        _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[6]);
                        if (_charTest == 0x4d) {
                            _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Lacus Magnus");
                            if (_charTest == 0) {
                                *hardcodedMapDescriptionGroupNum = 0x98;
                                _charTest = 0x97;
                                goto LAB_0046d83c;
                            }
                        } else {
                            _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[6]);
                            if (_charTest == 0x4f) {
                                _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Lakes of Konya");
                                if (_charTest == 0) {
                                    *hardcodedMapDescriptionGroupNum = 0x9a;
                                    _charTest = 0x99;
                                    goto LAB_0046d83c;
                                }
                            } else {
                                _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[6]);
                                if (_charTest == 0x41) {
                                    _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Lake Qaddas");
                                    if (_charTest == 0) {
                                        *hardcodedMapDescriptionGroupNum = 0x9c;
                                        _charTest = 0x9b;
                                        goto LAB_0046d83c;
                                    }
                                } else {
                                    _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[6]);
                                    if ((_charTest == 0x20)
                                        && (_charTest
                                            = MACRO_CALL(OS_Func::__stricmp)(mapName, "Litani and Jordan"),
                                            _charTest == 0)) {
                                        *hardcodedMapDescriptionGroupNum = 0x9e;
                                        _charTest = 0x9d;
                                        goto LAB_0046d83c;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        break;
    case 0x4d:
        _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[2]);
        if (_charTest != 0x52) {
            _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[2]);
            if ((_charTest == 0x4c)
                && (_charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Melos"), _charTest == 0)) {
                *hardcodedMapDescriptionGroupNum = 0xa0;
                _charTest = 0x9f;
                goto LAB_0046d83c;
            }
            break;
        }
        _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Marshy Mayhem");
        if (_charTest != 0)
            break;
        *hardcodedMapDescriptionGroupNum = 0x42;
        _charTest = 0x41;
        goto LAB_0046d83c;
    case 0x4e:
        _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[2]);
        if (_charTest == 0x20) {
            _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "No Escape");
            if (_charTest == 0) {
                *hardcodedMapDescriptionGroupNum = 0x22;
                _charTest = 0x21;
                goto LAB_0046d83c;
            }
        } else {
            _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[2]);
            if ((_charTest == 0x52)
                && (_charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "North vs South"), _charTest == 0)) {
                *hardcodedMapDescriptionGroupNum = 0x2a;
                _charTest = 0x29;
                goto LAB_0046d83c;
            }
        }
        break;
    case 0x4f:
        _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[6]);
        if (_charTest == 0x53) {
            _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Oasis Struggle");
            if (_charTest == 0) {
                *hardcodedMapDescriptionGroupNum = 4;
                _charTest = 3;
                goto LAB_0046d83c;
            }
        } else {
            _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[6]);
            if ((_charTest == 0x42)
                && (_charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Oasis by the Sea"), _charTest == 0)) {
                *hardcodedMapDescriptionGroupNum = 0x6c;
                _charTest = 0x6b;
                goto LAB_0046d83c;
            }
        }
        break;
    case 0x50:
        _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[3]);
        if (_charTest == 0x47) {
            _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Piggy in the middle");
            if (_charTest == 0) {
                *hardcodedMapDescriptionGroupNum = 0x18;
                _charTest = 0x17;
                goto LAB_0046d83c;
            }
        } else {
            _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[3]);
            if (_charTest == 0x20) {
                _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Pig in a Poke");
                if (_charTest == 0) {
                    *hardcodedMapDescriptionGroupNum = 0xa2;
                    _charTest = 0xa1;
                    goto LAB_0046d83c;
                }
            } else {
                _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[3]);
                if ((_charTest == 0x56)
                    && (_charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Province of Bodrum"),
                        _charTest == 0)) {
                    *hardcodedMapDescriptionGroupNum = 0xa4;
                    _charTest = 0xa3;
                    goto LAB_0046d83c;
                }
            }
        }
        break;
    case 0x52:
        _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[6]);
        if (_charTest == 0x49) {
            _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Riverside Rampage");
            if (_charTest == 0) {
                *hardcodedMapDescriptionGroupNum = 0x44;
                _charTest = 0x43;
                goto LAB_0046d83c;
            }
        } else {
            _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[6]);
            if (_charTest == 0x4f) {
                _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Rocky Oasis");
                if (_charTest == 0) {
                    *hardcodedMapDescriptionGroupNum = 0x68;
                    _charTest = 0x67;
                    goto LAB_0046d83c;
                }
            } else {
                _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[6]);
                if (_charTest == 0x45) {
                    _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Reed Sea");
                    if (_charTest == 0) {
                        *hardcodedMapDescriptionGroupNum = 0xa6;
                        _charTest = 0xa5;
                        goto LAB_0046d83c;
                    }
                } else {
                    _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[6]);
                    if (_charTest == 0x20) {
                        _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Region of Corinth");
                        if (_charTest == 0) {
                            *hardcodedMapDescriptionGroupNum = 0xa8;
                            _charTest = 0xa7;
                            goto LAB_0046d83c;
                        }
                    } else {
                        _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[6]);
                        if ((_charTest == 0x41)
                            && (_charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Rock Face"),
                                _charTest == 0)) {
                            *hardcodedMapDescriptionGroupNum = 0xaa;
                            _charTest = 0xa9;
                            goto LAB_0046d83c;
                        }
                    }
                }
            }
        }
        break;
    case 0x53:
        _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[1]);
        if (_charTest == 0x4c) {
            _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Sleeping With The Enemy");
            if (_charTest == 0) {
                *hardcodedMapDescriptionGroupNum = 0x38;
                _charTest = 0x37;
                goto LAB_0046d83c;
            }
        } else {
            _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[1]);
            if (_charTest == 0x54) {
                _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Strati");
                if (_charTest == 0) {
                    *hardcodedMapDescriptionGroupNum = 0xac;
                    _charTest = 0xab;
                    goto LAB_0046d83c;
                }
            } else {
                _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[6]);
                if (_charTest == 0x42) {
                    _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Small Barren Desert");
                    if (_charTest == 0) {
                        *hardcodedMapDescriptionGroupNum = 0x52;
                        _charTest = 0x51;
                        goto LAB_0046d83c;
                    }
                } else {
                    _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[6]);
                    if ((_charTest == 0x49)
                        && (_charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Small Island"),
                            _charTest == 0)) {
                        *hardcodedMapDescriptionGroupNum = 0x6a;
                        _charTest = 0x69;
                        goto LAB_0046d83c;
                    }
                }
            }
        }
        break;
    case 0x54:
        _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[1]);
        if (_charTest == 0x59) {
            _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Tyre");
            if (_charTest == 0) {
                *hardcodedMapDescriptionGroupNum = 0x5c;
                _charTest = 0x5b;
                goto LAB_0046d83c;
            }
        } else {
            _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[4]);
            switch (_charTest) {
            case 0x42:
                _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[5]);
                if ((_charTest == 0x55)
                    && (_charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "The Bulls Eye"),
                        _charTest == 0)) {
                    *hardcodedMapDescriptionGroupNum = 0x16;
                    _charTest = 0x15;
                    goto LAB_0046d83c;
                }
                break;
            case 0x43:
                _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[1]);
                if ((_charTest == 0x4f)
                    && (_charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Too Close For Comfort"),
                        _charTest == 0)) {
                    *hardcodedMapDescriptionGroupNum = 6;
                    _charTest = 5;
                    goto LAB_0046d83c;
                }
                break;
            case 0x44:
                _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[5]);
                if ((_charTest == 0x55)
                    && (_charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "The Dunes"), _charTest == 0)) {
                    *hardcodedMapDescriptionGroupNum = 0x76;
                    _charTest = 0x75;
                    goto LAB_0046d83c;
                }
                break;
            case 0x45:
                _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[1]);
                if (_charTest == 0x41) {
                    _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Target Zone");
                    if (_charTest == 0) {
                        *hardcodedMapDescriptionGroupNum = 0x10;
                        _charTest = 0xf;
                        goto LAB_0046d83c;
                    }
                } else {
                    _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[1]);
                    if ((_charTest == 0x52)
                        && (_charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Trapesac Island"),
                            _charTest == 0)) {
                        *hardcodedMapDescriptionGroupNum = 0xb2;
                        _charTest = 0xb1;
                        goto LAB_0046d83c;
                    }
                }
                break;
            case 0x46:
                _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[7]);
                if (_charTest == 0x44) {
                    _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "The ford across the river");
                    if (_charTest == 0) {
                        *hardcodedMapDescriptionGroupNum = 8;
                        _charTest = 7;
                        goto LAB_0046d83c;
                    }
                } else {
                    _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[7]);
                    if ((_charTest == 0x45)
                        && (_charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "The Forest Oasis"),
                            _charTest == 0)) {
                        *hardcodedMapDescriptionGroupNum = 0x34;
                        _charTest = 0x33;
                        goto LAB_0046d83c;
                    }
                }
                break;
            case 0x47:
                _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[5]);
                if (_charTest == 0x52) {
                    _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "The Great lake");
                    if (_charTest == 0) {
                        *hardcodedMapDescriptionGroupNum = 0x1a;
                        _charTest = 0x19;
                        goto LAB_0046d83c;
                    }
                } else {
                    _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[5]);
                    if ((_charTest == 0x55)
                        && (_charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "The Guardians"),
                            _charTest == 0)) {
                        *hardcodedMapDescriptionGroupNum = 0x30;
                        _charTest = 0x2f;
                        goto LAB_0046d83c;
                    }
                }
                break;
            case 0x49:
                _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[5]);
                if ((_charTest == 0x4e)
                    && (_charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Two in a bed"), _charTest == 0)) {
                    *hardcodedMapDescriptionGroupNum = 0xb4;
                    _charTest = 0xb3;
                    goto LAB_0046d83c;
                }
                break;
            case 0x4b:
                _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[5]);
                if ((_charTest == 0x49)
                    && (_charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "The Killing Plains"),
                        _charTest == 0)) {
                    *hardcodedMapDescriptionGroupNum = 0x24;
                    _charTest = 0x23;
                    goto LAB_0046d83c;
                }
                break;
            case 0x4c:
                _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[5]);
                if ((_charTest == 0x41)
                    && (_charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "The Last Stand"),
                        _charTest == 0)) {
                    *hardcodedMapDescriptionGroupNum = 0x32;
                    _charTest = 0x31;
                    goto LAB_0046d83c;
                }
                break;
            case 0x4f:
                _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[5]);
                if (_charTest == 0x4c) {
                    _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Tripoli");
                    if (_charTest == 0) {
                        *hardcodedMapDescriptionGroupNum = 0x5a;
                        _charTest = 0x59;
                        goto LAB_0046d83c;
                    }
                } else {
                    _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[5]);
                    if ((_charTest == 0x53)
                        && (_charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Thasos"), _charTest == 0)) {
                        *hardcodedMapDescriptionGroupNum = 0xae;
                        _charTest = 0xad;
                        goto LAB_0046d83c;
                    }
                }
                break;
            case 0x52:
                _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[5]);
                if ((_charTest == 0x49)
                    && (_charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "The River"), _charTest == 0)) {
                    *hardcodedMapDescriptionGroupNum = 0x14;
                    _charTest = 0x13;
                    goto LAB_0046d83c;
                }
                break;
            case 0x53:
                _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[3]);
                if ((_charTest == 0x4f)
                    && (_charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Tilos"), _charTest == 0)) {
                    *hardcodedMapDescriptionGroupNum = 0xb0;
                    _charTest = 0xaf;
                    goto LAB_0046d83c;
                }
                break;
            case 0x54:
                _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[5]);
                if ((_charTest == 0x52)
                    && (_charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "The Trench"), _charTest == 0)) {
                    *hardcodedMapDescriptionGroupNum = 0x3c;
                    _charTest = 0x3b;
                    goto LAB_0046d83c;
                }
                break;
            case 0x56:
                _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[5]);
                if ((_charTest == 0x41)
                    && (_charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "The Valley"), _charTest == 0)) {
                    *hardcodedMapDescriptionGroupNum = 0x4e;
                    _charTest = 0x4d;
                    goto LAB_0046d83c;
                }
                break;
            case 0x57:
                _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[5]);
                if ((_charTest == 0x45)
                    && (_charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "The Wet Lands"),
                        _charTest == 0)) {
                    *hardcodedMapDescriptionGroupNum = 0x4c;
                    _charTest = 0x4b;
                    goto LAB_0046d83c;
                }
            }
        }
        break;
    case 0x55:
        _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[1]);
        if ((_charTest == 0x50)
            && (_charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Upwards Alliance"), _charTest == 0)) {
            *hardcodedMapDescriptionGroupNum = 0x2c;
            _charTest = 0x2b;
            goto LAB_0046d83c;
        }
        break;
    case 0x57:
        _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[2]);
        if (_charTest == 0x53) {
            _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "West Coast");
            if (_charTest == 0) {
                *hardcodedMapDescriptionGroupNum = 0x2e;
                _charTest = 0x2d;
                goto LAB_0046d83c;
            }
        } else {
            _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[2]);
            if (_charTest == 0x54) {
                _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Watering Holes");
                if (_charTest == 0) {
                    *hardcodedMapDescriptionGroupNum = 0x74;
                    _charTest = 0x73;
                    goto LAB_0046d83c;
                }
            } else {
                _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[2]);
                if ((_charTest == 0x4c)
                    && (_charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Wall of Iron"), _charTest == 0)) {
                    *hardcodedMapDescriptionGroupNum = 0xb6;
                    _charTest = 0xb5;
                    goto LAB_0046d83c;
                }
            }
        }
    }
    _charTest = MACRO_CALL(OS_Func::__toupper)((int)*mapName);
    switch (_charTest) {
    case 0x42:
        _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[1]);
        if (_charTest == 0x45) {
            _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Best_Friends");
            if (_charTest == 0) {
                *hardcodedMapDescriptionGroupNum = 0x5e;
                /*
                  added by script: "Best Friends"
                 */
                pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_TRAIL_NAMES_CRU, 0x5d);
                return pcVar1;
            }
        } else {
            _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[1]);
            if ((_charTest == 0x49)
                && (_charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Bird_In_Flight"), _charTest == 0)) {
                *hardcodedMapDescriptionGroupNum = 0x53;
                /*
                  added by script: "Bird in Flight"
                 */
                pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_TRAIL_NAMES_CRU, 0x52);
                return pcVar1;
            }
        }
        break;
    case 0x43:
        _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[1]);
        if (_charTest == 0x4f) {
            _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Coastal_Trap");
            if (_charTest == 0) {
                *hardcodedMapDescriptionGroupNum = 0x58;
                /*
                  added by script: "Coastal Trap"
                 */
                pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_TRAIL_NAMES_CRU, 0x57);
                return pcVar1;
            }
        } else {
            _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[1]);
            if ((_charTest == 0x52)
                && (_charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Crossroads"), _charTest == 0)) {
                *hardcodedMapDescriptionGroupNum = 100;
                /*
                  added by script: "Crossroads"
                 */
                pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_TRAIL_NAMES_CRU, 99);
                return pcVar1;
            }
        }
        break;
    case 0x44:
        _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[1]);
        if ((_charTest == 0x49)
            && (_charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Divided"), _charTest == 0)) {
            *hardcodedMapDescriptionGroupNum = 0x60;
            /*
              added by script: "Divided"
             */
            pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_TRAIL_NAMES_CRU, 0x5f);
            return pcVar1;
        }
        break;
    case 0x45:
        _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[1]);
        if ((_charTest == 0x4e)
            && (_charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Enclosure"), _charTest == 0)) {
            *hardcodedMapDescriptionGroupNum = 0x5b;
            /*
              added by script: "Enclosure"
             */
            pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_TRAIL_NAMES_CRU, 0x5a);
            return pcVar1;
        }
        break;
    case 0x46:
        _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[1]);
        if ((_charTest == 0x55)
            && (_charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Fury_Bay"), _charTest == 0)) {
            *hardcodedMapDescriptionGroupNum = 0x54;
            /*
              added by script: "Fury Bay"
             */
            pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_TRAIL_NAMES_CRU, 0x53);
            return pcVar1;
        }
        break;
    case 0x4a:
        _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[1]);
        if ((_charTest == 0x45)
            && (_charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Jealous_Neighbours"), _charTest == 0)) {
            *hardcodedMapDescriptionGroupNum = 0x61;
            /*
              added by script: "Jealous Neighbours"
             */
            pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_TRAIL_NAMES_CRU, 0x60);
            return pcVar1;
        }
        break;
    case 0x4c:
        _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[1]);
        if (_charTest == 0x49) {
            _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Lionheart");
            if (_charTest == 0) {
                *hardcodedMapDescriptionGroupNum = 99;
                /*
                  added by script: "Lionheart"
                 */
                pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_TRAIL_NAMES_CRU, 0x62);
                return pcVar1;
            }
        } else {
            _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[1]);
            if ((_charTest == 0x4f)
                && (_charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Look_Out"), _charTest == 0)) {
                *hardcodedMapDescriptionGroupNum = 0x52;
                /*
                  added by script: "Look Out"
                 */
                pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_TRAIL_NAMES_CRU, 0x51);
                return pcVar1;
            }
        }
        break;
    case 0x4d:
        _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[3]);
        switch (_charTest) {
        case 0x44:
            _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[4]);
            if (_charTest == 0x49) {
                _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "MP-Divided");
                if (_charTest == 0) {
                    *hardcodedMapDescriptionGroupNum = 0x66;
                    /*
                      added by script: "MP-Divided"
                     */
                    pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_TRAIL_NAMES_CRU, 0x65);
                    return pcVar1;
                }
            } else {
                _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[4]);
                if ((_charTest == 0x4f)
                    && (_charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "MP-Downhill Scrum"),
                        _charTest == 0)) {
                    *hardcodedMapDescriptionGroupNum = 0x67;
                    /*
                      added by script: "MP-Downhill Scrum"
                     */
                    pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_TRAIL_NAMES_CRU, 0x66);
                    return pcVar1;
                }
            }
            break;
        case 0x4e:
            _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[6]);
            if (_charTest == 0x4d) {
                _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "MP-No Mans Land");
                if (_charTest == 0) {
                    *hardcodedMapDescriptionGroupNum = 0x68;
                    /*
                      added by script: "MP-No Mans Land"
                     */
                    pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_TRAIL_NAMES_CRU, 0x67);
                    return pcVar1;
                }
            } else {
                _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[6]);
                if ((_charTest == 0x57)
                    && (_charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "MP-No Where to Hide"),
                        _charTest == 0)) {
                    *hardcodedMapDescriptionGroupNum = 0x69;
                    /*
                      added by script: "MP-No Where to Hide"
                     */
                    pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_TRAIL_NAMES_CRU, 0x68);
                    return pcVar1;
                }
            }
            break;
        case 0x53:
            _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[4]);
            if (_charTest == 0x4c) {
                _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "MP-Slopes of Doom");
                if (_charTest == 0) {
                    *hardcodedMapDescriptionGroupNum = 0x6a;
                    /*
                      added by script: "MP-Slopes of Doom"
                     */
                    pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_TRAIL_NAMES_CRU, 0x69);
                    return pcVar1;
                }
            } else {
                _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[4]);
                if (_charTest == 0x4e) {
                    _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "MP-Snake River");
                    if (_charTest == 0) {
                        *hardcodedMapDescriptionGroupNum = 0x6b;
                        /*
                          added by script: "MP-Snake River"
                         */
                        pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_TRAIL_NAMES_CRU, 0x6a);
                        return pcVar1;
                    }
                } else {
                    _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[4]);
                    if ((_charTest == 0x55)
                        && (_charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "MP-Surrounded"),
                            _charTest == 0)) {
                        *hardcodedMapDescriptionGroupNum = 0x6c;
                        /*
                          added by script: "MP-Surrounded"
                         */
                        pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_TRAIL_NAMES_CRU, 0x6b);
                        return pcVar1;
                    }
                }
            }
            break;
        case 0x54:
            _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[4]);
            if (_charTest == 0x48) {
                _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "MP-The Rocky Divide");
                if (_charTest == 0) {
                    *hardcodedMapDescriptionGroupNum = 0x6d;
                    /*
                      added by script: "MP-The Rocky Divide"
                     */
                    pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_TRAIL_NAMES_CRU, 0x6c);
                    return pcVar1;
                }
            } else {
                _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[4]);
                if ((_charTest == 0x57)
                    && (_charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "MP-Two Falls"), _charTest == 0)) {
                    *hardcodedMapDescriptionGroupNum = 0x6e;
                    /*
                      added by script: "MP-Two Falls"
                     */
                    pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_TRAIL_NAMES_CRU, 0x6d);
                    return pcVar1;
                }
            }
            break;
        case 0x56:
            _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[4]);
            if ((_charTest == 0x41)
                && (_charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "MP-Valley of the Lords"),
                    _charTest == 0)) {
                *hardcodedMapDescriptionGroupNum = 0x6f;
                /*
                  added by script: "MP-Valley of the Lords"
                 */
                pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_TRAIL_NAMES_CRU, 0x6e);
                return pcVar1;
            }
        }
        break;
    case 0x50:
        _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[1]);
        if ((_charTest == 0x48)
            && (_charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Phoenix"), _charTest == 0)) {
            *hardcodedMapDescriptionGroupNum = 0x57;
            /*
              added by script: "Phoenix"
             */
            pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_TRAIL_NAMES_CRU, 0x56);
            return pcVar1;
        }
        break;
    case 0x52:
        _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[1]);
        if ((_charTest == 0x49)
            && (_charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Rivers_Fork"), _charTest == 0)) {
            *hardcodedMapDescriptionGroupNum = 0x5a;
            /*
              added by script: "Rivers Fork"
             */
            pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_TRAIL_NAMES_CRU, 0x59);
            return pcVar1;
        }
        break;
    case 0x53:
        _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[1]);
        if (_charTest == 0x4e) {
            _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Snake_River");
            if (_charTest == 0) {
                *hardcodedMapDescriptionGroupNum = 0x55;
                /*
                  added by script: "Snake River"
                 */
                pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_TRAIL_NAMES_CRU, 0x54);
                return pcVar1;
            }
        } else {
            _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[1]);
            if (_charTest == 0x50) {
                _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Spider_Island");
                if (_charTest == 0) {
                    *hardcodedMapDescriptionGroupNum = 0x5f;
                    /*
                      added by script: "Spider Island"
                     */
                    pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_TRAIL_NAMES_CRU, 0x5e);
                    return pcVar1;
                }
            } else {
                _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[1]);
                if ((_charTest == 0x57)
                    && (_charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Swampy_Island"),
                        _charTest == 0)) {
                    *hardcodedMapDescriptionGroupNum = 0x56;
                    /*
                      added by script: "Swampy Island"
                     */
                    pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_TRAIL_NAMES_CRU, 0x55);
                    return pcVar1;
                }
            }
        }
        break;
    case 0x54:
        _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[4]);
        if (_charTest == 0x48) {
            _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "The_Host");
            if (_charTest == 0) {
                *hardcodedMapDescriptionGroupNum = 0x5d;
                /*
                  added by script: "The Host"
                 */
                pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_TRAIL_NAMES_CRU, 0x5c);
                return pcVar1;
            }
        } else {
            _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[4]);
            if ((_charTest == 0x45)
                && (_charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Three_Little_Pigs"),
                    _charTest == 0)) {
                *hardcodedMapDescriptionGroupNum = 0x62;
                /*
                  added by script: "Three Little Pigs"
                 */
                pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_TRAIL_NAMES_CRU, 0x61);
                return pcVar1;
            }
        }
        break;
    case 0x55:
        _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[1]);
        if ((_charTest == 0x4c)
            && (_charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Ultimate_Victory"), _charTest == 0)) {
            *hardcodedMapDescriptionGroupNum = 0x65;
            /*
              added by script: "Ultimate Victory"
             */
            pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_TRAIL_NAMES_CRU, 100);
            return pcVar1;
        }
        break;
    case 0x57:
        _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[1]);
        if (_charTest == 0x41) {
            _charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Wazirs_Fortress");
            if (_charTest == 0) {
                *hardcodedMapDescriptionGroupNum = 0x59;
                /*
                  added by script: "Wazirs Fortress"
                 */
                pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_TRAIL_NAMES_CRU, 0x58);
                return pcVar1;
            }
        } else {
            _charTest = MACRO_CALL(OS_Func::__toupper)((int)mapName[1]);
            if ((_charTest == 0x49)
                && (_charTest = MACRO_CALL(OS_Func::__stricmp)(mapName, "Wide_Open_Plain"), _charTest == 0)) {
                *hardcodedMapDescriptionGroupNum = 0x5c;
                /*
                  added by script: "Wide Open Plain"
                 */
                pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_TRAIL_NAMES_CRU, 0x5b);
                return pcVar1;
            }
        }
    }
    return mapName;
}

}
