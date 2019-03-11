#include "../headers/Vertex.h"

Vertex::Vertex (float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
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