#include <iostream>
#include <fstream>
#include <iomanip>
#include <omp.h>
#include <cstdlib>
#include <dlfcn.h>
#include <string>
#include "../include/DataStructure.hpp"

// Тип для функции создания объекта структуры данных
template<typename T>
using create_func = DataStructure<T>* (*)();

int main(int argc, char* argv[]) {
    if (argc != 5) {
        std::cerr << "Usage: " << argv[0] << " <data_structure_and_algorithm_file> <xSize> <ySize> <zSize>" << std::endl;
        return 1;
    }

    int iterations = 10;
    std::string data_structure_file = argv[1];
    int xSize = std::atoi(argv[2]);
    int ySize = std::atoi(argv[3]);
    int zSize = std::atoi(argv[4]);
    int max_threads = omp_get_max_threads();

    // Компиляция файла
    std::string compile_command = "g++ -fPIC -shared -fopenmp -o libdata.so " + data_structure_file;
    
    if (std::system(compile_command.c_str()) != 0) {
        std::cerr << "Compilation failed!" << std::endl;
        return 1;
    }

    // Загрузка скомпилированного модуля
    void* data_handle = dlopen("./libdata.so", RTLD_LAZY);
    if (!data_handle) {
        std::cerr << "Error loading library: " << dlerror() << std::endl;
        return 1;
    }

    // Получение адреса функции создания объекта
    auto create_data_structure = (create_func<double>)dlsym(data_handle, "create_data_structure");
    if (!create_data_structure) {
        std::cerr << "Error locating create_data_structure function: " << dlerror() << std::endl;
        dlclose(data_handle);
        return 1;
    }

    // Создание объекта структуры данных
    DataStructure<double>* data_structure = create_data_structure();
    if (!data_structure) {
        std::cerr << "Error creating data structure!" << std::endl;
        dlclose(data_handle);
        return 1;
    }

    std::ofstream results("bin/benchmark_results.csv", std::ios::out | std::ios::trunc);
    if (!results.is_open()) {
        std::cerr << "Error opening or creating file for writing results" << std::endl;
        delete data_structure;
        dlclose(data_handle);
        return 1;
    }

    results << std::setw(10) << "Threads" << std::setw(15) << "Time" << "\n";

    // Инициализация структуры
    data_structure->initialize(xSize, ySize, zSize);

    for (int num_threads = 1; num_threads <= max_threads; num_threads++) {
        double total_elapsed_time = 0.0;
        //double total_result = 0.0;

        for (int iter = 0; iter < iterations; ++iter) {

            double start_time = omp_get_wtime();
            // Выполнение алгоритма
            double total_result = data_structure->algorithm(num_threads);
            
            double end_time = omp_get_wtime();
            
            double elapsed_time = end_time - start_time;

            total_elapsed_time += elapsed_time;
        }
        //std::cout << std::setw(10) << "Threads: " << num_threads << std::setw(15) << "; Result: " << total_result << std::endl;
        double avg_elapsed_time = total_elapsed_time / iterations;

        results << std::setw(10) << num_threads << std::setw(15) << avg_elapsed_time << "\n";
        std::cout << std::setw(10) << "Threads: " << num_threads << std::setw(15) << "; Avg Exec Time: " << avg_elapsed_time << " seconds" << std::endl;
    }

    results.close();
    delete data_structure;
    dlclose(data_handle);
    return 0;
}
