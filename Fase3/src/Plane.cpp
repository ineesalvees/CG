#include "../headers/Plane.h"
#include "../headers/Vertex.h"
#include "../headers/Figure.h"
#include "Figure.cpp"
#include "Vertex.cpp"
#include <iostream>
#include <fstream>
using namespace std;

void Plane::draw () {

	int i ;

	glBegin(GL_TRIANGLES);

	for ( i = 0; i < figure->getsize() ; i++) {
		Vertex v = this->figure->getvertex(i);

		glVertex3f(v.getx(), v.gety(),v.getz());

	}
	glEnd();
}


Plane::Plane(float size, float height) {
	this->size = size;
	this->height = height;

	this->figure = new Figure();

	this->figure->pushvertex(new Vertex(size/2.0,height,-size/2.0));
	this->figure->pushvertex(new Vertex(-size/2.0,height,size/2.0));
	this->figure->pushvertex(new Vertex(size/2.0,height,size/2.0));

	this->figure->pushvertex(new Vertex(size/2.0,height,-size/2.0));
	this->figure->pushvertex(new Vertex(-size/2.0,height,-size/2.0));
	this->figure->pushvertex(new Vertex(-size/2.0,height,size/2.0));

}

void Plane::save (char *path) {
	ofstream file (path);
		file << "P " << this->size << " " << this->height;
	file.close();

}

