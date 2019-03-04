#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
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

void drawCone(float radius, float height, int slices, int stack){
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
	drawCone(2, 3, 15, 10);
	

	// End of frame
	glutSwapBuffers();
}

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

	glClearColor(1,1,1,1) ;
	glClear(GL_COLOR_BUFFER_BIT);

// Required callback registry
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);


// Callback registration for keyboard processing
	glutKeyboardFunc(move);
	glutSpecialFunc(processSpecialKeys);

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

// enter GLUT's main cycle
	glutMainLoop();

	return 1;
}