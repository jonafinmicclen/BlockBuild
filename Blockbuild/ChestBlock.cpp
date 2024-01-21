#include "ChestBlock.h"

ChestBlock::ChestBlock() {

	setAllCornersFromTopLeft({ 9,1 });
	setAFaceUV({ 'T', allCornersCoords });
	setAFaceUV({ 'D', allCornersCoords });
 	setAllCornersFromTopLeft({ 10,1 });
	setAFaceUV({ 'R', allCornersCoords });
 	setAFaceUV({ 'B', allCornersCoords });
	setAFaceUV({ 'L', allCornersCoords });	//Rotated
	rotateFaceCW(4);	//This rotates the rotated texture so the chest is rendered correctly
	setAllCornersFromTopLeft({ 11,1 });
	setAFaceUV({ 'F', allCornersCoords });

}