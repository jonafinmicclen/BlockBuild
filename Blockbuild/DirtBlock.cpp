#include "DirtBlock.h"

DirtBlock::DirtBlock() {

	setAllCornersFromTopLeft({ 2,0 });
	setAllFacesUV(allCornersCoords);

}