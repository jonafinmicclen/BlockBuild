#ifndef GRAVELBLOCK_H
#define GRAVELBLOCK_H

#include "CubeBlock.h"

class GravelBlock : public CubeBlock {
public:
    std::pair<float, float> texturePos = { 5.0f, 4.0f }; // Change the value before base class constructor
    GravelBlock();
};

#endif // GRAVELBLOCK_H
