#ifndef MAIN_H
#define MAIN_H

#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include "RenderedObject.h"
#include "CubeBlock.h"
#include "Camera.h"
#include "InputHandler.h"

void renderLoop();
void reshape(int width, int height);
void physicsLoop(int value);

#endif // MAIN_H
