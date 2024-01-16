#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <Windows.h>
#include <thread>
#include <vector>
#include <iostream>
#include <glm/glm.hpp>

class InputHandler {
public:
	InputHandler();

	std::vector<char> getPressed();
	glm::vec2 getMouseMovement();

private:

	// Get center of screenm
	int centerX = GetSystemMetrics(SM_CXSCREEN) / 2;
	int centerY = GetSystemMetrics(SM_CYSCREEN) / 2;

	int pollingT = 2;

	void _keyboard_listener();
	void _mouse_listener();

	std::vector<char> pressedKeys;
	std::vector<char> pressedBuffer;

	//Mouse tracking
	POINT cursorPos = { 0,0 };
	glm::vec2 cursorPosBuffer = { 0,0 };
	glm::vec2 cursorSum = { 0,0 };
	glm::vec2 cursorSumBuffer = { 0,0 };

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
