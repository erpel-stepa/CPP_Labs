#include <iostream>
#include "module.h"

int main() {
    using namespace std;

    bool work = true;

    while (work) {

        cout << "\n1 - Задание 1\n";
        cout << "2 - Задание 2\n";
        cout << "3 - Задание 3\n";
        cout << "4 - Задание 4\n";
        cout << "0 - Выход\n";
        cout << "Выбор: ";

        int choice;
        cin >> choice;

        if (!cin.good()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Некорректный ввод\n";
            continue;
        }

        switch (choice) {
            case 1:
                task1();
                break;
            case 2:
                task2();
                break;
            case 3:
                task3();
                break;
            case 4:
                task4();
                break;
            case 0:
                work = false;
                break;
            default:
                cout << "Неверный пункт\n";
                break;
        }
    }

    return 0;
}
