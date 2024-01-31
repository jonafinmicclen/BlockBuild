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
        //MOUSE KEYS
        if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) && !MB_LEFT_PRESSED) {
            MB_LEFT_PRESSED = true;
            pressedKeys.push_back('T');
        }
        if ((GetAsyncKeyState(VK_RBUTTON) & 0x8000) && !MB_RIGHT_PRESSED) {
            MB_RIGHT_PRESSED = true;
            pressedKeys.push_back('Y');
        }
        //NUMBER KEYS
        if ((GetAsyncKeyState('0') & 0x8000) && !ZERO_PRESSED) {
            ZERO_PRESSED = true;
            pressedKeys.push_back('0');
        }
        if ((GetAsyncKeyState('1') & 0x8000) && !ONE_PRESSED) {
            ONE_PRESSED = true;
            pressedKeys.push_back('1');
        }
        if ((GetAsyncKeyState('2') & 0x8000) && !TWO_PRESSED) {
            TWO_PRESSED = true;
            pressedKeys.push_back('2');
        }
        if ((GetAsyncKeyState('3') & 0x8000) && !THREE_PRESSED) {
            THREE_PRESSED = true;
            pressedKeys.push_back('3');
        }
        if ((GetAsyncKeyState('4') & 0x8000) && !FOUR_PRESSED) {
            FOUR_PRESSED = true;
            pressedKeys.push_back('4');
        }
        if ((GetAsyncKeyState('5') & 0x8000) && !FIVE_PRESSED) {
            FIVE_PRESSED = true;
            pressedKeys.push_back('5');
        }
        if ((GetAsyncKeyState('6') & 0x8000) && !SIX_PRESSED) {
            SIX_PRESSED = true;
            pressedKeys.push_back('6');
        }
        if ((GetAsyncKeyState('7') & 0x8000) && !SEVEN_PRESSED) {
            SEVEN_PRESSED = true;
            pressedKeys.push_back('7');
        }
        if ((GetAsyncKeyState('8') & 0x8000) && !EIGHT_PRESSED) {
            EIGHT_PRESSED = true;
            pressedKeys.push_back('8');
        }
        if ((GetAsyncKeyState('9') & 0x8000) && !NINE_PRESSED) {
            NINE_PRESSED = true;
            pressedKeys.push_back('9');
        }
        if ((GetAsyncKeyState('E') & 0x8000) && !E_PRESSED) {
            E_PRESSED = true;
            pressedKeys.push_back('E');
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

    E_PRESSED = false;

    MB_RIGHT_PRESSED = false;
    MB_LEFT_PRESSED = false;

    ZERO_PRESSED = false;
    ONE_PRESSED = false;
    TWO_PRESSED = false;
    THREE_PRESSED = false;
    FOUR_PRESSED = false;
    FIVE_PRESSED = false;
    SIX_PRESSED = false;
    SEVEN_PRESSED = false;
    EIGHT_PRESSED = false;
    NINE_PRESSED = false;

    return pressedBuffer;
}


