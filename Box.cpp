#include "Box.h"
#include <iostream>
#include <fstream>
using namespace std;

void Box::draw () {
	float x = xx/2.0;
	float z = zz / 2.0;

	glBegin(GL_TRIANGLES);
		glColor3f(1, 0, 0);
		glVertex3f(-x,y,z); //E
		glVertex3f(-x,0.0f,z); //A
		glVertex3f(x,0.0f,z); //B
	glEnd();
	
	glBegin(GL_TRIANGLES);
		glColor3f(1, 0, 0);
		glVertex3f(-x,y,z); //E
		glVertex3f(x,0.0f,z); //B
		glVertex3f(x,y,z); //G
	glEnd();

	glBegin(GL_TRIANGLES);
		glColor3f(1, 1, 0);
		glVertex3f(x,y,-z); //H
		glVertex3f(-x,y,-z); //F
		glVertex3f(x,0.0f,-z); //C
	glEnd();

	glBegin(GL_TRIANGLES);
		glColor3f(1, 1, 0);
		glVertex3f(-x,y,-z); //F
		glVertex3f(-x,0.0f,-z); //D
		glVertex3f(x,0.0f,-z); //C
	glEnd();


	glBegin(GL_TRIANGLES);
		glColor3f(1, 0, 1);
		glVertex3f(-x,y,z); //E
		glVertex3f(-x,y,-z); //F
		glVertex3f(-x,0.0f,z); //A
	glEnd();

	glBegin(GL_TRIANGLES);
		glColor3f(1, 0, 1);
		glVertex3f(-x,0.0f,z); //A
		glVertex3f(-x,0.0f,-z); //D
		glVertex3f(x,0.0f,z); //B
	glEnd();

	glBegin(GL_TRIANGLES);
		glColor3f(1, 0, 1);
		glVertex3f(-x,0.0f,z); //A
		glVertex3f(-x,y,-z); //F
		glVertex3f(-x,0.0f,-z); //D
	glEnd();

	glBegin(GL_TRIANGLES);
		glColor3f(1, 0, 1);
		glVertex3f(-x,0.0f,-z); //D
		glVertex3f(x,0.0f,-z); //C
		glVertex3f(x,0.0f,z); //B
	glEnd();

	glBegin(GL_TRIANGLES);
		glColor3f(1, 0, 1);
		glVertex3f(-x,y,-z); //F
		glVertex3f(-x,y,z); //E
		glVertex3f(x,y,z); //G
	glEnd();

	glBegin(GL_TRIANGLES);
		glColor3f(1, 0, 1);
		glVertex3f(x,y,-z); //H
		glVertex3f(-x,y,-z); //F
		glVertex3f(x,y,z); //G
	glEnd();

	glBegin(GL_TRIANGLES);
		glColor3f(1, 0, 1);
		glVertex3f(x,y,z); //G
		glVertex3f(x,0.0f,z); //B
		glVertex3f(x,0.0f,-z); //C
	glEnd();

	glBegin(GL_TRIANGLES);
		glColor3f(1, 0, 1);
		glVertex3f(x,y,-z); //H
		glVertex3f(x,y,z); //G
		glVertex3f(x,0.0f,-z); //C
	glEnd();

	glBegin(GL_TRIANGLES);
		glColor3f(1, 0, 1);
		glVertex3f(-x,0.0f,-z); //D
		glVertex3f(-x,0.0f,z); //A
		glVertex3f(x,0.0f,-z); //C
	glEnd();

	glBegin(GL_LINES);
		glColor3f(1, 1, 1);
    	glVertex3f(0, 0, 0);
    	glVertex3f(4, 0, 0);
	glEnd();

	glBegin(GL_LINES);
		glColor3f(1, 1, 1);
    	glVertex3f(0, 0, 0);
    	glVertex3f(0, 0, 4);
	glEnd();

	glBegin(GL_LINES);
		glColor3f(1, 1, 1);
    	glVertex3f(0, 0, 0);
    	glVertex3f(0, 4, 0);
	glEnd();
}

Box::Box (float xx, float y, float zz, int slices) {
	this->xx = xx;
	this->y = y;
	this->zz = zz;
	this->slices = slices;
}

void Box::save (char *path) {
	ofstream file (path);
		file << "B " << this->xx << " " << this->y << " " << this->zz << " " << this->slices;
	file.close();
}
