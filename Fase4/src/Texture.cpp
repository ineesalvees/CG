#include "../headers/Texture.h"
#include <string.h>


Texture::Texture(){
}

Texture::Texture(float r, float g, float b, std::string texture){
	this->r = r;
	this->g = g;
	this->b = b;
	this->texture = texture;
};
