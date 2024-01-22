#include "CobblestoneBlock.h"

CobblestoneBlock::CobblestoneBlock() {

	setAllCornersFromTopLeft({ 0, 1 });
	setAllFacesUV(allCornersCoords);

}