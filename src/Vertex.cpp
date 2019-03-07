#include "../headers/Vertex.h"

Vertex::Vertex (float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

float Vertex::getx () {
	return this->x;
}

float Vertex::gety () {
	return this->y;
	
}

float Vertex::getz () {
	return this->z;
}