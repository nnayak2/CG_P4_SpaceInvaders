#include "alien.h"

alien* alien::alieninstance = NULL;

GLuint v, f, p;
char *vs = NULL, *fs = NULL;

//some local functions for the shader
char *textFileRead(char *fn)
{
   FILE *fp;
   char *content = NULL;

   int count = 0;

   if (fn != NULL) {
      fp = fopen(fn, "rt");

      if (fp != NULL) {

         fseek(fp, 0, SEEK_END);
         count = ftell(fp);
         rewind(fp);

         if (count > 0) {
            content = (char *)malloc(sizeof(char) * (count + 1));
            count = fread(content, sizeof(char), count, fp);
            content[count] = '\0';
         }
         fclose(fp);
      }
   }

   if (content == NULL)
   {
      fprintf(stderr, "ERROR: could not load in file %s\n", fn);
      exit(1);
   }
   return content;
}

GLint getUniLoc(GLuint program, const char *name)
{
   GLint loc;
   loc = glGetUniformLocation(program, name);
   if (loc == -1)
      printf("No such uniform named \"%s\"\n", name);

   return loc;
}

void printShaderLog(GLuint obj)
{
   GLint infoLogLength = 0;
   GLsizei charsWritten = 0;
   GLchar *infoLog;

   glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &infoLogLength);

   if (infoLogLength > 0)
   {
      infoLog = (char *)malloc(infoLogLength);
      glGetShaderInfoLog(obj, infoLogLength, &charsWritten, infoLog);
      printf("%s\n", infoLog);
      free(infoLog);
   }
}

void printProgramLog(GLuint obj)
{
   GLint infoLogLength = 0;
   GLsizei charsWritten = 0;
   GLchar *infoLog;

   glGetProgramiv(obj, GL_INFO_LOG_LENGTH, &infoLogLength);

   if (infoLogLength > 0)
   {
      infoLog = (char *)malloc(infoLogLength);
      glGetProgramInfoLog(obj, infoLogLength, &charsWritten, infoLog);
      printf("%s\n", infoLog);
      free(infoLog);
   }
}

void setupShaders()
{
   v = glCreateShader(GL_VERTEX_SHADER);
   f = glCreateShader(GL_FRAGMENT_SHADER);

   vs = textFileRead("shader.vert");
   fs = textFileRead("shader.frag");

   const char * ff = fs;
   const char * vv = vs;

   glShaderSource(v, 1, &vv, NULL);
   glShaderSource(f, 1, &ff, NULL);

   free(vs); free(fs);

   glCompileShader(v);
   glCompileShader(f);

   printShaderLog(v);
   printShaderLog(f);

   p = glCreateProgram();
   glAttachShader(p, f);
   glAttachShader(p, v);

   glLinkProgram(p);
   printProgramLog(p);
}


alien* alien::getAlien()
{
   if (alieninstance == NULL)
      alieninstance = new alien;
   return alieninstance;
}

void alien::setupGrid()
{
   direction = 1.0f;
   largestZ = -13;
   score = 0;
   requestEndGame = 0;

   al1 = new OBJLOADER("1.obj");
   al2 = new OBJLOADER("2.obj");
   al3 = new OBJLOADER("3.obj");
   al1_1 = new OBJLOADER("1_1.obj");
   al2_1 = new OBJLOADER("2_1.obj");
   al3_1 = new OBJLOADER("3_1.obj");

   float x = 0.5;
   for (int j = -17; j < -12; j++)
   {
      for (int i = -4; i < 5; i++)
      {
         alienParam temp;
         temp.position = glm::vec3(i, 0, j);
         temp.type = (int)x;
         aliens.push_back(temp);
      }
      x+=0.5;
   }

   setupShaders();
}

void alien::draw()
{
   glUseProgram(p);
   glEnable(GL_LIGHTING);
   glColor3f(1.0f, 1.0f, 1.0f);

   for (std::vector<alienParam>::iterator it = aliens.begin(); it != aliens.end(); it++)
   {
      glPushMatrix();
      glColor3f(1.0f, 1.0f, 1.0f);
      glTranslated(it->position.x, it->position.y,  it->position.z );
      glScalef(0.007f, 0.007f, 0.01f);

      if (it->type == 0) glUniform1f(getUniLoc(p, "type"), 0.0);
      else if (it->type == 1) glUniform1f(getUniLoc(p, "type"), 1.0);
      else glUniform1f(getUniLoc(p, "type"), 2.0);

      glUniform1f(getUniLoc(p, "time"), glutGet(GLUT_ELAPSED_TIME));
      int temp = it->position.x + 40; //some random offset so no artifacts at x = -1,0,1 

      if (it->type == 0)
      {
         if (temp % 2 == 0)
            al1->batchDraw();
         else
            al1_1->batchDraw();
      }
      else if (it->type == 1)
      {
         if (temp % 2 == 0)
            al2->batchDraw();
         else
            al2_1->batchDraw();
      }
      else
      {
         if (temp % 2 == 0)
            al3->batchDraw();
         else
            al3_1->batchDraw();
      }
             
      glColor3f(1.0f, 1.0f, 1.0f);
      glPopMatrix();
   }

   glColor3f(1.0f, 1.0f, 1.0f);
   glDisable(GL_LIGHTING);
   glUseProgram(0);
}

void alien::checkCollision()
{
   bool collision;
   std::vector<alienParam>::iterator iter = aliens.begin();
   while (iter != aliens.end())
   {
      //collision test for all bullets here
      collision = bullet::getBullet()->checkCollision(iter->position);
      if (collision) 
      {
         //Scoring pattern, 3 for the far ones, 2 for middle ones and 1 for close ones
         if (iter->type == 0)
            score += 3;
         else if (iter->type == 1)
            score += 2;
         else
            score++;
         //finally erase the alien also
         iter = aliens.erase(iter);
      }
      else
         iter++;
   }
}

void alien::updatePosition()
{
   int flag = 0;

   for (std::vector<alienParam>::iterator it = aliens.begin(); it != aliens.end(); it++)
   {
      it->position.x += ( elapsedTime * direction * 0.0005);
      if (it->position.x > 8 || it->position.x < -8)
         flag = 1;
   }

   if (flag)
   {
      direction = -direction * 1.2;
      for (std::vector<alienParam>::iterator it = aliens.begin(); it != aliens.end(); it++)
      {
         it->position.z += 0.5;

         //largest Z is used to reposition the bullets fired by alien so it doesnt kill another alien
         if (it->position.z > largestZ)
            largestZ = it->position.z;

         if (it->position.z > -5)
         {
            requestEndGame = 1;
         }
      }
   }
}