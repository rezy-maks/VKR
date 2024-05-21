// initialize_structure.h
#ifndef INITIALIZE_STRUCTURE_H
#define INITIALIZE_STRUCTURE_H

#include <vector>

struct atom {
    int x;
    int y;
    int z;
    double probability; 
};

// Функция для инициализации вектора
std::vector<atom> initialize_structure(int xSize, int ySize, int zSize);

#endif // INITIALIZE_STRUCTURE_H
