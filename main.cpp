#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include "Plane.cpp"
#include "Box.cpp"
#include <math.h>


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

// desenha um plano no xOz com tamanho size
void drawPlane(float size) {

	glBegin(GL_TRIANGLES);

		glVertex3f(size/2.0,0,-size/2.0); //A
		glVertex3f(-size/2.0,0,size/2.0); //C
		glVertex3f(size/2.0,0,size/2.0); //B
	glEnd();
		
	glBegin(GL_TRIANGLES);
		glVertex3f(size/2.0,0,-size/2.0); //A
		glVertex3f(-size/2.0,0,-size/2.0); //D
		glVertex3f(-size/2.0,0,size/2.0); //C


	glEnd();
}
void drawBox(float xx , float y , float zz , int slices) {
	float x = xx/2.0;
	float z = zz / 2.0;

	glBegin(GL_TRIANGLES);
		glColor3f(1, 0, 0);
		glVertex3f(-x,y,z); //E
		glVertex3f(-x,0.0f,z); //A
		glVertex3f(x,0.0f,z); //B
	glEnd();
	
	glBegin(GL_TRIANGLES);
		glColor3f(1, 0, 0);
		glVertex3f(-x,y,z); //E
		glVertex3f(x,0.0f,z); //B
		glVertex3f(x,y,z); //G
	glEnd();

	glBegin(GL_TRIANGLES);
		glColor3f(1, 1, 0);
		glVertex3f(x,y,-z); //H
		glVertex3f(-x,y,-z); //F
		glVertex3f(x,0.0f,-z); //C
	glEnd();

	glBegin(GL_TRIANGLES);
		glColor3f(1, 1, 0);
		glVertex3f(-x,y,-z); //F
		glVertex3f(-x,0.0f,-z); //D
		glVertex3f(x,0.0f,-z); //C
	glEnd();


	glBegin(GL_TRIANGLES);
		glColor3f(1, 0, 1);
		glVertex3f(-x,y,z); //E
		glVertex3f(-x,y,-z); //F
		glVertex3f(-x,0.0f,z); //A
	glEnd();

	glBegin(GL_TRIANGLES);
		glColor3f(1, 0, 1);
		glVertex3f(-x,0.0f,z); //A
		glVertex3f(-x,0.0f,-z); //D
		glVertex3f(x,0.0f,z); //B
	glEnd();

	glBegin(GL_TRIANGLES);
		glColor3f(1, 0, 1);
		glVertex3f(-x,0.0f,z); //A
		glVertex3f(-x,y,-z); //F
		glVertex3f(-x,0.0f,-z); //D
	glEnd();

	glBegin(GL_TRIANGLES);
		glColor3f(1, 0, 1);
		glVertex3f(-x,0.0f,-z); //D
		glVertex3f(x,0.0f,-z); //C
		glVertex3f(x,0.0f,z); //B
	glEnd();

	glBegin(GL_TRIANGLES);
		glColor3f(1, 0, 1);
		glVertex3f(-x,y,-z); //F
		glVertex3f(-x,y,z); //E
		glVertex3f(x,y,z); //G
	glEnd();

	glBegin(GL_TRIANGLES);
		glColor3f(1, 0, 1);
		glVertex3f(x,y,-z); //H
		glVertex3f(-x,y,-z); //F
		glVertex3f(x,y,z); //G
	glEnd();

	glBegin(GL_TRIANGLES);
		glColor3f(1, 0, 1);
		glVertex3f(x,y,z); //G
		glVertex3f(x,0.0f,z); //B
		glVertex3f(x,0.0f,-z); //C
	glEnd();

	glBegin(GL_TRIANGLES);
		glColor3f(1, 0, 1);
		glVertex3f(x,y,-z); //H
		glVertex3f(x,y,z); //G
		glVertex3f(x,0.0f,-z); //C
	glEnd();

	glBegin(GL_TRIANGLES);
		glColor3f(1, 0, 1);
		glVertex3f(-x,0.0f,-z); //D
		glVertex3f(-x,0.0f,z); //A
		glVertex3f(x,0.0f,-z); //C
	glEnd();

	glBegin(GL_LINES);
		glColor3f(1, 1, 1);
    	glVertex3f(0, 0, 0);
    	glVertex3f(4, 0, 0);
	glEnd();

	glBegin(GL_LINES);
		glColor3f(1, 1, 1);
    	glVertex3f(0, 0, 0);
    	glVertex3f(0, 0, 4);
	glEnd();

	glBegin(GL_LINES);
		glColor3f(1, 1, 1);
    	glVertex3f(0, 0, 0);
    	glVertex3f(0, 4, 0);
	glEnd();


}

void drawSphere( float radius , int slices, int stacks) {

}

void drawCone( float radius, float height, int slices, int stacks) {

}

void drawCylinder(float radius, float height, int slices) {

// put code to draw cylinder in here

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
	glPolygonMode(GL_FRONT,GL_LINE);
	glBegin(GL_TRIANGLES);

	glTranslatef(cx,cy,cz);
	//drawCylinder(1,2,10);
	//drawPlane(3);
	//drawBox(1,3,2,0);
	Plane *p = new Plane (4,2);
	p->draw();

	Box *b = new Box (1,3,3,0);
	b->draw();

	// End of frame
	glutSwapBuffers();
}


void processKeys(unsigned char c, int xx, int yy) {

// put code to process regular keys in here

}


void processSpecialKeys(int key, int xx, int yy) {

// put code to process special keys in here

}


int main(int argc, char **argv) {

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
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
// enter GLUT's main cycle
	glutMainLoop();

	
	return 1;
}