#pragma once

#include <string>

// структуры для ExamTaskC15
struct RecordC15 {
    int code;
    int hours;
    int year;
    int month;
};

struct YearSummary {
    int bestHours;
    int year;
    int bestMonth;
};

// структура для Five13
struct Student {
    std::string surname;
    int score;
};

void RunSort3();
void RunExamTaskC15();
void RunFive13();