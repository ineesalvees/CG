#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

float alpha = 0.61547999;
float beta = 0.61547999;
float rad = 8.66025;

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

void draw(float radius, int slices, int stack){
	//float d_angle = 2*M_PI / slices;
	//float act_angle = 0;
	float alpha, beta, beta1;

	
	//beta1 = beta + ((M_PI)/stack);

	for(int j = 0; j < stack; j++){
		for(int i=0; i < slices; i++){
			alpha = i * ((2*M_PI) / slices);
			beta = j * ((M_PI)/stack) - M_PI / 2;
			beta1 = beta + ((M_PI)/stack);

		glBegin(GL_TRIANGLES);

		//lateral 1
		glColor3f(1, 0, 0);
		glVertex3f(radius*cos(beta) * cos(alpha), radius*sin(beta), radius*cos(beta)*sin(alpha));
		glVertex3f(radius*cos(beta + ((M_PI)/stack)) * cos(alpha), sin(beta + ((M_PI)/stack))*radius, radius*cos(beta + ((M_PI)/stack))*sin(alpha));
		glVertex3f(radius*cos(beta)*cos(alpha + ((2*M_PI) / slices)),radius*sin(beta),radius*cos(beta)*sin(alpha + ((2*M_PI) / slices)));

		//lateral 2
		
		glColor3f(1, 0, 0);
		glVertex3f(radius*cos(beta + ((M_PI)/stack)) * cos(alpha), sin(beta + ((M_PI)/stack))*radius, radius*cos(beta + ((M_PI)/stack))*sin(alpha));
		glVertex3f(radius*cos(beta + ((M_PI)/stack))*cos(alpha + ((2*M_PI) / slices)), radius*sin(beta + ((M_PI)/stack)), radius*cos(beta1)*sin(alpha + ((2*M_PI) / slices)));
		glVertex3f(radius*cos(beta)*cos(alpha + ((2*M_PI) / slices)), radius*sin(beta), radius*cos(beta)*sin(alpha + ((2*M_PI) / slices)));

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
	draw(1, 50, 50);

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

void processKeys(unsigned char c, int xx, int yy) {

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