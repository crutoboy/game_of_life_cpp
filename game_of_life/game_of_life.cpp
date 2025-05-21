#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include "Console.h"

using namespace std;

Console console;

void center_print(string text, int percent_height) {
    int width, height;
    console.getConsoleSize(width, height);
    int indentX = (width-1 - text.length()) / 2;
    int indentY = (height - 1) * ((float)percent_height / 100.0);
    console.setCursorPosition(0, 0);
    for (int i = 0; i < indentY; i++) {
        cout << endl;
    }
    for (int i = 0; i < indentX; i++) {
        cout << " ";
    }
    cout << text;
}

int count_of_neighbors(vector<vector<bool>> cells, int x, int y, int maxX, int maxY) {
    int res = 0;
    for (int lx = -1; lx <= 1; lx++) {
        int X = x + lx;
        for (int ly = -1; ly <= 1; ly++) {
            int Y = y + ly;
            if (0 <= X && X < maxX && 0 <= Y && Y < maxY)
                res += cells[Y][X];
        }
    }
    res -= cells[y][x];
    return res;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, "");

    int width, height;
    INPUT_RECORD input_record;
    
    console.enableConsoleClickableMode();

    // приветственное меню
    bool is_init = false;
    while (true)
    {
        if (!is_init || input_record.EventType == WINDOW_BUFFER_SIZE_EVENT) {
            console.clearConsole();
            console.getConsoleSize(width, height);
            cout << "Размер окна: " << width << "x" << height;

            center_print("Добро пожаловать в игру \"Жизнь\"", 50);
            center_print("\u00A9crutoboy 2025", 100);
            center_print("Чтобы начать игру нажмите enter", 75);

            is_init = true;
        }
        else if (input_record.EventType == KEY_EVENT && input_record.Event.KeyEvent.bKeyDown) {
            if (input_record.Event.KeyEvent.wVirtualKeyCode == VK_RETURN) 
                break;
        }

        console.updateConsoleEvents(input_record);
    }


    // начальная конфигурация поля
    is_init = false;

    int width_playing_area = 1;
    int height_playing_area = 1;

    vector<vector<bool>> cells = { {false} };

    while (true)
    {
        if (!is_init || input_record.EventType == WINDOW_BUFFER_SIZE_EVENT) {
            console.clearConsole();
            console.setCursorPosition(0, 0);
            console.getConsoleSize(width, height);
            width_playing_area = width / 2; // Делим на 2, так как каждая ячейка занимает 2 символа 
            height_playing_area = height - 2;

            cells.resize(height_playing_area, vector<bool>(width_playing_area, false));
            for (int i = 0; i < height_playing_area; i++) {
                cells[i].resize(width_playing_area, false);
            }

            cout << "Размер окна: " << width << "x" << height << " (размер поля: " << width_playing_area << "x" << height_playing_area << ") ";
            cout << "\u00A9crutoboy 2025";
            for (int i = 0; i < height - 1; i++) {
                cout << endl;
            }

            cout << "Живая клетка - ЛКМ, мёртвая - ПКМ, запуск симуляции - enter";

            for (int x = 0; x < width_playing_area; x++) 
                for (int y = 0; y < height_playing_area; y++) 
                    if(cells[y][x])
                        console.writeCharAt(x * 2 + 1, y + 1, '*');

            is_init = true;
        }
        else if (input_record.EventType == MOUSE_EVENT) {
            MOUSE_EVENT_RECORD mouse_event = input_record.Event.MouseEvent;
            int X = mouse_event.dwMousePosition.X / 2;
            int Y = mouse_event.dwMousePosition.Y - 1;
            if (0 <= X && X < width_playing_area && 0 <= Y && Y < height_playing_area) {
                if (mouse_event.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) { // если нажата ЛКМ
                    cells[Y][X] = true;
                    console.writeCharAt(X * 2 + 1, Y + 1, '*');                        
                } 
                else if (mouse_event.dwButtonState & RIGHTMOST_BUTTON_PRESSED) { // если нажата ПКМ
                    cells[Y][X] = false;
                    console.writeCharAt(X * 2 + 1, Y + 1, ' ');
                }
            }
        }
        else if (input_record.EventType == KEY_EVENT && input_record.Event.KeyEvent.bKeyDown) {
            if (input_record.Event.KeyEvent.wVirtualKeyCode == VK_RETURN)
                break;
        }

        console.updateConsoleEvents(input_record);
    }


    // затираем инструкцию с управлением
    console.setCursorPosition(0, height - 1);
    for (int i = 0; i < width; i++) 
        cout << ' ';
    console.setCursorPosition(0, height - 1);
    cout << "Наслаждайтесь:) ";
    // симуляция "жизни"
    int count = 0;
    while (true) {
        vector<vector<bool>> new_cells = cells;
        for (int x = 0; x < width_playing_area; x++) {
            for (int y = 0; y < height_playing_area; y++) {
                int neighbors = count_of_neighbors(cells, x, y, width_playing_area, height_playing_area);
                if (cells[y][x] && (neighbors < 2 || neighbors > 3)) {
                    new_cells[y][x] = false;
                    console.writeCharAt(x * 2 + 1, y + 1, ' ');
                }
                else if (!cells[y][x] && neighbors == 3) {
                    new_cells[y][x] = true;
                    console.writeCharAt(x * 2 + 1, y + 1, '*');
                }
            }
        }
        cells = new_cells;
        console.setCursorPosition(16, height - 1);
        cout << ++count;
        Sleep(100);
    }
}