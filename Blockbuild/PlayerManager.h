#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H

class PlayerManager {
public:
	PlayerManager();

	int blockInHand;
	int numOfItems;

	void selectNextBlock();
	void setNumOfItems(const int num);
};

#endif // PLAYERMANAGER_H
