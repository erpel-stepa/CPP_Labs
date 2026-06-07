#include "module.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <random>

namespace {

// чистим ввод
void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// число в диапазоне
bool inRange(int value, int left, int right) {
    return value >= left && value <= right;
}

// выбор ввода
bool inputGraphByMenu(MatrixGraph& graph, int max_n, bool directed) {
    int choice = 0;
    std::string file_name;

    std::cout << "Способ ввода:\n";
    std::cout << "1) С клавиатуры\n";
    std::cout << "2) Из файла\n";
    std::cout << "3) Случайно\n";
    std::cout << "Ваш выбор: ";

    if (!readInt(choice)) {
        std::cout << "Введите целое число.\n";
        return false;
    }

    switch (choice) {
        case 1:
            return graph.inputFromKeyboard(max_n, directed);
        case 2:
            std::cout << "Имя файла: ";
            std::cin >> file_name;
            return graph.inputFromFile(file_name, max_n, directed);
        case 3:
            return graph.inputRandom(max_n, directed);
        default:
            std::cout << "Такого способа ввода нет.\n";
            return false;
    }
}

// печать чисел
void printNumbers(const std::vector<int>& numbers) {
    if (numbers.empty()) {
        std::cout << "-1\n";
        return;
    }

    for (int number : numbers) {
        std::cout << number << ' ';
    }
    std::cout << '\n';
}

}  // namespace

// безопасный ввод
bool readInt(int& value) {
    if (!(std::cin >> value)) {
        clearInput();
        return false;
    }
    return true;
}

// пустой граф
MatrixGraph::MatrixGraph() : vertex_count_(0) {
}

// копируем граф
MatrixGraph::MatrixGraph(const MatrixGraph& other)
    : vertex_count_(other.vertex_count_), matrix_(other.matrix_) {
}

// присваиваем граф
MatrixGraph& MatrixGraph::operator=(const MatrixGraph& other) {
    if (this != &other) {
        vertex_count_ = other.vertex_count_;
        matrix_ = other.matrix_;
    }
    return *this;
}

// удаляем граф
MatrixGraph::~MatrixGraph() {
    clear();
}

// очищает граф
void MatrixGraph::clear() {
    vertex_count_ = 0;
    matrix_.clear();
}

// проверяет пустоту
bool MatrixGraph::isEmpty() const {
    return vertex_count_ == 0;
}

// возвращает размер
int MatrixGraph::size() const {
    return vertex_count_;
}

// ввод с клавиатуры
bool MatrixGraph::inputFromKeyboard(int max_n, bool directed) {
    int n = 0;

    std::cout << "Количество вершин (1.." << max_n << "): ";
    if (!readInt(n) || !inRange(n, 1, max_n)) {
        std::cout << "Неверное количество вершин.\n";
        return false;
    }

    vertex_count_ = n;
    matrix_.assign(vertex_count_, std::vector<int>(vertex_count_, 0));

    std::cout << "Введите матрицу смежности (" << n << " x " << n << "):\n";
    for (int i = 0; i < vertex_count_; ++i) {
        for (int j = 0; j < vertex_count_; ++j) {
            int value = 0;
            if (!readInt(value) || (value != 0 && value != 1)) {
                std::cout << "Значения матрицы должны быть 0 или 1.\n";
                clear();
                return false;
            }
            matrix_[i][j] = value;
        }
    }

    if (!directed) {
        for (int i = 0; i < vertex_count_; ++i) {
            for (int j = i + 1; j < vertex_count_; ++j) {
                if (matrix_[i][j] != matrix_[j][i]) {
                    std::cout << "Для неориентированного графа матрица должна быть симметричной.\n";
                    clear();
                    return false;
                }
            }
        }
    }

    return true;
}

// ввод из файла
bool MatrixGraph::inputFromFile(const std::string& file_name, int max_n, bool directed) {
    std::ifstream fin(file_name);
    int n = 0;

    if (!fin.is_open()) {
        std::cout << "Файл не удалось открыть.\n";
        return false;
    }

    fin >> n;
    if (!fin || !inRange(n, 1, max_n)) {
        std::cout << "Неверное количество вершин в файле.\n";
        return false;
    }

    vertex_count_ = n;
    matrix_.assign(vertex_count_, std::vector<int>(vertex_count_, 0));

    for (int i = 0; i < vertex_count_; ++i) {
        for (int j = 0; j < vertex_count_; ++j) {
            int value = 0;
            fin >> value;
            if (!fin || (value != 0 && value != 1)) {
                std::cout << "Неверная матрица в файле.\n";
                clear();
                return false;
            }
            matrix_[i][j] = value;
        }
    }

    if (!directed) {
        for (int i = 0; i < vertex_count_; ++i) {
            for (int j = i + 1; j < vertex_count_; ++j) {
                if (matrix_[i][j] != matrix_[j][i]) {
                    std::cout << "Для неориентированного графа матрица должна быть симметричной.\n";
                    clear();
                    return false;
                }
            }
        }
    }

    return true;
}

// случайный граф
bool MatrixGraph::inputRandom(int max_n, bool directed) {
    int n = 0;
    int percent = 0;

    std::cout << "Количество вершин (1.." << max_n << "): ";
    if (!readInt(n) || !inRange(n, 1, max_n)) {
        std::cout << "Неверное количество вершин.\n";
        return false;
    }

    std::cout << "Вероятность ребра в процентах (0..100): ";
    if (!readInt(percent) || !inRange(percent, 0, 100)) {
        std::cout << "Неверный процент.\n";
        return false;
    }

    std::random_device device;
    std::mt19937 generator(device());
    std::uniform_int_distribution<int> chance(1, 100);

    vertex_count_ = n;
    matrix_.assign(vertex_count_, std::vector<int>(vertex_count_, 0));

    if (directed) {
        for (int i = 0; i < vertex_count_; ++i) {
            for (int j = 0; j < vertex_count_; ++j) {
                if (i != j && chance(generator) <= percent) {
                    matrix_[i][j] = 1;  // есть дуга
                }
            }
        }
    } else {
        for (int i = 0; i < vertex_count_; ++i) {
            for (int j = i; j < vertex_count_; ++j) {
                if (chance(generator) <= percent) {
                    matrix_[i][j] = 1;
                    matrix_[j][i] = 1;  // симметрия
                }
            }
        }
    }

    return true;
}

// печатает матрицу
void MatrixGraph::print() const {
    if (isEmpty()) {
        std::cout << "Граф пуст.\n";
        return;
    }

    for (int i = 0; i < vertex_count_; ++i) {
        for (int j = 0; j < vertex_count_; ++j) {
            std::cout << matrix_[i][j] << ' ';
        }
        std::cout << '\n';
    }
}

// степени вершин
std::vector<int> MatrixGraph::getDegrees() const {
    std::vector<int> degrees(vertex_count_, 0);

    for (int i = 0; i < vertex_count_; ++i) {
        for (int j = 0; j < vertex_count_; ++j) {
            if (matrix_[i][j] != 0) {
                ++degrees[i];  // обычное ребро
            }
        }
        if (matrix_[i][i] != 0) {
            ++degrees[i];  // петля дважды
        }
    }

    return degrees;
}

// города по пересадкам
std::vector<int> MatrixGraph::getCitiesByTransfers(int start, int transfers) const {
    std::vector<int> answer;
    std::vector<int> distance(vertex_count_, -1);
    std::queue<int> queue;
    int flights = transfers + 1;

    --start;
    if (!inRange(start, 0, vertex_count_ - 1) || transfers < 0) {
        return answer;
    }

    distance[start] = 0;
    queue.push(start);

    while (!queue.empty()) {
        int current = queue.front();
        queue.pop();

        for (int next = 0; next < vertex_count_; ++next) {
            if (matrix_[current][next] != 0 && distance[next] == -1) {
                distance[next] = distance[current] + 1;  // кратчайший путь
                queue.push(next);
            }
        }
    }

    for (int i = 0; i < vertex_count_; ++i) {
        if (distance[i] == flights) {
            answer.push_back(i + 1);
        }
    }

    return answer;
}

// обход маршрутов
void MatrixGraph::dfsRoutes(int current, int finish, std::vector<int>& path,
                            std::vector<bool>& used,
                            std::vector<std::vector<int> >& routes) const {
    if (current == finish) {
        routes.push_back(path);
        return;
    }

    for (int next = 0; next < vertex_count_; ++next) {
        if (matrix_[current][next] != 0 && !used[next]) {
            used[next] = true;
            path.push_back(next + 1);
            dfsRoutes(next, finish, path, used, routes);
            path.pop_back();       // откат пути
            used[next] = false;    // город свободен
        }
    }
}

// все простые маршруты
std::vector<std::vector<int> > MatrixGraph::findAllRoutes(int start, int finish) const {
    std::vector<std::vector<int> > routes;
    std::vector<int> path;
    std::vector<bool> used(vertex_count_, false);

    --start;
    --finish;
    if (!inRange(start, 0, vertex_count_ - 1) || !inRange(finish, 0, vertex_count_ - 1)) {
        return routes;
    }

    used[start] = true;
    path.push_back(start + 1);
    dfsRoutes(start, finish, path, used, routes);

    return routes;
}

// пустой список
RouteList::RouteList() {
}

// копируем список
RouteList::RouteList(const RouteList& other) : routes_(other.routes_) {
}

// присваиваем список
RouteList& RouteList::operator=(const RouteList& other) {
    if (this != &other) {
        routes_ = other.routes_;
    }
    return *this;
}

// удаляем список
RouteList::~RouteList() {
    routes_.clear();
}

// задает маршруты
void RouteList::setRoutes(const std::vector<std::vector<int> >& routes) {
    routes_ = routes;
}

// сортирует маршруты
void RouteList::sortRoutes() {
    std::sort(routes_.begin(), routes_.end(),
              [](const std::vector<int>& left, const std::vector<int>& right) {
                  if (left.size() != right.size()) {
                      return left.size() < right.size();
                  }
                  return left < right;  // словарный порядок
              });
}

// сохраняет файл
bool RouteList::saveToFile(const std::string& file_name) const {
    std::ofstream fout(file_name);

    if (!fout.is_open()) {
        return false;
    }

    if (routes_.empty()) {
        fout << -1 << '\n';
        return true;
    }

    fout << routes_.size() << '\n';
    for (const std::vector<int>& route : routes_) {
        for (int city : route) {
            fout << city << ' ';
        }
        fout << '\n';
    }

    return true;
}

// печатает маршруты
void RouteList::print() const {
    if (routes_.empty()) {
        std::cout << "-1\n";
        return;
    }

    std::cout << routes_.size() << '\n';
    for (const std::vector<int>& route : routes_) {
        for (int city : route) {
            std::cout << city << ' ';
        }
        std::cout << '\n';
    }
}

// запускает Graf1
void runGraf1() {
    MatrixGraph graph;
    std::vector<int> degrees;

    if (!inputGraphByMenu(graph, 100, false)) {
        return;
    }

    std::cout << "Исходный граф:\n";
    graph.print();
    std::cout << "Считаем степени вершин. Петли учитываются дважды.\n";

    degrees = graph.getDegrees();
    std::cout << "Результат:\n";
    printNumbers(degrees);
}

// запускает Graf6
void runGraf6() {
    MatrixGraph graph;
    int start = 0;
    int transfers = 0;
    std::vector<int> cities;

    if (!inputGraphByMenu(graph, 25, true)) {
        return;
    }

    std::cout << "Город K: ";
    if (!readInt(start) || !inRange(start, 1, graph.size())) {
        std::cout << "Неверный номер города.\n";
        return;
    }

    std::cout << "Количество пересадок L: ";
    if (!readInt(transfers) || transfers < 0) {
        std::cout << "Неверное количество пересадок.\n";
        return;
    }

    std::cout << "Исходный граф:\n";
    graph.print();
    std::cout << "Ищем кратчайшие пути ровно с " << transfers << " пересадками.\n";

    cities = graph.getCitiesByTransfers(start, transfers);
    std::cout << "Результат:\n";
    printNumbers(cities);
}

// запускает Graf10
void runGraf10() {
    MatrixGraph graph;
    RouteList routes;
    std::string out_file;
    int start = 0;
    int finish = 0;

    if (!inputGraphByMenu(graph, 15, true)) {
        return;
    }

    std::cout << "Город K1: ";
    if (!readInt(start) || !inRange(start, 1, graph.size())) {
        std::cout << "Неверный первый город.\n";
        return;
    }

    std::cout << "Город K2: ";
    if (!readInt(finish) || !inRange(finish, 1, graph.size())) {
        std::cout << "Неверный второй город.\n";
        return;
    }

    std::cout << "Имя файла для вывода: ";
    std::cin >> out_file;

    std::cout << "Исходный граф:\n";
    graph.print();
    std::cout << "Ищем все простые маршруты.\n";

    routes.setRoutes(graph.findAllRoutes(start, finish));
    routes.sortRoutes();

    std::cout << "Результат:\n";
    routes.print();

    if (routes.saveToFile(out_file)) {
        std::cout << "Результат сохранен в файл.\n";
    } else {
        std::cout << "Файл для вывода не удалось открыть.\n";
    }
}
