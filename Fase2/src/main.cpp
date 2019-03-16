#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES

#include "../headers/Translation.h"
#include "../headers/Figure.h"
#include "../headers/Rotation.h"
#include <math.h>
#include "../pugixml-1.9/src/pugixml.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <iostream> 
#include <sstream> 
#include <fstream>
#include <stdio.h>
#include <string.h>

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

void readFile(string name,Translation *translation, Rotation *rotation) {

  double arr[3];
  Figure *figure = new Figure();
  int verts = 0;

  ifstream nfile(name.c_str());

  stringstream ss;

  if (nfile.good())
  {
    string linha;
    getline(nfile, linha);
    
    	ss << linha; 
    	string temp; 
    	double found; 

    	while (!ss.eof()) { 
        	ss >> temp; 
        	if (stringstream(temp) >> found) {
            	arr[verts] = found;

            	if (verts == 2) {
            		figure->pushvertex(new Vertex(arr[0], arr[1], arr[2]));
            	}

            	verts = (verts + 1) % 3;

        	}

        	temp = ""; 

    	}
    	int index = 0;

     /*

		POR AQUI AS FUNCOES QUE VAO APLICAR A FIGURA TRANSLACOES E ROTACOES
	
     */
	 figure->draw();
    

  }

  nfile.close();
}


void groupReader(pugi::xml_node group,Translation *translation, Rotation *rotation) {


	//Translate translate = NULL;

	//group = scene.first_child();
	for (pugi::xml_node attr = group.first_child(); attr; attr = attr.next_sibling()) //percorre os varios atributos
    {
    	if (strcmp(attr.name(),"translate")==0) {


    		pugi::xml_attribute x , y , z;

    		x = attr.first_attribute();
    		y = x.next_attribute();
    		z = y.next_attribute();

    		std::string xv,yv,zv;
    		xv = x.value();
    		yv = y.value();
    		zv = z.value();


    		translation = new Translation(atof(xv.c_str()),atof(yv.c_str()),atof(zv.c_str()));

    		//printf("Translate\nx- %s \ny- %s \nz- %s\n",x.value(),y.value(),z.value());
    		//translate = new Translate(atol(x.value()),atol(y.value()),atol(z.value()));
    		continue;

    	}
    	if (strcmp(attr.name(),"rotate")==0) {

    		pugi::xml_attribute angle , cx,cy , cz;

    		angle = attr.first_attribute();

    		cx = angle.next_attribute();
    		cy = cx.next_attribute();
    		cz = cy.next_attribute();

    		std::string anglev,cxv,cyv,czv;
    		anglev = angle.value();
    		cxv = cx.value();
    		cyv = cy.value();
    		czv = cz.value();


    		rotation = new Rotation(atof(anglev.c_str()),atof(cxv.c_str()),atof(cyv.c_str()),atof(czv.c_str()));

    		printf("Rotate\nx- %s \ny- %s \nz- %s\n",cx.value(),cy.value(),cz.value());
    		continue;
    	}
    	if (strcmp(attr.name(),"models")==0) {

    		for (pugi::xml_node model = attr.first_child(); model; model = model.next_sibling())
    		{

    			pugi::xml_attribute filename = model.first_attribute();

    			printf("Models\n");
        		printf(filename.value());
        		readFile(filename.value(),translation,rotation);

    		}
    		
    	}
    	if (strcmp(attr.name(),"group")==0) {
    		printf("group--------\n");

    		groupReader(attr,translation,rotation);
    	}

    }


}

void parseFile2(char *path) {
	pugi::xml_document doc;
    
    if (!doc.load_file(path)) {
    	printf("ERROR");
    	return ;
    }

    pugi::xml_node scene = doc.child("scene");

    pugi::xml_node group = scene.first_child();

	for (pugi::xml_node group = scene.first_child(); group; group = group.next_sibling()) //percorre os varios groups
    {
    	groupReader(group,NULL,NULL);
    	//pugi::xml_attribute filename = model.first_attribute();
 		
        //readFile(filename.value());

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


	parseFile2(filename);
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