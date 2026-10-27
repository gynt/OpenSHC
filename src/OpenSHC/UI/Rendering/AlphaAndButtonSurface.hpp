/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/Rendering/AlphaAndButtonSurface.hpp'
*/

#pragma once

#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

        // SIZE: 0x00000010
        class AlphaAndButtonSurface {
        public:
            // Unsigned Double-Word (ddw, 4-bytes)
            ushort* surfacePtr; // 0x00000000 length: 4
            // [249 0x00462FF0] max of GM image widths, at least 350; multiplied with height for malloc Unsigned
            // Double-Word (ddw, 4-bytes)
            dword surfaceWidth; // 0x00000004 length: 4
            // [249 0x00462FF0] max of GM image heights, at least 350 Unsigned Double-Word (ddw, 4-bytes)
            dword surfaceHeight; // 0x00000008 length: 4
            int currentImageWidth; // 0x0000000C length: 4

        private:
            AlphaAndButtonSurface(AlphaAndButtonSurface const&);
            void operator=(AlphaAndButtonSurface const&);

        public:
            AlphaAndButtonSurface() {};
            ~AlphaAndButtonSurface() {};

            // Constructor
            /**
             * Constructor: sets the global AlphaAndButtonSurfaceObj surface pointer to NULL and returns it.
             */
            AlphaAndButtonSurface* Constructor_AlphaAndButtonSurface();

            /**
             * Clears DAT_ButtonCurrentlyInteracting and renders the basic button background with the given blend
             * strength to the context-based target.
             */
            void renderNonInteractingButtonBackground(int blendStrength);

            /**
             * Frees the surface buffer (this->surfacePtr) if allocated. Identical-code-folded: also used by the
             * TextEditorState destructor.
             */
            void freeMemory();

            /**
             * Scans every ButtonGmData entry (stride 0x1C, 0x4718 bytes) and all of its icon states to find the
             * largest GM image width and height (each at least 350), stores them and allocates a 16-bit surface of
             * that size used for pixel-precise button hit tests.
             */
            void prepareButtonAndAlphaSurface();

            /**
             * Pixel-precise hit test of the current button: clears the off-screen surface to magenta, renders the
             * button picture at 0,0 and returns TRUE if the pixel under the mouse is non-magenta. When
             * DAT_CurrentButtonPictureInGm is negative it negates that global in place (side effect), renders that
             * picture from the button's alpha GM instead and additionally requires the pixel's low 5 bits to be 31.
             */
            BOOLEnum isMouseOverOpaqueButtonPixel();

            /**
             * For a building index > 0 whose owner is on the local player's team or is an AI slot: calls
             * extendResourceCountdownForPlayerBuildingsOfType(type, 1, owner) and for keep-type buildings (manor
             * house, stone keep, stronghold, campground) shows the popularity/gold popups. Does not use this.
             */
            void ProcessBuildingClickBonus(int buildingIndex);

            /**
             * Opens the building-and-status menu for a clicked building and returns TRUE, or returns FALSE.
             * Buildings of the local player, gates/towers of a same-team player and (in the editor) outposts get a
             * menu tab chosen by building type (barracks keeps tab 1; granary 4 also copies rationsSetting to
             * rationsSetting2/3, keeps 2 copy taxesSetting to taxesSetting2/taxesSliderUI, dog cage copies the
             * building's release-dogs flag to the player); any statue owned by the local player or by nobody opens
             * tab 0x59. Gatehouses (or a drawbridge's gatehouse) with field241_0x2c6 set and unhandled types return
             * FALSE; own placed siege towers, outposts outside the editor and listed buildings of other
             * teams/neutral owners instead store the building id/uid in BuildingsState.field28/field29 and return
             * FALSE. On success it extends the resource countdown for the local player's buildings of that type,
             * sets buildingandstatusmenuMenuTabToSwitchTo, switches to MVT_BUILDING_AND_STATUS_MENU, selects the
             * building (unit selection cleared), notifies the tutorial and clears field28/field29. Rejected when
             * buildingID < 1 or the game is paused.
             */
            BOOLEnum openBuildingStatusMenuForBuildingID(int buildingID);

            /**
             * If unitIndex > 0, the unit belongs to the local player, its isSelectable_OR_matchTime field is 0, the
             * game mode is neither editor nor Siege-That, the game is not paused and the unit is not UT_S_TOWER:
             * closes the help dialog, sets menu tab 0x46, switches to MVT_BUILDING_AND_STATUS_MENU, selects the
             * unit (building selection cleared) and returns TRUE; otherwise FALSE.
             */
            BOOLEnum SelectUnitAndOpenStatusMenu(int unitIndex);

            /**
             * Draws a generic menu button background at DAT_ButtonX/Y sized by DAT_ButtonW/H from
             * GID_INTERFACE_ICONS_3 pieces. The blend argument is remapped to 32+(9*b-288)/16 (input or result 32 =
             * invisible, returns). With -1 (treated as b=0) it draws a 10-px-tiled stretchable button
             * (left/middle/right pieces, picture offset -9 for buttons >= 31 px tall) on the requested surface;
             * otherwise it picks a fixed-size picture (20/60/80/100/200/300 px wide, surface always chosen by
             * getAreWeInAInGameMenu) or a tiled variant for wide/odd sizes. When DAT_ButtonCurrentlyInteracting,
             * hover highlight pieces are overlaid with an alpha mask. Restores the previous draw buffer.
             */
            void renderBasicButton(int reverseOrBlendStrength, RenderTarget renderSurface);
        };

        static_assert_cpp98_obj(sizeof(AlphaAndButtonSurface) == 16, AlphaAndButtonSurface);

#pragma pack(pop)

    } // namespace Rendering
} // namespace UI
} // namespace OpenSHC
