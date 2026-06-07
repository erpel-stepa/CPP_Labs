#ifndef MODULE_H
#define MODULE_H

#include <iosfwd>
#include <string>

class Node {
private:
    int value; // значение узла
    bool variable; // флаг x
    Node* left; // левый потомок
    Node* right; // правый потомок

public:
    Node();
    Node(int value, bool variable = false);
    Node(const Node& other);
    Node& operator=(const Node& other);
    ~Node();

    int getValue() const;
    bool isVariable() const;
    Node* getLeft() const;
    Node* getRight() const;

    void setValue(int value);
    void setVariable(bool variable);
    void setLeft(Node* left);
    void setRight(Node* right);
};

class Validator {
public:
    Validator();
    Validator(const Validator& other);
    Validator& operator=(const Validator& other);
    ~Validator();

    bool isDigitOperand(char symbol) const;
    bool isNumber(const std::string& text) const;
    bool isOperator(char symbol) const;
    bool isBinaryOperator(int code) const;
    bool checkPostfix(const std::string& expression) const;
    bool checkInfix(const std::string& expression) const;
};

class ExpressionTree {
private:
    Node* root; // начало дерева
    Validator validator; // объект проверок

    Node* copyTree(Node* node) const; // копия ветки
    void clear(Node* node); // удалить ветку
    int priority(char operation) const; // приоритет операции
    int operationCode(char operation) const; // операция в число
    char operationSymbol(int code) const; // число в операцию
    bool containsVariable(Node* node) const; // поиск переменной
    int calculate(Node* node, int xValue) const; // расчет ветки
    void printSideways(Node* node, int level, std::ostream& out) const; // вывод боком
    void replaceMultiplication(Node* node); // убрать умножение
    void replaceConstants(Node* node, int xValue); // свернуть числа
    std::string readToken(const std::string& expression, int& index) const; // взять токен

public:
    ExpressionTree();
    ExpressionTree(const ExpressionTree& other);
    ExpressionTree& operator=(const ExpressionTree& other);
    ~ExpressionTree();

    Node* getRoot() const;
    void clear();
    bool buildFromPostfix(const std::string& expression);
    bool buildFromInfix(const std::string& expression);
    int calculate(int xValue = 0) const;
    void printSideways(std::ostream& out) const;
    void transformCalcTree3();
    void transformCalcTree25(int xValue);
};

void runCalcTree3();
void runCalcTree25();

#endif
