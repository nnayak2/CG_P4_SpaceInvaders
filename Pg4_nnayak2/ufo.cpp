#include "ufo.h"

ufo* ufo::ufoinstance = NULL;

ufo* ufo::getufo()
{
   if (ufoinstance == NULL)
      ufoinstance = new ufo;
   return ufoinstance;
}

void ufo::draw()
{
   glEnable(GL_LIGHTING);
   glColor3f(1.0f, 1.0f, 1.0f);
   for (std::vector<glm::vec3>::iterator it = position.begin(); it != position.end(); it++)
   {
      glPushMatrix();
      glTranslated(it->x, it->y, it->z);
      glRotatef(it->x * 30, 0.0f, 1.0f, 0.0f);
      glScalef(0.08f, 0.08f, 0.08f);
      glRotated(90, 0, 0, -1);
      glColor3f(0.8f, 0.0f, 0.0f);
      glutWireTorus(2, 4, 10, 10);//uf1->batchDraw();
      glPopMatrix();
   }
   glColor3f(1.0f, 1.0f, 1.0f);
   glDisable(GL_LIGHTING);
}

void ufo::checkCollision()
{
   bool collision;
   std::vector<glm::vec3>::iterator iter = position.begin();
   while (iter != position.end())
   {
      //collision test for all bullets here
      collision = bullet::getBullet()->checkCollision(*iter);
      if (collision)
      {
         iter = position.erase(iter);
         score+=5;
      }
      else
         iter++;
   }
}

void ufo::updatePosition()
{

   std::vector<glm::vec3>::iterator it = position.begin();
   while (it != position.end())
   {
      it->x += (elapsedTime * 1.5 * 0.0005);

      if (it->x > 15 || it->x < -15)
         it = position.erase(it);
      else
         it++;
   }

}

void ufo::addNewUfo()
{
   position.push_back(initPos);
}