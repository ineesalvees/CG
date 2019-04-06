#include "../headers/Rotation.h"

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

