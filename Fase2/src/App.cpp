#include "App.h"

App::App(){
    t = Transformation::Transformation();
    name = "";
    next = vector<App>();
    vertexes = vector<Vertex>();
}

App::App(string name, vector<App> next, vector<Vertex> vertexes, Transformation t){
    this->name = name;
    this->next = next;
    this->vertexes = vertexes;
    this->t = t;
}