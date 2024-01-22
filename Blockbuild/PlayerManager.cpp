#include "PlayerManager.h"

PlayerManager::PlayerManager() {
	blockInHand = 0;
	numOfItems = 0;
	actionCooldownCounter = 0;
	actionCooldownLength = 30;
	actionCooldown = false;
}

void PlayerManager::selectNextBlock() {
	if (!actionCooldown) {

		std::cout << "[PlayerManager]: Item no:" << blockInHand << " now in hand.\n";
		actionCooldown = true;

		if (blockInHand + 2 <= numOfItems) {		// Plus 2 as will add one afterwards and max index is 1-num of items.
			blockInHand++;
		}
		else {
			blockInHand = 0;
		}
	}
}

void PlayerManager::setNumOfItems(const int num) {
	numOfItems = num;
}

void PlayerManager::updateOnTick() {
	if (actionCooldown) {
		actionCooldownCounter++;
	}
	if (actionCooldownCounter > actionCooldownLength) {
		actionCooldown = false;
		actionCooldownCounter = 0;
	}
}

void PlayerManager::drawPlayerHUD() {



}