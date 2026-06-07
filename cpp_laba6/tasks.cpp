#include "tasks.h"

#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <locale>
#include <codecvt>

// ---------- UTF-8 <-> wstring ----------

std::wstring utf8ToWString(const std::string &s) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    return conv.from_bytes(s);
}

std::string wStringToUtf8(const std::wstring &ws) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    return conv.to_bytes(ws);
}

// ---------- Ввод данных ----------

int readIntInRange(const std::string &prompt, int l, int r) {
    using namespace std;

    int x;
    bool ok = false;

    while (!ok) {
        cout << prompt;
        cin >> x;

        if (!cin.fail() && x >= l && x <= r) {
            ok = true;
        } else {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ошибка. Ожидалось int в диапазоне [" << l << ".." << r << "]." << endl;
        }
    }

    return x;
}

int readPositiveInt(const std::string &prompt) {
    using namespace std;

    int x;
    bool ok = false;

    while (!ok) {
        cout << prompt;
        cin >> x;

        if (!cin.fail() && x > 0) {
            ok = true;
        } else {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ошибка. Ожидалось целое число (int > 0)." << endl;
        }
    }

    return x;
}

int readIntAtLeast(const std::string &prompt, int minValue) {
    using namespace std;

    int x;
    bool ok = false;

    while (!ok) {
        cout << prompt;
        cin >> x;

        if (!cin.fail() && x >= minValue) {
            ok = true;
        } else {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ошибка. Ожидалось целое число (int >= " << minValue << ")." << endl;
        }
    }

    return x;
}

double readDouble(const std::string &prompt) {
    using namespace std;

    double x;
    bool ok = false;

    while (!ok) {
        cout << prompt;
        cin >> x;

        if (!cin.fail()) {
            ok = true;
        } else {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ошибка. Ожидалось вещественное число (double)." << endl;
        }
    }

    return x;
}

float readPositiveFloat(const std::string &prompt) {
    using namespace std;

    float x;
    bool ok = false;

    while (!ok) {
        cout << prompt;
        cin >> x;

        if (!cin.fail() && x > 0) {
            ok = true;
        } else {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ошибка. Ожидалось вещественное число (float > 0)." << endl;
        }
    }

    return x;
}

short readPositiveShort(const std::string &prompt) {
    using namespace std;

    int tmp;
    bool ok = false;

    while (!ok) {
        cout << prompt;
        cin >> tmp;

        if (!cin.fail() && tmp > 0 && tmp <= 32767) {
            ok = true;
        } else {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ошибка. Ожидалось целое число (short int > 0)." << endl;
        }
    }

    return static_cast<short>(tmp);
}

std::string readWord(const std::string &prompt) {
    using namespace std;

    string s;
    bool ok = false;

    while (!ok) {
        cout << prompt;
        cin >> s;

        if (!cin.fail() && !s.empty()) {
            ok = true;
        } else {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ошибка. Ожидалась непустая строка без пробелов." << endl;
        }
    }

    return s;
}

// ---------- Задание 1 ----------

ClientRow readClientRow(int idx) {
    using namespace std;

    ClientRow row;
    bool ok = false;

    cout << "Строка " << idx << " (int int int int): продолжительность код год месяц" << endl;
    cout << "Ограничения: dur 1..30, code 10..99, year 2000..2010, month 1..12" << endl;

    while (!ok) {
        cout << "Введите: ";
        cin >> row.dur >> row.code >> row.year >> row.month;

        if (!cin.fail() &&
            row.dur >= 1 && row.dur <= 30 &&
            row.code >= 10 && row.code <= 99 &&
            row.year >= 2000 && row.year <= 2010 &&
            row.month >= 1 && row.month <= 12) {
            ok = true;
        } else {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ошибка. Проверьте диапазоны значений." << endl;
        }
    }

    return row;
}

bool isEarlier(const ClientRow &a, const ClientRow &b) {
    if (a.year < b.year) return true;
    if (a.year > b.year) return false;
    return a.month < b.month;
}

void task1() {
    using namespace std;

    int n = readPositiveInt("Введите количество записей (int > 0): ");

    ClientRow best;
    best.dur = 31;
    best.year = 9999;
    best.month = 99;

    for (int i = 1; i <= n; i++) {
        ClientRow cur = readClientRow(i);

        if (cur.dur < best.dur ||
            (cur.dur == best.dur && isEarlier(cur, best))) {
            best = cur;
        }
    }

    cout << "Минимальная продолжительность: " << best.dur << endl;
    cout << "Год: " << best.year << endl;
    cout << "Месяц: " << best.month << endl;
}

// ---------- Задание 2 ----------

std::wstring typeToWString(int t) {
    if (t == CIRCLE) return L"Круг";
    if (t == SQUARE) return L"Квадрат";
    return L"Отрезок";
}

Figure readFigure(int idx) {
    using namespace std;

    Figure f;

    cout << "Фигура " << idx << endl;

    int t = readIntInRange("Тип (int: 0-круг, 1-квадрат, 2-отрезок): ", 0, 2);
    f.type = static_cast<FigureType>(t);

    f.color = readWord("Цвет (строка без пробелов): ");

    if (f.type == CIRCLE) {
        f.radius = readPositiveShort("Радиус (short int > 0): ");
    } else if (f.type == SQUARE) {
        f.side = readPositiveInt("Сторона (int > 0): ");
    } else {
        f.length = readPositiveFloat("Длина (float > 0): ");
    }

    return f;
}

void task2() {
    using namespace std;

    // Настраиваем wide-вывод под текущую локаль
    std::locale loc("");
    std::wcout.imbue(loc);

    int n = readPositiveInt("Введите количество фигур (int > 0): ");

    ofstream fout("figures.txt");
    for (int i = 1; i <= n; i++) {
        Figure f = readFigure(i);

        fout << f.type << " " << f.color << " ";
        if (f.type == CIRCLE) fout << f.radius;
        else if (f.type == SQUARE) fout << f.side;
        else fout << f.length;
        fout << endl;
    }
    fout.close();

    ifstream fin("figures.txt");

    // Ширины колонок в СИМВОЛАХ (для wcout)
    const int W_NUM = 4;
    const int W_TYPE = 14;
    const int W_COLOR = 22;
    const int W_SIZE = 12;

    wcout << L"\n";
    wcout << left
          << setw(W_NUM)  << L"№"
          << setw(W_TYPE) << L"Тип"
          << setw(W_COLOR) << L"Цвет"
          << setw(W_SIZE) << L"Размер"
          << L"\n";

    int t;
    string color;
    int row = 1;

    // Числа форматируем стабильно
    wcout << fixed << setprecision(2);

    while (fin >> t >> color) {
        wstring wColor = utf8ToWString(color);

        wcout << left
              << setw(W_NUM)  << row
              << setw(W_TYPE) << typeToWString(t)
              << setw(W_COLOR) << wColor;

        if (t == CIRCLE) {
            short r;
            fin >> r;
            wcout << setw(W_SIZE) << r;
        } else if (t == SQUARE) {
            int s;
            fin >> s;
            wcout << setw(W_SIZE) << s;
        } else {
            float l;
            fin >> l;
            wcout << setw(W_SIZE) << l;
        }

        wcout << L"\n";
        row++;
    }

    fin.close();
}

// ---------- Задание 3 ----------

double distancePoints(const Point &a, const Point &b) {
    return std::sqrt(
        (a.x - b.x) * (a.x - b.x) +
        (a.y - b.y) * (a.y - b.y)
    );
}

double polygonArea(const std::vector<Point> &pts) {
    double s = 0.0;

    for (size_t i = 0; i < pts.size(); i++) {
        size_t j = (i + 1) % pts.size();
        s += pts[i].x * pts[j].y - pts[j].x * pts[i].y;
    }

    return std::fabs(s) / 2.0;
}

void printPoints(const std::vector<Point> &pts) {
    using namespace std;

    cout << "Список точек:" << endl;
    for (size_t i = 0; i < pts.size(); i++) {
        cout << i + 1 << ": (" << pts[i].x << ", " << pts[i].y << ")" << endl;
    }
}

int readPointIndex(const std::vector<Point> &pts, const std::string &prompt) {
    return readIntInRange(prompt, 1, static_cast<int>(pts.size()));
}

void task3() {
    using namespace std;

    int n = readIntAtLeast("Введите количество точек (int >= 3): ", 3);

    vector<Point> pts(n);

    for (int i = 0; i < n; i++) {
        cout << "Точка " << i + 1 << endl;
        pts[i].x = readDouble("x (double): ");
        pts[i].y = readDouble("y (double): ");
    }

    int cmd = -1;

    while (cmd != 0) {
        cout << endl;
        cout << "Меню работы с точками" << endl;
        cout << "1 - Показать точки" << endl;
        cout << "2 - Расстояние между двумя точками" << endl;
        cout << "3 - Переместить точку" << endl;
        cout << "4 - Добавить вершину" << endl;
        cout << "5 - Удалить вершину" << endl;
        cout << "6 - Площадь многоугольника" << endl;
        cout << "0 - Выход" << endl;
        cout << "Введите команду (int): ";

        cin >> cmd;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ошибка ввода." << endl;
            cmd = -1;
            continue;
        }

        if (cmd == 1) {
            printPoints(pts);
        } else if (cmd == 2) {
            int a = readPointIndex(pts, "Номер первой точки: ");
            int b = readPointIndex(pts, "Номер второй точки: ");
            while (a == b) {
                cout << "Номера должны различаться." << endl;
                b = readPointIndex(pts, "Номер второй точки: ");
            }
            cout << "Расстояние: " << distancePoints(pts[a - 1], pts[b - 1]) << endl;
        } else if (cmd == 3) {
            int idx = readPointIndex(pts, "Номер точки: ");
            double dx = readDouble("dx (double): ");
            double dy = readDouble("dy (double): ");
            pts[idx - 1].x += dx;
            pts[idx - 1].y += dy;
            cout << "Точка перемещена." << endl;
        } else if (cmd == 4) {
            Point p;
            p.x = readDouble("x (double): ");
            p.y = readDouble("y (double): ");
            pts.push_back(p);
            cout << "Вершина добавлена." << endl;
        } else if (cmd == 5) {
            if (pts.size() <= 3) {
                cout << "Нельзя удалить. Нужно минимум 3 точки." << endl;
            } else {
                int idx = readPointIndex(pts, "Номер вершины: ");
                pts.erase(pts.begin() + idx - 1);
                cout << "Вершина удалена." << endl;
            }
        } else if (cmd == 6) {
            cout << "Площадь: " << polygonArea(pts) << endl;
        } else if (cmd != 0) {
            cout << "Неизвестная команда." << endl;
        }
    }
}