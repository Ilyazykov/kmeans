#include "functions.h"

#include <fstream>
#include <sstream>

std::vector<Point<>> readData(std::string filePath)
{
    std::vector<Point<>> result;

    std::ifstream file(filePath);
    if (!file.is_open())
        throw std::runtime_error("Can't open input file");

    std::string line;
    while (std::getline(file, line)) {

        std::stringstream lineSream(line);
        std::istream_iterator<double> begin(lineSream);
        std::istream_iterator<double> end;

        result.emplace_back(begin, end);
    }

    return result;
}