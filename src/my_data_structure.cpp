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

    double algorithm() override {
        double total_probability = 0.0;
        #pragma omp parallel for reduction(+:total_probability)
        for (size_t i = 0; i < crystal.size(); ++i) {
            total_probability += crystal[i].probability;
        }
        return total_probability;
    }
};

extern "C" DataStructure<double>* create_data_structure() {
    return new MyDataStructure();
}
