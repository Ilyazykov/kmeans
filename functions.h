#ifndef KMEANS_FUNCTIONS_H
#define KMEANS_FUNCTIONS_H

#include <vector>
#include <iostream>
#include "Point.h"

std::vector<Point<>> readData(std::string filePath);

template <typename T>
void outputData(const std::vector<T>& data, std::ostream& out = std::cout) {
    for (auto x : data) {
        out << x << std::endl;
    }
}

#endif //KMEANS_FUNCTIONS_H
