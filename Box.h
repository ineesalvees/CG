#ifndef _BOX_H_
#define _BOX_H_

class Box { 
  private: 
  	float xx, y, zz;
  	int slices;

  public:
  	Box (float x, float y, float z, int slices);
    void draw (); 
    void save (char *path);
}; 

#endif
