#ifndef _BOX_H_
#define _BOX_H_

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class Box { 
  private: 
  	float xx, y, zz;
  	int slices;

  public:
  	Box (float x, float y, float z, int slices);
    void draw (double comp, double largure, double height, int stack); 
    void save (char *path);
}; 

#endif
