#include <iostream>
#include <fstream>
#include <iomanip>
#include <omp.h>
#include <cstdlib>
#include <vector>
#include "initialize_structure.h"

int main(int argc, char* argv[]) {
    if (argc != 5) {
        std::cerr << "Usage: " << argv[0] << " <Lx> <Ly> <Lz> <iterations>" << std::endl;
        return 1;
    }

    int Lx = std::atoi(argv[1]);
    int Ly = std::atoi(argv[2]);
    int Lz = std::atoi(argv[3]);
    int iterations = std::atoi(argv[4]);
    int max_threads = omp_get_max_threads();

    std::ofstream results("bin/benchmark_results.csv", std::ios::out | std::ios::trunc);
    if (!results.is_open()) {
        std::cerr << "Error opening or creating file for writing results" << std::endl;
        return 1;
    }

    std::ofstream initStructResult("bin/initStruct_results.csv", std::ios::out | std::ios::trunc);
    if (!initStructResult.is_open()) {
        std::cerr << "Error opening or creating file for writing initialization results" << std::endl;
        return 1;
    }

    results << std::setw(10) << "Threads" << std::setw(15) << "Time" << "\n";
    initStructResult << std::setw(10) << "Threads" << std::setw(15) << "InitTime" << "\n";

    for (int num_threads = 1; num_threads <= max_threads; num_threads++) {
        double total_elapsed_time = 0.0;
        double total_init_elapsed_time = 0.0;

        for (int iter = 0; iter < iterations; ++iter) {
            omp_set_num_threads(num_threads);

            // Инициализация структуры
            double init_start_time = omp_get_wtime();
            std::vector<atom> crystal = initialize_structure(Lx, Ly, Lz);
            double init_end_time = omp_get_wtime();
            double init_elapsed_time = init_end_time - init_start_time;

            double start_time = omp_get_wtime();

            // Параллельное вычисление суммы вероятностей каждого элемента вектора
            double total_probability = 0.0;
            #pragma omp parallel for reduction(+:total_probability)
            for (int i = 0; i < crystal.size(); ++i) {
                total_probability += crystal[i].probability;
            }
            
            double end_time = omp_get_wtime();
            double elapsed_time = end_time - start_time;

            // Освобождение памяти от вектора
            crystal.clear();

            total_elapsed_time += elapsed_time;
            total_init_elapsed_time += init_elapsed_time;
        }

        double avg_elapsed_time = total_elapsed_time / iterations;
        double avg_init_elapsed_time = total_init_elapsed_time / iterations;

        results << std::setw(10) << num_threads << std::setw(15) << avg_elapsed_time << "\n";
        initStructResult << std::setw(10) << num_threads << std::setw(15) << avg_init_elapsed_time << "\n";
        std::cout << std::setw(10) << "Threads: " << num_threads << std::setw(15) << ", Avg Init Time: " << avg_init_elapsed_time << " seconds, Avg Exec Time: " << avg_elapsed_time << " seconds" << std::endl;
    }

    results.close();
    initStructResult.close();
    return 0;
}
