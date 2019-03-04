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

void draw(double comp, double largure, double height, int stack){
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

			glBegin(GL_TRIANGLES);
				glColor3f(0, 0, 0);
				glVertex3f(x, y, z);
				glVertex3f(xx, y, z);
				glVertex3f(x, y, zz);
		
				glColor3f(0, 0, 0);
				glVertex3f(xx, y, z);
				glVertex3f(xx, y, zz);
				glVertex3f(x, y, zz);

				glColor3f(0, 0, 0);
				glVertex3f(x, yy, z);
				glVertex3f(x, yy, zz);
				glVertex3f(xx, yy, z);

				glColor3f(0, 0, 0);
				glVertex3f(xx, yy, z);
				glVertex3f(x, yy, zz);
				glVertex3f(xx, yy, zz);
			glEnd();

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

			glBegin(GL_TRIANGLES);
				glColor3f(0, 0, 0);
				glVertex3f(x, y, z);
				glVertex3f(x, yy, z);
				glVertex3f(x, yy, zz);
		
				glColor3f(0, 0, 0);
				glVertex3f(x, y, zz);
				glVertex3f(xx, yy, z);
				glVertex3f(x, yy, zz);

				glColor3f(0, 0, 0);
				glVertex3f(xx, y, z);
				glVertex3f(xx, y, zz);
				glVertex3f(xx, yy, zz);

				glColor3f(0, 0, 0);
				glVertex3f(xx, y, z);
				glVertex3f(xx, yy, zz);
				glVertex3f(xx, yy, z);
			glEnd();

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

			glBegin(GL_TRIANGLES);
				glColor3f(0, 0, 0);
				glVertex3f(x, y, z);
				glVertex3f(xx, y, z);
				glVertex3f(x, yy, z);
		
				glColor3f(0, 0, 0);
				glVertex3f(xx, y, z);
				glVertex3f(xx, yy, z);
				glVertex3f(x, yy, z);

				glColor3f(0, 0, 0);
				glVertex3f(x, y, zz);
				glVertex3f(x, yy, zz);
				glVertex3f(xx, y, zz);

				glColor3f(0, 0, 0);
				glVertex3f(xx, y, zz);
				glVertex3f(x, yy, zz);
				glVertex3f(xx, yy, zz);
			glEnd();

			x = x + stackC;    //x vai incrementando o valor do espaçamento do comprimento, para ficar com as stack indicadas
			xx = xx + stackC; //xx também incrementa o valor do espaçamento do comprimento, para ficar sempre na proxima camada no eixo do x	
		}
		y = y + stackA; //incrementar na altura o valor do espaçamento, para obter nessa altura as stack indicadas	
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
	glColor3b(1, 0, 0);
	draw(4, 3, 3, 5);

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