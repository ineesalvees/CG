#include "Cone.h"

void Cone::draw () {
    float act_angle = 0;

	float angle;

	for(int i=0; i < slices; i++){
		angle = i * ((2*M_PI) / slices);

		glBegin(GL_TRIANGLES);


			if (i % 2 == 0) glColor3f(0.847, 0.133, 0.372);
			else glColor3f(1, 0, 1);

			glVertex3f(0.0f,height / 2 ,0.0f);
			glVertex3f(radius*cos(angle + ((2*M_PI) / slices)),-height / 2 ,radius*sin(angle + ((2*M_PI) / slices)));
			glVertex3f(radius*cos(angle),-height / 2 ,radius*sin(angle));


			glColor3f(0.576, 0.847, 0.133);
			glVertex3f(0.0f,-height / 2 ,0.0f);
			glVertex3f(radius*cos(angle),-height / 2 ,radius*sin(angle));
			glVertex3f(radius*cos(angle + ((2*M_PI) / slices)),-height / 2 ,radius*sin(angle + ((2*M_PI) / slices)));
		glEnd();

	}
}

Cone::Cone (float radius, float height, int slices) {
	this->radius = radius;
	this->height = height;
	this->slices = slices;
}
