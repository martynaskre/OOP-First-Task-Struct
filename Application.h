//
// Created by Martynas Skrebė on 2022-02-09.
//

#ifndef INC_1_UZD_APPLICATION_H
#define INC_1_UZD_APPLICATION_H


#include <fstream>
#include "Student.h"

enum CalculationMode {
    average,
    median
};

class Application {
    int studentCount;
    CalculationMode calculationMode;
    Student *students;

public:
    Application();
    Application& setStudentCount(int count);
    void run();

protected:
    int gatherIntValue(std::string title, std::string error);
    int gatherMarkValue(std::string title, std::string error);
    std::string gatherStringValue(std::string title, std::string error);
    bool gatherBoolValue(std::string title, std::string error);

    void processStudentCount();
    void processCalculationMode();
    void processIndividualStudent();
    void displayData();

    int generateMark();
};


#endif //INC_1_UZD_APPLICATION_H
