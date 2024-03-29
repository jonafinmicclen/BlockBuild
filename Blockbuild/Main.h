#ifndef MAIN_H
#define MAIN_H

#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <cctype>  // Include this for isdigit
#include <string>
#include "RenderedObject.h"
#include "CubeBlock.h"
#include "Camera.h"
#include "InputHandler.h"
#include "WorldManager.h"
#include "GravelBlock.h"
#include "PlayerManager.h"

void renderLoop();
void reshape(int width, int height);
void physicsLoop(int value);

#endif // MAIN_H
 