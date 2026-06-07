#include <iostream>
#include "tasks.h"

int main() {
    setlocale(LC_ALL, "ru");

    int choice = -1;

    while (choice != 0) {
        std::cout << "Лабораторная работа №6" << std::endl;
        std::cout << "1 - Минимальная продолжительность занятий клиентов" << std::endl;
        std::cout << "2 - Геометрические фигуры и работа с файлом" << std::endl;
        std::cout << "3 - Точки на плоскости и площадь многоугольника" << std::endl;
        std::cout << "0 - Выход" << std::endl;
        std::cout << "Введите номер задания: ";

        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Ошибка. Ожидалось целое число." << std::endl << std::endl;
            continue;
        }

        switch (choice) {
            case 1:
                task1();
                break;
            case 2:
                task2();
                break;
            case 3:
                task3();
                break;
            case 0:
                std::cout << "Завершение программы." << std::endl;
                break;
            default:
                std::cout << "Такого задания нет." << std::endl;
        }

        std::cout << std::endl;
    }

    return 0;
}