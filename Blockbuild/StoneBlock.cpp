#include "StoneBlock.h"

StoneBlock::StoneBlock() : CubeBlock::CubeBlock() {
	setAllCornersFromTopLeft({ 1,0 });
	setAllFacesUV(allCornersCoords);
}