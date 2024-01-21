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

		actionCooldown = true;

		if (blockInHand + 2 <= numOfItems) {
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