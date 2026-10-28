#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/g_tutorialActionType.hpp"
#include "OpenSHC/Globals/g_tutorialActionBuildingType.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::Map::Buildings::BuildingType;

    /*
      Sets g_tutorialActionType (tutorial action type) and g_tutorialActionBuildingType (building type) unless actionState is 11
       and g_tutorialActionType is already 7 — in which case the update is skipped to avoid overwriting a
       pending state. Used to record which building-related action the player last performed for
       tutorial step evaluation.

       renamed by: Claude Sonnet 4.6
     */

    // FUNCTION: STRONGHOLDCRUSADER 0x004BC690
    void Helpers::SetTutorialBuildingActionState(int actionState, BuildingType buildingType)
    {
        if (actionState != 11 || g_tutorialActionType::instance != 7) {
            g_tutorialActionType::instance = actionState;
            g_tutorialActionBuildingType::instance = buildingType;
        }
    }

}
}
