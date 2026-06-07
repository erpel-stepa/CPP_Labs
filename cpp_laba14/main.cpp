#include <iostream>
#include <limits>
#include "module.h"

int main() {
    while (true) { // бесконечный цикл
        std::cout << "\nМЕНЮ LAB14 (Ассоциативные контейнеры)\n";
        std::cout << "1) STL5Assoc2 (Вектор V0 в наборе Vi)\n";
        std::cout << "2) STL5Assoc17 (Статистика длин слов)\n";
        std::cout << "3) STL5Assoc21 (Группировка по последней цифре)\n";
        std::cout << "0) Выход\n";
        std::cout << "Выберите пункт: ";

        int choice = -1; // переменная выбора
        if (!(std::cin >> choice)) { // если не число
            std::cout << "Ошибка ввода. Введите число.\n";
            std::cin.clear(); // сброс ошибки
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // чистка буфера
            continue; // на начало
        }

        try {
            switch (choice) { // ветвление меню
                case 1: run_stl5assoc2(); break; // первая задача
                case 2: run_stl5assoc17(); break; // вторая задача
                case 3: run_stl5assoc21(); break; // третья задача
                case 0:
                    std::cout << "Программа завершена.\n";
                    return 0; // выход
                default:
                    std::cout << "Такого пункта нет в меню.\n";
                    break;
            }
        } catch (const std::exception& error) { // ловим ошибки
            std::cout << "Ошибка: " << error.what() << '\n';
        }
    }
}