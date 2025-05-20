#include <iostream>
#include <string>
#include <windows.h>
#include "Console.h"

using namespace std;

Console console;

void center_print(string text, int percent_height) {
    int width, height;
    console.getConsoleSize(width, height);
    int indentX = (width - text.length()) / 2;
    int indentY = height * ((float)percent_height / 100.0);
    console.setCursorPosition(0, 0);
    for (int i = 0; i < indentY; i++) {
        cout << endl;
    }
    for (int i = 0; i < indentX; i++) {
        cout << " ";
    }
    cout << text;
}


int main() {
    setlocale(LC_ALL, "RU");

    center_print("Добро пожаловать в игру \"Жизнь\"", 50);
    center_print("Чтобы начать игру нажмите enter", 75);


    while (true) {
        
    }
}