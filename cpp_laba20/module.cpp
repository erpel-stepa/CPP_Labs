#include "module.h"

#include <cmath>
#include <ctime>
#include <fstream>
#include <limits>
#include <random>
#include <vector>

Point::Point() { // конструктор нулей
    x = 0.0;
    y = 0.0;
}

Point::Point(double newX, double newY) { // конструктор координат
    x = newX;
    y = newY;
}

Point::Point(const Point& other) { // конструктор копии
    x = other.x;
    y = other.y;
}

Point& Point::operator=(const Point& other) { // присваивание
    if (this != &other) {
        x = other.x;
        y = other.y;
    }
    return *this;
}

Point::~Point() { // деструктор
}

double Point::getX() const { // вернуть x
    return x;
}

double Point::getY() const { // вернуть y
    return y;
}

void Point::setX(double newX) { // задать x
    x = newX;
}

void Point::setY(double newY) { // задать y
    y = newY;
}

double Point::distanceTo(const Point& other) const { // расстояние точек
    double dx = x - other.x;
    double dy = y - other.y;
    return std::sqrt(dx * dx + dy * dy);
}

Point& Point::operator++() { // префиксный ++
    x += 1.0;
    return *this;
}

Point Point::operator++(int) { // постфиксный ++
    Point oldPoint(*this);
    x += 1.0;
    return oldPoint;
}

Point& Point::operator--() { // префиксный --
    x -= 1.0;
    return *this;
}

Point Point::operator--(int) { // постфиксный --
    Point oldPoint(*this);
    x -= 1.0;
    return oldPoint;
}

Point::operator int() const { // x как int
    return static_cast<int>(x);
}

Point::operator double() const { // y как double
    return y;
}

double Point::operator+(const Point& other) const { // точка + точка
    return distanceTo(other);
}

Point Point::operator+(int value) const { // точка + число
    return Point(x + value, y);
}

Point operator+(int value, const Point& point) { // число + точка
    return point + value;
}

std::ostream& operator<<(std::ostream& out, const Point& point) { // вывод точки перегрузкой
    out << "Точка(x = " << point.x << ", y = " << point.y << ")";
    return out;
}

static void clearInput() { // очистка ввода
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int readInt(const std::string& message) { // ввод int
    int value;
    while (true) {
        std::cout << message;
        if (std::cin >> value) {
            return value;
        }
        if (std::cin.eof()) {
            return 0;
        }
        std::cout << "Введите целое число\n";
        clearInput();
    }
}

double readDouble(const std::string& message) { // ввод double
    double value;
    while (true) {
        std::cout << message;
        if (std::cin >> value) {
            return value;
        }
        if (std::cin.eof()) {
            return 0.0;
        }
        std::cout << "Введите вещественное число\n";
        clearInput();
    }
}

static Point inputPointFromKeyboard(const std::string& name) { // ввод точки
    std::cout << name << "\n";
    double x = readDouble("x: ");
    double y = readDouble("y: ");
    return Point(x, y);
}

static Point randomPoint() { // случайная точка
    static std::mt19937 generator(static_cast<unsigned int>(std::time(nullptr)));
    std::uniform_int_distribution<int> distribution(-20, 20);
    return Point(distribution(generator), distribution(generator));
}

static bool readNumbersFromFile(const std::string& fileName, std::vector<int>& numbers) { // чтение файла
    std::ifstream file(fileName);
    if (!file.is_open()) {
        return false;
    }

    int count;
    if (!(file >> count) || count < 0) {
        return false;
    }

    numbers.clear();
    for (int i = 0; i < count; ++i) {
        int value;
        if (!(file >> value)) {
            return false;
        }
        numbers.push_back(value);
    }

    return true;
}

static bool inputPointsFromFile(Point& first, Point& second) { // точки из файла
    std::string fileName;
    std::cout << "Имя файла: ";
    std::cin >> fileName;

    std::vector<int> numbers;
    if (!readNumbersFromFile(fileName, numbers)) {
        std::cout << "Не получилось прочитать файл\n";
        return false;
    }

    if (numbers.size() < 4) {
        std::cout << "В файле нужно минимум 4 числа для двух точек\n";
        return false;
    }

    first = Point(numbers[0], numbers[1]);
    second = Point(numbers[2], numbers[3]);
    return true;
}

static bool inputTwoPoints(Point& first, Point& second) { // выбор ввода
    std::cout << "\nКак заполнить точки?\n";
    std::cout << "1) Ввести с клавиатуры\n";
    std::cout << "2) Прочитать из файла\n";
    std::cout << "3) Заполнить случайно\n";

    int choice = readInt("Ваш выбор: ");

    switch (choice) {
        case 1:
            first = inputPointFromKeyboard("Первая точка");
            second = inputPointFromKeyboard("Вторая точка");
            return true;
        case 2:
            return inputPointsFromFile(first, second);
        case 3:
            first = randomPoint();
            second = randomPoint();
            return true;
        default:
            std::cout << "Неверный способ ввода\n";
            return false;
    }
}

static void showConstructorsTest(const Point& source) { // тест конструкторов
    Point defaultPoint;
    Point coordinatePoint(source.getX(), source.getY());
    Point copiedPoint(coordinatePoint);
    Point assignedPoint;
    assignedPoint = copiedPoint;

    std::cout << "\nПроверка конструкторов и присваивания\n";
    std::cout << "По умолчанию: " << defaultPoint << "\n";
    std::cout << "С координатами: " << coordinatePoint << "\n";
    std::cout << "Копия: " << copiedPoint << "\n";
    std::cout << "После присваивания: " << assignedPoint << "\n";
}

void runTask1() { // задание 1
    Point first;
    Point second;

    if (!inputTwoPoints(first, second)) {
        return;
    }

    showConstructorsTest(first);

    std::cout << "\nИсходные данные\n";
    std::cout << "Первая: " << first << "\n";
    std::cout << "Вторая: " << second << "\n";
    std::cout << "Действие: считаем расстояние между точками\n";
    std::cout << "Расстояние: " << first.distanceTo(second) << "\n";
}

void runTask2() { // задание 2
    Point first;
    Point second;

    if (!inputTwoPoints(first, second)) {
        return;
    }

    showConstructorsTest(first);

    std::cout << "\nИсходные данные\n";
    std::cout << "Первая: " << first << "\n";
    std::cout << "Вторая: " << second << "\n";

    Point changedPoint(first);
    std::cout << "\nОперация ++: увеличивает x на 1\n";
    std::cout << "До: " << changedPoint << "\n";
    ++changedPoint;
    std::cout << "После префиксного ++: " << changedPoint << "\n";
    Point oldPlus = changedPoint++;
    std::cout << "Постфиксный ++ вернул: " << oldPlus << "\n";
    std::cout << "После постфиксного ++: " << changedPoint << "\n";

    std::cout << "\nОперация --: уменьшает x на 1\n";
    std::cout << "До: " << changedPoint << "\n";
    --changedPoint;
    std::cout << "После префиксного --: " << changedPoint << "\n";
    Point oldMinus = changedPoint--;
    std::cout << "Постфиксный -- вернул: " << oldMinus << "\n";
    std::cout << "После постфиксного --: " << changedPoint << "\n";

    int intX = static_cast<int>(first);
    double doubleY = first;
    std::cout << "\nПриведение типов\n";
    std::cout << "Явное к int: " << intX << "\n";
    std::cout << "Неявное к double: " << doubleY << "\n";

    std::cout << "\nБинарные операции\n";
    std::cout << "Операция + Point p: вычисляется расстояние до точки p\n";
    Point p = inputPointFromKeyboard("Точка p");
    double distanceByOperator = first + p;
    std::cout << "Первая точка: " << first << "\n";
    std::cout << "Точка p: " << p << "\n";
    std::cout << "Результат first + p: " << distanceByOperator << "\n";

    int shift = readInt("Целое число для прибавления к x: ");
    Point shifted = first + shift;
    std::cout << "\nОперация + целое число: увеличивается координата x\n";
    std::cout << "До: " << first << "\n";
    std::cout << "Действие: first + " << shift << "\n";
    std::cout << "Результат: " << shifted << "\n";
}
