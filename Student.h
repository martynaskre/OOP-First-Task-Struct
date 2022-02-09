//
// Created by Martynas Skrebė on 2022-02-09.
//

#ifndef INC_1_UZD_STUDENT_H
#define INC_1_UZD_STUDENT_H


#include <string>

class Student {
    const double AVERAGE_WEIGHT = 0.4;
    const double EXAM_WEIGHT = 0.6;

    std::string firstName;
    std::string lastName;
    int homeworkCount;
    int examResult;
    int *homeworks;

public:
    Student& setFirstName(std::string firstName);
    Student& setLastName(std::string lastName);
    Student& setHomeworkCount(int homeworkCount);
    Student& setHomeworkResult(int position, int mark);
    Student& setExamResult(int mark);

    std::string getFirstName();
    std::string getLastName();
    int getHomeworkCount();

    double calculateAverage();
};


#endif //INC_1_UZD_STUDENT_H
