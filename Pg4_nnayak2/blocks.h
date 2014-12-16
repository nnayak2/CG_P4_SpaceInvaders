#ifndef BLOCKS_H
#define BLOCKS_H

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

struct blocksParam
{
   glm::vec3 position;
};

class blocks
{
   static blocks *blocksinstance;

   GLfloat *bl_ambient;
   GLfloat *bl_diffuse;
   GLfloat *bl_specular;

   blocks()
   {
      bl_ambient = new GLfloat[]{0.8f, 0.8f, 0.0f, 1.0f};
      bl_diffuse = new GLfloat[]{0.7f, 0.7f, 0.0f, 1.0f};
      bl_specular = new GLfloat[]{0.2f, 0.2f, 0.0f, 1.0f};
      tex = SOIL_load_OGL_texture("2.bmp", SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, 0);
   }
public:
   std::vector<glm::vec3> block;
   GLuint tex;
   static blocks* getBlocks();
   void setupGrid();
   void draw();
   void checkCollision();
};

#endif