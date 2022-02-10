//
// Created by Martynas Skrebė on 2022-02-09.
//

#include <iostream>
#include "Application.h"

Application::Application() {
    srand(time(NULL));
}

void Application::run() {
    // processing calculation mode...
    this->processCalculationMode();

    // processing individual students...
    this->processIndividualStudent();

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
        std::cin >> value;

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
        std::cin >> textValue;

        if (textValue != "y" && textValue != "n") {
            std::cout << error << std::endl;
        }
    } while (textValue != "y" && textValue != "n");

    return textValue == "y";
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

    if (this->calculationMode == median) {
        std::cout << "Galutinis (Med.)" << std::endl;
    } else {
        std::cout << "Galutinis (Vid.)" << std::endl;
    }

    std::cout << "--------------------------------------------------------" << std::endl;

    for (int i = 0; i < this->students.size(); i++) {
        Student *student = &this->students[i];

        std::cout << std::left << std::setw(20) << student->getFirstName() << std::left << std::setw(20) << student->getLastName();
        std::cout << std::setprecision(2);

        if (this->calculationMode == median) {
            std::cout << student->calculateResult(
                student->calculateHomeworkMedian()
            );
        } else {
            std::cout << student->calculateResult(
                    student->calculateHomeworkAverage()
            );
        }

        std::cout << std::endl;
    }
}

int Application::generateMark() {
    return 1 + rand() % 10;
}
