#include "../headers/Rotation.h"

Rotation::Rotation(){
	angle = 0.0;
	axisX = 0.0;
	axisY = 0.0;
	axisZ = 0.0;
}

Rotation::Rotation(float angle, float axisX, float axisY, float axisZ){
	this->angle = angle;
	this->axisX = axisX;
	this->axisY = axisY;
	this->axisZ = axisZ;
}

