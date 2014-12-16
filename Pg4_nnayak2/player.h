#ifndef PLAYER_H
#define PLAYER_H

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

class player
{
   static player *playerinstance;
   player(){}
public:
   glm::vec3 position;
   static player* getPlayer();
   void setupPlayer();
   void draw();
   void checkCollision();
   void updatePosition();
   int lives;
   OBJLOADER *pl1;
};

#endif