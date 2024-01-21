#include "GrassBlock.h"

GrassBlock::GrassBlock() {

	setAllCornersFromTopLeft({3,0});
	setAFaceUV({ 'F', allCornersCoords });
	setAFaceUV({ 'B', allCornersCoords });
	setAFaceUV({ 'L', allCornersCoords });
	setAFaceUV({ 'R', allCornersCoords });
	rotateFaceCW(2);
	setAFaceUV({ 'D',{
		allCornersCoords[0],
		allCornersCoords[1],
		{allCornersCoords[1].x, allCornersCoords[1].y - 1 / 16},
		{allCornersCoords[0].x, allCornersCoords[0].y - 1 / 16}
		} });
	setAllCornersFromTopLeft({ 2,0 });
	setAFaceUV({ 'T',allCornersCoords });


}