#include <iostream>

#include "module.h"

int main() {
    while (true) {
        std::cout << "\nМеню лабораторной работы 16\n";
        std::cout << "1. Имена\n";
        std::cout << "2. Человек с именем\n";
        std::cout << "3. Человек с родителем\n";
        std::cout << "4. Города\n";
        std::cout << "5. Создаем имена\n";
        std::cout << "6. Создаем человека\n";
        std::cout << "7. Кот мяукает\n";
        std::cout << "0. Выход\n";

        const int command = read_int("Введите команду: ", 0, 7);

        switch (command) {
            case 1:
                run_task_names();
                break;
            case 2:
                run_task_person_with_name();
                break;
            case 3:
                run_task_person_with_parent();
                break;
            case 4:
                run_task_cities();
                break;
            case 5:
                run_task_create_names();
                break;
            case 6:
                run_task_create_people();
                break;
            case 7:
                run_task_cat();
                break;
            case 0:
                std::cout << "Завершение программы\n";
                return 0;
            default:
                std::cout << "Неизвестная команда\n";
                break;
        }
    }
}