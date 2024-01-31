#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

class BlockModelLoader
{
protected:

    struct blockInfo {
        int x;
        int y;
        int z;
        int blockN;
    };

public:

    std::vector<std::vector<blockInfo>> models;
    void loadModel(const std::string filePath);
};

