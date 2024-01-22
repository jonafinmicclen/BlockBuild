#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H

#include <iostream>

class PlayerManager {
public:
	PlayerManager();

	int blockInHand;
	int numOfItems;

	bool actionCooldown;
	int actionCooldownCounter;
	int actionCooldownLength;

	void selectNextBlock();
	void setNumOfItems(const int num);
	void updateOnTick();
	void drawPlayerHUD();
};

#endif // PLAYERMANAGER_H
