#include "../headers/Translation.h"
#include <math.h>
#include "../headers/Vertex.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string.h>
Translation::Translation(){
	time = 0.0;
}

Vertex Translation::getvertex (int i) {
	return this->vertexes.at(i);
}

void Translation::pushvertex (Vertex *v) {
	this->vertexes.push_back(*v);
}

int Translation::getsize() {
	this->vertexes.size();
}

