#ifndef _FIGURE_H_
#define _FIGURE_H_

#include "Vertex.h"
#include <vector>

class Figure { 
  private: 
  	std::vector<Vertex> vertexes;
  public:
    std::vector<Vertex> getvertexes ();
  	Vertex getvertex (int i);
  	void pushvertex (Vertex *v);
  	int getsize();
  	void save (char *filepath);
  	void draw();
	void box(float comp, float largure, float height, int stack);
	void cone(float radius, float height, int slices, int stack);
	void plane(float size, float height);
	void sphere(float radius, int slices, int stack);

}; 

#endif
