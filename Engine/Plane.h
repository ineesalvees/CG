#ifndef _PLANE_H_
#define _PLANE_H_

class Plane { 
  private: 
  	float size, height;

  public:
  	Plane (float size, float height);
    void draw (); 
    void save (char *path);
}; 

#endif


