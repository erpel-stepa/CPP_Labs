#ifndef STRUCTURES_H_
#define STRUCTURES_H_

#include <cstddef>   // size_t
#include <vector>    // vector<int>

// Стек на узлах
class Stack {
 private:
  // Узел стека
  struct TNode {
    int Data;        // значение узла
    TNode* Next;     // ссылка вниз

    // создаем узел
    TNode(int value, TNode* next = nullptr) : Data(value), Next(next) {} // быстрый init
  };

  TNode* top_; // вершина стека

  void copy_from(const Stack& other); // копируем узлы
  void clear();                       // чистим память

 public:
  Stack(); // пустой стек
  Stack(const Stack& other); // копия стека
  Stack& operator=(const Stack& other); // присваиваем копию
  ~Stack(); // освобождаем узлы

  void push(int value); // кладем наверх
  bool pop(int& removed_value); // снимаем сверху
  bool contains(int value) const; // ищем значение
  bool is_empty() const; // проверка пустоты
  const void* top_address() const; // адрес вершины

  std::vector<int> to_vector() const; // для вывода
};

// Очередь на узлах
class Queue {
 private:
  // Узел очереди
  struct TNode {
    int Data;       // значение узла
    TNode* Next;    // ссылка дальше

    explicit TNode(int value) : Data(value), Next(nullptr) {} // узел с null
  };

  TNode* head_; // начало очереди
  TNode* tail_; // конец очереди

  void copy_from(const Queue& other); // копируем узлы
  void clear();                       // чистим память

 public:
  Queue(); // пустая очередь
  Queue(const Queue& other); // копия очереди
  Queue& operator=(const Queue& other); // присваиваем копию
  ~Queue(); // освобождаем узлы

  void enqueue(int value); // добавить в хвост
  bool dequeue(int& removed_value); // удалить из головы
  bool contains(int value) const; // поиск значения
  bool is_empty() const; // проверка пустоты
  bool front(int& value) const; // посмотреть голову

  void move_first_n_to(Queue& other, int n); // перенос узлов

  const void* head_address() const; // адрес головы
  const void* tail_address() const; // адрес хвоста

  std::vector<int> to_vector() const; // для вывода
};

// Односвязный список
class LinkedList {
 private:
  // Узел списка
  struct Node {
    int value;      // значение узла
    Node* next;     // ссылка дальше

    explicit Node(int value_arg) : value(value_arg), next(nullptr) {} // init узла
  };

  Node* head_; // голова списка
  Node* tail_; // хвост списка

  void copy_from(const LinkedList& other); // копируем узлы
  void clear(); // чистим память

 public:
  LinkedList(); // пустой список
  LinkedList(const LinkedList& other); // копия списка
  LinkedList& operator=(const LinkedList& other); // присваиваем копию
  ~LinkedList(); // освобождаем узлы

  void push_back(int value); // добавить в конец
  bool remove_first(int value); // удалить первое
  bool contains(int value) const; // поиск значения
  bool is_empty() const; // проверка пустоты

  const void* fourth_address() const; // адрес 4-го
  void insert_after_every_fourth(int value); // вставка после 4-го
  void insert_sorted(int value); // вставка по месту

  const void* head_address() const; // адрес головы
  const void* tail_address() const; // адрес хвоста

  std::vector<int> to_vector() const; // для вывода
};

Stack build_stack_from_numbers(const std::vector<int>& numbers); // собрать стек

void run_task_dynamic5(); // решить Dynamic5
void run_task_dynamic22(); // решить Dynamic22
void run_task_list_work3(); // решить ListWork3
void run_task_list_work24(); // решить ListWork24
void run_task_list_work61(); // решить ListWork61
void run_demo_operations(); // показать операции

#endif  // STRUCTURES_H_