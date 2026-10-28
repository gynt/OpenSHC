/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/HoveredState.hpp'
*/

#pragma once

#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/UI/HoveredStateElement.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::Commands::MappersEnum;
    using OpenSHC::UI::HoveredStateElement;

#pragma pack(push, 1)

    // SIZE: 0x000001E0
    class HoveredState {
    public:
        HoveredStateElement elements[20]; // 0x00000000 length: 480

    private:
        HoveredState(HoveredState const&);
        void operator=(HoveredState const&);

    public:
        HoveredState() {};
        ~HoveredState() {};

        // Constructor
        /**
         * HoveredState constructor: clears all elements and returns this.
         */
        HoveredState* Constructor_HoveredState();

        /**
         * Sets all 20 HoveredState elements' type to M_MAPPER_NULL (really __thiscall on the HoveredState in ECX).
         */
        void clearHoveredState();

        /**
         * In multiplayer (not GM_SOLITARY), frees pending-command preview elements whose expiry time is <= current
         * map tick.
         */
        void clearInvalidatedHoverStates();

        /**
         * In multiplayer, stores a pending-command preview (x, y, mapper type, size, rotation/extra info; values >
         * 79 replaced by 15) in the first free of 20 slots, expiring at mapTimeInTicks + commandDelay + 5. Does
         * nothing if all slots are used.
         */
        void createHoverStateElement(int x, int y, MappersEnum type, int size, int flag);

        /**
         * In multiplayer, draws previews for each pending HoveredState element: flags, heads, brazier, tents,
         * mangonel, ballista via floating layer elements, otherwise the building placement ghost (sets
         * TileMapState.previewSkipChecks=1 and temporarily uiBuildingRotation, restored at end). NAME? renders
         * pending-command previews rather than calculating a hovered tile.
         */
        void renderPendingCommandPreviews();
    };

    static_assert_cpp98_obj(sizeof(HoveredState) == 480, HoveredState);

#pragma pack(pop)

} // namespace UI
} // namespace OpenSHC
