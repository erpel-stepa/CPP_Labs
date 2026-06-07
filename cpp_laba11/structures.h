#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <iostream>
#include <fstream>
#include <string>

class TList;
class TListB;

// режим ввода
enum class InputMode {
    kKeyboard = 1,
    kFile = 2,
    kRandom = 3
};

// SNode
class SNode {
private:
    int data;
    SNode* next;

public:
    SNode(int value = 0);

    friend class SinglyCircularList;
};

// DCNode
class DCNode {
private:
    int data;
    DCNode* next;
    DCNode* prev;

public:
    DCNode(int value = 0);

    friend class DoublyCircularList;
};

// DLNode
class DLNode {
private:
    int data;
    DLNode* next;
    DLNode* prev;

public:
    DLNode(int value = 0);

    friend class TList;
    friend void ToFirst(TList& L);
    friend void ToNext(TList& L);
    friend void SetData(TList& L, int D);
    friend bool IsLast(const TList& L);
};

// BNode
class BNode {
private:
    int data;
    BNode* next;
    BNode* prev;

public:
    BNode(int value = 0);

    friend class TListB;
    friend void LBToFirst(TListB& L);
    friend void LBToNext(TListB& L);
    friend void LBSetData(TListB& L, int D);
    friend bool IsBarrier(const TListB& L);
};

// односвязное кольцо
class SinglyCircularList {
private:
    SNode* head;
    int size;

    void copyFrom(const SinglyCircularList& other);

public:
    SinglyCircularList();
    SinglyCircularList(const SinglyCircularList& other);
    SinglyCircularList& operator=(const SinglyCircularList& other);
    ~SinglyCircularList();

    bool isEmpty() const;
    int getSize() const;
    SNode* getHead() const;

    void clear();
    void pushBack(int value);
    bool removeByValue(int value);
    SNode* find(int value) const;
    void print() const;
    void printFromNode(SNode* start, int count) const;
    void fill(InputMode mode);

    void writeAndDeleteStep4(const std::string& fileName);
    void findLongestNegativeSequence() const;
};

// двусвязное кольцо
class DoublyCircularList {
private:
    DCNode* head;
    int size;

    void copyFrom(const DoublyCircularList& other);
    void removeNode(DCNode* node);

public:
    DoublyCircularList();
    DoublyCircularList(const DoublyCircularList& other);
    DoublyCircularList& operator=(const DoublyCircularList& other);
    ~DoublyCircularList();

    bool isEmpty() const;
    int getSize() const;
    DCNode* getHead() const;
    DCNode* getLast() const;

    void clear();
    void pushBack(int value);
    bool removeByValue(int value);
    DCNode* find(int value) const;
    void print() const;
    void fill(InputMode mode);

    DCNode* removeEqualNeighbors();
};

// тип TList
class TList {
private:
    DLNode* first;
    DLNode* last;
    DLNode* current;
    int size;

    void copyFrom(const TList& other);

public:
    TList();
    TList(const TList& other);
    TList& operator=(const TList& other);
    ~TList();

    bool isEmpty() const;
    int getSize() const;

    DLNode* getFirst() const;
    DLNode* getLast() const;
    DLNode* getCurrent() const;

    void clear();
    void insertLast(int value);
    bool removeByValue(int value);
    DLNode* find(int value) const;
    void print() const;
    void fill(InputMode mode);

    friend void ToFirst(TList& L);
    friend void ToNext(TList& L);
    friend void SetData(TList& L, int D);
    friend bool IsLast(const TList& L);
};

// тип TListB
class TListB {
private:
    BNode* barrier;
    BNode* current;
    int size;

    void copyFrom(const TListB& other);

public:
    TListB();
    TListB(const TListB& other);
    TListB& operator=(const TListB& other);
    ~TListB();

    bool isEmpty() const;
    int getSize() const;

    BNode* getBarrier() const;
    BNode* getCurrent() const;

    void clear();
    void insertLast(int value);
    bool removeByValue(int value);
    BNode* find(int value) const;
    void print() const;
    void fill(InputMode mode);

    friend void LBToFirst(TListB& L);
    friend void LBToNext(TListB& L);
    friend void LBSetData(TListB& L, int D);
    friend bool IsBarrier(const TListB& L);
};

// общие функции
InputMode ChooseInputMode();
int ReadSize();
void FillArrayFromKeyboard(int*& arr, int& n);
void FillArrayFromFile(int*& arr, int& n);
void FillArrayRandom(int*& arr, int& n);
void PrintArray(int* arr, int n);

// функции TList
void ToFirst(TList& L);
void ToNext(TList& L);
void SetData(TList& L, int D);
bool IsLast(const TList& L);

// функции TListB
void LBToFirst(TListB& L);
void LBToNext(TListB& L);
void LBSetData(TListB& L, int D);
bool IsBarrier(const TListB& L);

// запуск задач
void RunListWork68();
void RunListWork42();
void RunListWork45();
void RunListWork48();
void RunNegativeSequenceTask();

#endif