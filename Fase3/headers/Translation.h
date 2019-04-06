#ifndef _TRANSLATION_H_
#define _TRANSLATION_H_

#include<GL/glut.h>
#include "Vertex.h"
#include <vector>

class Translation{
	private:
		std::vector<Vertex> vertexes;
		float time;

	public:
		Translation();
		Vertex getvertex (int i);
  		void pushvertex (Vertex *v);
  		int getsize();

		float getTime(){
			return this->time;
		}

		void setTime(float time){
			this->time = time;
		}

};
#endif
