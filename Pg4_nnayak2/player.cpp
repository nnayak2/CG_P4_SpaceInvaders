#include "player.h"

player* player::playerinstance = NULL;

player* player::getPlayer()
{
   if (playerinstance == NULL)
      playerinstance = new player;
   return playerinstance;
}

void player::setupPlayer()
{
   pl1 = new OBJLOADER("craft.obj");
   this->position = glm::vec3(0.0f, 0.0f, 0.0f);
   lives = 3;
}

void player::draw()
{
   glEnable(GL_LIGHTING);
   glColor3f(1.0f, 1.0f, 1.0f);
   glPushMatrix();
   glTranslatef(position.x, position.y, position.z);
   glRotatef(position.x * 5, 0.0f, 0.0f, 1.0f);
   glScalef(0.03f, 0.03f, 0.03f);
   glColor3f(0.3f, 0.3f, 0.8f);
   pl1->draw();
   glColor3f(1.0f, 1.0f, 1.0f);
   glPopMatrix();
   glColor3f(1.0f, 1.0f, 1.0f);
   glDisable(GL_LIGHTING);
}

void player::checkCollision()
{
   bool collision;
   collision = bullet::getBullet()->checkCollision(this->position);
   if (collision)
      lives--;
}

void player::updatePosition()
{
   //implemented in main with public vec3 position 
}