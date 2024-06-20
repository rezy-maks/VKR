#ifndef DATA_STRUCTURE_HPP
#define DATA_STRUCTURE_HPP

template<typename T>
class DataStructure {
public:
    virtual ~DataStructure() = default;
    virtual void initialize(int xSize, int ySize, int zSize) = 0;
    virtual T algorithm(int x) = 0;
};

#endif // DATA_STRUCTURE_HPP
