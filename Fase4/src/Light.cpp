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


void Light::renderLight() {
	float pos[4] = {x,y,z,1.0f};
	GLfloat amb[4] = {0.2, 0.2, 0.2, 1.0};
    GLfloat diff[4] = {1.0, 1.0, 1.0, 0};
    GLfloat spec[4] = {1.0, 1.0, 1.0, 1.0};

    glLightfv(GL_LIGHT0, GL_SPECULAR, spec);
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
}