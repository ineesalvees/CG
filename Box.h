#ifndef _BOX_H_
#define _BOX_H_

class Box { 
  private: 
  	float x, y, z;
  	int slices;

  public:
  	Box (float size, float height);
    void draw (); 
}; 

#endif
