#ifndef MODULE_H
#define MODULE_H

#include <string>

// проверяет и при необходимости создает входные файлы
void prepareFiles();

// задания
void task1();
void task2();
void task3();
void task4();

// рекурсивный разбор выражения без try/catch
double parseExpr(const std::string& s, int& i);
double parseExprRest(const std::string& s, int& i, double left);
double parseTerm(const std::string& s, int& i);
double parseTermRest(const std::string& s, int& i, double left);
double parseFactor(const std::string& s, int& i);

// вспомогательные функции работы с файлами
bool fileExists(const char* name);
long long fileSize(const char* name);

// создание тестовых файлов
void createA();
void createInts();
void createS();

#endif