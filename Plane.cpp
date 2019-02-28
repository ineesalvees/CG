#include "Plane.h"
#define _USE_MATH_DEFINES
#include <math.h>

void Plane::draw () {
    glBegin(GL_TRIANGLES);
		glVertex3f(size/2.0,height,-size/2.0);
		glVertex3f(-size/2.0,height,size/2.0);
		glVertex3f(size/2.0,height,size/2.0);
	glEnd();
		
	glBegin(GL_TRIANGLES);
		glVertex3f(size/2.0,height,-size/2.0);
		glVertex3f(-size/2.0,height,-size/2.0);
		glVertex3f(-size/2.0,height,size/2.0);
	glEnd();
}

Plane::Plane (float size, float height) {
	this->size = size;
	this->height = height;
}
