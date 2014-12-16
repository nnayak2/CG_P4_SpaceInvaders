#ifndef SCENE_H
#define SCENE_H

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

#include "alien.h"
#include "player.h"
#include "bullet.h"
#include "blocks.h"
#include "ufo.h"

class scene
{
	static scene *sceneinstance;
	scene(){}
public:
	std::vector<tinyobj::shape_t> shapes;
   std::vector<tinyobj::material_t> materials;
   std::vector<GLuint> textures;
   std::vector<std::string> texNames;
   int texNum;
   float oldTime, newTime;  //counter for alien shoting
   float oldTime2, newTime2; //counter for ufo
   float oldFrameTimestamp, newFrameTimestamp;
   char scoreTxt[11], livesTxt[11];
   bool gameEnded;
   int difficulty;
public:
	static scene* getScene();
	void loadScene();
	void draw();
   void drawGameText();
   void drawEndStats();
   void drawFPS(float);
   void drawDifficulty();
   void renderBackground();

   void loadTextures();
   //void setupShaders();
};

#endif