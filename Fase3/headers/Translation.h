#ifndef _TRANSLATION_H_
#define _TRANSLATION_H_

#include "Vertex.h"
#include "Transformation.h"
#include <vector>

#define POINT_COUNT 5

class Translation /*: public Transformation */{
	private:
		std::vector<Vertex> vertexes;
		float time;
		float p[POINT_COUNT][3];

	public:

		Translation();
		Vertex getvertex (int i);
  		void pushvertex (Vertex *v);
  		int getsize();
  		void getCatmullRomPoint(float t, float *p0, float *p1, float *p2, float *p3, float *pos, float *deriv);
  		void getGlobalCatmullRomPoint(float gt, float *pos, float *deriv);
  		void renderCatmullRomCurve();
  		void multMatrixVector(float *m, float *v, float *res);

  

		float getTime(){
			return this->time;
		}

		void setTime(float time){
			this->time = time;
		}

};
#endif
