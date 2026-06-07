#include "module.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <numeric>
#include <random>
#include <stdexcept>

namespace module_internal {

constexpr int kInputKeyboard = 1;
constexpr int kInputRandom = 2;
constexpr int kInputFile = 3;

// читаем целое число
int read_int_value(const std::string& prompt) {
  while (true) {
    std::cout << prompt;
    int value = 0;
    if (std::cin >> value) {
      return value;
    }

    std::cout << "Нужно ввести целое число\n";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
}

// читаем вещественное число
double read_double_value(const std::string& prompt) {
  while (true) {
    std::cout << prompt;
    double value = 0;
    if (std::cin >> value) {
      return value;
    }

    std::cout << "Нужно ввести число\n";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
}

// читаем короткий текст
std::string read_text_value(const std::string& prompt) {
  std::cout << prompt;
  std::string value;
  std::cin >> value;

  if (!std::cin) {
    throw std::runtime_error("Не удалось прочитать текст");
  }

  return value;
}

// выбор способа ввода
int choose_input_mode() {
  std::cout << "1) С клавиатуры\n";
  std::cout << "2) Случайно\n";
  std::cout << "3) Из файла\n";

  while (true) {
    const int mode = read_int_value("Режим: ");
    if (mode >= 1 && mode <= 3) {
      return mode;
    }
    std::cout << "Доступны только 1, 2, 3\n";
  }
}

// читаем массив int
std::vector<int> read_int_numbers_keyboard(int count) {
  if (count <= 0) {
    throw std::invalid_argument("Количество должно быть положительным");
  }

  std::vector<int> values;
  values.reserve(count);

  std::cout << "Введите " << count << " целых чисел: ";
  for (int i = 0; i < count; ++i) {
    int value = 0;
    if (!(std::cin >> value)) {
      throw std::runtime_error("Не удалось прочитать числа");
    }
    values.push_back(value);
  }

  return values;
}

// генерируем массив int
std::vector<int> generate_random_int_numbers(int count) {
  if (count <= 0) {
    throw std::invalid_argument("Количество должно быть положительным");
  }

  const int min_value = read_int_value("Минимум: ");
  const int max_value = read_int_value("Максимум: ");
  if (min_value > max_value) {
    throw std::invalid_argument("Минимум должен быть <= максимуму");
  }

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(min_value, max_value);

  std::vector<int> values;
  values.reserve(count);

  for (int i = 0; i < count; ++i) {
    values.push_back(dist(gen));
  }

  return values;
}

// читаем int из файла
std::vector<int> read_int_numbers_file(const std::string& file_name) {
  std::ifstream input(file_name);
  if (!input.is_open()) {
    throw std::runtime_error("Не удалось открыть файл: " + file_name);
  }

  int count = 0;
  if (!(input >> count)) {
    throw std::runtime_error("Не удалось прочитать N из файла");
  }

  if (count <= 0) {
    throw std::invalid_argument("В файле некорректное N");
  }

  std::vector<int> values;
  values.reserve(count);

  for (int i = 0; i < count; ++i) {
    int value = 0;
    if (!(input >> value)) {
      throw std::runtime_error("В файле не хватает чисел");
    }
    values.push_back(value);
  }

  return values;
}

// общая загрузка int
std::vector<int> load_int_numbers(bool (*is_valid)(int),
                                  const std::string& rule_text) {
  const int mode = choose_input_mode();

  if (mode == kInputKeyboard) {
    while (true) {
      const int count = read_int_value("Количество: ");
      if (!is_valid(count)) {
        std::cout << "Неверное количество, " << rule_text << '\n';
        continue;
      }
      return read_int_numbers_keyboard(count);
    }
  }

  if (mode == kInputRandom) {
    while (true) {
      const int count = read_int_value("Количество: ");
      if (!is_valid(count)) {
        std::cout << "Неверное количество, " << rule_text << '\n';
        continue;
      }
      return generate_random_int_numbers(count);
    }
  }

  const std::string file_name = read_text_value("Имя файла: ");
  const std::vector<int> values = read_int_numbers_file(file_name);

  if (!is_valid(static_cast<int>(values.size()))) {
    throw std::invalid_argument("Неверное N в файле, " + rule_text);
  }

  return values;
}

// проверки
bool is_positive(int count) { return count > 0; }
bool is_divisible_by_three(int count) { return count > 0 && count % 3 == 0; }
bool is_at_least_two(int count) { return count >= 2; }

// печать
void print_vector(const std::vector<int>& values) {
  for (std::vector<int>::const_iterator it = values.begin(); it != values.end(); ++it)
    std::cout << *it << ' ';
  std::cout << '\n';
}

void print_list(const std::list<int>& values) {
  for (std::list<int>::const_iterator it = values.begin(); it != values.end(); ++it)
    std::cout << *it << ' ';
  std::cout << '\n';
}

void print_deque(const std::deque<int>& values) {
  for (std::deque<int>::const_iterator it = values.begin(); it != values.end(); ++it)
    std::cout << *it << ' ';
  std::cout << '\n';
}

void print_double_vector(const std::vector<double>& values) {
  for (std::vector<double>::const_iterator it = values.begin(); it != values.end(); ++it)
    std::cout << *it << ' ';
  std::cout << '\n';
}

}  // namespace module_internal

// реализация CustomList
CustomList::CustomList() {}
CustomList::CustomList(const std::list<int>& values) : data_(values) {}

void CustomList::print() const {
  module_internal::print_list(data_);
}

// предикат для поиска минуса
bool is_negative(int value) {
  return value < 0;
}

void CustomList::solve_alg4() {
  std::list<int>::iterator it1 = std::find_if(data_.begin(), data_.end(), is_negative);
  
  if (it1 != data_.end()) {
    std::list<int>::iterator start = it1;
    std::advance(start, 1);
    
    std::list<int>::iterator it2 = std::find_if(start, data_.end(), is_negative);
    data_.erase(start, it2);
  }
}

// функтор для среднего значения
struct MeanOp {
  double operator()(int curr, int prev) const {
    return (curr + prev) / 2.0;
  }
};

void CustomList::solve_alg60() {
  std::vector<double> result;
  MeanOp mean_op;
  
  std::adjacent_difference(data_.begin(), data_.end(), std::back_inserter(result), mean_op);
  
  // удаляем первый лишний элемент
  if (!result.empty()) {
    result.erase(result.begin());
  }
  
  std::cout << "Вектор после adjacent_difference:\n";
  module_internal::print_double_vector(result);
}

// реализация CustomDeque
CustomDeque::CustomDeque() {}
CustomDeque::CustomDeque(const std::deque<int>& values) : data_(values) {}

void CustomDeque::print() const {
  module_internal::print_deque(data_);
}

// генератор последовательности
struct SequenceGen {
  int current_;
  SequenceGen() : current_(1) {}
  int operator()() { return current_++; }
};

void CustomDeque::solve_alg18(int n) {
  if (data_.size() < static_cast<size_t>(2 * n)) {
    std::cout << "Недостаточно элементов в деке\n";
    return;
  }
  
  SequenceGen gen;
  
  // заполняем с начала
  std::generate(data_.begin(), data_.begin() + n, gen);
  // заполняем с конца через rbegin
  std::generate(data_.rbegin(), data_.rbegin() + n, gen);
}

// реализация CustomVector
CustomVector::CustomVector() {}
CustomVector::CustomVector(const std::vector<int>& values) : data_(values) {}

void CustomVector::print() const {
  module_internal::print_vector(data_);
}

void CustomVector::prepare_thirds() {
  const int third = static_cast<int>(data_.size()) / 3;
  std::sort(data_.begin(), data_.begin() + third);
  std::sort(data_.begin() + third, data_.begin() + 2 * third);
  std::sort(data_.begin() + 2 * third, data_.end());
}

// функтор для группировки согласно задаче STL3Alg42
struct GroupCompare {
  int get_category(int x) const {
    if (x < 0) return 0;   // отрицательные в начало
    if (x == 0) return 1;  // нули в середину
    return 2;              // положительные в конец
  }

  bool operator()(int a, int b) const {
    return get_category(a) < get_category(b);
  }
};

void CustomVector::solve_alg48() {
  const int third = static_cast<int>(data_.size()) / 3;
  GroupCompare comp; // наш функциональный объект для группировки

  std::vector<int>::iterator p1 = data_.begin();
  std::vector<int>::iterator p2 = data_.begin() + third;
  std::vector<int>::iterator p3 = data_.begin() + 2 * third;
  std::vector<int>::iterator p4 = data_.end();

  // сливаем первые две трети
  std::inplace_merge(p1, p2, p3, comp);
  // сливаем результат с последней третью
  std::inplace_merge(p1, p3, p4, comp);
}

// запуск задач
void run_stl3alg4() {
  std::cout << "\nSTL3Alg4\n";
  const std::vector<int> values = module_internal::load_int_numbers(
      module_internal::is_positive, "нужно количество > 0");

  CustomList custom_list(std::list<int>(values.begin(), values.end()));

  std::cout << "Список до:\n";
  custom_list.print();

  std::cout << "Удаляем элементы между отрицательными...\n";
  custom_list.solve_alg4();

  std::cout << "Список после:\n";
  custom_list.print();
}

void run_stl3alg18() {
  std::cout << "\nSTL3Alg18\n";
  const std::vector<int> values = module_internal::load_int_numbers(
      module_internal::is_at_least_two, "нужно минимум 2 элемента");

  int n = 0;
  while (true) {
    n = module_internal::read_int_value("Введите N: ");
    if (n > 0 && 2 * n <= static_cast<int>(values.size())) {
      break;
    }
    std::cout << "Ошибка: N должно быть > 0 и 2*N <= размеру дека\n";
  }

  CustomDeque custom_deque(std::deque<int>(values.begin(), values.end()));

  std::cout << "Дек до:\n";
  custom_deque.print();

  std::cout << "Генерируем последовательности...\n";
  custom_deque.solve_alg18(n);

  std::cout << "Дек после:\n";
  custom_deque.print();
}

void run_stl3alg48() {
  std::cout << "\nSTL3Alg48\n";
  const std::vector<int> values = module_internal::load_int_numbers(
      module_internal::is_divisible_by_three, "количество должно быть кратно 3");

  CustomVector custom_vector(values);

  std::cout << "Подготавливаем трети (моделируем отсортированность)...\n";
  custom_vector.prepare_thirds();
  std::cout << "Вектор до:\n";
  custom_vector.print();

  std::cout << "Сливаем трети по категориям (согласно STL3Alg42)...\n";
  custom_vector.solve_alg48();
  
  std::cout << "Вектор после:\n";
  custom_vector.print();
}

void run_stl3alg60() {
  std::cout << "\nSTL3Alg60\n";
  const std::vector<int> values = module_internal::load_int_numbers(
      module_internal::is_at_least_two, "нужно минимум 2 элемента");
  
  CustomList custom_list(std::list<int>(values.begin(), values.end()));
  
  std::cout << "Список до:\n";
  custom_list.print();
  
  std::cout << "Считаем среднее соседних элементов...\n";
  custom_list.solve_alg60();
}