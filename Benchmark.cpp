//
// Created by Martynas Skrebė on 2022-03-13.
//

#include <iostream>
#include <utility>
#include "Benchmark.h"

std::map<std::string, BenchmarkResult> Benchmark::benchmarks;

void Benchmark::start(const std::string& benchmark, std::string title) {
    auto existingBenchmark = Benchmark::benchmarks.find(benchmark);

    if (existingBenchmark != Benchmark::benchmarks.end()) {
        existingBenchmark->second.start = std::chrono::steady_clock::now();
    } else {
        BenchmarkResult result = { std::chrono::steady_clock::now(), std::move(title) };

        Benchmark::benchmarks.insert(std::make_pair(benchmark, result));
    }
}

void Benchmark::end(const std::string& benchmark) {
    auto existingBenchmark = Benchmark::benchmarks.find(benchmark);

    if (existingBenchmark != Benchmark::benchmarks.end()) {
        std::chrono::steady_clock::time_point timeEnd = std::chrono::steady_clock::now();

        std::cout << existingBenchmark->second.title
                  << std::chrono::duration_cast<std::chrono::seconds> (timeEnd - existingBenchmark->second.start).count()
                  << "s" << std::endl;

        Benchmark::benchmarks.erase(existingBenchmark);
    }
}
