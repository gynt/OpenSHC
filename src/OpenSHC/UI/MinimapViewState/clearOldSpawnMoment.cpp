#include "../MinimapViewState.func.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004B6480
    void MinimapViewState::clearOldSpawnMoment()
    {
        if (this->spawnMomentCount == 0) {
            return;
        }
        DWORD _now = timeGetTime();
        int _count = this->spawnMomentCount;
        int _nextIndex = 0;
        if (_count <= 0) {
            return;
        }
        DWORD* _ptrMoment = this->spawnMoment;
        do {
            _nextIndex = _nextIndex + 1;
            /*
              If there is a spawnmoment older than 20 seconds, drop it and shift the rest down
             */
            if (20000 < (int)(_now - *_ptrMoment)) {
                if (_nextIndex < _count) {
                    int* piVar1 = this->spawnMomentX + _nextIndex + -1;
                    do {
                        *piVar1 = piVar1[1];
                        piVar1[0x14] = piVar1[0x15];
                        piVar1[0x28] = piVar1[0x29];
                        _nextIndex = _nextIndex + 1;
                        piVar1 = piVar1 + 1;
                    } while (_nextIndex < this->spawnMomentCount);
                }
                this->spawnMomentCount = this->spawnMomentCount + -1;
                return;
            }
            _ptrMoment = _ptrMoment + 1;
        } while (_nextIndex < _count);
    }

}
}
