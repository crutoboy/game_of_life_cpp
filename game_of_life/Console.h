#pragma once
#include <windows.h>

class Console {
private:
    HANDLE consoleHandler;
    DWORD consolePrevMode;
public:
    void getConsoleSize(int& width, int& height) {}
    void setCursorPosition(int x, int y) {}
    void writeCharAt(int x, int y, char ch, WORD color = 7) {}
    char readCharAt(int x, int y) {}
    void clearConsole() {}
    void enableConsoleClickableMode() {}
    void updateConsoleEvents() {}
    void disableConsoleClickableMode() {}
};

