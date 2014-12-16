#include "scene.h"
#include <math.h>

scene* scene::sceneinstance = NULL;

scene* scene::getScene()
{
	if (sceneinstance == NULL)
		sceneinstance = new scene;
	return sceneinstance;
}

void scene::loadScene()
{
   //load the aliens, barriers and player object
   alien *al = alien::getAlien();
   player *pl = player::getPlayer();
   blocks *bl = blocks::getBlocks();

   al->setupGrid();
   bl->setupGrid();
   pl->setupPlayer();

   //setup glut time
   oldTime = glutGet(GLUT_ELAPSED_TIME);
   oldTime2 = glutGet(GLUT_ELAPSED_TIME);
   oldFrameTimestamp = glutGet(GLUT_ELAPSED_TIME);
   newFrameTimestamp = glutGet(GLUT_ELAPSED_TIME);

   char tmpScoreTxt[] = { 'S', 'c', 'o', 'r', 'e', ' ', ':', ' ', '0', '0', '\0' };
   strcpy(scoreTxt, tmpScoreTxt);

   char tmpLivesTxt[] = { 'L', 'i', 'v', 'e', 's', ' ', ':', ' ', '0', '3', '\0' };
   strcpy(livesTxt, tmpLivesTxt);

   gameEnded = 0;
   difficulty = 1;
   loadTextures();
}

void scene::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   renderBackground();

   alien *al = alien::getAlien();
   player *pl = player::getPlayer();
   blocks *bl = blocks::getBlocks();
   bullet *bu = bullet::getBullet();
   ufo *uf = ufo::getufo();

   //timestamp for updating bullet and alien positions.
   float elapsedTime = glutGet(GLUT_ELAPSED_TIME) - oldFrameTimestamp;
   oldFrameTimestamp = newFrameTimestamp;
   newFrameTimestamp = glutGet(GLUT_ELAPSED_TIME);

   //hack: assume elapsed time cannot be a very high number (without this there is a glitch at first frame)
   elapsedTime = elapsedTime > 1000 ? 0 : elapsedTime;
   al->elapsedTime = elapsedTime;
   bu->elapsedTime = elapsedTime;
   uf->elapsedTime = elapsedTime;

   float deltaTime;
   newTime = glutGet(GLUT_ELAPSED_TIME);
   deltaTime = newTime - oldTime;

   float deltaTime2;
   newTime2 = glutGet(GLUT_ELAPSED_TIME);
   deltaTime2 = newTime2 - oldTime2;

   int sz = al->aliens.size();
   if (sz <= 0 || pl->lives <= 0 || al->requestEndGame == 1)
   {
      gameEnded = 1;
      drawEndStats();
   }

   if (!gameEnded){
      //alien shoots a bullet every 3 seconds
      if (deltaTime > (1/(float)difficulty) * 2000)
      {
         sz = rand() % sz;
         bu->addNewBullet(glm::vec3(al->aliens[sz].position.x, al->aliens[sz].position.y, al->largestZ + 1.0f), 1, 1);
         oldTime = newTime;
      }

      //new ufo enters every 15 seconds
      if (deltaTime2 > 18000)
      {
         uf->addNewUfo();
         oldTime2 = newTime2;
      }
   }

   drawGameText();
   drawFPS(elapsedTime);
   drawDifficulty();

   if (!gameEnded){
      //perform collision detection here
      al->checkCollision();
      bl->checkCollision();
      pl->checkCollision();
      uf->checkCollision();
   }
   //draw objects here
   bu->draw();
   al->draw();
   bl->draw();
   pl->draw();
   uf->draw();

   if (!gameEnded){
      //update positions here
      al->updatePosition();
      pl->updatePosition();
      bu->updatePosition();
      uf->updatePosition();
   }
}

void scene::drawGameText()
{
   glDisable(GL_LIGHTING);
   glPushMatrix();
   glColor3d(1, 1, 1);
   int score = alien::getAlien()->score + ufo::getufo()->score;
   int lives = player::getPlayer()->lives;

   glRasterPos3f(-6.0f, 5.0f, -10.0f);

   char buffer[5];

   itoa(score, buffer, 10);
   scoreTxt[8] = buffer[0];
   scoreTxt[9] = buffer[1];

   itoa(lives, buffer, 10);
   livesTxt[8] = buffer[0];
   livesTxt[9] = buffer[1];

   int i = 0;
   while (scoreTxt[i] != '\0') {
      glutBitmapCharacter(GLUT_BITMAP_9_BY_15, scoreTxt[i]);
      i++;
   }

   glRasterPos3f(3.0f, 5.0f, -10.0f);

   i = 0;
   while (livesTxt[i] != '\0') {
      glutBitmapCharacter(GLUT_BITMAP_9_BY_15, livesTxt[i]);
      i++;
   }

   glPopMatrix();
}

void scene::drawEndStats()
{
   glDisable(GL_LIGHTING);
   glPushMatrix();
   glColor3d(1, 1, 1);
   glRasterPos3f(-2.0f, 3.0f, -8.0f);
   char end[] = "Game Over";

   int i = 0;
   while (i < 10) {
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, end[i]);
      i++;
   }

   glPopMatrix();
}

void scene::drawFPS(float elapsedTime)
{
   static float myCounter;
   myCounter += elapsedTime;
   static float fps;
   if (myCounter > 500)
   {
      fps = 1000 / elapsedTime;
      myCounter = 0;
   }
   glDisable(GL_LIGHTING);
   glPushMatrix();
   glColor3d(1, 1, 1);
   glRasterPos3f(-1.0f, 3.0f, 6.0f);
   char end[20] = "FPS:000000";
   sprintf(end + 4, "%003.2f", fps);

   int i = 0;
   while (i < 11) {
      glutBitmapCharacter(GLUT_BITMAP_9_BY_15, end[i]);
      i++;
   }

   glPopMatrix();
}


void scene::loadTextures()
{
      std::string texName = "background.png";
      
      GLuint tex2d = SOIL_load_OGL_texture(texName.c_str(), SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, 0);
      if (tex2d == 0)
         printf("Loading texture failed \n");
      textures.push_back(tex2d);
}

void scene::renderBackground()
{
   glDisable(GL_LIGHTING);
   glEnable(GL_TEXTURE_2D);

   glBindTexture(GL_TEXTURE_2D, textures[0]);
   glBegin(GL_QUADS);
   glTexCoord2d(0, 0);
   glVertex3d(-50, -2, -100);
   glTexCoord2d(1, 0);
   glVertex3d(-50, -2, 50);
   glTexCoord2d(1, 1);
   glVertex3d(50, -2, 50);
   glTexCoord2d(0, 1);
   glVertex3d(50, -2, -100);
   glEnd();
   glBindTexture(GL_TEXTURE_2D, 0);

   glDisable(GL_TEXTURE_2D);
}

void scene::drawDifficulty()
{
   glDisable(GL_LIGHTING);
   glPushMatrix();
   glColor3d(1, 1, 1);

   glRasterPos3f(-2.5f, 5.0f, -14.0f);

   char text[] = "Difficulty:000";
   char buffer[5];
   itoa(difficulty, buffer, 10);
   //text[11] = buffer[1];
   text[11] = buffer[0];
   text[12] = '\0'; 

   int i = 0;
   while (text[i] != '\0') {
      glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);
      i++;
   }

   glPopMatrix();
}
