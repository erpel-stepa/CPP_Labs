#include <iostream>
#include <limits>

#include "module.h"

int main() {
    while (true) {
        std::cout << "\nМЕНЮ LAB13\n";
        std::cout << "1) STL3Alg4 (Список)\n";
        std::cout << "2) STL3Alg18 (Дек)\n";
        std::cout << "3) STL3Alg48 (Вектор)\n";
        std::cout << "4) STL3Alg60 (Список)\n";
        std::cout << "0) Выход\n";
        std::cout << "Выберите пункт: ";

        int choice = -1;
        std::cin >> choice;

        if (!std::cin) {
            std::cout << "Ошибка ввода\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        try {
            switch (choice) {
                case 1:
                    run_stl3alg4();
                    break;
                case 2:
                    run_stl3alg18();
                    break;
                case 3:
                    run_stl3alg48();
                    break;
                case 4:
                    run_stl3alg60();
                    break;
                case 0:
                    std::cout << "Завершение программы\n";
                    return 0;
                default:
                    std::cout << "Неизвестный пункт\n";
                    break;
            }
        } catch (const std::exception& error) {
            std::cout << "Ошибка: " << error.what() << '\n';
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}