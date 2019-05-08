#include "../headers/Vertex.h"
#include <math.h>

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
Vertex* Vertex::normalCalc() {
    float l, coordX, coordY, coordZ;

    l = sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
    coordX = this->x / l;
    coordY = this->y / l;
    coordZ = this->z / l;

    return new Vertex(coordX, coordY, coordZ);
}