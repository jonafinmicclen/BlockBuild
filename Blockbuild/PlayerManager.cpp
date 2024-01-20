#include "PlayerManager.h"

PlayerManager::PlayerManager() {
	blockInHand = 0;
	numOfItems = 0;
}

void PlayerManager::selectNextBlock() {
	if (blockInHand + 2 <= numOfItems) {
		blockInHand++;
	}
	else {
		blockInHand = 0;
	}
}

void PlayerManager::setNumOfItems(const int num) {
	numOfItems = num;
}