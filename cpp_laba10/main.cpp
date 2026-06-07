#include "structures.h"

#include <iostream>

int main() {
    bool rabotai_kod = true;
    while (rabotai_kod) {
        std::cout << "\nМеню\n";
        std::cout << "1) Dynamic5\n";
        std::cout << "2) Dynamic22\n";
        std::cout << "3) ListWork3\n";
        std::cout << "4) ListWork24\n";
        std::cout << "5) ListWork61\n";
        std::cout << "6) Демонстрация (add/remove/search)\n";
        std::cout << "0) Выход\n";
        std::cout << "Выберите пункт (0-6): ";

        int choice = 0;
        std::cin >> choice;
        if (!std::cin) {
            std::cout << "Ошибка ввода\n";
            rabotai_kod = false;
        }

        switch (choice) {
            case 1:
                run_task_dynamic5();
                break;
            case 2:
                run_task_dynamic22();
                break;
            case 3:
                run_task_list_work3();
                break;
            case 4:
                run_task_list_work24();
                break;
            case 5:
                run_task_list_work61();
                break;
            case 6:
                run_demo_operations();
                break;
            case 0:
                std::cout << "Завершение программы\n";
                return 0;
            default:
                std::cout << "Такого пункта нет\n";
                break;
        }
    }
}