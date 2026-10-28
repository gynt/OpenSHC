/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Synchrony/Actions.hpp'
*/

#pragma once

#include "OpenSHC/Game/Resources/ResourceType.hpp"
namespace OpenSHC {
namespace Synchrony {
    namespace Actions {

        using OpenSHC::Game::Resources::ResourceType;

        /**
         * Clears (sets to -10) every lobby position whose entry belongs to playerID (entry+1 == playerID).
         */
        void __cdecl RemovePositionOfPlayer(int playerID);

        /**
         * Executes a recruit command if the player's army (armySize + count_2) is below the map army limit.
         * Engineers/ladderman come from the engineer's guild, tunnelers from the tunneler's guild, monks from the
         * given building, and Arabian units from the mercenary post. All other types are recruited as European
         * units from the barracks.
         */
        void __cdecl ProcessRecruitUnit(int playerID, int unitType, undefined4 recruitmentBuildingID);

        /**
         * If the building UID still matches, sets the building's producedItemType (e.g. a workshop's weapon type).
         */
        void __cdecl SetBuildingProductionType(
            undefined4 playerID, int buildingID, int producedItemType, int buildingUID);

        /**
         * If the building UID matches, stores value in drawbridgeState2. Value 10 applies a raise/close change via
         * applyGateOrDrawbridgeOpenCloseChange(id, FALSE, TRUE), and any other value applies the open/lower change
         * (TRUE, TRUE). The first parameter (player) is unused.
         */
        void __cdecl OpenOrCloseDrawbridge(undefined4 playerID, int buildingID, int value, int buildingUID);

        /**
         * If the building UID matches, sets gateState to newGateState and clears gateState2. State 10 closes the
         * gate (timer -1), and state 11 opens it with gateCloseOpenTimer = 600. Both go through
         * applyGateOrDrawbridgeOpenCloseChange.
         */
        void __cdecl GateOpenOrClose(undefined4 playerID, int buildingID, int newGateState, int buildingUID);

        /**
         * Sets the player's tax setting.
         */
        void __cdecl ChangeTaxes(int playerID, int taxesSetting);

        /**
         * Sets the player's rations setting.
         */
        void __cdecl ChangeRations(int playerID, int rationsSetting);

        /**
         * Market trade. Buy (0): if gold (currentResources[15]) covers getBatchBuyPrice, it adds 5 goods via
         * processResourceGain and, only if that succeeds (storage space), subtracts the price from gold and
         * marketGold. Sell (1): if the stock is not negative, gets the sell amount and the sales price, adds the
         * price to gold, marketGold and finalResults.finalGold, and removes the sold goods via processResourceLoss.
         */
        void __cdecl ProcessBuyOrSell(int playerID, int buyOrSell, ResourceType resourceType);

        /**
         * If the player has at least 10 stone, takes 10 stone and gives the siege unit 20 stoneAmmunition.
         * Otherwise, for an AI player (not GM_SOLITARY, no human ID, AI character set), sets
         * resourcesToAcquireArray[stone] = 10 so the AI buys stone.
         */
        void __cdecl TryAcquireAmmunitionOrPlanToBuyStone(int playerID, int unitID);

        /**
         * For each live catapult/trebuchet in the given tribe (selection group), tops stoneAmmunition up toward 20
         * at 1 stone per 2 ammo. If stone runs short, it spends all remaining stone on the current unit and
         * returns. The return value is a meaningless pointer.
         */
        short* __cdecl SelectionReplenishAmmo(int playerID, int tribeID);

        /**
         * Toggles the per-player snoozed flag for buildingType (byte array in playerDataArray at 0x115df8c +
         * playerID*0x39f4, types <= 0x5A). For the local player it plays the 'work halted' or 'functioning again'
         * voice line. It then applies the state to all of the player's buildings of that type.
         */
        void __cdecl ProcessBuildingSleepUpdate(int playerID, int buildingType);

        /**
         * If the building UID matches, recomputes the repair cost. If the player has enough wood and stone, it
         * restores the tower to max health and deducts the resources. Otherwise it plays the missing wood/stone SFX
         * for the local player.
         */
        void __cdecl ProcessTowerRepair(
            int playerID, int buildingID, int requiredWood, int requiredStone, int gameObjectID);

        /**
         * Release-dogs action for a dog cage. If the building UID matches, it sets the release flag, clears the 4
         * inside-unit ID/UID slots, and spawns 4 UT_CAGEDOG units for the player on the cage's 2x2 tile corners
         * (x*8, y*8 plus 8 offsets). Each spawned dog is linked to the cage as workplace (ID+UID), and the cage
         * records them in insideUnitID1..4/UID1..4. Plays FX_DOG_CAGE at the cage.
         */
        void __cdecl ProcessReleaseDogs(int playerID, int buildingID, int buildingUID);

        /**
         * An ally (responderPlayerID) accepts a pending request. If the responder's requestStateUnk is 2 (aid), it
         * posts 'Will come to your aid', and if 1 (attack), 'Will attack' with the requested target. The message is
         * shown only when the requester is the local human player. Always clears the responder's request state and
         * the requester's isNotNervousByEnemyTroopValue.
         */
        void __cdecl ProcessAllyAcceptsRequest(int requesterPlayerID, int responderPlayerID);

        /**
         * An ally (responderPlayerID) denies a pending attack/aid request. It posts 'Will not come to your aid'
         * (state 2) or 'Will not attack' (state 1, with the target) to the requester if that is the local human.
         * Clears the responder's request state and the requester's isNotNervousByEnemyTroopValue.
         */
        void __cdecl processAllyDeniesAttackOrAidRequest(int requesterPlayerID, int responderPlayerID);

        /**
         * Handles an ally request from requestedByPlayerID to playerID. Kind 10 cancels it (clears state). Kind 11
         * is a defence request: a human target gets the 'requests you defend him' chat and state 2, and an AI
         * target accepts if determineAIPlayerHelp agrees. Any other kind is an attack request on targetPlayerID: a
         * human gets the 'request you attack' chat and state 1, and an AI accepts if
         * determineAIPlayerAttackRequestResponse agrees, then aborts its current attack.
         */
        void __cdecl ProcessAllyRequestAttackDefense(
            int targetPlayerID, int playerID, int requestedByPlayerID, int param_4);

        /**
         * A player (askee, who is actually the requester and receiver of the goods) asks askedPlayerID for amount
         * of goods index goodsIndex (resource = goodsIndex + RT_LOGS). A human asked player has the request stored
         * in requestedGoodsArray1Unk/2Unk[askee] and gets an 'is requesting goods' chat if local. An AI asked
         * player immediately transfers non-gold goods, plays the 'goods sent' bink and adds the sell value to the
         * final goods sent/received stats. Gold requests to an AI are ignored.
         */
        void __cdecl ProcessAllyRequestingGoods(int askedPlayerID, int goodsIndex, int amount, int askee);

        /**
         * Executes a goods transfer from senderPlayerID (param_4) to receiverPlayerID (param_1). Gold is capped at
         * the sender's gold, moved directly, and the amount is added to finalGoodsRecieved/finalGoodsSent. Other
         * goods (partial pitch is treated as pitch) go through processResourceGain/Loss, and getSellPrice of the
         * amount is added to the received/sent stats. Plays a deposit SFX for the local receiver (iron for
         * iron/gold, sword for weapons/armour, flour otherwise). Outside GM_SOLITARY/GM_SKIRMISH_SINGLE_PLAYER it
         * posts 'Goods received from ally' + '%d %s - ' to the local receiver or 'Goods sent to ally' + '%d %s' to
         * the local sender. Clears the sender's pending request from the receiver if it was for this resource type,
         * and plays the thanks Bink. NAME? This performs the transfer (an ally sending goods); it does not create a
         * request.
         */
        void __cdecl ProcessAllySendsGoods(int receiverPlayerID, ResourceType goodsType, int amount, int senderPlayerID);

        /**
         * An ally (denyingPlayerID) refuses a goods request: clears requestedGoodsArray1Unk/2Unk[requesterPlayerID]
         * in the denier's player data. If the requester is the local player (no human check), posts 'Ally denies
         * request'. The chat entry is attributed to requesterPlayerID itself.
         */
        void __cdecl ProcessAllyDeniesRequest(int requesterPlayerID, int denyingPlayerID);

    } // namespace Actions
} // namespace Synchrony
} // namespace OpenSHC
