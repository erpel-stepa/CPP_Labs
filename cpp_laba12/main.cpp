#include <iostream>
#include <fstream>
#include <map>
#include <string>

int main() {
    std::ifstream fin("input.txt");
    if (!fin) {
        std::cout << "Ошибка открытия файла\n";
        return 1;
    }

    std::multimap<std::string, std::string> employees;

    std::string department, surname;

    while (fin >> department >> surname) {
        employees.insert(std::make_pair(department, surname));
    }

    fin.close();

    // 1. Вывод всего списка
    std::cout << "Все сотрудники:\n";
    for (std::multimap<std::string, std::string>::iterator it = employees.begin(); it != employees.end(); ++it) {
        std::cout << it->first << " - " << it->second << "\n";
    }

    // 2. Поиск по отделу
    std::string target;
    std::cout << "\nВведите отдел: ";
    std::cin >> target;

    std::pair<
        std::multimap<std::string, std::string>::iterator,
        std::multimap<std::string, std::string>::iterator
    > range = employees.equal_range(target);

    std::cout << "Сотрудники отдела " << target << ":\n";

    if (range.first == range.second) {
        std::cout << "Нет сотрудников\n";
    } else {
        for (std::multimap<std::string, std::string>::iterator it = range.first; it != range.second; ++it) {
            std::cout << it->second << "\n";
        }
    }

    // 3. Подсчет количества сотрудников
    std::cout << "\nКоличество сотрудников по отделам:\n";

    std::string current_dep = "";
    int count = 0;

    for (std::multimap<std::string, std::string>::iterator it = employees.begin(); it != employees.end(); ++it) {
        if (it->first != current_dep) {
            if (current_dep != "") {
                std::cout << current_dep << ": " << count << "\n";
            }
            current_dep = it->first;
            count = 1;
        } else {
            ++count;
        }
    }

    if (current_dep != "") {
        std::cout << current_dep << ": " << count << "\n";
    }

    return 0;
}