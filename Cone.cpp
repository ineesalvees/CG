#include "Cone.h"
#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;


void Cone::draw () {
     float alpha = ((2 * M_PI)/slices); 
	 float beta = height/stack; 

	 for(float i = 0; i <(2 * M_PI); i +=alpha){

		 glBegin(GL_TRIANGLES);
		 	glColor3f(1, 0, 0);
			glVertex3f(0.0f, -height/2, 0.0f);
			glVertex3f(radius*sin(i+alpha), -height/2, radius*cos(i + alpha));
			glVertex3f(radius*sin(i), -height/2, radius*cos(i));
		 glEnd();
	 }
	
	 for (int i = 0; i<stack; i++){
		for (float j = 0; j <slices; j += alpha){

			float slice = (-height/2) + i * beta;
			float slice1 = (-height/2) + (i + 1) * beta;

			float raio = radius - (radius * i) / stack;
			float raio1 = radius - (radius * (i + 1)) / stack;

			glBegin(GL_TRIANGLES);
		 		glColor3f(1, 0, 0);
				glVertex3f(raio1 * sin(j), slice1, raio1 * cos(j));
		 		glVertex3f(raio * sin(j), slice, raio * cos(j));
				glVertex3f(raio1 * sin(j + alpha), slice1, raio1 * cos(j + alpha));

				glColor3f(0, 0, 0);
				glVertex3f(raio * sin(j), slice, raio * cos(j));
				glVertex3f(raio * sin(j + alpha), slice, raio * cos(j + alpha));
				glVertex3f(raio1 * sin(j + alpha), slice1, raio1 * cos(j + alpha));

		 	glEnd();
		}
	}
}

Cone::Cone (float radius, float height, int slices, int stack) {
	this->radius = radius;
	this->height = height;
	this->slices = slices;
	this->stack = stack;
}

void Cone::save (char *path) {
	ofstream file (path);
		file << "C " << this->radius << " " << this->height << " " << this->slices << " " << this->stack;
	file.close();

}
/*
// writing on a text file

int main () {
  ofstream myfile ("example.txt");
  if (myfile.is_open())
  {
    myfile << "This is a line.\n";
    myfile << "This is another line.\n";
    myfile.close();
  }
  else cout << "Unable to open file";
  return 0;
}
*/