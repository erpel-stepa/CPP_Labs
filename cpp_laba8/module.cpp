#include "module.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

void task1() {
    using namespace std;

    ifstream in("task1.txt");
    if (!in.is_open()) {
        cout << "Ошибка: файл task1.txt не найден\n";
        return;
    }

    ofstream out("task1_out.txt");
    if (!out.is_open()) {
        cout << "Ошибка: не удалось создать файл task1_out.txt\n";
        return;
    }

    int N, B;
    in >> N >> B; // читаем N и ограничение по весу
    if (!in || N <= 0 || B < 0) {
        cout << "Ошибка в данных файла task1.txt\n";
        return;
    }

    vector<int> weight(N), volume(N); // веса и объемы предметов

    for (int i = 0; i < N; i++) {
        in >> weight[i]; // читаем веса
        if (!in || weight[i] < 0) {
            cout << "Ошибка в весах (task1.txt)\n"; // отрицательный вес или не число
            return;
        }
    }

    for (int i = 0; i < N; i++) {
        in >> volume[i]; // читаем объемы
        if (!in || volume[i] < 0) {
            cout << "Ошибка в объемах (task1.txt)\n"; // отрицательный объем или не число
            return;
        }
    }



    vector<State> dp(B + 1); // dp[w] - лучшее состояние для веса w
    dp[0].count = 0; // вес 0 достижим без предметов

    for (int i = 0; i < N; i++) { // перебираем предметы
        for (int w = B; w >= weight[i]; w--) { // назад, чтобы не взять предмет 2 раза
            if (dp[w - weight[i]].count == -1) continue; // если предыдущий вес недостижим

            int newCount = dp[w - weight[i]].count + 1; // сколько будет предметов если взять i

            if (newCount > dp[w].count) { // для этого веса выбираем больше предметов
                dp[w].count = newCount; // обновляем максимум по количеству
                dp[w].vol = dp[w - weight[i]].vol + volume[i]; // объем тоже обновляем
                dp[w].last = i; // запоминаем последний предмет
                dp[w].prevW = w - weight[i]; // запоминаем прошлый вес
            }
        }
    }

    int bestW = 0; // тут будет лучший вес
    for (int w = 0; w <= B; w++) {
        if (dp[w].count == -1) continue; // пропускаем недостижимые веса

        if (w > bestW) bestW = w; // хотим вес как можно ближе к B
        else if (w == bestW && dp[w].count > dp[bestW].count)
            bestW = w; // если вес одинаковый, берем больше предметов
    }

    vector<int> result; // номера выбранных предметов
    for (int w = bestW; w != 0 && dp[w].last != -1; w = dp[w].prevW) // идем назад по prevW
        result.push_back(dp[w].last + 1);

    reverse(result.begin(), result.end()); // чтобы вывести в нормальном порядке

    for (int x : result) out << x << " "; // выводим номера
    out << "\n" << bestW << " " << dp[bestW].vol << "\n"; // общий вес и общий объем

    cout << "Задание 1 выполнено (task1_out.txt)\n";
}

void task2() {
    using namespace std;

    ifstream in("task2.txt");
    if (!in.is_open()) {
        cout << "Ошибка: файл task2.txt не найден\n";
        return;
    }

    ofstream out("task2_out.txt");
    if (!out.is_open()) {
        cout << "Ошибка: не удалось создать файл task2_out.txt\n";
        return;
    }

    int N;
    in >> N; // размер доски
    if (!in || N <= 1 || N >= 80) {
        cout << "Ошибка в размере доски (task2.txt)\n"; // проверяем диапазон
        return;
    }

    vector<vector<int>> board(N, vector<int>(N)); // сама доска

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            in >> board[i][j]; // читаем значение монеты
            if (!in || board[i][j] < 1 || board[i][j] > 100) {
                cout << "Ошибка в значениях монет (task2.txt)\n"; // монеты 1..100
                return;
            }
        }

    vector<vector<int>> dp(N, vector<int>(N)); // dp[i][j] - максимум до клетки (i,j)
    dp[0][0] = board[0][0]; // старт (левый верхний)

    for (int j = 1; j < N; j++)
        dp[0][j] = dp[0][j - 1] + board[0][j]; // первая строка только слева

    for (int i = 1; i < N; i++)
        dp[i][0] = dp[i - 1][0] + board[i][0]; // первый столбец только сверху

    for (int i = 1; i < N; i++)
        for (int j = 1; j < N; j++)
            dp[i][j] = board[i][j] + max(dp[i - 1][j], dp[i][j - 1]); // выбираем откуда выгоднее

    int i = N - 1, j = N - 1; // начинаем с правого нижнего
    string path; // сюда собираем путь

    while (i > 0 || j > 0) {
        if (i > 0 && (j == 0 || dp[i - 1][j] >= dp[i][j - 1])) {
            path += 'U'; // если идем вверх
            i--; // уменьшаем i
        } else {
            path += 'L'; // если идем влево
            j--; // уменьшаем j
        }
    }

    out << dp[N - 1][N - 1] << "\n" << path << "\n"; // максимум и путь

    cout << "Задание 2 выполнено (task2_out.txt)\n";
}

void task3() {
    int N = 0, K = 0;
    bool ok = false;

    while (!ok) {
        std::cout << "Введите N (1<N<20) и K (2<=K<=10): ";
        std::cin >> N >> K;

        if (!std::cin) {
            std::cin.clear(); // сбрасываем ошибку потока
            std::cin.ignore(10000, '\n'); // чистим мусор
            std::cout << "Ошибка ввода\n";
        } else if (N <= 1 || N >= 20 || K < 2 || K > 10) {
            std::cout << "Неверные значения\n"; // проверка диапазонов
        } else if (N + K >= 26) {
            std::cout << "N + K должно быть меньше 26\n"; // условие из задания
        } else {
            ok = true;
        }
    }

    std::vector<double> prev(4, 0.0), next(4, 0.0); // 4 состояния: 0..3 нуля подряд

    prev[0] = (K - 1); // первый разряд не ноль, значит вариантов K-1

    for (int pos = 1; pos < N; pos++) { // достраиваем остальные разряды
        std::fill(next.begin(), next.end(), 0.0); // обнуляем next перед шагом

        for (int z = 0; z <= 3; z++) {
            if (prev[z] == 0.0) continue; // если способов нет, пропускаем

            if (z < 3) next[z + 1] += prev[z]; // ставим 0 и увеличиваем серию нулей

            next[0] += prev[z] * (K - 1); // ставим не ноль, серия нулей сбрасывается
        }

        prev = next; // переходим на следующий разряд
    }

    double answer = 0.0;
    for (int z = 0; z <= 3; z++)
        answer += prev[z]; // суммируем все варианты на длине N

    std::cout << "Количество чисел: " << answer << std::endl; // вывод
}
