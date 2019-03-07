#ifndef _PLANE_H_
#define _PLANE_H_

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class Plane { 
  private: 
  	float size, height;

  public:
  	Plane (float size, float height);
    void draw (); 
    void save (char *path);
}; 

#endif


