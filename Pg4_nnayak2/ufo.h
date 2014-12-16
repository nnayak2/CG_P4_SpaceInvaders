#ifndef UFO_H
#define UFO_H

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

class ufo
{
   static ufo *ufoinstance;

   GLfloat *bl_ambient;
   GLfloat *bl_diffuse;
   GLfloat *bl_specular;

   ufo()
   { 
      score = 0; 
      uf1 = new OBJLOADER("ufo.obj");

      initPos = glm::vec3(-12.0f, 0.0f, -20.0f);
      bl_ambient = new GLfloat[]{0.0f, 0.6f, 0.0f, 1.0f};
      bl_diffuse = new GLfloat[]{0.0f, 0.8f, 0.0f, 1.0f};
      bl_specular = new GLfloat[]{0.0f, 0.0f, 0.0f, 1.0f};
   }
public:
   std::vector<glm::vec3> position;
   glm::vec3 initPos;
   float elapsedTime;
   int score;
   OBJLOADER *uf1;

   static ufo* getufo();

   void addNewUfo();

   void draw();
   void checkCollision();
   void updatePosition();
};

#endif