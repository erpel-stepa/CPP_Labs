#include <iostream>

#include "module.h"

// точка входа
int main() {
    int choice = -1;

    do {
        std::cout << "\nМеню\n";
        std::cout << "1) Graf1 - степени вершин\n";
        std::cout << "2) Graf6 - города с L пересадками\n";
        std::cout << "3) Graf10 - все маршруты между городами\n";
        std::cout << "0) Выход\n";
        std::cout << "Ваш выбор: ";

        if (!readInt(choice)) {
            std::cout << "Введите целое число.\n";
            continue;
        }

        switch (choice) {
            case 1:
                runGraf1();
                break;
            case 2:
                runGraf6();
                break;
            case 3:
                runGraf10();
                break;
            case 0:
                std::cout << "Выход.\n";
                break;
            default:
                std::cout << "Такого пункта меню нет.\n";
        }
    } while (choice != 0);

    return 0;
}
