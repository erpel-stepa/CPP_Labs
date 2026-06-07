#include <iostream>
#include "module.h"

int main() {
    int choice;

    do {
        std::cout << "\nЛаба 17\n";
        std::cout << "1) CalcTree3\n";
        std::cout << "2) CalcTree25\n";
        std::cout << "0) Выход\n";
        std::cout << "Ваш выбор: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                runCalcTree3();
                break;
            case 2:
                runCalcTree25();
                break;
            case 0:
                std::cout << "Работа завершена\n";
                break;
            default:
                std::cout << "Нет такого пункта\n";
        }
    } while (choice != 0);

    return 0;
}
