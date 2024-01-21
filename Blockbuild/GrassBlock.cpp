#include "GrassBlock.h"

GrassBlock::GrassBlock() {

	setAllCornersFromTopLeft({3,0});
	setAFaceUV({ 'F', allCornersCoords });
	setAFaceUV({ 'B', allCornersCoords });
	setAFaceUV({ 'L', allCornersCoords });
	setAFaceUV({ 'R', allCornersCoords });
	rotateFaceCW(2);
	setAFaceUV({ 'D',{
		allCornersCoords[3],
		allCornersCoords[2],
		{allCornersCoords[2].x, 1.0f/(16*16)},	// Idk where grass gets its texture from
		{allCornersCoords[3].x, 1.0f/(16*16)}
		} });
	setAllCornersFromTopLeft({ 2,0 });
	setAFaceUV({ 'T',allCornersCoords });


}