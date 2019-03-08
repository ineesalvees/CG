#include "../headers/Figure.h"
#include "../headers/Vertex.h"
#include <vector>

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