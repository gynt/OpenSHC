#include "../../Audio.func.hpp"
#include "../SFX.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Audio {

    using OpenSHC::Game::Resources::ResourceType;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0044A830
    int SFX::ComputePlayerPoints1(int playerID)
    {
        int _appleSalesPrice;
        int iVar1;
        int iVar2;
        int iVar3;
        int iVar4;
        int iVar5;
        int iVar6;
        int iVar7;
        int iVar8;
        int iVar9;
        int iVar10;
        int iVar11;
        int iVar12;
        int iVar13;
        int iVar14;
        int iVar15;
        int iVar16;
        int iVar17;
        int _woodSalesPriceDividedBy5;
        int _currentApple;
        int _currentArmor;
        int _currentBeer;
        int _currentBow;
        int _currentBread;
        int _currentCheese;
        int _currentCrossbow;
        int _currentFlour;
        int _currentGold;
        int _currentHops;
        int _currentIron;
        int _currentLeather;
        int _currentMace;
        int _currentMeat;
        int _currentPartialPitch;
        int _currentPike;
        int _currentSpear;
        int _currentStone;
        int _currentSword;
        int _totalTroopValue;
        _currentGold = DAT_GameState::instance.playerDataArray[playerID].currentResources[0xf];
        _totalTroopValue = DAT_GameState::instance.playerDataArray[playerID].totalTroopValue;
        _appleSalesPrice = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::getSalePriceOfGood,
            DAT_GameState::ptr)(OpenSHC::Game::Resources::RT_APPLE);
        _currentApple = DAT_GameState::instance.playerDataArray[playerID].currentResources[0xd];
        iVar1 = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::getSalePriceOfGood, DAT_GameState::ptr)(
            OpenSHC::Game::Resources::RT_MEAT);
        _currentMeat = DAT_GameState::instance.playerDataArray[playerID].currentResources[0xc];
        iVar2 = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::getSalePriceOfGood, DAT_GameState::ptr)(
            OpenSHC::Game::Resources::RT_CHEESE);
        _currentCheese = DAT_GameState::instance.playerDataArray[playerID].currentResources[0xb];
        iVar3 = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::getSalePriceOfGood, DAT_GameState::ptr)(
            OpenSHC::Game::Resources::RT_BREAD);
        _currentBread = DAT_GameState::instance.playerDataArray[playerID].currentResources[10];
        iVar4 = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::getSalePriceOfGood, DAT_GameState::ptr)(
            OpenSHC::Game::Resources::RT_IRONARMOR);
        _currentArmor = DAT_GameState::instance.playerDataArray[playerID].currentResources[0x18];
        iVar5 = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::getSalePriceOfGood, DAT_GameState::ptr)(
            OpenSHC::Game::Resources::RT_LEATHERARMOR);
        _currentLeather = DAT_GameState::instance.playerDataArray[playerID].currentResources[0x17];
        iVar6 = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::getSalePriceOfGood, DAT_GameState::ptr)(
            OpenSHC::Game::Resources::RT_SWORD);
        _currentSword = DAT_GameState::instance.playerDataArray[playerID].currentResources[0x16];
        iVar7 = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::getSalePriceOfGood, DAT_GameState::ptr)(
            OpenSHC::Game::Resources::RT_MACE);
        _currentMace = DAT_GameState::instance.playerDataArray[playerID].currentResources[0x15];
        iVar8 = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::getSalePriceOfGood, DAT_GameState::ptr)(
            OpenSHC::Game::Resources::RT_PIKE);
        _currentPike = DAT_GameState::instance.playerDataArray[playerID].currentResources[0x14];
        iVar9 = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::getSalePriceOfGood, DAT_GameState::ptr)(
            OpenSHC::Game::Resources::RT_SPEAR);
        _currentSpear = DAT_GameState::instance.playerDataArray[playerID].currentResources[0x13];
        iVar10 = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::getSalePriceOfGood, DAT_GameState::ptr)(
            OpenSHC::Game::Resources::RT_CROSSBOW);
        _currentCrossbow = DAT_GameState::instance.playerDataArray[playerID].currentResources[0x12];
        iVar11 = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::getSalePriceOfGood, DAT_GameState::ptr)(
            OpenSHC::Game::Resources::RT_BOW);
        _currentBow = DAT_GameState::instance.playerDataArray[playerID].currentResources[0x11];
        iVar12 = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::getSalePriceOfGood, DAT_GameState::ptr)(
            OpenSHC::Game::Resources::RT_FLOUR);
        _currentFlour = DAT_GameState::instance.playerDataArray[playerID].currentResources[0x10];
        iVar13 = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::getSalePriceOfGood, DAT_GameState::ptr)(
            OpenSHC::Game::Resources::RT_ALE);
        _currentBeer = DAT_GameState::instance.playerDataArray[playerID].currentResources[0xe];
        iVar14 = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::getSalePriceOfGood, DAT_GameState::ptr)(
            OpenSHC::Game::Resources::RT_PARTIALPITCH);
        _currentPartialPitch = DAT_GameState::instance.playerDataArray[playerID].currentResources[8];
        iVar15 = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::getSalePriceOfGood, DAT_GameState::ptr)(
            OpenSHC::Game::Resources::RT_IRON);
        _currentIron = DAT_GameState::instance.playerDataArray[playerID].currentResources[6];
        iVar16 = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::getSalePriceOfGood, DAT_GameState::ptr)(
            OpenSHC::Game::Resources::RT_STONE);
        _currentStone = DAT_GameState::instance.playerDataArray[playerID].currentResources[4];
        iVar17 = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::getSalePriceOfGood, DAT_GameState::ptr)(
            OpenSHC::Game::Resources::RT_HOPS);
        _currentHops = DAT_GameState::instance.playerDataArray[playerID].currentResources[3];
        _woodSalesPriceDividedBy5 = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::getSalePriceOfGood,
            DAT_GameState::ptr)(OpenSHC::Game::Resources::RT_WOOD);
        return (_woodSalesPriceDividedBy5 * DAT_GameState::instance.playerDataArray[playerID].currentResources[2]
                   + iVar17 * _currentHops + iVar16 * _currentStone + iVar15 * _currentIron
                   + iVar14 * _currentPartialPitch + iVar13 * _currentBeer + iVar12 * _currentFlour)
            / 10
            + DAT_GameState::instance.playerDataArray[playerID].currentPopulation * 10
            + (iVar11 * _currentBow + iVar4 * _currentArmor + iVar5 * _currentLeather + iVar6 * _currentSword
                  + iVar7 * _currentMace + iVar8 * _currentPike + iVar9 * _currentSpear + iVar10 * _currentCrossbow)
            / 10
            + (iVar3 * _currentBread + _appleSalesPrice * _currentApple + iVar1 * _currentMeat + iVar2 * _currentCheese)
            / 10
            + _totalTroopValue + _currentGold / 10;
    }

}
}
