#ifndef _VBO_H_
#define _VBO_H_

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <vector>
#include "Vertex.h"
#include "Texture.h"

class VBO {
	private: 
  		std::vector<Vertex> vertexes;
  		std::vector<Vertex> norm;
  		std::vector<Vertex> tex;
		float buff[1];
		GLuint buffers[1];
		Texture *texture;

	public:
		VBO(std::vector<Vertex> vertexes,std::vector<Vertex> norm,std::vector<Vertex> tex);
		void render ();
		Texture* getTexture() {
			return texture;		
		}
		void setTexture(Texture *tex) {
			texture = tex;		
		}
};

#endif
