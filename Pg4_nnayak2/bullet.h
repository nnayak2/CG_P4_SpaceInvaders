#ifndef BULLET_H
#define BULLET_H

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
#include <windows.h>
#include <mmsystem.h>

struct bulletParam
{
   glm::vec3 position;
   int type;
   int direction;
};

class bullet
{
   static bullet *bulletinstance;

   GLfloat *pl_ambient;
   GLfloat *pl_diffuse;
   GLfloat *pl_specular;

   GLfloat *al_ambient;
   GLfloat *al_diffuse;
   GLfloat *al_specular;

   bullet(){
      //setup different colors for the players bullet and aliens bullet
      pl_ambient = new GLfloat[]{0.3f, 0, 0, 1};
      pl_diffuse = new GLfloat[]{0.7f, 0, 0, 1};
      pl_specular = new GLfloat[]{0.5f, 0, 0, 1};

      al_ambient = new GLfloat[]{0, 0, 0.3f, 1};
      al_diffuse = new GLfloat[]{0, 0, 0.7f, 1};
      al_specular = new GLfloat[]{0, 0, 0.5f, 1};
   }
public:
   std::vector<bulletParam> bullets;
   float elapsedTime;
   static bullet* getBullet();
   void addNewBullet(glm::vec3 , int , int);
   void draw();
   bool checkCollision(glm::vec3);
   void updatePosition();
};

#endif