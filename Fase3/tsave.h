#ifndef _Transformation_H_
#define _Transformation_H_

#include "Translation.h"
#include "Color.h"
#include "Scale.h"
#include "Rotation.h"

class Transformation{
	private:
		Translation translation;
		Rotation rotation;
		Scale scale;
		Color color;

	public:
		Transformation();
		Transformation(Translation t, Rotation r, Scale s, Color c);

		Translation getTranslation(){
			return translation;
		}

		Rotation getRotation(){
			return rotation;
		}

		Scale getScale(){
			return scale;
		}

		Color getColor(){
			return color;
		}

		void setTranslation(Translation translation){
			this->translation = translation;
		}

		void setRotation(Rotation rotation){
			this->rotation = rotation;
		}

		void setScale(Scale scale){
			this->scale = scale;
		}

		void setColor(Color color){
			this->color = color;
		}
};
#endif