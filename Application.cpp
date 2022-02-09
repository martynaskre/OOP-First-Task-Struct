//
// Created by Martynas Skrebė on 2022-02-09.
//

#include <iostream>
#include "Application.h"

Application &Application::setStudentCount(int count) {
    this->studentCount = count;
    this->students = new Student[count];

    return *this;
}

void Application::run() {
    // processing student count....
    this->processStudentCount();

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

void Application::processStudentCount() {
    int count = this->gatherIntValue("Iveskite studentu skaiciu: ", "Neteisingas studentu skaicius.");

    this->setStudentCount(count);
}

void Application::processIndividualStudent() {
    for (int i = 0; i < this->studentCount; i++) {
        Student *student = &this->students[i];

        student->setFirstName(this->gatherStringValue("Iveskite studento varda: ", "Studento vardas tuscias."))
            .setLastName(this->gatherStringValue("Iveskite studento pavarde: ", "Studento pavarde tuscia."))
            .setHomeworkCount(this->gatherIntValue("Iveskite namu darbu skaiciu: ", "Neteisingas namu darbu skaicius."));

        for (int x = 0; x < student->getHomeworkCount(); x++) {
            student->setHomeworkResult(
                x,
                this->gatherMarkValue("Iveskite namu darbo rezultata: ", "Neteisingas namu darbo rezultatas.")
            );
        }

        student->setExamResult(this->gatherMarkValue("Iveskite egzamino rezultata: ", "Neteisingas egzamino rezultatas."));
    }
}

void Application::displayData() {
    std::cout << std::left << std::setw(20) << "Vardas";
    std::cout << std::left << std::setw(20) << "Pavarde";
    std::cout << "Galutinis (Vid.)" << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;

    for (int i = 0; i < this->studentCount; i++) {
        Student *student = &this->students[i];

        std::cout << std::left << std::setw(20) << student->getFirstName() << std::left << std::setw(20) << student->getLastName();
        std::cout << std::setprecision(2) << student->calculateAverage() << std::endl;
    }
}
