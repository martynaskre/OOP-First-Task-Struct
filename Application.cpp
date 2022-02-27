//
// Created by Martynas Skrebė on 2022-02-09.
//

#include <iostream>
#include <sstream>
#include "Application.h"

Application::Application() {
    srand(time(NULL));
}

void Application::run() {
    // selecting data source
    this->selectDataSource();

    if (this->dataSource == prompt) {
        // processing calculation mode...
        this->processCalculationMode();
    }

    // processing individual students...
    if (this->dataSource == prompt) {
        this->processIndividualStudent();
    } else {
        this->processStudentsFromFile();
    }

    // sorting students...
    this->sortStudents();

    // displaying data...
    this->displayData();
}

int Application::gatherIntValue(std::string title, std::string error) {
    int value;

    do {
        std::cout << title;
        std::cin >> value;

        if (value <= 0) {
            std::cout << error << std::endl;
        }
    } while (value <= 0);

    return value;
}

int Application::gatherMarkValue(std::string title, std::string error) {
    int value;

    do {
        std::cout << title;
        std::cin >> value;

        std::cout << value << std::endl;

        if (value <= 0 || value > 10) {
            std::cout << error << std::endl;
        }
    } while (value <= 0 || value > 10);

    return value;
}

std::string Application::gatherStringValue(std::string title, std::string error) {
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

bool Application::gatherBoolValue(std::string title, std::string error) {
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

        bool enterMarksManually = this->gatherBoolValue("Ar norite pazymius vesti ranka? (y arba n): ", "Neteisingas formatas.");

        do {
            if (enterMarksManually) {
                student.setHomeworkResult(
                        this->gatherMarkValue("Iveskite namu darbo rezultata: ", "Neteisingas namu darbo rezultatas.")
                );
            } else {
                int homeworkMark = this->generateMark();

                std::cout << "Sugeneruotas namu darbo rezultatas: " << homeworkMark << std::endl;

                student.setHomeworkResult(homeworkMark);
            }
        } while (this->gatherBoolValue("Ar norite ivesti namu darba? (y arba n): ", "Neteisingas formatas."));

        bool enterExamManually = this->gatherBoolValue("Ar norite egzamino rezultata vesti ranka? (y arba n): ", "Neteisingas formatas.");

        if (enterExamManually) {
            student.setExamResult(this->gatherMarkValue("Iveskite egzamino rezultata: ", "Neteisingas egzamino rezultatas."));
        } else {
            int examMark = this->generateMark();

            std::cout << "Sugeneruotas egzamino rezultatas: " << examMark << std::endl;

            student.setExamResult(examMark);
        }

        this->students.push_back(student);
    } while (this->gatherBoolValue("Ar norite prideti nauja studenta? (y arba n): ", "Neteisingas formatas."));
}

void Application::displayData() {
    std::cout << std::endl;
    std::cout << std::left << std::setw(20) << "Vardas";
    std::cout << std::left << std::setw(20) << "Pavarde";

    if (this->dataSource == prompt) {
        if (this->calculationMode == median) {
            std::cout << "Galutinis (Med.)" << std::endl;
        } else {
            std::cout << "Galutinis (Vid.)" << std::endl;
        }
    } else {
        std::cout << std::left << std::setw(20) << "Galutinis (Vid.)";
        std::cout << std::left << std::setw(20) << "Galutinis (Med.)" << std::endl;
    }

    if (this->dataSource == prompt) {
        std::cout << "--------------------------------------------------------" << std::endl;
    } else {
        std::cout << "----------------------------------------------------------------------------" << std::endl;
    }

    for (int i = 0; i < this->students.size(); i++) {
        Student *student = &this->students[i];

        std::cout << std::left << std::setw(20) << student->getFirstName();
        std::cout << std::left << std::setw(20) << student->getLastName();
        std::cout << std::setprecision(2);

        if (this->dataSource == prompt) {
            if (this->calculationMode == median) {
                std::cout << student->calculateResult(
                        student->calculateHomeworkMedian()
                );
            } else {
                std::cout << student->calculateResult(
                        student->calculateHomeworkAverage()
                );
            }
        } else {
            std::cout << std::left << std::setw(20) << student->calculateResult(
                    student->calculateHomeworkAverage()
            );

            std::cout << std::left << std::setw(20) << student->calculateResult(
                    student->calculateHomeworkMedian()
            );
        }

        std::cout << std::endl;
    }
}

int Application::generateMark() {
    return 1 + rand() % 10;
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
}

void Application::sortStudents() {
    std::sort(this->students.begin(), this->students.end(), Student::studentSorter);
}
