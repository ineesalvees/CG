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

std::vector<Vertex> Figure::getvertexes () {
	return this->vertexes;
}

std::vector<Vertex> Figure::getnorm () {
	return this->norm;
}

std::vector<Vertex> Figure::gettex () {
	return this->tex;
}

Vertex Figure::getvertex (int i) {
	return this->vertexes.at(i);
}

void Figure::pushvertex (Vertex *v) {
	this->vertexes.push_back(*v);
}
void Figure::pushNorm(Vertex *v) {
	this->norm.push_back(*v);
}
void Figure::pushTex(Vertex *v) {
	this->tex.push_back(*v);
}
int Figure::getsize() {
	return this->vertexes.size();
}

/*
void Figure::getvertexat(int i, Vertex** v){
    *v = vertexes.at(i);
}
*/
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
    	file << i->getx() << " " << i->gety() << " " << i->getz() << " ";
	}

	char src1[] = "";
	strcat(src1,filename);
	strcat(src1,"n");
	ofstream file1(src1);
	
	for(vector<Vertex>::const_iterator i = norm.begin(); i != norm.end(); ++i) {
    	file1 << i->getx() << " " << i->gety() << " " << i->getz() << " ";
	}

	char src2[] = "";
	strcat(src2,filename);
	strcat(src2,"t");
	ofstream file2(src2);
	
	for(vector<Vertex>::const_iterator i = tex.begin(); i != tex.end(); ++i) {
    	file2 << i->getx() << " " << i->gety() << " " << i->getz() << " ";
	}

}

void Figure::sphere(float radius, int slices, int stack) {

	float alpha, beta, beta1;
	Vertex* normal;
	float texU = 1 / (float)slices;
    float texV = 1 / (float)stack;

	for(int j = 0; j < stack; j++){
		for(int i=0; i < slices; i++){
			alpha = i * ((2*M_PI) / slices);
			beta = j * ((M_PI)/stack) - M_PI / 2;
			beta1 = beta + ((M_PI)/stack);

			Vertex *v1 = new Vertex(radius*cos(beta) * cos(alpha), radius*sin(beta), radius*cos(beta)*sin(alpha));
			normal = v1->normalCalc();
			pushvertex(v1);
			pushNorm(normal);
			pushTex(new Vertex(i*texU,j*texV + texV,0));
			
			Vertex *v2 = new Vertex(radius*cos(beta + ((M_PI)/stack)) * cos(alpha), sin(beta + ((M_PI)/stack))*radius, radius*cos(beta + ((M_PI)/stack))*sin(alpha));
			pushvertex(v2);
			normal = v2->normalCalc();
			pushNorm(normal);
			pushTex(new Vertex(i*texU + texU,j*texV,0));

			Vertex *v3 = new Vertex(radius*cos(beta)*cos(alpha + ((2*M_PI) / slices)),radius*sin(beta),radius*cos(beta)*sin(alpha + ((2*M_PI) / slices)));
			pushvertex(v3);
			normal = v3->normalCalc();
			pushNorm(normal);
			pushTex(new Vertex(i*texU + texU, j*texV + texV, 0));
			
			Vertex *v4 = new Vertex(radius*cos(beta + ((M_PI)/stack)) * cos(alpha), sin(beta + ((M_PI)/stack))*radius, radius*cos(beta + ((M_PI)/stack))*sin(alpha));
			pushvertex(v4);
			normal = v4->normalCalc();
			pushNorm(normal);
			pushTex(new Vertex(i*texU,j*texV + texV,0));
			
			Vertex *v5 = new Vertex(radius*cos(beta + ((M_PI)/stack))*cos(alpha + ((2*M_PI) / slices)), radius*sin(beta + ((M_PI)/stack)), radius*cos(beta1)*sin(alpha + ((2*M_PI) / slices)));
			pushvertex(v5);
			normal = v5->normalCalc();
			pushNorm(normal);
			pushTex(new Vertex(i*texU, j*texV, 0));
			
			Vertex *v6 = new Vertex(radius*cos(beta)*cos(alpha + ((2*M_PI) / slices)), radius*sin(beta), radius*cos(beta)*sin(alpha + ((2*M_PI) / slices)));
			pushvertex(v6);
			normal = v6->normalCalc();
			pushNorm(normal);
			pushTex(new Vertex(i*texU + texU, j*texV + texV, 0));
		
		}
	} 
}
void Figure::plane(float size, float height) {

	float aux = size / 2.0;

	pushvertex(new Vertex(-aux , 0 , -aux));
    pushNorm(new Vertex(0,1,0));
    pushTex(new Vertex(1,1,0));

    pushvertex(new Vertex(-aux , 0 , aux));
    pushNorm(new Vertex(0,1,0));
    pushTex(new Vertex(1,0,0));

    pushvertex(new Vertex(aux , 0 , aux));
    pushNorm(new Vertex(0,1,0));
    pushTex(new Vertex(0,1,0));

    pushvertex(new Vertex(-aux , 0 , -aux));
    pushNorm(new Vertex(0,1,0));
    pushTex(new Vertex(0,1,0));

    pushvertex(new Vertex(aux , 0 , aux));
    pushNorm(new Vertex(0,1,0));
    pushTex(new Vertex(1,0,0));
    
    pushvertex(new Vertex(aux , 0 , -aux));
    pushNorm(new Vertex(0,1,0));
    pushTex(new Vertex(0,0,0));


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
