#include "../headers/Group.h"
#include "../headers/VBO.h"
#include "../headers/Transformation.h"
#include "../headers/Light.h"
#include <vector>
#include "../headers/Texture.h"


Group::Group() {
	
}
std::vector<VBO> Group::getVBOs () {
	return this->vbos;
}

std::vector<Transformation*> Group::getTransformations () {
	return transformations;
}

std::vector<Group> Group::getChildren () {
	return this->children;
}

void Group::pushVBO (VBO *vbo) {
	this->vbos.push_back(*vbo);
}

void Group::pushTransformation (Transformation *transformation) {
	this->transformations.push_back(transformation);
}

void Group::pushGroup (Group *group) {
	this->children.push_back(*group);
}

void Group::pushLight(Light *light) {
	this->lights.push_back(light);
}
std::vector<Light*> Group::getLights () {
	return lights;
}

