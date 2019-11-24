#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>

#include "Point.h"
#include "functions.h"
#include "kmeans.h"

int main(int argc, char* argv[])
{
    // TODO use normal command line parser
    if (argc != 5)
    {
        throw std::runtime_error("usage: kmeans <input_file> <output_file_path> <klasters number> <streams number>");
    }

    std::string inputPath = argv[1];
    std::string outputPath = argv[2];
    int klasterNumber = atoi(argv[3]);
    int streamsNumber = atoi(argv[4]);

    std::vector<Point<>> data = readData(inputPath);

    std::vector<Point<>> centers = kmeans(data, klasterNumber);

    std::sort(centers.begin(), centers.end());

    std::ofstream outfile(outputPath);
    outputData(centers, outfile);

    return 0;
}
