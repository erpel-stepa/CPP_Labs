#include "module.h"

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <limits>
#include <map>

// пустой узел
Node::Node() : value(0), left(nullptr), right(nullptr), parent(nullptr) {
}

// узел с числом
Node::Node(int value) : value(value), left(nullptr), right(nullptr), parent(nullptr) {
}

// копия узла
Node::Node(const Node& other) : value(other.value), left(nullptr), right(nullptr), parent(nullptr) {
}

// присваивание узла
Node& Node::operator=(const Node& other) {
    if (this != &other) {        // не сам себе
        value = other.value;     // копируем число
        left = nullptr;          // связи не копируем
        right = nullptr;         // связи не копируем
        parent = nullptr;        // родителя не копируем
    }
    return *this;
}

// конец узла
Node::~Node() {
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}

// взять число
int Node::getValue() const {
    return value;
}

// взять левый
Node* Node::getLeft() const {
    return left;
}

// взять правый
Node* Node::getRight() const {
    return right;
}

// взять родителя
Node* Node::getParent() const {
    return parent;
}

// записать число
void Node::setValue(int value) {
    this->value = value;         // поле класса
}

// записать левый
void Node::setLeft(Node* node) {
    left = node;
    if (node != nullptr) {
        node->setParent(this);
    }
}

// записать правый
void Node::setRight(Node* node) {
    right = node;
    if (node != nullptr) {
        node->setParent(this);
    }
}

// записать родителя
void Node::setParent(Node* node) {
    parent = node;
}

// класс проверок
Checks::Checks() {
}

// копия проверок
Checks::Checks(const Checks& other) {
    (void)other;                 // без полей
}

// присваивание проверок
Checks& Checks::operator=(const Checks& other) {
    (void)other;                 // без полей
    return *this;
}

// конец проверок
Checks::~Checks() {
}

// очистка ввода
void Checks::clearInput() {
    std::cin.clear();                                                    // сброс ошибки
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // убрать мусор
}

// чтение числа
int Checks::readInt(const std::string& text) {
    int value;
    while (true) {
        std::cout << text;
        if (std::cin >> value) {  // ввод нормальный
            return value;
        }
        clearInput();            // чистим cin
        std::cout << "Ошибка ввода.\n";
    }
}

// выбор пункта
int Checks::readMenuChoice(int minValue, int maxValue) {
    int choice;
    while (true) {
        std::cout << "Ваш выбор: ";
        if (std::cin >> choice && choice >= minValue && choice <= maxValue) { // в диапазоне
            return choice;
        }
        clearInput();            // чистим cin
        std::cout << "Введите число от " << minValue << " до " << maxValue << ".\n";
    }
}

// чтение файла
bool Checks::readValuesFromFile(const std::string& fileName, std::vector<int>& values) {
    std::ifstream file(fileName); // открыть файл
    if (!file.is_open()) {        // не открылся
        return false;
    }

    int n;
    file >> n;                    // читаем N
    if (!file || n <= 0) {        // плохой размер
        return false;
    }

    values.clear();               // старое убрать
    for (int i = 0; i < n; ++i) {
        int value;
        if (!(file >> value)) {   // числа не хватило
            return false;
        }
        values.push_back(value);  // кладем число
    }

    return true;
}

// выбор ввода
std::vector<int> Checks::readValuesByChoice() {
    std::vector<int> values;

    std::cout << "Способ ввода:\n";
    std::cout << "1) С клавиатуры\n";
    std::cout << "2) Из файла\n";
    std::cout << "3) Рандомно\n";
    int choice = readMenuChoice(1, 3); // способ ввода

    if (choice == 1) {
        int n = readInt("Сколько чисел: ");
        while (n <= 0) {
            std::cout << "Количество должно быть больше нуля.\n";
            n = readInt("Сколько чисел: ");
        }
        for (int i = 0; i < n; ++i) {
            values.push_back(readInt("Число: ")); // добавляем вручную
        }
    } else if (choice == 2) {
        std::string fileName;
        std::cout << "Имя файла: ";
        std::cin >> fileName;
        while (!readValuesFromFile(fileName, values)) { // пока ошибка файла
            std::cout << "Файл не прочитан. Формат: N и затем N чисел.\n";
            std::cout << "Имя файла: ";
            std::cin >> fileName;
        }
    } else {
        int n = readInt("Сколько чисел: ");
        while (n <= 0) {
            std::cout << "Количество должно быть больше нуля.\n";
            n = readInt("Сколько чисел: ");
        }
        int minValue = readInt("Минимум: ");
        int maxValue = readInt("Максимум: ");
        if (minValue > maxValue) {
            std::swap(minValue, maxValue); // меняем местами
        }

        std::srand(static_cast<unsigned int>(std::time(nullptr))); // зерно рандома
        for (int i = 0; i < n; ++i) {
            values.push_back(minValue + std::rand() % (maxValue - minValue + 1)); // число в границах
        }
    }

    return values;
}

// пустое дерево
BinaryTree::BinaryTree() : root(nullptr) {
}

// копия дерева
BinaryTree::BinaryTree(const BinaryTree& other) : root(nullptr) {
    root = copyNodes(other.root); // глубокая копия
}

// присваивание дерева
BinaryTree& BinaryTree::operator=(const BinaryTree& other) {
    if (this != &other) {         // не сам себе
        clearTree();              // старое убрать
        root = copyNodes(other.root); // новое скопировать
    }
    return *this;
}

// удалить дерево
BinaryTree::~BinaryTree() {
    clearTree();                  // удалить узлы
}

// копируем узлы
Node* BinaryTree::copyNodes(Node* node) const {
    if (node == nullptr) {        // конец ветки
        return nullptr;
    }

    Node* copy = new Node(node->getValue());      // новый такой же узел
    copy->setLeft(copyNodes(node->getLeft()));    // копия слева
    copy->setRight(copyNodes(node->getRight()));  // копия справа
    return copy;                                  // вернуть корень копии
}

// очистка ветки
void BinaryTree::clear(Node* node) {
    if (node == nullptr) {        // нечего удалять
        return;
    }

    clear(node->getLeft());       // удалить слева
    clear(node->getRight());      // удалить справа
    delete node;                  // удалить корень
}

// взять корень
Node* BinaryTree::getRoot() const {
    return root;
}

// проверка пустоты
bool BinaryTree::isEmpty() const {
    return root == nullptr;
}

// очистка дерева
void BinaryTree::clearTree() {
    clear(root);                  // удалить все
    root = nullptr;               // дерево пустое
}

// вставка поиска
void BinaryTree::insertBst(Node*& node, int value) {
    if (node == nullptr) {        // нашли место
        node = new Node(value);   // создаем узел
        return;
    }

    if (value < node->getValue()) {   // меньше влево
        Node* left = node->getLeft(); // берем ссылку
        insertBst(left, value);       // вставляем ниже
        node->setLeft(left);          // возвращаем связь
    } else {
        Node* right = node->getRight(); // больше вправо
        insertBst(right, value);        // вставляем ниже
        node->setRight(right);          // возвращаем связь
    }
}

// собрать поиск
void BinaryTree::buildAsBst(const std::vector<int>& values) {
    clearTree();                  // сначала пусто
    for (int value : values) {
        insertBst(root, value);   // вставка в поиск
    }
}

// добавление уровнем
void BinaryTree::addLevelNode(int value) {
    Node* node = new Node(value); // новый узел
    if (root == nullptr) {
        root = node;              // первый корень
        return;
    }

    std::vector<Node*> queue;     // очередь уровней
    queue.push_back(root);        // начать с корня
    for (size_t i = 0; i < queue.size(); ++i) { // идем по очереди
        Node* current = queue[i]; // текущий узел
        if (current->getLeft() == nullptr) { // есть место слева
            current->setLeft(node);          // ставим слева
            return;
        }
        if (current->getRight() == nullptr) { // есть место справа
            current->setRight(node);          // ставим справа
            return;
        }
        queue.push_back(current->getLeft());  // следующий уровень
        queue.push_back(current->getRight()); // следующий уровень
    }
}

// собрать обычное
void BinaryTree::buildAsCommonTree(const std::vector<int>& values) {
    clearTree();                  // сначала пусто
    for (int value : values) {
        addLevelNode(value);      // добавляем по порядку
    }
}

// число узлов
int BinaryTree::countNodes(Node* node) const {
    if (node == nullptr) {        // пустая ветка
        return 0;
    }
    return 1 + countNodes(node->getLeft()) + countNodes(node->getRight()); // левое+правое+корень
}

// печать ветки
void BinaryTree::printTree(Node* node, int level) const {
    if (node == nullptr) {        // нечего печатать
        return;
    }

    printTree(node->getRight(), level + 1); // сначала правая
    for (int i = 0; i < level; ++i) {
        std::cout << "    ";
    }
    std::cout << node->getValue() << "\n";
    printTree(node->getLeft(), level + 1);  // потом левая
}

// печать дерева
void BinaryTree::printGraphic() const {
    if (root == nullptr) {
        std::cout << "(пусто)\n";
        return;
    }
    printTree(root, 0);          // печать от корня
}

// дерево в список
Node* BinaryTree::makeList(Node* node, Node*& previous) {
    if (node == nullptr) {        // край дерева
        return nullptr;
    }

    Node* head = makeList(node->getLeft(), previous); // идем влево
    if (previous == nullptr) {     // это самый левый
        head = node;               // будет головой
    } else {
        previous->setRight(node);  // next
        node->setLeft(previous);   // prev
    }
    previous = node;               // последний в списке

    Node* savedRight = node->getRight(); // запомнить право
    makeList(savedRight, previous);      // идем вправо
    return head;                         // голова списка
}

// конвертация поиска
Node* BinaryTree::convertBstToList() {
    Node* previous = nullptr;      // пока нет prev
    Node* head = makeList(root, previous); // строим список
    if (previous != nullptr) {
        previous->setRight(nullptr); // конец списка
    }
    root = nullptr;                  // узлы ушли
    return head;                     // вернуть список
}

// код поддерева
std::string BinaryTree::subtreeCode(Node* node, std::vector<Node*>& nodes,
                                    std::vector<std::string>& codes,
                                    std::vector<int>& sizes) const {
    if (node == nullptr) {        // пустая ветка
        return "#";               // метка пустоты
    }

    std::string leftCode = subtreeCode(node->getLeft(), nodes, codes, sizes);   // код слева
    std::string rightCode = subtreeCode(node->getRight(), nodes, codes, sizes); // код справа
    std::string code = "(" + leftCode + "," + rightCode + "," + std::to_string(node->getValue()) + ")"; // весь код
    int size = countNodes(node);     // размер поддерева

    nodes.push_back(node);           // адрес корня
    codes.push_back(code);           // строка формы
    sizes.push_back(size);           // размер ветки
    return code;                     // вернуть наверх
}

// поиск узла
bool BinaryTree::containsNode(Node* node, Node* target) const {
    if (node == nullptr) {        // дошли до края
        return false;
    }
    if (node == target) {         // нашли адрес
        return true;
    }
    return containsNode(node->getLeft(), target) || containsNode(node->getRight(), target); // ищем ниже
}

// отцепить узел
void BinaryTree::detachNode(Node*& current, Node* target) {
    if (current == nullptr) {     // пустая ветка
        return;
    }
    if (current == target) {      // нашли дубль
        clear(current);           // удалить ветку
        current = nullptr;        // отцепить от родителя
        return;
    }

    Node* left = current->getLeft();    // левый потомок
    Node* right = current->getRight();  // правый потомок
    detachNode(left, target);           // ищем слева
    detachNode(right, target);          // ищем справа
    current->setLeft(left);             // вернуть связь
    current->setRight(right);           // вернуть связь
}

// удалить дубли
int BinaryTree::removeDuplicateSubtrees() {
    int removed = 0;               // счетчик удалений

    while (root != nullptr) {
        std::vector<Node*> nodes;       // корни поддеревьев
        std::vector<std::string> codes; // коды поддеревьев
        std::vector<int> sizes;         // размеры поддеревьев
        subtreeCode(root, nodes, codes, sizes); // собрать актуальное дерево

        std::map<std::string, std::vector<int>> groups; // код -> индексы одинаковых веток
        for (int i = 0; i < static_cast<int>(codes.size()); ++i) {
            groups[codes[i]].push_back(i);
        }

        std::string biggestCode;   // код самой крупной группы дублей
        int biggestSize = 0;       // размер выбранного поддерева
        for (const auto& group : groups) {
            if (group.second.size() > 1) {
                int size = sizes[group.second[0]];
                if (size > 1 && size > biggestSize) {
                    biggestSize = size;
                    biggestCode = group.first;
                }
            }
        }

        if (biggestSize == 0) {    // дублей больше нет
            break;
        }

        const std::vector<int>& same = groups[biggestCode];
        for (size_t i = 0; i < same.size(); ++i) { // удаляем все одинаковые поддеревья
            detachNode(root, nodes[same[i]]);      // отцепить найденную ветку
            ++removed;                             // плюс удаление
        }
    }

    return removed;                // сколько удалили
}

// пустой список
DoublyList::DoublyList() : head(nullptr) {
}

// список с головой
DoublyList::DoublyList(Node* head) : head(head) {
}

// копия списка
DoublyList::DoublyList(const DoublyList& other) : head(nullptr) {
    Node* tail = nullptr;          // конец копии
    for (Node* current = other.head; current != nullptr; current = current->getRight()) { // идем по списку
        Node* copy = new Node(current->getValue()); // копия узла
        copy->setLeft(tail);       // prev на хвост
        if (tail == nullptr) {     // первый узел
            head = copy;           // новая голова
        } else {
            tail->setRight(copy);  // next от хвоста
        }
        tail = copy;               // сдвиг хвоста
    }
}

// присваивание списка
DoublyList& DoublyList::operator=(const DoublyList& other) {
    if (this != &other) {          // не сам себе
        Node* current = head;      // начало старого
        while (current != nullptr) {
            Node* next = current->getRight(); // запомнить next
            delete current;       // удалить старый
            current = next;       // перейти дальше
        }
        head = nullptr;            // список пуст

        Node* tail = nullptr;      // конец копии
        for (Node* node = other.head; node != nullptr; node = node->getRight()) { // копируем список
            Node* copy = new Node(node->getValue()); // новый узел
            copy->setLeft(tail);   // prev
            if (tail == nullptr) { // первый узел
                head = copy;       // голова
            } else {
                tail->setRight(copy); // next
            }
            tail = copy;           // сдвиг хвоста
        }
    }
    return *this;
}

// очистка списка
DoublyList::~DoublyList() {
    Node* current = head;          // старт списка
    while (current != nullptr) {
        Node* next = current->getRight(); // не потерять next
        delete current;          // удалить узел
        current = next;          // следующий узел
    }
    head = nullptr;              // список пуст
}

// задать голову
void DoublyList::setHead(Node* head) {
    this->head = head;           // новая голова
}

// печать списка
void DoublyList::printList() const {
    if (head == nullptr) {
        std::cout << "(пусто)\n";
        return;
    }

    const Node* current = head;  // печать с головы
    while (current != nullptr) {
        std::cout << current->getValue();
        current = current->getRight(); // следующий узел
        if (current != nullptr) {
            std::cout << ' ';
        }
    }
    std::cout << "\n";
}

// пустой итератор
PostOrderIterator::PostOrderIterator() : root(nullptr), current(nullptr) {
}

// итератор от корня
PostOrderIterator::PostOrderIterator(const Node* root) : root(root), current(firstPostOrderNode(root)) {
}

// копия итератора
PostOrderIterator::PostOrderIterator(const PostOrderIterator& other)
    : root(other.root), current(other.current) { // копия состояния
}

// присваивание итератора
PostOrderIterator& PostOrderIterator::operator=(const PostOrderIterator& other) {
    if (this != &other) {        // не сам себе
        root = other.root;       // копия корня
        current = other.current; // копия текущего
    }
    return *this;
}

// конец итератора
PostOrderIterator::~PostOrderIterator() {
    root = nullptr;              // убрать адрес
    current = nullptr;           // убрать адрес
}

// первый узел в порядке лево-право-корень
const Node* PostOrderIterator::firstPostOrderNode(const Node* node) const {
    const Node* result = node;
    while (result != nullptr && (result->getLeft() != nullptr || result->getRight() != nullptr)) {
        if (result->getLeft() != nullptr) {
            result = result->getLeft();
        } else {
            result = result->getRight();
        }
    }
    return result;
}

// сдвиг итератора
void PostOrderIterator::moveToNext() {
    if (current == nullptr || current == root) {
        current = nullptr;
        return;
    }

    const Node* parent = current->getParent();
    if (parent == nullptr) {
        current = nullptr;
        return;
    }

    if (parent->getRight() != nullptr && parent->getRight() != current) {
        current = firstPostOrderNode(parent->getRight());
    } else {
        current = parent;
    }
}

// есть следующий
bool PostOrderIterator::hasNext() const {
    return current != nullptr;   // есть следующий узел
}

// взять следующий
int PostOrderIterator::next() {
    if (current == nullptr) {
        return 0;
    }

    int value = current->getValue();    // значение текущего узла
    moveToNext();                       // подготовить следующий
    return value;
}

// рисунок котика
static void printCat() {
    std::cout << " /\\_/\\\\\n";
    std::cout << "( o.o )\n";
    std::cout << " > ^ <\n";
}

// запуск первой
void runTreeFun1() {
    std::cout << "\nTreeFun1\n";
    std::vector<int> values = Checks::readValuesByChoice(); // получить данные

    BinaryTree tree;
    tree.buildAsBst(values);      // строим BST

    std::cout << "Исходное дерево поиска:\n";
    tree.printGraphic();

    std::cout << "Делаем обход слева направо и связываем узлы через left/right.\n";
    Node* head = tree.convertBstToList(); // корень стал списком
    DoublyList list(head);                // обертка списка

    std::cout << "После преобразования дерево стало списком:\n";
    list.printList();

    std::cout << "TreeFun1 выполнена.\n";
    printCat();
}

// запуск пятой
void runTreeFun5() {
    std::cout << "\nTreeFun5\n";
    std::vector<int> values = Checks::readValuesByChoice(); // получить данные

    BinaryTree tree;
    tree.buildAsCommonTree(values); // обычное дерево

    std::cout << "Исходное дерево:\n";
    tree.printGraphic();

    std::cout << "Итератор идет в порядке лево-право-корень:\n";
    PostOrderIterator iterator(tree.getRoot()); // итератор от корня
    while (iterator.hasNext()) {
        std::cout << iterator.next() << ' '; // следующий в обходе
    }
    std::cout << "\n";

    std::cout << "После обхода дерево не менялось:\n";
    tree.printGraphic();

    std::cout << "TreeFun5 выполнена.\n";
    printCat();
}

// запуск тринадцатой
void runTreeFun13() {
    std::cout << "\nTreeFun13\n";
    std::vector<int> values = Checks::readValuesByChoice(); // получить данные

    BinaryTree tree;
    tree.buildAsCommonTree(values); // не дерево поиска

    std::cout << "Исходное дерево:\n";
    tree.printGraphic();

    std::cout << "Ищем одинаковые поддеревья и удаляем повторы, крупные раньше.\n";
    int removed = tree.removeDuplicateSubtrees(); // убрать дубли

    std::cout << "Удалено поддеревьев: " << removed << "\n";
    std::cout << "Дерево после удаления:\n";
    tree.printGraphic();

    std::cout << "TreeFun13 выполнена.\n";
    printCat();
}
