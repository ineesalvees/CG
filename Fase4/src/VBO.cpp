#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <IL/il.h>

#include "../headers/Figure.h"
#include "../headers/Vertex.h"
#include "../headers/VBO.h"

#include <vector>
#include "../headers/Texture.h"

using std::vector;

VBO::VBO(std::vector<Vertex> vertexes,std::vector<Vertex> norm,std::vector<Vertex> tex){
    this->vertexes = vertexes;
    this->norm = norm;
    this->tex = tex;
}
void VBO::setUpTexture(std::string t_file){
    unsigned int t,tw,th;
    unsigned char *texData;
    ilInit();

    ilEnable(IL_ORIGIN_SET);
    ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
    ilGenImages(1, &t);
    ilBindImage(t);
    ilLoadImage((ILstring) t_file.c_str());
    tw = ilGetInteger(IL_IMAGE_WIDTH);
    th = ilGetInteger(IL_IMAGE_HEIGHT);
    ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
    texData = ilGetData();

    glGenTextures(1, &glu);
    glBindTexture(GL_TEXTURE_2D, glu);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
    glBindTexture(GL_TEXTURE_2D, 0);
}
void VBO::set() {
    //setup
    buff_size[0] = vertexes.size();
    buff_size[1] = norm.size();
    buff_size[2] = tex.size();

    int index = 0;
    float* vertex_array = (float*) malloc(sizeof(float) * (vertexes.size()) * 3);
    float* normal_array = (float*) malloc(sizeof(float) * (norm.size()) * 3);
    float* texture_array = (float*) malloc(sizeof(float) * (tex.size()) * 2);

    for(Vertex v: vertexes){
        vertex_array[index] = v.getx();
        vertex_array[index+1] = v.gety();
        vertex_array[index+2] = v.getz();
        index+=3;
    }
    index = 0;
    for(Vertex n: vertexes){
        normal_array[index] = n.getx();
        normal_array[index+1] = n.gety();
        normal_array[index+2] = n.getz();
        index+=3;
    }

    index = 0;
    for(Vertex t: vertexes){
        texture_array[index] = t.getx();
        texture_array[index+1] = t.gety();
        index+=2;
    }
//buffers = meu buffs
    glGenBuffers(3, buffs);
    glBindBuffer(GL_ARRAY_BUFFER, buffs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * buff_size[0] * 3, vertex_array, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, buffs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * buff_size[1] * 3, normal_array, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, buffs[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * buff_size[2] * 2, texture_array, GL_STATIC_DRAW);

    free(vertex_array);
    free(normal_array);
    free(texture_array);
}

void VBO::render () {

    float amb[4] = {0.2, 0.2, 0.2, 1};
    float diff[4] = {0.8, 0.8, 0.8, 1};
    float spec[4] = {0, 0, 0, 1};
    float emi[4] = {texture->getR(),texture->getG(),texture->getB(),1};
    float shin = 200;

    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shin);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emi);

    glBindBuffer(GL_ARRAY_BUFFER, buffs[0]);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    if(buff_size[1]){
        glBindBuffer(GL_ARRAY_BUFFER, buffs[1]);
        glNormalPointer(GL_FLOAT, 0, 0);
    }

    if(buff_size[2]){
        glBindBuffer(GL_ARRAY_BUFFER, buffs[2]);
        glTexCoordPointer(2, GL_FLOAT, 0, 0);
        glBindTexture(GL_TEXTURE_2D, glu);
    }

    glDrawArrays(GL_TRIANGLES, 0, buff_size[0] * 3);
    glBindTexture(GL_TEXTURE_2D, 0);
}