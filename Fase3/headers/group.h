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
		std::vector<Group> children;

	public:
		std::vector<VBO> getVBOs ();
		std::vector<Transformation> getTransformations ();
		std::vector<Group> getChildren ();
		void pushVBO (VBO vbo);
		void pushTransformation (Transformation transformation);
		void pushGroup (Group group);
};

#endif