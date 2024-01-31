#include "BlockModelLoader.h"

void BlockModelLoader::loadModel(const std::string filePath) {

    // Open the file
    std::ifstream inputFile("example.txt");

    // Check if the file is open
    if (!inputFile.is_open()) {
        std::cerr << "[BlockModelLoader]:Error opening the file." << std::endl;
    }

    // To store model data
    std::vector<blockInfo> model;

    // Read and parse the file
    char discard; // to discard '(' and ','
    int x, y, z, blockN;

    while (inputFile >> discard >> x >> discard >> y >> discard >> z >> discard >> blockN >> discard) {
        model.push_back({ x, y, z, blockN });
    }

    // Close the file
    inputFile.close();

    models.push_back(model);

}