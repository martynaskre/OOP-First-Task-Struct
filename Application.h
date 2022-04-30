//
// Created by Martynas Skrebė on 2022-02-09.
//

#ifndef INC_1_UZD_APPLICATION_H
#define INC_1_UZD_APPLICATION_H


#include <fstream>
#include <deque>
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

struct Application {
    std::deque<Student> students;
    std::deque<Student> smartStudents;
    std::deque<Student> dumbStudents;
    CalculationMode calculationMode;
    DataSource dataSource;
    ProgramMode programMode;
    std::ifstream reader;
    std::ofstream writer;

public:
    void run();

protected:
    static int gatherIntValue(const std::string& title, const std::string& error);
    static int gatherMarkValue(const std::string& title, const std::string& error);
    static std::string gatherStringValue(const std::string& title, const std::string& error);
    static bool gatherBoolValue(const std::string& title, const std::string& error);

    void selectProgramMode();
    void selectDataSource();
    void selectFile();
    void processCalculationMode();
    void processIndividualStudent();
    void processStudentsFromFile();
    void writeData(const std::string& filename, std::deque<Student>& students);
    void sortStudents();
    void selectSeedFile();
    void seedStudents();
    void splitStudents();
    void performCalculation();
    void performBenchmark();
};


#endif //INC_1_UZD_APPLICATION_H
