#include "../headers/Transformation.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdio.h>

#include <cmath>

Transformation::Transformation(){
	this->x = 0;
	this->y = 0;
	this->z = 0;
}


Transformation::Transformation(float x, float y, float z){
	this->x = x;
	this->y = y;
	this->z = z;
}

// rotate
Rotation::Rotation(float time, float x, float y, float z,float angle) : Transformation (x,y,z) {
	this->angle = angle;
	this->time = time;
}

void Rotation::make(){
    float curr_ang = angle;

    if(time > 0){
        float elapsed = glutGet(GLUT_ELAPSED_TIME) % (int) (time * 1000);
        curr_ang = (elapsed *360) / (time * 1000);
    }

    glRotatef(curr_ang,getx(),gety(),getz());
}
Rotation::~Rotation(void){

}
// color
Color::Color(float r, float g, float b) : Transformation (r,g,b) {
}

void Color::make(){
        printf("x:%f y:%f z:%f\n",getx(),gety(),getz());
    glColor3f(getx(),gety(),getz());
}
Color::~Color(void){

}

//scale
Scale::Scale(float x, float y, float z) : Transformation (x,y,z) {
}

void Scale::make(){
        printf("x:%f y:%f z:%f\n",getx(),gety(),getz());
    glScalef(getx(),gety(),getz());
}

Scale::~Scale(void){

}

//translation
Translation::Translation(float x, float y, float z,float t) : Transformation (x,y,z){
    time = t;
}

void catmullCalculate(float t, int* index, float* p, std::vector<Vertex*> points){
    float aux[4];
    float t_2 = t*t;
    float t_3 = t*t*t;

    float m[4][4] = { { -0.5f, 1.5f, -1.5f, 0.5f },
                                  { 1.0f, -2.5f, 2.0f, -0.5f },
                                  { -0.5f, 0.0f, 0.5f, 0.0f },
                                  { 0.0f, 1.0f, 0.0f, 0.0f }};

    p[0] = 0.0;
    p[1] = 0.0;
    p[2] = 0.0;

    aux[0] = t_3*m[0][0] + t_2*m[1][0] + t*m[2][0] + m[3][0];
    aux[1] = t_3*m[0][1] + t_2*m[1][1] + t*m[2][1] + m[3][1];
    aux[2] = t_3*m[0][2] + t_2*m[1][2] + t*m[2][2] + m[3][2];
    aux[3] = t_3*m[0][3] + t_2*m[1][3] + t*m[2][3] + m[3][3];


    int i_0 = index[0];
    int i_1 = index[1];
    int i_2 = index[2];
    int i_3 = index[3];
    Vertex* v0 = points[i_0];
    Vertex* v1 = points[i_1];
    Vertex* v2 = points[i_2];
    Vertex* v3 = points[i_3];

    p[0] = aux[0] * v0->getx() + aux[1] * v1->getx() + aux[2] * v2->getx() + aux[3] * v3->getx();
    p[1] = aux[0] * v0->gety() + aux[1] * v1->gety() + aux[2] * v2->gety() + aux[3] * v3->gety();
    p[2] = aux[0] * v0->getz() + aux[1] * v1->getz() + aux[2] * v2->getz() + aux[3] * v3->getz();
}

void catmullRomPoint(float t, float *p, std::vector<Vertex*> points){
    int size = points.size();

    float rt = t*size;
    int i = floor(rt);
    rt = rt - i;

    int index[4];
    index[0] = (i  + size - 1) % size;
    index[1] = (index[0]  + 1) % size;
    index[2] = (index[1]  + 1) % size;
    index[3] = (index[2]  + 1) % size;

    catmullCalculate(rt,index,p,points);
}

void Translation::generateCurve(){
    float p[3];

    if(catmull_points.size() != 0) {
        for (float gt = 0; gt < 1; gt += 0.01) {
            catmullRomPoint(gt, p, catmull_points);
            curve_points.push_back(new Vertex(p[0], p[1], p[2]));
        }
    }
    else return;
}

int Translation::getCurveSize(){
    return catmull_points.size();
}

void Translation::drawCurve() {
    if (curve_points.size() != 0) {

        glBegin(GL_LINE_LOOP);

        for (Vertex *v: curve_points) {
            glVertex3f(v->getx(), v->gety(), v->getz());
        }

        glEnd();
    }
}

void Translation::pushvertex(Vertex *v){
    catmull_points.push_back(v);
}

void Translation::make() {


    float coord[3] = {getx(),gety(),getz()};

    if(time>0){
        float elapsed = glutGet(GLUT_ELAPSED_TIME) % (int) (time * 1000);
        float rt = elapsed/(time*1000);

        catmullRomPoint(rt,coord,catmull_points);
    }

    glTranslatef(coord[0], coord[1], coord[2]);

}

Translation::Translation(void){

}

Translation::~Translation(void){

}
