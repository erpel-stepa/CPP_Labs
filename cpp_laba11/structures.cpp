#include "structures.h"
#include <cstdlib>

// SNode
SNode::SNode(int value) {
    data = value;
    next = nullptr;
}

// DCNode
DCNode::DCNode(int value) {
    data = value;
    next = nullptr;
    prev = nullptr;
}

// DLNode
DLNode::DLNode(int value) {
    data = value;
    next = nullptr;
    prev = nullptr;
}

// BNode
BNode::BNode(int value) {
    data = value;
    next = nullptr;
    prev = nullptr;
}

// общие функции
InputMode ChooseInputMode() {
    int mode;

    std::cout << "\nВыберите способ ввода\n";
    std::cout << "1) С клавиатуры\n";
    std::cout << "2) Из файла\n";
    std::cout << "3) Случайно\n";
    std::cout << "Ваш выбор: ";
    std::cin >> mode;

    if (mode == 2) return InputMode::kFile;
    if (mode == 3) return InputMode::kRandom;
    return InputMode::kKeyboard;
}

int ReadSize() {
    int n;
    std::cout << "Введите количество элементов: ";
    std::cin >> n;

    while (n <= 0) {
        std::cout << "Число должно быть больше 0: ";
        std::cin >> n;
    }

    return n;
}

void FillArrayFromKeyboard(int*& arr, int& n) {
    n = ReadSize();
    arr = new int[n];

    std::cout << "Введите элементы:\n";
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }
}

void FillArrayFromFile(int*& arr, int& n) {
    std::string fileName;
    std::cout << "Введите имя файла: ";
    std::cin >> fileName;

    std::ifstream fin(fileName);
    if (!fin) {
        std::cout << "Файл не открыт\n";
        arr = nullptr;
        n = 0;
        return;
    }

    fin >> n;
    if (n <= 0) {
        std::cout << "Некорректный размер\n";
        arr = nullptr;
        n = 0;
        fin.close();
        return;
    }

    arr = new int[n];
    for (int i = 0; i < n; i++) {
        fin >> arr[i];
    }

    fin.close();
}

void FillArrayRandom(int*& arr, int& n) {
    n = ReadSize();
    arr = new int[n];

    int leftBorder;
    int rightBorder;

    std::cout << "Левая граница: ";
    std::cin >> leftBorder;
    std::cout << "Правая граница: ";
    std::cin >> rightBorder;

    if (leftBorder > rightBorder) {
        int temp = leftBorder;
        leftBorder = rightBorder;
        rightBorder = temp;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = leftBorder + rand() % (rightBorder - leftBorder + 1);
    }
}

void PrintArray(int* arr, int n) {
    if (arr == nullptr || n == 0) {
        std::cout << "Массив пуст\n";
        return;
    }

    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
}

// односвязное кольцо
SinglyCircularList::SinglyCircularList() {
    head = nullptr;
    size = 0;
}

SinglyCircularList::SinglyCircularList(const SinglyCircularList& other) {
    head = nullptr;
    size = 0;
    copyFrom(other);
}

SinglyCircularList& SinglyCircularList::operator=(const SinglyCircularList& other) {
    if (this != &other) {
        clear();
        copyFrom(other);
    }
    return *this;
}

SinglyCircularList::~SinglyCircularList() {
    clear();
}

void SinglyCircularList::copyFrom(const SinglyCircularList& other) {
    if (other.head == nullptr) {
        return;
    }

    SNode* p = other.head;
    for (int i = 0; i < other.size; i++) {
        pushBack(p->data);
        p = p->next;
    }
}

bool SinglyCircularList::isEmpty() const {
    return head == nullptr;
}

int SinglyCircularList::getSize() const {
    return size;
}

SNode* SinglyCircularList::getHead() const {
    return head;
}

void SinglyCircularList::clear() {
    if (head == nullptr) {
        return;
    }

    SNode* tail = head;
    while (tail->next != head) {
        tail = tail->next;
    }
    tail->next = nullptr;

    SNode* p = head;
    while (p != nullptr) {
        SNode* nextNode = p->next;
        delete p;
        p = nextNode;
    }

    head = nullptr;
    size = 0;
}

void SinglyCircularList::pushBack(int value) {
    SNode* node = new SNode(value);

    if (head == nullptr) {
        head = node;
        node->next = node;
        size++;
        return;
    }

    SNode* tail = head;
    while (tail->next != head) {
        tail = tail->next;
    }

    tail->next = node;
    node->next = head;
    size++;
}

bool SinglyCircularList::removeByValue(int value) {
    if (head == nullptr) {
        return false;
    }

    SNode* current = head;
    SNode* prev = head;
    while (prev->next != head) {
        prev = prev->next;
    }

    do {
        if (current->data == value) {
            if (size == 1) {
                delete current;
                head = nullptr;
                size = 0;
                return true;
            }

            if (current == head) {
                head = head->next;
            }

            prev->next = current->next;
            delete current;
            size--;
            return true;
        }

        prev = current;
        current = current->next;
    } while (current != head);

    return false;
}

SNode* SinglyCircularList::find(int value) const {
    if (head == nullptr) {
        return nullptr;
    }

    SNode* p = head;
    do {
        if (p->data == value) {
            return p;
        }
        p = p->next;
    } while (p != head);

    return nullptr;
}

void SinglyCircularList::print() const {
    if (head == nullptr) {
        std::cout << "Список пуст\n";
        return;
    }

    SNode* p = head;
    do {
        std::cout << p->data << " ";
        p = p->next;
    } while (p != head);

    std::cout << "\n";
}

void SinglyCircularList::printFromNode(SNode* start, int count) const {
    if (start == nullptr || count <= 0) {
        std::cout << "Нет элементов\n";
        return;
    }

    SNode* p = start;
    for (int i = 0; i < count; i++) {
        std::cout << p->data << " ";
        p = p->next;
    }
    std::cout << "\n";
}

void SinglyCircularList::fill(InputMode mode) {
    clear();

    int* arr = nullptr;
    int n = 0;

    if (mode == InputMode::kKeyboard) {
        FillArrayFromKeyboard(arr, n);
    } else if (mode == InputMode::kFile) {
        FillArrayFromFile(arr, n);
    } else {
        FillArrayRandom(arr, n);
    }

    if (arr == nullptr || n == 0) {
        return;
    }

    std::cout << "Получены элементы: ";
    PrintArray(arr, n);

    for (int i = 0; i < n; i++) {
        pushBack(arr[i]);
    }

    delete[] arr;
}

void SinglyCircularList::writeAndDeleteStep4(const std::string& fileName) {
    std::ofstream fout(fileName);
    if (!fout) {
        std::cout << "Не удалось открыть файл\n";
        return;
    }

    if (head == nullptr) {
        std::cout << "Список пуст\n";
        fout.close();
        return;
    }

    std::cout << "\nИсходное кольцо:\n";
    print();

    SNode* current = head;
    SNode* prev = head;
    while (prev->next != head) {
        prev = prev->next;
    }

    std::cout << "\nПорядок вывода и удаления:\n";

    while (size > 0) {
        std::cout << current->data << " ";
        fout << current->data << " ";

        if (size == 1) {
            delete current;
            head = nullptr;
            size = 0;
            break;
        }

        SNode* nextNode = current->next;

        if (current == head) {
            head = head->next;
        }

        prev->next = current->next;
        delete current;
        size--;

        current = nextNode;

        for (int step = 0; step < 3; step++) {
            prev = current;
            current = current->next;
        }
    }

    std::cout << "\n";
    fout.close();
    std::cout << "Запись сделана в файл: " << fileName << "\n";
}

void SinglyCircularList::findLongestNegativeSequence() const {
    if (head == nullptr) {
        std::cout << "Список пуст\n";
        return;
    }

    std::cout << "\nИсходное кольцо:\n";
    print();

    bool allNegative = true;
    SNode* q = head;
    do {
        if (q->data >= 0) {
            allNegative = false;
            break;
        }
        q = q->next;
    } while (q != head);

    if (allNegative) {
        std::cout << "Максимальная цепочка:\n";
        print();
        std::cout << "Длина: " << size << "\n";
        return;
    }

    SNode* bestStart = nullptr;
    int bestLen = 0;

    SNode* currentStart = nullptr;
    int currentLen = 0;

    SNode* p = head;
    for (int i = 0; i < size * 2; i++) {
        if (p->data < 0) {
            if (currentLen == 0) {
                currentStart = p;
            }

            currentLen++;

            if (currentLen > size) {
                currentLen = size;
            }

            if (currentLen > bestLen) {
                bestLen = currentLen;
                bestStart = currentStart;
            }
        } else {
            currentLen = 0;
            currentStart = nullptr;
        }

        p = p->next;
    }

    if (bestLen == 0) {
        std::cout << "Отрицательных цепочек нет\n";
        return;
    }

    std::cout << "Максимальная цепочка:\n";
    printFromNode(bestStart, bestLen);
    std::cout << "Длина: " << bestLen << "\n";
}

// двусвязное кольцо
DoublyCircularList::DoublyCircularList() {
    head = nullptr;
    size = 0;
}

DoublyCircularList::DoublyCircularList(const DoublyCircularList& other) {
    head = nullptr;
    size = 0;
    copyFrom(other);
}

DoublyCircularList& DoublyCircularList::operator=(const DoublyCircularList& other) {
    if (this != &other) {
        clear();
        copyFrom(other);
    }
    return *this;
}

DoublyCircularList::~DoublyCircularList() {
    clear();
}

void DoublyCircularList::copyFrom(const DoublyCircularList& other) {
    if (other.head == nullptr) {
        return;
    }

    DCNode* p = other.head;
    for (int i = 0; i < other.size; i++) {
        pushBack(p->data);
        p = p->next;
    }
}

bool DoublyCircularList::isEmpty() const {
    return head == nullptr;
}

int DoublyCircularList::getSize() const {
    return size;
}

DCNode* DoublyCircularList::getHead() const {
    return head;
}

DCNode* DoublyCircularList::getLast() const {
    if (head == nullptr) {
        return nullptr;
    }
    return head->prev;
}

void DoublyCircularList::clear() {
    if (head == nullptr) {
        return;
    }

    DCNode* p = head->next;
    while (p != head) {
        DCNode* nextNode = p->next;
        delete p;
        p = nextNode;
    }

    delete head;
    head = nullptr;
    size = 0;
}

void DoublyCircularList::pushBack(int value) {
    DCNode* node = new DCNode(value);

    if (head == nullptr) {
        head = node;
        node->next = node;
        node->prev = node;
        size++;
        return;
    }

    DCNode* last = head->prev;
    last->next = node;
    node->prev = last;
    node->next = head;
    head->prev = node;
    size++;
}

void DoublyCircularList::removeNode(DCNode* node) {
    if (node == nullptr || head == nullptr) {
        return;
    }

    if (size == 1) {
        delete node;
        head = nullptr;
        size = 0;
        return;
    }

    node->prev->next = node->next;
    node->next->prev = node->prev;

    if (node == head) {
        head = node->next;
    }

    delete node;
    size--;
}

bool DoublyCircularList::removeByValue(int value) {
    if (head == nullptr) {
        return false;
    }

    DCNode* p = head;
    do {
        if (p->data == value) {
            removeNode(p);
            return true;
        }
        p = p->next;
    } while (p != head);

    return false;
}

DCNode* DoublyCircularList::find(int value) const {
    if (head == nullptr) {
        return nullptr;
    }

    DCNode* p = head;
    do {
        if (p->data == value) {
            return p;
        }
        p = p->next;
    } while (p != head);

    return nullptr;
}

void DoublyCircularList::print() const {
    if (head == nullptr) {
        std::cout << "Список пуст\n";
        return;
    }

    DCNode* p = head;
    do {
        std::cout << p->data << " ";
        p = p->next;
    } while (p != head);

    std::cout << "\n";
}

void DoublyCircularList::fill(InputMode mode) {
    clear();

    int* arr = nullptr;
    int n = 0;

    if (mode == InputMode::kKeyboard) {
        FillArrayFromKeyboard(arr, n);
    } else if (mode == InputMode::kFile) {
        FillArrayFromFile(arr, n);
    } else {
        FillArrayRandom(arr, n);
    }

    if (arr == nullptr || n == 0) {
        return;
    }

    std::cout << "Получены элементы: ";
    PrintArray(arr, n);

    for (int i = 0; i < n; i++) {
        pushBack(arr[i]);
    }

    delete[] arr;
}

DCNode* DoublyCircularList::removeEqualNeighbors() {
    if (head == nullptr) {
        std::cout << "Список пуст\n";
        return nullptr;
    }

    std::cout << "\nИсходный список:\n";
    print();

    int originalSize = size;
    bool* mark = new bool[originalSize];

    for (int i = 0; i < originalSize; i++) {
        mark[i] = false;
    }

    DCNode* p = head;
    for (int i = 0; i < originalSize; i++) {
        if (p->prev->data == p->next->data) {
            mark[i] = true;
        }
        p = p->next;
    }

    bool changed = false;
    p = head;

    for (int i = 0; i < originalSize; i++) {
        DCNode* nextNode = p->next;
        if (mark[i]) {
            removeNode(p);
            changed = true;
            if (head == nullptr) {
                break;
            }
        }
        p = nextNode;
        if (head == nullptr) {
            break;
        }
    }

    delete[] mark;

    if (!changed) {
        std::cout << "Подходящих элементов нет\n";
    }

    std::cout << "Список после обработки:\n";
    print();
    std::cout << "Адрес последнего элемента: " << getLast() << "\n";

    return getLast();
}

// тип TList
TList::TList() {
    first = nullptr;
    last = nullptr;
    current = nullptr;
    size = 0;
}

TList::TList(const TList& other) {
    first = nullptr;
    last = nullptr;
    current = nullptr;
    size = 0;
    copyFrom(other);
}

TList& TList::operator=(const TList& other) {
    if (this != &other) {
        clear();
        copyFrom(other);
    }
    return *this;
}

TList::~TList() {
    clear();
}

void TList::copyFrom(const TList& other) {
    if (other.first == nullptr) {
        return;
    }

    DLNode* p = other.first;
    DLNode* savedCurrent = other.current;

    while (p != nullptr) {
        insertLast(p->data);
        if (p == savedCurrent) {
            current = last;
        }
        p = p->next;
    }
}

bool TList::isEmpty() const {
    return first == nullptr;
}

int TList::getSize() const {
    return size;
}

DLNode* TList::getFirst() const {
    return first;
}

DLNode* TList::getLast() const {
    return last;
}

DLNode* TList::getCurrent() const {
    return current;
}

void TList::clear() {
    DLNode* p = first;
    while (p != nullptr) {
        DLNode* nextNode = p->next;
        delete p;
        p = nextNode;
    }

    first = nullptr;
    last = nullptr;
    current = nullptr;
    size = 0;
}

void TList::insertLast(int value) {
    DLNode* node = new DLNode(value);

    if (first == nullptr) {
        first = node;
        last = node;
        current = node;
        size++;
        return;
    }

    last->next = node;
    node->prev = last;
    last = node;
    current = node;
    size++;
}

bool TList::removeByValue(int value) {
    DLNode* p = first;

    while (p != nullptr) {
        if (p->data == value) {
            if (p->prev != nullptr) {
                p->prev->next = p->next;
            } else {
                first = p->next;
            }

            if (p->next != nullptr) {
                p->next->prev = p->prev;
            } else {
                last = p->prev;
            }

            if (current == p) {
                if (p->next != nullptr) {
                    current = p->next;
                } else {
                    current = last;
                }
            }

            delete p;
            size--;

            if (size == 0) {
                first = nullptr;
                last = nullptr;
                current = nullptr;
            }

            return true;
        }
        p = p->next;
    }

    return false;
}

DLNode* TList::find(int value) const {
    DLNode* p = first;

    while (p != nullptr) {
        if (p->data == value) {
            return p;
        }
        p = p->next;
    }

    return nullptr;
}

void TList::print() const {
    if (first == nullptr) {
        std::cout << "Список пуст\n";
        return;
    }

    DLNode* p = first;
    while (p != nullptr) {
        std::cout << p->data << " ";
        p = p->next;
    }
    std::cout << "\n";
}

void TList::fill(InputMode mode) {
    clear();

    int* arr = nullptr;
    int n = 0;

    if (mode == InputMode::kKeyboard) {
        FillArrayFromKeyboard(arr, n);
    } else if (mode == InputMode::kFile) {
        FillArrayFromFile(arr, n);
    } else {
        FillArrayRandom(arr, n);
    }

    if (arr == nullptr || n == 0) {
        return;
    }

    std::cout << "Получены элементы: ";
    PrintArray(arr, n);

    for (int i = 0; i < n; i++) {
        insertLast(arr[i]);
    }

    delete[] arr;
}

// функции TList
void ToFirst(TList& L) {
    L.current = L.first;
}

void ToNext(TList& L) {
    if (L.current != nullptr && L.current->next != nullptr) {
        L.current = L.current->next;
    }
}

void SetData(TList& L, int D) {
    if (L.current != nullptr) {
        L.current->data = D;
    }
}

bool IsLast(const TList& L) {
    return L.current == L.last;
}

// тип TListB (тут задается барьер)
TListB::TListB() {
    barrier = new BNode(0);
    barrier->next = barrier;
    barrier->prev = barrier;
    current = barrier;
    size = 0;
}

TListB::TListB(const TListB& other) {
    barrier = new BNode(0);
    barrier->next = barrier;
    barrier->prev = barrier;
    current = barrier;
    size = 0;
    copyFrom(other);
}

TListB& TListB::operator=(const TListB& other) {
    if (this != &other) {
        clear();
        copyFrom(other);
    }
    return *this;
}

TListB::~TListB() {
    clear();
    delete barrier;
    barrier = nullptr;
    current = nullptr;
}

void TListB::copyFrom(const TListB& other) {
    BNode* p = other.barrier->next;

    while (p != other.barrier) {
        insertLast(p->data);
        p = p->next;
    }

    if (other.current == other.barrier) {
        current = barrier;
        return;
    }

    int pos = 0;
    int needPos = 0;
    p = other.barrier->next;

    while (p != other.barrier) {
        pos++;
        if (p == other.current) {
            needPos = pos;
            break;
        }
        p = p->next;
    }

    current = barrier->next;
    for (int i = 1; i < needPos; i++) {
        current = current->next;
    }
}

bool TListB::isEmpty() const {
    return size == 0;
}

int TListB::getSize() const {
    return size;
}

BNode* TListB::getBarrier() const {
    return barrier;
}

BNode* TListB::getCurrent() const {
    return current;
}

void TListB::clear() {
    BNode* p = barrier->next;
    while (p != barrier) {
        BNode* nextNode = p->next;
        delete p;
        p = nextNode;
    }

    barrier->next = barrier;
    barrier->prev = barrier;
    current = barrier;
    size = 0;
}

void TListB::insertLast(int value) {
    BNode* node = new BNode(value);
    BNode* last = barrier->prev;

    last->next = node;
    node->prev = last;
    node->next = barrier;
    barrier->prev = node;

    if (barrier->next == barrier) {
        barrier->next = node;
    }

    current = node;
    size++;
}

bool TListB::removeByValue(int value) {
    BNode* p = barrier->next;

    while (p != barrier) {
        if (p->data == value) {
            p->prev->next = p->next;
            p->next->prev = p->prev;

            if (barrier->next == p) {
                barrier->next = p->next;
            }

            if (barrier->prev == p) {
                barrier->prev = p->prev;
            }

            if (current == p) {
                current = p->next;
            }

            delete p;
            size--;

            if (size == 0) {
                barrier->next = barrier;
                barrier->prev = barrier;
                current = barrier;
            }

            return true;
        }

        p = p->next;
    }

    return false;
}

BNode* TListB::find(int value) const {
    BNode* p = barrier->next;

    while (p != barrier) {
        if (p->data == value) {
            return p;
        }
        p = p->next;
    }

    return nullptr;
}

void TListB::print() const {
    if (size == 0) {
        std::cout << "Список пуст\n";
        return;
    }

    BNode* p = barrier->next;
    while (p != barrier) {
        std::cout << p->data << " ";
        p = p->next;
    }
    std::cout << barrier->data << std::endl;
    std::cout << "\n";

}

void TListB::fill(InputMode mode) {
    clear();

    int* arr = nullptr;
    int n = 0;

    if (mode == InputMode::kKeyboard) {
        FillArrayFromKeyboard(arr, n);
    } else if (mode == InputMode::kFile) {
        FillArrayFromFile(arr, n);
    } else {
        FillArrayRandom(arr, n);
    }

    if (arr == nullptr || n == 0) {
        return;
    }

    std::cout << "Получены элементы: ";
    PrintArray(arr, n);

    for (int i = 0; i < n; i++) {
        insertLast(arr[i]);
    }

    delete[] arr;
}

// функции TListB
void LBToFirst(TListB& L) {
    L.current = L.barrier->next;
}

void LBToNext(TListB& L) {
    if (L.current != nullptr) {
        L.current = L.current->next;
    }
}

void LBSetData(TListB& L, int D) {
    if (L.current != L.barrier) {
        L.current->data = D;
    }
}

bool IsBarrier(const TListB& L) {
    return L.current == L.barrier;
}

// запуск задач
void RunListWork68() {
    std::cout << "\nListWork68\n";

    SinglyCircularList list;
    InputMode mode = ChooseInputMode();
    list.fill(mode);

    if (list.isEmpty()) {
        std::cout << "Список пуст\n";
        return;
    }

    std::string fileName;
    std::cout << "Введите имя выходного файла: ";
    std::cin >> fileName;

    list.writeAndDeleteStep4(fileName);

    std::cout << "\nБазовые операции на отдельной копии\n";
    SinglyCircularList demo;
    demo.fill(mode);

    if (!demo.isEmpty()) {
        std::cout << "Список: ";
        demo.print();

        int value;
        std::cout << "Что найти: ";
        std::cin >> value;
        if (demo.find(value) != nullptr) {
            std::cout << "Элемент найден\n";
        } else {
            std::cout << "Элемент не найден\n";
        }

        std::cout << "Что добавить в конец: ";
        std::cin >> value;
        demo.pushBack(value);
        std::cout << "После добавления: ";
        demo.print();

        std::cout << "Что удалить: ";
        std::cin >> value;
        if (demo.removeByValue(value)) {
            std::cout << "После удаления: ";
            demo.print();
        } else {
            std::cout << "Такого элемента нет\n";
        }
    }
}

void RunListWork42() {
    std::cout << "\nListWork42\n";

    DoublyCircularList list;
    InputMode mode = ChooseInputMode();
    list.fill(mode);

    if (list.isEmpty()) {
        std::cout << "Список пуст\n";
        return;
    }

    list.removeEqualNeighbors();

    std::cout << "\nБазовые операции на новой копии\n";
    DoublyCircularList demo;
    demo.fill(mode);

    if (!demo.isEmpty()) {
        std::cout << "Список: ";
        demo.print();

        int value;
        std::cout << "Что найти: ";
        std::cin >> value;
        if (demo.find(value) != nullptr) {
            std::cout << "Элемент найден\n";
        } else {
            std::cout << "Элемент не найден\n";
        }

        std::cout << "Что добавить в конец: ";
        std::cin >> value;
        demo.pushBack(value);
        std::cout << "После добавления: ";
        demo.print();

        std::cout << "Что удалить: ";
        std::cin >> value;
        if (demo.removeByValue(value)) {
            std::cout << "После удаления: ";
            demo.print();
        } else {
            std::cout << "Такого элемента нет\n";
        }
    }
}

void RunListWork45() {
    std::cout << "\nListWork45\n";

    TList list;
    InputMode mode = ChooseInputMode();
    list.fill(mode);

    if (list.isEmpty()) {
        std::cout << "Список пуст\n";
        return;
    }

    std::cout << "\nИсходный список:\n";
    list.print();

    ToFirst(list);
    int count = 0;
    int number = 1;

    while (list.getCurrent() != nullptr) {
        count++;

        if (number % 2 != 0) {
            SetData(list, 0);
        }

        if (IsLast(list)) {
            break;
        }

        ToNext(list);
        number++;
    }

    std::cout << "После обнуления нечетных позиций:\n";
    list.print();
    std::cout << "Количество элементов: " << count << "\n";
    std::cout << "Адрес первого: " << list.getFirst() << "\n";
    std::cout << "Адрес последнего: " << list.getLast() << "\n";
    std::cout << "Адрес текущего: " << list.getCurrent() << "\n";

    std::cout << "\nБазовые операции на новой копии\n";
    TList demo;
    demo.fill(mode);

    if (!demo.isEmpty()) {
        std::cout << "Список: ";
        demo.print();

        int value;
        std::cout << "Что найти: ";
        std::cin >> value;
        if (demo.find(value) != nullptr) {
            std::cout << "Элемент найден\n";
        } else {
            std::cout << "Элемент не найден\n";
        }

        std::cout << "Что добавить в конец: ";
        std::cin >> value;
        demo.insertLast(value);
        std::cout << "После добавления: ";
        demo.print();

        std::cout << "Что удалить: ";
        std::cin >> value;
        if (demo.removeByValue(value)) {
            std::cout << "После удаления: ";
            demo.print();
        } else {
            std::cout << "Такого элемента нет\n";
        }
    }
}

void RunListWork48() {
    std::cout << "\nListWork48\n";

    TListB list;
    InputMode mode = ChooseInputMode();
    list.fill(mode);

    if (list.isEmpty()) {
        std::cout << "Список пуст\n";
        return;
    }

    std::cout << "\nИсходный список:\n";
    list.print();

    LBToFirst(list);
    int count = 0;
    int number = 1;

    while (!IsBarrier(list)) {
        count++;

        if (number % 2 != 0) {
            LBSetData(list, 0);
        }

        LBToNext(list);
        number++;
    }

    std::cout << "После обнуления нечетных позиций:\n";
    list.print();
    std::cout << "Количество элементов: " << count << "\n";
    std::cout << "Адрес текущего элемента: " << list.getCurrent() << "\n";
    std::cout << "Адрес барьерного элемента: " << list.getBarrier() << "\n";

    std::cout << "\nБазовые операции на новой копии\n";
    TListB demo;
    demo.fill(mode);

    if (!demo.isEmpty()) {
        std::cout << "Список: ";
        demo.print();

        int value;
        std::cout << "Что найти: ";
        std::cin >> value;
        if (demo.find(value) != nullptr) {
            std::cout << "Элемент найден\n";
        } else {
            std::cout << "Элемент не найден\n";
        }

        std::cout << "Что добавить в конец: ";
        std::cin >> value;
        demo.insertLast(value);
        std::cout << "После добавления: ";
        demo.print();

        std::cout << "Что удалить: ";
        std::cin >> value;
        if (demo.removeByValue(value)) {
            std::cout << "После удаления: ";
            demo.print();
        } else {
            std::cout << "Такого элемента нет\n";
        }
    }
}

void RunNegativeSequenceTask() {
    std::cout << "\nЗадача 3\n";

    SinglyCircularList list;
    InputMode mode = ChooseInputMode();
    list.fill(mode);

    if (list.isEmpty()) {
        std::cout << "Список пуст\n";
        return;
    }

    list.findLongestNegativeSequence();

    std::cout << "\nБазовые операции на новой копии\n";
    SinglyCircularList demo;
    demo.fill(mode);

    if (!demo.isEmpty()) {
        std::cout << "Список: ";
        demo.print();

        int value;
        std::cout << "Что найти: ";
        std::cin >> value;
        if (demo.find(value) != nullptr) {
            std::cout << "Элемент найден\n";
        } else {
            std::cout << "Элемент не найден\n";
        }

        std::cout << "Что добавить в конец: ";
        std::cin >> value;
        demo.pushBack(value);
        std::cout << "После добавления: ";
        demo.print();

        std::cout << "Что удалить: ";
        std::cin >> value;
        if (demo.removeByValue(value)) {
            std::cout << "После удаления: ";
            demo.print();
        } else {
            std::cout << "Такого элемента нет\n";
        }
    }
}