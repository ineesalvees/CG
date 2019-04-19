#ifndef _BEZIER_H_
#define _BEZIER_H_

#include "../headers/Figure.h"
#include <string>
#include <fstream>
#include <iostream>


class Bezier {
	Figure* bezierPatch_parse(std::string patch_path, int tesselation);
};

#endif