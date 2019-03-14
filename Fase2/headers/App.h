#ifndef _App_H_
#define _App_H_

#include <vector>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include<GL/glut.h>
#include "Vertex.h"
#include "Transformation.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class App{
    private:
        string name;
        vector<App> next;
        vector<Vertex> vertexes;
        Transformation t;
    
    public:
        App();
        App(string name, vector<App> next, vector<Vertex> vertexes, Transformation t);

        string getName(){
            return this->name;
        }

        vector<App> getNext(){
            return this->next;
        }
        
        vector<Vertex> getVertexes(){
            return this->vertexes;
        }

        Transformation getTransformation(){
            return this->t;
        }

        void setName(string n){
            this->name = n;
        }

        void setNext(vector<App> n){
            this->next = n;
        }

        void setVertexes(vector<Vertex> v){
            this->vertexes = v;
        }

        void setTransformation(Transformation t){
            this->t = t;
        }
};
#endif