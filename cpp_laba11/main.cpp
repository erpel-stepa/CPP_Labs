#include <iostream>
#include <clocale>
#include <ctime>
#include <cstdlib>
#include "structures.h"

int main() {
    setlocale(LC_ALL, "");
    srand(static_cast<unsigned>(time(nullptr)));

    int choice;

    do {
        std::cout << "\nЛабораторная работа по спискам\n";
        std::cout << "1) ListWork68\n";
        std::cout << "2) ListWork42\n";
        std::cout << "3) ListWork45\n";
        std::cout << "4) ListWork48\n";
        std::cout << "5) Циклический список: максимальная цепочка отрицательных\n";
        std::cout << "0) Выход\n";
        std::cout << "Ваш выбор: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                RunListWork68();
                break;
            case 2:
                RunListWork42();
                break;
            case 3:
                RunListWork45();
                break;
            case 4:
                RunListWork48();
                break;
            case 5:
                RunNegativeSequenceTask();
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