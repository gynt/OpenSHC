#include "OpenSHC/Map/LandscapeState.func.hpp"

#include "OpenSHC/Globals/DAT_OrganismDefinedData.hpp"

namespace OpenSHC {
namespace Map {

    // counter >= 2 (signed jl 0x4F3740); countdown is decremented and tested for < 0 by the flags of the add (jns).
    // FUNCTION: STRONGHOLDCRUSADER 0x004F3730
    void LandscapeState::updateWind()
    {
        this->wind.counter++;
        if (this->wind.counter >= 2) {
            this->wind.countdown--;
            this->wind.counter = 0;
            this->wind.valueIs2 = 0;
            this->wind.valueIs1 = 0;
            if (this->wind.countdown < 0) {
                this->wind.countdown = 32;
                this->wind.value = DAT_OrganismDefinedData::instance.WindRelatedArray[this->wind.index];
                if (this->wind.value == 2) {
                    this->wind.valueIs2 = 1;
                }
                else if (this->wind.value == 1) {
                    this->wind.valueIs1 = 1;
                }
                this->wind.index++;
                if (this->wind.index >= 40) {
                    this->wind.index = 0;
                }
            }
        }
    }

}
}
