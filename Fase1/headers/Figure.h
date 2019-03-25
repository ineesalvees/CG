#ifndef _FIGURE_H_
#define _FIGURE_H_

#include "Vertex.h"
#include <vector>

class Figure { 
  private: 
  	std::vector<Vertex> vertexes;
  public:
  	Vertex getvertex (int i);
  	void pushvertex (Vertex *v);
  	void add (float x, float y, float z);
  	int getsize();
  	void save (char *filepath);
  	void draw();

}; 

#endif
