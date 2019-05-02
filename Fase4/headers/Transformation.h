#ifndef _Transformation_H_
#define _Transformation_H_

#include "Vertex.h"
#include <stdio.h>
#include <vector>
using namespace std;

class Transformation{
	private:
		float x;
		float y;
		float z;

	public:
		Transformation();
		Transformation (float x, float y, float z);
		
		float getx () {
			return this->x;
		}

		float gety () {
			return this->y;
		}

		float getz () {
			return this->z;
		}
		/*
		float getx ();
		float gety ();
		float getz ();
		*/
		virtual void make () { };
};

class Translation : public Transformation {
    float time;
    std::vector<Vertex*> curve_points;
    std::vector<Vertex*> catmull_points;

public:
    Translation();
    Translation(float x, float y, float z,float t);
    void pushvertex(Vertex *v);
    void generateCurve();
    void drawCurve();
    int getCurveSize();
    void make();

   	float getTime(){
		return this->time;
	}

	void setTime(float time){
		this->time = time;
	}
    virtual ~Translation(void);

};

class Rotation : public Transformation {
	private:
		float time;
		float angle;

	public:
		Rotation(float time, float x, float y, float z, float angle);
	    void make();

		float getTime(){
			return time;
		}
		float getAngle() {
			return angle;
		}
    virtual ~Rotation(void);

};

class Color : public Transformation {
	public:
		Color(float r, float b, float g);
	    void make() override;
	    virtual ~Color(void);

};

class Scale : public Transformation {
	public:
		Scale(float x, float y, float z);
	    void make() override;
	    virtual ~Scale(void);


};
#endif
