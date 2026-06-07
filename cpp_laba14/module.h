#ifndef LAB14_MODULE_H_
#define LAB14_MODULE_H_

#include <vector>
#include <string>
#include <set>
#include <map>

// логика первой задачи
class VectorManager {
public:
    explicit VectorManager(const std::vector<int>& v0); // конструктор V0
    void process_subsets(const std::vector<std::vector<int>>& subsets); // метод проверки
private:
    std::vector<int> v0_; // храним эталон
};

// логика второй задачи
class DictionaryManager {
public:
    explicit DictionaryManager(const std::vector<std::string>& words); // берем слова
    void calculate_lengths(); // считаем длины
private:
    std::vector<std::string> words_; // вектор строк
};

// логика третьей задачи
class GroupManager {
public:
    explicit GroupManager(const std::vector<int>& data); // берем числа
    void group_by_last_digit(); // группируем
private:
    std::vector<int> data_; // вектор интов
};

// функции для main
void run_stl5assoc2();
void run_stl5assoc17();
void run_stl5assoc21();

// сервисные функции
namespace input_utils {
    int read_int(const std::string& prompt); // читаем инт
    std::string read_word(const std::string& prompt); // читаем слово
    std::vector<int> load_vector(const std::string& name); // грузим вектор
    int choose_mode(); // меню ввода
}

#endif