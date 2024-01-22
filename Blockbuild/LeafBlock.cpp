#include "LeafBlock.h"

LeafBlock::LeafBlock() {

	setAllCornersFromTopLeft({ 4, 3 });
	setAllFacesUV(allCornersCoords);

}