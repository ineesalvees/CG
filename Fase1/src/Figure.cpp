#include "../headers/Figure.h"
#include "../headers/Vertex.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

Vertex Figure::getvertex (int i) {
	return this->vertexes.at(i);
}

void Figure::pushvertex (Vertex *v) {
	this->vertexes.push_back(*v);
}

void Figure::add (float x, float y, float z) {
	Vertex *v = new Vertex (x,y,z);
	this->vertexes.push_back(*v);
}

int Figure::getsize() {
	this->vertexes.size();
}

void Figure::draw() {
	int index;
	glBegin(GL_TRIANGLES);

	 for (index = 0; index < this->getsize(); index ++) {
	 		Vertex v = this->getvertex(index);
			glVertex3f(v.getx(), v.gety(), v.getz());
	 }
	 glEnd();
}

void Figure::save (char *filename) {
	char src[] = "";
	strcat(src,filename);
	
	ofstream file(src);
	
	for(vector<Vertex>::const_iterator i = vertexes.begin(); i != vertexes.end(); ++i) {
    	file<< i->getx() << " " << i->gety() << " " << i->getz() << " ";
	}
}