#include "Plane.h"

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
