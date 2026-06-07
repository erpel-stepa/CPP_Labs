#ifndef MODULE_H
#define MODULE_H

#include <string>

class HammingCoder {
private:
    std::string message;
    std::string code;
    int parityCount;

    bool isPowerOfTwo(int number) const;
    int calculateSyndrome(const std::string& receivedCode) const;
    std::string correctCode(const std::string& receivedCode, int syndrome) const;

public:
    HammingCoder();
    HammingCoder(const HammingCoder& other);
    HammingCoder& operator=(const HammingCoder& other);
    ~HammingCoder();

    void setMessage(const std::string& newMessage);
    void buildCode();
    void printSolution() const;
};

class HuffmanCoder {
private:
    class Node {
    private:
        std::string symbol;
        int frequency;
        Node* left;
        Node* right;

    public:
        Node(const std::string& newSymbol, int newFrequency);
        Node(Node* leftNode, Node* rightNode);
        Node(const Node& other);
        Node& operator=(const Node& other);
        ~Node();

        std::string getSymbol() const;
        int getFrequency() const;
        Node* getLeft() const;
        Node* getRight() const;
        bool isLeaf() const;
    };

    std::string text;
    Node* root;

    void clear();
    void copyFrom(const HuffmanCoder& other);
    void buildCodes(Node* node, const std::string& code) const;
    void printTree(Node* node, const std::string& prefix) const;

public:
    HuffmanCoder();
    HuffmanCoder(const HuffmanCoder& other);
    HuffmanCoder& operator=(const HuffmanCoder& other);
    ~HuffmanCoder();

    void setText(const std::string& newText);
    void buildTree();
    void printSolution() const;
};

class CaesarCipher {
private:
    int shift;

    std::string shiftSymbol(const std::string& symbol, int currentShift) const;

public:
    CaesarCipher();
    CaesarCipher(const CaesarCipher& other);
    CaesarCipher& operator=(const CaesarCipher& other);
    ~CaesarCipher();

    void setShift(int newShift);
    std::string encrypt(const std::string& text) const;
    std::string decrypt(const std::string& text) const;
};

void runHammingTask();
void runHuffmanTask();
void runCaesarTask();

#endif
