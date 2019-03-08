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
  	int getsize();
  	void save (char *filepath);

}; 

#endif
