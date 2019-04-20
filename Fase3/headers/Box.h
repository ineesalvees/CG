#ifndef _BOX_H_
#define _BOX_H_
#include "Figure.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class Box { 
  private: 
  	float comp, largure, height;
  	int stack;

  public:
  	Figure *figure;
  	Box (float comp, float largure, float height, int stack);
    void draw (); 
    void save (char *path);
}; 

#endif
