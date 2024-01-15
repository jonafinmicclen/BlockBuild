#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <Windows.h>
#include <thread>
#include <vector>
#include <iostream>

class InputHandler {
public:
	InputHandler();
	std::vector<char> getPressed();

private:
	void _listener();

	std::vector<char> pressedKeys;
	std::vector<char> pressedBuffer;

	// Bool for each key
	bool W_PRESSED = false;
	bool A_PRESSED = false;
	bool S_PRESSED = false;
	bool D_PRESSED = false;
	bool UP_PRESSED = false;
	bool DOWN_PRESSED = false;
	bool LEFT_PRESSED = false;
	bool RIGHT_PRESSED = false;
	bool MB_RIGHT_PRESSED = false;
	bool MB_LEFT_PRESSED = false;
};

#endif // INPUTHANDLER_H
