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
	double stackC, stackL, stackA; //espaçamento entre as stack de comprimento, largura e altura
	int i, j;

	stackC = comp / stack; 
	stackL = largure / stack; 
	stackA = height/ stack; 

	
	// FACES DE CIMA E DE BAIXO
	
	y = height/ 2; 
	yy = -y; //y é usado para indicar a altura da face de cima e yy é a altura a que a base de baixo vai estar
	z = largure / 2; //z assume metade do valor da largura, ficando o poligono centrado no eixo do z

	for (i = 0; i < stack; i++){
		x = -(comp / 2);  // x assume metade do valor do comprimento, ficando o poligono centrado no eixo do x
		xx = x + stackC;  //incrementa também o xx, para andar sempre à frente do x, para fazer o triângulo
 		zz = z - stackL;  //decrementa o z, pois temos o z com o seu valor maximo positivo e para o plano ficar centrado temos que ir tirando o espaçamento entre as stack de largur e altura
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

			x = x + stackC;   //incrementa o x, sendo o x assumindo o valor na proxima camada
			xx = xx + stackC;//incrementa também o xx, para andar sempre à frente do x, para fazer o triângulo
		}
		z = z - stackL;// z vai decrementando sempre o valor do espaçamento lateral, para ficar com as stack certas na largureura
	}

	
	x = -(comp / 2); // face da esqueda
	xx = -x; // face da direita
	y = -(height/ 2); //a altura onde se iniciam as faces laterais

	for (i = 0; i < stack; i++){
		z = largure / 2;    //z assume metade do valor da largura, ficando o poligono centrado no eixo do z
		zz = z - stackL;  //decrementa z, pois temos o z com o seu valor maximo positivo e para o plano ficar centrado temos que ir tirando o espaçamento entre as stack de largureura
		yy = y + stackA; //para o poligono ficar centrado, começamos com y negativo, sendo o seu valor metade da altura

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

			z = z - stackL;   // z vai decrementando sempre o valor do espaçamento lateral, para ficar com as stack certas na largureura
			zz = zz - stackL;//decrementa o z, pois temos o z com o seu valor maximo positivo e para o plano ficar centrado temos que ir tirando o espaçamento entre as stack de largureura
		}
		y = y + stackA; //incrementar na altura o valor do espaçamento, para obter nessa altura as stack indicadas	
	}

	

	z = largure / 2; //Face da frente
	zz = -z; // Face trás
	y = -(height/ 2); //altura que se inicia as stack frente e trás

	for (i = 0; i < stack; i++){
		x = -(comp / 2);  //valor da coordenada x, onde se começam a desenhar os triângulos
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

			x = x + stackC;    //x vai incrementando o valor do espaçamento do comprimento, para ficar com as stack indicadas
			xx = xx + stackC; //xx também incrementa o valor do espaçamento do comprimento, para ficar sempre na proxima camada no eixo do x	
		}
		y = y + stackA; //incrementar na altura o valor do espaçamento, para obter nessa altura as stack indicadas	
	}
}

void Box::save (char *path) {
	
}
