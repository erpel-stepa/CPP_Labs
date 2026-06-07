#include "module.h"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cctype>

bool g_ok = true; // флаг ошибок для задания 4

// проверяет существует ли файл
bool fileExists(const char* name) {
    using namespace std;

    ifstream f(name, ios::binary); // пробуем открыть
    bool ok = f.is_open(); // получилось или нет
    if (ok) f.close(); // закрываем
    return ok; // возвращаем результат
}

// возвращает размер файла в байтах
long long fileSize(const char* name) {
    using namespace std;

    ifstream f(name, ios::binary); // открываем
    if (!f.is_open()) return -1; // если нет файла

    f.seekg(0, ios::end); // идем в конец
    long long sz = (long long)f.tellg(); // размер
    f.close(); // закрываем
    return sz; // возвращаем
}

// создает A.bin с вещественными числами
void createA() {
    using namespace std;

    ofstream out("A.bin", ios::binary); // создаем файл
    if (!out.is_open()) {
        cout << "Не удалось создать A.bin\n";
        return;
    }

    double a[6] = { 1.5, -2.0, 3.3, 4.4, 5.5, 6.6 }; // тестовые данные

    for (int i = 0; i < 6; i++) { // запись массива
        out.write((char*)&a[i], sizeof(double)); // пишем double
    }

    out.close(); // закрываем
}

// создает ints.bin с 80 целыми числами
void createInts() {
    using namespace std;

    ofstream out("ints.bin", ios::binary); // создаем файл
    if (!out.is_open()) {
        cout << "Не удалось создать ints.bin\n";
        return;
    }

    for (int i = 1; i <= 80; i++) { // 80 чисел
        out.write((char*)&i, sizeof(int)); // запись int
    }

    out.close(); // закрываем
}

// создает S1.bin и S2.bin отсортированные
void createS() {
    using namespace std;

    ofstream out1("S1.bin", ios::binary); // создаем S1
    if (out1.is_open()) {
        double s1[6] = { -5, -1, 0, 2, 9, 20 }; // по возрастанию
        for (int i = 0; i < 6; i++) {
            out1.write((char*)&s1[i], sizeof(double)); // запись
        }
        out1.close();
    } else {
        cout << "Не удалось создать S1.bin\n";
    }

    ofstream out2("S2.bin", ios::binary); // создаем S2
    if (out2.is_open()) {
        double s2[7] = { -10, -1, 1, 2, 5, 100, 101 }; // по возрастанию
        for (int i = 0; i < 7; i++) {
            out2.write((char*)&s2[i], sizeof(double)); // запись
        }
        out2.close();
    } else {
        cout << "Не удалось создать S2.bin\n";
    }
}

// проверяет файлы и создает их если нужно
void prepareFiles() {
    long long szA = fileSize("A.bin"); // размер A
    if (!fileExists("A.bin") || szA < (long long)sizeof(double) || szA % (long long)sizeof(double) != 0)
        createA(); // создаем если нет

    long long szI = fileSize("ints.bin"); // размер ints
    long long cntI = -1;
    if (szI > 0 && szI % (long long)sizeof(int) == 0)
        cntI = szI / (long long)sizeof(int); // считаем элементы
    if (!fileExists("ints.bin") || szI <= 0 || szI % (long long)sizeof(int) != 0 || cntI <= 50)
        createInts(); // создаем если нужно

    long long szS1 = fileSize("S1.bin"); // размер S1
    long long szS2 = fileSize("S2.bin"); // размер S2
    bool okS1 = fileExists("S1.bin") && szS1 >= (long long)sizeof(double) && szS1 % (long long)sizeof(double) == 0;
    bool okS2 = fileExists("S2.bin") && szS2 >= (long long)sizeof(double) && szS2 % (long long)sizeof(double) == 0;
    if (!okS1 || !okS2)
        createS(); // создаем если нужно
}

void task1() {
    using namespace std;

    prepareFiles(); // гарантируем входной файл

    remove("B.bin"); // удаляем старый B

    ifstream in("A.bin", ios::binary); // открываем A
    if (!in.is_open()) {
        createA(); // создаем если не открылся
        in.open("A.bin", ios::binary); // открываем снова
    }
    if (!in.is_open()) {
        cout << "Ошибка открытия A.bin\n";
        return;
    }

    in.seekg(0, ios::end); // конец
    long long size = (long long)in.tellg(); // размер
    if (size < (long long)sizeof(double) || size % (long long)sizeof(double) != 0) {
        cout << "A.bin некорректный\n";
        in.close();
        return;
    }

    long long count = size / (long long)sizeof(double); // элементов

    cout << "A.bin было: "; // вывод до
    in.seekg(0, ios::beg); // в начало
    for (int i = 0; i < (int)count; i++) { // читаем все
        double x = 0;
        in.read((char*)&x, sizeof(double)); // чтение
        cout << x; // вывод
        if (i + 1 < (int)count) cout << " "; // пробел
    }
    cout << "\n";

    double first = 0; // первый элемент
    double last = 0; // последний элемент

    in.clear(); // сброс флагов
    in.seekg(0, ios::beg); // начало
    in.read((char*)&first, sizeof(double)); // первый

    in.seekg(size - (long long)sizeof(double), ios::beg); // к последнему
    in.read((char*)&last, sizeof(double)); // последний

    ofstream out("B.bin", ios::binary); // создаем B
    if (!out.is_open()) {
        cout << "Ошибка создания B.bin\n";
        in.close();
        return;
    }

    out.write((char*)&first, sizeof(double)); // запись
    out.write((char*)&last, sizeof(double)); // запись

    in.close();
    out.close();

    ifstream b("B.bin", ios::binary); // открываем B для вывода
    if (!b.is_open()) {
        cout << "B.bin не открылся\n";
        return;
    }

    cout << "B.bin стало: "; // вывод после
    for (int i = 0; i < 2; i++) { // в B всегда 2 элемента
        double x = 0;
        b.read((char*)&x, sizeof(double)); // чтение
        cout << x; // вывод
        if (i == 0) cout << " "; // пробел
    }
    cout << "\n";

    b.close();

    cout << "Готово\n";
    cout << "Почему так: по условию записали первый и последний элементы A.bin\n";
}

void task2() {
    using namespace std;

    prepareFiles(); // гарантируем файл

    ifstream in("ints.bin", ios::binary); // открываем
    if (!in.is_open()) {
        createInts(); // создаем если не открылся
        in.open("ints.bin", ios::binary); // открываем снова
    }
    if (!in.is_open()) {
        cout << "Ошибка открытия ints.bin\n";
        return;
    }

    in.seekg(0, ios::end); // конец
    long long size = (long long)in.tellg(); // размер
    if (size <= 0 || size % (long long)sizeof(int) != 0) {
        cout << "ints.bin некорректный\n";
        in.close();
        return;
    }

    long long countBefore = size / (long long)sizeof(int); // было элементов
    if (countBefore <= 50) {
        cout << "В файле не больше 50 элементов\n";
        in.close();
        return;
    }

    cout << "ints.bin было: "; // вывод до
    in.seekg(0, ios::beg); // в начало
    for (int i = 0; i < (int)countBefore; i++) { // читаем все
        int x = 0;
        in.read((char*)&x, sizeof(int)); // чтение
        cout << x; // вывод
        if (i + 1 < (int)countBefore) cout << " "; // пробел
    }
    cout << "\n";

    long long skip = countBefore - 50; // сколько удалить
    in.clear(); // сброс флагов
    in.seekg(skip * (long long)sizeof(int), ios::beg); // на первый новый

    ofstream out("temp.bin", ios::binary); // временный
    if (!out.is_open()) {
        cout << "Ошибка создания temp.bin\n";
        in.close();
        return;
    }

    for (int i = 0; i < 50; i++) { // копируем 50
        int x = 0;
        in.read((char*)&x, sizeof(int)); // читаем
        out.write((char*)&x, sizeof(int)); // пишем
    }

    in.close();
    out.close();

    remove("ints.bin"); // удаляем старый
    rename("temp.bin", "ints.bin"); // заменяем

    ifstream fin("ints.bin", ios::binary); // открываем после
    if (!fin.is_open()) {
        cout << "ints.bin не открылся после замены\n";
        return;
    }

    cout << "ints.bin стало: "; // вывод после
    for (int i = 0; i < 50; i++) { // теперь 50
        int x = 0;
        fin.read((char*)&x, sizeof(int)); // чтение
        cout << x; // вывод
        if (i != 49) cout << " "; // пробел
    }
    cout << "\n";

    fin.close();

    cout << "Готово\n";
    cout << "Почему так: удалили первые " << skip << " элементов, чтобы осталось 50\n";
}

void task3() {
    using namespace std;

    prepareFiles(); // гарантируем входные файлы

    ifstream f1("S1.bin", ios::binary); // открываем S1
    ifstream f2("S2.bin", ios::binary); // открываем S2

    if (!f1.is_open() || !f2.is_open()) {
        createS(); // создаем если не открылось
        if (f1.is_open()) f1.close();
        if (f2.is_open()) f2.close();
        f1.open("S1.bin", ios::binary);
        f2.open("S2.bin", ios::binary);
    }

    if (!f1.is_open() || !f2.is_open()) {
        cout << "Ошибка открытия S1 или S2\n";
        return;
    }

    long long n1 = fileSize("S1.bin") / (long long)sizeof(double); // элементов S1
    long long n2 = fileSize("S2.bin") / (long long)sizeof(double); // элементов S2

    cout << "S1.bin было: "; // вывод S1
    f1.seekg(0, ios::beg); // в начало
    for (int i = 0; i < (int)n1; i++) {
        double x = 0;
        f1.read((char*)&x, sizeof(double));
        cout << x;
        if (i + 1 < (int)n1) cout << " ";
    }
    cout << "\n";

    cout << "S2.bin было: "; // вывод S2
    f2.seekg(0, ios::beg); // в начало
    for (int i = 0; i < (int)n2; i++) {
        double x = 0;
        f2.read((char*)&x, sizeof(double));
        cout << x;
        if (i + 1 < (int)n2) cout << " ";
    }
    cout << "\n";

    f1.clear(); // сброс
    f2.clear(); // сброс
    f1.seekg(0, ios::beg); // снова в начало
    f2.seekg(0, ios::beg); // снова в начало

    ofstream out("S3.bin", ios::binary); // создаем результат
    if (!out.is_open()) {
        cout << "Ошибка создания S3.bin\n";
        f1.close();
        f2.close();
        return;
    }

    double a = 0, b = 0;
    bool hasA = false, hasB = false;

    f1.read((char*)&a, sizeof(double));
    if (!f1.fail()) hasA = true;

    f2.read((char*)&b, sizeof(double));
    if (!f2.fail()) hasB = true;

    while (hasA && hasB) {
        if (a <= b) {
            out.write((char*)&a, sizeof(double));
            f1.read((char*)&a, sizeof(double));
            hasA = !f1.fail();
        } else {
            out.write((char*)&b, sizeof(double));
            f2.read((char*)&b, sizeof(double));
            hasB = !f2.fail();
        }
    }

    while (hasA) {
        out.write((char*)&a, sizeof(double));
        f1.read((char*)&a, sizeof(double));
        hasA = !f1.fail();
    }

    while (hasB) {
        out.write((char*)&b, sizeof(double));
        f2.read((char*)&b, sizeof(double));
        hasB = !f2.fail();
    }

    f1.close();
    f2.close();
    out.close();

    long long n3 = fileSize("S3.bin") / (long long)sizeof(double); // элементов S3
    ifstream fin("S3.bin", ios::binary); // открываем S3 для вывода
    if (!fin.is_open()) {
        cout << "Ошибка открытия S3.bin\n";
        return;
    }

    cout << "S3.bin стало: "; // вывод S3
    for (int i = 0; i < (int)n3; i++) {
        double x = 0;
        fin.read((char*)&x, sizeof(double));
        cout << x;
        if (i + 1 < (int)n3) cout << " ";
    }
    cout << "\n";

    fin.close();

    cout << "Готово\n";
    cout << "Почему так: слили два отсортированных файла и получился отсортированный S3\n";
}

void task4() {
    using namespace std;

    bool done = false; // флаг

    while (!done) {
        string s; // строка
        cout << "Введите выражение: ";
        cin >> s; // ввод

        if (!cin.good()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Некорректный ввод\n";
        } else if (s.length() == 0) {
            cout << "Некорректный ввод\n";
        } else {
            int i = 0; // позиция
            g_ok = true; // сброс
            double result = 0; // ответ

            result = parseExpr(s, i); // считаем

            if (!g_ok || i != (int)s.length()) {
                cout << "Некорректное выражение, повторите\n";
            } else {
                cout << "Готово\n";
                cout << "Было: строковое выражение\n";
                cout << "Стало: вычисленное значение\n";
                cout << "Результат = " << result << "\n";
                done = true;
            }
        }
    }
}

// разбирает выражение с + и -
double parseExpr(const std::string& s, int& i) {
    if (!g_ok) return 0;

    double left = parseTerm(s, i); // первый терм
    return parseExprRest(s, i, left); // продолжаем +/-
}

double parseExprRest(const std::string& s, int& i, double left) {
    if (!g_ok) return 0;

    if (i >= (int)s.length()) return left; // конец строки

    char c = s[i]; // текущий символ

    if (c == '+' || c == '-') {
        i++; // пропускаем знак
        double right = parseTerm(s, i); // следующий терм
        if (!g_ok) return 0;

        if (c == '+') left = left + right; // считаем
        else left = left - right; // считаем

        return parseExprRest(s, i, left); // рекурсивно дальше
    }

    return left; // если не + и не -
}

// разбирает терм с *
double parseTerm(const std::string& s, int& i) {
    if (!g_ok) return 0;

    double left = parseFactor(s, i); // первый фактор
    return parseTermRest(s, i, left); // продолжаем *
}

double parseTermRest(const std::string& s, int& i, double left) {
    if (!g_ok) return 0;

    if (i >= (int)s.length()) return left; // конец строки

    char c = s[i]; // текущий символ

    if (c == '*') {
        i++; // пропускаем *
        double right = parseFactor(s, i); // следующий фактор
        if (!g_ok) return 0;

        left = left * right; // считаем

        return parseTermRest(s, i, left); // рекурсивно дальше
    }

    return left; // если не *
}

// разбирает фактор: цифра или (выражение)
double parseFactor(const std::string& s, int& i) {
    if (!g_ok) return 0;

    if (i >= (int)s.length()) {
        g_ok = false;
        return 0;
    }

    if (std::isdigit((unsigned char)s[i])) {
        double v = (double)(s[i] - '0'); // одна цифра
        i++; // сдвиг
        return v;
    }

    if (s[i] == '(') {
        i++; // пропуск (
        double v = parseExpr(s, i); // внутри скобок
        if (!g_ok) return 0;

        if (i >= (int)s.length() || s[i] != ')') {
            g_ok = false;
            return 0;
        }

        i++; // пропуск )
        return v;
    }

    g_ok = false;
    return 0;
}