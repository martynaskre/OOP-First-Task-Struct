//
// Created by Martynas Skrebė on 2022-03-12.
//

#ifndef INC_1_UZD_FAKER_H
#define INC_1_UZD_FAKER_H


#include <string>
#include <random>

struct Faker {
    static const std::vector<std::string> firstNames;
    static const std::vector<std::string> lastNames;

    static std::random_device rd;
    static std::mt19937 mt;

public:
    static int randomNumber(int from, int to);

    static std::string randomFirstName();
    static std::string randomLastName();
    static std::string randomFullName();
    static int randomMark();
};


#endif //INC_1_UZD_FAKER_H
