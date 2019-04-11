#include "Transformation.h"

Transformation::Transformation(){
	translation = Translation::Translation();
	rotation = Rotation::Rotation();
	scale = Scale::Scale();
	color = Color::Color();
}

Transformation::Transformation(Translation translation, Rotation rotation, Scale scale, Color color){
	this->translation = translation;
	this->rotation = rotation;
	this->scale = scale;
	this->color = color;
}

int main(){}