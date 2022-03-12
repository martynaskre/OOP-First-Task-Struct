//
// Created by Martynas Skrebė on 2022-02-09.
//

#include "Student.h"
#include <utility>
#include <iostream>
#include "Faker.h"

Student &Student::setFirstName(std::string firstName) {
    this->firstName = firstName;

    return *this;
}

Student &Student::setLastName(std::string lastName) {
    this->lastName = lastName;

    return *this;
}

Student &Student::setHomeworkResult(int mark) {
    this->homeworks.push_back(mark);

    return *this;
}

Student &Student::setHomeworkResults(std::vector<int> homeworks) {
    this->homeworks = std::move(homeworks);

    return *this;
}

Student &Student::setExamResult(int mark) {
    this->examResult = mark;

    return *this;
}

std::string Student::getFirstName() {
    return this->firstName;
}

std::string Student::getLastName() {
    return this->lastName;
}

std::vector<int> Student::getHomeworkResults() {
    return this->homeworks;
}

int Student::getExamResult() {
    return this->examResult;
}

double Student::calculateHomeworkAverage() {
    double average = 0;

    for (int i = 0; i < this->homeworks.size(); i++) {
        average += this->homeworks[i];
    }

    average /= this->homeworks.size();

    return AVERAGE_WEIGHT * average + EXAM_WEIGHT * this->examResult;
}

double Student::calculateHomeworkMedian() {
    std::sort(this->homeworks.begin(), this->homeworks.end());

    if (this->homeworks.size() % 2 != 0) {
        return (double) this->homeworks[this->homeworks.size() / 2];
    }

    return (double) (this->homeworks[(this->homeworks.size() - 1) / 2] + this->homeworks[this->homeworks.size() / 2]) / 2;
}

double Student::calculateResult(double homeworkMark) {
    return AVERAGE_WEIGHT * homeworkMark + EXAM_WEIGHT * this->examResult;
}

bool Student::studentSorter(Student student1, Student student2) {
    return (student1.getFirstName() < student2.getFirstName());
}

Student Student::generateStudent(int homeworksCount) {
    Student student;

    for (int i = 0; i < homeworksCount; i++) {
        student.setHomeworkResult(Faker::randomMark());
    }

    student.setFirstName(Faker::randomFirstName())
        .setLastName(Faker::randomLastName())
        .setExamResult(Faker::randomMark());

    return student;
}
