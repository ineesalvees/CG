#ifndef _PLANE_H_
#define _PLANE_H_
#include "Vertex.h"
#include "Figure.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class Plane { 
  private: 
  	float size, height;
    Figure *figure;

  public:
  	Plane (float size, float height);
    void draw (); 
    void save (char *path);
}; 

#endif


