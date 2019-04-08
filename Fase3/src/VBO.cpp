#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "../headers/Figure.h"
#include "../headers/Vertex.h"
#include "../headers/VBO.h"

#include <vector>

using std::vector;

void VBO::render (std::vector<Vertex*> vertexes) {

	//setup
	buff[0] = vertexes.size();

    int index = 0;
    float* vertex_array = (float*) malloc(sizeof(float) * (vertexes.size()) * 3);

    for(Vertex* v: vertexes){
        vertex_array[index] = v->getx();
        vertex_array[index+1] = v->gety();
        vertex_array[index+2] = v->getz();
        index+=3;
    }

    glGenBuffers(1, buffers);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * buff[0] * 3, vertex_array, GL_STATIC_DRAW);

    free(vertex_array);

    //render
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, buff[0] * 3);
}