//
// Created by Martynas Skrebė on 2022-02-09.
//

#include <iostream>
#include <sstream>
#include "Application.h"
#include "Faker.h"
#include "Benchmark.h"

void Application::run() {
    Benchmark::start("application", "Programos veikimo laikas: ");

    // selecting program mode...
    this->selectProgramMode();

    if (this->programMode == calculation) {
        // selecting data source...
        this->selectDataSource();

        // performing calculations...
        this->performCalculation();
    } else if (this->programMode == seeding) {
        // selecting seed file...
        this->selectSeedFile();

        Benchmark::start("seeding", "Studentu generavimo laikas: ");

        // seeding students...
        this->seedStudents();

        Benchmark::end("seeding");
    } else {
        // performing benchmark...
        this->performBenchmark();
    }

    Benchmark::end("application");
}

int Application::gatherIntValue(const std::string& title, const std::string& error) {
    int value;

    do {
        std::cout << title;
        std::cin >> value;

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (value <= 0) {
            std::cout << error << std::endl;
        }
    } while (value <= 0);

    return value;
}

int Application::gatherMarkValue(const std::string& title, const std::string& error) {
    int value;

    do {
        std::cout << title;
        std::cin >> value;

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (value <= 0 || value > 10) {
            std::cout << error << std::endl;
        }
    } while (value <= 0 || value > 10);

    return value;
}

std::string Application::gatherStringValue(const std::string& title, const std::string& error) {
    std::string value;

    do {
        std::cout << title;
        std::getline(std::cin, value);

        if (value.empty()) {
            std::cout << error << std::endl;
        }
    } while (value.empty());

    return value;
}

bool Application::gatherBoolValue(const std::string& title, const std::string& error) {
    std::string textValue;

    do {
        std::cout << title;
        std::getline(std::cin, textValue);

        if (textValue != "y" && textValue != "n") {
            std::cout << error << std::endl;
        }
    } while (textValue != "y" && textValue != "n");

    return textValue == "y";
}

void Application::selectDataSource() {
    bool useFile = this->gatherBoolValue("Ar duomenis uzkrauti is failo? (y arba n): ", "Neteisingas atsakymo formatas.");

    if (useFile) {
        this->dataSource = file;

        this->selectFile();
    } else {
        this->dataSource = prompt;
    }
}

void Application::selectFile() {
    std::string filename;
    bool errorOccurred = true;

    while (errorOccurred) {
        std::cout << "Iveskite failo pavadinima[numatysis pavadinimas: studentai.txt]: ";
        std::getline(std::cin, filename);

        if (filename.empty()) {
            filename = "studentai.txt";
        }
        
        try {
            this->reader.open(filename);

            if (this->reader.fail()) {
                throw std::invalid_argument("Klaida! Neteisingas failo pavadinimas.");
            }

            errorOccurred = false;
        } catch (const std::invalid_argument& e) {
            std::cout << e.what() << std::endl;
        }
    }
}

void Application::processCalculationMode() {
    bool useAverage = this->gatherBoolValue("Ar norite skaiciuoti vidurki? (y arba n): ", "Neteisingas atsakymo formatas.");

    if (useAverage) {
        std::cout << "Programa skaiciuos studentu vidurki." << std::endl;

        this->calculationMode = average;
    } else {
        std::cout << "Programa skaiciuos studentu mediana." << std::endl;

        this->calculationMode = median;
    }
}

void Application::processIndividualStudent() {
    do {
        Student student;

        student.setFirstName(this->gatherStringValue("Iveskite studento varda: ", "Studento vardas tuscias."))
                .setLastName(this->gatherStringValue("Iveskite studento pavarde: ", "Studento pavarde tuscia."));

        int marksCount = this->gatherIntValue("Iveskite pazymiu skaiciu: ", "Neteisingas pazymiu skaicius.");

        bool enterMarksManually = this->gatherBoolValue("Ar norite pazymius vesti ranka? (y arba n): ", "Neteisingas formatas.");

        for (int i = 0; i < marksCount; i++) {
            if (enterMarksManually) {
                student.setHomeworkResult(
                        this->gatherMarkValue("Iveskite namu darbo rezultata: ", "Neteisingas namu darbo rezultatas.")
                );
            } else {
                int homeworkMark = Faker::randomMark();

                std::cout << "Sugeneruotas namu darbo rezultatas: " << homeworkMark << std::endl;

                student.setHomeworkResult(homeworkMark);
            }
        }

        bool enterExamManually = this->gatherBoolValue("Ar norite egzamino rezultata vesti ranka? (y arba n): ", "Neteisingas formatas.");

        if (enterExamManually) {
            student.setExamResult(this->gatherMarkValue("Iveskite egzamino rezultata: ", "Neteisingas egzamino rezultatas."));
        } else {
            int examMark = Faker::randomMark();

            std::cout << "Sugeneruotas egzamino rezultatas: " << examMark << std::endl;

            student.setExamResult(examMark);
        }

        this->students.push_back(student);
    } while (this->gatherBoolValue("Ar norite prideti nauja studenta? (y arba n): ", "Neteisingas formatas."));
}

void Application::writeData(const std::string& filename, std::deque<Student>& students) {
    this->writer.open(filename);

    std::stringstream header;

    header << std::endl;
    header << std::left << std::setw(20) << "Vardas";
    header << std::left << std::setw(20) << "Pavarde";

    if (this->dataSource == prompt) {
        if (this->calculationMode == median) {
            header << "Galutinis (Med.)" << std::endl;
        } else {
            header << "Galutinis (Vid.)" << std::endl;
        }
    } else {
        header << std::left << std::setw(20) << "Galutinis (Vid.)";
        header << std::left << std::setw(20) << "Galutinis (Med.)" << std::endl;
    }

    if (this->dataSource == prompt) {
        header << "--------------------------------------------------------" << std::endl;
    } else {
        header << "----------------------------------------------------------------------------" << std::endl;
    }

    this->writer.write(header.str().c_str(), header.str().length());

    for (auto & i : students) {
        std::stringstream studentLine;

        Student *student = &i;

        studentLine << std::left << std::setw(20) << student->getFirstName();
        studentLine << std::left << std::setw(20) << student->getLastName();
        studentLine << std::setprecision(2);

        if (this->dataSource == prompt) {
            if (this->calculationMode == median) {
                studentLine << student->calculateResult(
                        student->calculateHomeworkMedian()
                );
            } else {
                studentLine << student->calculateResult(
                        student->calculateHomeworkAverage()
                );
            }
        } else {
            studentLine << std::left << std::setw(20) << student->calculateResult(
                    student->calculateHomeworkAverage()
            );

            studentLine << std::left << std::setw(20) << student->calculateResult(
                    student->calculateHomeworkMedian()
            );
        }

        studentLine << std::endl;

        this->writer.write(studentLine.str().c_str(), studentLine.str().length());
    }

    this->writer.close();
}

void Application::processStudentsFromFile() {
    std::string line;

    this->reader.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while (std::getline(this->reader, line)) {
        Student student;

        std::istringstream lineStream(line);
        std::string firstName, lastName;

        lineStream >> firstName >> lastName;

        student.setFirstName(firstName)
            .setLastName(lastName);

        std::vector<int> marks;
        int mark;

        while (lineStream >> mark) {
            marks.push_back(mark);
        }

        student.setExamResult(marks.back());

        marks.pop_back();

        student.setHomeworkResults(marks);

        this->students.push_back(student);
    }

    this->reader.close();
}

void Application::sortStudents() {
    std::sort(this->students.begin(), this->students.end(), Student::studentSorter);
}

void Application::selectProgramMode() {
    bool benchmarkData = this->gatherBoolValue("Ar norite testuoti programa? (y arba n): ", "Neteisingas atsakymo formatas.");

    if (benchmarkData) {
        this->programMode = benchmark;

        return;
    } else {
        bool seedData = this->gatherBoolValue("Ar generuoti studentu duomenis? (y arba n): ", "Neteisingas atsakymo formatas.");

        this->programMode = (seedData)
                            ? seeding
                            : calculation;
    }
}

void Application::selectSeedFile() {
    std::string filename;
    bool errorOccurred = true;

    while (errorOccurred) {
        std::cout << "Iveskite failo pavadinima[numatysis pavadinimas: studentai.txt]: ";
        std::getline(std::cin, filename);

        if (filename.empty()) {
            filename = "studentai.txt";
        }

        try {
            this->writer.open(filename);

            if (this->writer.fail()) {
                throw std::invalid_argument("Klaida! Neteisingas failo pavadinimas.");
            }

            errorOccurred = false;
        } catch (const std::invalid_argument& e) {
            std::cout << e.what() << std::endl;
        }
    }
}

void Application::seedStudents() {
    int studentsToSeed = this->gatherIntValue("Koki skaiciu studentu norite sugeneruoti: ", "Neteisingas atsakymo formatas");
    int homeworksToSeed = this->gatherIntValue("Koki skaiciu namu darbu sugeneruoti: ", "Neteisingas atsakymo formatas");

    std::stringstream heading;

    heading << std::left << std::setw(20) << "Vardas";
    heading << std::left << std::setw(20) << "Pavarde";

    for (int i = 1; i <= homeworksToSeed; i++) {
        heading << std::left << "ND" << std::setw(8) << i;
    }

    heading << std::left << std::setw(10) << "Egz." << std::endl;

    this->writer.write(heading.str().c_str(), heading.str().length());

    for (int i = 0; i < studentsToSeed; i++) {
        std::stringstream studentStream;

        Student student = Student::generateStudent(homeworksToSeed);

        studentStream << std::left << std::setw(20) << student.getFirstName();
        studentStream << std::left << std::setw(20) << student.getLastName();

        for (int x = 0; x < homeworksToSeed; x++) {
            studentStream << std::left << std::setw(10) << student.getHomeworkResults()[x];
        }

        studentStream << std::left << std::setw(10) << student.getExamResult() << std::endl;

        this->writer.write(studentStream.str().c_str(), studentStream.str().length());
    }

    this->writer.close();
}

void Application::splitStudents() {
    auto smartIterator = std::stable_partition(this->students.begin(), this->students.end(), [](Student &student) {
        return student.calculateHomeworkAverage() <= 5;
    });

    this->smartStudents.insert(this->smartStudents.end(), smartIterator, this->students.end());

    this->students.erase(smartIterator, this->students.end());
}

void Application::performCalculation() {
    if (this->dataSource == prompt) {
        // processing calculation mode...
        this->processCalculationMode();
    }

    // processing individual students...
    if (this->dataSource == prompt) {
        this->processIndividualStudent();
    } else {
        Benchmark::start("reading", "Studentu is failo nuskaitymo laikas: ");

        this->processStudentsFromFile();

        Benchmark::end("reading");
    }

    Benchmark::start("sorting", "Studentu rusiavimo didejimo tvarka laikas: ");

    // sorting students...
    this->sortStudents();

    Benchmark::end("sorting");

    Benchmark::start("splitting", "Studentu perskyrimo i dvi grupes laikas: ");

    // splitting students into separate vectors...
    this->splitStudents();

    Benchmark::end("splitting");

    Benchmark::start("kietuoliai", "Kietuoliu i faila irasymo laikas: ");

    // writing "kietuoliai"...
    this->writeData("kietuoliai.txt", this->smartStudents);

    Benchmark::end("kietuoliai");

    Benchmark::start("vargseliai", "Vargseliu i faila irasymo laikas: ");

    // writing "vargseliai"...
    this->writeData("vargseliai.txt", this->students);

    Benchmark::end("vargseliai");
}

void Application::performBenchmark() {
    std::vector<std::string> files = { "1000.txt", "10000.txt", "100000.txt", "1000000.txt", "10000000.txt" };

    for (auto & file : files) {
        this->reader.open(file);

        if (this->reader.fail()) {
            continue;
        }

        std::cout << file << " testavimas prasideda..." << std::endl;

        this->performCalculation();

        this->smartStudents.clear();
        this->dumbStudents.clear();
        this->students.clear();

        std::cout << std::endl;
    }
}
