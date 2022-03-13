cmake_minimum_required(VERSION 3.21)
project(1_uzd)

set(CMAKE_CXX_STANDARD 14)

add_executable(1_uzd main.cpp Application.cpp Application.h Student.cpp Student.h Faker.cpp Faker.h Benchmark.cpp Benchmark.h)
