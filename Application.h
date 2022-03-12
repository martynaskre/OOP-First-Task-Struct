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

enum DataSource {
    file,
    prompt
};

class Application {
    std::vector<Student> students;
    CalculationMode calculationMode;
    DataSource dataSource;
    std::ifstream reader;

public:
    void run();

protected:
    int gatherIntValue(std::string title, std::string error);
    int gatherMarkValue(std::string title, std::string error);
    std::string gatherStringValue(std::string title, std::string error);
    bool gatherBoolValue(std::string title, std::string error);

    void selectDataSource();
    void selectFile();
    void processCalculationMode();
    void processIndividualStudent();
    void processStudentsFromFile();
    void displayData();
    void sortStudents();
};


#endif //INC_1_UZD_APPLICATION_H
