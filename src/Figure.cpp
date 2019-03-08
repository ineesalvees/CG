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

int Figure::getsize() {
	this->vertexes.size();
}

void Figure::save (char *filename) {
	char src[] = "src/";
	strcat(src,filename);
	
	ofstream file(src);
	
	for(vector<Vertex>::const_iterator i = vertexes.begin(); i != vertexes.end(); ++i) {
    	file<< i->getx() << " " << i->gety() << " " << i->getz() << " ";
	}
}