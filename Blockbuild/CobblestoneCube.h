#ifndef COBBLESTONECUBE_H
#define COBBLESTONECUBE_H

#include "CubeBlock.h"
#include <string>

class CobblestoneCube : public CubeBlock {
public:
    CobblestoneCube() : CubeBlock({0,0,0}) {
        textureFilePath = "C:/Users/jonat/Music/new/terrain.png";
    }
private:
	const char* textureFilePath = "C:/Users/jonat/Music/new/terrain.png";
};
#endif // COBBLESTONECUBE_H
