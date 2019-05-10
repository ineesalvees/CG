#include "../headers/Texture.h"
#include <string.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <IL/il.h>


Texture::Texture(){
}

Texture::Texture(float r, float g, float b, std::string texture){
	this->r = r;
	this->g = g;
	this->b = b;
	this->texture = texture;
};


