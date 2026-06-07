#include <iostream>
#include "tasks.h"

using namespace std;

static void PrintMenu() {
    cout << "Лаба 7\n";
    cout << "1) Sort3      — пузырек убыв.\n";
    cout << "2) ExamTaskC15 — лучший месяц\n";
    cout << "3) Five13      — Шелл сорт\n";
    cout << "0) Выход\n";
    cout << "------------------------------\n";
}

static void ClearBadInputMain() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // очищаем ввод
}

static int ReadMenuChoice() {
    while (true) {
        cout << "Выберите пункт (0..3): ";
        int cmd;
        cin >> cmd;

        if (!cin) {
            cout << "Ошибка: введите число.\n";
            ClearBadInputMain();
            continue;
        }

        ClearBadInputMain();

        if (cmd < 0 || cmd > 3) {
            cout << "Ошибка: выберите число от 0 до 3.\n";
            continue;
        }

        return cmd;
    }
}

int main() {
    setlocale(LC_ALL, "ru");

    while (true) {
        PrintMenu();
        int cmd = ReadMenuChoice();

        if (cmd == 0) {
            cout << "Выход.\n";
            break;
        }

        if (cmd == 1) RunSort3();
        else if (cmd == 2) RunExamTaskC15();
        else if (cmd == 3) RunFive13();

        cout << "\nНажмите Enter, чтобы вернуться в меню...";
        cin.get(); // ждём Enter
    }

    return 0;
}