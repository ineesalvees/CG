#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include "../headers/Plane.h"
#include "../headers/Box.h"
#include "../headers/Cone.h"
#include "../headers/Sphere.h"
#include <math.h>
#include "../pugixml-1.9/src/pugixml.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <iostream> 
#include <sstream> 
#include <fstream>
#include <stdio.h>

char *filename;

float ax = 0;
float ay = 0;
float az = 0;

float cx = 0;
float cy = 0;
float cz = 0;

float speed = 5;

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}




// write function to process keyboard events
void move(unsigned char key, int x, int y){
	switch (key) {
        case 'q':
            cx++;
			glutPostRedisplay();
            break;
        case 'w':
            cx--;
			glutPostRedisplay();
            break;
		case 'a':
			cy++;
			glutPostRedisplay();
			break;
		case 's':
			cy--;
			glutPostRedisplay();
			break;
		case 'z':
            cz++;
			glutPostRedisplay();
            break;
        case 'x':
            cz--;
			glutPostRedisplay();
            break;
		case 't':
			ax += speed;
			glutPostRedisplay();
			break;
		case 'y':
			ax -= speed;
			glutPostRedisplay();
			break;
		case 'g':
			ay += speed;
			glutPostRedisplay();
			break;
		case 'h':
	 		ay -= speed;
			glutPostRedisplay();
 			break;
		case 'b':
			az += speed;
			glutPostRedisplay();
			break;
		case 'n':
			az -= speed;
			glutPostRedisplay();
			break;	
	}
}


using namespace std; 

void readFile(string name) {
  int i = 0;
  int arr[10];

  ifstream nfile(name.c_str());

  stringstream ss;

  if (nfile.good())
  {
    string linha;
    getline(nfile, linha);
    
    

    if (linha.at(0) == 'P') { //Plano
    	ss << linha; 
    	string temp; 
    	int found; 
    	while (!ss.eof()) { 
        	ss >> temp; 
        	if (stringstream(temp) >> found) {
            	arr[i] = found;
            	i++;
        	}

        	temp = ""; 
    	}
    	Plane *p = new Plane (arr[0],arr[1]);
    	p->draw();
    }



    if ( linha.at(0) == 'C' || linha.at(0) == 'B' ) { //cone
    	ss << linha; 
    	string temp; 
    	int found; 
    	while (!ss.eof()) { 
        	ss >> temp; 
        	if (stringstream(temp) >> found) {
            	arr[i] = found;
            	i++;
        	}

        	temp = ""; 
    	}
    	if (linha.at(0) == 'C') {
    		Cone *c = new Cone (arr[0],arr[1],arr[2],arr[3]);
    		c->draw();
    	}
    	if (linha.at(0) == 'B') {
    		Box *b = new Box (arr[0],arr[1],arr[2],arr[3]);
			b->draw(arr[0],arr[1],arr[2],arr[3]);    	
    	}

    }

    if ( linha.at(0) == 'S') { //sphere
    	ss << linha; 
    	string temp; 
    	int found; 
    	while (!ss.eof()) { 
        	ss >> temp; 
        	if (stringstream(temp) >> found) {
            	arr[i] = found;
            	i++;
        	}

        	temp = ""; 
    	}
    	Sphere *s = new Sphere(arr[0],arr[1],arr[2]);
    	s->draw();
    }

  }

  nfile.close();
}
void parseFile(char * path) {

	pugi::xml_document doc;
    
    if (!doc.load_file(path)) {
    	printf("ERROR");
    	return ;
    }

    pugi::xml_node scene = doc.child("scene");

	for (pugi::xml_node model = scene.first_child(); model; model = model.next_sibling())
    {

    	pugi::xml_attribute filename = model.first_attribute();
 
        readFile(filename.value());

    }
}

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(5.0,5.0,5.0, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);

	glRotatef(ax,1,0,0);
	glRotatef(ay,0,1,0);
	glRotatef(az,0,0,1);
	glTranslatef(cx,cy,cz);

	glPolygonMode(GL_FRONT,GL_LINE);


	Plane *p = new Plane (6,2);
	//p->draw();
	p->save("/home/joaonuno/Desktop/3Ano/2semestre/CG/Trabalho/Git/CG/PlanoTESTE.3d");

	Box *b = new Box (1,3,3,0);
	//b->draw();
	b->save("/home/joaonuno/Desktop/3Ano/2semestre/CG/Trabalho/Git/CG/BoxTESTE.3d");

	Cone *c = new Cone(2,3,100,30);
	c->save("/home/joaonuno/Desktop/3Ano/2semestre/CG/Trabalho/Git/CG/ConeTESTE.3d");

	Sphere *s = new Sphere(3,20,30);
	s->save("/home/joaonuno/Desktop/3Ano/2semestre/CG/Trabalho/Git/CG/SphereTESTE.3d");

	parseFile(filename);
	// End of frame
	glutSwapBuffers();
}




int main(int argc, char **argv) {

	filename = argv[1];
// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");
		
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutKeyboardFunc(move);
	
// Callback registration for keyboard processing
//	glutKeyboardFunc(processKeys);
//	glutSpecialFunc(processSpecialKeys);
	
//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
// enter GLUT's main cycle
	glutMainLoop();

	
	return 1;
}