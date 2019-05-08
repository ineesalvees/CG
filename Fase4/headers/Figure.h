#ifndef _FIGURE_H_
#define _FIGURE_H_

#include "Vertex.h"
#include <vector>

class Figure { 
  private: 
  	std::vector<Vertex> vertexes;
    std::vector<Vertex> norm;
    std::vector<Vertex> tex;
  public:
    std::vector<Vertex> getvertexes ();
    std::vector<Vertex> getnorm ();
    std::vector<Vertex> gettex ();
  	Vertex getvertex (int i);
  	void pushvertex (Vertex *v);
    void pushNorm(Vertex *v);
    void pushTex(Vertex *v);
  	int getsize();
    void getvertexat(int i, Vertex** v);
  	void save (char *filepath);
  	void draw();
	  void box(float comp, float largure, float height, int stack);
	  void cone(float radius, float height, int slices, int stack);
	  void plane(float size, float height);
	  void sphere(float radius, int slices, int stack);

}; 

#endif
