#include "tasks.h"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <limits>

// Sort3
void ClearBadInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int ReadIntInRange(const std::string& prompt, int lo, int hi) {
    while (true) {
        std::cout << prompt;
        int x;
        std::cin >> x;

        if (!std::cin) {
            std::cout << "Ошибка: введите целое число.\n";
            ClearBadInput();
            continue;
        }

        if (x < lo || x > hi) {
            std::cout << "Ошибка: диапазон [" << lo << "; " << hi << "].\n";
            ClearBadInput();
            continue;
        }

        ClearBadInput();
        return x;
    }
}

bool TryOpenForWrite(const std::string& fileName) {
    std::ofstream test(fileName);
    return test.is_open();
}

void PrintArrayWithBorder(const std::vector<int>& a, int sortedCount, std::ostream& out) {
    for (int i = 0; i < (int)a.size(); i++) {
        out << a[i];
        if (i + 1 < (int)a.size()) out << ' ';
        if (i + 1 == sortedCount) out << " | ";
    }
    out << '\n';
}

void RunSort3() {
    using namespace std;

    cout << "\n=== Sort3 ===\n";
    cout << "Пример:\n";
    cout << "N=5\n";
    cout << "3 10 -2 10 0\n";
    cout << "sort3_protocol.txt\n\n";

    int n = ReadIntInRange("Введите N (1..1000): ", 1, 1000);

    vector<int> a(n);
    cout << "Введите " << n << " целых чисел:\n";

    while (true) {
        cout << "Массив: ";
        bool ok = true;

        for (int i = 0; i < n; i++) {
            cin >> a[i];
            if (!cin) ok = false;
        }

        if (!ok) {
            cout << "Ошибка: нужны целые числа. Повторите ввод.\n";
            ClearBadInput();
            continue;
        }

        ClearBadInput();
        break;
    }

    string outFileName;
    while (true) {
        cout << "Файл протокола: ";
        getline(cin, outFileName);

        if (outFileName.empty()) {
            cout << "Ошибка: имя файла пустое.\n";
            continue;
        }
        if (!TryOpenForWrite(outFileName)) {
            cout << "Ошибка: файл не создать. Дайте другое имя.\n";
            continue;
        }
        break;
    }

    ofstream fout(outFileName);
    if (!fout.is_open()) {
        cout << "Ошибка: не открыть файл.\n";
        return;
    }

    cout << "\nПротокол:\n";

    // метод простых обменов, отсортированная часть копится СЛЕВА
    for (int i = 0; i < n - 1; i++) {
        for (int j = n - 1; j > i; j--) { // идём справа налево
            if (a[j] > a[j - 1]) {        // сравнение соседних, убывание
                int tmp = a[j];
                a[j] = a[j - 1];
                a[j - 1] = tmp;
            }
        }

        PrintArrayWithBorder(a, i + 1, cout);
        PrintArrayWithBorder(a, i + 1, fout);
    }

    cout << "\nГотово. Файл: " << outFileName << "\n";
}

// ExamTaskC15
void SelectionSortSummaries(std::vector<YearSummary>& v) {
    int n = (int)v.size();

    for (int i = 0; i < n - 1; i++) {
        int best = i;

        for (int j = i + 1; j < n; j++) {
            if (v[j].bestHours > v[best].bestHours) best = j;
            else if (v[j].bestHours == v[best].bestHours && v[j].year < v[best].year) best = j;
        }

        if (best != i) {
            YearSummary t = v[i];
            v[i] = v[best];
            v[best] = t;
        }
    }
}

void RunExamTaskC15() {
    using namespace std;

    cout << "\n=== ExamTaskC15 ===\n";
    cout << "Пример:\n";
    cout << "K=12\nN=3\n";
    cout << "12 7 2001 1\n12 6 2001 2\n12 3 2002 5\n\n";

    int K = ReadIntInRange("Введите K (10..99): ", 10, 99);
    int N = ReadIntInRange("Введите N (0..100000): ", 0, 100000);

    vector<RecordC15> recs;
    recs.reserve(N);

    cout << "Введите " << N << " строк: <Код> <Часы> <Год> <Месяц>\n";

    for (int i = 0; i < N; i++) {
        while (true) {
            cout << "Строка " << (i + 1) << ": ";

            int code, hours, year, month;
            cin >> code >> hours >> year >> month;

            if (!cin) {
                cout << "Ошибка: нужно 4 целых.\n";
                ClearBadInput();
                continue;
            }

            if (code < 10 || code > 99) { cout << "Ошибка: код 10..99.\n"; ClearBadInput(); continue; }
            if (hours < 1 || hours > 30) { cout << "Ошибка: часы 1..30.\n"; ClearBadInput(); continue; }
            if (year < 2000 || year > 2010) { cout << "Ошибка: год 2000..2010.\n"; ClearBadInput(); continue; }
            if (month < 1 || month > 12) { cout << "Ошибка: месяц 1..12.\n"; ClearBadInput(); continue; }

            ClearBadInput();

            RecordC15 r;
            r.code = code; r.hours = hours; r.year = year; r.month = month;
            recs.push_back(r);
            break;
        }
    }

    const int Y0 = 2000, YN = 11, MN = 12;
    int sum[YN][MN];
    bool yearHas[YN];

    for (int y = 0; y < YN; y++) {
        yearHas[y] = false;
        for (int m = 0; m < MN; m++) sum[y][m] = 0;
    }

    for (const auto& r : recs) {
        if (r.code != K) continue;
        int yi = r.year - Y0;
        int mi = r.month - 1;
        sum[yi][mi] += r.hours;
        yearHas[yi] = true;
    }

    vector<YearSummary> ans;

    for (int yi = 0; yi < YN; yi++) {
        if (!yearHas[yi]) continue;

        int bestH = -1, bestM = 1;

        for (int mi = 0; mi < MN; mi++) {
            int val = sum[yi][mi];
            int month = mi + 1;

            if (val > bestH) { bestH = val; bestM = month; }
            else if (val == bestH && month < bestM) { bestM = month; }
        }

        YearSummary s;
        s.bestHours = bestH;
        s.year = Y0 + yi;
        s.bestMonth = bestM;
        ans.push_back(s);
    }

    cout << "\nРезультат:\n";
    if (ans.empty()) {
        cout << "Нет данных\n";
        return;
    }

    SelectionSortSummaries(ans);

    for (const auto& s : ans) {
        cout << s.bestHours << ' ' << s.year << ' ' << s.bestMonth << '\n';
    }
}

// Five13
bool LessStudent(const Student& a, const Student& b) {
    if (a.score != b.score) return a.score < b.score;
    return a.surname < b.surname;
}

void ShellSortStudents(std::vector<Student>& a) {
    int n = (int)a.size();

    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            Student temp = a[i];
            int j = i;

            while (j >= gap && LessStudent(temp, a[j - gap])) {
                a[j] = a[j - gap];
                j -= gap;
            }
            a[j] = temp;
        }
    }
}

bool TryReadStudentsFromFile(const std::string& fileName,
                            std::vector<Student>& outStudents,
                            std::string& err) {
    outStudents.clear();

    std::ifstream fin(fileName);
    if (!fin.is_open()) { err = "Не удалось открыть файл."; return false; }

    std::string surname;
    int score;

    while (true) {
        if (!(fin >> surname >> score)) break;

        if (score < 0 || score > 100) { err = "Неверный балл (0..100)."; return false; }

        Student s;
        s.surname = surname;
        s.score = score;
        outStudents.push_back(s);
    }

    if (outStudents.empty()) { err = "Файл пуст или формат неверный."; return false; }
    return true;
}

void RunFive13() {
    using namespace std;

    cout << "\n=== Five13 ===\n";
    cout << "Формат входного файла: Фамилия Балл\n";
    cout << "Пример:\nIvanov 87\nPetrov 65\n\n";

    string inName;
    vector<Student> students;
    string err;

    while (true) {
        cout << "Входной файл: ";
        getline(cin, inName);

        if (inName.empty()) { cout << "Ошибка: имя пустое.\n"; continue; }

        if (TryReadStudentsFromFile(inName, students, err)) break;

        cout << "Ошибка: " << err << "\n";
    }

    string outName;
    while (true) {
        cout << "Выходной файл: ";
        getline(cin, outName);

        if (outName.empty()) { cout << "Ошибка: имя пустое.\n"; continue; }
        if (!TryOpenForWrite(outName)) { cout << "Ошибка: не создать файл.\n"; continue; }
        break;
    }

    ShellSortStudents(students);

    ofstream fout(outName);
    if (!fout.is_open()) {
        cout << "Ошибка: не открыть для записи.\n";
        return;
    }

    for (const auto& s : students) {
        fout << left << setw(15) << s.surname
             << right << setw(3) << s.score << '\n';
    }

    fout.close();
    cout << "Готово: " << outName << "\n";
}