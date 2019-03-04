#include "Cone.h"

void Sphere::draw () {
	//float d_angle = 2*M_PI / slices;
	//float act_angle = 0;
	float alpha, beta, beta1;

	
	//beta1 = beta + ((M_PI)/stack);

	for(int j = 0; j < stack; j++){
		for(int i=0; i < slices; i++){
			alpha = i * ((2*M_PI) / slices);
			beta = j * ((M_PI)/stack) - M_PI / 2;
			beta1 = beta + ((M_PI)/stack);

		glBegin(GL_TRIANGLES);

		//lateral 1
		glColor3f(1, 0, 0);
		glVertex3f(radius*cos(beta) * cos(alpha), radius*sin(beta), radius*cos(beta)*sin(alpha));
		glVertex3f(radius*cos(beta + ((M_PI)/stack)) * cos(alpha), sin(beta + ((M_PI)/stack))*radius, radius*cos(beta + ((M_PI)/stack))*sin(alpha));
		glVertex3f(radius*cos(beta)*cos(alpha + ((2*M_PI) / slices)),radius*sin(beta),radius*cos(beta)*sin(alpha + ((2*M_PI) / slices)));

		//lateral 2
		
		glColor3f(1, 0, 0);
		glVertex3f(radius*cos(beta + ((M_PI)/stack)) * cos(alpha), sin(beta + ((M_PI)/stack))*radius, radius*cos(beta + ((M_PI)/stack))*sin(alpha));
		glVertex3f(radius*cos(beta + ((M_PI)/stack))*cos(alpha + ((2*M_PI) / slices)), radius*sin(beta + ((M_PI)/stack)), radius*cos(beta1)*sin(alpha + ((2*M_PI) / slices)));
		glVertex3f(radius*cos(beta)*cos(alpha + ((2*M_PI) / slices)), radius*sin(beta), radius*cos(beta)*sin(alpha + ((2*M_PI) / slices)));

		glEnd();
	}
	} 
}

Cone::Cone (float radius, float height, int slices) {
	this->radius = radius;
	this->height = height;
	this->slices = slices;
}