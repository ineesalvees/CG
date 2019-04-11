#ifndef _Transformation_H_
#define _Transformation_H_

#include "Translation.h"
#include "Color.h"
#include "Scale.h"
#include "Rotation.h"

class Transformation{
	private:
		float x;
		float y;
		float z;

	public:
		Transformation (float x, float y, float z);
		float getx ();
		float gety ();
		float getz ();
		virtual void make () {};
};
#endif