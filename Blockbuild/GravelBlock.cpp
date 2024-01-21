#include "GravelBlock.h"

GravelBlock::GravelBlock() : CubeBlock::CubeBlock() {
	setAllCornersFromTopLeft({ 0,0 });
	setAllFacesUV(allCornersCoords);
}