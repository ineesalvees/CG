#ifndef _SPHERE_H_
#define _SPHERE_H_

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
