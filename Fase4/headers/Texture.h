#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <string>
//#include "IL/il.h"


using namespace std; 
class Texture{
	private:
		float r,g,b;
		std::string texture;

	public:
		Texture();
		Texture(float r, float g, float b, std::string texture);

		float getR() {
			return r;
		}
		float getG() {
			return g;
		}
		float getB() {
			return b;
		}
		std::string getTexture() {
			return texture;
		}
		

};
#endif
