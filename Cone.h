#ifndef _CONE_H_
#define _CONE_H_

class Cone { 
  private: 
  	float radius, height;
  	int slices, stack;

  public:
  	Cone (float radius, float height, int slices, int stack);
    void draw (); 
}; 

#endif
