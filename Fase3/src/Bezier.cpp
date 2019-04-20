#include "../headers/Bezier.h"

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

    p_size = stoi(line);
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