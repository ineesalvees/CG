#ifndef _VERTEX_H_
#define _VERTEX_H_

class Vertex { 
  private: 
  	float x, y, z;

  public:
  	Vertex (float x, float y, float z);
  	float getx ();
  	float getz ();
  	float gety ();
}; 

#endif
