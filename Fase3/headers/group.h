#ifndef _Group_H_
#define _Group_H_

#include <vector>
#include "VBO.h"
#include "Transformation.h"

using std::vector;


class Group {
	private:
		std::vector<VBO> vbos; 
		std::vector<Transformation> transformations;
		std::vector<Group> child;

	public:
		

};
#endif