#include <iostream>
#include "module.h"

int main() {
    int choice;

    do {
        std::cout << "\nМеню:\n";
        std::cout << "1 — Археолог\n";
        std::cout << "2 — Хромой король\n";
        std::cout << "3 — K-ичные числа\n";
        std::cout << "0 — Выход\n";
        std::cout << "Выберите задание: ";

        std::cin >> choice;
        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(10000,'\n');
            std::cout << "Ошибка ввода, попробуйте снова\n";
            choice = -1;
        }

        switch (choice) {
            case 1: task1(); break;
            case 2: task2(); break;
            case 3: task3(); break;
            case 0: std::cout << "Выход\n"; break;
            default: std::cout << "Неверный пункт меню\n";
        }

    } while (choice != 0);

    return 0;
}
