#include "InputHandler.h"

InputHandler::InputHandler() {  // Initialise threads

    std::thread keyboard_listener([this]() { _keyboard_listener(); });  // Start Keyboard thread
    keyboard_listener.detach();

    std::thread mouse_listener([this]() { _mouse_listener(); });        // Start Mouse thread
    mouse_listener.detach();
}
void InputHandler::_mouse_listener() {

    while (true) {

        // Move the mouse cursor to the middle of the screen
        SetCursorPos(centerX, centerY);

        // Get the current cursor position, only calculate if values returned
        if (GetCursorPos(&cursorPos)) {

            cursorPosBuffer.x = cursorPos.x;
            cursorPosBuffer.y = cursorPos.y;
        }
        Sleep(pollingT);
        if (GetCursorPos(&cursorPos)) {

            cursorSum.x += cursorPosBuffer.x - cursorPos.x;
            cursorSum.y += cursorPosBuffer.y - cursorPos.y;
        }
    }
}

void InputHandler::_keyboard_listener() {

    // Add for each key you want to listen for
    while (true) {
        if ((GetAsyncKeyState('W') & 0x8000) && !W_PRESSED) {
            W_PRESSED = true;
            pressedKeys.push_back('W');
        }
        if ((GetAsyncKeyState('A') & 0x8000) && !A_PRESSED) {
            A_PRESSED = true;
            pressedKeys.push_back('A');
        }
        if ((GetAsyncKeyState('S') & 0x8000) && !S_PRESSED) {
            S_PRESSED = true;
            pressedKeys.push_back('S');
        }
        if ((GetAsyncKeyState('D') & 0x8000) && !D_PRESSED) {
            D_PRESSED = true;
            pressedKeys.push_back('D');
        }
        if ((GetAsyncKeyState(VK_UP) & 0x8000) && !UP_PRESSED) {
            UP_PRESSED = true;
            pressedKeys.push_back('U');
        }
        if ((GetAsyncKeyState(VK_DOWN) & 0x8000) && !DOWN_PRESSED) {
            DOWN_PRESSED = true;
            pressedKeys.push_back('M');
        }
        if ((GetAsyncKeyState(VK_LEFT) & 0x8000) && !LEFT_PRESSED) {
            LEFT_PRESSED = true;
            pressedKeys.push_back('L');
        }
        if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) && !RIGHT_PRESSED) {
            RIGHT_PRESSED = true;
            pressedKeys.push_back('R');
        }
        if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) && !MB_LEFT_PRESSED) {
            MB_LEFT_PRESSED = true;
            pressedKeys.push_back('T');
        }
        if ((GetAsyncKeyState(VK_RBUTTON) & 0x8000) && !MB_RIGHT_PRESSED) {
            MB_RIGHT_PRESSED = true;
            pressedKeys.push_back('Y');
        }
    }
}

glm::vec2 InputHandler::getMouseMovement() {

    cursorSumBuffer = cursorSum;
    cursorSum.x = 0;
    cursorSum.y = 0;
    return cursorSumBuffer;

}

std::vector<char> InputHandler::getPressed() {

    // Return pressed keys and clear buffers
    pressedBuffer.clear();
    std::vector<char> pressedBuffer = pressedKeys;
    pressedKeys.clear();

    //Must reset each key
    W_PRESSED = false;
    A_PRESSED = false;
    S_PRESSED = false;
    D_PRESSED = false;
    UP_PRESSED = false;
    DOWN_PRESSED = false;
    LEFT_PRESSED = false;
    RIGHT_PRESSED = false;
    MB_RIGHT_PRESSED = false;
    MB_LEFT_PRESSED = false;

    return pressedBuffer;
}
