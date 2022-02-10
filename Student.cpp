//
// Created by Martynas Skrebė on 2022-02-09.
//

#include "Student.h"
#include <utility>
#include <iostream>

Student &Student::setFirstName(std::string firstName) {
    this->firstName = firstName;

    return *this;
}

Student &Student::setLastName(std::string lastName) {
    this->lastName = lastName;

    return *this;
}

Student &Student::setHomeworkCount(int homeworkCount) {
    this->homeworkCount = homeworkCount;
    this->homeworks = new int[homeworkCount];

    return *this;
}

Student &Student::setHomeworkResult(int position, int mark) {
    this->homeworks[position] = mark;

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

int Student::getHomeworkCount() {
    return this->homeworkCount;
}

double Student::calculateHomeworkAverage() {
    double average = 0;

    for (int i = 0; i < this->homeworkCount; i++) {
        average += this->homeworks[i];
    }

    average /= this->homeworkCount;

    return AVERAGE_WEIGHT * average + EXAM_WEIGHT * this->examResult;
}

double Student::calculateHomeworkMedian() {
    std::sort(this->homeworks, this->homeworks + this->homeworkCount);

    if (this->homeworkCount % 2 != 0) {
        return (double) this->homeworks[this->homeworkCount / 2];
    }

    return (double) (this->homeworks[(this->homeworkCount - 1) / 2] + this->homeworks[this->homeworkCount / 2]) / 2;
}

double Student::calculateResult(double homeworkMark) {
    return AVERAGE_WEIGHT * homeworkMark + EXAM_WEIGHT * this->examResult;
}
