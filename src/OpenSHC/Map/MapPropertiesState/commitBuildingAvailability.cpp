#include "../../Map.func.hpp"
#include "../MapPropertiesState.func.hpp"

#include "OpenSHC/UI/BuildingNameRelatedSubStruct.hpp"

#include "OpenSHC/Globals/DAT_MissionAestheticsDefinedData.hpp"

namespace OpenSHC {
namespace Map {
    using OpenSHC::UI::BuildingNameRelatedSubStruct;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004BAEC0
    void MapPropertiesState::commitBuildingAvailability()
    {
        ushort _buildingAvailableUShort;
        uint _arrayOffset;
        int _arrayIndex;
        int _storedIndex;
        BuildingNameRelatedSubStruct* _ptr;
        short* psVar1;
        int iVar2;
        bool _buildingIsAvailable;
        short* _buildingAvailabilityPtr;
        int _index1;
        int _index2;
        int _index3;
        int _bnIndex;
        psVar1 = this->buildingAvailabilityRelatedFlags;
        /*
          bitmask for setting two shorts to 1
         */
        for (_storedIndex = 190; _storedIndex != 0; _storedIndex = _storedIndex + -1) {
            psVar1[0] = 1;
            psVar1[1] = 1;
            psVar1 = psVar1 + 2;
        }
        this->buildingAvailabilityArray2[0] = 1;
        this->buildingAvailabilityArray2[1] = 1;
        this->buildingAvailabilityArray2[2] = 1;
        this->buildingAvailabilityArray2[3] = 1;
        this->buildingAvailabilityArray2[4] = 1;
        this->buildingAvailabilityArray2[5] = 1;
        this->buildingAvailabilityArray2[6] = 1;
        this->buildingAvailabilityArray2[7] = 1;
        this->buildingAvailabilityArray2[8] = 1;
        this->buildingAvailabilityArray2[9] = 1;
        psVar1 = this->buildingAvailabilityArray2 + 10;
        for (_storedIndex = 19; _storedIndex != 0; _storedIndex = _storedIndex + -1) {
            psVar1[0] = 0;
            psVar1[1] = 0;
            psVar1 = psVar1 + 2;
        }
        *psVar1 = 0;
        _arrayIndex = 0;
        if (DAT_MissionAestheticsDefinedData::instance.BuildingNameRelatedStructArray[0].nameNumberInTextGroup != -1) {
            _arrayOffset = 0;
            _buildingAvailabilityPtr = this->buildingAvailability;
            _storedIndex = _arrayIndex;
            do {
                iVar2 = 1;
                _buildingIsAvailable = *_buildingAvailabilityPtr != 0;
                _ptr = (BuildingNameRelatedSubStruct*)((
                    int)&DAT_MissionAestheticsDefinedData::instance.BuildingNameRelatedStructArray[0]
                        .field1_0x4[0]);
                do {
                    _index1 = _ptr->identifier1;
                    _buildingAvailableUShort = (ushort)_buildingIsAvailable;
                    if (_index1 < 1) {
                        if (-1 < _index1)
                            break;
                        if (_buildingIsAvailable) {
                            *(undefined2*)((int)this + (0x290 - _index1) * 2) = 1;
                        }
                    } else {
                        this->buildingAvailabilityRelatedFlags[_index1] = _buildingAvailableUShort;
                    }
                    _index2 = _ptr->identifier2;
                    if (_index2 < 1) {
                        if (-1 < _index2)
                            break;
                        if (_buildingIsAvailable) {
                            *(undefined2*)((int)this + (0x290 - _index2) * 2) = 1;
                        }
                    } else {
                        this->buildingAvailabilityRelatedFlags[_index2] = _buildingAvailableUShort;
                    }
                    _index3 = _ptr->field2_0x8;
                    if (_index3 < 1) {
                        if (-1 < _index3)
                            break;
                        if (_buildingIsAvailable) {
                            *(undefined2*)((int)this + (0x290 - _index3) * 2) = 1;
                        }
                    } else {
                        this->buildingAvailabilityRelatedFlags[_index3] = _buildingAvailableUShort;
                    }
                    iVar2 = iVar2 + 3;
                    _ptr = _ptr + 3;
                } while (iVar2 < 10);
                _buildingAvailabilityPtr = _buildingAvailabilityPtr + 1;
                _arrayIndex = _storedIndex + 1;
                _arrayOffset = _storedIndex * 40 + 0x28;
                _bnIndex = _storedIndex + 1;
                _storedIndex = _arrayIndex;
            } while (DAT_MissionAestheticsDefinedData::instance.BuildingNameRelatedStructArray[_bnIndex]
                         .nameNumberInTextGroup
                != -1);
        }
        this->buildingAvailabilityArray2[10] = 1;
        this->buildingAvailabilityArray2[0x14] = 1;
        this->buildingAvailabilityArray2[0x1e] = 1;
        this->buildingAvailabilityArray2[0x28] = 1;
        this->buildingAvailabilityArray2[0x19] = 1;
        this->buildingAvailabilityArray2[0x1c] = 1;
        this->field8_0x224 = _arrayIndex + -2;
    }

}
}
