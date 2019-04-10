#ifndef _VBO_H_
#define _VBO_H_

#include <vector>
#include "Vertex.h"
//#include </usr/local/Cellar/glew/2.1.0/include/GL/glew.h>
//#include <GL/glut.h>

class VBO {
	private: 
  		std::vector<Vertex> vertexes;
		float buff[1];
		GLuint buffers[1];

	public:
		VBO(std::vector<Vertex> vertexes);
		void render ();
};

#endif