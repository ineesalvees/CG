#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

#include "../headers/Vertex.h"
#include "../headers/Figure.h"
#include "../headers/Plane.h"
#include "../headers/Box.h"
#include "../headers/Cone.h"
#include "../headers/Sphere.h"

void generatePatch(char* patch_path, char* tesselation, char* f_path);
void writeFile(Shape* s, string f_path);

using namespace std;

int main (int argc, char *argv[]) {
	cout << argv[1] << "\n";

	if (argc > 2) {
		if (strcmp(argv[1],"Sphere") == 0) {
			cout << "Drawing Sphere!\n";

			float radius = atof(argv[2]);
			int slices = atoi(argv[3]);
			int stacks = atoi(argv[4]);

			Sphere *s = new Sphere(radius,slices,stacks);
			s->figure->save(argv[5]);
		}
		if (strcmp(argv[1],"Box") == 0) {
			cout << "Drawing Box!\n";

			float x = atof(argv[2]);
			float y = atof(argv[3]);
			float z = atof(argv[4]);
			int slices = atoi(argv[5]);

			Box *b = new Box(x,y,z,slices);
			b->figure->save(argv[6]);
			
		}
		if (strcmp(argv[1],"Plane") == 0) {
			cout << "Drawing Plane!\n";

			float size = atof(argv[2]);
			float height = atof(argv[3]);

			Plane *p = new Plane(size,height);
			p->figure->save(argv[4]);
		}
		if (strcmp(argv[1],"Cone") == 0) {
			cout << "Drawing Cone!\n";

			float radius = atof(argv[2]);
			float height = atof(argv[3]);
			int slices = atoi(argv[4]);
			int stacks = atoi(argv[5]);
			
			Cone *c = new Cone (radius,height,slices,stacks);
			c->figure->save(argv[6]);
		}
		if (strcmp(argv[1],"Orbit") == 0) {
			cout << "Drawing orbit!\n";

			Figure *f = new Figure ();

			float radius = atof(argv[2]);
			int lados = 1000;
			float inc = (2 * M_PI) / lados;

			for (int i=0; i<lados; i+=2) {
				f->add(radius*sin(inc*i),0,radius*cos(inc*i));
				f->add(radius*sin(inc*(i+1)),0,radius*cos(inc*(i+1)));
				f->add(radius*sin(inc*(i+1)),0,radius*cos(inc*(i+2)));
			}
			f->save(argv[3]);
		}
		if (strcmp(argv[1],"Teapot") == 0){
			generatePatch(argv[2],argv[3],argv[4]);
		}
		
		if (strcmp(argv[1],"Torus") == 0) {

	Figure *f = new Figure ();

	float radiusIn = atof(argv[2]);
	float radiusOut = atof(argv[3]);
	int sides = atoi(argv[4]);
	int rings = atoi(argv[5]);

	float dimSide = (2*M_PI)/sides;
	float dimRing = (2*M_PI)/rings;

	for (int i = 0; i < rings; i++) {		
		double a0 = i*dimRing;
		double a1 = a0 + dimRing;

		float x0 = cos(a0);
		float y0 = sin(a0);
		float x1 = cos(a1);
		float y1 = sin(a1);

		for (int j = 0; j < sides+1; j++){

			//pontos actuais
			float c = cos(j*dimSide);
			float r = radiusIn * c + radiusOut;
			float z = radiusIn * sin(j*dimSide);
			
			//proximos pontos
			float nc = cos((j+1)*dimSide);
			float nr = radiusIn * nc + radiusOut;
			float nz = radiusIn * sin((j+1)*dimSide);

			f->pushvertex(new Vertex(x0*r,y0*r,z));
			f->pushvertex(new Vertex(x1*r,y1*r,z));
			f->pushvertex(new Vertex(x0*nr,y0*nr,nz));
				

			f->pushvertex(new Vertex(x0*nr,y0*nr,nz));
			f->pushvertex(new Vertex(x1*r,y1*r,z));
			f->pushvertex(new Vertex(x1*nr,y1*nr,nz));
		}
	}
			f->save(argv[6]);


		}

	} else {
		cout << "Argumentos insuficientes!\n";
	}


void generatePatch(char* patch_path, char* tesselation, char* f_path){
    int tess;

    tess = atoi(tesselation);

    Figure* f = bezier_Parse(patch_path,tess);
    writeFile(f,f_path);
}

// Writes all our Shape's Vertexes on the desired file ("f_path")
void writeFile(Figure* f, string f_path){
    char buff[1024];
    int i;
    int size = f->getSize();
    Vertex* v;

    system("mkdir -p ../files3d/ ");
    string path = "../files3d/" + f_path;
    ofstream file (path,std::ofstream::out);

    for(i=0;i<size;i++){
        f->getVertexAt(i,&v);
        sprintf(buff, "%f %f %f\n", v->getx(), v->gety(), v->getz());
        file << buff;
    }

    file.close();
}


}
