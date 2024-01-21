#include "TntBlock.h"

TntBlock::TntBlock() {

	setAllCornersFromTopLeft({ 8,0 });
	setAFaceUV({ 'F', allCornersCoords });
	setAFaceUV({ 'B', allCornersCoords });
	setAFaceUV({ 'L', allCornersCoords });
	setAFaceUV({ 'R', allCornersCoords });
	rotateFaceCW(2);
	setAllCornersFromTopLeft({ 9,0 });
	setAFaceUV({ 'D', allCornersCoords });
	setAllCornersFromTopLeft({ 10,0 });
	setAFaceUV({ 'T', allCornersCoords });
}