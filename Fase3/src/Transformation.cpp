#include "Transformation.h"

Transformation::Transformation(float x, float y, float z){
	this->x = x;
	this->y = y;
	this->z = z;
}

float Transformation::getx () {
	return this->x;
}

float Transformation::gety () {
	return this->y;
}

float Transformation::getz () {
	return this->z;
}
