#include <iostream>
#include "module.h"

int main() {
    int choice;

    do {
        std::cout << "\nМеню\n";
        std::cout << "1) Код Хемминга\n";
        std::cout << "2) Код Хаффмана\n";
        std::cout << "3) Шифр Цезаря\n";
        std::cout << "0) Выход\n";
        std::cout << "Ваш выбор: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                runHammingTask();
                break;
            case 2:
                runHuffmanTask();
                break;
            case 3:
                runCaesarTask();
                break;
            case 0:
                std::cout << "Работа завершена.\n";
                break;
            default:
                std::cout << "Такого пункта нет.\n";
                break;
        }
    } while (choice != 0);

    return 0;
}
