#include "../headers/Light.h"
#include <string.h>

using namespace std; 

Light::Light(){
	x = 0.0;
	y = 0.0;
	z = 0.0;
}

Light::Light(float x, float y, float z, std::string type){
	this->x = x;
	this->y = y;
	this->z = z;
	this->type = type;
};
