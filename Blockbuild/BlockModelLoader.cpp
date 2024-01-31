#include "BlockModelLoader.h"

void BlockModelLoader::loadModel(const std::string filePath) {

    // Open the file
    std::ifstream inputFile(filePath);

    // Check if the file is open
    if (!inputFile.is_open()) {
        std::cerr << "[BlockModelLoader]:Error opening the file." << std::endl;
    }

    // To store model data
    std::vector<blockInfo> model;

    // Read and parse the file
    char discard; // to discard '(' and ','
    int x, y, z, blockN;

    // Read the entire line
    std::string line;
    std::getline(inputFile, line);

    std::vector<std::string> segment;
    segment.push_back(", ");

    for (const auto& character : line) {
        if (character != '{' && character != '}' && character != '(' && character != ')') {
            segment.back() += character;
        }
        if (character == ')') {
            segment.push_back("");
        }
    }

    for (auto& seg : segment) {

        seg = seg.substr(2);

        std::string newSeg;
        std::stringstream ss(seg);
        std::vector<int> segVec;

        while (getline(ss, newSeg, ' ')) {
            std::cout << newSeg << "\n";
            newSeg.erase(std::remove(newSeg.begin(), newSeg.end(), ','), newSeg.end());
            segVec.push_back(stoi(newSeg));
            //std::cout << segVec.back();
        }
    }

    // Close the file
    inputFile.close();


    models.push_back(model);



    //for (const auto& blockInfo : models.back()) {
    //    std::cout << blockInfo.x << ", " << blockInfo.y << ", " << blockInfo.z << ", " << blockInfo.blockN << "\n";
   // }

}