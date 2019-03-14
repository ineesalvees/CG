#include "../headers/Box.h"
#include "../headers/Figure.h"
#include "../headers/Vertex.h"
#include <iostream>
#include <fstream>
using namespace std;

void Box::draw () {
	int index = 0;

	 glBegin(GL_TRIANGLES);

	 for (index = 0; index < figure->getsize(); index ++) {
	 		Vertex v = this->figure->getvertex(index);
			glVertex3f(v.getx(), v.gety(), v.getz());
	 }
	 glEnd();
}

Box::Box (float comp, float largure, float height, int stack) {
	this->comp = comp;
	this->largure = largure;
	this->height = height;
	this->stack = stack;
	this->figure = new Figure();


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

				this->figure->pushvertex(new Vertex(x, y, z));
				this->figure->pushvertex(new Vertex(xx, y, z));
				this->figure->pushvertex(new Vertex(x, y, zz));

				this->figure->pushvertex(new Vertex(xx, y, z));
				this->figure->pushvertex(new Vertex(xx, y, zz));
				this->figure->pushvertex(new Vertex(x, y, zz));

				this->figure->pushvertex(new Vertex(x, yy, z));
				this->figure->pushvertex(new Vertex(x, yy, zz));
				this->figure->pushvertex(new Vertex(xx, yy, z));

				this->figure->pushvertex(new Vertex(xx, yy, z));
				this->figure->pushvertex(new Vertex(x, yy, zz));
				this->figure->pushvertex(new Vertex(xx, yy, zz));

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

				this->figure->pushvertex(new Vertex(x, y, z));
				this->figure->pushvertex(new Vertex(x, yy, z));
				this->figure->pushvertex(new Vertex(x, yy, zz));

				this->figure->pushvertex(new Vertex(x, y, zz));
				this->figure->pushvertex(new Vertex(xx, yy, z));
				this->figure->pushvertex(new Vertex(x, yy, zz));

				this->figure->pushvertex(new Vertex(xx, y, z));
				this->figure->pushvertex(new Vertex(xx, y, zz));
				this->figure->pushvertex(new Vertex(xx, yy, zz));

				this->figure->pushvertex(new Vertex(xx, y, z));
				this->figure->pushvertex(new Vertex(xx, yy, zz));
				this->figure->pushvertex(new Vertex(xx, yy, z));

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

				this->figure->pushvertex(new Vertex(x, y, z));
				this->figure->pushvertex(new Vertex(xx, y, z));
				this->figure->pushvertex(new Vertex(x, yy, z));

				this->figure->pushvertex(new Vertex(xx, y, z));
				this->figure->pushvertex(new Vertex(xx, yy, z));
				this->figure->pushvertex(new Vertex(x, yy, z));

				this->figure->pushvertex(new Vertex(x, y, zz));
				this->figure->pushvertex(new Vertex(x, yy, zz));
				this->figure->pushvertex(new Vertex(xx, y, zz));

				this->figure->pushvertex(new Vertex(xx, y, zz));
				this->figure->pushvertex(new Vertex(x, yy, zz));
				this->figure->pushvertex(new Vertex(xx, yy, zz));

			x = x + stackC;  
			xx = xx + stackC; 	
		}
		y = y + stackA;	
	}
}

void Box::save (char *path) {
	
}
