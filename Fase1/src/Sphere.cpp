#include "../headers/Sphere.h"
#include "../headers/Vertex.h"
#include "../headers/Figure.h"
#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

void Sphere::draw () {

	int index = 0;

	 glBegin(GL_TRIANGLES);

	 for (index = 0; index < figure->getsize(); index ++) {
	 		Vertex v = this->figure->getvertex(index);
			glVertex3f(v.getx(), v.gety(), v.getz());
	 }
	 glEnd();
}

Sphere::Sphere (float radius, int slices, int stack) {
	this->radius = radius;
	this->stack = stack;
	this->slices = slices;
	this->figure = new Figure();
	float alpha, beta, beta1;

	for(int j = 0; j < stack; j++){
		for(int i=0; i < slices; i++){
			alpha = i * ((2*M_PI) / slices);
			beta = j * ((M_PI)/stack) - M_PI / 2;
			beta1 = beta + ((M_PI)/stack);

		//lateral 1
		this->figure->pushvertex(new Vertex(radius*cos(beta) * cos(alpha), radius*sin(beta), radius*cos(beta)*sin(alpha)));
		this->figure->pushvertex(new Vertex(radius*cos(beta + ((M_PI)/stack)) * cos(alpha), sin(beta + ((M_PI)/stack))*radius, radius*cos(beta + ((M_PI)/stack))*sin(alpha)));
		this->figure->pushvertex(new Vertex(radius*cos(beta)*cos(alpha + ((2*M_PI) / slices)),radius*sin(beta),radius*cos(beta)*sin(alpha + ((2*M_PI) / slices))));
		
		//lateral 2
		this->figure->pushvertex(new Vertex(radius*cos(beta + ((M_PI)/stack)) * cos(alpha), sin(beta + ((M_PI)/stack))*radius, radius*cos(beta + ((M_PI)/stack))*sin(alpha)));
		this->figure->pushvertex(new Vertex(radius*cos(beta + ((M_PI)/stack))*cos(alpha + ((2*M_PI) / slices)), radius*sin(beta + ((M_PI)/stack)), radius*cos(beta1)*sin(alpha + ((2*M_PI) / slices))));
		this->figure->pushvertex(new Vertex(radius*cos(beta)*cos(alpha + ((2*M_PI) / slices)), radius*sin(beta), radius*cos(beta)*sin(alpha + ((2*M_PI) / slices))));
		}
	} 


}

void Sphere::save (char *path) {
	ofstream file (path);
		file << "S " << this->radius << " " << this->stack << " " << this->slices;
	file.close();
}