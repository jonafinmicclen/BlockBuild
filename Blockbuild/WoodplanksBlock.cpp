#include "WoodplanksBlock.h"

WoodplanksBlock::WoodplanksBlock() : CubeBlock::CubeBlock() {
	setAllCornersFromTopLeft({ 4,0 });
	setAllFacesUV(allCornersCoords);
}