#ifndef _Rotation_H_
#define _Rotation_H_

#include<GL/glut.h>

class Rotation{
	private:
		float angle, axisX, axisY, axisZ;

	public:
		Rotation();
		Rotation(float angle, float axisX, float axisY, float axisZ);

		float getAngle(){
			return angle;
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