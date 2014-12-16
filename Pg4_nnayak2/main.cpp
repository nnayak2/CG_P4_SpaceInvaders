#include "main.h"

//Define all key press handlers here. Declaration of extern in header
glm::vec3 eye, look, up;
float znear, zfar;
int pixwidth, pixheight;
float shootBreaker = 0;

void Keyboard(unsigned char key, int x, int y)
{
   switch (key)
   {
   case ' ':
      //Player shoots a bullet, shoot breaker limits bullets shot per time value
      if ( !scene::getScene()->gameEnded )//  && shootBreaker > 200000)
      {
         shootBreaker = 0;
         glm::vec3 temp = player::getPlayer()->position;
         bullet::getBullet()->addNewBullet(glm::vec3(temp.x, temp.y, temp.z - 1.0f), -1, 0);
      }
      break;
   }
}

void SpecialInput(int key, int x, int y)
{
   switch (key)
   {
   case GLUT_KEY_UP:
      if (!scene::getScene()->gameEnded)
         scene::getScene()->difficulty > 8 ? 9 : scene::getScene()->difficulty++;
      break;
   case GLUT_KEY_DOWN:
      if (!scene::getScene()->gameEnded)
         scene::getScene()->difficulty < 2 ? 1 : scene::getScene()->difficulty--;
      break;
   case GLUT_KEY_LEFT:
      if (!scene::getScene()->gameEnded)
         (player::getPlayer()->position.x - 1) < -7 ? -7 : player::getPlayer()->position.x-=0.5;
      break;
   case GLUT_KEY_RIGHT:
      if (!scene::getScene()->gameEnded)
         (player::getPlayer()->position.x + 1) > 7 ? 7: player::getPlayer()->position.x+=0.5;
      break;
   }
}

void draw()
{
   shootBreaker += glutGet(GLUT_ELAPSED_TIME);
   scene::getScene()->draw();
   glutSwapBuffers();
}

void redraw()
{
   glutPostRedisplay();
}

void handle_menu(int ID)
{
   glBindTexture(GL_TEXTURE_2D, scene::getScene()->textures[ID]);
}


void initialiseGLUT(int argc, char **argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
   glutInitWindowSize(pixwidth, pixheight);
   glutCreateWindow("\t CSC561: Space Invaders");

   glShadeModel(GL_SMOOTH);
   glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
   glClearDepth(1.0f);
   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LEQUAL);
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

   if (glewInit() != GLEW_OK)
   {
      printf("problem\n");
   }

   //scene *scn = scene::getScene();
   scene::getScene()->loadScene();

   //Initialize the model view and projection matrices
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(45, (float)1, znear, zfar);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt(eye.x, eye.y, eye.z, look.x, look.y, look.z, up.x, up.y, up.z);

   glEnable(GL_LIGHTING);
   GLfloat LightAmbient[] = { 0.4f, 0.4f, 0.4f, 1.0f };
   GLfloat LightDiffuse[] = { 0.7f, 0.7f, 0.7f, 1.0f };
   GLfloat LightSpecular[] = { 0.2f, 0.2f, 0.2f, 1.0f };
   GLfloat LightPosition[] = { 0.0f, 20.0f, 2.0f, 1.0f };

   glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
   glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpecular);
   glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
   glEnable(GL_LIGHT0);

   GLfloat *bl_ambient = new GLfloat[]{0.1f, 0.6f, 0.6f, 1.0f};
   GLfloat *bl_diffuse = new GLfloat[]{0.1f, 0.8f, 0.8f, 1.0f};
   GLfloat *bl_specular = new GLfloat[]{0.0f, 0.2f, 0.2f, 1.0f};

   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, bl_ambient);
   glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, bl_diffuse);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, bl_specular);

   glEnable(GL_COLOR_MATERIAL);

   glutKeyboardFunc(Keyboard);
   glutSpecialFunc(SpecialInput);
   glutDisplayFunc(draw);
   glutIdleFunc(redraw);
   glutMainLoop();
}

int main(int argc, char* argv[])
{
      pixheight = 512;
      pixwidth = 512;
 
      eye = glm::vec3(0, 12, 13);
      look = glm::vec3(0, 0, -5);
      up = glm::vec3(0, 0.5, 0);
      znear = 0.1;
      zfar = 100;

   initialiseGLUT(argc, argv);
}

