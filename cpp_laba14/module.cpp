#include "module.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <limits>

namespace input_utils {
    // ввод с проверкой
    int read_int(const std::string& prompt) {
        int val;
        while (true) { // цикл до победного
            std::cout << prompt;
            if (std::cin >> val) return val; // если ок
            std::cout << "Ошибка: введите целое число.\n";
            std::cin.clear(); // сброс флагов
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // пропуск мусора
        }
    }

    // чтение строки
    std::string read_word(const std::string& prompt) {
        std::cout << prompt;
        std::string s;
        std::cin >> s; // берем слово
        return s;
    }

    // подменю ввода
    int choose_mode() {
        std::cout << "Выберите способ ввода:\n1) Клавиатура\n2) Рандом\n3) Файл\n";
        return read_int("Режим: "); // вернуть выбор
    }

    // заполнение данных
    std::vector<int> load_vector(const std::string& name) {
        int mode = choose_mode(); // узнаем режим
        std::vector<int> res; // пустой вектор
        if (mode == 1) { // ввод руками
            int n = read_int("Размер вектора " + name + ": ");
            for(int i = 0; i < n; ++i) res.push_back(read_int("Элемент [" + std::to_string(i) + "]: "));
        } else if (mode == 2) { // рандом
            int n = read_int("Размер для рандома: ");
            for(int i = 0; i < n; ++i) res.push_back(rand() % 100); // до 100
        } else { // файл
            std::string path = read_word("Путь к файлу: ");
            std::ifstream in(path); // поток файла
            int n, val;
            if (in >> n) { // читаем размер
                for(int i = 0; i < n; ++i) { in >> val; res.push_back(val); }
            } else {
                std::cout << "Файл не найден или пуст.\n";
            }
        }
        std::cout << "Создан вектор " << name << ": ";
        for(int x : res) std::cout << x << " "; // печатаем итог
        std::cout << "\n";
        return res; // вернуть результат
    }
}

// --- Задача 2 ---
VectorManager::VectorManager(const std::vector<int>& v0) : v0_(v0) {} // сохраняем V0

void VectorManager::process_subsets(const std::vector<std::vector<int>>& subsets) {
    std::set<int> s0(v0_.begin(), v0_.end()); // V0 в сет
    std::cout << "Шаг 1: Создано множество уникальных элементов из V0.\n";

    int total_found = 0; // счетчик совпадений
    for (size_t i = 0; i < subsets.size(); ++i) { // идем по Vi
        std::cout << "Анализ V" << i+1 << "... ";
        std::set<int> si(subsets[i].begin(), subsets[i].end()); // Vi в сет

        // алгоритм поиска включения
        if (std::includes(si.begin(), si.end(), s0.begin(), s0.end())) {
            std::cout << "[ВКЛЮЧАЕТ V0]\n";
            total_found++; // плюс один
        } else {
            std::cout << "[НЕ ВКЛЮЧАЕТ]\n";
        }
    }
    std::cout << "Итог: количество подходящих векторов = " << total_found << "\n";
}

// --- Задача 17 ---
DictionaryManager::DictionaryManager(const std::vector<std::string>& words) : words_(words) {} // берем слова

void DictionaryManager::calculate_lengths() {
    std::map<char, int> m; // мапа буква-длина
    std::cout << "Действие: Перебор слов и накопление длин в M.\n";

    // цикл через итератор
    for (std::vector<std::string>::iterator it = words_.begin(); it != words_.end(); ++it) {
        char first_letter = (*it)[0]; // берем букву
        int len = static_cast<int>(it->size()); // берем длину
        m[first_letter] += len; // суммируем в мапу
        std::cout << " Обработано слово: " << *it << " (Буква: " << first_letter << ", Длина: " << len << ")\n";
    }

    std::cout << "Состояние отображения M (Буква -> Сумма длин):\n";
    for (std::map<char, int>::iterator it = m.begin(); it != m.end(); ++it) { // вывод мапы
        std::cout << it->first << it->second << " "; // ключ и сумма
    }
    std::cout << "\n";
}

// --- Задача 21 ---
GroupManager::GroupManager(const std::vector<int>& data) : data_(data) {} // берем инты

void GroupManager::group_by_last_digit() {
    std::multimap<int, int> m; // мультимапа цифра-число
    std::cout << "Действие: Распределение элементов по ключам (последняя цифра).\n";

    // цикл итератором
    for (std::vector<int>::iterator it = data_.begin(); it != data_.end(); ++it) {
        int key = std::abs(*it) % 10; // последняя цифра
        m.insert(std::make_pair(key, *it)); // вставка пары
        std::cout << " Число " << *it << " отправлено в группу ключа " << key << "\n";
    }

    std::cout << "Итоговое мультиотображение M:\n";
    for (std::multimap<int, int>::iterator it = m.begin(); it != m.end(); ++it) { // вывод результата
        std::cout << "Ключ [" << it->first << "]: " << it->second << "\n"; // ключ и значение
    }
}

// запуск второй задачи
void run_stl5assoc2() {
    std::vector<int> v0 = input_utils::load_vector("V0"); // грузим V0
    int n = input_utils::read_int("Введите количество векторов Vi для проверки (N): ");
    std::vector<std::vector<int>> subsets; // вектор векторов
    for(int i = 0; i < n; ++i) { // цикл загрузки Vi
        subsets.push_back(input_utils::load_vector("V" + std::to_string(i+1)));
    }
    VectorManager vm(v0); // создаем менеджер
    vm.process_subsets(subsets); // решаем
}

// запуск семнадцатой задачи
void run_stl5assoc17() {
    int n = input_utils::read_int("Сколько слов ввести? ");
    std::vector<std::string> words; // вектор строк
    for(int i = 0; i < n; ++i) { // цикл ввода
        words.push_back(input_utils::read_word("Слово " + std::to_string(i+1) + ": "));
    }
    std::cout << "Исходный вектор слов сформирован.\n";
    DictionaryManager dm(words); // создаем менеджер
    dm.calculate_lengths(); // решаем
}

// запуск двадцать первой задачи
void run_stl5assoc21() {
    std::vector<int> v = input_utils::load_vector("V"); // грузим вектор
    GroupManager gm(v); // создаем менеджер
    gm.group_by_last_digit(); // решаем
}