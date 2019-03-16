#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <math.h>
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

void Figure::sphere(float radius, int slices, int stack) {

	float alpha, beta, beta1;

	for(int j = 0; j < stack; j++){
		for(int i=0; i < slices; i++){
			alpha = i * ((2*M_PI) / slices);
			beta = j * ((M_PI)/stack) - M_PI / 2;
			beta1 = beta + ((M_PI)/stack);

		pushvertex(new Vertex(radius*cos(beta) * cos(alpha), radius*sin(beta), radius*cos(beta)*sin(alpha)));
		pushvertex(new Vertex(radius*cos(beta + ((M_PI)/stack)) * cos(alpha), sin(beta + ((M_PI)/stack))*radius, radius*cos(beta + ((M_PI)/stack))*sin(alpha)));
		pushvertex(new Vertex(radius*cos(beta)*cos(alpha + ((2*M_PI) / slices)),radius*sin(beta),radius*cos(beta)*sin(alpha + ((2*M_PI) / slices))));
		
		pushvertex(new Vertex(radius*cos(beta + ((M_PI)/stack)) * cos(alpha), sin(beta + ((M_PI)/stack))*radius, radius*cos(beta + ((M_PI)/stack))*sin(alpha)));
		pushvertex(new Vertex(radius*cos(beta + ((M_PI)/stack))*cos(alpha + ((2*M_PI) / slices)), radius*sin(beta + ((M_PI)/stack)), radius*cos(beta1)*sin(alpha + ((2*M_PI) / slices))));
		pushvertex(new Vertex(radius*cos(beta)*cos(alpha + ((2*M_PI) / slices)), radius*sin(beta), radius*cos(beta)*sin(alpha + ((2*M_PI) / slices))));
		}
	} 
}
void Figure::plane(float size, float height) {

	pushvertex(new Vertex(size/2.0,height,-size/2.0));
	pushvertex(new Vertex(-size/2.0,height,size/2.0));
	pushvertex(new Vertex(size/2.0,height,size/2.0));

	pushvertex(new Vertex(size/2.0,height,-size/2.0));
	pushvertex(new Vertex(-size/2.0,height,-size/2.0));
	pushvertex(new Vertex(-size/2.0,height,size/2.0));

}

void Figure::cone(float radius, float height, int slices, int stack) {

	float alpha = ((2 * M_PI)/slices); 
	float beta = height/stack; 

	 for(float i = 0; i <(2 * M_PI); i +=alpha){
	 	pushvertex(new Vertex(0.0f, -height/2, 0.0f));
	 	pushvertex(new Vertex(radius*sin(i+alpha), -height/2, radius*cos(i + alpha)));
		pushvertex(new Vertex(radius*sin(i), -height/2, radius*cos(i)));
	 }
	 for (int i = 0; i<stack; i++){
		for (float j = 0; j <slices; j += alpha){

			float slice = (-height/2) + i * beta;
			float slice1 = (-height/2) + (i + 1) * beta;

			float raio = radius - (radius * i) / stack;
			float raio1 = radius - (radius * (i + 1)) / stack;
	 	
	 		pushvertex(new Vertex(raio1 * sin(j), slice1, raio1 * cos(j)));
	 		pushvertex(new Vertex(raio * sin(j), slice, raio * cos(j)));
	 		pushvertex(new Vertex(raio1 * sin(j + alpha), slice1, raio1 * cos(j + alpha)));


	 		pushvertex(new Vertex(raio * sin(j), slice, raio * cos(j)));
	 		pushvertex(new Vertex(raio * sin(j + alpha), slice, raio * cos(j + alpha)));
	 		pushvertex(new Vertex(raio1 * sin(j + alpha), slice1, raio1 * cos(j + alpha)));

		}
	}


}
void Figure::box(float comp, float largure, float height, int stack) {



	double x, y, z, xx, yy, zz; 
	double stackC, stackL, stackA; //espaçamento entre as stacks de comprimento, largura e altura
	int i, j;

	stackC = comp / stack; 
	stackL = largure / stack; 
	stackA = height/ stack; 

	
	// FACES DE CIMA E DE BAIXO
	
	y = height/ 2; //cima
	yy = -y; //baixo 
	z = largure / 2; //z tem metade do valor da largura -> poligono centrado no eixo do z

	for (i = 0; i < stack; i++){
		x = -(comp / 2);  // x tem metade do valor do comprimento -> poligono centrado no eixo do x
		xx = x + stackC;  //xx é ponto auxiliar, incrementa-se para andar sempre à frente do x e fazer o triângulo 
 		zz = z - stackL; 
		for (j = 0; j < stack; j++){

				pushvertex(new Vertex(x, y, z));
				pushvertex(new Vertex(xx, y, z));
				pushvertex(new Vertex(x, y, zz));
				pushvertex(new Vertex(xx, y, z));
				pushvertex(new Vertex(xx, y, zz));
				pushvertex(new Vertex(x, y, zz));
				pushvertex(new Vertex(x, yy, z));
				pushvertex(new Vertex(x, yy, zz));
				pushvertex(new Vertex(xx, yy, z));
				pushvertex(new Vertex(xx, yy, z));
				pushvertex(new Vertex(x, yy, zz));
				pushvertex(new Vertex(xx, yy, zz));

			x = x + stackC;   //incrementar x para a proxima camada
			xx = xx + stackC;//mais uma vez incrementar tb o xx, pela razão que já foi referida
		}
		z = z - stackL;
	}

	//FACES DA ESQUERDA E DA DIREITA
	
	x = -(comp / 2); // esqueRda
	xx = -x; // direita
	y = -(height/ 2); //altura inicial

	for (i = 0; i < stack; i++){
		z = largure / 2;    //z tem metade do valor da largura -> poligono centrado no eixo do z
		zz = z - stackL;
		yy = y + stackA;

		for (j = 0; j < stack; j++){

				pushvertex(new Vertex(x, y, z));
				pushvertex(new Vertex(x, yy, z));
				pushvertex(new Vertex(x, yy, zz));

				pushvertex(new Vertex(x, y, zz));
				pushvertex(new Vertex(xx, yy, z));
				pushvertex(new Vertex(x, yy, zz));

				pushvertex(new Vertex(xx, y, z));
				pushvertex(new Vertex(xx, y, zz));
				pushvertex(new Vertex(xx, yy, zz));

				pushvertex(new Vertex(xx, y, z));
				pushvertex(new Vertex(xx, yy, zz));
				pushvertex(new Vertex(xx, yy, z));

				glVertex3f(xx, y, z);
				glVertex3f(xx, yy, zz);
				glVertex3f(xx, yy, z);

			z = z - stackL; 
			zz = zz - stackL; 		
		}
		y = y + stackA; //temos que incrementar na altura o valor do espaçamento para as stacks ficarem direitas	
	}

	//FACES DA FRENTE E DE TRÁS

	z = largure / 2; //frente
	zz = -z; //trás
	y = -(height/ 2); //altura inicial

	for (i = 0; i < stack; i++){
		x = -(comp / 2);  //valor do x onde se começam a desenhar os triângulos
		xx = x + stackC;   //valor do x na proxima camada de comprimento
		yy = y + stackA; //valor do y na proxima camada de altura

		for (j = 0; j < stack; j++){

				pushvertex(new Vertex(x, y, z));
				pushvertex(new Vertex(xx, y, z));
				pushvertex(new Vertex(x, yy, z));

				pushvertex(new Vertex(xx, y, z));
				pushvertex(new Vertex(xx, yy, z));
				pushvertex(new Vertex(x, yy, z));

				pushvertex(new Vertex(x, y, zz));
				pushvertex(new Vertex(x, yy, zz));
				pushvertex(new Vertex(xx, y, zz));

				pushvertex(new Vertex(xx, y, zz));
				pushvertex(new Vertex(x, yy, zz));
				pushvertex(new Vertex(xx, yy, zz));

			x = x + stackC;  
			xx = xx + stackC; 	
		}
		y = y + stackA;	
	}
}