#ifndef _SPHERE_H_
#define _SPHERE_H_

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class Sphere { 
  private: 
  	float radius;
  	int slices, stack;

  public:
  	Sphere (float radius, int slices, int stack);
    void draw (); 
    void save (char *path);
}; 

#endif
