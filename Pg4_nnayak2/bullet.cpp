#include "bullet.h"

bullet* bullet::bulletinstance = NULL;

// distance between two glm::vec3 values
float distance(glm::vec3 p1, glm::vec3 p2) 
{
   return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2) + pow(p1.z - p2.z, 2));
}

bullet* bullet::getBullet()
{
   if (bulletinstance == NULL)
      bulletinstance = new bullet;
   return bulletinstance;
}

void bullet::addNewBullet(glm::vec3 initPos, int dir, int type)
{
   bulletParam temp;
   temp.direction = dir;
   temp.position = initPos;
   temp.type = type;
   PlaySound(TEXT("shoot.wav"), NULL, SND_ALIAS | SND_ASYNC);
   bullets.push_back(temp);
}

void bullet::draw()
{
   glEnable(GL_LIGHTING);
   glColor3f(1.0f, 1.0f, 1.0f);
   for (std::vector<bulletParam>::iterator it = bullets.begin(); it != bullets.end(); it++)
   {
      glPushMatrix();
      glTranslatef(it->position.x, it->position.y, it->position.z);
      if (it->type == 0){
         glColor3f(0.8f, 0.0f, 0.4f);
         glutSolidSphere(0.18, 6, 6);
      }
      else{
         glColor3f(0.0f, 0.4f, 0.8f);
         glutSolidSphere(0.18, 6, 6);
      }
      glPopMatrix();
   }
   glColor3f(1.0f, 1.0f, 1.0f);
   glDisable(GL_LIGHTING);
}

void bullet::updatePosition()
{
   std::vector<bulletParam>::iterator iter = bullets.begin();
   while (iter != bullets.end())
   {
      if (iter->direction == 1)
         iter->position.z += (elapsedTime * 0.008);
      else
         iter->position.z -= (elapsedTime * 0.008);

      if (iter->position.z < -25 || iter->position.z > 5)
         iter = bullets.erase(iter);
      else
         iter++;
   }
}

bool bullet::checkCollision(glm::vec3 pos)
{
   float d;
   std::vector<bulletParam>::iterator iter = bullets.begin();
   while (iter != bullets.end())
   {
      d = distance(pos, iter->position);
      if (d < 0.5)
      {
         //erase bullet and send signal to erase object
         iter = bullets.erase(iter);
         PlaySound(TEXT("explosion.wav"), NULL, SND_ALIAS | SND_ASYNC);
         return true;
      }
      else
         iter++;
   }
   return false;
}