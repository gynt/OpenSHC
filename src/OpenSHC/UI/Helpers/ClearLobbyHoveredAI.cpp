#include "../Helpers.func.hpp"

#include "OpenSHC/Globals/DAT_LobbyAddAICurrentlyHoveredAI.hpp"

namespace OpenSHC {
namespace UI {

    /*
      Clears the currently hovered AI slot in the lobby add-AI UI by zeroing   DAT_LobbyAddAICurrentlyHoveredAI. Note:
      Ghidra marks this as an inlined function, so it may not   appear as a standalone call in all callers.      renamed
      by: Claude Sonnet 4.6
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004AE7C0
    void Helpers::ClearLobbyHoveredAI() { DAT_LobbyAddAICurrentlyHoveredAI::instance = 0; }

}
}
