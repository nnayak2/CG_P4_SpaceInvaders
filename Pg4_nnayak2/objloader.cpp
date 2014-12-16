#include "objloader.h"

void OBJLOADER::draw()
{
   for (std::vector<tinyobj::shape_t>::iterator iter = shapes.begin();
      iter != shapes.end(); iter++)
   {
      for (std::vector<unsigned int>::iterator ind = iter->mesh.indices.begin();
         ind != iter->mesh.indices.end(); ind++)
      {
         bool normalsPresent = 1;
         if ((iter->mesh.normals).size() == 0)
            normalsPresent = 0;

         glm::vec3 v1, v2, v3;
         glm::vec3 n1, n2, n3;

         //Read and store individual vertices, normals and tex coords of the triangle
         v1 = glm::vec3((iter->mesh.positions)[*ind * 3], (iter->mesh.positions)[*ind * 3 + 1], (iter->mesh.positions)[*ind * 3 + 2]);
         if (normalsPresent) n1 = glm::vec3((iter->mesh.normals)[*ind * 3], (iter->mesh.normals)[*ind * 3 + 1], (iter->mesh.normals)[*ind * 3 + 2]);
         ind++;
         v2 = glm::vec3((iter->mesh.positions)[*ind * 3], (iter->mesh.positions)[*ind * 3 + 1], (iter->mesh.positions)[*ind * 3 + 2]);
         if (normalsPresent) n2 = glm::vec3((iter->mesh.normals)[*ind * 3], (iter->mesh.normals)[*ind * 3 + 1], (iter->mesh.normals)[*ind * 3 + 2]);
         ind++;
         v3 = glm::vec3((iter->mesh.positions)[*ind * 3], (iter->mesh.positions)[*ind * 3 + 1], (iter->mesh.positions)[*ind * 3 + 2]);
         if (normalsPresent) n3 = glm::vec3((iter->mesh.normals)[*ind * 3], (iter->mesh.normals)[*ind * 3 + 1], (iter->mesh.normals)[*ind * 3 + 2]);


         //try some default values for normals and textures since it wasn't present in obj
         if (!normalsPresent)
            n1 = n2 = n3 = -glm::normalize(glm::cross((v3 - v1), (v2 - v1)));

         glBegin(GL_TRIANGLES);

         glNormal3f(n1.x, n1.y, n1.z);
         glVertex3f(v1.x, v1.y, v1.z);

         glNormal3f(n2.x, n2.y, n2.z);
         glVertex3f(v2.x, v2.y, v2.z);

         glNormal3f(n3.x, n3.y, n3.z);
         glVertex3f(v3.x, v3.y, v3.z);

         glEnd();
      }
   }
}


void OBJLOADER::initData()
{
   // Copy data to GPU
   glGenVertexArrays(1, &vertex_array_object);
   glBindVertexArray(vertex_array_object);

   // Vertex
   size_t vertex_buffer_size = 0;
   for (size_t i = 0; i < shapes.size(); i++)
   {
      vertex_buffer_size += sizeof(float)* shapes[i].mesh.positions.size();
   }

   glGenBuffers(1, &vertex_buffer);
   glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
   glBufferData(GL_ARRAY_BUFFER, vertex_buffer_size, NULL, GL_DYNAMIC_COPY);
   vertex_buffer_size = 0;

   for (size_t i = 0; i < shapes.size(); i++)
   {
      glBufferSubData(GL_ARRAY_BUFFER, vertex_buffer_size, sizeof(float)* shapes[i].mesh.positions.size(), &shapes[i].mesh.positions[0]);
      vertex_buffer_size += sizeof(float)* shapes[i].mesh.positions.size();
   }

   // Index
   size_t index_buffer_size = 0;
   for (size_t i = 0; i < shapes.size(); i++)
   {
      index_buffer_size += sizeof(unsigned int)* shapes[i].mesh.indices.size();
   }

   glGenBuffers(1, &index_buffer);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_size, NULL, GL_STATIC_DRAW);
   index_buffer_size = 0;
   for (size_t i = 0; i < shapes.size(); i++) {
      glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_size, sizeof(unsigned int)* shapes[i].mesh.indices.size(), &shapes[i].mesh.indices[0]);
      index_buffer_size += sizeof(unsigned int)* shapes[i].mesh.indices.size();
   }

   glBindVertexArray(0);
}

void OBJLOADER::subInitData()
{
   // Copy data to GPU
   glBindVertexArray(vertex_array_object);

   // Vertex
   size_t vertex_buffer_size = 0;
   for (size_t i = 0; i < shapes.size(); i++)
   {
      vertex_buffer_size += sizeof(float)* shapes[i].mesh.positions.size();
   }
   glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
   glBufferData(GL_ARRAY_BUFFER, vertex_buffer_size, NULL, GL_DYNAMIC_COPY);
   vertex_buffer_size = 0;

   for (size_t i = 0; i < shapes.size(); i++)
   {
      glBufferSubData(GL_ARRAY_BUFFER, vertex_buffer_size, sizeof(float)* shapes[i].mesh.positions.size(), &shapes[i].mesh.positions[0]);
      vertex_buffer_size += sizeof(float)* shapes[i].mesh.positions.size();
   }


   // Index
   size_t index_buffer_size = 0;
   for (size_t i = 0; i < shapes.size(); i++)
   {
      index_buffer_size += sizeof(unsigned int)* shapes[i].mesh.indices.size();
   }
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_size, NULL, GL_STATIC_DRAW);
   index_buffer_size = 0;

   for (size_t i = 0; i < shapes.size(); i++) {
      glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_size, sizeof(unsigned int)* shapes[i].mesh.indices.size(), &shapes[i].mesh.indices[0]);
      index_buffer_size += sizeof(unsigned int)* shapes[i].mesh.indices.size();
   }
}

void OBJLOADER::batchDraw()
{
   subInitData();

   glBindVertexArray(vertex_array_object);
   glEnableVertexAttribArray(0);

   size_t vertex_buffer_size = 0;
   size_t index_buffer_size = 0;

   for (size_t i = 0; i < shapes.size(); i++)
   {
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)vertex_buffer_size);
      glDrawElements(GL_TRIANGLES, shapes[i].mesh.indices.size(), GL_UNSIGNED_INT, (void*)index_buffer_size);

      vertex_buffer_size += sizeof(float)* shapes[i].mesh.positions.size();
      index_buffer_size += sizeof(unsigned int)*shapes[i].mesh.indices.size();
   }

   glDisableVertexAttribArray(0);
   glBindVertexArray(0);

   glFlush();
   glFinish();
}