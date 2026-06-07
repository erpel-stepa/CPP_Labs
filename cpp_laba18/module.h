#ifndef MODULE_H
#define MODULE_H

#include <iostream>
#include <string>
#include <vector>

class Node {
private:
    int value;       // число в узле
    Node* left;      // левый/prev
    Node* right;     // правый/next
    Node* parent;    // родитель для итератора

public:
    Node();
    explicit Node(int value);
    Node(const Node& other);
    Node& operator=(const Node& other);
    ~Node();

    int getValue() const;
    Node* getLeft() const;
    Node* getRight() const;
    Node* getParent() const;
    void setValue(int value);
    void setLeft(Node* node);
    void setRight(Node* node);
    void setParent(Node* node);
};

class Checks {
public:
    Checks();
    Checks(const Checks& other);
    Checks& operator=(const Checks& other);
    ~Checks();

    static void clearInput();
    static int readInt(const std::string& text);
    static int readMenuChoice(int minValue, int maxValue);
    static bool readValuesFromFile(const std::string& fileName, std::vector<int>& values);
    static std::vector<int> readValuesByChoice();
};

class BinaryTree {
private:
    Node* root;      // корень дерева

    Node* copyNodes(Node* node) const;                // копия ветки
    void clear(Node* node);                           // удалить ветку
    void printTree(Node* node, int level) const;      // печать боком
    void insertBst(Node*& node, int value);           // вставка в BST
    void addLevelNode(int value);                     // вставка по уровню
    int countNodes(Node* node) const;                 // размер ветки
    Node* makeList(Node* node, Node*& previous);      // дерево в список
    std::string subtreeCode(Node* node, std::vector<Node*>& nodes,
                            std::vector<std::string>& codes,
                            std::vector<int>& sizes) const; // код ветки
    bool containsNode(Node* node, Node* target) const;       // есть ли узел
    void detachNode(Node*& current, Node* target);           // отцепить ветку

public:
    BinaryTree();
    BinaryTree(const BinaryTree& other);
    BinaryTree& operator=(const BinaryTree& other);
    ~BinaryTree();

    Node* getRoot() const;
    bool isEmpty() const;
    void clearTree();
    void buildAsBst(const std::vector<int>& values);
    void buildAsCommonTree(const std::vector<int>& values);
    void printGraphic() const;
    Node* convertBstToList();
    int removeDuplicateSubtrees();
};

class DoublyList {
private:
    Node* head;      // начало списка

public:
    DoublyList();
    explicit DoublyList(Node* head);
    DoublyList(const DoublyList& other);
    DoublyList& operator=(const DoublyList& other);
    ~DoublyList();

    void setHead(Node* head);
    void printList() const;
};

class PostOrderIterator {
private:
    const Node* root;               // корень обхода
    const Node* current;            // следующий узел

    const Node* firstPostOrderNode(const Node* node) const;
    void moveToNext();

public:
    PostOrderIterator();
    explicit PostOrderIterator(const Node* root);
    PostOrderIterator(const PostOrderIterator& other);
    PostOrderIterator& operator=(const PostOrderIterator& other);
    ~PostOrderIterator();

    bool hasNext() const;
    int next();
};

void runTreeFun1();
void runTreeFun5();
void runTreeFun13();

#endif
