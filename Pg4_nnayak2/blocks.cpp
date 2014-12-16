#include "blocks.h"

blocks* blocks::blocksinstance = NULL;

blocks* blocks::getBlocks()
{
   if (blocksinstance == NULL)
      blocksinstance = new blocks;
   return blocksinstance;
}

void blocks::setupGrid()
{
   glm::vec3 pos1(-6, 0, -4);
   glm::vec3 pos2(-5.5, 0, -4);
   glm::vec3 pos3(-5, 0, -4);
   glm::vec3 pos4(-6, 0, -3.5);
   glm::vec3 pos5(-5.5, 0, -3.5);
   glm::vec3 pos6(-5, 0, -3.5);

   glm::vec3 pos7(-2, 0, -4);
   glm::vec3 pos8(-1.5, 0, -4);
   glm::vec3 pos9(-1, 0, -4);
   glm::vec3 pos10(-2, 0, -3.5);
   glm::vec3 pos11(-1.5, 0, -3.5);
   glm::vec3 pos12(-1, 0, -3.5);

   glm::vec3 pos13(6, 0, -4);
   glm::vec3 pos14(5.5, 0, -4);
   glm::vec3 pos15(5, 0, -4);
   glm::vec3 pos16(6, 0, -3.5);
   glm::vec3 pos17(5.5, 0, -3.5);
   glm::vec3 pos18(5, 0, -3.5);

   glm::vec3 pos19(2, 0, -4);
   glm::vec3 pos20(1.5, 0, -4);
   glm::vec3 pos21(1, 0, -4);
   glm::vec3 pos22(2, 0, -3.5);
   glm::vec3 pos23(1.5, 0, -3.5);
   glm::vec3 pos24(1, 0, -3.5);

   this->block.push_back(pos1);
   this->block.push_back(pos2);
   this->block.push_back(pos3);
   this->block.push_back(pos4);
   this->block.push_back(pos5);
   this->block.push_back(pos6);
   this->block.push_back(pos7);
   this->block.push_back(pos8);
   this->block.push_back(pos9);
   this->block.push_back(pos10);
   this->block.push_back(pos11);
   this->block.push_back(pos12);
   this->block.push_back(pos13);
   this->block.push_back(pos14);
   this->block.push_back(pos15);
   this->block.push_back(pos16);
   this->block.push_back(pos17);
   this->block.push_back(pos18);
   this->block.push_back(pos19);
   this->block.push_back(pos20);
   this->block.push_back(pos21);
   this->block.push_back(pos22);
   this->block.push_back(pos23);
   this->block.push_back(pos24);
}

void blocks::draw()
{
   glEnable(GL_LIGHTING);
   glColor3f(1.0f, 1.0f, 1.0f);
   for (std::vector<glm::vec3>::iterator it = block.begin(); it != block.end(); it++)
   {
      glPushMatrix();
      glColor3f(0.8f, 0.6f, 0.0f);
      glTranslatef(it->x, it->y, it->z);

      glutSolidCube(0.5);

      glPopMatrix();
   }
   glColor3f(1.0f, 1.0f, 1.0f);
   glDisable(GL_LIGHTING);
}

void blocks::checkCollision()
{
   bool collision;
   std::vector<glm::vec3>::iterator iter = block.begin();
   while (iter != block.end())
   {
      //collision test for all bullets here
      collision = bullet::getBullet()->checkCollision(*iter);
      if (collision)
      {
         iter = block.erase(iter);
      }
      else
         iter++;
   }
}
