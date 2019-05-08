#ifndef _VERTEX_H_
#define _VERTEX_H_

#include <string>


class Vertex { 
  private: 
  	float x, y, z;

  public:
  	Vertex (float x, float y, float z);
  	Vertex (std::string str);
  	float getx () const;
  	float gety () const;
  	float getz () const;
  	Vertex* normalCalc();
    
}; 

#endif
