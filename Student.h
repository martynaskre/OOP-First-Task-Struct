//
// Created by Martynas Skrebė on 2022-02-09.
//

#ifndef INC_1_UZD_STUDENT_H
#define INC_1_UZD_STUDENT_H


#include <string>
#include <vector>

class Student {
    constexpr static const double AVERAGE_WEIGHT = 0.4;
    constexpr static const double EXAM_WEIGHT = 0.6;

    std::string firstName;
    std::string lastName;
    std::vector<int> homeworks;
    int examResult;

public:
    Student& setFirstName(std::string firstName);
    Student& setLastName(std::string lastName);
    Student& setHomeworkResult(int mark);
    Student& setExamResult(int mark);

    std::string getFirstName();
    std::string getLastName();

    double calculateHomeworkAverage();
    double calculateHomeworkMedian();
    double calculateResult(double homeworkMark);
};


#endif //INC_1_UZD_STUDENT_H
