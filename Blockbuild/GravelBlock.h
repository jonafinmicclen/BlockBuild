#ifndef GRAVELBLOCK_H
#define GRAVELBLOCK_H

#include "CubeBlock.h"

class GravelBlock : public CubeBlock {
public:
    GravelBlock() {
        std::pair<float, float> texturePos = { 1.0f, 1.0f }; // Change the value before base class constructor
    }
};

#endif // GRAVELBLOCK_H
