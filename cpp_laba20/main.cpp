#include <iostream>
#include "module.h"

int main() { // главное меню
    int choice = -1;

    while (choice != 0) {
        std::cout << "\nМеню\n";
        std::cout << "1) Расстояние между точками\n";
        std::cout << "2) Операторы класса Point\n";
        std::cout << "0) Выход\n";
        choice = readInt("Ваш выбор: ");

        switch (choice) {
            case 1:
                runTask1();
                break;
            case 2:
                runTask2();
                break;
            case 0:
                std::cout << "Работа завершена\n";
                break;
            default:
                std::cout << "Такого пункта нет\n";
        }
    }

    return 0;
}
