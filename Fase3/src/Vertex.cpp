#include "../headers/Vertex.h"

Vertex::Vertex (float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Vertex::Vertex(std::string str){
    size_t pos;

    x = std::stof(str,&pos);
    str.erase(0,pos+1);
    y = std::stof(str,&pos);
    str.erase(0,pos+1);
    z = std::stof(str,&pos);
}

float Vertex::getx () const {
	return this->x;
}

float Vertex::gety () const {
	return this->y;
	
}

float Vertex::getz () const {
	return this->z;
}