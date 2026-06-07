#include <iostream>
#include <ctime>
#include <clocale>
#include "tasks.h"

using namespace std;

int main() {
    setlocale(0, "");
    srand((unsigned int)time(NULL));

    while (true) {
        cout << "\nМеню\n";
        cout << "1 – Слова с буквой «А»\n";
        cout << "2 – Коды символов строки\n";
        cout << "3 – Шифрование XOR\n";
        cout << "4 – Уникальные символы\n";
        cout << "5 – HEX → OCT\n";
        cout << "6 – Азбука Морзе\n";
        cout << "7 – FN1 → FN2\n";
        cout << "0 – Выход\n";

        int c = getInt("Ваш выбор: ", 0, 7);
        if (c == 0) break;

        if (c == 1) task1();
        if (c == 2) task2();
        if (c == 3) task3();
        if (c == 4) task4();
        if (c == 5) task5();
        if (c == 6) task6();
        if (c == 7) task7();
    }

    return 0;
}