#ifndef MODULE_H
#define MODULE_H

#include <iostream>
#include <string>

class Point {
private:
    double x;
    double y; // свойства методы перегрузка

public:
    Point();
    Point(double newX, double newY);
    Point(const Point& other);
    Point& operator=(const Point& other);
    ~Point();

    double getX() const;
    double getY() const;
    void setX(double newX);
    void setY(double newY);

    double distanceTo(const Point& other) const;

    Point& operator++();
    Point operator++(int);
    Point& operator--();
    Point operator--(int);

    explicit operator int() const;
    operator double() const;

    double operator+(const Point& other) const;
    Point operator+(int value) const;

    friend Point operator+(int value, const Point& point);
    friend std::ostream& operator<<(std::ostream& out, const Point& point);
};

int readInt(const std::string& message);
double readDouble(const std::string& message);
void runTask1();
void runTask2();

#endif
