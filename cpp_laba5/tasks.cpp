#include "tasks.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cctype>
#include <vector>

using namespace std;

// -------------------- Вспомогательные функции --------------------

int getInt(const string& msg, int mn, int mx) {
    string s;
    while (true) {
        cout << msg;
        getline(cin, s);

        if (s.empty()) {
            cout << "Пустой ввод. Повторите.\n";
        } else {
            bool ok = true;
            for (char c : s) {
                if (!isdigit((unsigned char)c)) ok = false;
            }
            if (ok) {
                int x = stoi(s);
                if (x >= mn && x <= mx) return x;
            }
            cout << "Ошибка. Введите число от " << mn << " до " << mx << ".\n";
        }
    }
}

vector<string> splitUTF8(const string& s) {
    vector<string> res;
    size_t i = 0;
    while (i < s.size()) {
        unsigned char c = (unsigned char)s[i];
        if (c < 128) {
            res.push_back(s.substr(i, 1));
            i += 1;
        } else {
            res.push_back(s.substr(i, 2));
            i += 2;
        }
    }
    return res;
}

// -------------------- Ввод строки --------------------

string randomRussianString() {
    string rus[32] = {
        "А","Б","В","Г","Д","Е","Ж","З","И","Й","К","Л","М","Н","О","П",
        "Р","С","Т","У","Ф","Х","Ц","Ч","Ш","Щ","Ъ","Ы","Ь","Э","Ю","Я"
    };

    int words = getInt("Введите количество слов (1..50): ", 1, 50);
    string s;

    for (int w = 0; w < words; w++) {
        int len = 1 + rand() % 8;
        for (int i = 0; i < len; i++) {
            s += rus[rand() % 32];
        }
        if (w != words - 1) s += ' ';
    }

    cout << "Случайная строка:\n" << s << endl;
    return s;
}

string inputManual() {
    cout << "Введите строку: ";
    string s;
    getline(cin, s);
    return s;
}

string inputFromFile() {
    cout << "Введите имя файла: ";
    string name;
    getline(cin, name);

    ifstream fin(name.c_str());
    if (!fin.is_open()) {
        cout << "Файл не найден. Создать его? (1-да, 2-нет): ";
        int c = getInt("", 1, 2);
        if (c == 1) {
            ofstream fout(name.c_str());
            fout.close();
            cout << "Файл создан.\n";
        }
        return "";
    }

    string s, line;
    while (getline(fin, line)) {
        s += line + " ";
    }
    fin.close();

    cout << "Строка из файла:\n" << s << endl;
    return s;
}

string getString(bool allowRandom) {
    cout << "Как вводить строку?\n";
    cout << "1 - руками\n";
    if (allowRandom) cout << "2 - случайно (русские слова)\n";
    cout << "3 - из файла\n";

    int c = getInt("Ваш выбор: ", 1, allowRandom ? 3 : 3);

    if (c == 1) return inputManual();
    if (c == 2 && allowRandom) return randomRussianString();
    return inputFromFile();
}

// -------------------- Задание 1 --------------------

void task1() {
    string s = getString(true);
    if (s.empty()) return;

    vector<string> chars = splitUTF8(s);

    for (const string& ch : chars) {
        if (ch != " " && (ch < "А" || ch > "Я")) {
            cout << "Ошибка: допускаются только заглавные русские буквы.\n";
            return;
        }
    }

    int count = 0;
    bool inWord = false;
    bool hasA = false;

    for (const string& ch : chars) {
        if (ch == " ") {
            if (inWord && hasA) count++;
            inWord = false;
            hasA = false;
        } else {
            inWord = true;
            if (ch == "А") hasA = true;
        }
    }

    if (inWord && hasA) count++;

    cout << "Количество слов с буквой «А»: " << count << endl;
}

// -------------------- Задание 2 --------------------

void task2() {
    string s = getString(true);
    if (s.empty()) return;

    cout << "Коды (по байтам):\n";
    for (unsigned char c : s) {
        cout << (int)c << " ";
    }
    cout << endl;
}

// -------------------- Задание 3 --------------------

void task3() {
    string s = getString(true);
    if (s.empty()) return;

    int g = getInt("Введите гамму (127..255): ", 127, 255);

    string enc = s;

    for (size_t i = 0; i < enc.size(); i++) {
        enc[i] = (unsigned char)enc[i] ^ (unsigned char)g;
    }

    cout << "Зашифрованная строка:\n";
    cout << enc << endl;

    for (size_t i = 0; i < enc.size(); i++) {
        enc[i] = (unsigned char)enc[i] ^ (unsigned char)g;
    }

    cout << "Расшифрованная строка:\n";
    cout << enc << endl;
}

// -------------------- Задание 4 --------------------

void task4() {
    string s = getString(true);
    if (s.empty()) return;

    vector<string> chars = splitUTF8(s);
    vector<int> cnt(chars.size(), 0);

    for (size_t i = 0; i < chars.size(); i++) {
        for (size_t j = 0; j < chars.size(); j++) {
            if (chars[i] == chars[j]) cnt[i]++;
        }
    }

    cout << "Уникальные символы:\n";
    for (size_t i = 0; i < chars.size(); i++) {
        if (cnt[i] == 1 && chars[i] != " ")
            cout << chars[i];
    }
    cout << endl;
}

// -------------------- Задание 5 --------------------

void task5() {
    cout << "Введите шестнадцатеричное число: ";
    string hexs;
    getline(cin, hexs);

    for (char c : hexs) {
        if (!isxdigit((unsigned char)c)) {
            cout << "Ошибка: не HEX-число.\n";
            return;
        }
    }

    int dec = 0;
    for (char c : hexs) {
        int v;
        if (isdigit(c)) v = c - '0';
        else if (c >= 'A' && c <= 'F') v = c - 'A' + 10;
        else v = c - 'a' + 10;
        dec = dec * 16 + v;
    }

    if (dec == 0) {
        cout << "8-ричная система: 0\n";
        return;
    }

    string oct;
    while (dec > 0) {
        oct = char('0' + dec % 8) + oct;
        dec /= 8;
    }

    cout << "8-ричная система: " << oct << endl;
}

// -------------------- Задание 6 --------------------

string morzeRus(const string& ch) {
    if (ch == "А") return ".-";
    if (ch == "Б") return "-...";
    if (ch == "В") return ".--";
    if (ch == "Г") return "--.";
    if (ch == "Д") return "-..";
    if (ch == "Е") return ".";
    if (ch == "Ж") return "...-";
    if (ch == "З") return "--..";
    if (ch == "И") return "..";
    if (ch == "Й") return ".---";
    if (ch == "К") return "-.-";
    if (ch == "Л") return ".-..";
    if (ch == "М") return "--";
    if (ch == "Н") return "-.";
    if (ch == "О") return "---";
    if (ch == "П") return ".--.";
    if (ch == "Р") return ".-.";
    if (ch == "С") return "...";
    if (ch == "Т") return "-";
    if (ch == "У") return "..-";
    if (ch == "Ф") return "..-.";
    if (ch == "Х") return "....";
    if (ch == "Ц") return "-.-.";
    if (ch == "Ч") return "---.";
    if (ch == "Ш") return "----";
    if (ch == "Щ") return "--.-";
    if (ch == "Ъ") return "--.--";
    if (ch == "Ы") return "-.--";
    if (ch == "Ь") return "-..-";
    if (ch == "Э") return "..-..";
    if (ch == "Ю") return "..--";
    if (ch == "Я") return ".-.-";
    return "";
}

void task6() {
    string s = getString(true);
    if (s.empty()) return;

    vector<string> chars = splitUTF8(s);

    cout << "Код Морзе:\n";
    for (const string& ch : chars) {
        if (ch == " ") {
            cout << "/ ";
        } else {
            string m = morzeRus(ch);
            if (!m.empty()) cout << m << " ";
        }
    }
    cout << endl;
}

// -------------------- Задание 7 --------------------

void task7() {
    ifstream f("FN1");
    if (!f.is_open()) {
        cout << "Файл FN1 не найден. Создать? (1-да, 2-нет): ";
        int c = getInt("", 1, 2);
        if (c == 1) {
            ofstream nf("FN1");
            nf.close();
            cout << "FN1 создан.\n";
        }
        return;
    }

    ofstream g("FN2");
    string x;
    bool errorFound = false;

    while (getline(f, x)) {
        int a = 0, b = 0;
        char op = 0;
        int i = 0;
        bool bad = false;

        // пропуск пробелов
        while (i < (int)x.size() && x[i] == ' ') i++;

        // первое число
        if (i >= (int)x.size() || !isdigit((unsigned char)x[i])) bad = true;
        while (!bad && i < (int)x.size() && isdigit((unsigned char)x[i])) {
            a = a * 10 + (x[i] - '0');
            i++;
        }

        // пробелы
        while (!bad && i < (int)x.size() && x[i] == ' ') i++;

        // знак
        if (!bad) {
            if (i >= (int)x.size() || (x[i] != '+' && x[i] != '-')) bad = true;
            else {
                op = x[i];
                i++;
            }
        }

        // пробелы
        while (!bad && i < (int)x.size() && x[i] == ' ') i++;

        // второе число
        if (!bad && (i >= (int)x.size() || !isdigit((unsigned char)x[i]))) bad = true;
        while (!bad && i < (int)x.size() && isdigit((unsigned char)x[i])) {
            b = b * 10 + (x[i] - '0');
            i++;
        }

        // пробелы
        while (!bad && i < (int)x.size() && x[i] == ' ') i++;

        // знак '=' (разрешён, как в условии). Может быть, а может и не быть.
        if (!bad && i < (int)x.size() && x[i] == '=') {
            i++;
        }

        // пробелы после '='
        while (!bad && i < (int)x.size() && x[i] == ' ') i++;

        // если остались какие-то символы — ошибка
        if (!bad && i < (int)x.size()) bad = true;

        // доп.проверка: натуральные и не более 3 цифр (1..999)
        if (!bad) {
            if (a < 1 || a > 999 || b < 1 || b > 999) bad = true;
        }

        if (bad) {
            errorFound = true;
        } else {
            int r = (op == '+') ? a + b : a - b;
            g << a << " " << op << " " << b << " = " << r << "\n";
        }
    }

    f.close();
    g.close();

    if (errorFound) {
        cout << "Ошибка: в файле FN1 есть недопустимые символы или неверный формат.\n";
        cout << "Разрешено: число (+ или -) число и в конце может быть '='.\n";
    } else {
        cout << "Результаты записаны в FN2.\n";
    }
}