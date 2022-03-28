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

enum ProgramMode {
    seeding,
    calculation,
    benchmark,
};

class Application {
    std::vector<Student> students;
    std::vector<Student> smartStudents;
    std::vector<Student> dumbStudents;
    CalculationMode calculationMode;
    DataSource dataSource;
    ProgramMode programMode;
    std::ifstream reader;
    std::ofstream writer;

public:
    void run();

protected:
    int gatherIntValue(std::string title, std::string error);
    int gatherMarkValue(std::string title, std::string error);
    std::string gatherStringValue(std::string title, std::string error);
    bool gatherBoolValue(std::string title, std::string error);

    void selectProgramMode();
    void selectDataSource();
    void selectFile();
    void processCalculationMode();
    void processIndividualStudent();
    void processStudentsFromFile();
    void writeData(std::string filename, std::vector<Student>& students);
    void sortStudents();
    void selectSeedFile();
    void seedStudents();
    void splitStudents();
    void performCalculation();
    void performBenchmark();
};


#endif //INC_1_UZD_APPLICATION_H
