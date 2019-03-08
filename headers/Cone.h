#ifndef _CONE_H_
#define _CONE_H_

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Figure.h"

class Cone { 
  private: 
  	float radius, height;
  	int slices, stack;
  	Figure *figure;

  public:
  	Cone (float radius, float height, int slices, int stack);
    void draw (); 
    void save (char *path);
}; 

#endif
