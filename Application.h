//
// Created by Martynas Skrebė on 2022-02-09.
//

#ifndef INC_1_UZD_APPLICATION_H
#define INC_1_UZD_APPLICATION_H


#include <fstream>
#include <vector>
#include "Student.h"

enum CalculationMode {
    average,
    median
};

class Application {
    std::vector<Student> students;
    CalculationMode calculationMode;

public:
    Application();
    void run();

protected:
    int gatherIntValue(std::string title, std::string error);
    int gatherMarkValue(std::string title, std::string error);
    std::string gatherStringValue(std::string title, std::string error);
    bool gatherBoolValue(std::string title, std::string error);

    void processCalculationMode();
    void processIndividualStudent();
    void displayData();

    int generateMark();
};


#endif //INC_1_UZD_APPLICATION_H
