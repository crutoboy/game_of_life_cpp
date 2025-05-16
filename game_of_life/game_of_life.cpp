
/*
int main() {
    int width, height;
    while (true) {
        getConsoleSize(width, height);
        std::cout << "Ширина: " << width << ", Высота: " << height << std::endl;
    } 
    return 0;
}
*/



#include <windows.h>
#include "Console.h"


/*int main() {
    // Записываем символ 'X' в позицию (5, 5) с зелёным цветом
    writeCharAt(5, 5, 'X', FOREGROUND_GREEN);

    // Читаем символ из позиции (5, 5)
    char ch = readCharAt(5, 5);
    std::cout << "Символ в (5, 5): " << ch << std::endl;

    // Перемещаем курсор в конец, чтобы видеть вывод
    setCursorPosition(0, 10);
    return 0;
}
*/

int main() {
    Console console;
    int x, y;
    while (true) {
        console.getConsoleSize(x, y);
        console.clearConsole();
        console.writeCharAt(x-1, y-1, 'X', FOREGROUND_GREEN);
    }
}