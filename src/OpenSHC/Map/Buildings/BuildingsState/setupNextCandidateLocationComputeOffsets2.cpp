#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"



#include "OpenSHC/Globals/PTR_ARRAY_0040be48.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040BC40
void BuildingsState::setupNextCandidateLocationComputeOffsets2(int size,int nudge,int try,int offset)

{
switch(size) {
case 1:
this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.field179_0x7e8c[try].x;
this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.field179_0x7e8c[try].y;
break;
case 2:
this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.field180_0x7ecc[try].x;
this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.field180_0x7ecc[try].y;
break;
case 3:
this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.field181_0x7f2c[try].x;
this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.field181_0x7f2c[try].y;
break;
case 4:
this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.field182_0x7fac[try].x;
this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.field182_0x7fac[try].y;
break;
case 5:
this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.field183_0x804c[try].x;
this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.field183_0x804c[try].y;
break;
case 6:
this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.field184_0x810c[try].x;
this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.field184_0x810c[try].y;
break;
case 7:
this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.field185_0x81ec[try].x;
this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.field185_0x81ec[try].y;
break;
case 8:
this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.field186_0x82ec[try].x;
this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.field186_0x82ec[try].y;
break;
case 9:
this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.field187_0x840c[try].x;
this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.field187_0x840c[try].y;
break;
case 10:
this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.field188_0x854c[try].x;
this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.field188_0x854c[try].y;
break;
case 0xb:
this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.field189_0x86ac[try].x;
this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.field189_0x86ac[try].y;
break;
case 0xc:
this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.field190_0x882c[try].x;
this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.field190_0x882c[try].y;
break;
case 0xd:
this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.field191_0x89cc[try].x;
this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.field191_0x89cc[try].y;
}
if ((uint)((try / size) * 2) < 7) {
/* 
  WARNING: Switch is manually overridden
 */

switch(PTR_ARRAY_0040be48::instance[(try / size) * 2]) {
case (undefined *)0x40bda4:
this->DAT_TempYOffset = this->DAT_TempYOffset - offset;
break;
case (undefined *)0x40bdb0:
this->DAT_TempYOffset = this->DAT_TempYOffset + offset;
break;
case (undefined *)0x40bdbc:
this->DAT_TempXOffset = this->DAT_TempXOffset + offset;
break;
case (undefined *)0x40bdc8:
this->DAT_TempXOffset = this->DAT_TempXOffset - offset;
}
}
if ((this->DAT_TempXOffset < size) && (this->DAT_TempYOffset < size)) {
if (0x7fffffff < (uint)this->DAT_TempXOffset) {
this->DAT_TempXOffset = (this->DAT_TempXOffset - nudge) + 1;
return;
}
if (0x7fffffff < (uint)this->DAT_TempYOffset) {
this->DAT_TempYOffset = (this->DAT_TempYOffset - nudge) + 1;
}
}
return;
}


}
}
}