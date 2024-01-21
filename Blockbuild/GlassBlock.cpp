#include "GlassBlock.h"

GlassBlock::GlassBlock() : CubeBlock()	{
	setAllCornersFromTopLeft({ 1,3 });
	setAllFacesUV(allCornersCoords);
}