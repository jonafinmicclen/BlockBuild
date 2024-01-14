#include "CubeBlock.h"

//Init
CubeBlock::CubeBlock() {

    addVertex({-0.5, -0.5, -0.5});
    addVertex({-0.5, 0.5, -0.5}); 
    addVertex({0.5, 0.5, -0.5}); 
    addVertex({0.5, -0.5, -0.5}); 
    addVertex({-0.5, -0.5, 0.5});  
    addVertex({-0.5, 0.5, 0.5});   
    addVertex({0.5, 0.5, 0.5});   
    addVertex({0.5, -0.5, 0.5});  

    addSurface({0, 1, 2, 3});
    addSurface({4, 7, 6, 5});
    addSurface({0, 3, 7, 4});
    addSurface({1, 5, 6, 2});
    addSurface({1, 0, 4, 5});
    addSurface({3, 2, 6, 7});
}
