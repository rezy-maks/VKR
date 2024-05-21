#include "initialize_structure.h"
#include <random>
#include <omp.h>

template <typename T>
const T& clamp(const T& value, const T& min, const T& max) {
    return std::max(min, std::min(value, max));
}

std::vector<atom> initialize_structure(int xSize, int ySize, int zSize) {
    std::vector<atom> crystal;
    crystal.reserve(xSize * ySize * zSize);  // Резервируем память для повышения производительности

    // Создаем генераторы случайных чисел
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> dist(0.5, 0.1);  // Нормальное распределение со средним 0.5 и стандартным отклонением 0.1

    #pragma omp parallel for collapse(3)
    for (int x = 0; x < xSize; ++x) {
        for (int y = 0; y < ySize; ++y) {
            for (int z = 0; z < zSize; ++z) {
                double probability;
                #pragma omp critical
                {
                    probability = clamp(dist(gen), 0.0, 1.0);  // Генерируем и ограничиваем вероятность в диапазоне [0, 1]
                }
                atom new_atom = {x, y, z, probability};
                #pragma omp critical
                crystal.push_back(new_atom);
            }
        }
    }

    return crystal;
}
