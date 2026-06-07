#include <iostream>
#include "module.h"

// главное меню
int main() {
    int choice = -1;

    while (choice != 0) {
        std::cout << "\nЛаба 18\n";
        std::cout << "1) TreeFun1: дерево поиска в двусвязный список\n";
        std::cout << "2) TreeFun5: итератор лево-право-корень\n";
        std::cout << "3) TreeFun13: удалить дублирующиеся поддеревья\n";
        std::cout << "0) Выход\n";
        std::cout << "Ваш выбор: ";

        if (!(std::cin >> choice)) {
            Checks::clearInput();
            std::cout << "Нужно ввести число.\n";
            continue;
        }

        switch (choice) {
            case 1:
                runTreeFun1();
                break;
            case 2:
                runTreeFun5();
                break;
            case 3:
                runTreeFun13();
                break;
            case 0:
                std::cout << "Выход.\n";
                break;
            default:
                std::cout << "Такого пункта нет.\n";
                break;
        }
    }

    return 0;
}
