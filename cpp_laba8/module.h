#pragma once

struct State {
    int count = -1;   // сколько предметов набрали
    int vol = 0;      // суммарный объем
    int last = -1;    // индекс последнего предмета
    int prevW = -1;   // прошлый вес (для восстановления)
};

void task1();
void task2();
void task3();
