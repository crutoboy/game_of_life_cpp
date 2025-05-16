#include "Console.h"
#include <windows.h>
#include <iostream>

void Console::getConsoleSize(int& width, int& height) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void Console::setCursorPosition(int x, int y) {
    COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void Console::writeCharAt(int x, int y, char ch, WORD color) {
    CHAR_INFO charInfo;
    charInfo.Char.AsciiChar = ch;
    charInfo.Attributes = color;
    COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
    SMALL_RECT region = { pos.X, pos.Y, pos.X, pos.Y };
    WriteConsoleOutputA(GetStdHandle(STD_OUTPUT_HANDLE), &charInfo, { 1, 1 }, { 0, 0 }, &region); // Исправлено: region вместо ®ion
}

char Console::readCharAt(int x, int y) {
    CHAR_INFO buffer;
    COORD size = { 1, 1 };
    COORD coord = { 0, 0 };
    SMALL_RECT region = { static_cast<SHORT>(x), static_cast<SHORT>(y), static_cast<SHORT>(x), static_cast<SHORT>(y) };
    ReadConsoleOutputA(GetStdHandle(STD_OUTPUT_HANDLE), &buffer, size, coord, &region); // Исправлено: region вместо ®ion
    return buffer.Char.AsciiChar;
}

void Console::clearConsole() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD consoleSize = csbi.dwSize.X * csbi.dwSize.Y;
    COORD topLeft = { 0, 0 };
    DWORD written;
    FillConsoleOutputCharacterA(hConsole, ' ', consoleSize, topLeft, &written);
    FillConsoleOutputAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE, consoleSize, topLeft, &written);
    SetConsoleCursorPosition(hConsole, topLeft);
}