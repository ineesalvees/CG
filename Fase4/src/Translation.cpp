#include "../headers/Translation.h"
#include <math.h>
#include "../headers/Vertex.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


Translation::Translation(){
	time = 0.0;
}

Vertex Translation::getvertex (int i) {
	return this->vertexes.at(i);
}

void Translation::pushvertex (Vertex *v) {
	this->vertexes.push_back(*v);
}

int Translation::getsize() {
	return this->vertexes.size();
}

void Translation::multMatrixVector(float *m, float *v, float *res) {

	for (int j = 0; j < 4; ++j) {
		res[j] = 0;
		for (int k = 0; k < 4; ++k) {
			res[j] += v[k] * m[j * 4 + k];
		}
	}

}

void Translation::getCatmullRomPoint(float t, float *p0, float *p1, float *p2, float *p3, float *pos, float *deriv) {

	// catmull-rom matrix
	float m[4][4] = {	{-0.5f,  1.5f, -1.5f,  0.5f},
						{ 1.0f, -2.5f,  2.0f, -0.5f},
						{-0.5f,  0.0f,  0.5f,  0.0f},
						{ 0.0f,  1.0f,  0.0f,  0.0f}};
	
	//vector que vamos usar para guardar os pontos
	float p[4];

	//vector do eixo dos X
	float AxisX[4];

	//vector do eixo dos Y
	float AxisY[4];

	//vector do eixo dos Z
	float AxisZ[4];

	// Compute A = M * P
	// componente x
	p[0] = p0[0];
	p[1] = p1[0];
	p[2] = p2[0];
	p[3] = p3[0];

	//fazer multiplicação da matriz pelo vector e guardar no vector do eixo dos X
	multMatrixVector((float *)m, p, AxisX);

	// componente y
	p[0] = p0[1];
	p[1] = p1[1];
	p[2] = p2[1];
	p[3] = p3[1];

	//fazer multiplicação da matriz pelo vector e guardar no vector do eixo dos Y
	multMatrixVector((float *)m, p, AxisY);

	//componente z
	p[0] = p0[2];
	p[1] = p1[2];
	p[2] = p2[2];
	p[3] = p3[2];

	//fazer multiplicação da matriz pelo vector e guardar no vector do eixo dos Z
	multMatrixVector((float *)m, p, AxisZ);
	
	// Compute pos = T * A
	float t_vector[4] = {pow(t, 3), pow(t, 2), t, 1};
	pos[0] = t_vector[0]*AxisX[0] + t_vector[1]*AxisX[1] + t_vector[2]*AxisX[2] + t_vector[3]*AxisX[3];
	pos[1] = t_vector[0]*AxisY[0] + t_vector[1]*AxisY[1] + t_vector[2]*AxisY[2] + t_vector[3]*AxisY[3];
	pos[2] = t_vector[0]*AxisZ[0] + t_vector[1]*AxisZ[1] + t_vector[2]*AxisZ[2] + t_vector[3]*AxisZ[3];

	// compute deriv = T' * A
	float deriv_t_vector[4] = {3*pow(t, 2), 2*t, 1, 0};
	deriv[0] = deriv_t_vector[0]*AxisX[0] + deriv_t_vector[1]*AxisX[1] + deriv_t_vector[2]*AxisX[2] + deriv_t_vector[3]*AxisX[3];
	deriv[1] = deriv_t_vector[0]*AxisY[0] + deriv_t_vector[1]*AxisY[1] + deriv_t_vector[2]*AxisY[2] + deriv_t_vector[3]*AxisY[3];
	deriv[2] = deriv_t_vector[0]*AxisZ[0] + deriv_t_vector[1]*AxisZ[1] + deriv_t_vector[2]*AxisZ[2] + deriv_t_vector[3]*AxisZ[3];
}


// given  global t, returns the point in the curve
void Translation::getGlobalCatmullRomPoint(float gt, float *pos, float *deriv) {

	float t = gt * POINT_COUNT; // this is the real global t
	int index = floor(t);  // which segment
	t = t - index; // where within  the segment

	// indices store the points
	int indices[4]; 
	indices[0] = (index + POINT_COUNT-1)%POINT_COUNT;	
	indices[1] = (indices[0]+1)%POINT_COUNT;
	indices[2] = (indices[1]+1)%POINT_COUNT; 
	indices[3] = (indices[2]+1)%POINT_COUNT;

	getCatmullRomPoint(t, p[indices[0]], p[indices[1]], p[indices[2]], p[indices[3]], pos, deriv);
}


void Translation::renderCatmullRomCurve() {

// draw curve using line segments with GL_LINE_LOOP

	float pos[3];
	float deriv[3];

	glBegin(GL_LINE_LOOP);
	for(float i = 0; i<1; i+=0.01){
		getGlobalCatmullRomPoint(i, pos, deriv);
		//printf("%f\n", i);
		glVertex3f(pos[0], pos[1], pos[2]);
	}
	glEnd();

}
