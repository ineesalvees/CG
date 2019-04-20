#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES

#include "../headers/Transformation.h"
#include "../headers/Figure.h"
#include "../headers/VBO.h"
#include "../headers/Group.h"
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

int start = 0;

float ax = 0;
float ay = 0;
float az = 0;

float cx = 0;
float cy = 0;
float cz = 0;

float speed = 5;

int X_TRANSLATE = 0;
int Y_TRANSLATE = 0;
int Z_TRANSLATE = 0;

int mode = GL_FILL;
int mode_aux = 1;

float scale = 1;

int X_ANGLE = 0;
int Y_ANGLE = 0;
int Z_ANGLE = 0;

//Mouse movements
int alpha = 0, beta = 45, r = 50;
float camX = 0, camY, camZ = 5;
int startX, startY, tracking = 0;

float px = 0.0f, py = 0.0f, pz = 10.0f, dx= 0.0f, dy = 0.0f, dz = -1.0f, ux = 0.0f, uy = 1.0f, uz = 0.0f;
double alfa = M_PI;
double beta1 = M_PI;
int mexer = 0;
int timebase = 0, frame = 0;


using namespace std; 


std::vector<Group> groups;

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

void changeMode() {
    if (mode_aux == 0)
        mode = GL_LINE;
    else if (mode_aux == 1)
        mode = GL_FILL;
    else if (mode_aux == 2)
        mode = GL_POINT;

    glPolygonMode(GL_FRONT_AND_BACK, mode);
}

void moveforward(){

    px = px + 0.5 * dx;
    py = py + 0.5 * dy;
    pz = pz + 0.5 * dz;
}

void movebackwards(){

    px = px - 0.5 * dx;
    py = py - 0.5 * dy;
    pz = pz - 0.5 * dz;
}



VBO* readFile(string name) {

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

    VBO *vbo = new VBO(figure->getvertexes());
    return vbo;


  }

  nfile.close();
}


Group* groupReader(pugi::xml_node group,Translation *translation, Rotation *rotation,Color *color, Scale *scale) {
    glPushMatrix();

    Group *res = new Group();


    for (pugi::xml_node attr = group.first_child(); attr; attr = attr.next_sibling()) //percorre os varios atributos
    {
        if (strcmp(attr.name(),"translate")==0  ) {

            pugi::xml_attribute time,x , y , z;

            x = attr.first_attribute();
            if(strcmp(x.name(),"time")==0) {
                translation = new Translation();
                std::string timev,xv,yv,zv;

                time = x;
                timev = time.value();
                translation->setTime(atof(timev.c_str()));

                for (pugi::xml_node point = attr.first_child(); point ; point = point.next_sibling()) {
                    
                    x = point.first_attribute();
                    y = x.next_attribute();
                    z = y.next_attribute();
                    xv = x.value();
                    yv = y.value();
                    zv = z.value();
                    Vertex *vertex = new Vertex(atof(xv.c_str()),atof(yv.c_str()),atof(zv.c_str()));
                    translation->pushvertex(vertex);
                }
            }
            else {
                y = x.next_attribute();
                z = y.next_attribute();
                std::string xv,yv,zv;
                xv = x.value();
                yv = y.value();
                zv = z.value();
                /*
                Vertex *vertex = new Vertex(atof(xv.c_str()),atof(yv.c_str()),atof(zv.c_str()));
                translation->pushvertex(vertex);
                */
                
                translation = new Translation(atof(xv.c_str()),atof(yv.c_str()),atof(zv.c_str()),0);

            }
            continue;

        }
        if (strcmp(attr.name(),"rotate")==0) {

            pugi::xml_attribute time , cx,cy , cz;

            time = attr.first_attribute();

            cx = time.next_attribute();
            cy = cx.next_attribute();
            cz = cy.next_attribute();

            std::string timev,cxv,cyv,czv;
            timev = time.value();
            cxv = cx.value();
            cyv = cy.value();
            czv = cz.value();


            rotation = new Rotation(atof(timev.c_str()),atof(cxv.c_str()),atof(cyv.c_str()),atof(czv.c_str()));

            //printf("Rotate\nx- %s \ny- %s \nz- %s\n",cx.value(),cy.value(),cz.value());
            continue;
        }

        if (strcmp(attr.name(),"scale")==0 || strcmp(attr.name(),"color")==0) {

            pugi::xml_attribute x , y , z;

            x = attr.first_attribute();
            y = x.next_attribute();
            z = y.next_attribute();

            std::string xv,yv,zv;
            xv = x.value();
            yv = y.value();
            zv = z.value();

            if (strcmp(attr.name(),"scale")==0) scale = new Scale(atof(xv.c_str()),atof(yv.c_str()),atof(zv.c_str()));
            else color = new Color(atof(xv.c_str()),atof(yv.c_str()),atof(zv.c_str()));

            continue;
        }


        if (strcmp(attr.name(),"models")==0) {

            for (pugi::xml_node model = attr.first_child(); model; model = model.next_sibling())
            {

                pugi::xml_attribute filename = model.first_attribute();
                
                
                res->pushVBO(readFile(filename.value()));
                
                
            }

            


            if (translation != NULL) res->pushTransformation(translation);
            //if (rotation != NULL) res->pushTransformation(rotation);
            if (scale != NULL) res->pushTransformation(scale);
            if (color != NULL) res->pushTransformation(color);

            




            continue;
            
        }
        if (strcmp(attr.name(),"group")==0) {
            //printf("group--------\n");


            res->pushGroup(groupReader(attr,translation,rotation,color,scale));

        }

    }
    glPopMatrix();

    return res;

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


        Group *g = groupReader(group,NULL,NULL,NULL,NULL);

        groups.push_back(*g);


    }

}

void render(Group g){
    glPushMatrix();
    vector<Transformation*> t_list = g.getTransformations();
    for(Transformation *t: t_list){
        t->make();
    }

    vector<VBO> vbos = g.getVBOs();
    for(VBO v: vbos) v.render();

    vector<Group> children = g.getChildren();
    for(Group child: children) render(child);
    glPopMatrix();
}

void renderScene() {
    float fps;
    int time;
    char s[64];

    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();

    dx = sin(alfa);
    dy = sin(beta1);
    dz = cos(alfa);

    gluLookAt(px, py, pz,
              px + dx, py + dy, pz + dz,
              ux, uy, uz);

    frame++;
    time=glutGet(GLUT_ELAPSED_TIME);
    if (time - timebase > 1000) {
        fps = frame*1000.0/(time-timebase);
        timebase = time;
        frame = 0;
        sprintf(s, "FPS: %f6.2", fps);
        glutSetWindowTitle(s);
    }

    if (mexer){
        moveforward();
    };

    glColor3f(1,1,1);

    changeMode();

    glTranslatef(X_TRANSLATE ,Y_TRANSLATE ,Z_TRANSLATE);

    glRotatef(X_ANGLE, 1, 0, 0);
    glRotatef(Y_ANGLE, 0, 1, 0);
    glRotatef(Z_ANGLE, 0, 0, 1);

    //Zoom in & Zoom out
    glScalef(scale, scale, scale);

    //glPolygonMode(GL_FRONT,GL_LINE);
    for(Group g: groups) render(g);

   
    // End of frame
    glutSwapBuffers();
}

// write function to process keyboard events
void keyboard(unsigned char key, int x, int y){
    if (key == 'm') {
        mode_aux++;
        mode_aux = mode_aux % 3;
    }

    if (key == '+')
        scale += 0.1;


    if (key == '-') {
        scale -= 0.1;
        if (scale <= 0.1)
            scale = 0.1;
    }

    if (key == 'n')
        mexer = (mexer + 1) % 2;

    if (key == ' ')
        moveforward();

    if (key == 'b')
        movebackwards();

    glutPostRedisplay();
}

void movement (int key, int x, int y) {

   switch (key) {
        case GLUT_KEY_LEFT :
            alfa += 0.1f;
            break;
        case GLUT_KEY_RIGHT :
            alfa -= 0.1f;
            break;
        case GLUT_KEY_UP :
            beta1 -= 0.08f;
            if (beta1 < M_PI / 2)
                beta1 = M_PI / 2;
            break;
        case GLUT_KEY_DOWN :
            beta1 += 0.08f;
            if (beta1 > 3 * M_PI / 2)
                beta1 = 3 * M_PI / 2;
            break;
    }

    glutPostRedisplay();
}

void processMouseButtons(int button, int state, int xx, int yy) {

    if (state == GLUT_DOWN)  {
        startX = xx;
        startY = yy;
        if (button == GLUT_LEFT_BUTTON)
            tracking = 1;
        else if (button == GLUT_RIGHT_BUTTON)
            tracking = 2;
        else
            tracking = 0;
    }
    else if (state == GLUT_UP) {
        if (tracking == 1) {
            alpha += (xx - startX);
            beta += (yy - startY);
        }
        else if (tracking == 2) {

            r -= yy - startY;
            if (r < 3)
                r = 3.0;
        }
        tracking = 0;
    }

    glutPostRedisplay();
}


void processMouseMotion(int xx, int yy) {

    int deltaX, deltaY;
    int alphaAux, betaAux;
    int rAux;

    if (!tracking)
        return;

    deltaX = xx - startX;
    deltaY = yy - startY;

    if (tracking == 1) {
        alfa += 0.0001 * -(xx - startX);
        beta1 += 0.0001 * (yy - startY);

        alphaAux = alpha + deltaX;
        betaAux = beta + deltaY;

        if (betaAux > 85.0)
            betaAux = 85.0;
        else if (betaAux < -85.0)
            betaAux = -85.0;

        rAux = r;
    }
    else if (tracking == 2) {

        alphaAux = alpha;
        betaAux = beta;
        rAux = r - deltaY;
        if (rAux < 3)
            rAux = 3;
    }
    camX = rAux * sin(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
    camZ = rAux * cos(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
    camY = rAux *                                sin(betaAux * 3.14 / 180.0);

    glutPostRedisplay();
}




int main(int argc, char **argv) {

    filename = argv[1];
// init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800,800);
    glutCreateWindow("CG@DI-UM");
    glEnableClientState(GL_VERTEX_ARRAY);

    #ifdef __APPLE__
    #else
        glewInit();
    #endif

        
    parseFile2(filename);

// Required callback registry 
    glutDisplayFunc(renderScene);
    //glutIdleFunc(renderScene);
    glutReshapeFunc(changeSize);
//  glutKeyboardFunc(move);

    glutKeyboardFunc(keyboard);
    glutSpecialFunc(movement);

    glutMouseFunc(processMouseButtons);
    glutMotionFunc(processMouseMotion);
    
// Callback registration for keyboard processing
//  glutKeyboardFunc(processKeys);
//  glutSpecialFunc(processSpecialKeys);
    
//  OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    
// enter GLUT's main cycle
    glutMainLoop();

    
    return 1;
}
