//
// Created by Martynas Skrebė on 2022-02-09.
//

#ifndef INC_1_UZD_APPLICATION_H
#define INC_1_UZD_APPLICATION_H


#include <fstream>
#include "Student.h"

class Application {
    int studentCount;
    Student *students;

public:
    Application& setStudentCount(int count);
    void run();

protected:
    int gatherIntValue(std::string title, std::string error);
    int gatherMarkValue(std::string title, std::string error);
    std::string gatherStringValue(std::string title, std::string error);

    void processStudentCount();
    void processIndividualStudent();
    void displayData();
};


#endif //INC_1_UZD_APPLICATION_H
