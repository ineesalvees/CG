#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include "../headers/Figure.h"
#include "../headers/Vertex.h"
#include "../headers/VBO.h"

#include <vector>
#include "../headers/Texture.h"

using std::vector;

VBO::VBO(std::vector<Vertex> vertexes){
    this->vertexes = vertexes;
}

void VBO::render () {

	//setup
	buff[0] = vertexes.size();
    buff[1] = norm.size();
    buff[2] = tex.size();

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

    glGenBuffers(3, buffers);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * buff[0] * 3, vertex_array, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * buff[1] * 3, normal_array, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * buff[2] * 2, texture_array, GL_STATIC_DRAW);

    free(vertex_array);
    free(normal_array);
    free(texture_array);

    //render
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, buff[0] * 3);
}