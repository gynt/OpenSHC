#include "../GreatestLord.func.hpp"

#include "OpenSHC/Audio/SFX.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BlendingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_GreatestLordDefinedData.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Coordinates/XYPairShort.hpp"
#include "OpenSHC/Game/Player/PlayerData.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {

        using DE::SHCDE::eGM;
        using DE::SHCDE::eTextSections;
        using IO::Graphics::GmID;
        using Text::TextAlignment;
        using WindowsHelper::Enums::BOOLEnum;
        using Coordinates::XYPairShort;
        using Game::Player::PlayerData;
        using Rendering::Colors::BGR24;

        // FUNCTION: STRONGHOLDCRUSADER 0x004AE0F0
        void GreatestLord::MenuModalRenderFunction_GreatestLord(int x, int y, int width, int height)
        {
            int iVar1;
            XYPairShort XVar2;
            int _zeroIfDead;
            int _playerPoints;
            XYPairShort* pXVar3;
            char* pcVar4;
            int iVar5;
            int iVar6;
            int* piVar7;
            int iVar8;
            int iVar9;
            XYPairShort XVar10;
            int xPos;
            TextAlignment TVar11;
            BGR24 BVar12;
            BOOLEnum BVar13;
            XYPairShort local_d4;
            PlayerData* _playerData;
            int local_c8[20];
            undefined4 local_78;
            XYPairShort local_74;
            int local_70[4];
            undefined4 local_60;
            undefined4 local_54;
            undefined4 local_48;
            undefined4 local_3c;
            undefined4 local_30;
            undefined4 local_24;
            undefined4 local_18;
            undefined4 local_c;
            int _playerIndex_1;
            int _playerIndex_2;
            int _playerIndex_3;
            xPos = x + 0x3a;
            XVar2 = (XYPairShort)(height + -0x60);
            iVar5 = 0;
            local_c8[10] = 0;
            local_c8[0xb] = 0;
            local_c8[0xc] = 0;
            local_c8[0xd] = 0;
            local_c8[0xe] = 0;
            local_c8[0xf] = 0;
            local_c8[0x10] = 0;
            local_c8[0x11] = 0;
            local_c8[0x12] = 0;
            local_c8[0x13] = 0;
            local_c8[0] = 0;
            local_c8[1] = 0;
            local_c8[2] = 0;
            local_c8[3] = 0;
            local_c8[4] = 0;
            local_c8[5] = 0;
            local_c8[6] = 0;
            local_c8[7] = 0;
            local_c8[8] = 0;
            local_c8[9] = 0;
            if (0 < (int)XVar2) {
                do {
                    if (iVar5 == 0) {
                        iVar8 = 1;
                    } else {
                        iVar8 = (-(uint)(iVar5 != height + -0x78) & 0xfffffffa) + 0xd;
                    }
                    iVar9 = 0;
                    if (0 < width + -0x30) {
                        do {
                            iVar6 = iVar8;
                            if (iVar9 == 0) {
                            LAB_004ae1c0:
                                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                                    DAT_TextureRenderCoreObject::ptr)(IO::Graphics::GID_INTERFACE_ICONS_3,
                                    iVar6, iVar9 + 0x18 + x, iVar5 + 0x18 + y,
                                    IO::Graphics::GID_INTERFACE_ICONS_3, iVar6 + 3, 0);
                            } else {
                                if (iVar9 == width + -0x48) {
                                    iVar6 = iVar8 + 2;
                                    goto LAB_004ae1c0;
                                }
                                if (iVar8 != 7) {
                                    iVar6 = iVar8 + 1;
                                    goto LAB_004ae1c0;
                                }
                            }
                            iVar9 = iVar9 + 0x18;
                        } while (iVar9 < width + -0x30);
                    }
                    iVar5 = iVar5 + 0x18;
                } while (iVar5 < (int)XVar2);
            }
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                DAT_PencilRenderCore::ptr)(x + 0x30, y + 0x30, width + -0x31 + x, height + -0x61 + y, 0x14);
            local_78 = 0;
            local_70[1] = 0;
            local_60 = 0;
            local_54 = 0;
            local_48 = 0;
            local_3c = 0;
            local_30 = 0;
            local_24 = 0;
            local_18 = 0;
            local_c = 0;
            local_d4 = XVar2;
            if (DAT_GreatestLordDefinedData::instance.tableSortBy == 1) {
                XVar2.x = 0;
                XVar2.y = 0;
                local_d4 = (XYPairShort)(local_c8 + 0x14);
                _playerIndex_1 = 1;
                piVar7 = local_70;
                /*
                  Would need to split for proper type, but not possible. -TheRedDaemon
                 */
                _playerData = &DAT_GameState::instance.playerDataArray[1];
                pXVar3 = &local_74;
                do {
                    if (DAT_GameSynchronyState::instance.finalResults.active[_playerIndex_1] != 0) {
                        *(int*)local_d4 = _playerIndex_1;
                        iVar5 = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getAliveLordForPlayer,
                            DAT_UnitsState::ptr)(_playerIndex_1);
                        if ((iVar5 == 0)
                            && ((int)(DAT_GameCore::instance.section1127 + 200)
                                < (int)DAT_GameCore::instance.mapTimeInTicks)) {
                            local_c8[_playerIndex_1] = 1;
                            pXVar3->x = 0;
                            pXVar3->y = 0;
                            *piVar7 = 0;
                        } else {
                            XVar10 = *(XYPairShort*)(_playerData->currentResources + 0xf);
                            *pXVar3 = XVar10;
                            if ((int)XVar10 < 0) {
                                pXVar3->x = 0;
                                pXVar3->y = 0;
                            }
                            *piVar7 = _playerData->armySize;
                        }
                        local_d4 = (XYPairShort)((int)local_d4 + 0xc);
                        XVar2 = (XYPairShort)((int)XVar2 + 1);
                        pXVar3 = pXVar3 + 3;
                        piVar7 = piVar7 + 3;
                    }
                    _playerData = _playerData + 0xe7d;
                    _playerIndex_1 = _playerIndex_1 + 1;
                } while ((int)_playerData < 0x117ccc8);
            }
            if (DAT_GreatestLordDefinedData::instance.tableSortBy == 0) {
                XVar2.x = 0;
                XVar2.y = 0;
                local_d4 = (XYPairShort)(local_c8 + 0x14);
                _playerIndex_2 = 1;
                piVar7 = local_70;
                _playerData = &DAT_GameState::instance.playerDataArray[1];
                pXVar3 = &local_74;
                do {
                    if (DAT_GameSynchronyState::instance.finalResults.active[_playerIndex_2] != 0) {
                        *(int*)local_d4 = _playerIndex_2;
                        iVar5 = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getAliveLordForPlayer,
                            DAT_UnitsState::ptr)(_playerIndex_2);
                        if ((iVar5 == 0)
                            && ((int)(DAT_GameCore::instance.section1127 + 200)
                                < (int)DAT_GameCore::instance.mapTimeInTicks)) {
                            local_c8[_playerIndex_2] = 1;
                            pXVar3->x = 0;
                            pXVar3->y = 0;
                        LAB_004ae3af:
                            *piVar7 = 0;
                        } else {
                            iVar5 = _playerData->armySize;
                            *pXVar3 = _playerData->barracksParadegroundLocations[0][5];
                            *piVar7 = iVar5;
                            if (iVar5 < 0)
                                goto LAB_004ae3af;
                        }
                        local_d4 = (XYPairShort)((int)local_d4 + 0xc);
                        XVar2 = (XYPairShort)((int)XVar2 + 1);
                        pXVar3 = pXVar3 + 3;
                        piVar7 = piVar7 + 3;
                    }
                    _playerData = _playerData + 0xe7d;
                    _playerIndex_2 = _playerIndex_2 + 1;
                } while ((int)_playerData < 0x117cc98);
            }
            if (DAT_GreatestLordDefinedData::instance.tableSortBy == -1) {
                XVar2.x = 0;
                XVar2.y = 0;
                local_d4 = (XYPairShort)(local_c8 + 0x14);
                _playerIndex_3 = 1;
                piVar7 = local_70;
                pXVar3 = &local_74;
                do {
                    if (DAT_GameSynchronyState::instance.finalResults.active[_playerIndex_3] != 0) {
                        *(int*)local_d4 = _playerIndex_3;
                        _zeroIfDead = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getAliveLordForPlayer,
                            DAT_UnitsState::ptr)(_playerIndex_3);
                        if ((_zeroIfDead == 0)
                            && ((int)(DAT_GameCore::instance.section1127 + 200)
                                < (int)DAT_GameCore::instance.mapTimeInTicks)) {
                            local_c8[_playerIndex_3] = 1;
                            pXVar3->x = 0;
                            pXVar3->y = 0;
                        } else {
                            _playerPoints = MACRO_CALL(Audio::SFX_Func::ComputePlayerPoints1)(_playerIndex_3);
                            pXVar3->x = (short)_playerPoints;
                            pXVar3->y = (short)((uint)_playerPoints >> 0x10);
                        }
                        local_d4 = (XYPairShort)((int)local_d4 + 0xc);
                        XVar2 = (XYPairShort)((int)XVar2 + 1);
                        pXVar3 = pXVar3 + 3;
                        *piVar7 = 0;
                        piVar7 = piVar7 + 3;
                    }
                    _playerIndex_3 = _playerIndex_3 + 1;
                } while (_playerIndex_3 < 9);
            }
            _playerData = (PlayerData*)0x0;
            if (0 < (int)XVar2) {
                XVar10.x = 0;
                XVar10.y = 0;
                do {
                    iVar5 = -1;
                    pXVar3 = &local_74;
                    iVar8 = 0;
                    do {
                        if ((pXVar3[-1] != (XYPairShort)0x0)
                            && ((iVar5 == -1
                                || (((int)XVar10 <= (int)*pXVar3
                                    && ((*pXVar3 != XVar10 || ((int)local_d4 < (int)pXVar3[1])))))))) {
                            local_d4 = pXVar3[1];
                            XVar10 = *pXVar3;
                            iVar5 = iVar8;
                        }
                        iVar8 = iVar8 + 1;
                        pXVar3 = pXVar3 + 3;
                    } while (iVar8 < (int)XVar2);
                    if (iVar5 < 0)
                        break;
                    local_c8[(int)&_playerData->field_0x547] = local_c8[iVar5 * 3 + 0x14];
                    _playerData = (PlayerData*)((int)&_playerData->armySize + 1);
                    local_c8[iVar5 * 3 + 0x14] = 0;
                } while ((int)_playerData < (int)XVar2);
            }
            iVar5 = y + 0x7e;
            local_d4.x = 1;
            local_d4.y = 0;
            do {
                if (1 < (int)local_d4) {
                    iVar5 = iVar5 + 0x18;
                }
                iVar8 = local_c8[(int)local_d4 + 10];
                if (iVar8 < 1)
                    break;
                iVar9 = local_c8[iVar8];
                iVar6 = 0;
                if (iVar9 == 0) {
                    iVar1 = DAT_GameState::instance.mapAndTime.playerGroupArray[iVar8];
                    if (0 < iVar1) {
                        MACRO_CALL_MEMBER(
                            UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            DE::SHCDE::GM_INTERFACE_ICONS2, iVar1 * 2 + 0x1ec, x + 0x26, iVar5 + -2);
                    }
                } else {
                    MACRO_CALL_MEMBER(
                        UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                        DE::SHCDE::GM_INTERFACE_ICONS2, 0x299, x + 0x26, iVar5 + 2);
                    iVar6 = 6;
                }
                DAT_TextManagerObject::instance.field12_0x30 = 1;
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderMultilineText6Unk, DAT_TextManagerObject::ptr)(
                    DAT_GameSynchronyState::instance.finalResults.names[iVar8], xPos, iVar5 + iVar6, 0x104,
                    (uint)((int)(DAT_RenderingDefinedData::instance
                            .ColorArray[DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[iVar8]])),
                    0, 0x12, 0);
                if (iVar9 == 0) {
                    iVar9 = DAT_GameState::instance.playerDataArray[iVar8].currentResources[0xf];
                    if (iVar9 < 0) {
                        iVar9 = 0;
                    }
                    MACRO_CALL_MEMBER(
                        Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                        iVar9, x + 0x16d, iVar5, Text::TTA_LEFT, 0xccfaff, 0x12, FALSE, 0);
                    MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2,
                        DAT_TextManagerObject::ptr)(DAT_GameState::instance.playerDataArray[iVar8].armySize, x + 0x1ef,
                        iVar5, Text::TTA_LEFT, 0xccfaff, 0x12, FALSE, 0);
                }
                local_d4 = (XYPairShort)((int)local_d4 + 1);
            } while ((int)local_d4 < 9);
            if (DAT_GreatestLordDefinedData::instance.tableSortBy == 1) {
                iVar6 = 0;
                BVar13 = FALSE;
                iVar9 = 0x11;
                BVar12 = 0xccfaff;
                TVar11 = Text::TTA_LEFT;
                iVar5 = y + 0x168;
                iVar8 = xPos;
                /*
                  "Sorted by gold"   added by script: "Sorted by gold"
                 */
                pcVar4 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MP_RANK, 2);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    pcVar4, iVar8, iVar5, TVar11, BVar12, iVar9, BVar13, iVar6);
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGM,
                    DAT_TextureRenderCoreObject::ptr)(DE::SHCDE::GM_INTERFACE_ICONS2, 0x2da,
                    DAT_TextManagerObject::instance.currentXOffset_0x0 + 10 + xPos, y + 0x163);
            }
            if (DAT_GreatestLordDefinedData::instance.tableSortBy == 0) {
                iVar6 = 0;
                BVar13 = FALSE;
                iVar9 = 0x11;
                BVar12 = 0xccfaff;
                TVar11 = Text::TTA_LEFT;
                iVar5 = y + 0x168;
                iVar8 = xPos;
                /*
                  "Sorted by troops"   added by script: "Sorted by troops"
                 */
                pcVar4 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MP_RANK, 3);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    pcVar4, iVar8, iVar5, TVar11, BVar12, iVar9, BVar13, iVar6);
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGM,
                    DAT_TextureRenderCoreObject::ptr)(DE::SHCDE::GM_INTERFACE_ICONS2, 0x298,
                    DAT_TextManagerObject::instance.currentXOffset_0x0 + 10 + xPos, y + 0x15e);
            }
            if (DAT_GreatestLordDefinedData::instance.tableSortBy == -1) {
                iVar9 = 0;
                BVar13 = FALSE;
                iVar8 = 0x11;
                BVar12 = 0xccfaff;
                TVar11 = Text::TTA_LEFT;
                iVar5 = y + 0x168;
                /*
                  added by script: "Greatest Lord"
                 */
                pcVar4 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MP_RANK, 1);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    pcVar4, xPos, iVar5, TVar11, BVar12, iVar8, BVar13, iVar9);
            }
        }

    }
}
}
