#include "module.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <cstdlib>

// ===== TreeNode =====

TreeNode::TreeNode(int value) {
    data = value; // число узла
    left = NULL; // левый пустой
    right = NULL; // правый пустой
}

// ===== input_utils =====

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

    // вывод массива
    void print_array(const int* data, int size, const std::string& title) {
        std::cout << title;
        for (int i = 0; i < size; ++i) std::cout << data[i] << " ";
        std::cout << "\n";
    }

    // загрузка массива
    int* load_array(const std::string& name, int& size) {
        int mode = choose_mode(); // узнаем режим
        int* arr = NULL; // пока пусто

        if (mode == 1) { // ввод руками
            size = Validator::read_positive_int("Количество элементов " + name + ": ");
            arr = new int[size]; // память под массив
            for (int i = 0; i < size; ++i) {
                arr[i] = read_int("Элемент [" + std::to_string(i) + "]: ");
            }
        } else if (mode == 2) { // рандом
            size = Validator::read_positive_int("Количество случайных чисел: ");
            arr = new int[size]; // память под массив

            int left = read_int("Левая граница: ");
            int right = read_int("Правая граница: ");
            while (left > right) { // проверка границ
                std::cout << "Ошибка: левая граница больше правой.\n";
                left = read_int("Левая граница: ");
                right = read_int("Правая граница: ");
            }

            for (int i = 0; i < size; ++i) {
                arr[i] = left + std::rand() % (right - left + 1); // случайное число
            }
        } else { // файл
            while (true) { // пока не откроем файл
                std::string path = read_word("Путь к файлу: ");
                std::ifstream in(path.c_str()); // поток файла

                if (!in.is_open()) {
                    std::cout << "Файл не найден.\n";
                    continue;
                }

                if (!(in >> size) || size <= 0) {
                    std::cout << "Ошибка в первой строке файла.\n";
                    in.close();
                    continue;
                }

                arr = new int[size]; // память под числа
                bool ok = true; // флаг чтения

                for (int i = 0; i < size; ++i) {
                    if (!(in >> arr[i])) {
                        ok = false; // не хватило чисел
                        break;
                    }
                }

                in.close(); // закрыли файл

                if (!ok) {
                    delete[] arr; // чистим память
                    arr = NULL;
                    std::cout << "Ошибка во второй строке файла.\n";
                    continue;
                }

                break; // файл считан
            }
        }

        std::cout << "Исходные данные " << name << ": ";
        for (int i = 0; i < size; ++i) std::cout << arr[i] << " ";
        std::cout << "\n";
        return arr; // вернуть массив
    }
}

// ===== Validator =====

int Validator::read_positive_int(const std::string& prompt) {
    int value;
    while (true) { // пока не > 0
        value = input_utils::read_int(prompt);
        if (value > 0) return value; // если ок
        std::cout << "Ошибка: число должно быть больше 0.\n";
    }
}

// ===== BinarySearchTree =====

BinarySearchTree::BinarySearchTree() : root_(NULL) {} // пустое дерево

BinarySearchTree::BinarySearchTree(const BinarySearchTree& other) {
    root_ = copy_tree(other.root_); // копируем ветки
}

BinarySearchTree& BinarySearchTree::operator=(const BinarySearchTree& other) {
    if (this != &other) { // защита от себя
        clear_tree(root_); // чистим старое
        root_ = copy_tree(other.root_); // копируем новое
    }
    return *this; // вернуть себя
}

BinarySearchTree::~BinarySearchTree() {
    clear_tree(root_); // чистим память
}

TreeNode* BinarySearchTree::copy_tree(TreeNode* node) const {
    if (node == NULL) return NULL; // пустая ветка

    TreeNode* new_node = new TreeNode(node->data); // новый узел
    new_node->left = copy_tree(node->left); // копируем влево
    new_node->right = copy_tree(node->right); // копируем вправо
    return new_node; // вернуть адрес
}

void BinarySearchTree::clear_tree(TreeNode* node) {
    if (node == NULL) return; // база рекурсии
    clear_tree(node->left); // чистим левую ветку
    clear_tree(node->right); // чистим правую ветку
    delete node; // удалить узел
}

TreeNode* BinarySearchTree::insert_node(TreeNode* node, int value) {
    if (node == NULL) {
        return new TreeNode(value); // новый узел
    }

    if (value < node->data) {
        node->left = insert_node(node->left, value); // идем влево
    } else {
        node->right = insert_node(node->right, value); // идем вправо
    }

    return node; // вернуть текущий узел
}

TreeNode* BinarySearchTree::find_min(TreeNode* node) const {
    if (node == NULL) return NULL; // пусто
    while (node->left != NULL) node = node->left; // идем влево
    return node; // минимальный узел
}

TreeNode* BinarySearchTree::remove_node(TreeNode* node, int value) {
    if (node == NULL) return NULL; // не нашли

    if (value < node->data) {
        node->left = remove_node(node->left, value); // ищем слева
    } else if (value > node->data) {
        node->right = remove_node(node->right, value); // ищем справа
    } else {
        if (node->left == NULL && node->right == NULL) {
            delete node; // удаляем лист
            return NULL;
        }

        if (node->left == NULL) {
            TreeNode* temp = node->right; // правый сын
            delete node;
            return temp;
        }

        if (node->right == NULL) {
            TreeNode* temp = node->left; // левый сын
            delete node;
            return temp;
        }

        TreeNode* temp = find_min(node->right); // минимум справа
        node->data = temp->data; // копируем значение
        node->right = remove_node(node->right, temp->data); // удаляем дубликат
    }

    return node; // вернуть узел
}

TreeNode* BinarySearchTree::search_node(TreeNode* node, int value) const {
    if (node == NULL) return NULL; // пусто
    if (node->data == value) return node; // нашли

    if (value < node->data) return search_node(node->left, value); // поиск слева
    return search_node(node->right, value); // поиск справа
}

void BinarySearchTree::print_graphic_node(TreeNode* node, int level) const {
    if (node == NULL) return; // пустая ветка

    print_graphic_node(node->right, level + 1); // сначала вправо

    for (int i = 0; i < level; ++i) std::cout << "    "; // отступы
    std::cout << node->data << "\n"; // печать узла

    print_graphic_node(node->left, level + 1); // потом влево
}

void BinarySearchTree::print_descending_node(TreeNode* node) const {
    if (node == NULL) return; // пустая ветка
    print_descending_node(node->right); // сначала правое
    std::cout << node->data << " "; // потом корень
    print_descending_node(node->left); // потом левое
}

void BinarySearchTree::print_inorder_node(TreeNode* node) const {
    if (node == NULL) return; // пустая ветка
    print_inorder_node(node->left); // левое поддерево
    std::cout << node->data << " "; // корень
    print_inorder_node(node->right); // правое поддерево
}

void BinarySearchTree::insert(int value) {
    root_ = insert_node(root_, value); // вставка в дерево
}

void BinarySearchTree::remove(int value) {
    root_ = remove_node(root_, value); // удаление из дерева
}

bool BinarySearchTree::search(int value) const {
    return search_node(root_, value) != NULL; // результат поиска
}

bool BinarySearchTree::is_empty() const {
    return root_ == NULL; // пусто или нет
}

void BinarySearchTree::build_from_array(const int* data, int size) {
    for (int i = 0; i < size; ++i) insert(data[i]); // вставляем по одному
}

void BinarySearchTree::print_graphic() const {
    if (is_empty()) {
        std::cout << "Дерево пустое.\n";
        return;
    }
    print_graphic_node(root_, 0); // печать дерева
}

void BinarySearchTree::print_descending() const {
    print_descending_node(root_); // запуск обхода
}

void BinarySearchTree::print_inorder() const {
    print_inorder_node(root_); // запуск обхода
}

void* BinarySearchTree::get_root_address() const {
    return root_; // адрес корня
}

// ===== BinaryTree =====

BinaryTree::BinaryTree() : root_(NULL) {} // пустое дерево

BinaryTree::BinaryTree(const BinaryTree& other) {
    root_ = copy_tree(other.root_); // копируем дерево
}

BinaryTree& BinaryTree::operator=(const BinaryTree& other) {
    if (this != &other) { // защита от себя
        clear_tree(root_);
        root_ = copy_tree(other.root_);
    }
    return *this; // вернуть себя
}

BinaryTree::~BinaryTree() {
    clear_tree(root_); // чистим память
}

TreeNode* BinaryTree::copy_tree(TreeNode* node) const {
    if (node == NULL) return NULL; // пустая ветка

    TreeNode* new_node = new TreeNode(node->data); // новый узел
    new_node->left = copy_tree(node->left); // копируем левую ветку
    new_node->right = copy_tree(node->right); // копируем правую ветку
    return new_node; // вернуть адрес
}

void BinaryTree::clear_tree(TreeNode* node) {
    if (node == NULL) return; // конец рекурсии
    clear_tree(node->left); // чистим слева
    clear_tree(node->right); // чистим справа
    delete node; // удаляем узел
}

void BinaryTree::insert_random(int value) {
    TreeNode* new_node = new TreeNode(value); // новый узел

    if (root_ == NULL) {
        root_ = new_node; // первый узел
        return;
    }

    TreeNode* current = root_; // старт от корня

    while (true) { // ищем место
        int side = std::rand() % 2; // 0 или 1

        if (side == 0) { // пробуем влево
            if (current->left == NULL) {
                current->left = new_node; // вставили слева
                return;
            }
            current = current->left; // идем глубже
        } else { // пробуем вправо
            if (current->right == NULL) {
                current->right = new_node; // вставили справа
                return;
            }
            current = current->right; // идем глубже
        }
    }
}

void BinaryTree::build_from_array(const int* data, int size) {
    for (int i = 0; i < size; ++i) {
        insert_random(data[i]); // случайная вставка
    }
}

TreeNode* BinaryTree::search_node(TreeNode* node, int value) const {
    if (node == NULL) return NULL; // пустая ветка
    if (node->data == value) return node; // нашли

    TreeNode* left_result = search_node(node->left, value); // ищем слева
    if (left_result != NULL) return left_result; // если нашли слева

    return search_node(node->right, value); // иначе ищем справа
}

void BinaryTree::print_graphic_node(TreeNode* node, int level) const {
    if (node == NULL) return; // пустая ветка

    print_graphic_node(node->right, level + 1); // вправо

    for (int i = 0; i < level; ++i) std::cout << "    "; // отступы
    std::cout << node->data << "\n"; // узел

    print_graphic_node(node->left, level + 1); // влево
}

int BinaryTree::count_nodes(TreeNode* node) const {
    if (node == NULL) return 0; // пусто
    return 1 + count_nodes(node->left) + count_nodes(node->right); // считаем узлы
}

bool BinaryTree::check_balance(TreeNode* node) const {
    if (node == NULL) return true; // пустая ветка норм

    int left_count = count_nodes(node->left); // сколько слева
    int right_count = count_nodes(node->right); // сколько справа
    int diff = left_count - right_count; // разница
    if (diff < 0) diff = -diff; // модуль разницы

    if (diff > 1) return false; // условие нарушено

    return check_balance(node->left) && check_balance(node->right); // идем глубже
}

bool BinaryTree::search(int value) const {
    return search_node(root_, value) != NULL; // результат поиска
}

bool BinaryTree::is_empty() const {
    return root_ == NULL; // пусто или нет
}

bool BinaryTree::is_ideal_balanced() const {
    return check_balance(root_); // проверка дерева
}

void BinaryTree::print_graphic() const {
    if (is_empty()) {
        std::cout << "Дерево пустое.\n";
        return;
    }
    print_graphic_node(root_, 0); // печать дерева
}

// ===== Задача 3 =====

class DescendingTreePrinter {
public:
    explicit DescendingTreePrinter(const int* data, int size) { // строим дерево
        tree_.build_from_array(data, size);
    }

    void solve() {
        std::cout << "Исходное дерево:\n";
        tree_.print_graphic();

        std::cout << "P1 = " << tree_.get_root_address() << "\n";
        std::cout << "Действие: обратный инфиксный обход дерева.\n";
        std::cout << "Результат: ";
        tree_.print_descending();
        std::cout << "\n";
    }

private:
    BinarySearchTree tree_; // дерево поиска
};

// ===== Задача 16 =====

class TreeSortManager {
public:
    explicit TreeSortManager(const int* data, int size) { // строим дерево
        tree_.build_from_array(data, size);
    }

    void solve() {
        std::cout << "Дерево после вставки элементов:\n";
        tree_.print_graphic();

        std::cout << "P1 = " << tree_.get_root_address() << "\n";
        std::cout << "Отсортированный набор: ";
        tree_.print_inorder();
        std::cout << "\n";
    }

private:
    BinarySearchTree tree_; // дерево поиска
};

// ===== Задача 19 =====

class BalanceChecker {
public:
    explicit BalanceChecker(const int* data, int size) { // строим дерево
        tree_.build_from_array(data, size);
    }

    void solve() {
        std::cout << "Исходное бинарное дерево:\n";
        tree_.print_graphic();

        std::cout << "Действие: случайно построили бинарное дерево и проверяем баланс.\n";
        std::cout << "Результат: ";
        if (tree_.is_ideal_balanced()) {
            std::cout << "True\n";
        } else {
            std::cout << "False\n";
        }
    }

private:
    BinaryTree tree_; // обычное дерево
};

// запуск первой задачи
void run_treework3() {
    int size = 0; // размер набора
    int* data = input_utils::load_array("для дерева поиска", size); // грузим числа

    DescendingTreePrinter manager(data, size); // создаем менеджер
    manager.solve(); // решаем

    BinarySearchTree extra_tree; // для показа базовых методов
    extra_tree.build_from_array(data, size);

    int value = input_utils::read_int("Введите число для поиска: ");
    if (extra_tree.search(value)) {
        std::cout << "Элемент найден.\n";
    } else {
        std::cout << "Элемент не найден.\n";
    }

    int del_value = input_utils::read_int("Введите число для удаления: ");
    std::cout << "До удаления:\n";
    extra_tree.print_graphic();
    extra_tree.remove(del_value); // удаляем узел
    std::cout << "После удаления:\n";
    extra_tree.print_graphic();

    delete[] data; // чистим массив
}

// запуск второй задачи
void run_treework16() {
    int size = 0; // размер набора
    int* data = input_utils::load_array("для сортировки", size); // грузим числа

    input_utils::print_array(data, size, "Исходный набор: ");

    TreeSortManager manager(data, size); // создаем менеджер
    manager.solve(); // решаем

    BinarySearchTree extra_tree; // еще одно дерево
    extra_tree.build_from_array(data, size);

    int add_value = input_utils::read_int("Введите число для добавления: ");
    std::cout << "До добавления:\n";
    extra_tree.print_graphic();
    extra_tree.insert(add_value); // добавляем узел
    std::cout << "После добавления:\n";
    extra_tree.print_graphic();

    int value = input_utils::read_int("Введите число для поиска: ");
    if (extra_tree.search(value)) {
        std::cout << "Элемент найден.\n";
    } else {
        std::cout << "Элемент не найден.\n";
    }

    delete[] data; // чистим массив
}

// запуск третьей задачи
void run_treework19() {
    int size = 0; // размер набора
    int* data = input_utils::load_array("для бинарного дерева", size); // грузим числа

    BalanceChecker checker(data, size); // создаем проверку
    checker.solve(); // решаем

    BinaryTree extra_tree; // дерево для поиска
    extra_tree.build_from_array(data, size);

    int value = input_utils::read_int("Введите число для поиска: ");
    if (extra_tree.search(value)) {
        std::cout << "Элемент найден.\n";
    } else {
        std::cout << "Элемент не найден.\n";
    }

    delete[] data; // чистим массив
}