#pragma once

#include <string>
#include <vector>

// Задание 1
struct ClientRow {
    int dur;
    int code;
    int year;
    int month;
};

// Задание 2
enum FigureType {
    CIRCLE,
    SQUARE,
    SEGMENT
};

struct Figure {
    FigureType type;
    std::string color;

    union {
        short radius;
        int side;
        float length;
    };
};

// Задание 3
struct Point {
    double x;
    double y;
};

void task1();
void task2();
void task3();