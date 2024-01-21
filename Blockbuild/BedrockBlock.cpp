#include "BedrockBlock.h"

BedrockBlock::BedrockBlock() : CubeBlock::CubeBlock() {
	setAllCornersFromTopLeft({ 1,1 });
	setAllFacesUV(allCornersCoords);
}