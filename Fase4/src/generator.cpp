#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

#include "../headers/Vertex.h"
#include "../headers/Figure.h"

#include "../headers/Bezier.h"
//#include "Bezier.cpp"
//void generatePatch(char* patch_path, char* tesselation, char* f_path);
//void writeFile(Shape* s, string f_path);

using namespace std;



void processPatch(int tesselation, int n);
Vertex* bezierCalc(float u, float v, int n);
Vertex* vertexCalc(float t, float *p1, float *p2, float *p3, float *p4);

int p_size;
int* patches;
Figure* model = new Figure();
vector<Vertex*> control_points;



Figure* bezierPatch_parse(string patch_path, int tesselation){
    string line;
    ifstream file(patch_path);

    if (file.fail()) {
        cout<< "Couldn't find file: " << patch_path  << "." << endl;
    }

    getline(file,line);

    p_size = std::stoi(line);
    patches = (int *) malloc (sizeof(int) * p_size*16);

    for(int i= 0; i != p_size; i++){
        getline(file,line);

        for(int j = 0; j< 16; j++){
            int pos = line.find(",");
            string token = line.substr(0,pos);
            patches[(j+(16*i))] = atoi(token.c_str());
            line.erase(0,pos+1);
        }
    }

    getline(file,line);

    while(getline(file,line)){
        Vertex* v = new Vertex(line);
        control_points.push_back(v);
    }

    for(int i=0; i != p_size; i++){
        processPatch(tesselation, i);
    }

    return model;
}

void processPatch(int tesselation, int n) {
    float aux = 1.0/tesselation;
    float u, v, u2, v2;

    for (int i = 0; i < tesselation; i++) {
        for (int j = 0; j < tesselation; j++) {
            u = i * aux;
            v = j * aux;
            u2 = (i + 1) * aux;
            v2 = (j + 1) * aux;

            Vertex *p1 = bezierCalc(u,v,n);
            Vertex *p2 = bezierCalc(u,v2,n);
            Vertex *p3 = bezierCalc(u2,v,n);
            Vertex *p4 = bezierCalc(u2,v2,n);

            model->pushvertex(p1);
            model->pushvertex(p3);
            model->pushvertex(p4);

            model->pushvertex(p1);
            model->pushvertex(p4);
            model->pushvertex(p2);
        }
    }
}

Vertex* bezierCalc(float u, float v, int n_patch){
    float bz[4][3], res[4][3];
    int j = 0, k = 0;
    n_patch = (16*n_patch);


    for(int i = 0; i < 16; i++){
        bz[j][0] = control_points.at(patches[n_patch+i])->getx();
        bz[j][1] = control_points.at(patches[n_patch+i])->gety();
        bz[j][2] = control_points.at(patches[n_patch+i])->getz();

        j++;

        if( j % 4 == 0){
            Vertex *v = vertexCalc(u,bz[0],bz[1],bz[2],bz[3]);

            res[k][0] = v->getx();
            res[k][1] = v->gety();
            res[k][2] = v->getz();

            k++;
            j=0;
        }
    }

    return vertexCalc(v,res[0],res[1],res[2],res[3]);
}

Vertex* vertexCalc(float t, float *p1, float *p2, float *p3, float *p4){
    float points[3];

    float bz1= (1.0 -t) * (1.0 -t) * (1.0 -t);
    float bz2 = 3 * t * (1.0 -t) * (1.0 -t);
    float bz3 = 3 * t * t * (1.0 -t);
    float bz4 = t * t * t;

    points[0] = bz1*p1[0] + bz2*p2[0] + bz3*p3[0] + bz4*p4[0];
    points[1] = bz1*p1[1] + bz2*p2[1] + bz3*p3[1] + bz4*p4[1];
    points[2] = bz1*p1[2] + bz2*p2[2] + bz3*p3[2] + bz4*p4[2];

    return (new Vertex(points[0],points[1],points[2]));
}











int main (int argc, char *argv[]) {
	cout << argv[1] << "\n";

	if (argc > 2) {
		/*
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
		/*
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
		*/
		if (strcmp(argv[1],"Teapot") == 0){
			int tess;

    		printf("helelo");
    		tess = atoi(argv[3]);
    		Figure* f = bezierPatch_parse(argv[2],tess);
    		f->save(argv[4]);
			/*
			cout << "Drawing Teapot!\n";
			generatePatch(argv[2],argv[3],argv[4]);
			*/
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

}

/*

void generatePatch(char* patch_path, char* tesselation, char* f_path){
    int tess;

    tess = atoi(tesselation);

    Figure* f = bezierPatch_parse(patch_path,tess);
    f->save(f_path);
}
// Writes all our Figure's Vertexes on the desired file ("f_path")
void writeFile(Figure* f, string f_path){
    char buff[1024];
    int i;
    int size = f->getsize();
    Vertex* v;

    system("mkdir -p ../files3d/ ");
    string path = "../files3d/" + f_path;
    ofstream file (path,std::ofstream::out);

    for(i=0;i<size;i++){
        f->getvertexat(i,&v);
        sprintf(buff, "%f %f %f\n", v->getx(), v->gety(), v->getz());
        file << buff;
    }

    file.close();
}
*/