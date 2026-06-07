#ifndef LAB15_MODULE_H_
#define LAB15_MODULE_H_

#include <string>

// класс узла
class TreeNode {
public:
    int data; // число
    TreeNode* left; // левый сын
    TreeNode* right; // правый сын

    explicit TreeNode(int value); // конструктор узла
};

// класс дерева поиска
class BinarySearchTree {
public:
    BinarySearchTree(); // пустое дерево
    BinarySearchTree(const BinarySearchTree& other); // копия
    BinarySearchTree& operator=(const BinarySearchTree& other); // присваивание
    ~BinarySearchTree(); // деструктор

    void insert(int value); // вставка
    void remove(int value); // удаление
    bool search(int value) const; // поиск
    bool is_empty() const; // проверка пустоты

    void build_from_array(const int* data, int size); // строим дерево
    void print_graphic() const; // боковой вывод
    void print_descending() const; // по убыванию
    void print_inorder() const; // инфиксный вывод
    void* get_root_address() const; // адрес корня

private:
    TreeNode* root_; // корень

    TreeNode* copy_tree(TreeNode* node) const; // копия ветки
    void clear_tree(TreeNode* node); // удаление ветки

    TreeNode* insert_node(TreeNode* node, int value); // вставка узла
    TreeNode* remove_node(TreeNode* node, int value); // удаление узла
    TreeNode* find_min(TreeNode* node) const; // минимум
    TreeNode* search_node(TreeNode* node, int value) const; // поиск узла

    void print_graphic_node(TreeNode* node, int level) const; // печать ветки
    void print_descending_node(TreeNode* node) const; // обратный обход
    void print_inorder_node(TreeNode* node) const; // инфиксный обход
};

// класс обычного бинарного дерева
class BinaryTree {
public:
    BinaryTree(); // пустое дерево
    BinaryTree(const BinaryTree& other); // копия
    BinaryTree& operator=(const BinaryTree& other); // присваивание
    ~BinaryTree(); // деструктор

    void build_from_array(const int* data, int size); // случайная сборка
    void insert_random(int value); // случайная вставка
    bool search(int value) const; // поиск
    bool is_empty() const; // пусто или нет
    bool is_ideal_balanced() const; // проверка баланса
    void print_graphic() const; // боковой вывод

private:
    TreeNode* root_; // корень

    TreeNode* copy_tree(TreeNode* node) const; // копия ветки
    void clear_tree(TreeNode* node); // очистка
    TreeNode* search_node(TreeNode* node, int value) const; // поиск узла
    void print_graphic_node(TreeNode* node, int level) const; // печать ветки

    int count_nodes(TreeNode* node) const; // число узлов
    bool check_balance(TreeNode* node) const; // проверка условия
};

// отдельный класс проверок
class Validator {
public:
    static int read_positive_int(const std::string& prompt); // число > 0
};

// функции для main
void run_treework3();
void run_treework16();
void run_treework19();

// сервисные функции
namespace input_utils {
    int read_int(const std::string& prompt); // читаем инт
    std::string read_word(const std::string& prompt); // читаем слово
    int choose_mode(); // меню ввода
    int* load_array(const std::string& name, int& size); // грузим массив
    void print_array(const int* data, int size, const std::string& title); // вывод массива
}

#endif