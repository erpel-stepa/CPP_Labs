#include "module.h"

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stack>
#include <vector>

Node::Node() { // пустой узел
    value = 0;
    variable = false;
    left = nullptr;
    right = nullptr;
}

Node::Node(int value, bool variable) { // узел с данными
    this->value = value;
    this->variable = variable;
    left = nullptr;
    right = nullptr;
}

Node::Node(const Node& other) { // копия узла
    value = other.value;
    variable = other.variable;
    left = nullptr;
    right = nullptr;
}

Node& Node::operator=(const Node& other) { // присваивание узла
    if (this != &other) {
        value = other.value;
        variable = other.variable;
        left = nullptr;
        right = nullptr;
    }
    return *this;
}

Node::~Node() { // удаление узла
    left = nullptr;
    right = nullptr;
}

int Node::getValue() const { // взять значение
    return value;
}

bool Node::isVariable() const { // это переменная
    return variable;
}

Node* Node::getLeft() const { // левый сын
    return left;
}

Node* Node::getRight() const { // правый сын
    return right;
}

void Node::setValue(int value) { // смена значения
    this->value = value;
}

void Node::setVariable(bool variable) { // смена флага
    this->variable = variable;
}

void Node::setLeft(Node* left) { // смена левого
    this->left = left;
}

void Node::setRight(Node* right) { // смена правого
    this->right = right;
}

Validator::Validator() = default; // объект проверок

Validator::Validator(const Validator& other) = default; // копия проверок

Validator& Validator::operator=(const Validator& other) = default; // присваивание проверок

Validator::~Validator() = default; // удаление проверок

bool Validator::isDigitOperand(char symbol) const { // цифра операнд
    return symbol >= '0' && symbol <= '9';
}

bool Validator::isNumber(const std::string& text) const { // целое число
    if (text.empty()) {
        return false;
    }

    for (char symbol : text) {
        if (symbol < '0' || symbol > '9') {
            return false;
        }
    }
    return true;
}

bool Validator::isOperator(char symbol) const { // знак операции
    return symbol == '+' || symbol == '-' || symbol == '*' ||
           symbol == '/' || symbol == '%' || symbol == '^';
}

bool Validator::isBinaryOperator(int code) const { // код операции
    return code >= -6 && code <= -1; // отрицательные коды
}

bool Validator::checkPostfix(const std::string& expression) const { // проверка опз
    int count = 0; // счет операндов

    for (char symbol : expression) {
        if (symbol == ' ') {
            continue;
        }
        if (isDigitOperand(symbol)) {
            count++; // появился операнд
        } else if (isOperator(symbol) && symbol != '^') {
            count--; // операция съедает два
            if (count < 1) {
                return false;
            }
        } else {
            return false;
        }
    }

    return count == 1;
}

bool Validator::checkInfix(const std::string& expression) const { // проверка инфикса
    if (expression.empty()) {
        return false;
    }

    for (char symbol : expression) {
        if (symbol == ' ' || symbol == 'x' || symbol == '(' || symbol == ')' ||
            isOperator(symbol) || isDigitOperand(symbol)) {
            continue;
        }
        return false;
    }

    return true;
}

ExpressionTree::ExpressionTree() { // пустое дерево
    root = nullptr;
}

ExpressionTree::ExpressionTree(const ExpressionTree& other) { // копия дерева
    root = copyTree(other.root);
}

ExpressionTree& ExpressionTree::operator=(const ExpressionTree& other) { // присваивание дерева
    if (this != &other) {
        clear();
        root = copyTree(other.root);
    }
    return *this;
}

ExpressionTree::~ExpressionTree() { // очистка дерева
    clear();
}

Node* ExpressionTree::copyTree(Node* node) const { // копируем дерево
    if (node == nullptr) {
        return nullptr;
    }

    Node* newNode = new Node(node->getValue(), node->isVariable()); // новый корень
    newNode->setLeft(copyTree(node->getLeft())); // копия слева
    newNode->setRight(copyTree(node->getRight())); // копия справа
    return newNode;
}

void ExpressionTree::clear(Node* node) { // чистим узлы
    if (node == nullptr) {
        return;
    }

    clear(node->getLeft()); // чистим детей
    clear(node->getRight());
    delete node;
}

int ExpressionTree::priority(char operation) const { // приоритет знака
    if (operation == '^') {
        return 3;
    }
    if (operation == '*' || operation == '/' || operation == '%') {
        return 2;
    }
    if (operation == '+' || operation == '-') {
        return 1;
    }
    return 0;
}

int ExpressionTree::operationCode(char operation) const { // знак в код
    if (operation == '+') return -1;
    if (operation == '-') return -2;
    if (operation == '*') return -3;
    if (operation == '/') return -4;
    if (operation == '%') return -5;
    if (operation == '^') return -6;
    return 0;
}

char ExpressionTree::operationSymbol(int code) const { // код в знак
    if (code == -1) return '+';
    if (code == -2) return '-';
    if (code == -3) return '*';
    if (code == -4) return '/';
    if (code == -5) return '%';
    if (code == -6) return '^';
    return '?';
}

bool ExpressionTree::containsVariable(Node* node) const { // ищем x
    if (node == nullptr) {
        return false;
    }
    if (node->isVariable()) {
        return true;
    }
    return containsVariable(node->getLeft()) || containsVariable(node->getRight()); // ищем ниже
}

int ExpressionTree::calculate(Node* node, int xValue) const { // считаем поддерево
    if (node == nullptr) {
        return 0;
    }
    if (node->isVariable()) {
        return xValue;
    }
    if (!validator.isBinaryOperator(node->getValue())) {
        return node->getValue();
    }

    int leftValue = calculate(node->getLeft(), xValue); // считаем детей
    int rightValue = calculate(node->getRight(), xValue);

    if (node->getValue() == -1) return leftValue + rightValue; // выбираем операцию
    if (node->getValue() == -2) return leftValue - rightValue;
    if (node->getValue() == -3) return leftValue * rightValue;
    if (node->getValue() == -4) return rightValue == 0 ? 0 : leftValue / rightValue; // защита деления
    if (node->getValue() == -5) return rightValue == 0 ? 0 : leftValue % rightValue;

    int result = 1; // степень вручную
    for (int i = 0; i < rightValue; i++) {
        result *= leftValue;
    }
    return result;
}

void ExpressionTree::printSideways(Node* node, int level, std::ostream& out) const { // печать боком
    if (node == nullptr) {
        return;
    }

    printSideways(node->getRight(), level + 1, out); // сначала справа

    out << std::setw(level * 8 + 8); // отступ уровня
    if (node->isVariable()) {
        out << "x";
    } else if (validator.isBinaryOperator(node->getValue())) {
        out << operationSymbol(node->getValue());
    } else {
        out << node->getValue();
    }
    out << '\n';

    printSideways(node->getLeft(), level + 1, out); // потом слева
}

void ExpressionTree::replaceMultiplication(Node* node) { // убрать умножение
    if (node == nullptr) {
        return;
    }

    replaceMultiplication(node->getLeft()); // вниз по дереву
    replaceMultiplication(node->getRight());

    if (node->getValue() == -3) {
        int value = calculate(node, 0); // считаем умножение
        clear(node->getLeft()); // удаляем детей
        clear(node->getRight());
        node->setLeft(nullptr); // делаем лист
        node->setRight(nullptr);
        node->setValue(value);
    }
}

void ExpressionTree::replaceConstants(Node* node, int xValue) { // свернуть константы
    if (node == nullptr) {
        return;
    }

    replaceConstants(node->getLeft(), xValue); // сначала дети
    replaceConstants(node->getRight(), xValue);

    if (!containsVariable(node) && validator.isBinaryOperator(node->getValue())) { // нет переменной
        int value = calculate(node, xValue); // значение ветки
        clear(node->getLeft()); // удаляем ветку
        clear(node->getRight());
        node->setLeft(nullptr); // оставляем число
        node->setRight(nullptr);
        node->setValue(value);
    }
}

std::string ExpressionTree::readToken(const std::string& expression, int& index) const { // чтение токена
    while (index < static_cast<int>(expression.size()) && expression[index] == ' ') { // пропуск пробелов
        index++;
    }

    std::string token;
    if (index >= static_cast<int>(expression.size())) {
        return token;
    }

    if (expression[index] >= '0' && expression[index] <= '9') {
        while (index < static_cast<int>(expression.size()) && // собираем число
               expression[index] >= '0' && expression[index] <= '9') {
            token += expression[index];
            index++;
        }
    } else {
        token += expression[index]; // один символ
        index++;
    }

    return token;
}

Node* ExpressionTree::getRoot() const { // корень дерева
    return root;
}

void ExpressionTree::clear() { // удалить дерево
    clear(root);
    root = nullptr;
}

bool ExpressionTree::buildFromPostfix(const std::string& expression) { // строим из опз
    clear();
    if (!validator.checkPostfix(expression)) {
        return false;
    }

    std::stack<Node*> nodes; // стек узлов

    for (char symbol : expression) {
        if (symbol == ' ') {
            continue;
        }
        if (validator.isDigitOperand(symbol)) {
            nodes.push(new Node(symbol - '0')); // кладем число
        } else {
            Node* right = nodes.top(); // правый операнд
            nodes.pop();
            Node* left = nodes.top(); // левый операнд
            nodes.pop();

            Node* operation = new Node(operationCode(symbol)); // узел операции
            operation->setLeft(left);
            operation->setRight(right);
            nodes.push(operation); // готовое поддерево
        }
    }

    root = nodes.top(); // последний корень
    return true;
}

bool ExpressionTree::buildFromInfix(const std::string& expression) { // строим из инфикса
    clear();
    if (!validator.checkInfix(expression)) {
        return false;
    }

    std::stack<char> operations; // стек операций
    std::stack<Node*> nodes; // стек узлов
    int index = 0;

    while (index < static_cast<int>(expression.size())) {
        std::string token = readToken(expression, index); // следующий токен
        if (token.empty()) {
            break;
        }

        if (validator.isNumber(token)) {
            int number = std::stoi(token); // строка в число
            if (number < 1 || number > 30) {
                return false;
            }
            nodes.push(new Node(number)); // узел числа
        } else if (token == "x") {
            nodes.push(new Node(0, true)); // узел x
        } else if (token == "(") {
            operations.push('('); // открыли скобку
        } else if (token == ")") {
            while (!operations.empty() && operations.top() != '(') { // закрываем скобку
                char operation = operations.top();
                operations.pop();

                if (nodes.size() < 2) {
                    return false;
                }
                Node* right = nodes.top(); // берем операнды
                nodes.pop();
                Node* left = nodes.top();
                nodes.pop();

                Node* newNode = new Node(operationCode(operation)); // строим операцию
                newNode->setLeft(left);
                newNode->setRight(right);
                nodes.push(newNode);
            }
            if (operations.empty()) {
                return false;
            }
            operations.pop(); // убрать скобку
        } else if (validator.isOperator(token[0])) {
            while (!operations.empty() && operations.top() != '(' && // старшие операции
                   priority(operations.top()) >= priority(token[0])) {
                char operation = operations.top();
                operations.pop();

                if (nodes.size() < 2) {
                    return false;
                }
                Node* right = nodes.top(); // берем операнды
                nodes.pop();
                Node* left = nodes.top();
                nodes.pop();

                Node* newNode = new Node(operationCode(operation)); // строим узел
                newNode->setLeft(left);
                newNode->setRight(right);
                nodes.push(newNode);
            }
            operations.push(token[0]); // новая операция
        } else {
            return false;
        }
    }

    while (!operations.empty()) {
        if (operations.top() == '(') {
            return false;
        }

        char operation = operations.top(); // остаток операций
        operations.pop();

        if (nodes.size() < 2) {
            return false;
        }
        Node* right = nodes.top(); // два операнда
        nodes.pop();
        Node* left = nodes.top();
        nodes.pop();

        Node* newNode = new Node(operationCode(operation)); // новое поддерево
        newNode->setLeft(left);
        newNode->setRight(right);
        nodes.push(newNode);
    }

    if (nodes.size() != 1) {
        return false;
    }

    root = nodes.top(); // корень готов
    return true;
}

int ExpressionTree::calculate(int xValue) const { // считаем дерево
    return calculate(root, xValue);
}

void ExpressionTree::printSideways(std::ostream& out) const { // печатаем дерево
    if (root == nullptr) {
        out << "дерево пустое\n";
        return;
    }
    printSideways(root, 0, out);
}

void ExpressionTree::transformCalcTree3() { // замена умножения
    replaceMultiplication(root);
}

void ExpressionTree::transformCalcTree25(int xValue) { // замена констант
    replaceConstants(root, xValue);
}

static std::string inputFromKeyboard(const std::string& message) { // строка с клавиатуры
    std::string expression;
    std::cout << message;
    std::cin.ignore(10000, '\n'); // чистим ввод
    std::getline(std::cin, expression);
    return expression;
}

static std::string inputFromFile() { // строка из файла
    std::string fileName;
    std::string expression;

    std::cout << "Имя файла: ";
    std::cin >> fileName;

    std::ifstream file(fileName); // открываем файл
    if (!file) {
        std::cout << "Файл не открылся\n";
        return "";
    }

    std::getline(file, expression);
    return expression;
}

static std::string randomPostfix() { // случайная опз
    const std::string variants[] = {
        "23*4+",
        "84/52*+",
        "93%27*+",
        "56*78+/"
    };
    return variants[std::rand() % 4];
}

static std::string randomInfix() { // случайный инфикс
    const std::string variants[] = {
        "2+3*x",
        "(10+x)*2-5",
        "30%(x+2)+4",
        "2^3+x*5"
    };
    return variants[std::rand() % 4];
}

static std::string chooseInput(bool postfix) { // выбор ввода
    int choice;
    static bool randomStarted = false;

    if (!randomStarted) {
        std::srand(static_cast<unsigned>(std::time(nullptr))); // запуск рандома
        randomStarted = true;
    }

    std::cout << "1) С клавиатуры\n";
    std::cout << "2) Из файла\n";
    std::cout << "3) Рандомно\n";
    std::cout << "Способ ввода: ";
    std::cin >> choice;

    if (choice == 1) {
        return inputFromKeyboard(postfix ? "Введите ОПЗ: " : "Введите инфикс: ");
    }
    if (choice == 2) {
        return inputFromFile();
    }
    if (choice == 3) {
        std::string expression = postfix ? randomPostfix() : randomInfix(); // случайный пример
        std::cout << "Выражение: " << expression << '\n';
        return expression;
    }

    std::cout << "Выбран рандом\n";
    return postfix ? randomPostfix() : randomInfix();
}

static void printTaskDone() { // котик в конце
    std::cout << "\nЗадание выполнено\n";
    std::cout << " /\\_/\\\\\n";
    std::cout << "( o.o )\n";
    std::cout << " > ^ <\n";
}

void runCalcTree3() { // задача CalcTree3
    ExpressionTree tree;
    std::string expression = chooseInput(true); // читаем выражение

    if (!tree.buildFromPostfix(expression)) {
        std::cout << "Некорректное выражение\n";
        return;
    }

    std::cout << "\nДерево до:\n";
    tree.printSideways(std::cout);

    std::cout << "Действие: заменяем умножение значением поддерева\n";
    tree.transformCalcTree3();

    std::cout << "Дерево после:\n";
    tree.printSideways(std::cout);
    std::cout << "Указатель на корень: " << tree.getRoot() << '\n';
    printTaskDone();
}

void runCalcTree25() { // задача CalcTree25
    ExpressionTree tree;
    std::string expression = chooseInput(false); // читаем выражение
    int xValue;
    std::string fileName;

    if (!tree.buildFromInfix(expression)) {
        std::cout << "Некорректное выражение\n";
        return;
    }

    std::cout << "x = ";
    std::cin >> xValue;

    std::cout << "Файл результата FN2: ";
    std::cin >> fileName;

    std::ofstream file(fileName); // файл вывода
    if (!file) {
        std::cout << "Файл результата не открылся\n";
        return;
    }

    int result = tree.calculate(xValue); // считаем ответ
    std::cout << "\nДерево до:\n";
    tree.printSideways(std::cout);
    std::cout << "Значение выражения: " << result << '\n';

    file << "Значение выражения: " << result << "\n\n";
    file << "Дерево до:\n";
    tree.printSideways(file);

    std::cout << "Действие: сворачиваем поддеревья без x\n";
    tree.transformCalcTree25(xValue);

    std::cout << "Дерево после:\n";
    tree.printSideways(std::cout);

    file << "\nДерево после:\n";
    tree.printSideways(file);

    std::cout << "Результат записан в файл\n";
    printTaskDone();
}
