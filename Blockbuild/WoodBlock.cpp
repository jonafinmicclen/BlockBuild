#include "WoodBlock.h"

WoodBlock::WoodBlock() {

	setAllCornersFromTopLeft({ 5,1 });
	setAFaceUV({ 'T', allCornersCoords });
	setAFaceUV({ 'D', allCornersCoords });
	setAllCornersFromTopLeft({ 4,1 });
	setAFaceUV({ 'R', allCornersCoords });
	setAFaceUV({ 'B', allCornersCoords });
	setAFaceUV({ 'L', allCornersCoords });	//Rotated
	rotateFaceCW(4);	//This rotates the rotated texture so the chest is rendered correctly
	setAFaceUV({ 'F', allCornersCoords });

}