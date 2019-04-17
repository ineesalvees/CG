#ifndef _Transformation_H_
#define _Transformation_H_

#include "Translation.h"
#include "Color.h"
#include "Scale.h"


class Transformation{
	private:
		float x;
		float y;
		float z;

	public:
		Transformation();
		Transformation (float x, float y, float z);
		float getx ();
		float gety ();
		float getz ();
		virtual void make () {};
};

class Rotation : public Transformation {
	private:
		float time, axisX, axisY, axisZ;

	public:
		Rotation();
		Rotation(float time, float axisX, float axisY, float axisZ);

		float getTime(){
			return time;
		}

		float getAxisX(){
			return axisX;
		}

		float getAxisY(){
			return axisY;
		}

		float getAxisZ(){
			return axisZ;
		}
};

#endif
