#include "structures.h"

#include <algorithm>  // swap
#include <fstream>    // ifstream
#include <iostream>   // cout/cin
#include <limits>     // numeric_limits
#include <random>     // rng
#include <string>     // string
#include <vector>     // vector

// ===== Stack =====

Stack::Stack() : top_(nullptr) {} // init пусто

Stack::Stack(const Stack& other) : top_(nullptr) { // init пусто
  copy_from(other); // копируем данные
}

Stack& Stack::operator=(const Stack& other) { // оператор =
  if (this != &other) { // защита self
    clear();            // чистим старое
    copy_from(other);   // копируем новое
  }
  return *this; // вернуть себя
}

Stack::~Stack() { // деструктор
  clear(); // удалить узлы
}

void Stack::copy_from(const Stack& other) { // копия стека
  std::vector<int> values; // временный буфер
  for (TNode* cur = other.top_; cur != nullptr; cur = cur->Next) { // идем по узлам
    values.push_back(cur->Data); // сохраняем значения
  }

  for (std::size_t i = values.size(); i > 0; --i) { // обратный порядок
    push(values[i - 1]); // восстановить стек
  }
}

void Stack::clear() { // чистка памяти
  while (top_ != nullptr) { // пока есть узлы
    TNode* to_delete = top_; // запомнить узел
    top_ = top_->Next;       // сдвиг вершины
    delete to_delete;        // освободить узел
  }
}

void Stack::push(int value) { // положить элемент
  top_ = new TNode(value, top_); // новый узел сверху
}

bool Stack::pop(int& removed_value) { // снять элемент
  if (top_ == nullptr) { // пустой стек
    return false; // нечего снимать
  }
  TNode* to_delete = top_; // узел удаляем
  removed_value = to_delete->Data; // сохранить D
  top_ = top_->Next; // сдвиг вершины
  delete to_delete; // освободить память
  return true; // успех
}

bool Stack::contains(int value) const { // поиск значения
  for (TNode* cur = top_; cur != nullptr; cur = cur->Next) { // идем сверху
    if (cur->Data == value) { // нашли совпадение
      return true; // есть в стеке
    }
  }
  return false; // не нашли
}

bool Stack::is_empty() const { // проверка пустоты
  return top_ == nullptr; // нет вершины
}

const void* Stack::top_address() const { // адрес вершины
  return static_cast<const void*>(top_); // вернуть указатель
}

std::vector<int> Stack::to_vector() const { // для вывода
  std::vector<int> out; // список значений
  for (TNode* cur = top_; cur != nullptr; cur = cur->Next) { // по стеку
    out.push_back(cur->Data); // собрать данные
  }
  return out; // вернуть вектор
}

// ===== Queue =====

Queue::Queue() : head_(nullptr), tail_(nullptr) {} // init пусто

Queue::Queue(const Queue& other) : head_(nullptr), tail_(nullptr) { // init пусто
  copy_from(other); // копируем данные
}

Queue& Queue::operator=(const Queue& other) { // оператор =
  if (this != &other) { // защита self
    clear();            // чистим старое
    copy_from(other);   // копируем новое
  }
  return *this; // вернуть себя
}

Queue::~Queue() { // деструктор
  clear(); // удалить узлы
}

void Queue::copy_from(const Queue& other) { // копия очереди
  for (TNode* cur = other.head_; cur != nullptr; cur = cur->Next) { // по всем узлам
    enqueue(cur->Data); // добавить в хвост
  }
}

void Queue::clear() { // чистка памяти
  while (head_ != nullptr) { // пока не пусто
    TNode* to_delete = head_; // запомнить узел
    head_ = head_->Next; // сдвиг головы
    delete to_delete; // освободить узел
  }
  tail_ = nullptr; // хвост тоже пуст
}

void Queue::enqueue(int value) { // добавить элемент
  TNode* node = new TNode(value); // новый узел
  if (tail_ == nullptr) { // очередь пустая
    head_ = tail_ = node; // оба на node
  } else {
    tail_->Next = node; // пришить в конец
    tail_ = node; // обновить хвост
  }
}

bool Queue::dequeue(int& removed_value) { // убрать элемент
  if (head_ == nullptr) { // пустая очередь
    return false; // нечего удалять
  }
  TNode* to_delete = head_; // узел удаляем
  removed_value = to_delete->Data; // сохранить значение
  head_ = head_->Next; // сдвиг головы
  if (head_ == nullptr) { // стало пусто
    tail_ = nullptr; // хвост обнулить
  }
  delete to_delete; // освободить узел
  return true; // успех
}

bool Queue::contains(int value) const { // поиск значения
  for (TNode* cur = head_; cur != nullptr; cur = cur->Next) { // по очереди
    if (cur->Data == value) { // нашли
      return true; // есть
    }
  }
  return false; // нет
}

bool Queue::is_empty() const { // проверка пустоты
  return head_ == nullptr; // нет головы
}

bool Queue::front(int& value) const { // посмотреть голову
  if (head_ == nullptr) { // пустая очередь
    return false; // нет элемента
  }
  value = head_->Data; // вернуть значение
  return true; // успех
}

void Queue::move_first_n_to(Queue& other, int n) { // перенос узлов
  if (n <= 0 || head_ == nullptr) { // нечего переносить
    return; // выход
  }

  TNode* first_moved = head_; // первая переносимая
  TNode* last_moved = head_; // последняя переносимая
  int moved_count = 1; // счетчик

  while (last_moved->Next != nullptr && moved_count < n) { // ищем границу
    last_moved = last_moved->Next; // двигаем конец
    ++moved_count; // увеличиваем счетчик
  }

  TNode* new_head = last_moved->Next; // новая голова 1й
  last_moved->Next = nullptr; // отрезали кусок

  head_ = new_head; // обновили голову
  if (head_ == nullptr) { // первая стала пустой
    tail_ = nullptr; // хвост тоже null
  }

  if (other.tail_ == nullptr) { // вторая пустая
    other.head_ = first_moved; // голова = кусок
    other.tail_ = last_moved; // хвост = конец куска
  } else {
    other.tail_->Next = first_moved; // пришили к хвосту
    other.tail_ = last_moved; // обновили хвост
  }
}

const void* Queue::head_address() const { // адрес головы
  return static_cast<const void*>(head_); // вернуть указатель
}

const void* Queue::tail_address() const { // адрес хвоста
  return static_cast<const void*>(tail_); // вернуть указатель
}

std::vector<int> Queue::to_vector() const { // для вывода
  std::vector<int> out; // список значений
  for (TNode* cur = head_; cur != nullptr; cur = cur->Next) { // по очереди
    out.push_back(cur->Data); // собрать данные
  }
  return out; // вернуть вектор
}

// ===== LinkedList =====

LinkedList::LinkedList() : head_(nullptr), tail_(nullptr) {} // init пусто

LinkedList::LinkedList(const LinkedList& other) : head_(nullptr), tail_(nullptr) { // init пусто
  copy_from(other); // копируем данные
}

LinkedList& LinkedList::operator=(const LinkedList& other) { // оператор =
  if (this != &other) { // защита self
    clear(); // чистим старое
    copy_from(other); // копируем новое
  }
  return *this; // вернуть себя
}

LinkedList::~LinkedList() { // деструктор
  clear(); // удалить узлы
}

void LinkedList::copy_from(const LinkedList& other) { // копия списка
  for (Node* cur = other.head_; cur != nullptr; cur = cur->next) { // по узлам
    push_back(cur->value); // добавить в конец
  }
}

void LinkedList::clear() { // чистка памяти
  while (head_ != nullptr) { // пока есть узлы
    Node* to_delete = head_; // запомнить узел
    head_ = head_->next; // сдвиг головы
    delete to_delete; // удалить узел
  }
  tail_ = nullptr; // хвост null
}

void LinkedList::push_back(int value) { // добавить элемент
  Node* node = new Node(value); // новый узел
  if (tail_ == nullptr) { // список пустой
    head_ = tail_ = node; // первый элемент
  } else {
    tail_->next = node; // пришить в конец
    tail_ = node; // обновить хвост
  }
}

bool LinkedList::remove_first(int value) { // удалить первое
  Node* prev = nullptr; // предыдущий узел
  Node* cur = head_; // текущий узел

  while (cur != nullptr) { // пока не конец
    if (cur->value == value) { // нашли нужный
      if (prev == nullptr) { // удаляем голову
        head_ = cur->next; // новая голова
      } else {
        prev->next = cur->next; // пропуск узла
      }

      if (cur == tail_) { // если хвост
        tail_ = prev; // обновить хвост
      }

      delete cur; // удалить узел
      return true; // успешно
    }
    prev = cur; // сдвиг prev
    cur = cur->next; // сдвиг cur
  }
  return false; // не нашли
}

bool LinkedList::contains(int value) const { // поиск значения
  for (Node* cur = head_; cur != nullptr; cur = cur->next) { // по узлам
    if (cur->value == value) { // нашли
      return true; // есть
    }
  }
  return false; // нет
}

bool LinkedList::is_empty() const { // проверка пустоты
  return head_ == nullptr; // нет головы
}

const void* LinkedList::fourth_address() const { // адрес 4-го
  Node* cur = head_; // старт с головы
  for (int i = 0; i < 3 && cur != nullptr; ++i) { // 3 шага вперед
    cur = cur->next; // перейти дальше
  }
  return static_cast<const void*>(cur); // вернуть адрес
}

void LinkedList::insert_after_every_fourth(int value) { // вставка M
  Node* cur = head_; // текущий узел
  int index = 0; // счетчик позиций

  while (cur != nullptr) { // идем по списку
    ++index; // увеличиваем позицию
    if (index % 4 == 0) { // каждый 4-й
      Node* inserted = new Node(value); // новый узел M
      inserted->next = cur->next; // связать с хвостом
      cur->next = inserted; // вставить после cur
      if (tail_ == cur) { // если вставка в конце
        tail_ = inserted; // обновить хвост
      }
      cur = inserted->next; // прыгнуть дальше
    } else {
      cur = cur->next; // обычный шаг
    }
  }
}

void LinkedList::insert_sorted(int value) { // вставка по возрастанию
  Node* node = new Node(value); // новый узел
  if (head_ == nullptr || value <= head_->value) { // вставка в начало
    node->next = head_; // новый указывает на старую
    head_ = node; // новая голова
    if (tail_ == nullptr) { // был пустой список
      tail_ = node; // хвост тоже node
    }
    return; // закончили
  }

  Node* cur = head_; // старт с головы
  while (cur->next != nullptr && cur->next->value < value) { // ищем место
    cur = cur->next; // сдвиг вперед
  }

  node->next = cur->next; // вставка между
  cur->next = node; // пришить узел
  if (node->next == nullptr) { // вставили в конец
    tail_ = node; // обновили хвост
  }
}

const void* LinkedList::head_address() const { // адрес головы
  return static_cast<const void*>(head_); // вернуть указатель
}

const void* LinkedList::tail_address() const { // адрес хвоста
  return static_cast<const void*>(tail_); // вернуть указатель
}

std::vector<int> LinkedList::to_vector() const { // для вывода
  std::vector<int> out; // список значений
  for (Node* cur = head_; cur != nullptr; cur = cur->next) { // по списку
    out.push_back(cur->value); // собрать данные
  }
  return out; // вернуть вектор
}

// ===== helpers / tasks =====

Stack build_stack_from_numbers(const std::vector<int>& numbers) { // собрать стек
  Stack stack; // новый стек
  for (int value : numbers) { // по всем числам
    stack.push(value); // пушим в стек
  }
  return stack; // вернуть стек
}

namespace {

// режим ввода
enum class InputMode {
  kKeyboard = 1, // ввод руками
  kFile = 2, // ввод из файла
  kRandom = 3, // ввод рандом
};

void print_ptr_or_null(const void* ptr) { // печать адреса
  if (ptr == nullptr) { // если null
    std::cout << "nullptr"; // вывести null
  } else {
    std::cout << ptr; // вывести адрес
  }
}

void print_values(const std::vector<int>& v) { // печать значений
  std::cout << "{";
  for (std::size_t i = 0; i < v.size(); ++i) {
    std::cout << v[i];
    if (i + 1 != v.size()) {
      std::cout << " ";
    }
  }
  std::cout << "}";
}

bool read_int(const std::string& prompt, int& value) { // ввод int
  std::cout << prompt; // печать запроса
  std::cin >> value; // чтение значения
  if (std::cin) { // если ок
    return true; // успех
  }

  std::cin.clear(); // сброс флагов
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // чистим строку
  return false; // провал
}

InputMode read_input_mode(const std::string& label) { // выбор режима
  while (true) { // пока не выбрали
    std::cout << "\nВыбор ввода для " << label << "\n";
    std::cout << "1) С клавиатуры\n";
    std::cout << "2) Из файла\n";
    std::cout << "3) Рандомно (диапазон)\n";
    int choice = 0;
    if (!read_int("Введите (1/2/3): ", choice)) { // читаем выбор
      std::cout << "Некорректный ввод\n";
      continue; // повтор
    }

    if (choice == static_cast<int>(InputMode::kKeyboard)) { // вариант 1
      return InputMode::kKeyboard; // вернуть режим
    }
    if (choice == static_cast<int>(InputMode::kFile)) { // вариант 2
      return InputMode::kFile; // вернуть режим
    }
    if (choice == static_cast<int>(InputMode::kRandom)) { // вариант 3
      return InputMode::kRandom; // вернуть режим
    }
    std::cout << "Такого варианта нет\n";
  }
}

bool read_count_and_values_keyboard(const std::string& label, int min_count,
                                   std::vector<int>& values) { // ввод массива
  int count = 0;
  if (!read_int("Количество элементов для " + label + ": ", count) ||
      count < min_count) { // проверка min
    std::cout << "Некорректное количество\n";
    return false; // ошибка
  }

  values.assign(count, 0); // выделить размер
  std::cout << "Введите " << count << " чисел: ";
  for (int i = 0; i < count; ++i) { // читаем числа
    std::cin >> values[i]; // чтение элемента
    if (!std::cin) { // ошибка ввода
      std::cout << "Некорректный ввод числа\n";
      return false; // провал
    }
  }
  return true; // успех
}

bool read_count_and_values_file(const std::string& label, int min_count,
                               std::vector<int>& values) { // чтение из файла
  std::cout << "Путь к файлу для " << label << ": ";
  std::string path;
  std::cin >> path; // путь к файлу

  std::ifstream input(path); // открыть файл
  if (!input.is_open()) { // если не открылся
    std::cout << "Файл не открылся\n";
    return false; // ошибка
  }

  int count = 0;
  input >> count; // читаем N
  if (!input || count < min_count) { // проверка N
    std::cout << "Некорректное количество в файле\n";
    return false; // ошибка
  }

  values.assign(count, 0); // подготовка массива
  for (int i = 0; i < count; ++i) { // читаем числа
    input >> values[i]; // чтение ai
    if (!input) { // не хватило данных
      std::cout << "В файле недостаточно чисел\n";
      return false; // ошибка
    }
  }
  return true; // успех
}

bool read_count_and_values_random(const std::string& label, int min_count,
                                 std::vector<int>& values) { // рандом массив
  int count = 0;
  if (!read_int("Количество элементов для " + label + ": ", count) ||
      count < min_count) { // проверка min
    std::cout << "Некорректное количество\n";
    return false; // ошибка
  }

  int min_value = 0;
  int max_value = 0;
  if (!read_int("Минимум диапазона: ", min_value) ||
      !read_int("Максимум диапазона: ", max_value)) { // ввод границ
    std::cout << "Некорректный диапазон\n";
    return false; // ошибка
  }
  if (min_value > max_value) { // если перепутали
    std::swap(min_value, max_value); // поменять местами
  }

  std::mt19937 gen(std::random_device{}()); // генератор
  std::uniform_int_distribution<int> dist(min_value, max_value); // диапазон

  values.assign(count, 0); // подготовка массива
  for (int i = 0; i < count; ++i) { // генерим числа
    values[i] = dist(gen); // случайное число
  }

  std::cout << "Сгенерировано: ";
  for (int i = 0; i < count; ++i) { // печать массива
    std::cout << values[i] << (i + 1 == count ? '\n' : ' ');
  }
  return true; // успех
}

bool read_values_with_mode(const std::string& label, int min_count,
                          std::vector<int>& values) { // общий ввод массива
  InputMode mode = read_input_mode(label); // выбрать режим
  if (mode == InputMode::kKeyboard) { // клавиатура
    return read_count_and_values_keyboard(label, min_count, values); // ввод руками
  }
  if (mode == InputMode::kFile) { // файл
    return read_count_and_values_file(label, min_count, values); // ввод из файла
  }
  return read_count_and_values_random(label, min_count, values); // ввод рандом
}

bool read_single_int_with_mode(const std::string& label, int& value) { // общий ввод int
  InputMode mode = read_input_mode(label); // выбрать режим
  if (mode == InputMode::kKeyboard) { // клавиатура
    return read_int("Введите значение для " + label + ": ", value); // ввод значения
  }

  if (mode == InputMode::kFile) { // файл
    std::cout << "Путь к файлу для " << label << ": ";
    std::string path;
    std::cin >> path; // путь к файлу
    std::ifstream input(path); // открыть файл
    if (!input.is_open()) { // не открылся
      std::cout << "Файл не открылся\n";
      return false; // ошибка
    }
    input >> value; // читаем число
    if (!input) { // не число
      std::cout << "В файле нет корректного числа\n";
      return false; // ошибка
    }
    return true; // успех
  }

  int min_value = 0;
  int max_value = 0;
  if (!read_int("Минимум диапазона: ", min_value) ||
      !read_int("Максимум диапазона: ", max_value)) { // ввод границ
    std::cout << "Некорректный диапазон\n";
    return false; // ошибка
  }
  if (min_value > max_value) { // если перепутали
    std::swap(min_value, max_value); // поменять местами
  }

  std::mt19937 gen(std::random_device{}()); // генератор
  std::uniform_int_distribution<int> dist(min_value, max_value); // диапазон
  value = dist(gen); // случайное значение
  std::cout << "Сгенерировано значение: " << value << '\n';
  return true; // успех
}

} // namespace

void run_task_dynamic5() { // задача Dynamic5
  std::cout << "\n(Dynamic5)\n";

  std::vector<int> values;
  if (!read_values_with_mode("стека", 1, values)) { // ввод стека
    std::cout << "Не удалось получить входные данные\n";
    return; // выход
  }

  Stack stack = build_stack_from_numbers(values); // собрать стек

  const void* p1 = stack.top_address(); // адрес P1
  std::cout << "P1 (вершина стека): ";
  print_ptr_or_null(p1); // печать адреса
  std::cout << '\n';

  int d = 0;
  stack.pop(d); // снять вершину

  std::cout << "D (снятый элемент): " << d << '\n';
  std::cout << "P2 (новая вершина): ";
  print_ptr_or_null(stack.top_address()); // адрес P2
  std::cout << '\n';
}

void run_task_dynamic22() { // задача Dynamic22
  std::cout << "\n(Dynamic22)\n";

  int n = 0;
  if (!read_single_int_with_mode("N", n) || n <= 0) { // ввод N
    std::cout << "Некорректное N\n";
    return; // выход
  }

  std::vector<int> first_values;
  if (!read_values_with_mode("первой очереди", 1, first_values)) { // ввод Q1
    std::cout << "Не удалось получить первую очередь\n";
    return; // выход
  }

  std::vector<int> second_values;
  if (!read_values_with_mode("второй очереди", 1, second_values)) { // ввод Q2
    std::cout << "Не удалось получить вторую очередь\n";
    return; // выход
  }

  Queue queue1;
  Queue queue2;
  for (int value : first_values) { // заполнить Q1
    queue1.enqueue(value); // enqueue
  }
  for (int value : second_values) { // заполнить Q2
    queue2.enqueue(value); // enqueue
  }

  std::cout << "До переноса узлов\n";
  std::cout << "  Первая очередь: ";
  print_values(queue1.to_vector());
  std::cout << '\n';
  std::cout << "  Вторая очередь: ";
  print_values(queue2.to_vector());
  std::cout << '\n';

  std::cout << "Переносим N первых из первой в конец второй (без new/delete)\n";
  queue1.move_first_n_to(queue2, n); // перенос без new/delete

  std::cout << "После переноса узлов\n";
  std::cout << "  Первая очередь: ";
  print_values(queue1.to_vector());
  std::cout << '\n';
  std::cout << "  Вторая очередь: ";
  print_values(queue2.to_vector());
  std::cout << '\n';

  std::cout << "Адреса первой очереди (P1, P2): ";
  print_ptr_or_null(queue1.head_address()); // P1
  std::cout << ' ';
  print_ptr_or_null(queue1.tail_address()); // P2
  std::cout << '\n';

  std::cout << "Адреса второй очереди (P3, P4): ";
  print_ptr_or_null(queue2.head_address()); // P3
  std::cout << ' ';
  print_ptr_or_null(queue2.tail_address()); // P4
  std::cout << '\n';
}

void run_task_list_work3() { // задача ListWork3
  std::cout << "\n(ListWork3)\n";

  std::vector<int> values;
  if (!read_values_with_mode("односвязного списка", 5, values)) { // минимум 5
    std::cout << "Не удалось получить список\n";
    return; // выход
  }

  LinkedList list;
  for (int value : values) { // заполнить список
    list.push_back(value); // push_back
  }

  std::cout << "Указатель P4 (4-й элемент): ";
  print_ptr_or_null(list.fourth_address()); // адрес 4-го
  std::cout << '\n';
}

void run_task_list_work24() { // задача ListWork24
  std::cout << "\n(ListWork24)\n";

  std::vector<int> values;
  if (!read_values_with_mode("односвязного списка", 1, values)) { // ввод списка
    std::cout << "Не удалось получить список\n";
    return; // выход
  }

  int m = 0;
  if (!read_single_int_with_mode("M", m)) { // ввод M
    std::cout << "Не удалось получить значение M\n";
    return; // выход
  }

  LinkedList list;
  for (int value : values) { // заполнить список
    list.push_back(value); // push_back
  }

  std::cout << "Исходный список: ";
  print_values(list.to_vector());
  std::cout << '\n';

  std::cout << "Вставляем M после каждого 4-го элемента\n";
  list.insert_after_every_fourth(m); // вставки после 4-х

  std::cout << "Список после вставок: ";
  print_values(list.to_vector());
  std::cout << '\n';

  std::cout << "Указатель P2 (последний элемент): ";
  print_ptr_or_null(list.tail_address()); // адрес хвоста
  std::cout << '\n';
}

void run_task_list_work61() { // задача ListWork61
  std::cout << "\n(ListWork61)\n";

  std::vector<int> values;
  if (!read_values_with_mode("данных для списка", 1, values)) { // ввод N чисел
    std::cout << "Не удалось получить входные данные\n";
    return; // выход
  }

  std::cout << "Входные числа: ";
  print_values(values);
  std::cout << '\n';

  std::cout << "Строим упорядоченный список вставками\n";
  LinkedList list;
  for (int value : values) { // вставка по одному
    list.insert_sorted(value); // поддержать порядок
  }

  std::cout << "Итоговый список: ";
  print_values(list.to_vector());
  std::cout << '\n';

  std::cout << "P1 (голова списка): ";
  print_ptr_or_null(list.head_address()); // адрес головы
  std::cout << '\n';
}

void run_demo_operations() { // демонстрация операций
  std::cout << "\n(Демонстрация операций)\n";

  Stack stack;
  std::cout << "\nStack\n";
  std::cout << "  Добавление: push(10), push(20)\n";
  stack.push(10); // добавить 10
  stack.push(20); // добавить 20
  int removed_value = 0;
  bool popped = stack.pop(removed_value); // удалить вершину
  std::cout << "  Удаление: pop() -> "
            << (popped ? std::to_string(removed_value) : std::string("empty"))
            << '\n';
  std::cout << "  Поиск: contains(10) -> "
            << (stack.contains(10) ? "true" : "false") << '\n';

  Queue queue;
  std::cout << "\nQueue\n";
  std::cout << "  Добавление: enqueue(1), enqueue(2)\n";
  queue.enqueue(1); // добавить 1
  queue.enqueue(2); // добавить 2
  bool dequeued = queue.dequeue(removed_value); // удалить голову
  std::cout << "  Удаление: dequeue() -> "
            << (dequeued ? std::to_string(removed_value) : std::string("empty"))
            << '\n';
  std::cout << "  Поиск: contains(2) -> "
            << (queue.contains(2) ? "true" : "false") << '\n';

  LinkedList list;
  std::cout << "\nList\n";
  std::cout << "  Добавление: push_back(5), push_back(7), push_back(9)\n";
  list.push_back(5); // добавить 5
  list.push_back(7); // добавить 7
  list.push_back(9); // добавить 9
  bool deleted = list.remove_first(7); // удалить 7
  std::cout << "  Удаление: remove_first(7) -> "
            << (deleted ? "true" : "false") << '\n';
  std::cout << "  Поиск: contains(9) -> "
            << (list.contains(9) ? "true" : "false") << '\n';
}