#ifndef _BEZIER_H_
#define _BEZIER_H_

#include "Figure.h"
#include <string>
#include <fstream>
#include <iostream>


class Bezier {
	public:
		Figure* bezierPatch_parse(std::string patch_path, int tesselation);
		void processPatch(int tesselation, int n);
		Vertex* bezierCalc(float u, float v, int n_patch);
		Vertex* vertexCalc(float t, float *p1, float *p2, float *p3, float *p4);
};

#endif