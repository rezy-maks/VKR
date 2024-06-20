#include <vector>
#include <random>
#include <omp.h>
#include <algorithm>
#include <iostream>
#include "../include/DataStructure.hpp"

template <typename T>
const T& clamp(const T& value, const T& min, const T& max) {
    return std::max(min, std::min(value, max));
}

struct atom {
    int x;
    int y;
    int z;
    double probability;
};

class MyDataStructure : public DataStructure<double> {
private:
    std::vector<atom> crystal;

public:
    MyDataStructure() = default;

    void initialize(int xSize, int ySize, int zSize) override {
        crystal.clear();
        crystal.reserve(xSize * ySize * zSize);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::normal_distribution<> dist(0.5, 0.1);

        for (int x = 0; x < xSize; ++x) {
            for (int y = 0; y < ySize; ++y) {
                for (int z = 0; z < zSize; ++z) {
                    double probability = clamp(dist(gen), 0.0, 1.0);
                    atom new_atom = {x, y, z, probability};
                    crystal.push_back(new_atom);
                }
            }
        }
    }

    double algorithm(int num_threads_o) override {
        std::vector<double> local_sums(num_threads_o, 0.0);
        omp_set_num_threads(num_threads_o);

        #pragma omp parallel num_threads(num_threads_o)
        {
            //std::cout << "Threads: " << num_threads << std::endl;
            int thread_id = omp_get_thread_num();
            //std::cout << " Threads: " << num_threads_o<< "; Thread ID: " << thread_id << std::endl;
            double local_sum = 0.0;

            #pragma omp for
            for (size_t i = 0; i < crystal.size(); ++i) {
                local_sum += crystal[i].probability;
            }

        local_sums[thread_id] = local_sum;
        //std::cout << "Threads: " << num_threads<< "; Local sums: " << local_sums[thread_id] << std::endl;
    }

    double total_probability = 0.0;
    for (double sum : local_sums) {
        total_probability += sum;
    }

    return total_probability;
}

};

extern "C" DataStructure<double>* create_data_structure() {
    return new MyDataStructure();
}
