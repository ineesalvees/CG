#ifndef _TRANSLATION_H_
#define _TRANSLATION_H_

#include<GL/glut.h>

class Translation{
	private:
		float x, y, z;

	public:
		Translation();
		Translation (float x, float y, float z);

		float getX(){
			return this->x;
		}

		float getY(){
			return this->y;
		}

		float getZ(){
			return this->z;
		}

		void setX(float x){
			this->x = x;
		}

		void setY(float y){
			this->y = y;
		}

		void setZ(float z){
			this->z = z;
		}
};
#endif