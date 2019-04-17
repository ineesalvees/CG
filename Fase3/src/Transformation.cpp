#include "../headers/Transformation.h"

Transformation::Transformation(){
	this->x = 0;
	this->y = 0;
	this->z = 0;
}


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

// rotate
Rotation::Rotation(){
	time = 0.0;
	axisX = 0.0;
	axisY = 0.0;
	axisZ = 0.0;
}

Rotation::Rotation(float time, float axisX, float axisY, float axisZ){
	this->time = time;
	this->axisX = axisX;
	this->axisY = axisY;
	this->axisZ = axisZ;
}


