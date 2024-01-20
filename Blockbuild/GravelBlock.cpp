#include "GravelBlock.h"

GravelBlock::GravelBlock() : CubeBlock::CubeBlock() {
	setTexturePos({ 1.0f,1.0f });
	setVertexAndCoords();
	std::cout << "set";
}