#include "module.h"

#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <iomanip>
#include <limits>
#include <map>
#include <vector>

// символы UTF-8
static std::vector<std::string> splitUtf8(const std::string& text) {
    std::vector<std::string> symbols;
    for (int i = 0; i < static_cast<int>(text.size());) {
        unsigned char current = static_cast<unsigned char>(text[i]);
        int length = 1;
        if ((current & 0xE0) == 0xC0) {
            length = 2;
        } else if ((current & 0xF0) == 0xE0) {
            length = 3;
        } else if ((current & 0xF8) == 0xF0) {
            length = 4;
        }
        symbols.push_back(text.substr(i, length));
        i += length;
    }
    return symbols;
}

// печать списка
static void printWeightList(const std::vector<std::pair<std::pair<std::string, std::string>, int>>& items, int total) {
    for (const auto& item : items) {
        std::cout << item.first.first << "=" << std::fixed << std::setprecision(2)
                  << static_cast<double>(item.second) / total << " ";
    }
    std::cout << "\n";
}

// пустой кодер
HammingCoder::HammingCoder() {
    message = "";
    code = "";
    parityCount = 0;
}

// копия кодера
HammingCoder::HammingCoder(const HammingCoder& other) {
    message = other.message;
    code = other.code;
    parityCount = other.parityCount;
}

// присваивание кодера
HammingCoder& HammingCoder::operator=(const HammingCoder& other) {
    if (this != &other) {
        message = other.message;
        code = other.code;
        parityCount = other.parityCount;
    }
    return *this;
}

// пустой деструктор
HammingCoder::~HammingCoder() {
}

// степень двойки
bool HammingCoder::isPowerOfTwo(int number) const {
    return number > 0 && (number & (number - 1)) == 0;
}

// синдром ошибки
int HammingCoder::calculateSyndrome(const std::string& receivedCode) const {
    int totalCount = static_cast<int>(receivedCode.size());
    int syndrome = 0;

    for (int parity = 1; parity <= totalCount; parity <<= 1) {
        int sum = 0;
        for (int position = 1; position <= totalCount; ++position) {
            if ((position & parity) != 0) {
                sum ^= receivedCode[position - 1] - '0';
            }
        }
        if (sum != 0) {
            syndrome += parity;
        }
    }

    return syndrome;
}

// исправление одного ошибочного бита
std::string HammingCoder::correctCode(const std::string& receivedCode, int syndrome) const {
    std::string correctedCode = receivedCode;

    if (syndrome >= 1 && syndrome <= static_cast<int>(correctedCode.size())) {
        correctedCode[syndrome - 1] = correctedCode[syndrome - 1] == '0' ? '1' : '0';
    }

    return correctedCode;
}

// задать сообщение
void HammingCoder::setMessage(const std::string& newMessage) {
    message = newMessage;
    code = "";
    parityCount = 0;
}

// строим код
void HammingCoder::buildCode() {
    int dataCount = static_cast<int>(message.size());
    parityCount = 0;

    while ((1 << parityCount) < dataCount + parityCount + 1) {
        ++parityCount;
    }

    int totalCount = dataCount + parityCount;
    std::vector<int> bits(totalCount + 1, 0);
    int dataIndex = 0;

    for (int position = 1; position <= totalCount; ++position) {
        if (!isPowerOfTwo(position)) {
            bits[position] = message[dataIndex] - '0';
            ++dataIndex;
        }
    }

    for (int parity = 1; parity <= totalCount; parity <<= 1) {
        int sum = 0;
        for (int position = 1; position <= totalCount; ++position) {
            if ((position & parity) != 0) {
                sum ^= bits[position];
            }
        }
        bits[parity] = sum;
    }

    code = "";
    for (int position = 1; position <= totalCount; ++position) {
        code += static_cast<char>('0' + bits[position]);
    }
}

// печать решения
void HammingCoder::printSolution() const {
    int totalCount = static_cast<int>(code.size());

    std::cout << "Сообщение: " << message << "\n";
    std::cout << "Информационных битов: " << message.size() << "\n";
    std::cout << "Контрольных битов: " << parityCount << "\n";
    std::cout << "Позиции контроля: ";
    bool firstParity = true;
    for (int parity = 1; parity <= totalCount; parity <<= 1) {
        if (!firstParity) {
            std::cout << ", ";
        }
        std::cout << parity;
        firstParity = false;
    }
    std::cout << "\n";
    std::cout << "Код Хемминга: " << code << "\n\n";

    std::cout << "Построение вручную:\n";
    std::cout << "1) На позиции степеней двойки ставим контрольные биты.\n";
    std::cout << "2) Остальные позиции заполняем исходным сообщением слева направо.\n";
    std::cout << "3) Контрольные биты считаем по четности.\n\n";

    std::cout << "pos: ";
    for (int i = 1; i <= totalCount; ++i) {
        std::cout << std::setw(2) << i << " ";
    }
    std::cout << "\nbit: ";
    for (char bit : code) {
        std::cout << std::setw(2) << bit << " ";
    }
    std::cout << "\n";

    int errorPosition;
    std::cout << "\nВведите позицию бита, в котором имитировать ошибку (1-"<< totalCount << "): ";
    while (!(std::cin >> errorPosition) || errorPosition < 1 || errorPosition > totalCount) {
        std::cout << "Нужно ввести число от 1 до " << totalCount << ": ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::string receivedCode = code;
    receivedCode[errorPosition - 1] = receivedCode[errorPosition - 1] == '0' ? '1' : '0';

    int syndrome = calculateSyndrome(receivedCode);
    std::string correctedCode = correctCode(receivedCode, syndrome);

    std::cout << "\nИсправление ошибки по синдрому:\n";
    std::cout << "Принятый код с ошибкой в позиции " << errorPosition << ": " << receivedCode << "\n";
    std::cout << "Синдром: " << syndrome << "\n";
    if (syndrome == 0) {
        std::cout << "Ошибки не обнаружены.\n";
    } else {
        std::cout << "Ошибка найдена в позиции " << syndrome << ". Инвертируем этот бит.\n";
    }
    std::cout << "Исправленный код: " << correctedCode << "\n";
}

// лист дерева
HuffmanCoder::Node::Node(const std::string& newSymbol, int newFrequency) {
    symbol = newSymbol;
    frequency = newFrequency;
    left = nullptr;
    right = nullptr;
}

// общий узел
HuffmanCoder::Node::Node(Node* leftNode, Node* rightNode) {
    symbol = leftNode->symbol + rightNode->symbol;
    frequency = leftNode->frequency + rightNode->frequency;
    left = leftNode;
    right = rightNode;
}

// копия узла
HuffmanCoder::Node::Node(const Node& other) {
    symbol = other.symbol;
    frequency = other.frequency;
    left = other.left == nullptr ? nullptr : new Node(*other.left);
    right = other.right == nullptr ? nullptr : new Node(*other.right);
}

// присваивание узла
HuffmanCoder::Node& HuffmanCoder::Node::operator=(const Node& other) {
    if (this != &other) {
        delete left;
        delete right;
        symbol = other.symbol;
        frequency = other.frequency;
        left = other.left == nullptr ? nullptr : new Node(*other.left);
        right = other.right == nullptr ? nullptr : new Node(*other.right);
    }
    return *this;
}

// удалить узел
HuffmanCoder::Node::~Node() {
    delete left;
    delete right;
}

// взять символ
std::string HuffmanCoder::Node::getSymbol() const {
    return symbol;
}

// взять частоту
int HuffmanCoder::Node::getFrequency() const {
    return frequency;
}

// левый сын
HuffmanCoder::Node* HuffmanCoder::Node::getLeft() const {
    return left;
}

// правый сын
HuffmanCoder::Node* HuffmanCoder::Node::getRight() const {
    return right;
}

// проверка листа
bool HuffmanCoder::Node::isLeaf() const {
    return left == nullptr && right == nullptr;
}

// пустой кодер
HuffmanCoder::HuffmanCoder() {
    text = "";
    root = nullptr;
}

// копия кодера
HuffmanCoder::HuffmanCoder(const HuffmanCoder& other) {
    root = nullptr;
    copyFrom(other);
}

// присваивание кодера
HuffmanCoder& HuffmanCoder::operator=(const HuffmanCoder& other) {
    if (this != &other) {
        clear();
        copyFrom(other);
    }
    return *this;
}

// удалить дерево
HuffmanCoder::~HuffmanCoder() {
    clear();
}

// очистка дерева
void HuffmanCoder::clear() {
    delete root;
    root = nullptr;
}

// копировать кодер
void HuffmanCoder::copyFrom(const HuffmanCoder& other) {
    text = other.text;
    root = other.root == nullptr ? nullptr : new Node(*other.root);
}

// задать текст
void HuffmanCoder::setText(const std::string& newText) {
    clear();
    text = newText;
}

// строим дерево
void HuffmanCoder::buildTree() {
    std::vector<std::string> symbols = splitUtf8(text);
    std::map<std::string, int> frequencies;

    for (const std::string& symbol : symbols) {
        ++frequencies[symbol];
    }

    std::vector<Node*> nodes;
    for (const auto& pair : frequencies) {
        nodes.push_back(new Node(pair.first, pair.second));
    }

    while (nodes.size() > 1) {
        std::sort(nodes.begin(), nodes.end(), [](Node* a, Node* b) {
            if (a->getFrequency() == b->getFrequency()) {
                return a->getSymbol() < b->getSymbol();
            }
            return a->getFrequency() < b->getFrequency();
        });

        Node* left = nodes[0];
        Node* right = nodes[1];
        nodes.erase(nodes.begin());
        nodes.erase(nodes.begin());
        nodes.push_back(new Node(left, right));
    }

    root = nodes.empty() ? nullptr : nodes[0];
}

// собрать коды
void HuffmanCoder::buildCodes(Node* node, const std::string& code) const {
    if (node == nullptr) {
        return;
    }
    if (node->isLeaf()) {
        std::cout << "'" << node->getSymbol() << "' : "
                  << (code.empty() ? "0" : code) << "\n";
        return;
    }
    buildCodes(node->getLeft(), code + "0");
    buildCodes(node->getRight(), code + "1");
}

// печать дерева
void HuffmanCoder::printTree(Node* node, const std::string& prefix) const {
    if (node == nullptr) {
        return;
    }

    printTree(node->getRight(), prefix + "        ");

    if (node->isLeaf()) {
        std::cout << prefix << node->getSymbol() << " (" << node->getFrequency() << ")\n";
    } else {
        std::cout << prefix << "* (" << node->getFrequency() << ")\n";
    }

    printTree(node->getLeft(), prefix + "        ");
}

// печать решения
void HuffmanCoder::printSolution() const {
    std::vector<std::string> symbols = splitUtf8(text);
    std::map<std::string, int> frequencies;
    std::map<std::string, std::string> codes;
    int total = static_cast<int>(symbols.size());

    for (const std::string& symbol : symbols) {
        ++frequencies[symbol];
    }

    std::function<void(Node*, std::string)> collect = [&](Node* node, std::string code) {
        if (node == nullptr) {
            return;
        }
        if (node->isLeaf()) {
            codes[node->getSymbol()] = code.empty() ? "0" : code;
            return;
        }
        collect(node->getLeft(), code + "0");
        collect(node->getRight(), code + "1");
    };
    collect(root, "");

    int fixedLength = static_cast<int>(std::ceil(std::log2(frequencies.size())));
    int fixedBits = fixedLength * static_cast<int>(symbols.size());
    int huffmanBits = 0;
    double probabilitySum = 0.0;
    double averageLength = 0.0;

    for (const std::string& symbol : symbols) {
        huffmanBits += static_cast<int>(codes[symbol].size());
    }
    for (const auto& pair : frequencies) {
        double probability = static_cast<double>(pair.second) / total;
        probabilitySum += probability;
        averageLength += probability * codes[pair.first].size();
    }

    std::cout << "Сообщение: " << text << "\n";
    std::cout << "Символов: " << symbols.size() << "\n";
    std::cout << "Разных символов: " << frequencies.size() << "\n\n";

    std::cout << "Вероятности символов:\n";
    for (const auto& pair : frequencies) {
        double probability = static_cast<double>(pair.second) / total;
        std::cout << "'" << pair.first << "' : " << pair.second << "/" << total
                  << " = " << std::fixed << std::setprecision(2) << probability << "\n";
    }
    std::cout << "Сумма вероятностей: " << std::fixed << std::setprecision(2)
              << probabilitySum << "\n\n";

    std::vector<std::pair<std::pair<std::string, std::string>, int>> items;
    for (const auto& pair : frequencies) {
        items.push_back({{pair.first, pair.first}, pair.second});
    }

    std::cout << "Построение дерева Хаффмана:\n";
    int step = 1;
    while (items.size() > 1) {
        std::sort(items.begin(), items.end(), [](const auto& a, const auto& b) {
            if (a.second == b.second) {
                return a.first.second < b.first.second;
            }
            return a.second < b.second;
        });

        std::cout << step << ") Список: ";
        printWeightList(items, total);

        auto first = items[0];
        auto second = items[1];
        std::cout << "   Берем две минимальные: " << first.first.first << "="
                  << std::fixed << std::setprecision(2) << static_cast<double>(first.second) / total
                  << " и " << second.first.first << "="
                  << static_cast<double>(second.second) / total << "\n";
        std::cout << "   Объединяем: " << first.second << "/" << total << " + "
                  << second.second << "/" << total << " = "
                  << first.second + second.second << "/" << total << "\n";

        items.erase(items.begin());
        items.erase(items.begin());
        items.push_back({{"(" + first.first.first + "+" + second.first.first + ")",
                          first.first.second + second.first.second},
                         first.second + second.second});
        ++step;
    }
    std::cout << "Осталась одна вершина с весом 1.00\n";
    std::cout << "Левому ребру даем 0, правому ребру даем 1.\n";

    std::cout << "\nКоды символов:\n";
    for (const auto& pair : codes) {
        std::cout << "'" << pair.first << "' : " << pair.second
                  << "  l=" << pair.second.size() << "\n";
    }

    std::cout << "\nДерево кодирования боком:\n";
    std::cout << "Правое ребро - 1, левое ребро - 0.\n";
    printTree(root, "");

    std::cout << "\nРавномерный код: " << fixedLength << " бит на символ\n";
    std::cout << "Размер при равномерном кодировании: " << fixedBits << " бит\n";
    std::cout << "Размер при коде Хаффмана: " << huffmanBits << " бит\n";
    std::cout << "Средняя длина L = sum(pi * li) = "
              << std::fixed << std::setprecision(2) << averageLength << "\n";
}

// пустой шифр
CaesarCipher::CaesarCipher() {
    shift = 0;
}

// копия шифра
CaesarCipher::CaesarCipher(const CaesarCipher& other) {
    shift = other.shift;
}

// присваивание шифра
CaesarCipher& CaesarCipher::operator=(const CaesarCipher& other) {
    if (this != &other) {
        shift = other.shift;
    }
    return *this;
}

// пустой деструктор
CaesarCipher::~CaesarCipher() {
}

// задать сдвиг
void CaesarCipher::setShift(int newShift) {
    shift = newShift;
}

// сдвиг символа
std::string CaesarCipher::shiftSymbol(const std::string& symbol, int currentShift) const {
    std::vector<std::string> ru = splitUtf8("АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ");
    std::vector<std::string> ruSmall = splitUtf8("абвгдеёжзийклмнопрстуфхцчшщъыьэюя");
    std::vector<std::string> en = splitUtf8("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    std::vector<std::string> enSmall = splitUtf8("abcdefghijklmnopqrstuvwxyz");

    std::vector<std::vector<std::string>> alphabets = {ru, ruSmall, en, enSmall};
    for (const std::vector<std::string>& alphabet : alphabets) {
        for (int i = 0; i < static_cast<int>(alphabet.size()); ++i) {
            if (symbol == alphabet[i]) {
                int index = (i + currentShift) % static_cast<int>(alphabet.size());
                if (index < 0) {
                    index += static_cast<int>(alphabet.size());
                }
                return alphabet[index];
            }
        }
    }

    return symbol;
}

// зашифровать текст
std::string CaesarCipher::encrypt(const std::string& text) const {
    std::vector<std::string> symbols = splitUtf8(text);
    std::string result;

    for (const std::string& symbol : symbols) {
        result += shiftSymbol(symbol, shift);
    }

    return result;
}

// расшифровать текст
std::string CaesarCipher::decrypt(const std::string& text) const {
    std::vector<std::string> symbols = splitUtf8(text);
    std::string result;

    for (const std::string& symbol : symbols) {
        result += shiftSymbol(symbol, -shift);
    }

    return result;
}

// задание Хемминга
void runHammingTask() {
    HammingCoder coder;
    coder.setMessage("0010111010010");
    coder.buildCode();
    coder.printSolution();
}

// задание Хаффмана
void runHuffmanTask() {
    HuffmanCoder coder;
    coder.setText("КРИЧАЛ АРХИП, АРХИП ОХРИП");
    coder.buildTree();
    coder.printSolution();
}

// задание Цезаря
void runCaesarTask() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string text;
    int shift;

    std::cout << "Введите текст: ";
    std::getline(std::cin, text);
    std::cout << "Сдвиг: ";
    std::cin >> shift;

    CaesarCipher cipher;
    cipher.setShift(shift);

    std::string encrypted = cipher.encrypt(text);
    std::string decrypted = cipher.decrypt(encrypted);

    std::cout << "Исходный текст: " << text << "\n";
    std::cout << "Зашифровано: " << encrypted << "\n";
    std::cout << "Расшифровано: " << decrypted << "\n";
}
