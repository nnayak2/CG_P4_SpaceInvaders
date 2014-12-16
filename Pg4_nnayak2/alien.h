#ifndef ALIEN_H
#define ALIEN_H

#include <vector>
#include "glm/glm.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "tiny_obj_loader.h"
#include <map>
#include "soil/SOIL.h"
#include <GL\glew.h>
#include <GL/glut.h>

#include "bullet.h"
#include "objloader.h"

struct alienParam
{
   glm::vec3 position;
   int type;
   int currentOrientation;
};

class alien
{
   static alien *alieninstance;
   alien(){}
public:
   std::vector<alienParam> aliens;
   float direction, largestZ;
   float elapsedTime;
   int score;
   OBJLOADER *al1, *al2, *al3, *al1_1, *al2_1, *al3_1;
   bool requestEndGame;

   static alien* getAlien();
   void setupGrid();
   void draw();
   void checkCollision();
   void updatePosition();
};

#endif