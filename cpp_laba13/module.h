#ifndef LAB13_MODULE_H_
#define LAB13_MODULE_H_

#include <deque>
#include <list>
#include <string>
#include <vector>

// обертка для списка
class CustomList {
public:
    CustomList();
    explicit CustomList(const std::list<int>& values);

    void solve_alg4();
    void solve_alg60();
    void print() const;

private:
    std::list<int> data_;
};

// обертка для дека
class CustomDeque {
public:
    CustomDeque();
    explicit CustomDeque(const std::deque<int>& values);

    void solve_alg18(int n);
    void print() const;

private:
    std::deque<int> data_;
};

// обертка для вектора
class CustomVector {
public:
    CustomVector();
    explicit CustomVector(const std::vector<int>& values);

    void prepare_thirds();
    void solve_alg48();
    void print() const;

private:
    std::vector<int> data_;
};

// запуск задач
void run_stl3alg4();
void run_stl3alg18();
void run_stl3alg48();
void run_stl3alg60();

namespace module_internal {

    // ввод int
    int read_int_value(const std::string& prompt);

    // ввод double
    double read_double_value(const std::string& prompt);

    // ввод строки
    std::string read_text_value(const std::string& prompt);

    // выбор способа ввода
    int choose_input_mode();

    // чтение int с клавиатуры
    std::vector<int> read_int_numbers_keyboard(int count);

    // генерация int
    std::vector<int> generate_random_int_numbers(int count);

    // чтение int из файла
    std::vector<int> read_int_numbers_file(const std::string& file_name);

    // общая загрузка int
    std::vector<int> load_int_numbers(bool (*is_valid)(int),
                                      const std::string& rule_text);

    // проверки количества
    bool is_positive(int count);
    bool is_divisible_by_three(int count);
    bool is_at_least_two(int count);

    // печать контейнеров
    void print_vector(const std::vector<int>& values);
    void print_list(const std::list<int>& values);
    void print_deque(const std::deque<int>& values);
    void print_double_vector(const std::vector<double>& values);

}  // namespace module_internal

#endif  // LAB13_MODULE_H_