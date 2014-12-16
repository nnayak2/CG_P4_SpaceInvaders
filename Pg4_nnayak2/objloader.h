#ifndef OBJLOADER_H
#define OBJLOADER_H

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

class OBJLOADER
{
public:

   OBJLOADER(char *filename)
   {
      std::string err = tinyobj::LoadObj(shapes, materials, filename);
      vertex_buffer = 0;
      vertex_array_object = 0;
      index_buffer = 0;
      normal_buffer = 0;
      tex_buffer = 0;

      initData();

      if (!err.empty())
      {
         std::cerr << err << std::endl;
         exit(1);
      }
   }

   std::vector<tinyobj::shape_t> shapes;
   std::vector<tinyobj::material_t> materials;
   GLuint vertex_buffer, vertex_array_object, index_buffer, normal_buffer, tex_buffer;
   std::vector<GLuint> textures;
   void draw();
   void initData();
   void batchDraw();
   void subInitData();

};

#endif