//
// Created by Martynas Skrebė on 2022-03-13.
//

#ifndef INC_1_UZD_BENCHMARK_H
#define INC_1_UZD_BENCHMARK_H


#include <chrono>
#include <map>

struct BenchmarkResult {
    std::chrono::steady_clock::time_point start;
    std::string title;
};

struct Benchmark {
    static std::map<std::string, BenchmarkResult> benchmarks;

public:
    static void start(const std::string& benchmark, std::string title = "Time difference is: ");
    static void end(const std::string& benchmark);
};


#endif //INC_1_UZD_BENCHMARK_H
